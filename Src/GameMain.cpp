//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１１　　　　　　                 ver 3.2        2023.1.31
//
//		ゲームのメイン処理
//																GameMain.cpp
//=============================================================================
#include "GameMain.h"
#include "Playchar.h"
#include "Camera.h"
#include "Map.h"
#include "Weapon.h"
#include "Effect.h"
#include "BackFore.h"
#include "SceneManager.h"
#include "ObjectManager.h"

namespace {
	CGameMain* gameMainInstance;
}

// ============================================================================================
//
// CGameMain ゲームメインクラスの処理
//
// ============================================================================================
//------------------------------------------------------------------------
//
//	ゲームメインクラスのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CGameMain::CGameMain(CMain*	pMain)
{
	gameMainInstance = this;
	m_pMain = pMain;		// メインクラス

	m_pD3D = nullptr;			//	Direct3Dオブジェクト
	m_pXAudio = nullptr;		//	XAudioオブジェクト
	m_pDI = nullptr;			//	DirectInputDオブジェクト
	m_pFont = nullptr;			//	フォントテクスチャー
	m_pShader = nullptr;		//	シェーダー
	m_pFbxMeshCtrl = nullptr;	// メッシュコントロールクラス

	m_dwGameStatus = 0;		// ゲームステータス

	// カメラ・ライト・ビュー
	m_vEyePt = VECTOR3(0,0,0);		// カメラ（視点）位置
	m_vLookatPt = VECTOR3(0,0,0);	// 注視位置
	m_mView = XMMatrixIdentity();	// ビューマトリックス
	m_mProj = XMMatrixIdentity();	// プロジェクションマトリックス
	m_vLightDir = VECTOR3(0,0,0);	// ディレクショナルライトの方向

	// プロシージャ
	m_pPcProc = nullptr;
	m_pCameraProc = nullptr;
	m_pMapProc = nullptr;
	m_pWeaponProc = nullptr;
	m_pEffectProc = nullptr;
	m_pBackForeProc = nullptr;

	// サウンド
	m_pSeLazer = nullptr;
	m_pSeNitro = nullptr;
	m_pSeDead = nullptr;
	m_pSeFire = nullptr;
	m_pBgm1 = nullptr;

	SceneManager::Start();
	ObjectManager::Start();
}
//------------------------------------------------------------------------
//
//	ゲームメインクラスのデストラクタ	
//
//------------------------------------------------------------------------
CGameMain::~CGameMain()
{
	ObjectManager::Release();
	SceneManager::Release();

	MyImgui::ImguiQuit();          // -- 2020.11.15    // MyImguiの終了処理

	SAFE_DELETE(m_pSeLazer);
	SAFE_DELETE(m_pSeFire);
	SAFE_DELETE(m_pSeDead);
	SAFE_DELETE(m_pSeNitro);
	SAFE_DELETE(m_pBgm1);

	SAFE_DELETE(m_pPcProc);
	SAFE_DELETE(m_pCameraProc);
	SAFE_DELETE(m_pMapProc);
	SAFE_DELETE(m_pWeaponProc);
	SAFE_DELETE(m_pEffectProc);
	SAFE_DELETE(m_pBackForeProc);

	SAFE_DELETE(m_pFbxMeshCtrl);    // -- 2021.2.4
	SAFE_DELETE(m_pShader);
	SAFE_DELETE(m_pFont);
	SAFE_DELETE(m_pDI);
	SAFE_DELETE(m_pXAudio);
	SAFE_DELETE(m_pD3D);

	CoUninitialize();   // COMの解放
}

//------------------------------------------------------------------------
//
//	アプリケーションの初期化処理	
//
//  引数　なし
//
//	戻り値 HRESULT
//		S_OK	= 正常
//		E_FAIL	= 異常
//
//------------------------------------------------------------------------
HRESULT CGameMain::Init()
{
	// ＣＯＭの初期化
	//CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	CoInitialize( NULL );

	// Direct3Dの初期化
	m_pD3D = new CDirect3D;
	if (FAILED(m_pD3D->InitD3D(m_pMain->m_hWnd, WINDOW_WIDTH, WINDOW_HEIGHT))) {
		MessageBox(0, _T("Direct3Dを初期化出来ません"), nullptr, MB_OK);
		return E_FAIL;
	}

	// シェーダーの初期化
	m_pShader = new CShader(m_pD3D);
	if (FAILED(m_pShader->InitShader())) {
		MessageBox(0, _T("Shaderを生成・初期化出来ません"), nullptr, MB_OK);
		return E_FAIL;
	}

	// XAudio2の初期化
	m_pXAudio = new CXAudio;
	if (FAILED(m_pXAudio->InitAudio(m_pMain->m_hWnd))) {
		MessageBox(0, _T("XAudio2を初期化出来ません"), nullptr, MB_OK);
		return E_FAIL;
	}

	// DirectInputの初期化
	m_pDI = new CDirectInput;
	if (!(m_pDI->StartDirectInput(m_pMain->m_hInstance, m_pMain->m_hWnd, 
                    INIT_KEYBOARD | INIT_MOUSE | INIT_JOYSTICK, WINDOW_WIDTH, WINDOW_HEIGHT))) {
		MessageBox(0, _T("DirectInputを初期化出来ません"), nullptr, MB_OK);
		return E_FAIL;
	}

	// フォントテクスチャーの初期化
	m_pFont = new CFontTexture(m_pShader);

	// MyImguiの初期化
	MyImgui::ImguiInit(m_pMain->m_hWnd, m_pD3D, WINDOW_WIDTH, WINDOW_HEIGHT);           // -- 2020.11.15

	// Fbxメッシュコントロールクラス
	m_pFbxMeshCtrl = new CFbxMeshCtrl(m_pShader);                       // -- 2021.2.4

	// ----------------------------------------------------------------------------------------
	// 変数の初期化
	m_dwGameStatus = GAMEMAIN;
	m_vLightDir = normalize( VECTOR3(0.8f, 1, -1) );  // 光源座標の初期値。正規化する

	// プロジェクショントランスフォーム（射影変換）の初期値
	//m_mProj = XMMatrixPerspectiveFovLH((FLOAT)(XM_PI / 4), (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0);
	m_mProj = XMMatrixPerspectiveFovLH(XMConvertToRadians(38.0f), (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0);

	// ビュートランスフォーム（視点座標変換）の初期値
	VECTOR3 vUpVec(0.0f, 1.0f, 0.0f);//上方位置
	m_vEyePt = VECTOR3(0.0f, 1.0f, 0.0f);
	m_vLookatPt = VECTOR3(0.0f, 1.0f, 1.0f);
	m_mView = XMMatrixLookAtLH(m_vEyePt, m_vLookatPt, vUpVec);

	// 各プロシージャの初期化
	m_pPcProc = new CPcProc(this);		// ＰＣプロシージャ

	m_pCameraProc = new CCameraProc(this);	// カメラプロシージャ

	m_pEffectProc = new CEffectProc(this);  // ３Ｄ効果

	m_pWeaponProc = new CWeaponProc(this);	// Weaponプロシージャ

	m_pMapProc = new CMapProc(this);	// Mapプロシージャ

	m_pBackForeProc = new CBackForeProc(this);  // 前景・背景

	// サウンド
	m_pSeLazer = new CXAudioSource( m_pXAudio, _T("Data/Sound/Lazer.wav"), 10);
	m_pSeNitro = new CXAudioSource( m_pXAudio, _T("Data/Sound/Nitro2.WAV"), 10);
	m_pSeDead = new CXAudioSource( m_pXAudio, _T("Data/Sound/Dead.wav"), 10);
	m_pSeFire = new CXAudioSource( m_pXAudio, _T("Data/Sound/M_FIRE4.WAV"), 10);
	m_pBgm1 = new CXAudioSource( m_pXAudio, _T("Data/Sound/DO_HT204.WAV"));
	//m_pBgm1 = new CXAudioSource( m_pXAudio, _T("Data/Sound/B003B.MID"));

	// ＢＧＭの再生
	m_pBgm1->Play(AUDIO_LOOP);


	// マップのロード
	//（ 最初はマップ１をロードする）
	m_pMapProc->LoadMap(1);

	return S_OK;
}

//------------------------------------------------------------------------
//
//	ゲームのループ処理	
//
//  引数　なし
//
//	戻り値 なし
//
//------------------------------------------------------------------------
void CGameMain::Update()
{

	m_pDI->GetInput();			// 入力情報の取得
	m_pFont->Refresh();         // フォント情報のリフレッシュ
	MyImgui::ImguiNewFrame();   // MyImgui描画前処理    // -- 2020.11.15

	if (m_pDI->CheckKey(KD_TRG, DIK_F4))  ChangeScreenMode();   // フルスクリーンの切り替え       // -- 2018.12.14

	switch (m_dwGameStatus)
	{

	case GAMEMAIN:			// ゲーム主処理
		GameMain();
		break;

	case GAMEEND:			// ゲーム終了
		PostQuitMessage(0);
		break;

	}

	MyImgui::ImguiRender();      // MyImgui実描画処理    // -- 2020.11.15

	//画面更新（バックバッファをフロントバッファに）
	//m_pD3D->m_pSwapChain->Present(1, 0);                   // 60fps Vsync
	m_pD3D->m_pSwapChain->Present(0, 0);                   // Vsyncなし

	SceneManager::Update();
	ObjectManager::Update();
}

//------------------------------------------------------------------------
//
//	ゲームのメイン処理	
//
//  引数　なし
//
//	戻り値 なし
//
//------------------------------------------------------------------------
void CGameMain::GameMain()
{

	//画面クリア（実際は単色で画面を塗りつぶす処理）
	float ClearColor[4] = { 0,0,0,1 };// クリア色作成　RGBAの順
	m_pD3D->ClearRenderTarget(ClearColor); // 画面クリア

	// Mapの更新
	m_pMapProc->Update();

	// ＰＣの更新
	m_pPcProc->UpdateAll();

	// 武器の更新
	m_pWeaponProc->UpdateAll();

	// ３Ｄ効果の更新
	m_pEffectProc->UpdateAll();

	// 前景・背景の更新
	m_pBackForeProc->Update();

	// カメラの更新
	m_pCameraProc->UpdateAll();

}

void CGameMain::Draw()
{
	ObjectManager::Draw();
	SceneManager::Draw();
}

//------------------------------------------------------------------------
//
//	アプリケーションの終了処理	
//
//  引数　なし
//
//	戻り値 なし
//
//------------------------------------------------------------------------
void CGameMain::Quit()
{
	;
}

//------------------------------------------------------------------------    // -- 2018.12.14
//
//	ウィンドウモードとフルスクリーンモードを切り替える処理	
//
//  引数　モード  0:ウインドウモード　1:フルスクリーン　-1:モード切り替え（省略値）
//
//	戻り値 なし
//
//------------------------------------------------------------------------
HRESULT CGameMain::ChangeScreenMode(int nMode)
{
	HRESULT Ret = S_OK;
	BOOL bFullScreen;  // フルスクリーンモードか？

	//	現在のスクリーンモードを得る
	m_pD3D->m_pSwapChain->GetFullscreenState(&bFullScreen, nullptr);

	switch (nMode)
	{
	case 0:    // ウインドウモードにする
		if( bFullScreen ) Ret = m_pD3D->m_pSwapChain->SetFullscreenState(false, nullptr);
		break;
	case 1:    // フルスクリーンモードにする
		if( !bFullScreen ) Ret = m_pD3D->m_pSwapChain->SetFullscreenState(true, nullptr);
		break;
	default:   // 現在のモードを切り替える
		if (bFullScreen)
		{
			Ret = m_pD3D->m_pSwapChain->SetFullscreenState(false, nullptr);
		}
		else {
			Ret = m_pD3D->m_pSwapChain->SetFullscreenState(true, nullptr);
		}
	}

	return Ret;
}

CGameMain* GameDevice()
{
	return gameMainInstance;
}

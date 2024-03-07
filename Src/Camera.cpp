//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１１                             ver 3.2        2023.1.31
//
//		カメラ制御
//
//		(視点変更処理・障害物回避処理が入っている)
//
//																Camera.cpp
//=============================================================================
#include  "Camera.h"
#include  "Playchar.h"
#include  "Map.h"

//==========================================================================================================================
//
// カメラプロシージャのコンストラクタ
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
// -------------------------------------------------------------------------------------------------------------------------
CCameraProc::CCameraProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_nCamObjNo = 0;    // 選択するカメラオブジェクトＮＯ初期値０

	// -------------------------------------------------------------------------------------
	// オブジェクトの生成
	// 
	// -------------------------------------------------------------------------------------
	// カメラオブジェクト[0]     Ctrl:0 TPS
	m_pObjArray.push_back(new CCameraObj(this));     // m_pObjArrayにオブジェクトを登録する
	((CCameraObj*)m_pObjArray.back())->InitCam(      // オブジェクトに初期値を設定する
		0,                                           // カメラ制御（0:TPS)
		VECTOR3(0.0f, 2.0f, 0.0f),                   // TPS 基準注視点
		VECTOR3(0.0f, 2.2f, -6.7f),                  // TPS 基準視点
		1.5f,                                        // カメラ回転増分値
		0.05f                                        // カメラ移動増分値
	);

}
// ---------------------------------------------------------------------------
//
// カメラプロシージャの更新処理
//
//
// ---------------------------------------------------------------------------
void CCameraProc::Update()
{
	// カメラ制御の変更
	// 表示するオブジェクトを切り替える
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_F)) // Fキー
	{
		m_nCamObjNo = (m_nCamObjNo + 1) % m_pObjArray.size();   // 表示するオブジェクトを切り替える
		//((CCameraObj*)m_pObjArray[m_nCamObjNo])->SetCamBase();  // カメラ変位初期値を設定する
	}
}
//-----------------------------------------------------------------------------
// カメラプロシージャからカメラオブジェクトの基準値に初期値を設定する処理
//
// ・カメラ制御、基準ローカルベクトル、増分値などをカメラオブジェクトに設定する処理
//   この処理はオブジェクトのInitCam()を使用して設定する
//
//   引数
//      int no           オブジェクトＮｏ
//      int ctrl         カメラ制御（0:ＴＰＳ視点  1:ＦＰＳ視点  2:固定視点）
//      VECTOR3 lookat   基準ローカル注視点ベクトル
//      VECTOR3 eye      基準ローカル視点ベクトル
//      float rot        角度増分
//      float dis        移動増分
//
//-----------------------------------------------------------------------------
void CCameraProc::InitCam(int no, int ctrl, VECTOR3 lookat, VECTOR3 eye, float rot, float dist)
{
	if (no < 0 || no >= m_pObjArray.size())
	{
		MessageBox(nullptr, _T("■ InitCam( No,　・・・・・) ■"), _T("指定要素番号のオブジェクトがありません"), MB_OK);
		return;
	}

	((CCameraObj*)m_pObjArray[no])->InitCam(ctrl, lookat, eye, rot, dist);
}

// ============================================================================================================
// ---------------------------------------------------------------------------
//
// カメラオブジェクトのコンストラクタ
//
// ---------------------------------------------------------------------------
CCameraObj::CCameraObj(CBaseProc* pProc) : CBaseObj(pProc)
{
	// 基点ワールドマトリックスの初期値
	m_mBaseWorld = XMMatrixTranslation(0, 0, 0);

}
// ---------------------------------------------------------------------------
//
// カメラオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CCameraObj::~CCameraObj()
{
	;
}
//----------------------------------------------------------------------------- 
// カメラオブジェクトの制御
//
//　ＰＣの動きに合わせてカメラを制御する
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CCameraObj::Update()
{
	// プロシージャで指定したオブジェクトＮＯのオブジェクトのみ処理を行う
	if (((CCameraProc*)m_pProc)->GetCamObjNo() != m_dwObjNo) return;

	// 注視点・視点の基点となる基点ワールドマトリックスの設定
	if (m_nCtrl == 0)  // TPS
	{
		// TPSは、ＰＣのローカル軸マトリックスを設定する
		m_mBaseWorld = m_pGMain->m_pPcProc->GetPcObjPtr()->GetLocalMatrix();
	}
	else if (m_nCtrl == 1) {  // FPS
		// FPSは、ＰＣのワールドマトリックスを設定する
		m_mBaseWorld = m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld();
	}
	else {  // 固定カメラ
		// 固定カメラは絶対座標の原点を設定する
		m_mBaseWorld = XMMatrixTranslation(0, 0, 0);
	}

	// カメラオブジェクトの位置を手動操作
	ManualOperation();

	// 注視点のベクトルを作成する処理
	// (注視点のローカル座標と基点ワールドマトリックスを掛け合わせ、注視点マトリックスを得る)
	MATRIX4X4 mLookat = XMMatrixTranslationFromVector(m_vLocalLookat) * m_mBaseWorld;
	m_pGMain->m_vLookatPt = GetPositionVector(mLookat);    // 注視点マトリックスから注視点位置を得る

	// カメラ（視点）ベクトルを作成する処理
	// (カメラ（視点）のローカル座標と基点ワールドマトリックスを掛け合わせ、視点マトリックスを得る)
	MATRIX4X4 mEye = XMMatrixTranslationFromVector(m_vLocalEye) * m_mBaseWorld;
	m_pGMain->m_vEyePt = GetPositionVector(mEye);        // 視点マトリックスから視点位置を得る

	// TPS視点の時、障害物を回避する処理
	if (m_nCtrl == 0) EvasiveObstacle();

	// 視点ベクトルと注視点ベクトルからカメラのワールドマトリックスを得る（今は使用していない）
	m_mWorld = GetLookatMatrix(m_pGMain->m_vEyePt, m_pGMain->m_vLookatPt);

	// ビューマトリックスの作成
	VECTOR3 vUpVec(0.0f, 1.0f, 0.0f);    // 上方位置を絶対座標の上方向とする
	// カメラ(視点)の位置、上方向、および注視点を使用して、左手座標系のビュー行列を作成
	m_pGMain->m_mView = XMMatrixLookAtLH(m_pGMain->m_vEyePt, m_pGMain->m_vLookatPt, vUpVec);

	// カメラの位置、上方向、およびカメラの向きを使用して、左手座標系のビュー行列を作成（使用していない）
	//VECTOR3 vEyeDir = XMVector3TransformCoord(VECTOR3(0, 0, 1), GetRotateMatrix(m_mWorld));
	//m_pGMain->m_mView = XMMatrixLookToLH(m_pGMain->m_vEyePt, vEyeDir, vUpVec);

	// ライト視点からのビュートランスフォーム（ShadowMap用）ライト視点をＰＣの位置に合わせるとき（使用していない）
	//m_pGMain->m_vLightEye = m_pGMain->m_vLookatPt + m_pGMain->m_vLightDir * 100.0f;	        // カメラ（視点）位置を光源の方向100ｍの位置にする
	//m_pGMain->m_mLightView = XMMatrixLookAtLH(m_pGMain->m_vLightEye, m_pGMain->m_vLookatPt, vUpVec);

}

//-----------------------------------------------------------------------------
// カメラオブジェクトの基準値に初期値を設定する処理
//
// ・カメラ制御、基準ローカルベクトル、増分値などを設定する処理
//
//   引数
//      int ctrl         カメラ制御（0:ＴＰＳ視点  1:ＦＰＳ視点  2:固定視点）
//      VECTOR3 lookat   基準ローカル注視点ベクトル
//      VECTOR3 eye      基準ローカル視点ベクトル
//      float rot        角度増分
//      float dis        移動増分
//
//-----------------------------------------------------------------------------
void CCameraObj::InitCam(int ctrl, VECTOR3 lookat, VECTOR3 eye, float rot, float dist)
{
	m_nCtrl = ctrl;
	m_vBaseLocalLookat = lookat;
	m_vBaseLocalEye = eye;
	m_fBaseRotUp = rot;
	m_fBaseDistUp = dist;

	SetCamBase();   // カメラ変位初期値を設定する
}
//-----------------------------------------------------------------------------
// 障害物を回避する処理
//
// ・視点と注視点との間に障害物があった場合、視点を障害物の前に移動する処理
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CCameraObj::EvasiveObstacle()
{
	VECTOR3 vHit;
	VECTOR3 vNorm;
	if (m_pGMain->m_pMapProc->Hitcheck(m_pGMain->m_vEyePt, m_pGMain->m_vLookatPt, &vHit, &vNorm))   // 障害物との接触チェック
	{
		MATRIX4X4 mTemp;
		mTemp = GetLookatMatrix(vHit, m_pGMain->m_vLookatPt);        // 障害物との接触点から注視位置を見るマトリックス
		mTemp = XMMatrixTranslation(0.0f, 0.0f, 0.01f) * mTemp;      // 障害物との接触点から1cm注視方向に移動した視点位置を得る
		m_pGMain->m_vEyePt = GetPositionVector(mTemp);
	}
}
//----------------------------------------------------------------------------- 
// カメラオブジェクトの手動操作制御
//
//   カメラオブジェクトの位置を手動で操作する
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CCameraObj::ManualOperation()
{
	CDirectInput* pDI = m_pGMain->m_pDI;

	// カメラ視点の相対位置の変更
	if (m_nCtrl == 0)   // TPS視点の時
	{
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD6) || pDI->CheckKey(KD_DAT, DIK_RBRACKET)) // →  ]
		{
			SetLocalEyeTPS(m_fBaseRotUp, 0, 0);
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD4) || pDI->CheckKey(KD_DAT, DIK_SEMICOLON)) // ←  ;
		{
			SetLocalEyeTPS(-m_fBaseRotUp, 0, 0);
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD8) || pDI->CheckKey(KD_DAT, DIK_AT)) // ↑  @
		{
			SetLocalEyeTPS(0, m_fBaseRotUp, 0);
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD2) || pDI->CheckKey(KD_DAT, DIK_COLON)) // ↓  :
		{
			SetLocalEyeTPS(0, -m_fBaseRotUp, 0);
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD7) || pDI->CheckKey(KD_DAT, DIK_P)) // 近づける  P
		{
			SetLocalEyeTPS(0, 0, -m_fBaseDistUp);
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD9) || pDI->CheckKey(KD_DAT, DIK_LBRACKET)) // 遠ざかる  [
		{
			SetLocalEyeTPS(0, 0, m_fBaseDistUp);
		}
	}
	else if (m_nCtrl == 1) {    // FPS視点の時

		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD6) || pDI->CheckKey(KD_DAT, DIK_RBRACKET)) // →  ]
		{
			m_vLocalEye.x -= m_fBaseDistUp;
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD4) || pDI->CheckKey(KD_DAT, DIK_SEMICOLON)) // ←  ;
		{
			m_vLocalEye.x += m_fBaseDistUp;
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD8) || pDI->CheckKey(KD_DAT, DIK_AT)) // ↑  @
		{
			m_vLocalLookat.y += m_fBaseDistUp;
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD2) || pDI->CheckKey(KD_DAT, DIK_COLON)) // ↓  :
		{
			m_vLocalLookat.y -= m_fBaseDistUp;
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD7) || pDI->CheckKey(KD_DAT, DIK_P)) // 近づける  P
		{
			m_vLocalEye.z += m_fBaseDistUp;
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD9) || pDI->CheckKey(KD_DAT, DIK_LBRACKET)) // 遠ざかる  [
		{
			m_vLocalEye.z -= m_fBaseDistUp;
		}
	}
	else {    // 固定カメラの時

		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD6) || pDI->CheckKey(KD_DAT, DIK_RBRACKET)) // 右移動  ]
		{
			m_vLocalLookat.x += m_fBaseDistUp;
			m_vLocalEye.x += m_fBaseDistUp;
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD4) || pDI->CheckKey(KD_DAT, DIK_SEMICOLON)) // 左移動  ;
		{
			m_vLocalLookat.x -= m_fBaseDistUp;
			m_vLocalEye.x -= m_fBaseDistUp;
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD8) || pDI->CheckKey(KD_DAT, DIK_AT)) // 前移動  @
		{
			m_vLocalLookat.z += m_fBaseDistUp;
			m_vLocalEye.z += m_fBaseDistUp;
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD2) || pDI->CheckKey(KD_DAT, DIK_COLON)) // 後移動  :
		{
			m_vLocalLookat.z -= m_fBaseDistUp;
			m_vLocalEye.z -= m_fBaseDistUp;
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD7) || pDI->CheckKey(KD_DAT, DIK_P)) // ←  P
		{
			m_vLocalLookat.x -= m_fBaseDistUp;
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD9) || pDI->CheckKey(KD_DAT, DIK_LBRACKET)) // →  [
		{
			m_vLocalLookat.x += m_fBaseDistUp;
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD3) || pDI->CheckKey(KD_DAT, DIK_BACKSLASH)) // ↑  バックスラッシュ
		{
			m_vLocalLookat.z += m_fBaseDistUp;
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD1) || pDI->CheckKey(KD_DAT, DIK_SLASH)) // ↓  /
		{
			m_vLocalLookat.z -= m_fBaseDistUp;
		}
	}

	// 基準値に戻す処理
	if (pDI->CheckKey(KD_DAT, DIK_HOME) || pDI->CheckKey(KD_DAT, DIK_H))
	{
		SetCamBase();    // カメラ変位初期値を設定する
	}
}

//-----------------------------------------------------------------------------
// ＴＰＳのときカメラ位置の手動設定処理
//
//   m_vRotUp.xとm_vRotUp.yに回転角度変位値、
//   m_vPosUp.zに注視点から視点までの直線距離変位値が入っている、
//   その値を基に、変位値を計算し、その結果をm_vLocalEyeに設定する
//
//   引数	float fRotY : Ｙ回転
//			float fRotX : Ｘ回転
//			float fDist : 距離
//
//   戻り値　なし
//-----------------------------------------------------------------------------
void	CCameraObj::SetLocalEyeTPS(float fRotY, float fRotX, float fDist)
{
	m_vRotUp.x += fRotX;
	m_vRotUp.y += fRotY;
	m_vPosUp.z += fDist;

	MATRIX4X4 mRotY = XMMatrixRotationY(XMConvertToRadians(m_vRotUp.y));
	MATRIX4X4 mRotX = XMMatrixRotationX(XMConvertToRadians(m_vRotUp.x));
	m_vLocalEye = GetPositionVector(XMMatrixTranslationFromVector(m_vBaseLocalEye + m_vPosUp) * mRotX * mRotY);
}
//-----------------------------------------------------------------------------
// カメラ変位初期値を設定する処理
//
// ・基準ローカルベクトルをローカルベクトルに設定する。
// ・角度と位置の変位値のクリヤー
//
//   引数	なし
//
//   戻り値　なし
//-----------------------------------------------------------------------------
void	CCameraObj::SetCamBase()
{
	// カメラ変位の初期値を設定する
	m_vLocalLookat = m_vBaseLocalLookat;      // 基準ローカル注視点ベクトルをローカル注視点ベクトルに設定する
	m_vLocalEye = m_vBaseLocalEye;            // 基準ローカル視点ベクトルをローカル視点ベクトルに設定する
	m_vRotUp = VECTOR3(0, 0, 0);     // 角度変位値のクリヤー
	m_vPosUp = VECTOR3(0, 0, 0);     // 位置変位値のクリヤー

}
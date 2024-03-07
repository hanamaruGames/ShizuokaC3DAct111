//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�P�@�@�@�@�@�@                 ver 3.2        2023.1.31
//
//		�Q�[���̃��C������
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
// CGameMain �Q�[�����C���N���X�̏���
//
// ============================================================================================
//------------------------------------------------------------------------
//
//	�Q�[�����C���N���X�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CGameMain::CGameMain(CMain*	pMain)
{
	gameMainInstance = this;
	m_pMain = pMain;		// ���C���N���X

	m_pD3D = nullptr;			//	Direct3D�I�u�W�F�N�g
	m_pXAudio = nullptr;		//	XAudio�I�u�W�F�N�g
	m_pDI = nullptr;			//	DirectInputD�I�u�W�F�N�g
	m_pFont = nullptr;			//	�t�H���g�e�N�X�`���[
	m_pShader = nullptr;		//	�V�F�[�_�[
	m_pFbxMeshCtrl = nullptr;	// ���b�V���R���g���[���N���X

	m_dwGameStatus = 0;		// �Q�[���X�e�[�^�X

	// �J�����E���C�g�E�r���[
	m_vEyePt = VECTOR3(0,0,0);		// �J�����i���_�j�ʒu
	m_vLookatPt = VECTOR3(0,0,0);	// �����ʒu
	m_mView = XMMatrixIdentity();	// �r���[�}�g���b�N�X
	m_mProj = XMMatrixIdentity();	// �v���W�F�N�V�����}�g���b�N�X
	m_vLightDir = VECTOR3(0,0,0);	// �f�B���N�V���i�����C�g�̕���

	// �v���V�[�W��
	m_pPcProc = nullptr;
	m_pCameraProc = nullptr;
	m_pMapProc = nullptr;
	m_pWeaponProc = nullptr;
	m_pEffectProc = nullptr;
	m_pBackForeProc = nullptr;

	// �T�E���h
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
//	�Q�[�����C���N���X�̃f�X�g���N�^	
//
//------------------------------------------------------------------------
CGameMain::~CGameMain()
{
	ObjectManager::Release();
	SceneManager::Release();

	MyImgui::ImguiQuit();          // -- 2020.11.15    // MyImgui�̏I������

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

	CoUninitialize();   // COM�̉��
}

//------------------------------------------------------------------------
//
//	�A�v���P�[�V�����̏���������	
//
//  �����@�Ȃ�
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �ُ�
//
//------------------------------------------------------------------------
HRESULT CGameMain::Init()
{
	// �b�n�l�̏�����
	//CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	CoInitialize( NULL );

	// Direct3D�̏�����
	m_pD3D = new CDirect3D;
	if (FAILED(m_pD3D->InitD3D(m_pMain->m_hWnd, WINDOW_WIDTH, WINDOW_HEIGHT))) {
		MessageBox(0, _T("Direct3D���������o���܂���"), nullptr, MB_OK);
		return E_FAIL;
	}

	// �V�F�[�_�[�̏�����
	m_pShader = new CShader(m_pD3D);
	if (FAILED(m_pShader->InitShader())) {
		MessageBox(0, _T("Shader�𐶐��E�������o���܂���"), nullptr, MB_OK);
		return E_FAIL;
	}

	// XAudio2�̏�����
	m_pXAudio = new CXAudio;
	if (FAILED(m_pXAudio->InitAudio(m_pMain->m_hWnd))) {
		MessageBox(0, _T("XAudio2���������o���܂���"), nullptr, MB_OK);
		return E_FAIL;
	}

	// DirectInput�̏�����
	m_pDI = new CDirectInput;
	if (!(m_pDI->StartDirectInput(m_pMain->m_hInstance, m_pMain->m_hWnd, 
                    INIT_KEYBOARD | INIT_MOUSE | INIT_JOYSTICK, WINDOW_WIDTH, WINDOW_HEIGHT))) {
		MessageBox(0, _T("DirectInput���������o���܂���"), nullptr, MB_OK);
		return E_FAIL;
	}

	// �t�H���g�e�N�X�`���[�̏�����
	m_pFont = new CFontTexture(m_pShader);

	// MyImgui�̏�����
	MyImgui::ImguiInit(m_pMain->m_hWnd, m_pD3D, WINDOW_WIDTH, WINDOW_HEIGHT);           // -- 2020.11.15

	// Fbx���b�V���R���g���[���N���X
	m_pFbxMeshCtrl = new CFbxMeshCtrl(m_pShader);                       // -- 2021.2.4

	// ----------------------------------------------------------------------------------------
	// �ϐ��̏�����
	m_dwGameStatus = GAMEMAIN;
	m_vLightDir = normalize( VECTOR3(0.8f, 1, -1) );  // �������W�̏����l�B���K������

	// �v���W�F�N�V�����g�����X�t�H�[���i�ˉe�ϊ��j�̏����l
	//m_mProj = XMMatrixPerspectiveFovLH((FLOAT)(XM_PI / 4), (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0);
	m_mProj = XMMatrixPerspectiveFovLH(XMConvertToRadians(38.0f), (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0);

	// �r���[�g�����X�t�H�[���i���_���W�ϊ��j�̏����l
	VECTOR3 vUpVec(0.0f, 1.0f, 0.0f);//����ʒu
	m_vEyePt = VECTOR3(0.0f, 1.0f, 0.0f);
	m_vLookatPt = VECTOR3(0.0f, 1.0f, 1.0f);
	m_mView = XMMatrixLookAtLH(m_vEyePt, m_vLookatPt, vUpVec);

	// �e�v���V�[�W���̏�����
	m_pPcProc = new CPcProc(this);		// �o�b�v���V�[�W��

	m_pCameraProc = new CCameraProc(this);	// �J�����v���V�[�W��

	m_pEffectProc = new CEffectProc(this);  // �R�c����

	m_pWeaponProc = new CWeaponProc(this);	// Weapon�v���V�[�W��

	m_pMapProc = new CMapProc(this);	// Map�v���V�[�W��

	m_pBackForeProc = new CBackForeProc(this);  // �O�i�E�w�i

	// �T�E���h
	m_pSeLazer = new CXAudioSource( m_pXAudio, _T("Data/Sound/Lazer.wav"), 10);
	m_pSeNitro = new CXAudioSource( m_pXAudio, _T("Data/Sound/Nitro2.WAV"), 10);
	m_pSeDead = new CXAudioSource( m_pXAudio, _T("Data/Sound/Dead.wav"), 10);
	m_pSeFire = new CXAudioSource( m_pXAudio, _T("Data/Sound/M_FIRE4.WAV"), 10);
	m_pBgm1 = new CXAudioSource( m_pXAudio, _T("Data/Sound/DO_HT204.WAV"));
	//m_pBgm1 = new CXAudioSource( m_pXAudio, _T("Data/Sound/B003B.MID"));

	// �a�f�l�̍Đ�
	m_pBgm1->Play(AUDIO_LOOP);


	// �}�b�v�̃��[�h
	//�i �ŏ��̓}�b�v�P�����[�h����j
	m_pMapProc->LoadMap(1);

	return S_OK;
}

//------------------------------------------------------------------------
//
//	�Q�[���̃��[�v����	
//
//  �����@�Ȃ�
//
//	�߂�l �Ȃ�
//
//------------------------------------------------------------------------
void CGameMain::Update()
{

	m_pDI->GetInput();			// ���͏��̎擾
	m_pFont->Refresh();         // �t�H���g���̃��t���b�V��
	MyImgui::ImguiNewFrame();   // MyImgui�`��O����    // -- 2020.11.15

	if (m_pDI->CheckKey(KD_TRG, DIK_F4))  ChangeScreenMode();   // �t���X�N���[���̐؂�ւ�       // -- 2018.12.14

	switch (m_dwGameStatus)
	{

	case GAMEMAIN:			// �Q�[���又��
		GameMain();
		break;

	case GAMEEND:			// �Q�[���I��
		PostQuitMessage(0);
		break;

	}

	MyImgui::ImguiRender();      // MyImgui���`�揈��    // -- 2020.11.15

	//��ʍX�V�i�o�b�N�o�b�t�@���t�����g�o�b�t�@�Ɂj
	//m_pD3D->m_pSwapChain->Present(1, 0);                   // 60fps Vsync
	m_pD3D->m_pSwapChain->Present(0, 0);                   // Vsync�Ȃ�

	SceneManager::Update();
	ObjectManager::Update();
}

//------------------------------------------------------------------------
//
//	�Q�[���̃��C������	
//
//  �����@�Ȃ�
//
//	�߂�l �Ȃ�
//
//------------------------------------------------------------------------
void CGameMain::GameMain()
{

	//��ʃN���A�i���ۂ͒P�F�ŉ�ʂ�h��Ԃ������j
	float ClearColor[4] = { 0,0,0,1 };// �N���A�F�쐬�@RGBA�̏�
	m_pD3D->ClearRenderTarget(ClearColor); // ��ʃN���A

	// Map�̍X�V
	m_pMapProc->Update();

	// �o�b�̍X�V
	m_pPcProc->UpdateAll();

	// ����̍X�V
	m_pWeaponProc->UpdateAll();

	// �R�c���ʂ̍X�V
	m_pEffectProc->UpdateAll();

	// �O�i�E�w�i�̍X�V
	m_pBackForeProc->Update();

	// �J�����̍X�V
	m_pCameraProc->UpdateAll();

}

void CGameMain::Draw()
{
	ObjectManager::Draw();
	SceneManager::Draw();
}

//------------------------------------------------------------------------
//
//	�A�v���P�[�V�����̏I������	
//
//  �����@�Ȃ�
//
//	�߂�l �Ȃ�
//
//------------------------------------------------------------------------
void CGameMain::Quit()
{
	;
}

//------------------------------------------------------------------------    // -- 2018.12.14
//
//	�E�B���h�E���[�h�ƃt���X�N���[�����[�h��؂�ւ��鏈��	
//
//  �����@���[�h  0:�E�C���h�E���[�h�@1:�t���X�N���[���@-1:���[�h�؂�ւ��i�ȗ��l�j
//
//	�߂�l �Ȃ�
//
//------------------------------------------------------------------------
HRESULT CGameMain::ChangeScreenMode(int nMode)
{
	HRESULT Ret = S_OK;
	BOOL bFullScreen;  // �t���X�N���[�����[�h���H

	//	���݂̃X�N���[�����[�h�𓾂�
	m_pD3D->m_pSwapChain->GetFullscreenState(&bFullScreen, nullptr);

	switch (nMode)
	{
	case 0:    // �E�C���h�E���[�h�ɂ���
		if( bFullScreen ) Ret = m_pD3D->m_pSwapChain->SetFullscreenState(false, nullptr);
		break;
	case 1:    // �t���X�N���[�����[�h�ɂ���
		if( !bFullScreen ) Ret = m_pD3D->m_pSwapChain->SetFullscreenState(true, nullptr);
		break;
	default:   // ���݂̃��[�h��؂�ւ���
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

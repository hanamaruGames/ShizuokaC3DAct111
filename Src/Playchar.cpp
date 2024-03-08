//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�P�@�@�@�@�@�@                 ver 3.2        2023.1.31
//
//		�v���C�L�����N�^�[�̐���
//																Playchar.cpp
//=============================================================================
#include  "Playchar.h"
#include  "Camera.h"
#include  "BackFore.h"
#include  "Weapon.h"
#include  "Map.h"
#include  "Effect.h"

//============================================================================
//
// �o�b�v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CPcProc::CPcProc()
{
	BASEHOLDITEM hi;

	// Fbx�X�L�����b�V���̐ݒ�                                          // -- 2022.12.20
	// �o�b�Q�@�e�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|
	//m_pMeshArray.push_back( new CFbxMesh( GameDevice()->m_pFbxMeshCtrl, _T("Data/Char/PC2/pc2g.mesh")));    // �o�b�Q�@�e
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC2/pc2g_stand.anmx"));  // 0:eAnimNum_Idle
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC2/pc2g_walk.anmx"));   // 1:eAnimNum_Walk
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC2/pc2g_walk.anmx"));   // 2:eAnimNum_Run
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC2/pc2g_walk.anmx"));   // 3:eAnimNum_Attack
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC2/pc2g_die.anmx"));    // 4:eAnimNum_Die
	//m_pMeshArray.back()->m_fHeightMax = 0.01f;
	//m_pMeshArray.back()->m_iMaxDevide = 64;
	//m_HoldItemArray.push_back(hi);
	//m_HoldItemArray.back().m_nHoldObjNo = 4;	// ��Ɏ�����̃I�u�W�F�ԍ�(�����ȏe)
	//m_HoldItemArray.back().m_nPosMesh = 3;	// �e�̍����ʒu�̃��b�V���ԍ�
	//m_HoldItemArray.back().m_nPosBone = 13;	// �e�̍����ʒu�̃{�[���ԍ�
	//m_HoldItemArray.back().m_nOffsetPos = VECTOR3(0.2f, 0.0f, -0.03f);  // ��Ɏ�����̈ʒu�I�t�Z�b�g
	//m_HoldItemArray.back().m_nOffsetRot = VECTOR3(-90.0f, 0.0f, 0.0f);  // ��Ɏ�����̊p�x�I�t�Z�b�g

	// �o�b�Q�@���|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|
	//m_pMeshArray.push_back( new CFbxMesh( GameDevice()->m_pFbxMeshCtrl, _T("Data/Char/PC2/pc2s.mesh")));    // �o�b�Q�@��
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC2/pc2s_stand.anmx"));  // 0:eAnimNum_Idle
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC2/pc2s_walk.anmx"));   // 1:eAnimNum_Walk
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC2/pc2s_walk.anmx"));   // 2:eAnimNum_Run
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC2/pc2s_attack.anmx")); // 3:eAnimNum_Attack
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC2/pc2s_die.anmx"));    // 4:eAnimNum_Die
	//m_pMeshArray.back()->m_fHeightMax = 0.01f;
	//m_pMeshArray.back()->m_iMaxDevide = 64;
	//m_HoldItemArray.push_back(hi);
	//m_HoldItemArray.back().m_nHoldObjNo = 1;	// ��Ɏ�����̃I�u�W�F�ԍ�(�����Ȍ�)
	//m_HoldItemArray.back().m_nPosMesh = 3;		// ���̍����ʒu�̃��b�V���ԍ�
	//m_HoldItemArray.back().m_nPosBone = 13;	// ���̍����ʒu�̃{�[���ԍ�
	//m_HoldItemArray.back().m_nOffsetPos = VECTOR3(0.0f, 0.0f, 0.0f);  // ��Ɏ�����̈ʒu�I�t�Z�b�g
	//m_HoldItemArray.back().m_nOffsetRot = VECTOR3(0.0f, 0.0f, -90.0f);  // ��Ɏ�����̊p�x�I�t�Z�b�g

	// �o�b�S�@�e�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|
	//m_pMeshArray.push_back( new CFbxMesh(GameDevice()->m_pFbxMeshCtrl, _T("Data/Char/PC4/pc4g.mesh")));    // �o�b�S�@�e
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC4/pc4g_stand.anmx"));  // 0:eAnimNum_Idle
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC4/pc4g_walk.anmx"));   // 1:eAnimNum_Walk
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC4/pc4g_walk.anmx"));   // 2:eAnimNum_Run
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC4/pc4g_walk.anmx"));   // 3:eAnimNum_Attack
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC4/pc4g_die.anmx"));    // 4:eAnimNum_Die
	//m_pMeshArray.back()->m_fHeightMax = 0.01f;
	//m_pMeshArray.back()->m_iMaxDevide = 64;
	//m_HoldItemArray.push_back(hi);
	//m_HoldItemArray.back().m_nHoldObjNo = 4;	// ��Ɏ�����̃I�u�W�F�ԍ�(�����ȏe)
	//m_HoldItemArray.back().m_nPosMesh = 7;		// �e�̍����ʒu�̃��b�V���ԍ�
	//m_HoldItemArray.back().m_nPosBone = 19;	// �e�̍����ʒu�̃{�[���ԍ�
	//m_HoldItemArray.back().m_nOffsetPos = VECTOR3(0.0f, 0.0f, 0.0f);  // ��Ɏ�����̈ʒu�I�t�Z�b�g
	//m_HoldItemArray.back().m_nOffsetRot = VECTOR3(0.0f, 180.0f, 0.0f);  // ��Ɏ�����̊p�x�I�t�Z�b�g

	// �o�b�S�@���|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|
	//m_pMeshArray.push_back( new CFbxMesh(GameDevice()->m_pFbxMeshCtrl, _T("Data/Char/PC4/pc4s.mesh")));    // �o�b�S�@��
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC4/pc4s_stand.anmx"));  // 0:eAnimNum_Idle
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC4/pc4s_walk.anmx"));   // 1:eAnimNum_Walk
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC4/pc4s_walk.anmx"));   // 2:eAnimNum_Run
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC4/pc4s_attack.anmx")); // 3:eAnimNum_Attack
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC4/pc4s_die.anmx"));    // 4:eAnimNum_Die
	//m_pMeshArray.back()->m_fHeightMax = 0.01f;
	//m_pMeshArray.back()->m_iMaxDevide = 64;
	//m_HoldItemArray.push_back(hi);
	//m_HoldItemArray.back().m_nHoldObjNo = 1;	// ��Ɏ�����̃I�u�W�F�ԍ�(�����Ȍ�)
	//m_HoldItemArray.back().m_nPosMesh = 7;		// ���̍����ʒu�̃��b�V���ԍ�
	//m_HoldItemArray.back().m_nPosBone = 19;		// ���̍����ʒu�̃{�[���ԍ�
	//m_HoldItemArray.back().m_nOffsetPos = VECTOR3(0.0f, 0.0f, 0.0f);  // ��Ɏ�����̈ʒu�I�t�Z�b�g
	//m_HoldItemArray.back().m_nOffsetRot = VECTOR3(0.0f, 180.0f, -90.0f);  // ��Ɏ�����̊p�x�I�t�Z�b�g

	// �L�����N�^�[�@�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|
	m_pMeshArray.push_back(new CFbxMesh(GameDevice()->m_pFbxMeshCtrl, _T("Data/Char/Character/character.mesh")));    // �L�����N�^�[
	m_pMeshArray.back()->LoadAnimation(_T("Data/Char/Character/character_stand.anmx"));   // 0:eAnimNum_Idle
	m_pMeshArray.back()->LoadAnimation(_T("Data/Char/Character/character_forward_start_RAXZ.anmx"), eRootAnimXZ);  // 1:eAnimNum_Walk
	m_pMeshArray.back()->LoadAnimation(_T("Data/Char/Character/character_forward_middle_RAXZ.anmx"), eRootAnimXZ); // 2:eAnimNum_Run
	m_pMeshArray.back()->LoadAnimation(_T("Data/Char/Character/character_attack.anmx"));  // 3:eAnimNum_Attack
	m_pMeshArray.back()->LoadAnimation(_T("Data/Char/Character/character_die.anmx"));     // 4:eAnimNum_Die
	m_pMeshArray.back()->m_fHeightMax = 0.01f;
	m_pMeshArray.back()->m_iMaxDevide = 16;
	m_HoldItemArray.push_back(hi);
	m_HoldItemArray.back().m_nHoldObjNo = 1;	// ��Ɏ�����̃I�u�W�F�ԍ�(�����Ȍ�)
	m_HoldItemArray.back().m_nPosMesh = 0;		// ���̍����ʒu�̃��b�V���ԍ�
	m_HoldItemArray.back().m_nPosBone = 13;	// ���̍����ʒu�̃{�[���ԍ�
	m_HoldItemArray.back().m_nOffsetPos = VECTOR3(0.2f, 0.0f, 0.0f);  // ��Ɏ�����̈ʒu�I�t�Z�b�g
	m_HoldItemArray.back().m_nOffsetRot = VECTOR3(0.0f, 0.0f, -90.0f);  // ��Ɏ�����̊p�x�I�t�Z�b�g

	// Dreyar�@�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|                        // -- 2022.12.20
	//m_pMeshArray.push_back(new CFbxMesh(GameDevice()->m_pFbxMeshCtrl, _T("Data/Char/Dreyar/Dreyar.mesh")));    // Dreyar
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/Dreyar/Dreyar_Idle.anmx"));    // 0:eAnimNum_Idle
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/Dreyar/Dreyar_Walking.anmx")); // 1:eAnimNum_Walk
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/Dreyar/Dreyar_Running.anmx")); // 2:eAnimNum_Run
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/Dreyar/Dreyar_Sword.anmx"));   // 3:eAnimNum_Attack
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/Dreyar/Dreyar_Dying.anmx"));   // 4:eAnimNum_Die
	//m_pMeshArray.back()->m_fHeightMax = 0.01f;
	//m_pMeshArray.back()->m_iMaxDevide = 16;
	//m_HoldItemArray.push_back(hi);
	//m_HoldItemArray.back().m_nHoldObjNo = 3;	// ��Ɏ�����̃I�u�W�F�ԍ�(�\�[�h)
	//m_HoldItemArray.back().m_nPosMesh = 0;		// ���̍����ʒu�̃��b�V���ԍ�
	//m_HoldItemArray.back().m_nPosBone = 45;		// ���̍����ʒu�̃{�[���ԍ�
	//m_HoldItemArray.back().m_nOffsetPos = VECTOR3(0.0f, 0.02f, -0.04f);  // ��Ɏ�����̈ʒu�I�t�Z�b�g
	//m_HoldItemArray.back().m_nOffsetRot = VECTOR3(0.0f, 0.0f, -90.0f);  // ��Ɏ�����̊p�x�I�t�Z�b�g

	// Maria�@�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|                            // -- 2022.12.20
	//m_pMeshArray.push_back(new CFbxMesh(GameDevice()->m_pFbxMeshCtrl, _T("Data/Char/Maria/Maria.mesh")));    // Maria
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/Maria/Maria_Idle.anmx"));    // 0:eAnimNum_Idle
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/Maria/Maria_Walking.anmx")); // 1:eAnimNum_Walk
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/Maria/Maria_Running.anmx")); // 2:eAnimNum_Run
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/Maria/Maria_Slash.anmx"));   // 3:eAnimNum_Attack
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/Maria/Maria_Dying.anmx"));   // 4:eAnimNum_Die
	//m_pMeshArray.back()->m_fHeightMax = 0.01f;
	//m_pMeshArray.back()->m_iMaxDevide = 16;
	//m_HoldItemArray.push_back(hi);
	//m_HoldItemArray.back().m_nHoldObjNo = 3;	// ��Ɏ�����̃I�u�W�F�ԍ�(�\�[�h)
	//m_HoldItemArray.back().m_nPosMesh = 0;		// ���̍����ʒu�̃��b�V���ԍ�
	//m_HoldItemArray.back().m_nPosBone = 43;		// ���̍����ʒu�̃{�[���ԍ�
	//m_HoldItemArray.back().m_nOffsetPos = VECTOR3(0.0f, 0.01f, -0.02f);  // ��Ɏ�����̈ʒu�I�t�Z�b�g
	//m_HoldItemArray.back().m_nOffsetRot = VECTOR3(0.0f, 0.0f, -90.0f);  // ��Ɏ�����̊p�x�I�t�Z�b�g

	// -------------------------------------------------------------------------
	m_pObjArray.push_back(new CPcObj(this));	// m_pObjArray�ɃI�u�W�F�N�g��o�^����

	// -------------------------------------------------------------------------  // -- 2022.2.16
	// �o�b�v���V�[�W���̏���������
	m_dwProcID = PC_ID;       // PC��ID
	m_nNum = PC_ALLMAX;       // �ő�o����

}

// ---------------------------------------------------------------------------
//
// �o�b�v���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CPcProc::~CPcProc()
{
	;
}


//============================================================================
//
// �o�b�I�u�W�F�N�g�̃R���X�g���N�^
//
//  ����
//  CBaseProc* pProc		�F �e�v���V�[�W���ւ̃|�C���^
//
// ---------------------------------------------------------------------------
CPcObj::CPcObj(CBaseProc* pProc) : CBaseObj(pProc)
{
	m_fLocalRotY = 0.0f;                   // -- 2018.8.4
	m_bSide = true;                        // -- 2018.8.4

	// �o�E���f�B���O�{�b�N�X�̐ݒ�
	m_pBBox = new CBBox(GameDevice()->m_pShader, VECTOR3(-0.25f, -0.05f, -0.25f), VECTOR3(0.25f, 2.0f, 0.25f));
	m_pBBox->m_mWorld = m_mWorld;                            // -- 2021.1.11

	m_nMaxHp = PC_MAXHP;
	m_nAtc = PC_ATC;

	// -----------------------------------------------------------------------  // -- 2022.2.16
	// �o�b�I�u�W�F�N�g�̏���������
	m_bActive = true;
	ResetStatus();

	m_AnimStatus.playAnim = true;
	m_AnimStatus.SetNum(eAnimNum_Idle);
	m_AnimStatus.animFrame = 0;

	// �O�i�ړ����x�{��(�����l�͂P�{)
	m_nMoveFwdPower = 1;

	m_nHp = m_nMaxHp;

	m_seLaser = new CXAudioSource(_T("Data/Sound/Lazer.wav"), 10);

}
// ---------------------------------------------------------------------------
//
// �o�b�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CPcObj::~CPcObj() 
{
	SAFE_DELETE(m_seLaser);
}

// ---------------------------------------------------------------------------
//
// �o�b�I�u�W�F�N�g�̃��[�J�����}�g���b�N�X�𓾂�֐�
//
//  m_mWorld�̈ʒu����m_fLocalRotY�̊p�x��������
//  ���[�J�����}�g���b�N�X��Ԃ�
//
// ---------------------------------------------------------------------------
MATRIX4X4 CPcObj::GetLocalMatrix()
{
	MATRIX4X4 mPos = GetPositionMatrix(m_mWorld);
	MATRIX4X4 mRotY;

	mRotY = XMMatrixRotationY(XMConvertToRadians(m_fLocalRotY));
	mRotY = mRotY * mPos;
	return mRotY;
}


//-----------------------------------------------------------------------------
// �o�b�I�u�W�F�N�g�̍X�V
//
//�@�L�[�{�[�h�ło�b�𓮂���
//�@�o�b�̃A�j���[�V�����A�W�����v�A���R����
//�@���[���h���W�ԊҁA�}�b�v�Ƃ̐ڐG����
//�@�o�b�̍U���������s��
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CPcObj::Update()
{

	// ��O�̈ʒu��ۑ�
	m_mWorldOld = m_mWorld;

	// �e��Ԃɉ���������
	switch (m_dwStatus) {
	case  FLASH:  // �o�b���_���[�W���畜�A�����Ƃ��̏���
	case  NORMAL: // �o�b���ʏ��Ԃ̂Ƃ��̏���
		UpdateNormal();  // �o�b�I�u�W�F�N�g�̍X�V �ʏ��ԁiNORMAL�j
		break;

	case  DAMAGE: // �o�b���_���[�W��Ԃ̂Ƃ��̏���
		UpdateDamage();  // �o�b�I�u�W�F�N�g�̍X�V �_���[�W��ԁiDAMAGE�j
		break;

	case  DEAD:	// �o�b�����S��Ԃ̂Ƃ��̏���
		UpdateDead();  // �o�b�I�u�W�F�N�g�̍X�V ���S��ԁiDEAD�j
		break;

	}

	// �}�b�v�R���W�����Ǝ��R����
	m_fJumpY += GAMEGRAVITY * m_fJumpTime;	// ���R����
	m_fJumpTime += 1.0f;
	if (ObjectManager::FindGameObject<CMapProc>()->isCollisionMoveGravity(&m_mWorld, m_mWorldOld) != 3)  // �}�b�v�R���W����
	{
		m_fJumpY = 0.0f;  // ���R�����̒�~
		m_fJumpTime = 0.0f;
	}

	// �o�E���f�B���O�{�b�N�X
	m_pBBox->m_mWorld = m_mWorld;
	//m_pBBox->m_mWorld = GetMesh()->GetFrameMatrices(m_AnimStatus, m_mWorld, 0);  // ���[�g�{�[��
	//m_pBBox->Render( GameDevice()->m_mView, GameDevice()->m_mProj, GameDevice()->m_vLightDir, GameDevice()->m_vEyePt);


	// ��Ɏ������A�C�e���̕\��������     // -- 2021.2.4
	if (GetHoldItem().m_nHoldObjNo != 0) // ��Ɏ������A�C�e��������Ƃ�
	{
		MATRIX4X4 mHold;
		mHold = GetMesh()->GetFrameMatrices(m_AnimStatus, m_mWorld, GetHoldItem().m_nPosBone, GetHoldItem().m_nPosMesh);  // ��̈ʒu�̃{�[���}�g���b�N�X
		ObjectManager::FindGameObject<CWeaponHoldProc>()->Disp(mHold, GetHoldItem()); // �A�C�e���\��
	}

	// �o�b�̓���̖��O�\��
	VECTOR3 vPcPos = GetPositionVector(m_mWorld);
	//vPcPos.y += 2.0f;
	//GameDevice()->m_pFont->Draw3D(vPcPos, GameDevice()->m_mView, GameDevice()->m_mProj, GameDevice()->m_vEyePt, _T("�v���C�L�����N�^�["), VECTOR2(0.5f, 0.2f), RGB(0, 0, 255), 1.0f, _T("HGP�n�p�p�߯�ߑ�"));


}

void CPcObj::Draw()
{
	//�����_�����O
	GetMesh()->Render(m_AnimStatus, m_mWorld, GameDevice()->m_mView, GameDevice()->m_mProj, GameDevice()->m_vLightDir, GameDevice()->m_vEyePt);
	//GetMesh()->RenderDisplace(m_AnimStatus, m_mWorld, GameDevice()->m_mView, GameDevice()->m_mProj, GameDevice()->m_vLightDir, GameDevice()->m_vEyePt);
}

//-----------------------------------------------------------------------------   // -- 2019.3.5
// �o�b�I�u�W�F�N�g�̍X�V �ʏ��ԁiNORMAL�j
//
//�@�L�[�{�[�h�ło�b�𓮂���
//�@�o�b�̃A�j���[�V�����A�W�����v�A���R����
//�@���[���h���W�ԊҁA�}�b�v�Ƃ̐ڐG����
//�@�o�b�̍U���������s��
//
//
//   �����@�Ȃ�
//
//-----------------------------------------------------------------------------
void	CPcObj::UpdateNormal()
{

	if (m_dwStatus == FLASH) // �o�b���_���[�W���畜�A�����Ƃ��̏���
	{
		m_nCnt1--;
		if (m_nCnt1 <= 0) m_dwStatus = NORMAL;
		//GameDevice()->m_pRenderBufProc->SetDrawFont(300, 10, _T("** ���G��� **"), 16, RGB(255, 0, 0));
	}
	UpdateNormalMove();      // �o�b�I�u�W�F�N�g�̈ړ�����
	UpdateNormalAttack();    // �o�b�I�u�W�F�N�g�̍U������

}
//-----------------------------------------------------------------------------   // -- 2019.3.5
// �o�b�I�u�W�F�N�g�̈ړ�����
//
//�@�L�[�{�[�h�^�}�E�X�ło�b�𓮂���
//�@�o�b�̃A�j���[�V�����A�W�����v�A���R����
//�@���[���h���W�ԊҁA�}�b�v�Ƃ̐ڐG����
//
//
//   �����@�Ȃ�
//
//-----------------------------------------------------------------------------
void	CPcObj::UpdateNormalMove()
{
	CDirectInput* pDI = GameDevice()->m_pDI;
	const float PC_JUMP_SPEED = PC_JUMP_SPEED_X100 / 100.0f;  // �W�����v�X�s�[�h

	MATRIX4X4 mYaw;  // �o�b�x����]�}�g���b�N�X
	MATRIX4X4 mPos;  // �o�b�ړ��}�g���b�N�X
	bool	  bKeyPush = false;// �L�[�����������ǂ����̃`�F�b�N

	// �L�[�{�[�h�A�}�E�X�A�W���C�X�e�B�b�N����

	// �W�����v   ------------------------------------------------
	if ((pDI->CheckKey(KD_TRG, DIK_J) || pDI->CheckJoy(KD_TRG, DIJ_Z)) && m_fJumpY == 0.0f) {
		bKeyPush = true;
		m_fJumpY = PC_JUMP_SPEED;
		m_fJumpTime = 1.0f;
	}
	// ���R�����̏����l
	mPos = XMMatrixTranslation(0.0f, m_fJumpY, 0.0f);

	// �T�C�h���[�h�̐؂�ւ�  -------------------------------------
	// (���E�ړ��̎��A������ς��邩�ǂ���)
	if (pDI->CheckKey(KD_TRG, DIK_Y))
	{
		if (m_bSide)
		{
			m_bSide = false;   // ���E�ړ��̎��A������ς���
		}
		else {
			m_bSide = true;    // ���E�ړ��̎��A������ς��Ȃ�
		}
	}

	// ���[�J�����i�x���j�̉�]����  --------------------------------
	if (pDI->CheckKey(KD_DAT, DIK_RIGHT) || pDI->CheckMouse(KD_DAT, DIM_RIGHT) || pDI->CheckJoy(KD_DAT, DIJ_R)) //	���L�[
	{
		m_fLocalRotY += PC_ROT_LOWSPEED;
		if (m_fLocalRotY >= 360.0f) m_fLocalRotY -= 360.0f;
	}

	if (pDI->CheckKey(KD_DAT, DIK_LEFT) || pDI->CheckMouse(KD_DAT, DIM_LEFT) || pDI->CheckJoy(KD_DAT, DIJ_L)) //	���L�[
	{
		m_fLocalRotY -= PC_ROT_LOWSPEED;
		if (m_fLocalRotY < 0.0f) m_fLocalRotY += 360.0f;
	}

	// �o�b�̈ړ�����  ---------------------------------------------
	// �O�i����
	if (pDI->CheckKey(KD_DAT, DIK_W) || pDI->CheckKey(KD_DAT, DIK_UP) || pDI->CheckJoy(KD_DAT, DIJ_UP)) //	���L�[
	{
		bKeyPush = true;
		mPos = UpdateNormalMoveKeystate(DIK_W);
	}
	// ��ޏ���
	if (pDI->CheckKey(KD_DAT, DIK_S) || pDI->CheckKey(KD_DAT, DIK_DOWN) || pDI->CheckJoy(KD_DAT, DIJ_DOWN)) //���L�[
	{
		bKeyPush = true;
		mPos = UpdateNormalMoveKeystate(DIK_S);
	}
	// �E�ړ�����
	if (pDI->CheckKey(KD_DAT, DIK_D) || pDI->CheckJoy(KD_DAT, DIJ_RIGHT))//���L�[
	{
		bKeyPush = true;
		mPos = UpdateNormalMoveKeystate(DIK_D);
	}
	// ���ړ�����
	if (pDI->CheckKey(KD_DAT, DIK_A) || pDI->CheckJoy(KD_DAT, DIJ_LEFT))//���L�[
	{
		bKeyPush = true;
		mPos = UpdateNormalMoveKeystate(DIK_A);
	}

	// �L�[�������Ă��Ȃ��Ƃ��ŁA����������̂Ƃ��A�C�h���ɖ߂�    // -- 2023.1.31
	if (!bKeyPush && (m_AnimStatus.animNum == eAnimNum_Walk || m_AnimStatus.animNum == eAnimNum_Run))
	{
		m_AnimStatus.SetNum(eAnimNum_Idle);
	}

	// ���[�J��������Ƃ��āA�o�b���ړ������郏�[���h�}�g���b�N�X��ݒ�
	mYaw = XMMatrixRotationY(XMConvertToRadians(m_vRotUp.y));
	m_mWorld = mPos * mYaw * GetLocalMatrix();

}

//-----------------------------------------------------------------------------   // -- 2021.1.10
// �o�b�I�u�W�F�N�g�̈ړ������@�L�[���얈�̊e��ړ�����
//
//   �����@DWORD Key �L�[��ʁ@DirectInput�̃L�[�R�[�h
//
//   �߂�l  �ړ��}�g���b�N�X
//-----------------------------------------------------------------------------
MATRIX4X4 CPcObj::UpdateNormalMoveKeystate(DWORD DIKey)
{
	const float PC_MOVE_BASESPEED = PC_MOVE_BASESPEED_X100 / 100.0f;  // �ړ���{�X�s�[�h

	MATRIX4X4 mPos = XMMatrixTranslation(0.0f, m_fJumpY, 0.0f);

	if (m_AnimStatus.animNum == eAnimNum_Idle) m_AnimStatus.SetNum(eAnimNum_Walk);  // �A�C�h�����̂Ƃ��́A���s�A�j���[�V�����ɂ���
	if (m_AnimStatus.isEnd(eAnimNum_Walk))  m_AnimStatus.SetNum(eAnimNum_Run);  // ���s�A�j���[�V�������I������Ƃ��A����̃A�j���[�V�����ɂ���

	if (m_bSide && DIKey != DIK_W)   // �T�C�h���[�h�őO�i�ȊO�̂Ƃ�
	{
		switch (DIKey)
		{
		case DIK_S:    // ���
			// ������ς����Ɍ��
			mPos = XMMatrixTranslation(0.0f, m_fJumpY, -PC_MOVE_BASESPEED);
			break;
		case DIK_D:    // �E
			// ������ς����ɉE�ړ�
			mPos = XMMatrixTranslation(PC_MOVE_BASESPEED, m_fJumpY, 0.0f);
			break;
		case DIK_A:    // ��
			// ������ς����ɍ��ړ�
			mPos = XMMatrixTranslation(-PC_MOVE_BASESPEED, m_fJumpY, 0.0f);
			break;
		}
	}
	else {
		// �i�s�����ɉ�]���Ă���O�i

		// ���[�g�{�[���A�j���[�V�������s�����ǂ������[�g�A�j���[�V�����^�C�v���m�F����
		if (GetMesh()->GetRootAnimType(m_AnimStatus.animNum) == eRootAnimNone)
		{
			// ���[�g�{�[���A�j���[�V�������s�킸�Œ�̑O�i�ړ��l
			mPos = XMMatrixTranslation(0.0f, m_fJumpY, PC_MOVE_BASESPEED * m_nMoveFwdPower);  // ��{���x�ɑO�i���x�{�����|���� // -- 2022.12.20
		}
		else {
			// ���[�g�{�[���A�j���[�V�����ł̑O�i�ړ��l
			MATRIX4X4 mWork = GetMesh()->GetRootAnimUpMatrices(m_AnimStatus);      // -- 2022.12.20
			mWork._43 *= m_nMoveFwdPower;    // �y�����ɑO�i���x�{�����|����       // -- 2022.12.20
			mPos = XMMatrixTranslation(0.0f, m_fJumpY, 0.0f) * mWork;
		}

		// �i�s�����ɉ�]���鏈��
		// �E��]�p�x��m_vRotUp.y�ɂ���B-180�`180�x
		// �E�P��̉�]���x��PC_ROTSPEED
		if (m_vRotUp.y > 180.0f)  m_vRotUp.y -= 360.0f;
		if (m_vRotUp.y < -180.0f) m_vRotUp.y += 360.0f;

		float fAngle = 0.0f;  // �ڕW��]�p�x
		switch (DIKey)
		{
		case DIK_W:    // �O�i
			fAngle = 0.0f;
			break;
		case DIK_S:    // ���
			if (m_vRotUp.y >= 0)  // �ŏ���]�ɂȂ�悤�ɕ��������킹��
			{
				fAngle = 180.0f;
			}
			else {
				fAngle = -180.0f;
			}
			break;
		case DIK_D:    // �E
			fAngle = 90.0f;
			if (m_vRotUp.y == -180.0f) m_vRotUp.y = 180.0f;  // �ŏ���]�ɂȂ�悤�ɕ��������킹��
			break;
		case DIK_A:    // ��
			fAngle = -90.0f;
			if (m_vRotUp.y == 180.0f) m_vRotUp.y = -180.0f;  // �ŏ���]�ɂȂ�悤�ɕ��������킹��
			break;
		}

		if (m_vRotUp.y > fAngle)  // ����]
		{
			m_vRotUp.y -= PC_ROT_SPEED;
			if (m_vRotUp.y < fAngle) m_vRotUp.y = fAngle;
		}
		if (m_vRotUp.y < fAngle)  // �E��]
		{
			m_vRotUp.y += PC_ROT_SPEED;
			if (m_vRotUp.y > fAngle) m_vRotUp.y = fAngle;
		}

	}
	return mPos;
}

//-----------------------------------------------------------------------------   // -- 2019.3.5
// �o�b�I�u�W�F�N�g�̍U������
//
//�@�L�[�{�[�h�^�}�E�X�ło�b�̍U���������s��
//
//
//   �����@�Ȃ�
//
//-----------------------------------------------------------------------------
void	CPcObj::UpdateNormalAttack()
{
	CDirectInput* pDI = GameDevice()->m_pDI;

	// ------------------------------------------------------------- 
	// ���[�U�[�̔���
	if (pDI->CheckKey(KD_DAT, DIK_X) || pDI->CheckJoy(KD_DAT, DIJ_A) || pDI->CheckMouse(KD_DAT, DIM_LBUTTON)) // X�L�[
	{
		MATRIX4X4 mGun, mHold;
		VECTOR3 vOffset;

		// ��Ɏ��A�C�e������e�̏��𓾂Ĕ��˂���
		mHold = GetMesh()->GetFrameMatrices(m_AnimStatus, m_mWorld, GetHoldItem().m_nPosBone, GetHoldItem().m_nPosMesh);  // �e�̍����ʒu�̃{�[���}�g���b�N�X
		CWeaponHoldProc* pHold = ObjectManager::FindGameObject<CWeaponHoldProc>();
		pHold->GetInfo(mHold, GetHoldItem(), mGun, vOffset); // �{�[���}�g���b�N�X���w�肵�Ď�Ɏ��A�C�e���̏��𓾂�
		if (pHold->GetKind(GetHoldItem()) != 2)   // �e�������Ă��Ȃ��Ƃ�
		{
			vOffset.z = 0.8f;   // �Ƃ肠�����O����0.8
		}
		CWeaponLaserProc* pLaser = ObjectManager::FindGameObject<CWeaponLaserProc>();
		pLaser->Start(mGun, vOffset, m_mWorld, PC); // ���[�U�[����
		m_seLaser->Play(); // ���[�U�[���ˌ��ʉ�

	}

}
//-----------------------------------------------------------------------------   // -- 2019.3.5
// �o�b�I�u�W�F�N�g�̍X�V �_���[�W��ԁiDAMAGE�j
//
//�@�_���[�W���󂯂��Ƃ��̏���
//
//
//   �����@�Ȃ�
//
//-----------------------------------------------------------------------------
void	CPcObj::UpdateDamage()
{
	MATRIX4X4 mTemp;

	ObjectManager::FindGameObject<CBackForeProc>()->GetSprite()->DrawRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, RGB(255, 255, 255), 1.0f); // ��ʂ���u�����t���b�V��

	mTemp = XMMatrixTranslation(0, 0, -0.25f);	// �o�b�N����
	m_mWorld = mTemp * m_mWorld;

	m_nHp -= m_pHitObj->GetAtc();	// �U�����󂯂��_���[�W
	if (m_nHp <= 0)		// HP���O�Ȃ̂Ŏ��S��
	{
		m_nHp = 0;
		m_dwStatus = DEAD;		// HP���O�Ȃ̂Ŏ��S��
		m_AnimStatus.SetNum(eAnimNum_Die);	// ���S���[�V�����ɂ���
		m_nCnt1 = PC_DEADTIME;		// ���S���Ԃ̐ݒ�
	}
	else {
		m_nCnt1 = PC_FLASHTIME;   // ���G��Ԃ̎���
		m_dwStatus = FLASH;     // �_���[�W����̕��A�������s��
	}
}
//-----------------------------------------------------------------------------   // -- 2019.3.5
// �o�b�I�u�W�F�N�g�̍X�V ���S��ԁiDEAD�j
//
//�@���S��Ԃ̂Ƃ��̏���
//
//
//   �����@�Ȃ�
//
//-----------------------------------------------------------------------------
void	CPcObj::UpdateDead()
{
	ObjectManager::FindGameObject<CBackForeProc>()->GetSprite()->DrawRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, RGB(255, 0, 0), 0.5f); // ��ʂ�Ԃ�����

	if (m_AnimStatus.isEnd(eAnimNum_Die))  // ���S���[�V�������I������Ƃ�
	{
		m_AnimStatus.playAnim = false;	// ��U�A�A�j���[�V�������~�߂�
		m_AnimStatus.animFrame = m_AnimStatus.endFrame - 1; // �t���[���G���h�̈��O�ɂ���
	}
	if (--m_nCnt1 <= 0) // ���S���Ԃ��I������Ƃ�
	{
		m_pProc->AddNum(-1);	// �o�b������炷
		if (m_pProc->GetNum() <= 0)
		{
			m_AnimStatus.playAnim = true;	// �A�j���[�V�����𕜊�������
			GameDevice()->m_dwGameStatus = GAMEOVER;	// �Q�[���I�[�o�[��
		}
		else {
			// �Q�[���I�[�o�[�łȂ��Ƃ�
			m_AnimStatus.SetNum(eAnimNum_Idle);	// �A�j���[�V�������A�C�h����Ԃɖ߂�
			m_AnimStatus.playAnim = true;	// �A�j���[�V�����𕜊�������
			m_nHp = m_nMaxHp;
			m_dwStatus = FLASH;     // ���S����̕��A����
			m_nCnt1 = PC_DEADFLASHTIME;   // ���G��Ԃ̎���
		}
	}
}

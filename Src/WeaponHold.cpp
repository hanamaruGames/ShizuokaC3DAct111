//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�P�@�@�@�@�@�@                 ver 3.2        2023.1.31
//
//		����E��Ɏ��A�C�e���̏���
//															WeaponHold.cpp
//=============================================================================
#include  "WeaponHold.h"

#include  "Playchar.h"
#include  "Effect.h"

//============================================================================
//
// ����E��Ɏ��A�C�e���v���V�[�W���̃R���X�g���N�^
//
// �E���ڍU�����镐��ł͂Ȃ��A�����\��������A�ʒu����Ԃ����肷��
//
//   ���b�V���̓v���V�[�W���ł͂Ȃ��A�I�u�W�F�N�g�œǂݍ���
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CWeaponHoldProc::CWeaponHoldProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (int i = 0; i < WEAPON_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponHoldObj(this));	// m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
		((CWeaponHoldObj*)m_pObjArray.back())->Init();   // �I�u�W�F�N�g�̏�����
	}
}
// ---------------------------------------------------------------------------
//
// ����E��Ɏ��A�C�e���v���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponHoldProc::~CWeaponHoldProc()
{
	;
}

// ---------------------------------------------------------------------------
//
// ����E��Ɏ��A�C�e���v���V�[�W���̏��𓾂�
//
//     MATRIX4X4  mHold       �F���̈ʒu
//     BASEHOLDITEM HoldItem  :��Ɏ�����̏��
//     MATRIX4X4& mMat        :��Ɏ�����̃}�g���b�N�X(Out)
//     VECTOR3& vMin          :�o�E���f�B���O�{�b�N�X��Min(Out)
//     VECTOR3& vMax          :�o�E���f�B���O�{�b�N�X��Max(Out)
//
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
void  CWeaponHoldProc::GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vMin, VECTOR3& vMax)
{
	((CWeaponHoldObj*)m_pObjArray[HoldItem.m_nHoldObjNo])->GetInfo(mHold, HoldItem, mMat, vMin, vMax);	// ����E���I�u�W�F�N�g

	return;
}
// ---------------------------------------------------------------------------
//
// ����E��Ɏ��A�C�e���v���V�[�W���̏��𓾂�
//
//     MATRIX4X4  mHold       �F���̈ʒu
//     BASEHOLDITEM HoldItem  :��Ɏ�����̏��
//     MATRIX4X4& mMat        :��Ɏ�����̃}�g���b�N�X(Out)
//     VECTOR3& vOffset       :�e���܂ł̃I�t�Z�b�g(Out)
//
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
void  CWeaponHoldProc::GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vOffset)
{
	((CWeaponHoldObj*)m_pObjArray[HoldItem.m_nHoldObjNo])->GetInfo(mHold, HoldItem, mMat, vOffset);	// ����E�e�I�u�W�F�N�g

	return;
}

// ---------------------------------------------------------------------------
//
// ����E��Ɏ��A�C�e���v���V�[�W���̃o�E���f�B���O�{�b�N�X�𓾂�
//
//     MATRIX4X4  mHold       �F���̈ʒu
//     BASEHOLDITEM HoldItem  :��Ɏ�����̏��
//
//     �߂�l�@�@CBBox* �o�E���f�B���O�{�b�N�X
// ---------------------------------------------------------------------------
CBBox* CWeaponHoldProc::GetBBox(MATRIX4X4 mHold, BASEHOLDITEM HoldItem)
{
	return ((CWeaponHoldObj*)m_pObjArray[HoldItem.m_nHoldObjNo])->GetBBox(mHold, HoldItem);	// ����E���I�u�W�F�N�g
}

// ---------------------------------------------------------------------------
//
// ����E��Ɏ��A�C�e���v���V�[�W���̕\��
//
//     MATRIX4X4  mHold       �F���̈ʒu
//     BASEHOLDITEM HoldItem  :��Ɏ�����̏��
//
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
BOOL CWeaponHoldProc::Disp(MATRIX4X4 mHold, BASEHOLDITEM HoldItem)
{

	((CWeaponHoldObj*)m_pObjArray[HoldItem.m_nHoldObjNo])->Disp(mHold, HoldItem);	// ����E���I�u�W�F�N�g

	return TRUE;
}

// ---------------------------------------------------------------------------   // -- 2023.1.31
//
// ����E��Ɏ��A�C�e���v���V�[�W���̃I�u�W�F�N�g�ԍ���Ԃ�
//
//     BASEHOLDITEM HoldItem  :��Ɏ�����̏��
//
//     �߂�l�@�@int �I�u�W�F�N�g�ԍ�
// ---------------------------------------------------------------------------
int CWeaponHoldProc::GetKind(BASEHOLDITEM HoldItem)
{
	return ((CWeaponHoldObj*)m_pObjArray[HoldItem.m_nHoldObjNo])->GetKind();
}

//============================================================================
//
// ����E��Ɏ��A�C�e���I�u�W�F�N�g�̃R���X�g���N�^
//
// �E���ڍU�����镐��ł͂Ȃ��A�����\��������A�ʒu����Ԃ����肷��
//
// ---------------------------------------------------------------------------
CWeaponHoldObj::CWeaponHoldObj(CBaseProc* pProc) : CBaseObj(pProc)
{
	m_nKindNo = 0;
	m_pMesh = NULL;
	m_vOffset = VECTOR3(0.0f, 0.0f, 0.0f);   // �I�t�Z�b�g�̐ݒ�
}
//============================================================================
//
// ����E��Ɏ��A�C�e���I�u�W�F�N�g�̏�����
//
// �E���b�V���́A�v���V�[�W���ł͂Ȃ��I�u�W�F�N�g�̒��ɐݒ肷��
//
// ---------------------------------------------------------------------------
void CWeaponHoldObj::Init()
{

	switch (m_dwObjNo)
	{
	case 0:     // ���ݒ�
		m_nKindNo = 0;
		m_pMesh = NULL; // �I�u�W�F�N�g�͖���
		m_pBBox = NULL; // BBox�̐ݒ�
		m_vOffset = VECTOR3(0.0f, 0.0f, 0.0f);   // �I�t�Z�b�g�Ȃ�
		break;

	case 1:     // �����Ȍ��̐ݒ�
		m_nKindNo = 1;  // 1:��ʁ@��
		m_pMesh = NULL; // �I�u�W�F�N�g�͖���
		m_pBBox = new CBBox(m_pGMain->m_pShader, VECTOR3(-0.15f, -0.15f, -0.15f), VECTOR3(0.15f, 1.8f, 0.15f));// BBox�̐ݒ�
		m_vOffset = VECTOR3(0.0f, 0.0f, 0.0f);   // �e���܂ł̃I�t�Z�b�g�̐ݒ�
		break;

	case 2:     // ���i���{���j���b�V���̐ݒ�
		m_nKindNo = 1;  // 1:��ʁ@��
		m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Sword.mesh"));
		m_pBBox = new CBBox(m_pGMain->m_pShader, VECTOR3(-0.15f, 0.1f, -0.15f), VECTOR3(0.15f, 1.8f, 0.15f));// BBox�̐ݒ�
		m_vOffset = VECTOR3(0.0f, 0.0f, 0.0f);   // �e���܂ł̃I�t�Z�b�g�̐ݒ�
		break;

	case 3:     // ���i�\�[�h�j���b�V���̐ݒ�
		m_nKindNo = 1;  // 1:��ʁ@��
		//m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Sword2.mesh"));
		m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Swordm.mesh"));                   // -- 2022.12.20
		m_pBBox = new CBBox(m_pGMain->m_pShader, VECTOR3(-0.15f, 0.1f, -0.15f), VECTOR3(0.15f, 1.8f, 0.15f));// BBox�̐ݒ�
		m_vOffset = VECTOR3(0.0f, 0.0f, 0.0f);   // �e���܂ł̃I�t�Z�b�g�̐ݒ�
		break;

	case 4:     // �����ȏe�̐ݒ�
		m_nKindNo = 2;  // 2:��ʁ@�e
		m_pMesh = NULL; // �I�u�W�F�N�g�͖���
		m_vOffset = VECTOR3(0.0f, 0.0f, 0.51f);   // �e���܂ł̃I�t�Z�b�g�̐ݒ�
		break;

	case 5:     // �e�i���C�t���j���b�V���̐ݒ�
		m_nKindNo = 2;  // 2:��ʁ@�e
		m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Gun.mesh"));
		m_vOffset = VECTOR3(0.0f, 0.0f, 0.51f);   // �e���܂ł̃I�t�Z�b�g�̐ݒ�
		break;

	case 6:     // �e�i�s�X�g���j���b�V���̐ݒ�
		m_nKindNo = 2;  // 2:��ʁ@�e
		m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Pistol.mesh"));
		m_vOffset = VECTOR3(0.0f, 0.07f, 0.17f);   // �e���܂ł̃I�t�Z�b�g�̐ݒ�
		break;

	case 7:     // �����ȏ��̐ݒ�
		m_nKindNo = 1;  // 1:��ʁ@��
		m_pMesh = NULL; // �I�u�W�F�N�g�͖���
		m_pBBox = new CBBox(m_pGMain->m_pShader, VECTOR3(-1.0f, -1.5f, -0.3f), VECTOR3(1.0f, 1.5f, 0.3f));// BBox�̐ݒ�
		m_vOffset = VECTOR3(0.0f, 0.0f, 0.0f);   // �e���܂ł̃I�t�Z�b�g�̐ݒ�
		break;

	default:
		m_nKindNo = 0;
		m_pMesh = NULL; // �I�u�W�F�N�g�͖���
		m_pBBox = NULL; // BBox�̐ݒ�
		m_vOffset = VECTOR3(0.0f, 0.0f, 0.0f);   // �I�t�Z�b�g�Ȃ�
		break;
	}

	m_bActive = FALSE;
	m_dwStatus = NORMAL;

}
// ---------------------------------------------------------------------------
//
// ����E��Ɏ��A�C�e���I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponHoldObj::~CWeaponHoldObj()
{
	SAFE_DELETE(m_pMesh);
}

// ---------------------------------------------------------------------------
//
// ����E��Ɏ��A�C�e���I�u�W�F�N�g�̏��𓾂�
//
//     MATRIX4X4  mHold       �F���̈ʒu
//     BASEHOLDITEM HoldItem  :��Ɏ�����̏��
//     MATRIX4X4& mMat        :��Ɏ�����̃}�g���b�N�X(Out)
//     VECTOR3& vMin          :�o�E���f�B���O�{�b�N�X��Min(Out)
//     VECTOR3& vMax          :�o�E���f�B���O�{�b�N�X��Max(Out)
//
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
void  CWeaponHoldObj::GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vMin, VECTOR3& vMax)
{
	// �I�t�Z�b�g�}�g���b�N�X�̌v�Z
	MATRIX4X4 mPos = XMMatrixTranslation(HoldItem.m_nOffsetPos.x, HoldItem.m_nOffsetPos.y, HoldItem.m_nOffsetPos.z);

	MATRIX4X4 mRotX = XMMatrixRotationX(XMConvertToRadians(HoldItem.m_nOffsetRot.x));
	MATRIX4X4 mRotY = XMMatrixRotationY(XMConvertToRadians(HoldItem.m_nOffsetRot.y));
	MATRIX4X4 mRotZ = XMMatrixRotationZ(XMConvertToRadians(HoldItem.m_nOffsetRot.z));

	MATRIX4X4 mOffset = mRotY * mRotX * mRotZ;
	mOffset = mOffset * mPos;

	// 
	// ���[���h�}�g���b�N�X�̌v�Z
	// 
	// �A���A���̂Ƃ�m_mWorld��m_pBBox->m_mWorld�̐ݒ�͍s���Ă��Ȃ�!!
	// 
	mMat = mOffset * mHold;     // ���̈ʒu�̃��[���h�}�g���b�N�X

	vMin = m_pBBox->m_vMin;
	vMax = m_pBBox->m_vMax;

	return;
}

// ---------------------------------------------------------------------------
//
// ����E��Ɏ��A�C�e���I�u�W�F�N�g�̏��𓾂�
//
//     MATRIX4X4  mHold       �F�e�̈ʒu
//     BASEHOLDITEM HoldItem  :��Ɏ�����̏��
//     MATRIX4X4& mMat        :��Ɏ�����̃}�g���b�N�X(Out)
//     VECTOR3& vOffset       :�e���܂ł̃I�t�Z�b�g(Out)
//
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
void  CWeaponHoldObj::GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vOffset)
{
	// �I�t�Z�b�g�}�g���b�N�X�̌v�Z
	MATRIX4X4 mPos = XMMatrixTranslation(HoldItem.m_nOffsetPos.x, HoldItem.m_nOffsetPos.y, HoldItem.m_nOffsetPos.z);

	MATRIX4X4 mRotX = XMMatrixRotationX(XMConvertToRadians(HoldItem.m_nOffsetRot.x));
	MATRIX4X4 mRotY = XMMatrixRotationY(XMConvertToRadians(HoldItem.m_nOffsetRot.y));
	MATRIX4X4 mRotZ = XMMatrixRotationZ(XMConvertToRadians(HoldItem.m_nOffsetRot.z));

	MATRIX4X4 mOffset = mRotY * mRotX * mRotZ;
	mOffset = mOffset * mPos;

	// ���[���h�}�g���b�N�X�̌v�Z
	// 
	// �A���A���̂Ƃ�m_mWorld�̐ݒ�͍s���Ă��Ȃ�!!
	// 
	mMat = mOffset * mHold;     // �e�̈ʒu�̃��[���h�}�g���b�N�X

	vOffset = m_vOffset;

	return;
}

// ---------------------------------------------------------------------------
//
// ����E��Ɏ��A�C�e���I�u�W�F�N�g�̃o�E���f�B���O�{�b�N�X�𓾂�
//
//     MATRIX4X4  mHold       �F���̈ʒu
//     BASEHOLDITEM HoldItem  :��Ɏ�����̏��
//
//     �߂�l�@�@CBBox* �o�E���f�B���O�{�b�N�X
// ---------------------------------------------------------------------------
CBBox* CWeaponHoldObj::GetBBox(MATRIX4X4 mHold, BASEHOLDITEM HoldItem)
{

	// �I�t�Z�b�g�}�g���b�N�X�̌v�Z
	MATRIX4X4 mPos = XMMatrixTranslation(HoldItem.m_nOffsetPos.x, HoldItem.m_nOffsetPos.y, HoldItem.m_nOffsetPos.z);

	MATRIX4X4 mRotX = XMMatrixRotationX(XMConvertToRadians(HoldItem.m_nOffsetRot.x));
	MATRIX4X4 mRotY = XMMatrixRotationY(XMConvertToRadians(HoldItem.m_nOffsetRot.y));
	MATRIX4X4 mRotZ = XMMatrixRotationZ(XMConvertToRadians(HoldItem.m_nOffsetRot.z));

	MATRIX4X4 mOffset = mRotY * mRotX * mRotZ;
	mOffset = mOffset * mPos;

	// ���[���h�}�g���b�N�X�̌v�Z
	// 
	// �A���A���̂Ƃ�m_mWorld��m_pBBox->m_mWorld�̐ݒ���s���Ă���!!
	// 
	m_mWorld = mOffset * mHold;     // ���̈ʒu�̃��[���h�}�g���b�N�X
	m_pBBox->m_mWorld = m_mWorld;   // �o�E���f�B���O�{�b�N�X�̃��[���h�}�g���b�N�X���Z�b�g

	return m_pBBox;

}


// ---------------------------------------------------------------------------
//
// ����E��Ɏ��A�C�e���I�u�W�F�N�g�̕`��
//
//     MATRIX4X4  mHold        �F�A�C�e���̈ʒu
//     VECTOR3    vPos         :�ʒu�̃I�t�Z�b�g
//     VECTOR3    vRot         :�p�x�̃I�t�Z�b�g
//
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
BOOL CWeaponHoldObj::Disp(MATRIX4X4 mHold, BASEHOLDITEM HoldItem)
{
	m_bActive = TRUE;  // �X�^�[�g���ɕ\���J�n

	// �I�t�Z�b�g�}�g���b�N�X�̌v�Z
	MATRIX4X4 mPos = XMMatrixTranslation(HoldItem.m_nOffsetPos.x, HoldItem.m_nOffsetPos.y, HoldItem.m_nOffsetPos.z);

	MATRIX4X4 mRotX = XMMatrixRotationX(XMConvertToRadians(HoldItem.m_nOffsetRot.x));
	MATRIX4X4 mRotY = XMMatrixRotationY(XMConvertToRadians(HoldItem.m_nOffsetRot.y));
	MATRIX4X4 mRotZ = XMMatrixRotationZ(XMConvertToRadians(HoldItem.m_nOffsetRot.z));

	MATRIX4X4 mOffset = mRotY * mRotX * mRotZ;
	mOffset = mOffset * mPos;

	// ���[���h�}�g���b�N�X�̌v�Z
	m_mWorld = mOffset * mHold;     // ���̈ʒu�̃��[���h�}�g���b�N�X
	if (m_pBBox) m_pBBox->m_mWorld = m_mWorld;   // �o�E���f�B���O�{�b�N�X�̃��[���h�}�g���b�N�X���Z�b�g

	// �����_�����O
	Render();

	m_bActive = FALSE;  // �P�񏈗�������A����

	return TRUE;
}

// ---------------------------------------------------------------------------
//
// ����E��Ɏ��A�C�e���I�u�W�F�N�g�̍X�V
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
void CWeaponHoldObj::Update()
{
	;
}
// ---------------------------------------------------------------------------
//
// ����E��Ɏ��A�C�e���I�u�W�F�N�g�̕`��
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
void CWeaponHoldObj::Render()
{

	// ��Ɏ��A�C�e���̃����_�����O
	if (m_pMesh) m_pMesh->Render(m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);

	// �o�E���f�B���O�{�b�N�X�����_�����O
	//if (m_pBBox) m_pBBox->Render(m_pGMain->m_mView, m_pGMain->m_mProj, VECTOR3(0, 0, 0), m_pGMain->m_vEyePt);
}

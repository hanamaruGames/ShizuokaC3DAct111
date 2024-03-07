//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�P�@�@�@�@�@�@                 ver 3.2        2023.1.31
//
//		����E���[�U�[�̏���
//															WeaponLaser.cpp
//=============================================================================
#include  "WeaponLaser.h"
#include  "Map.h"
#include  "Playchar.h"
#include  "Effect.h"


// ---------------------------------------------------------------------------
//
// ����E���[�U�[�v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CWeaponLaserProc::CWeaponLaserProc()
{
	// ���[�U�[���b�V���̐ݒ�
	m_pMeshArray.push_back(new CFbxMesh(GameDevice()->m_pFbxMeshCtrl, _T("Data/Item/Laser2.mesh")));   // -- 2022.12.20

	for (int i = 0; i < WEAPON_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponLaserObj(this));	// m_pObjArray�ɕ���E���[�U�[�I�u�W�F�N�g�𐶐�����
	}
}
// ---------------------------------------------------------------------------
//
// ����E���[�U�[�v���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponLaserProc::~CWeaponLaserProc()
{
	;
}
// ---------------------------------------------------------------------------
//
// ����E���[�U�[�v���V�[�W���̔���
//
//  MATRIX4X4  mGun         �F�e�̈ʒu�}�g���b�N�X
//  VECTOR3 vOffset      �F�ʒu�̔�����
//  MATRIX4X4  mOwnerWorld  �F���˂���L�����̃}�g���b�N�X
//  DWORD       dwOwner      �F����𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
// ---------------------------------------------------------------------------
bool CWeaponLaserProc::Start(MATRIX4X4 mGun, VECTOR3 vOffset, MATRIX4X4 mOwnerWorld, DWORD dwOwner)
{
	// ���[�U�[�̔���
	MATRIX4X4 mLay, mOwnerRot, mOffset;

	mLay = GetPositionMatrix(mGun);               // �e�̈ʒu(��]����菜��)
	mOwnerRot = GetRotateMatrix(mOwnerWorld);     // ���˂���L�����̉�]�}�g���b�N�X�̂�(�ʒu����菜��)�ɂ���
	mLay = mOwnerRot * mLay;                      // �e�̈ʒu����A�L�����̕����Ŕ��˂���}�g���b�N�X�����
	mOffset = XMMatrixTranslation(vOffset.x, vOffset.y, vOffset.z);	// �ʒu�̔�����
	mLay = mOffset * mLay;

	for (int i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(mLay, dwOwner);	       // ����E���[�U�[�I�u�W�F�N�g�̔���
			return true;
		}
	}

	return FALSE;
}

// ---------------------------------------------------------------------------
//
// ����E���[�U�[�v���V�[�W���̔���
//
//  MATRIX4X4  mWorld       �F���[�U�[�̔��ˈʒu�̃}�g���b�N�X
//  DWORD       dwOwner      �F����𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
// ---------------------------------------------------------------------------
bool CWeaponLaserProc::Start(MATRIX4X4 mWorld, DWORD dwOwner)
{
	for (int i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(mWorld, dwOwner);	       // ����E���[�U�[�I�u�W�F�N�g�̔���
			return true;
		}
	}
	return FALSE;
}

// ---------------------------------------------------------------------------
//
// ����E���[�U�[�I�u�W�F�N�g�̃R���X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponLaserObj::CWeaponLaserObj(CBaseProc* pProc) : CBaseObj(pProc)
{
	m_vTarget = VECTOR3(0, 0, 0);		// �^�[�Q�b�g
	m_vStart = VECTOR3(0, 0, 0);		// ���ˈʒu
	m_vEnd = VECTOR3(0, 0, 0);			// �ŏI���B�_

	m_bActive = FALSE;
	m_dwStatus = NORMAL;

	m_nAtc = WEAPON_ATC;

	m_dwOwner = 0;


}
// ---------------------------------------------------------------------------
//
// ����E���[�U�[�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponLaserObj::~CWeaponLaserObj()
{
	;
}

// ---------------------------------------------------------------------------
//
// ����E���[�U�[�I�u�W�F�N�g�̔���
//
//     MATRIX4X4 mStartWorld     ���[�U�[�̔��ˈʒu�̃}�g���b�N�X
//     DWORD      dwOwner         ����𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
bool CWeaponLaserObj::Start(MATRIX4X4 mStartWorld, DWORD dwOwner)
{

	if (m_bActive) return FALSE;

	m_bActive = true;
	m_mWorldOld = mStartWorld;  // ���[�U�[�̔��ˈʒu�̃}�g���b�N�X��ۑ����Ă���

	MATRIX4X4 mScale;
	mScale = XMMatrixScaling(1.0f, 1.0f, WEAPON_LENGTH);  // ���[�U�[�̒����̊g��}�g���b�N�X���쐬����
	m_mWorld = mScale * mStartWorld;                // ���[�U�[�̔��ˈʒu���烌�[�U�[�̒����Ɋg�債���}�g���b�N�X���쐬����

	MATRIX4X4 mTrans;
	mTrans = XMMatrixTranslation(0.0f, 0.0f, WEAPON_LENGTH);
	mTrans = mTrans * mStartWorld;     // ���[�U�[�̓��B�_�̃}�g���b�N�X���쐬����

	m_vStart = GetPositionVector(m_mWorldOld);	// ���[�U�[�̔��ˈʒu
	m_vEnd = GetPositionVector(mTrans);			// ���[�U�[�̓��B�ʒu

	m_dwOwner = dwOwner;

	return true;
}

// ---------------------------------------------------------------------------
//
// ����E���[�U�[�I�u�W�F�N�g�̍X�V
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
void CWeaponLaserObj::Update()
{

	if (m_bActive)
	{
		CPcProc* pPc = ObjectManager::FindGameObject<CPcProc>();
		// �G��o�b�Ƃ̂����蔻��
		if ((m_dwOwner != PC && pPc->Hitcheck(this, m_vEnd, m_vStart)))
		{
			ObjectManager::FindGameObject<CEffectParticleProc>()->Start(m_vHitPos, m_vHitNormal);	// �p�[�e�B�N���̔���
			//GameDevice()->m_pEffectProc->m_pEffectBillProc->Start(m_vHitPos);	// �����r���{�[�h�̔���
			GameDevice()->m_pSeDead->Play();// �������ʉ�

		}
		else {
			// �}�b�v�Ƃ̂����蔻��
			VECTOR3 vHit, vNormal;
			if (ObjectManager::FindGameObject<CMapProc>()->Hitcheck(m_vEnd, m_vStart, &vHit, &vNormal))
			{
				ObjectManager::FindGameObject<CEffectParticleProc>()->Start(vHit, vNormal);	// �p�[�e�B�N���̔���
				//GameDevice()->m_pEffectProc->m_pEffectBillProc->Start(vHit);	// �����r���{�[�h�̔���
				GameDevice()->m_pSeDead->Play();// �������ʉ�
			}
		}

		// �����_�����O
		Render();

	}

	m_bActive = FALSE;	// �P��ł�������

}

// ---------------------------------------------------------------------------
//
// ����E���[�U�[�I�u�W�F�N�g�̃����_�����O
//
//   �A�e�����Ȃ������_�����O�@���̕�����(0,0,0)
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
void CWeaponLaserObj::Render()
{

	// ���Z�����F�̃u�����f�B���O��ݒ�
	UINT mask = 0xffffffff;
	GameDevice()->m_pD3D->m_pDeviceContext->OMSetBlendState(GameDevice()->m_pD3D->m_pBlendStateAdd, nullptr, mask);
	GetMesh()->Render(m_mWorld, GameDevice()->m_mView, GameDevice()->m_mProj, VECTOR3(0, 0, 0), GameDevice()->m_vEyePt);        // -- 2022.2.16

	// �ʏ�̃u�����f�B���O��ݒ�
	GameDevice()->m_pD3D->m_pDeviceContext->OMSetBlendState(GameDevice()->m_pD3D->m_pBlendStateTrapen, nullptr, mask);

}

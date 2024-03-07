//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�P                             ver 3.2        2023.1.31
// 
//		����@���[�U�[
//														WeaponLaser.h
//=============================================================================
#pragma once
#include "GameMain.h"

// --------------------------------------------------------------------
//����@���[�U�[�@�I�u�W�F�N�g�N���X
// --------------------------------------------------------------------
class CWeaponLaserObj : public CBaseObj
{
protected:
	// �萔��`  ------------------------------------------
	static const int WEAPON_ATC = 10;       // �U����
	static const int WEAPON_LENGTH = 25;	// ���[�U�[�̒���

	// -------------------------------------------------

	VECTOR3                  m_vTarget;			// �^�[�Q�b�g
	VECTOR3                  m_vStart;			// ���ˈʒu
	VECTOR3                  m_vEnd;			// �ŏI���B�_
	DWORD                    m_dwOwner;			// ����𔭎˂����L�����敪�iPC:PC�@ENM:�G�j

public:
	bool Start(MATRIX4X4, DWORD dwOwner) override;
	void Update() override;
	void Render();

	// �A�N�Z�X�֐�
	CWeaponLaserObj(CBaseProc* pProc);	// �R���X�g���N�^        // -- 2022.2.16
	virtual	~CWeaponLaserObj();
};
// --------------------------------------------------------------------
//����@���[�U�[�@�v���V�[�W���N���X
// --------------------------------------------------------------------
class CWeaponLaserProc : public CBaseProc
{
protected:
	// �萔��`  ------------------------------------------
	static const int WEAPON_MAX = 20;    // MAX :����I�u�W�F�N�g�̐��B�i�����������j

public:
	bool Start(MATRIX4X4, DWORD dwOwner);  //����@���[�U�[�̔���
	bool Start(MATRIX4X4 mGun, VECTOR3 vOffset, MATRIX4X4 mOwnerWorld, DWORD dwOwner);

	CWeaponLaserProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponLaserProc();
};

//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�P                             ver 3.2        2023.1.31
// 
//		����@���[�U�[
//														WeaponLaser.h
//=============================================================================
#pragma once
#include "GameMain.h"
#include "Object3D.h"

// --------------------------------------------------------------------
//����@���[�U�[�@�I�u�W�F�N�g�N���X
// --------------------------------------------------------------------
class CWeaponLaserObj : public CBaseObj
{
public:
	// �I�u�W�F�N�g�敪
	enum OwnerID {
		PC = 0x00000001,
		NPC = 0x00000002,
		ENM = 0x00000004,
		OTHER = 0,
	};
protected:
	// �萔��`  ------------------------------------------
	static const int WEAPON_ATC = 10;       // �U����
	static const int WEAPON_LENGTH = 25;	// ���[�U�[�̒���

	// -------------------------------------------------

	VECTOR3                  m_vTarget;			// �^�[�Q�b�g
	VECTOR3                  m_vStart;			// ���ˈʒu
	VECTOR3                  m_vEnd;			// �ŏI���B�_
	OwnerID m_dwOwner;			// ����𔭎˂����L�����敪�iPC:PC�@ENM:�G�j

public:
	bool Start(MATRIX4X4, OwnerID dwOwner);
	void Update() override;
	void Draw() override;
	bool	Start(MATRIX4X4 mGun, DWORD dwOwner) override;

	// �A�N�Z�X�֐�
	CWeaponLaserObj(CBaseProc* pProc);	// �R���X�g���N�^        // -- 2022.2.16
	virtual	~CWeaponLaserObj();

	CXAudioSource* m_pSeDead;
};
// --------------------------------------------------------------------
//����@���[�U�[�@�v���V�[�W���N���X
// --------------------------------------------------------------------
class CWeaponLaserProc : public Object3D
{
protected:
	// �萔��`  ------------------------------------------
	static const int WEAPON_MAX = 20;    // MAX :����I�u�W�F�N�g�̐��B�i�����������j

public:
	bool Start(MATRIX4X4, DWORD dwOwner);  //����@���[�U�[�̔���
	bool Start(MATRIX4X4 mGun, VECTOR3 vOffset, MATRIX4X4 mOwnerWorld, CWeaponLaserObj::OwnerID dwOwner);

	CWeaponLaserProc();	// �R���X�g���N�^
	virtual	~CWeaponLaserProc();
};

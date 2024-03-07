//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�P                             ver 3.2        2023.1.31
//		����E�S�́@�@�w�b�_�t�@�C��								Weapon.h
//=============================================================================
#pragma once

#include "GameMain.h"

#include "WeaponLaser.h"
#include "WeaponHold.h"


// ======================================================================
// ����S�̂̃��C���v���V�[�W���N���X
// ======================================================================
class CWeaponProc : public CBaseProc
{
public:
	CWeaponLaserProc*     m_pWeaponLaserProc;
	CWeaponHoldProc*      m_pWeaponHoldProc;

public:
	CWeaponProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponProc() { ; }
};



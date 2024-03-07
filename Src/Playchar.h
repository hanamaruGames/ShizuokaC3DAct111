//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�P�@�@�@�@�@�@                 ver 3.2        2023.1.31
//		�v���C�L�����N�^�[�@�w�b�_�t�@�C��							Playchar.h
//=============================================================================
#pragma once
#include "GameMain.h"


// ---------------------------------------------------------------------
// �v���V�[�W��ID
// ---------------------------------------------------------------------
#define  PC_ID				100


//======================================================================
// �v���C�L�����N�^�[�@�I�u�W�F�N�g�N���X
//======================================================================
class CPcObj : public CBaseObj
{
protected:
	// �A�j���[�V�����ԍ� ---------------------------------
	const enum PCANIMNUM { eAnimNum_Idle = 0, eAnimNum_Walk = 1, eAnimNum_Run = 2, eAnimNum_Attack = 3, eAnimNum_Die = 4 };

	// �萔��`  ----------------------------------------
	static const int PC_DEADTIME = 200;				// ���S���̎���
	static const int PC_FLASHTIME = 5;				// �_���[�W��̖��G����
	static const int PC_DEADFLASHTIME = 400;		// ���S�㕜�A�����Ƃ��̖��G����
	static const int PC_MAXHP = 1000;				// �ő�̗�
	static const int PC_ATC = 50;					// �̂̍U����
	static const int PC_MOVE_FWDPOWER = 2;			// �O�i�ړ����x�{��     // -- 2023.1.31
	static const int PC_ROT_SPEED = 8;				// ��]���x             // -- 2023.1.31
	static const int PC_ROT_LOWSPEED = 1;			// �ᑬ��]���x         // -- 2023.1.31
	static const int PC_MOVE_BASESPEED_X100 = 16;	// �ړ���{���x��100�{  // -- 2023.1.31
	static const int PC_JUMP_SPEED_X100 = 20;		// �W�����v���x��100�{  // -- 2023.1.31


	// -------------------------------------------------
	float				m_fLocalRotY;		// ���[�J����(Y��)
	bool				m_bSide;			// ���ړ����[�h
	int					m_nMoveFwdPower;	// �O�i�ړ����x�{��

public:
	void Update() override;
	void UpdateNormal();       // -- 2019.3.5
	void UpdateNormalMove();   // -- 2019.3.5
	MATRIX4X4 UpdateNormalMoveKeystate(DWORD DIKey);  // -- 2021.1.10
	void UpdateNormalAttack(); // -- 2019.3.5
	void UpdateDamage();       // -- 2019.3.5
	void UpdateDead();         // -- 2019.3.5
	MATRIX4X4  GetLocalMatrix();			// ���[�J�����}�g���b�N�X�𓾂�
	void SetLocalRotY(float fRotY) { m_fLocalRotY = fRotY; }   // ���[�J����(Y��)���Z�b�g����

	CPcObj(CBaseProc* pProc);	// �R���X�g���N�^        // -- 2022.2.16
	virtual	~CPcObj();
};

//======================================================================
// �v���C�L�����N�^�[�@�v���V�[�W���N���X
//======================================================================
class CPcProc : public CBaseProc
{
protected:
	// �萔��`  ------------------------------------------
	static const int PC_ALLMAX = 3;      // PC�̍ő�o����

public:
	CPcObj*			    GetPcObjPtr() { return (CPcObj*)GetObjArrayPtr()[0]; }
	
	// �R���X�g���N�^
	CPcProc(CGameMain* pGMain);
	virtual	~CPcProc();
};


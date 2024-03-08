//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�P�@�@�@�@�@�@                 ver 3.2        2023.1.31
//		�v���C�L�����N�^�[�@�w�b�_�t�@�C��							Playchar.h
//=============================================================================
#pragma once
#include "GameMain.h"
#include "Object3D.h"

//======================================================================
// �v���C�L�����N�^�[�@�I�u�W�F�N�g�N���X
//======================================================================
class CPcObj : public CBaseObj
{
protected:
	// �A�j���[�V�����ԍ� ---------------------------------
	const enum PCANIMNUM { eAnimNum_Idle = 0, eAnimNum_Walk = 1, eAnimNum_Run = 2, eAnimNum_Attack = 3, eAnimNum_Die = 4 };

	// -------------------------------------------------
	float				m_fLocalRotY;		// ���[�J����(Y��)
	bool				m_bSide;			// ���ړ����[�h
	int					m_nMoveFwdPower;	// �O�i�ړ����x�{��

public:
	CPcObj(CBaseProc* pProc);	// �R���X�g���N�^        // -- 2022.2.16
	virtual	~CPcObj();
	void Update() override;
	void Draw() override;
	void OnCollision(CBaseObj* other) override;
private:
	MATRIX4X4 UpdateNormalMoveKeystate(DWORD DIKey);  // -- 2021.1.10
public:
	MATRIX4X4  GetLocalMatrix();			// ���[�J�����}�g���b�N�X�𓾂�
	void SetLocalRotY(float fRotY) { m_fLocalRotY = fRotY; }   // ���[�J����(Y��)���Z�b�g����
	int Remain() { return m_remain;	}
	int HpMax() { return hp.max; }
	int HpNow() { return hp.current; }
private:
	int m_remain; // �c�@
	struct Hp {
		int current;
		int max;
		Hp() {
			max = 1; // ����Ɏg���邱�Ƃ�����̂ŁA0�ɂ͂��Ȃ�
			current = max;
		}
	};
	Hp hp;
	CXAudioSource* m_seLaser; // ���ˉ��i����̕��Ɏ������������悢�j
	float m_jumpY;
	float m_jumpVelocity;
	float m_vRotY;

	float m_recoverTimer;
	// �X�e�[�g�p�^�[��
	enum Status {
		eNormal = 0,
		eAttack,
		eDead,
		eFlash,
	};
	Status m_status;
	void UpdateNormal();       // -- 2019.3.5
	void UpdateNormalMove();   // -- 2019.3.5
	void UpdateNormalAttack(); // -- 2019.3.5
	void UpdateDamage();       // -- 2019.3.5
	void UpdateDead();         // -- 2019.3.5
};

//======================================================================
// �v���C�L�����N�^�[�@�v���V�[�W���N���X
//======================================================================
class CPcProc : public Object3D
{
private:
public:
	CPcProc();
	virtual	~CPcProc();
	CPcObj* Obj() { return dynamic_cast<CPcObj*>(GetObj()); }
};

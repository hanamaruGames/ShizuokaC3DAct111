//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�P                             ver 3.2        2023.1.31
//
//		��{�v���V�[�W���E��{�I�u�W�F�N�g�N���X����
//																BaseProc.h
//=============================================================================
#pragma once
#include <vector>
#include "MyMath.h"
#include "FbxMesh.h"

// -------------------------------------------------------------------------------------------------  // -- 2021.2.4
// 
// ��Ɏ��A�C�e���═����w�肷��\����
// 
// -------------------------------------------------------------------------------------------------
struct BASEHOLDITEM
{
	int				m_nHoldObjNo;	// ��Ɏ��A�C�e���̃I�u�W�F�N�g�ԍ�
	int				m_nPosMesh;		// �A�C�e������������X�L�����b�V���̈ʒu�@���b�V���ԍ�
	int				m_nPosBone;		// �A�C�e������������X�L�����b�V���̈ʒu�@�{�[���ԍ�
	VECTOR3			m_nOffsetPos;	// ��Ɏ��A�C�e���̈ʒu�I�t�Z�b�g
	VECTOR3			m_nOffsetRot;	// ��Ɏ��A�C�e���̊p�x�I�t�Z�b�g
	BASEHOLDITEM()
	{
		m_nHoldObjNo = 0;				// ��Ɏ��A�C�e���̃I�u�W�F�N�g�ԍ�
		m_nPosMesh = 0;					// �A�C�e������������X�L�����b�V���̈ʒu�@���b�V���ԍ�
		m_nPosBone = 0;					// �A�C�e������������X�L�����b�V���̈ʒu�@�{�[���ԍ�
		m_nOffsetPos = VECTOR3(0, 0, 0);	// ��Ɏ��A�C�e���̈ʒu�I�t�Z�b�g
		m_nOffsetRot = VECTOR3(0, 0, 0);	// ��Ɏ��A�C�e���̊p�x�I�t�Z�b�g
	}
};

class CBBox;
class CBaseProc;

// --------------------------------------------------------------------------------------------------
// ��{�I�u�W�F�N�g�N���X
// 
// ���@�I�u�W�F�N�g�Ƃ́A�Q�[�����ɓo�ꂷ����̕��́A�Ⴆ�΂o�b��A����̂P�Ȃǂ��w���B
// �@�@�Ȃ��A�I�u�W�F�N�g�́A�e�v���V�[�W���̃����o�[�z��Ƃ��Đ錾����
// 
// --------------------------------------------------------------------------------------------------
class CBaseObj
{
protected:
	CBaseProc*		m_pProc;			// �e�̃v���V�[�W��                     // -- 2022.2.16
	bool			m_bActive;			// true:�\��  false:��\��
	int				m_nMeshIdx;			// ���b�V���z��̓Y��                   // -- 2022.12.20
	ANIMATION_STATUS m_AnimStatus;		// �A�j���[�V�����X�e�[�^�X
	CBBox*			m_pBBox;			// �o�E���f�B���O�{�b�N�X�N���X
	MATRIX4X4		m_mWorldOld;		// ���[���h�}�g���N�X�i��O�j
	MATRIX4X4		m_mWorld;			// ���[���h�}�g���N�X
	CBaseObj*		m_pHitObj;			// ������������̃I�u�W�F�N�g
	VECTOR3			m_vHitPos;			// ���������ꏊ�̍��W
	VECTOR3			m_vHitNormal;		// ���������ꏊ�̖@�����W
	int				m_nAtc;				// �U����

public:
	// �I�u�W�F�N�g�̔�������
	virtual bool	Start() { return true; }
	virtual bool	Start(VECTOR3 vPos) { return true; }
	virtual bool	Start(VECTOR3 vPos, VECTOR3 vNormal) { return true; }
	virtual bool	Start(MATRIX4X4 mGun, DWORD dwOwner) { return true; }
	virtual bool	Start(VECTOR3 vStart, VECTOR3 vTarget, DWORD dwOwner) { return true; }
	virtual bool	Start(MATRIX4X4 mMat, VECTOR3 vMin, VECTOR3 vMax, DWORD dwOwner) { return true; }
	virtual bool	Start(MATRIX4X4 mGun, VECTOR3 vOffset, MATRIX4X4 mOwnerWorld, DWORD dwOwner) { return true; }

	// �����蔻�菈��
	virtual bool    Hitcheck(CBaseObj* pOtherObj, VECTOR3 vNow, VECTOR3 vOld);
	virtual bool    Hitcheck(CBaseObj* pOtherObj, CBBox* pBBoxAtack);

	// �X�V����
	virtual	void    Update() { ; }
	virtual void    Draw() {}
	virtual void    OnCollision(CBaseObj* other) {}

	// �I�u�W�F�N�g���m���d�Ȃ�Ȃ��悤�ɂ��郁���o�֐�
	virtual	CBaseObj*	SetKeepOffset(CBaseProc* pProj);
	// �I�u�W�F�N�g��mWorld�ƈ����ʒu�Ƃ̋��������߂�
	virtual	float   GetDistance(VECTOR3 vPos);    // -- 2018.8.2

	// �A�N�Z�X�֐�
	virtual bool	GetActive() { return m_bActive; }
	virtual void	SetActive(bool bActive) { m_bActive = bActive; }
	virtual CFbxMesh* GetMesh();											// ���b�V���A�h���X    // -- 2022.2.16
	virtual BASEHOLDITEM GetHoldItem();										// ��Ɏ��A�C�e��    // -- 2022.2.16
	virtual int		GetMeshIdx() { return m_nMeshIdx; }						// ���b�V���z��̓Y��  // -- 2022.12.20
	virtual void	SetMeshIdx(int nIdx) { m_nMeshIdx = nIdx; }				// ���b�V���z��̓Y��  // -- 2022.12.20
	virtual CBBox*	GetBBox() { return m_pBBox; }
	virtual MATRIX4X4  GetWorld() { return m_mWorld; }
	virtual MATRIX4X4  GetWorldOld() { return m_mWorldOld; }
	virtual void    SetWorld(MATRIX4X4 mWorld) { m_mWorld = mWorld; }
	virtual void    SetWorldOld(MATRIX4X4 mWorldOld) { m_mWorldOld = mWorldOld; }
	virtual int		GetAtc() { return m_nAtc; }
	virtual ANIMATION_STATUS GetAnimStatus() { return m_AnimStatus; }    // -- 2018.8.2
	virtual void    SetAnimStatus(ANIMATION_STATUS as) { m_AnimStatus = as; }    // -- 2018.8.2

	// �R���X�g���N�^�i��{�I�u�W�F�N�g�̏������j
	CBaseObj(CBaseProc* pProc);
	// �f�X�g���N�^
	virtual		~CBaseObj();
};

// --------------------------------------------------------------------------------------------------
// ��{�v���V�[�W���N���X
//
//   ���@�v���V�[�W���Ƃ́A�u�����̏�������ɂ܂Ƃ߂����́v�Ƃ����Ӗ�
//       �����̃I�u�W�F�N�g�≺�ʃv���V�[�W�����R���g���[������N���X�̂���
//
// --------------------------------------------------------------------------------------------------
class  CBaseProc
{
protected:
	// 
	// ���ʂ̃v���V�[�W���|�C���^�z��́A�v���V�[�W�����K�w�\���ɂ��ĊǗ�����Ƃ��Ɏg�p����
	// �I�u�W�F�N�g�|�C���^�z��́A�v���V�[�W���̒��ɃI�u�W�F�N�g��z�u���ĊǗ�����Ƃ��Ɏg�p����
	// ��ʓI�ɂ́A�ǂ��炩�Е��݂̂��g�p���邱��
	std::vector<CBaseObj*>   m_pObjArray;	// �I�u�W�F�N�g�|�C���^�z��
	std::vector<CFbxMesh*>   m_pMeshArray;	// ���b�V���|�C���^�z��   // -- 2022.12.20
	std::vector<BASEHOLDITEM> m_HoldItemArray;		// ��Ɏ�����   // -- 2022.12.20
public:
	// �S�̍X�V�����i�S�Ẵv���V�[�W����I�u�W�F�N�g��ǂ݉����čX�V����������j
	virtual void	UpdateAll() final;

	// �X�V�����iUpdateAll()�̒��ŋN���B�v���V�[�W���̍X�V�����j
	virtual void    Update() { ; }

	// �����蔻��i�S�Ẵv���V�[�W����I�u�W�F�N�g��ǂ݉����ď���������j
	virtual bool    Hitcheck(CBaseObj* pOtherObj, VECTOR3 vNow, VECTOR3 vOld) final;
	virtual bool    Hitcheck(CBaseObj* pOtherObj, CBBox* pBBoxAtack) final;

	//	�v���V�[�W���ƃI�u�W�F�N�g��T�����S�ẴI�u�W�F�N�g���m���A�N�e�B�u�ɂ���
	virtual void	SetNonActive();

	// �A�N�Z�X�֐�
	virtual std::vector<CBaseObj*>  GetObjArrayPtr() { return m_pObjArray; }  // �I�u�W�F�N�g�|�C���^�z��̃A�h���X��Ԃ�
	virtual std::vector<CFbxMesh*>   GetMeshArrayPtr() { return m_pMeshArray; }	// ���b�V���|�C���^�z��   // -- 2022.2.16
	virtual std::vector<BASEHOLDITEM> GetHoldItemArrayPtr() { return m_HoldItemArray; }		// ��Ɏ�����   // -- 2022.2.16
	virtual CBaseObj* GetObj(int i=0) { return m_pObjArray[i]; } // -- 2022.2.16
	virtual CFbxMesh* GetMesh(int idx = 0);                      // -- 2022.12.20
	virtual BASEHOLDITEM  GetHoldItem(int idx = 0);              // -- 2022.12.20

	// �R���X�g���N�^�i��{�v���V�[�W���̏������j
	CBaseProc();
	// �f�X�g���N�^�i�v���V�[�W���ƃI�u�W�F�N�g�̉���j
	virtual		~CBaseProc();
	virtual void Draw();
};

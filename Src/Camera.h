//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�P                             ver 3.2        2023.1.31
//
//		�J��������
//
//		(���_�ύX�����E��Q����������������Ă���)
//
//																Camera.h
//=============================================================================
#pragma once
#include "GameMain.h"

//======================================================================
// �J�����@�I�u�W�F�N�g�N���X
//======================================================================
class CCameraObj : public CBaseObj
{
protected:
	int     m_nCtrl;                       // �J��������i0:�s�o�r���_  1:�e�o�r���_  2:�Œ莋�_�j
	VECTOR3 m_vBaseLocalLookat;            // ����[�J�������_�x�N�g��
	VECTOR3 m_vBaseLocalEye;               // ����[�J�����_�x�N�g��
	float   m_fBaseRotUp;                  // �p�x����
	float   m_fBaseDistUp;                 // �ړ�����

	MATRIX4X4 m_mBaseWorld;                // �����_�E���_�̊�_�ƂȂ��_���[���h�}�g���b�N�X
	VECTOR3 m_vLocalLookat;                // ���[�J�������_�x�N�g��
	VECTOR3 m_vLocalEye;                   // ���[�J�����_�x�N�g��

public:
	void Update() override;
	void InitCam(int ctrl, VECTOR3 lookat, VECTOR3 eye, float rot, float dist);
	void EvasiveObstacle();
	void ManualOperation();
	void SetLocalEyeTPS(float fRotY, float fRotX, float fDist);
	void SetCamBase();
	int  GetCtrl() { return m_nCtrl; }

	CCameraObj(CBaseProc* pProc);	// �R���X�g���N�^
	virtual	~CCameraObj();
};


//======================================================================
// �J�����@�v���V�[�W���N���X
//======================================================================
class CCameraProc : public CBaseProc
{
protected:
	int  m_nCamObjNo;                         // �J�����I�u�W�F�N�g�̗v�f�ԍ�

public:
	void Update() override;
	int GetCtrl() { return ((CCameraObj*)GetObjArrayPtr()[m_nCamObjNo])->GetCtrl(); }
	int GetCamObjNo() { return m_nCamObjNo; }
	void SetCamObjNo(int no) { m_nCamObjNo = no; }
	void InitCam(int no, int ctrl, VECTOR3 lookat, VECTOR3 eye, float rot, float dist);

	CCameraProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CCameraProc() { ; }
};


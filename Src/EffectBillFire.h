//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�P�@�@�@�@�@�@                 ver 3.2        2023.1.31
// 
//		�r���{�[�h�@���̃w�b�_�t�@�C��
//																EffectBillFire.h
//=============================================================================
#pragma once
#include "GameMain.h"
#include "Object3D.h"
#include "EffectStruct.h"

// ------------------------------------------------------------------------
//	�r���{�[�h�@���̃I�u�W�F�N�g�N���X
//
// ------------------------------------------------------------------------
class CEffectBillFireObj : public CBaseObj
{
public:
	// �萔��`  ------------------------------------------
	static const int EFFECT_ANIM_SPEED = 5;     // �A�j���[�V�����̑���

	// ----------------------------------------------------
	CDirect3D* m_pD3D;
	CShader* m_pShader;
	// 
	bool           m_bAuto;
	int            m_nBillIdx;
	VECTOR3        m_vPos;
	VECTOR2        m_vUVOffset;
	DWORD          m_dwFrame;

public:
	// 
	CEffectBillFireObj(CBaseProc* pProc);
	virtual ~CEffectBillFireObj();

	void Init();

	bool Start(int BillIdx, VECTOR3 vPos);
	void Update() override;
	void Draw() override;

	BILLBOARDBASE* GetBillArrayPtr();

};

// ========================================================================================
//
//	�r���{�[�h�@���̃v���V�[�W���N���X
//
// ========================================================================================
class CEffectBillFireObj;
class CEffectBillFireProc : public Object3D
{
protected:
	// �萔��`  ------------------------------------------
	static const int EFFECT_MAX = 500;       // MAX :�I�u�W�F�N�g�̐��B

	// ----------------------------------------------------
	std::vector<BILLBOARDBASE> m_BillboardArray;

public:
	HRESULT Load(TCHAR* szFName, BILLBOARDBASE* pBillBase);
	HRESULT SetSrc(BILLBOARDBASE* pBillBase);
	bool Start(VECTOR3 vPos);
	bool Start(int nBillIdx, VECTOR3 vPos);
	CEffectBillFireObj* Start(int nBillIdx = 0);

	BILLBOARDBASE* GetBillArrayPtr(int i);

	CEffectBillFireProc();	// �R���X�g���N�^
	virtual	~CEffectBillFireProc();	// �f�X�g���N�^
};

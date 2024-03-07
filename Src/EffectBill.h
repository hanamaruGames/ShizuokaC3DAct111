//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�P�@�@�@�@�@�@                 ver 3.2        2023.1.31
// 
//		�r���{�[�h�@�w�b�_�t�@�C��
//																EffectBill.h
//=============================================================================
#pragma once
#include "GameMain.h"
#include "Object3D.h"
#include "EffectStruct.h"

// ------------------------------------------------------------------------
//
//	�r���{�[�h�̃I�u�W�F�N�g�N���X
//
// ------------------------------------------------------------------------
class CEffectBillObj : public CBaseObj
{
public:
	// �萔��`  ------------------------------------------
	static const int EFFECT_ANIM_SPEED = 5;     // �A�j���[�V�����̑���

	// ----------------------------------------------------
	CDirect3D* m_pD3D;
	CShader* m_pShader;
	// 
	int            m_nBillIdx;
	VECTOR3        m_vPos;
	VECTOR2        m_vUVOffset;
	DWORD          m_dwFrame;

public:
	// 
	CEffectBillObj(CBaseProc* pProc);
	virtual	~CEffectBillObj();

	void Init();

	bool Start(int BillIdx, VECTOR3 vPos);
	void Update() override;
	bool Render();
	void RenderMesh();

	BILLBOARDBASE* GetBillArrayPtr();

};

// ========================================================================================
//
//	�r���{�[�h�̃v���V�[�W���N���X
//
// ========================================================================================
class CEffectBillProc : public Object3D
{
protected:
	// �萔��`  ------------------------------------------
	static const int EFFECT_MAX = 20;       // MAX :�I�u�W�F�N�g�̐��B

	// ----------------------------------------------------
	std::vector<BILLBOARDBASE> m_BillboardArray;

public:
	HRESULT Load(TCHAR* szFName, BILLBOARDBASE* pBillBase);
	HRESULT SetSrc(BILLBOARDBASE* pBillBase);
	bool Start(VECTOR3 vPos);
	bool Start(int nBillIdx, VECTOR3 vPos);

	BILLBOARDBASE* GetBillArrayPtr(int i);

	CEffectBillProc();	// �R���X�g���N�^
	virtual	~CEffectBillProc();	// �f�X�g���N�^
};


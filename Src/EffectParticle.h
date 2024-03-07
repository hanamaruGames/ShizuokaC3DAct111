//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�P�@�@�@�@�@�@                 ver 3.2        2023.1.31
// 
//		�p�[�e�B�N���̃w�b�_�t�@�C��
//															EffectParticle.h
//=============================================================================
#pragma once
#include "GameMain.h"
#include "EffectStruct.h"

// -----------------------------------------------------------------------------
//	�p�[�e�B�N���̃I�u�W�F�N�g�N���X
//�i�|�C���g�X�v���C�g�Ńp�[�e�B�N���������j
//
// ----------------------------------------------------------------------------
class CEffectParticleObj : public CBaseObj
{
protected:
	// �萔��`  ------------------------------------------
	static const int EFFECT_NUM_MAX = 100;    // MAX :�P�̃I�u�W�F�N�g�̒��̔������B

	// ----------------------------------------------------
	CDirect3D* m_pD3D;
	CShader* m_pShader;

	int            m_nPartIdx;     // �p�[�e�B�N���\���̔z��̗v�f�ԍ�
	int            m_MaxParticle;
	VECTOR3        m_vEmitPos;
	PART*          m_pPtArray;     // ��̃I�u�W�F�N�g�̒��̃p�[�e�B�N���z��
	int            m_Frame;

public:
	// 
	CEffectParticleObj(CBaseProc* pProc);
	virtual	~CEffectParticleObj();

	void Init();

	bool Start(int nPartIdx, VECTOR3 vEmitPos, VECTOR3 vNormal);
	void Update() override;
	void Render();
	void RenderParticle(MATRIX4X4 W, MATRIX4X4 V, MATRIX4X4 P);

	PARTICLEBASE* GetPartArrayPtr();

};

// ========================================================================================
//
//	�p�[�e�B�N���̃v���V�[�W���N���X
//
// ========================================================================================
class CEffectParticleProc : public CBaseProc
{
protected:
	// �萔��`  ------------------------------------------
	static const int EFFECT_MAX = 50;       // MAX :�I�u�W�F�N�g�̐��B

	// ----------------------------------------------------
	// �p�[�e�B�N���\���̔z��
	std::vector<PARTICLEBASE> m_ParticleArray;

public:
	bool Start(VECTOR3 vEmitPos, VECTOR3 vNormal = VECTOR3(0.0f, 0.0f, 0.0f));
	bool Start(int nPartIdx, VECTOR3 vEmitPos, VECTOR3 vNormal = VECTOR3(0.0f, 0.0f, 0.0f));

	HRESULT Load(TCHAR* szFName, PARTICLEBASE* pPartBase);
	HRESULT SetSrc(PARTICLEBASE* pPartBase);

	PARTICLEBASE* GetPartArrayPtr(int i);

	CEffectParticleProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CEffectParticleProc();	// �f�X�g���N�^
};

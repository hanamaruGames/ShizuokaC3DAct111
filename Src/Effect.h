//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�P                             ver 3.2        2023.1.31
//
//		�G�t�F�N�g�̏���
//																	Effect.h
//=============================================================================
#pragma once
#include "GameMain.h"
#include "Object3D.h"

#include "EffectStruct.h"
#include "EffectParticle.h"
#include "EffectBill.h"
#include "EffectBillFire.h"

// ========================================================================================
//
//	�G�t�F�N�g�S�̂̃��C���v���V�[�W���N���X
//
// ========================================================================================
class CEffectProc : public Object3D
{
public:
	CEffectParticleProc* m_pEffectParticleProc;
	CEffectBillProc*     m_pEffectBillProc;
	CEffectBillFireProc* m_pEffectBillFireProc;

public:
	CEffectProc();	// �R���X�g���N�^
	virtual	~CEffectProc() { ; }
};
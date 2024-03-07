//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�P                             ver 3.2        2023.1.31
//
//		�G�t�F�N�g�̏���
//																	Effect.cpp
//=============================================================================

#include "Effect.h"

//------------------------------------------------------------------------
//
//	�G�t�F�N�g�@���C���v���V�[�W���N���X�̃R���X�g���N�^	
//
//------------------------------------------------------------------------
CEffectProc::CEffectProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pEffectParticleProc = new CEffectParticleProc(pGMain);     // �p�[�e�B�N���v���V�[�W���̐���
	m_pProcArray.push_back(m_pEffectParticleProc);   // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pEffectBillProc = new CEffectBillProc(pGMain);     // �r���{�[�h�v���V�[�W���̐���
	m_pProcArray.push_back(m_pEffectBillProc);        // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pEffectBillFireProc = new CEffectBillFireProc(pGMain);     // �r���{�[�h���v���V�[�W���̐���
	m_pProcArray.push_back(m_pEffectBillFireProc);        // �v���V�[�W�����v���V�[�W���z��ɓo�^����

};


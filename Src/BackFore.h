//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�P�@�@�@�@�@�@                 ver 3.2        2023.1.31
//		                                                             BackFore.h
//=============================================================================
#pragma once
#include "GameMain.h"


// --------------------------------------------------------------------
// �O�i�E�w�i�@�v���V�[�W���N���X
// 
// (����)��{�v���V�[�W���N���X�͌p�����Ă��Ȃ�
// --------------------------------------------------------------------
class CBackForeProc 
{
protected:
	CGameMain*		m_pGMain;
	CSpriteImage*   m_pImageForegrd;
	CSprite*        m_pSprite;

public:
	void			Update();
	CSpriteImage*   GetImage() { return m_pImageForegrd; }
	CSprite*        GetSprite() { return m_pSprite; }
	CBackForeProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CBackForeProc();

};


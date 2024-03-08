//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１１　　　　　　                 ver 3.2        2023.1.31
//		                                                             BackFore.h
//=============================================================================
#pragma once
#include "GameMain.h"
#include "Object3D.h"
#include "Sprite3D.h"

// --------------------------------------------------------------------
// 前景・背景　プロシージャクラス
// 
// (注意)基本プロシージャクラスは継承していない
// --------------------------------------------------------------------
class CBackForeProc : Object3D
{
protected:
	CSpriteImage*   m_pImageForegrd;
	CSprite*        m_pSprite;

public:
	void			Draw() override;
	CSpriteImage*   GetImage() { return m_pImageForegrd; }
	CSprite*        GetSprite() { return m_pSprite; }
	CBackForeProc();	// コンストラクタ
	~CBackForeProc();

};


//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１１                             ver 3.2        2023.1.31
//		武器・全体　　ヘッダファイル								Weapon.h
//=============================================================================
#pragma once

#include "GameMain.h"
#include "Object3D.h"

#include "WeaponLaser.h"
#include "WeaponHold.h"


// ======================================================================
// 武器全体のメインプロシージャクラス
// ======================================================================
class CWeaponProc : public Object3D
{
public:
//	CWeaponLaserProc*     m_pWeaponLaserProc;
//	CWeaponHoldProc*      m_pWeaponHoldProc;

public:
	CWeaponProc();	// コンストラクタ
	virtual	~CWeaponProc() { ; }
};



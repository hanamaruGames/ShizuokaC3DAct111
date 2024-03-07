//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１１                             ver 3.2        2023.1.31
// 
//		武器　レーザー
//														WeaponLaser.h
//=============================================================================
#pragma once
#include "GameMain.h"

// --------------------------------------------------------------------
//武器　レーザー　オブジェクトクラス
// --------------------------------------------------------------------
class CWeaponLaserObj : public CBaseObj
{
protected:
	// 定数定義  ------------------------------------------
	static const int WEAPON_ATC = 10;       // 攻撃力
	static const int WEAPON_LENGTH = 25;	// レーザーの長さ

	// -------------------------------------------------

	VECTOR3                  m_vTarget;			// ターゲット
	VECTOR3                  m_vStart;			// 発射位置
	VECTOR3                  m_vEnd;			// 最終到達点
	DWORD                    m_dwOwner;			// 武器を発射したキャラ区分（PC:PC　ENM:敵）

public:
	bool Start(MATRIX4X4, DWORD dwOwner) override;
	void Update() override;
	void Render();

	// アクセス関数
	CWeaponLaserObj(CBaseProc* pProc);	// コンストラクタ        // -- 2022.2.16
	virtual	~CWeaponLaserObj();
};
// --------------------------------------------------------------------
//武器　レーザー　プロシージャクラス
// --------------------------------------------------------------------
class CWeaponLaserProc : public CBaseProc
{
protected:
	// 定数定義  ------------------------------------------
	static const int WEAPON_MAX = 20;    // MAX :武器オブジェクトの数。（同時発生数）

public:
	bool Start(MATRIX4X4, DWORD dwOwner);  //武器　レーザーの発射
	bool Start(MATRIX4X4 mGun, VECTOR3 vOffset, MATRIX4X4 mOwnerWorld, DWORD dwOwner);

	CWeaponLaserProc(CGameMain* pGMain);	// コンストラクタ
	virtual	~CWeaponLaserProc();
};

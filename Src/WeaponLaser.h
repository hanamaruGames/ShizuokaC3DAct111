//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１１                             ver 3.2        2023.1.31
// 
//		武器　レーザー
//														WeaponLaser.h
//=============================================================================
#pragma once
#include "GameMain.h"
#include "Object3D.h"

// --------------------------------------------------------------------
//武器　レーザー　オブジェクトクラス
// --------------------------------------------------------------------
class CWeaponLaserObj : public CBaseObj
{
public:
	// オブジェクト区分
	enum OwnerID {
		PC = 0x00000001,
		NPC = 0x00000002,
		ENM = 0x00000004,
		OTHER = 0,
	};
protected:
	// 定数定義  ------------------------------------------
	static const int WEAPON_ATC = 10;       // 攻撃力
	static const int WEAPON_LENGTH = 25;	// レーザーの長さ

	// -------------------------------------------------

	VECTOR3                  m_vTarget;			// ターゲット
	VECTOR3                  m_vStart;			// 発射位置
	VECTOR3                  m_vEnd;			// 最終到達点
	OwnerID m_dwOwner;			// 武器を発射したキャラ区分（PC:PC　ENM:敵）

public:
	bool Start(MATRIX4X4, OwnerID dwOwner);
	void Update() override;
	void Draw() override;
	bool	Start(MATRIX4X4 mGun, DWORD dwOwner) override;

	// アクセス関数
	CWeaponLaserObj(CBaseProc* pProc);	// コンストラクタ        // -- 2022.2.16
	virtual	~CWeaponLaserObj();

	CXAudioSource* m_pSeDead;
};
// --------------------------------------------------------------------
//武器　レーザー　プロシージャクラス
// --------------------------------------------------------------------
class CWeaponLaserProc : public Object3D
{
protected:
	// 定数定義  ------------------------------------------
	static const int WEAPON_MAX = 20;    // MAX :武器オブジェクトの数。（同時発生数）

public:
	bool Start(MATRIX4X4, DWORD dwOwner);  //武器　レーザーの発射
	bool Start(MATRIX4X4 mGun, VECTOR3 vOffset, MATRIX4X4 mOwnerWorld, CWeaponLaserObj::OwnerID dwOwner);

	CWeaponLaserProc();	// コンストラクタ
	virtual	~CWeaponLaserProc();
};

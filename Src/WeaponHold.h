//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１１                             ver 3.2        2023.1.31
// 
//		武器　手に持つアイテム
//														WeaponHold.h
//=============================================================================
#pragma once
#include "GameMain.h"

// --------------------------------------------------------------------
//武器　手に持つアイテム　オブジェクトクラス
// --------------------------------------------------------------------
class CWeaponHoldObj : public CBaseObj
{
protected:
	int                      m_nKindNo;			// 手に持つアイテムの種類(1:剣　2:銃)
	CFbxMesh* m_pMesh;			// Fbxメッシュ(プロシージャではなくオブジェクトにメッシュを持たせる)
	VECTOR3                  m_vOffset;			// 銃口までのオフセット（銃のみ）
public:
	void Init();
	bool Disp(MATRIX4X4 mHold, BASEHOLDITEM HoldItem);
	void GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vOffset);
	void GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vMin, VECTOR3& vMax);
	CBBox* GetBBox(MATRIX4X4 mHold, BASEHOLDITEM HoldItem);

	void Update() override;
	void Render();

	int GetKind() { return m_nKindNo; }

	CWeaponHoldObj(CBaseProc* pProc);	// コンストラクタ        // -- 2022.2.16
	virtual	~CWeaponHoldObj();
};
// --------------------------------------------------------------------
//武器　手に持つアイテム　プロシージャクラス
// --------------------------------------------------------------------
class CWeaponHoldProc : public CBaseProc
{
protected:
	// 定数定義  ------------------------------------------
	static const int WEAPON_MAX = 15;    // MAX :武器オブジェクトの数。（同時発生数）

public:
	bool Disp(MATRIX4X4 mHold, BASEHOLDITEM HoldItem); // 武器　の表示
	void GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vOffset);
	void GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vMin, VECTOR3& vMax);
	CBBox* GetBBox(MATRIX4X4 mHold, BASEHOLDITEM HoldItem);
	int GetKind(BASEHOLDITEM HoldItem);
	CWeaponHoldProc(CGameMain* pGMain);	// コンストラクタ
	virtual	~CWeaponHoldProc();
};

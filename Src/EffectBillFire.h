//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１１　　　　　　                 ver 3.2        2023.1.31
// 
//		ビルボード　炎のヘッダファイル
//																EffectBillFire.h
//=============================================================================
#pragma once
#include "GameMain.h"
#include "Object3D.h"
#include "EffectStruct.h"

// ------------------------------------------------------------------------
//	ビルボード　炎のオブジェクトクラス
//
// ------------------------------------------------------------------------
class CEffectBillFireObj : public CBaseObj
{
public:
	// 定数定義  ------------------------------------------
	static const int EFFECT_ANIM_SPEED = 5;     // アニメーションの速さ

	// ----------------------------------------------------
	CDirect3D* m_pD3D;
	CShader* m_pShader;
	// 
	bool           m_bAuto;
	int            m_nBillIdx;
	VECTOR3        m_vPos;
	VECTOR2        m_vUVOffset;
	DWORD          m_dwFrame;

public:
	// 
	CEffectBillFireObj(CBaseProc* pProc);
	virtual ~CEffectBillFireObj();

	void Init();

	bool Start(int BillIdx, VECTOR3 vPos);
	void Update() override;
	void Draw() override;

	BILLBOARDBASE* GetBillArrayPtr();

};

// ========================================================================================
//
//	ビルボード　炎のプロシージャクラス
//
// ========================================================================================
class CEffectBillFireObj;
class CEffectBillFireProc : public Object3D
{
protected:
	// 定数定義  ------------------------------------------
	static const int EFFECT_MAX = 500;       // MAX :オブジェクトの数。

	// ----------------------------------------------------
	std::vector<BILLBOARDBASE> m_BillboardArray;

public:
	HRESULT Load(TCHAR* szFName, BILLBOARDBASE* pBillBase);
	HRESULT SetSrc(BILLBOARDBASE* pBillBase);
	bool Start(VECTOR3 vPos);
	bool Start(int nBillIdx, VECTOR3 vPos);
	CEffectBillFireObj* Start(int nBillIdx = 0);

	BILLBOARDBASE* GetBillArrayPtr(int i);

	CEffectBillFireProc();	// コンストラクタ
	virtual	~CEffectBillFireProc();	// デストラクタ
};

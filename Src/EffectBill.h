//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１１　　　　　　                 ver 3.2        2023.1.31
// 
//		ビルボード　ヘッダファイル
//																EffectBill.h
//=============================================================================
#pragma once
#include "GameMain.h"
#include "Object3D.h"
#include "EffectStruct.h"

// ------------------------------------------------------------------------
//
//	ビルボードのオブジェクトクラス
//
// ------------------------------------------------------------------------
class CEffectBillObj : public CBaseObj
{
public:
	// 定数定義  ------------------------------------------
	static const int EFFECT_ANIM_SPEED = 5;     // アニメーションの速さ

	// ----------------------------------------------------
	CDirect3D* m_pD3D;
	CShader* m_pShader;
	// 
	int            m_nBillIdx;
	VECTOR3        m_vPos;
	VECTOR2        m_vUVOffset;
	DWORD          m_dwFrame;

public:
	// 
	CEffectBillObj(CBaseProc* pProc);
	virtual	~CEffectBillObj();

	void Init();

	bool Start(int BillIdx, VECTOR3 vPos);
	void Update() override;
	bool Render();
	void RenderMesh();

	BILLBOARDBASE* GetBillArrayPtr();

};

// ========================================================================================
//
//	ビルボードのプロシージャクラス
//
// ========================================================================================
class CEffectBillProc : public Object3D
{
protected:
	// 定数定義  ------------------------------------------
	static const int EFFECT_MAX = 20;       // MAX :オブジェクトの数。

	// ----------------------------------------------------
	std::vector<BILLBOARDBASE> m_BillboardArray;

public:
	HRESULT Load(TCHAR* szFName, BILLBOARDBASE* pBillBase);
	HRESULT SetSrc(BILLBOARDBASE* pBillBase);
	bool Start(VECTOR3 vPos);
	bool Start(int nBillIdx, VECTOR3 vPos);

	BILLBOARDBASE* GetBillArrayPtr(int i);

	CEffectBillProc();	// コンストラクタ
	virtual	~CEffectBillProc();	// デストラクタ
};


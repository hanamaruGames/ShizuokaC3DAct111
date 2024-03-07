//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１１　　　　　　                 ver 3.2        2023.1.31
// 
//		パーティクルのヘッダファイル
//															EffectParticle.h
//=============================================================================
#pragma once
#include "GameMain.h"
#include "EffectStruct.h"

// -----------------------------------------------------------------------------
//	パーティクルのオブジェクトクラス
//（ポイントスプライトでパーティクルを実現）
//
// ----------------------------------------------------------------------------
class CEffectParticleObj : public CBaseObj
{
protected:
	// 定数定義  ------------------------------------------
	static const int EFFECT_NUM_MAX = 100;    // MAX :１つのオブジェクトの中の発生数。

	// ----------------------------------------------------
	CDirect3D* m_pD3D;
	CShader* m_pShader;

	int            m_nPartIdx;     // パーティクル構造体配列の要素番号
	int            m_MaxParticle;
	VECTOR3        m_vEmitPos;
	PART*          m_pPtArray;     // 一つのオブジェクトの中のパーティクル配列
	int            m_Frame;

public:
	// 
	CEffectParticleObj(CBaseProc* pProc);
	virtual	~CEffectParticleObj();

	void Init();

	bool Start(int nPartIdx, VECTOR3 vEmitPos, VECTOR3 vNormal);
	void Update() override;
	void Render();
	void RenderParticle(MATRIX4X4 W, MATRIX4X4 V, MATRIX4X4 P);

	PARTICLEBASE* GetPartArrayPtr();

};

// ========================================================================================
//
//	パーティクルのプロシージャクラス
//
// ========================================================================================
class CEffectParticleProc : public CBaseProc
{
protected:
	// 定数定義  ------------------------------------------
	static const int EFFECT_MAX = 50;       // MAX :オブジェクトの数。

	// ----------------------------------------------------
	// パーティクル構造体配列
	std::vector<PARTICLEBASE> m_ParticleArray;

public:
	bool Start(VECTOR3 vEmitPos, VECTOR3 vNormal = VECTOR3(0.0f, 0.0f, 0.0f));
	bool Start(int nPartIdx, VECTOR3 vEmitPos, VECTOR3 vNormal = VECTOR3(0.0f, 0.0f, 0.0f));

	HRESULT Load(TCHAR* szFName, PARTICLEBASE* pPartBase);
	HRESULT SetSrc(PARTICLEBASE* pPartBase);

	PARTICLEBASE* GetPartArrayPtr(int i);

	CEffectParticleProc(CGameMain* pGMain);	// コンストラクタ
	~CEffectParticleProc();	// デストラクタ
};

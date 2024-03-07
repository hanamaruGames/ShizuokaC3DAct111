//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１１                             ver 3.2        2023.1.31
//
//		エフェクトの処理
//																	Effect.cpp
//=============================================================================

#include "Effect.h"

//------------------------------------------------------------------------
//
//	エフェクト　メインプロシージャクラスのコンストラクタ	
//
//------------------------------------------------------------------------
CEffectProc::CEffectProc()
{
	Instantiate<CEffectParticleProc>();
//	m_pEffectParticleProc = new CEffectParticleProc(pGMain);     // パーティクルプロシージャの生成
//	m_pProcArray.push_back(m_pEffectParticleProc);   // プロシージャをプロシージャ配列に登録する

	Instantiate<CEffectBillProc>();
//	m_pEffectBillProc = new CEffectBillProc(pGMain);     // ビルボードプロシージャの生成
//	m_pProcArray.push_back(m_pEffectBillProc);        // プロシージャをプロシージャ配列に登録する

	Instantiate<CEffectBillFireProc>();
//	m_pEffectBillFireProc = new CEffectBillFireProc(pGMain);     // ビルボード炎プロシージャの生成
//	m_pProcArray.push_back(m_pEffectBillFireProc);        // プロシージャをプロシージャ配列に登録する

};


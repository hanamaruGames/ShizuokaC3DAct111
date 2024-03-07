//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１１                             ver 3.2        2023.1.31
//
//		エフェクトの処理
//																	Effect.h
//=============================================================================
#pragma once
#include "GameMain.h"
#include "Object3D.h"

#include "EffectStruct.h"
#include "EffectParticle.h"
#include "EffectBill.h"
#include "EffectBillFire.h"

// ========================================================================================
//
//	エフェクト全体のメインプロシージャクラス
//
// ========================================================================================
class CEffectProc : public Object3D
{
public:
	CEffectParticleProc* m_pEffectParticleProc;
	CEffectBillProc*     m_pEffectBillProc;
	CEffectBillFireProc* m_pEffectBillFireProc;

public:
	CEffectProc();	// コンストラクタ
	virtual	~CEffectProc() { ; }
};
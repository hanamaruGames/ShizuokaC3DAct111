//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１１　　　　　　                 ver 3.2        2023.1.31
//		プレイキャラクター　ヘッダファイル							Playchar.h
//=============================================================================
#pragma once
#include "GameMain.h"


// ---------------------------------------------------------------------
// プロシージャID
// ---------------------------------------------------------------------
#define  PC_ID				100


//======================================================================
// プレイキャラクター　オブジェクトクラス
//======================================================================
class CPcObj : public CBaseObj
{
protected:
	// アニメーション番号 ---------------------------------
	const enum PCANIMNUM { eAnimNum_Idle = 0, eAnimNum_Walk = 1, eAnimNum_Run = 2, eAnimNum_Attack = 3, eAnimNum_Die = 4 };

	// 定数定義  ----------------------------------------
	static const int PC_DEADTIME = 200;				// 死亡中の時間
	static const int PC_FLASHTIME = 5;				// ダメージ後の無敵時間
	static const int PC_DEADFLASHTIME = 400;		// 死亡後復帰したときの無敵時間
	static const int PC_MAXHP = 1000;				// 最大体力
	static const int PC_ATC = 50;					// 体の攻撃力
	static const int PC_MOVE_FWDPOWER = 2;			// 前進移動速度倍率     // -- 2023.1.31
	static const int PC_ROT_SPEED = 8;				// 回転速度             // -- 2023.1.31
	static const int PC_ROT_LOWSPEED = 1;			// 低速回転速度         // -- 2023.1.31
	static const int PC_MOVE_BASESPEED_X100 = 16;	// 移動基本速度の100倍  // -- 2023.1.31
	static const int PC_JUMP_SPEED_X100 = 20;		// ジャンプ速度の100倍  // -- 2023.1.31


	// -------------------------------------------------
	float				m_fLocalRotY;		// ローカル軸(Y軸)
	bool				m_bSide;			// 横移動モード
	int					m_nMoveFwdPower;	// 前進移動速度倍率

public:
	void Update() override;
	void UpdateNormal();       // -- 2019.3.5
	void UpdateNormalMove();   // -- 2019.3.5
	MATRIX4X4 UpdateNormalMoveKeystate(DWORD DIKey);  // -- 2021.1.10
	void UpdateNormalAttack(); // -- 2019.3.5
	void UpdateDamage();       // -- 2019.3.5
	void UpdateDead();         // -- 2019.3.5
	MATRIX4X4  GetLocalMatrix();			// ローカル軸マトリックスを得る
	void SetLocalRotY(float fRotY) { m_fLocalRotY = fRotY; }   // ローカル軸(Y軸)をセットする

	CPcObj(CBaseProc* pProc);	// コンストラクタ        // -- 2022.2.16
	virtual	~CPcObj();
};

//======================================================================
// プレイキャラクター　プロシージャクラス
//======================================================================
class CPcProc : public CBaseProc
{
protected:
	// 定数定義  ------------------------------------------
	static const int PC_ALLMAX = 3;      // PCの最大出現数

public:
	CPcObj*			    GetPcObjPtr() { return (CPcObj*)GetObjArrayPtr()[0]; }
	
	// コンストラクタ
	CPcProc(CGameMain* pGMain);
	virtual	~CPcProc();
};


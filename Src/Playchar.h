//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１１　　　　　　                 ver 3.2        2023.1.31
//		プレイキャラクター　ヘッダファイル							Playchar.h
//=============================================================================
#pragma once
#include "GameMain.h"
#include "Object3D.h"

//======================================================================
// プレイキャラクター　オブジェクトクラス
//======================================================================
class CPcObj : public CBaseObj
{
protected:
	// アニメーション番号 ---------------------------------
	const enum PCANIMNUM { eAnimNum_Idle = 0, eAnimNum_Walk = 1, eAnimNum_Run = 2, eAnimNum_Attack = 3, eAnimNum_Die = 4 };

	// -------------------------------------------------
	float				m_fLocalRotY;		// ローカル軸(Y軸)
	bool				m_bSide;			// 横移動モード
	int					m_nMoveFwdPower;	// 前進移動速度倍率

public:
	CPcObj(CBaseProc* pProc);	// コンストラクタ        // -- 2022.2.16
	virtual	~CPcObj();
	void Update() override;
	void Draw() override;
	void OnCollision(CBaseObj* other) override;
private:
	MATRIX4X4 UpdateNormalMoveKeystate(DWORD DIKey);  // -- 2021.1.10
public:
	MATRIX4X4  GetLocalMatrix();			// ローカル軸マトリックスを得る
	void SetLocalRotY(float fRotY) { m_fLocalRotY = fRotY; }   // ローカル軸(Y軸)をセットする
	int Remain() { return m_remain;	}
	int HpMax() { return hp.max; }
	int HpNow() { return hp.current; }
private:
	int m_remain; // 残機
	struct Hp {
		int current;
		int max;
		Hp() {
			max = 1; // 分母に使われることがあるので、0にはしない
			current = max;
		}
	};
	Hp hp;
	CXAudioSource* m_seLaser; // 発射音（武器の方に持たせた方がよい）
	float m_jumpY;
	float m_jumpVelocity;
	float m_vRotY;

	float m_recoverTimer;
	// ステートパターン
	enum Status {
		eNormal = 0,
		eAttack,
		eDead,
		eFlash,
	};
	Status m_status;
	void UpdateNormal();       // -- 2019.3.5
	void UpdateNormalMove();   // -- 2019.3.5
	void UpdateNormalAttack(); // -- 2019.3.5
	void UpdateDamage();       // -- 2019.3.5
	void UpdateDead();         // -- 2019.3.5
};

//======================================================================
// プレイキャラクター　プロシージャクラス
//======================================================================
class CPcProc : public Object3D
{
private:
public:
	CPcProc();
	virtual	~CPcProc();
	CPcObj* Obj() { return dynamic_cast<CPcObj*>(GetObj()); }
};

//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１１　　　　　　                 ver 3.2        2023.1.31
//
//		プレイキャラクターの制御
//																Playchar.cpp
//=============================================================================
#include  "Playchar.h"
#include  "Camera.h"
#include  "BackFore.h"
#include  "Weapon.h"
#include  "Map.h"
#include  "Effect.h"
#include "Time.h"

namespace {
	// 定数定義  ----------------------------------------
	const float DEADTIME = 3.0f;				// 死亡中の時間
	const float FLASHTIME = 0.1f;				// ダメージ後の無敵時間
	const float DEADFLASHTIME = 7.0f;		// 死亡後復帰したときの無敵時間
	const int PC_MAXHP = 1000;				// 最大体力
	const int PC_ATC = 50;					// 体の攻撃力
	const int PC_MOVE_FWDPOWER = 2;			// 前進移動速度倍率     // -- 2023.1.31
	const float ROT_SPEED = 360.0f;		// 回転速度（秒）             // -- 2023.1.31
	const float ROT_LOWSPEED = 60.0f;	// 低速回転速度（秒）         // -- 2023.1.31
	const float MOVE_BASESPEED = 10.0f;     // 移動速度（１秒あたり）
	const int REMAIN_MAX = 3;                // PCの最大出現数
	const float GAMEGRAVITY = -9.8f / 2.0f; // 重力加速度（１秒あたり）
	const float JUMP_POWER = 0.5f;
};


//============================================================================
//
// ＰＣプロシージャのコンストラクタ
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CPcProc::CPcProc()
{
	BASEHOLDITEM hi;

	// Fbxスキンメッシュの設定                                          // -- 2022.12.20
	// ＰＣ２　銃－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
	//m_pMeshArray.push_back( new CFbxMesh( GameDevice()->m_pFbxMeshCtrl, _T("Data/Char/PC2/pc2g.mesh")));    // ＰＣ２　銃
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC2/pc2g_stand.anmx"));  // 0:eAnimNum_Idle
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC2/pc2g_walk.anmx"));   // 1:eAnimNum_Walk
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC2/pc2g_walk.anmx"));   // 2:eAnimNum_Run
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC2/pc2g_walk.anmx"));   // 3:eAnimNum_Attack
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC2/pc2g_die.anmx"));    // 4:eAnimNum_Die
	//m_pMeshArray.back()->m_fHeightMax = 0.01f;
	//m_pMeshArray.back()->m_iMaxDevide = 64;
	//m_HoldItemArray.push_back(hi);
	//m_HoldItemArray.back().m_nHoldObjNo = 4;	// 手に持つ武器のオブジェ番号(透明な銃)
	//m_HoldItemArray.back().m_nPosMesh = 3;	// 銃の根元位置のメッシュ番号
	//m_HoldItemArray.back().m_nPosBone = 13;	// 銃の根元位置のボーン番号
	//m_HoldItemArray.back().m_nOffsetPos = VECTOR3(0.2f, 0.0f, -0.03f);  // 手に持つ武器の位置オフセット
	//m_HoldItemArray.back().m_nOffsetRot = VECTOR3(-90.0f, 0.0f, 0.0f);  // 手に持つ武器の角度オフセット

	// ＰＣ２　剣－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
	//m_pMeshArray.push_back( new CFbxMesh( GameDevice()->m_pFbxMeshCtrl, _T("Data/Char/PC2/pc2s.mesh")));    // ＰＣ２　剣
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC2/pc2s_stand.anmx"));  // 0:eAnimNum_Idle
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC2/pc2s_walk.anmx"));   // 1:eAnimNum_Walk
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC2/pc2s_walk.anmx"));   // 2:eAnimNum_Run
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC2/pc2s_attack.anmx")); // 3:eAnimNum_Attack
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC2/pc2s_die.anmx"));    // 4:eAnimNum_Die
	//m_pMeshArray.back()->m_fHeightMax = 0.01f;
	//m_pMeshArray.back()->m_iMaxDevide = 64;
	//m_HoldItemArray.push_back(hi);
	//m_HoldItemArray.back().m_nHoldObjNo = 1;	// 手に持つ武器のオブジェ番号(透明な剣)
	//m_HoldItemArray.back().m_nPosMesh = 3;		// 剣の根元位置のメッシュ番号
	//m_HoldItemArray.back().m_nPosBone = 13;	// 剣の根元位置のボーン番号
	//m_HoldItemArray.back().m_nOffsetPos = VECTOR3(0.0f, 0.0f, 0.0f);  // 手に持つ武器の位置オフセット
	//m_HoldItemArray.back().m_nOffsetRot = VECTOR3(0.0f, 0.0f, -90.0f);  // 手に持つ武器の角度オフセット

	// ＰＣ４　銃－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
	//m_pMeshArray.push_back( new CFbxMesh(GameDevice()->m_pFbxMeshCtrl, _T("Data/Char/PC4/pc4g.mesh")));    // ＰＣ４　銃
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC4/pc4g_stand.anmx"));  // 0:eAnimNum_Idle
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC4/pc4g_walk.anmx"));   // 1:eAnimNum_Walk
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC4/pc4g_walk.anmx"));   // 2:eAnimNum_Run
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC4/pc4g_walk.anmx"));   // 3:eAnimNum_Attack
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC4/pc4g_die.anmx"));    // 4:eAnimNum_Die
	//m_pMeshArray.back()->m_fHeightMax = 0.01f;
	//m_pMeshArray.back()->m_iMaxDevide = 64;
	//m_HoldItemArray.push_back(hi);
	//m_HoldItemArray.back().m_nHoldObjNo = 4;	// 手に持つ武器のオブジェ番号(透明な銃)
	//m_HoldItemArray.back().m_nPosMesh = 7;		// 銃の根元位置のメッシュ番号
	//m_HoldItemArray.back().m_nPosBone = 19;	// 銃の根元位置のボーン番号
	//m_HoldItemArray.back().m_nOffsetPos = VECTOR3(0.0f, 0.0f, 0.0f);  // 手に持つ武器の位置オフセット
	//m_HoldItemArray.back().m_nOffsetRot = VECTOR3(0.0f, 180.0f, 0.0f);  // 手に持つ武器の角度オフセット

	// ＰＣ４　剣－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
	//m_pMeshArray.push_back( new CFbxMesh(GameDevice()->m_pFbxMeshCtrl, _T("Data/Char/PC4/pc4s.mesh")));    // ＰＣ４　剣
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC4/pc4s_stand.anmx"));  // 0:eAnimNum_Idle
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC4/pc4s_walk.anmx"));   // 1:eAnimNum_Walk
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC4/pc4s_walk.anmx"));   // 2:eAnimNum_Run
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC4/pc4s_attack.anmx")); // 3:eAnimNum_Attack
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/PC4/pc4s_die.anmx"));    // 4:eAnimNum_Die
	//m_pMeshArray.back()->m_fHeightMax = 0.01f;
	//m_pMeshArray.back()->m_iMaxDevide = 64;
	//m_HoldItemArray.push_back(hi);
	//m_HoldItemArray.back().m_nHoldObjNo = 1;	// 手に持つ武器のオブジェ番号(透明な剣)
	//m_HoldItemArray.back().m_nPosMesh = 7;		// 剣の根元位置のメッシュ番号
	//m_HoldItemArray.back().m_nPosBone = 19;		// 剣の根元位置のボーン番号
	//m_HoldItemArray.back().m_nOffsetPos = VECTOR3(0.0f, 0.0f, 0.0f);  // 手に持つ武器の位置オフセット
	//m_HoldItemArray.back().m_nOffsetRot = VECTOR3(0.0f, 180.0f, -90.0f);  // 手に持つ武器の角度オフセット

	// キャラクター　－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
	m_pMeshArray.push_back(new CFbxMesh(GameDevice()->m_pFbxMeshCtrl, _T("Data/Char/Character/character.mesh")));    // キャラクター
	m_pMeshArray.back()->LoadAnimation(_T("Data/Char/Character/character_stand.anmx"));   // 0:eAnimNum_Idle
	m_pMeshArray.back()->LoadAnimation(_T("Data/Char/Character/character_forward_start_RAXZ.anmx"), eRootAnimXZ);  // 1:eAnimNum_Walk
	m_pMeshArray.back()->LoadAnimation(_T("Data/Char/Character/character_forward_middle_RAXZ.anmx"), eRootAnimXZ); // 2:eAnimNum_Run
	m_pMeshArray.back()->LoadAnimation(_T("Data/Char/Character/character_attack.anmx"));  // 3:eAnimNum_Attack
	m_pMeshArray.back()->LoadAnimation(_T("Data/Char/Character/character_die.anmx"));     // 4:eAnimNum_Die
	m_pMeshArray.back()->m_fHeightMax = 0.01f;
	m_pMeshArray.back()->m_iMaxDevide = 16;
	m_HoldItemArray.push_back(hi);
	m_HoldItemArray.back().m_nHoldObjNo = 1;	// 手に持つ武器のオブジェ番号(透明な剣)
	m_HoldItemArray.back().m_nPosMesh = 0;		// 剣の根元位置のメッシュ番号
	m_HoldItemArray.back().m_nPosBone = 13;	// 剣の根元位置のボーン番号
	m_HoldItemArray.back().m_nOffsetPos = VECTOR3(0.2f, 0.0f, 0.0f);  // 手に持つ武器の位置オフセット
	m_HoldItemArray.back().m_nOffsetRot = VECTOR3(0.0f, 0.0f, -90.0f);  // 手に持つ武器の角度オフセット

	// Dreyar　－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－                        // -- 2022.12.20
	//m_pMeshArray.push_back(new CFbxMesh(GameDevice()->m_pFbxMeshCtrl, _T("Data/Char/Dreyar/Dreyar.mesh")));    // Dreyar
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/Dreyar/Dreyar_Idle.anmx"));    // 0:eAnimNum_Idle
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/Dreyar/Dreyar_Walking.anmx")); // 1:eAnimNum_Walk
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/Dreyar/Dreyar_Running.anmx")); // 2:eAnimNum_Run
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/Dreyar/Dreyar_Sword.anmx"));   // 3:eAnimNum_Attack
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/Dreyar/Dreyar_Dying.anmx"));   // 4:eAnimNum_Die
	//m_pMeshArray.back()->m_fHeightMax = 0.01f;
	//m_pMeshArray.back()->m_iMaxDevide = 16;
	//m_HoldItemArray.push_back(hi);
	//m_HoldItemArray.back().m_nHoldObjNo = 3;	// 手に持つ武器のオブジェ番号(ソード)
	//m_HoldItemArray.back().m_nPosMesh = 0;		// 剣の根元位置のメッシュ番号
	//m_HoldItemArray.back().m_nPosBone = 45;		// 剣の根元位置のボーン番号
	//m_HoldItemArray.back().m_nOffsetPos = VECTOR3(0.0f, 0.02f, -0.04f);  // 手に持つ武器の位置オフセット
	//m_HoldItemArray.back().m_nOffsetRot = VECTOR3(0.0f, 0.0f, -90.0f);  // 手に持つ武器の角度オフセット

	// Maria　－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－                            // -- 2022.12.20
	//m_pMeshArray.push_back(new CFbxMesh(GameDevice()->m_pFbxMeshCtrl, _T("Data/Char/Maria/Maria.mesh")));    // Maria
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/Maria/Maria_Idle.anmx"));    // 0:eAnimNum_Idle
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/Maria/Maria_Walking.anmx")); // 1:eAnimNum_Walk
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/Maria/Maria_Running.anmx")); // 2:eAnimNum_Run
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/Maria/Maria_Slash.anmx"));   // 3:eAnimNum_Attack
	//m_pMeshArray.back()->LoadAnimation(_T("Data/Char/Maria/Maria_Dying.anmx"));   // 4:eAnimNum_Die
	//m_pMeshArray.back()->m_fHeightMax = 0.01f;
	//m_pMeshArray.back()->m_iMaxDevide = 16;
	//m_HoldItemArray.push_back(hi);
	//m_HoldItemArray.back().m_nHoldObjNo = 3;	// 手に持つ武器のオブジェ番号(ソード)
	//m_HoldItemArray.back().m_nPosMesh = 0;		// 剣の根元位置のメッシュ番号
	//m_HoldItemArray.back().m_nPosBone = 43;		// 剣の根元位置のボーン番号
	//m_HoldItemArray.back().m_nOffsetPos = VECTOR3(0.0f, 0.01f, -0.02f);  // 手に持つ武器の位置オフセット
	//m_HoldItemArray.back().m_nOffsetRot = VECTOR3(0.0f, 0.0f, -90.0f);  // 手に持つ武器の角度オフセット

	// -------------------------------------------------------------------------
	m_pObjArray.push_back(new CPcObj(this));	// m_pObjArrayにオブジェクトを登録する

	// -------------------------------------------------------------------------  // -- 2022.2.16
	// ＰＣプロシージャの初期化処理
}

// ---------------------------------------------------------------------------
//
// ＰＣプロシージャのデストラクタ
//
// ---------------------------------------------------------------------------
CPcProc::~CPcProc()
{
	;
}


//============================================================================
//
// ＰＣオブジェクトのコンストラクタ
//
//  引数
//  CBaseProc* pProc		： 親プロシージャへのポインタ
//
// ---------------------------------------------------------------------------
CPcObj::CPcObj(CBaseProc* pProc) : CBaseObj(pProc)
{
	m_fLocalRotY = 0.0f;                   // -- 2018.8.4
	m_bSide = true;                        // -- 2018.8.4

	// バウンディングボックスの設定
	m_pBBox = new CBBox(GameDevice()->m_pShader, VECTOR3(-0.25f, -0.05f, -0.25f), VECTOR3(0.25f, 2.0f, 0.25f));
	m_pBBox->m_mWorld = m_mWorld;                            // -- 2021.1.11

	hp.max = PC_MAXHP;
	hp.current = hp.max;

	m_nAtc = PC_ATC;

	// -----------------------------------------------------------------------  // -- 2022.2.16
	// ＰＣオブジェクトの初期化処理
	m_bActive = true;

	m_AnimStatus.playAnim = true;
	m_AnimStatus.SetNum(eAnimNum_Idle);
	m_AnimStatus.animFrame = 0;

	// 前進移動速度倍率(初期値は１倍)
	m_nMoveFwdPower = 1;

	m_seLaser = new CXAudioSource(_T("Data/Sound/Lazer.wav"), 10);

	m_jumpY = 0.0f;
	m_jumpVelocity = 0.0f;

	m_vRotY = 0.0f;

	m_remain = REMAIN_MAX;
	m_status = Status::eNormal;
	m_recoverTimer = 1.0f;
}
// ---------------------------------------------------------------------------
//
// ＰＣオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CPcObj::~CPcObj() 
{
	SAFE_DELETE(m_seLaser);
}

// ---------------------------------------------------------------------------
//
// ＰＣオブジェクトのローカル軸マトリックスを得る関数
//
//  m_mWorldの位置情報とm_fLocalRotYの角度情報を元に
//  ローカル軸マトリックスを返す
//
// ---------------------------------------------------------------------------
MATRIX4X4 CPcObj::GetLocalMatrix()
{
	MATRIX4X4 mPos = GetPositionMatrix(m_mWorld);
	MATRIX4X4 mRotY;

	mRotY = XMMatrixRotationY(XMConvertToRadians(m_fLocalRotY));
	mRotY = mRotY * mPos;
	return mRotY;
}

VECTOR3 CPcObj::Position()
{
	return GetPositionVector(m_mWorld);
}

VECTOR3 CPcObj::Rotation()
{
	return VECTOR3(0, m_fLocalRotY, 0);
}


//-----------------------------------------------------------------------------
// ＰＣオブジェクトの更新
//
//　キーボードでＰＣを動かす
//　ＰＣのアニメーション、ジャンプ、自然落下
//　ワールド座標返還、マップとの接触判定
//　ＰＣの攻撃処理を行う
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CPcObj::Update()
{

	// 一つ前の位置を保存
	m_mWorldOld = m_mWorld;

	// 各状態に応じた処理
	switch (m_status) {
	case Status::eFlash:  // ＰＣがダメージから復帰したときの処理
	case Status::eNormal: // ＰＣが通常状態のときの処理
		UpdateNormal();  // ＰＣオブジェクトの更新 通常状態（NORMAL）
		break;
	case Status::eDead:	// ＰＣが死亡状態のときの処理
		UpdateDead();  // ＰＣオブジェクトの更新 死亡状態（DEAD）
		break;

	}

	// マップコリジョンと自然落下
	m_jumpY += m_jumpVelocity;	// 自然落下
	m_jumpVelocity += GAMEGRAVITY * Time::DeltaTime();
	if (m_jumpVelocity <= 0.0f) {
		if (ObjectManager::FindGameObject<CMapProc>()->isCollisionMoveGravity(&m_mWorld, m_mWorldOld) != 3)  // マップコリジョン
		{
			m_jumpY = 0.0f;  // 自然落下の停止
			m_jumpVelocity = 0.0f;
		}
	}
	// バウンディングボックス
	m_pBBox->m_mWorld = m_mWorld;

}

void CPcObj::Draw()
{
	//レンダリング
	GetMesh()->Render(m_AnimStatus, m_mWorld);

	//m_pBBox->m_mWorld = GetMesh()->GetFrameMatrices(m_AnimStatus, m_mWorld, 0);  // ルートボーン
	//m_pBBox->Render( GameDevice()->m_mView, GameDevice()->m_mProj, GameDevice()->m_vLightDir, GameDevice()->m_vEyePt);

	// 手に持つ武器やアイテムの表示をする     // -- 2021.2.4
	if (GetHoldItem().m_nHoldObjNo != 0) // 手に持つ武器やアイテムがあるとき
	{
		MATRIX4X4 mHold;
		mHold = GetMesh()->GetFrameMatrices(m_AnimStatus, m_mWorld, GetHoldItem().m_nPosBone, GetHoldItem().m_nPosMesh);  // 手の位置のボーンマトリックス
		ObjectManager::FindGameObject<CWeaponHoldProc>()->Disp(mHold, GetHoldItem()); // アイテム表示
	}

	// ＰＣの頭上の名前表示
	VECTOR3 vPcPos = GetPositionVector(m_mWorld);
	vPcPos.y += 2.0f;
	GameDevice()->m_pFont->Draw3D(vPcPos, GameDevice()->m_mView, GameDevice()->m_mProj, GameDevice()->m_vEyePt, _T("プレイキャラクター"), VECTOR2(0.5f, 0.2f), RGB(0, 0, 255), 1.0f, _T("HGP創英角ﾎﾟｯﾌﾟ体"));
}

void CPcObj::OnCollision(CBaseObj* other)
{
	switch (m_status) { // この時はダメージを受けない
	case Status::eDead:
	case Status::eFlash:
		return;
	}
	if (other == nullptr && dynamic_cast<CWeaponLaserObj*>(other) == nullptr)
		return;

	MATRIX4X4 mTemp;

	ObjectManager::FindGameObject<CBackForeProc>()->GetSprite()->DrawRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, RGB(255, 255, 255), 1.0f); // 画面を一瞬白くフラッシュ

	mTemp = XMMatrixTranslation(0, 0, -0.25f);	// バックする
	m_mWorld = mTemp * m_mWorld;

	hp.current -= other->GetAtc();	// 攻撃を受けたダメージ
	if (hp.current <= 0)		// HPが０なので死亡へ
	{
		hp.current = 0;
		m_status = Status::eDead;		// HPが０なので死亡へ
		m_AnimStatus.SetNum(eAnimNum_Die);	// 死亡モーションにする
		m_recoverTimer = DEADTIME;		// 死亡時間の設定
	}
	else {
		m_recoverTimer = FLASHTIME;   // 無敵状態の時間
		m_status = Status::eFlash;     // ダメージからの復帰処理を行う
	}
}

//-----------------------------------------------------------------------------   // -- 2019.3.5
// ＰＣオブジェクトの更新 通常状態（NORMAL）
//
//　キーボードでＰＣを動かす
//　ＰＣのアニメーション、ジャンプ、自然落下
//　ワールド座標返還、マップとの接触判定
//　ＰＣの攻撃処理を行う
//
//
//   引数　なし
//
//-----------------------------------------------------------------------------
void	CPcObj::UpdateNormal()
{

	if (m_status == Status::eFlash) // ＰＣがダメージから復帰したときの処理
	{
		m_recoverTimer -= Time::DeltaTime();
		if (m_recoverTimer <= 0) m_status = Status::eNormal;
		//GameDevice()->m_pRenderBufProc->SetDrawFont(300, 10, _T("** 無敵状態 **"), 16, RGB(255, 0, 0));
	}
	UpdateNormalMove();      // ＰＣオブジェクトの移動処理
	UpdateNormalAttack();    // ＰＣオブジェクトの攻撃処理

}
//-----------------------------------------------------------------------------   // -- 2019.3.5
// ＰＣオブジェクトの移動処理
//
//　キーボード／マウスでＰＣを動かす
//　ＰＣのアニメーション、ジャンプ、自然落下
//　ワールド座標返還、マップとの接触判定
//
//
//   引数　なし
//
//-----------------------------------------------------------------------------
void	CPcObj::UpdateNormalMove()
{
	CDirectInput* pDI = GameDevice()->m_pDI;

	MATRIX4X4 mYaw;  // ＰＣＹ軸回転マトリックス
	MATRIX4X4 mPos;  // ＰＣ移動マトリックス
	bool	  bKeyPush = false;// キーを押したかどうかのチェック

	// キーボード、マウス、ジョイスティック操作

	// ジャンプ   ------------------------------------------------
	if ((pDI->CheckKey(KD_TRG, DIK_J) || pDI->CheckJoy(KD_TRG, DIJ_Z)) && m_jumpY == 0.0f) {
		bKeyPush = true;
		m_jumpY = 0.0f;
		m_jumpVelocity = JUMP_POWER;
	}
	// 自然落下の初期値
	mPos = XMMatrixTranslation(0.0f, m_jumpY, 0.0f);

	// サイドモードの切り替え  -------------------------------------
	// (左右移動の時、方向を変えるかどうか)
	if (pDI->CheckKey(KD_TRG, DIK_Y))
	{
		if (m_bSide)
		{
			m_bSide = false;   // 左右移動の時、方向を変える
		}
		else {
			m_bSide = true;    // 左右移動の時、方向を変えない
		}
	}

	// ローカル軸（Ｙ軸）の回転処理  --------------------------------
	if (pDI->CheckKey(KD_DAT, DIK_RIGHT) || pDI->CheckMouse(KD_DAT, DIM_RIGHT) || pDI->CheckJoy(KD_DAT, DIJ_R)) //	→キー
	{
		m_fLocalRotY += ROT_LOWSPEED * Time::DeltaTime();
		if (m_fLocalRotY >= 360.0f) m_fLocalRotY -= 360.0f;
	}

	if (pDI->CheckKey(KD_DAT, DIK_LEFT) || pDI->CheckMouse(KD_DAT, DIM_LEFT) || pDI->CheckJoy(KD_DAT, DIJ_L)) //	←キー
	{
		m_fLocalRotY -= ROT_LOWSPEED * Time::DeltaTime();
		if (m_fLocalRotY < 0.0f) m_fLocalRotY += 360.0f;
	}

	// ＰＣの移動処理  ---------------------------------------------
	// 前進処理
	if (pDI->CheckKey(KD_DAT, DIK_W) || pDI->CheckKey(KD_DAT, DIK_UP) || pDI->CheckJoy(KD_DAT, DIJ_UP)) //	↑キー
	{
		bKeyPush = true;
		mPos = UpdateNormalMoveKeystate(DIK_W);
	}
	// 後退処理
	if (pDI->CheckKey(KD_DAT, DIK_S) || pDI->CheckKey(KD_DAT, DIK_DOWN) || pDI->CheckJoy(KD_DAT, DIJ_DOWN)) //↓キー
	{
		bKeyPush = true;
		mPos = UpdateNormalMoveKeystate(DIK_S);
	}
	// 右移動処理
	if (pDI->CheckKey(KD_DAT, DIK_D) || pDI->CheckJoy(KD_DAT, DIJ_RIGHT))//→キー
	{
		bKeyPush = true;
		mPos = UpdateNormalMoveKeystate(DIK_D);
	}
	// 左移動処理
	if (pDI->CheckKey(KD_DAT, DIK_A) || pDI->CheckJoy(KD_DAT, DIJ_LEFT))//←キー
	{
		bKeyPush = true;
		mPos = UpdateNormalMoveKeystate(DIK_A);
	}

	// キーを押していないときで、歩きか走りのときアイドルに戻す    // -- 2023.1.31
	if (!bKeyPush && (m_AnimStatus.animNum == eAnimNum_Walk || m_AnimStatus.animNum == eAnimNum_Run))
	{
		m_AnimStatus.SetNum(eAnimNum_Idle);
	}

	// ローカル軸を基準として、ＰＣを移動させるワールドマトリックスを設定
	mYaw = XMMatrixRotationY(XMConvertToRadians(m_vRotY));
	m_mWorld = mPos * mYaw * GetLocalMatrix();

}

//-----------------------------------------------------------------------------   // -- 2021.1.10
// ＰＣオブジェクトの移動処理　キー操作毎の各種移動処理
//
//   引数　DWORD Key キー種別　DirectInputのキーコード
//
//   戻り値  移動マトリックス
//-----------------------------------------------------------------------------
MATRIX4X4 CPcObj::UpdateNormalMoveKeystate(DWORD DIKey)
{
	MATRIX4X4 mPos = XMMatrixTranslation(0.0f, m_jumpY, 0.0f);

	if (m_AnimStatus.animNum == eAnimNum_Idle) m_AnimStatus.SetNum(eAnimNum_Walk);  // アイドル中のときは、歩行アニメーションにする
	if (m_AnimStatus.isEnd(eAnimNum_Walk))  m_AnimStatus.SetNum(eAnimNum_Run);  // 歩行アニメーションが終わったとき、走りのアニメーションにする

	if (m_bSide && DIKey != DIK_W)   // サイドモードで前進以外のとき
	{
		switch (DIKey)
		{
		case DIK_S:    // 後退
			// 方向を変えずに後退
			mPos = XMMatrixTranslation(0.0f, m_jumpY, -MOVE_BASESPEED*Time::DeltaTime());
			break;
		case DIK_D:    // 右
			// 方向を変えずに右移動
			mPos = XMMatrixTranslation(MOVE_BASESPEED * Time::DeltaTime(), m_jumpY, 0.0f);
			break;
		case DIK_A:    // 左
			// 方向を変えずに左移動
			mPos = XMMatrixTranslation(-MOVE_BASESPEED * Time::DeltaTime(), m_jumpY, 0.0f);
			break;
		}
	}
	else {
		// 進行方向に回転してから前進

		// ルートボーンアニメーションを行うかどうかルートアニメーションタイプを確認する
		if (GetMesh()->GetRootAnimType(m_AnimStatus.animNum) == eRootAnimNone)
		{
			// ルートボーンアニメーションを行わず固定の前進移動値
			mPos = XMMatrixTranslation(0.0f, m_jumpY, MOVE_BASESPEED * Time::DeltaTime() * m_nMoveFwdPower);  // 基本速度に前進速度倍率を掛ける // -- 2022.12.20
		}
		else {
			// ルートボーンアニメーションでの前進移動値
			MATRIX4X4 mWork = GetMesh()->GetRootAnimUpMatrices(m_AnimStatus);      // -- 2022.12.20
			mWork._43 *= m_nMoveFwdPower;    // Ｚ方向に前進速度倍率を掛ける       // -- 2022.12.20
			mPos = XMMatrixTranslation(0.0f, m_jumpY, 0.0f) * mWork;
		}

		// 進行方向に回転する処理
		// ・回転角度はm_vRotYにある。-180～180度
		// ・１回の回転速度はPC_ROTSPEED
		if (m_vRotY > 180.0f)  m_vRotY -= 360.0f;
		if (m_vRotY < -180.0f) m_vRotY += 360.0f;

		float fAngle = 0.0f;  // 目標回転角度
		switch (DIKey)
		{
		case DIK_W:    // 前進
			fAngle = 0.0f;
			break;
		case DIK_S:    // 後退
			if (m_vRotY >= 0)  // 最小回転になるように方向を合わせる
			{
				fAngle = 180.0f;
			}
			else {
				fAngle = -180.0f;
			}
			break;
		case DIK_D:    // 右
			fAngle = 90.0f;
			if (m_vRotY == -180.0f) m_vRotY = 180.0f;  // 最小回転になるように方向を合わせる
			break;
		case DIK_A:    // 左
			fAngle = -90.0f;
			if (m_vRotY == 180.0f) m_vRotY = -180.0f;  // 最小回転になるように方向を合わせる
			break;
		}

		if (m_vRotY > fAngle)  // 左回転
		{
			m_vRotY -= ROT_SPEED * Time::DeltaTime();
			if (m_vRotY < fAngle) m_vRotY = fAngle;
		}
		if (m_vRotY < fAngle)  // 右回転
		{
			m_vRotY += ROT_SPEED * Time::DeltaTime();
			if (m_vRotY > fAngle) m_vRotY = fAngle;
		}

	}
	return mPos;
}

//-----------------------------------------------------------------------------   // -- 2019.3.5
// ＰＣオブジェクトの攻撃処理
//
//　キーボード／マウスでＰＣの攻撃処理を行う
//
//
//   引数　なし
//
//-----------------------------------------------------------------------------
void	CPcObj::UpdateNormalAttack()
{
	CDirectInput* pDI = GameDevice()->m_pDI;

	// ------------------------------------------------------------- 
	// レーザーの発射
	if (pDI->CheckKey(KD_DAT, DIK_X) || pDI->CheckJoy(KD_DAT, DIJ_A) || pDI->CheckMouse(KD_DAT, DIM_LBUTTON)) // Xキー
	{
		MATRIX4X4 mGun, mHold;
		VECTOR3 vOffset;

		// 手に持つアイテムから銃の情報を得て発射する
		mHold = GetMesh()->GetFrameMatrices(m_AnimStatus, m_mWorld, GetHoldItem().m_nPosBone, GetHoldItem().m_nPosMesh);  // 銃の根元位置のボーンマトリックス
		CWeaponHoldProc* pHold = ObjectManager::FindGameObject<CWeaponHoldProc>();
		pHold->GetInfo(mHold, GetHoldItem(), mGun, vOffset); // ボーンマトリックスを指定して手に持つアイテムの情報を得る
		if (pHold->GetKind(GetHoldItem()) != 2)   // 銃を持っていないとき
		{
			vOffset.z = 0.8f;   // とりあえず前方に0.8
		}
		CWeaponLaserProc* pLaser = ObjectManager::FindGameObject<CWeaponLaserProc>();
		pLaser->Start(mGun, vOffset, m_mWorld, CWeaponLaserObj::OwnerID::PC); // レーザー発射
		m_seLaser->Play(); // レーザー発射効果音

	}

}

//-----------------------------------------------------------------------------   // -- 2019.3.5
// ＰＣオブジェクトの更新 死亡状態（DEAD）
//
//　死亡状態のときの処理
//
//
//   引数　なし
//
//-----------------------------------------------------------------------------
void	CPcObj::UpdateDead()
{
	ObjectManager::FindGameObject<CBackForeProc>()->GetSprite()->DrawRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, RGB(255, 0, 0), 0.5f); // 画面を赤くする

	if (m_AnimStatus.isEnd(eAnimNum_Die))  // 死亡モーションが終わったとき
	{
		m_AnimStatus.playAnim = false;	// 一旦、アニメーションを止める
		m_AnimStatus.animFrame = m_AnimStatus.endFrame - 1; // フレームエンドの一つ手前にする
	}
	m_recoverTimer -= Time::DeltaTime();
	if (m_recoverTimer <= 0) // 死亡時間が終わったとき
	{
		m_remain--;
		if (m_remain <= 0)
		{
			m_AnimStatus.playAnim = true;	// アニメーションを復活させる
			SceneManager::ChangeScene("TitleScene");
//			GameDevice()->m_dwGameStatus = GAMEOVER;	// ゲームオーバーへ
		}
		else {
			// ゲームオーバーでないとき
			m_AnimStatus.SetNum(eAnimNum_Idle);	// アニメーションをアイドル状態に戻す
			m_AnimStatus.playAnim = true;	// アニメーションを復活させる
			hp.current = hp.max;
			m_status = Status::eFlash;     // 死亡からの復帰処理
			m_recoverTimer = DEADFLASHTIME;   // 無敵状態の時間
		}
	}
}

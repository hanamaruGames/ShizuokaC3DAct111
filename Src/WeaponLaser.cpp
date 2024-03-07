//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１１　　　　　　                 ver 3.2        2023.1.31
//
//		武器・レーザーの処理
//															WeaponLaser.cpp
//=============================================================================
#include  "WeaponLaser.h"
#include  "Map.h"
#include  "Playchar.h"
#include  "Effect.h"


// ---------------------------------------------------------------------------
//
// 武器・レーザープロシージャのコンストラクタ
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CWeaponLaserProc::CWeaponLaserProc()
{
	// レーザーメッシュの設定
	m_pMeshArray.push_back(new CFbxMesh(GameDevice()->m_pFbxMeshCtrl, _T("Data/Item/Laser2.mesh")));   // -- 2022.12.20

	for (int i = 0; i < WEAPON_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponLaserObj(this));	// m_pObjArrayに武器・レーザーオブジェクトを生成する
	}
}
// ---------------------------------------------------------------------------
//
// 武器・レーザープロシージャのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponLaserProc::~CWeaponLaserProc()
{
	;
}
// ---------------------------------------------------------------------------
//
// 武器・レーザープロシージャの発射
//
//  MATRIX4X4  mGun         ：銃の位置マトリックス
//  VECTOR3 vOffset      ：位置の微調整
//  MATRIX4X4  mOwnerWorld  ：発射するキャラのマトリックス
//  DWORD       dwOwner      ：武器を発射したキャラ区分（PC:PC(省略値)　ENM:敵）
//
// ---------------------------------------------------------------------------
bool CWeaponLaserProc::Start(MATRIX4X4 mGun, VECTOR3 vOffset, MATRIX4X4 mOwnerWorld, DWORD dwOwner)
{
	// レーザーの発射
	MATRIX4X4 mLay, mOwnerRot, mOffset;

	mLay = GetPositionMatrix(mGun);               // 銃の位置(回転を取り除く)
	mOwnerRot = GetRotateMatrix(mOwnerWorld);     // 発射するキャラの回転マトリックスのみ(位置を取り除く)にする
	mLay = mOwnerRot * mLay;                      // 銃の位置から、キャラの方向で発射するマトリックスを作る
	mOffset = XMMatrixTranslation(vOffset.x, vOffset.y, vOffset.z);	// 位置の微調整
	mLay = mOffset * mLay;

	for (int i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(mLay, dwOwner);	       // 武器・レーザーオブジェクトの発射
			return true;
		}
	}

	return FALSE;
}

// ---------------------------------------------------------------------------
//
// 武器・レーザープロシージャの発射
//
//  MATRIX4X4  mWorld       ：レーザーの発射位置のマトリックス
//  DWORD       dwOwner      ：武器を発射したキャラ区分（PC:PC(省略値)　ENM:敵）
//
// ---------------------------------------------------------------------------
bool CWeaponLaserProc::Start(MATRIX4X4 mWorld, DWORD dwOwner)
{
	for (int i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(mWorld, dwOwner);	       // 武器・レーザーオブジェクトの発射
			return true;
		}
	}
	return FALSE;
}

// ---------------------------------------------------------------------------
//
// 武器・レーザーオブジェクトのコンストラクタ
//
// ---------------------------------------------------------------------------
CWeaponLaserObj::CWeaponLaserObj(CBaseProc* pProc) : CBaseObj(pProc)
{
	m_vTarget = VECTOR3(0, 0, 0);		// ターゲット
	m_vStart = VECTOR3(0, 0, 0);		// 発射位置
	m_vEnd = VECTOR3(0, 0, 0);			// 最終到達点

	m_bActive = FALSE;
	m_dwStatus = NORMAL;

	m_nAtc = WEAPON_ATC;

	m_dwOwner = 0;


}
// ---------------------------------------------------------------------------
//
// 武器・レーザーオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponLaserObj::~CWeaponLaserObj()
{
	;
}

// ---------------------------------------------------------------------------
//
// 武器・レーザーオブジェクトの発射
//
//     MATRIX4X4 mStartWorld     レーザーの発射位置のマトリックス
//     DWORD      dwOwner         武器を発射したキャラ区分（PC:PC(省略値)　ENM:敵）
//
//     戻り値　　なし
// ---------------------------------------------------------------------------
bool CWeaponLaserObj::Start(MATRIX4X4 mStartWorld, DWORD dwOwner)
{

	if (m_bActive) return FALSE;

	m_bActive = true;
	m_mWorldOld = mStartWorld;  // レーザーの発射位置のマトリックスを保存しておく

	MATRIX4X4 mScale;
	mScale = XMMatrixScaling(1.0f, 1.0f, WEAPON_LENGTH);  // レーザーの長さの拡大マトリックスを作成する
	m_mWorld = mScale * mStartWorld;                // レーザーの発射位置からレーザーの長さに拡大したマトリックスを作成する

	MATRIX4X4 mTrans;
	mTrans = XMMatrixTranslation(0.0f, 0.0f, WEAPON_LENGTH);
	mTrans = mTrans * mStartWorld;     // レーザーの到達点のマトリックスを作成する

	m_vStart = GetPositionVector(m_mWorldOld);	// レーザーの発射位置
	m_vEnd = GetPositionVector(mTrans);			// レーザーの到達位置

	m_dwOwner = dwOwner;

	return true;
}

// ---------------------------------------------------------------------------
//
// 武器・レーザーオブジェクトの更新
//
//     引数　　　なし
//     戻り値　　なし
// ---------------------------------------------------------------------------
void CWeaponLaserObj::Update()
{

	if (m_bActive)
	{
		CPcProc* pPc = ObjectManager::FindGameObject<CPcProc>();
		// 敵やＰＣとのあたり判定
		if ((m_dwOwner != PC && pPc->Hitcheck(this, m_vEnd, m_vStart)))
		{
			ObjectManager::FindGameObject<CEffectParticleProc>()->Start(m_vHitPos, m_vHitNormal);	// パーティクルの発生
			//GameDevice()->m_pEffectProc->m_pEffectBillProc->Start(m_vHitPos);	// 爆発ビルボードの発生
			GameDevice()->m_pSeDead->Play();// 爆発効果音

		}
		else {
			// マップとのあたり判定
			VECTOR3 vHit, vNormal;
			if (ObjectManager::FindGameObject<CMapProc>()->Hitcheck(m_vEnd, m_vStart, &vHit, &vNormal))
			{
				ObjectManager::FindGameObject<CEffectParticleProc>()->Start(vHit, vNormal);	// パーティクルの発生
				//GameDevice()->m_pEffectProc->m_pEffectBillProc->Start(vHit);	// 爆発ビルボードの発生
				GameDevice()->m_pSeDead->Play();// 爆発効果音
			}
		}

		// レンダリング
		Render();

	}

	m_bActive = FALSE;	// １回ですぐ消す

}

// ---------------------------------------------------------------------------
//
// 武器・レーザーオブジェクトのレンダリング
//
//   陰影をつけないレンダリング　光の方向が(0,0,0)
//
//     引数　　　なし
//     戻り値　　なし
// ---------------------------------------------------------------------------
void CWeaponLaserObj::Render()
{

	// 加算合成色のブレンディングを設定
	UINT mask = 0xffffffff;
	GameDevice()->m_pD3D->m_pDeviceContext->OMSetBlendState(GameDevice()->m_pD3D->m_pBlendStateAdd, nullptr, mask);
	GetMesh()->Render(m_mWorld, GameDevice()->m_mView, GameDevice()->m_mProj, VECTOR3(0, 0, 0), GameDevice()->m_vEyePt);        // -- 2022.2.16

	// 通常のブレンディングを設定
	GameDevice()->m_pD3D->m_pDeviceContext->OMSetBlendState(GameDevice()->m_pD3D->m_pBlendStateTrapen, nullptr, mask);

}

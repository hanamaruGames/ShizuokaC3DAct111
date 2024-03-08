//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１１                             ver 3.2        2023.1.31
// 
//		  マップを作成しロードする処理
//																MapLoadMap.cpp
//=============================================================================
#pragma once
#include  "BaseProc.h"
#include  "Map.h"
#include  "Playchar.h"
#include  "Weapon.h"
#include  "Effect.h"

//----------------------------------------------------------------------------- // -- 2023.1.31
//
// マップをロードする関数
//
// ・作成したマップは必ずこの関数に登録し、
// 　この関数から呼び出されなければならない
//
// 引数   int mapno : ロードするマップの番号
// 戻り値 bool  true:マップ有り   false:マップなし
//
//-----------------------------------------------------------------------------
bool CMapProc::LoadMap(int mapno)
{
	switch (mapno)
	{
	case  1:			// マップＮＯ１
		MakeMap1();
		break;


	default:
		// 該当番号のマップ無し
		return false;
	}

	m_dwMapNo = mapno;    // マップＮＯの設定
	m_bActive = true;     // マップ表示
	return true;
}
//-----------------------------------------------------------------------------
//
// マップ１の作成処理
//
// map50Field1
//
//-----------------------------------------------------------------------------
void CMapProc::MakeMap1()
{
	// vector初期化用の構造体
	const STAGEMAP      sm;
	const NAVIGATIONMAP nv;

	// 全マップの削除 -----------------------------------------------
	DestroyAll();

	// 全ての効果の非表示化 
	ObjectManager::FindGameObject<CEffectProc>()->SetNonActive();

	CPcProc* pPc = ObjectManager::FindGameObject<CPcProc>();

	// ＰＣを(0,0,-20)の位置に置く -------------------------------------
	pPc->GetPcObjPtr()->SetWorld(XMMatrixTranslation(0.0f, 0.05f, -20.0f));
	pPc->GetPcObjPtr()->SetWorldOld(pPc->GetPcObjPtr()->GetWorld());
	pPc->GetPcObjPtr()->SetLocalRotY(0.0f);  // ローカル軸(Y軸)を0度にする

	// ステージマップの設定・コリジョンマップの設定 -----------------------------------------
	m_pColMesh = new CCollision(GameDevice()->m_pFbxMeshCtrl);     // コリジョンマップの生成

	// マップメッシュの設定[0]
	m_StageMap.push_back(sm);
	//m_StageMap.back().m_pMesh = new CFbxMesh(GameDevice()->m_pFbxMeshCtrl, _T("Data/Map/MapClsc/map40.mesh"));
	m_StageMap.back().m_pMesh = new CFbxMesh(GameDevice()->m_pFbxMeshCtrl, _T("Data/Map/MapTkr/map50Field1.mesh"));       // -- 2022.2.16
	m_StageMap.back().m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	//m_pColMesh->AddFbxLoad(_T("Data/Map/MapClsc/map40_CHK.mesh"), m_StageMap.back().m_mWorld); // マップメッシュコリジョンの設定
	m_pColMesh->AddFbxLoad(_T("Data/Map/MapTkr/map50Field1.mesh"), m_StageMap.back().m_mWorld); // マップメッシュコリジョンの設定

	// ドアメッシュの設定[1]
	m_StageMap.push_back(sm);
	m_StageMap.back().m_pMesh = new CFbxMesh(GameDevice()->m_pFbxMeshCtrl, _T("Data/Map/MapItem/DOOR1.mesh"));
	m_StageMap.back().m_mWorld = XMMatrixTranslation(-80.0f, 0.0f, 80.0f);
	m_pColMesh->AddFbxLoad(_T("Data/Map/MapItem/DOOR1.mesh"), m_StageMap.back().m_mWorld); // ドアメッシュコリジョンの設定

	// 水面の設定[2]
	m_StageMap.push_back(sm);
	m_StageMap.back().m_pWave = new CWave(GameDevice()->m_pShader, 50, 70, _T("Data/Map/MapItem/WaterNM.png"));             // 水面の大きさ（メートル単位）とノーマルマップテクスチャの指定
	m_StageMap.back().m_mWorld = XMMatrixTranslation(38.0f, -0.5f, -5.0f);      // 水面を置く位置（作成した水面の左端、手前端の位置を指定する）
	m_StageMap.back().m_nMaterialFlag = 3;   // 水面のディスプレイスメントマッピング

	// 溶岩流の設定[2]
	//m_StageMap.push_back(sm);
	//m_StageMap.back().m_pWave = new CWave(GameDevice()->m_pShader, 50,70, _T("Data/Map/MapItem/lava03_NM.png"), _T("Data/Map/MapItem/lava03.png"), _T("Data/Map/MapItem/lava03.png"));      // 溶岩流の大きさ（メートル単位）と各種テクスチャの指定
	//m_StageMap.back().m_pWave->m_fMaxDistance = 40.0f;
	//m_StageMap.back().m_pWave->m_fMinDistance = 20.0f;
	//m_StageMap.back().m_pWave->m_fWaveHeight = 0.15f;
	//m_StageMap.back().m_mWorld = XMMatrixTranslation(38.0f, -0.5f, -5.0f);      // 溶岩流を置く位置（作成した溶岩流の左端、手前端の位置を指定する）
	//m_StageMap.back().m_nMaterialFlag = 3;   // 溶岩流のディスプレイスメントマッピング

	// 空用  -----------------------------------------------------------
	// 空マップの設定[0]
	m_SkyMap.push_back(sm);
	m_SkyMap.back().m_pMesh = new CFbxMesh(GameDevice()->m_pFbxMeshCtrl, _T("Data/Map/Sky/sky2.mesh"));
	m_SkyMap.back().m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 0.0f);

	// ナビゲーションマップの設定 --------------------------------------
	// ナビマップの設定[0]
	m_NavMap.push_back(nv);
	m_NavMap.back().vMin = VECTOR3(-30.0f, 0.05f, 10.0f);
	m_NavMap.back().vMax = VECTOR3(30.0f, 0.05f, 30.0f);

}


//=============================================================================
// 
// 		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１１                             ver 3.2       2022.11.14
//		  マップの処理
//																	Map.cpp
//=============================================================================
#include  "BaseProc.h"
#include  "Map.h"
#include  "Playchar.h"
#include  "Weapon.h"


//=============================================================================
//
// マッププロシージャのコンストラクタ
//
//-----------------------------------------------------------------------------
CMapProc::CMapProc()
{
	// クラス全体のクリヤー
	// (vectorクラスは初期化不要)
//	GameDevice() = pGMain;
	m_dwMapNo = 0;
	m_bActive = false;
	m_pColMesh   = nullptr;					// コリジョンメッシュへのポインタ
	m_nEvtIdx = 0;							// -- 2021.2.4

}

//-----------------------------------------------------------------------------
//
// マッププロシージャのデストラクタ
//
//-----------------------------------------------------------------------------
CMapProc::~CMapProc()
{
	DestroyAll();
}

//-----------------------------------------------------------------------------
//
// マップの削除
//
//-----------------------------------------------------------------------------
void CMapProc::DestroyAll()
{
	m_dwMapNo = 0;
	m_bActive = false;
	m_nEvtIdx = 0;							// -- 2021.2.4

	// メッシュのデリート
	for(DWORD i = 0; i<m_SkyMap.size(); i++)
	{
		SAFE_DELETE(m_SkyMap[i].m_pMesh);
		SAFE_DELETE(m_SkyMap[i].m_pWave);    // 使用していないが念のため削除
	}
	for(DWORD i = 0; i<m_StageMap.size(); i++)
	{
		SAFE_DELETE(m_StageMap[i].m_pMesh);
		SAFE_DELETE(m_StageMap[i].m_pWave);
	}
	for (DWORD i = 0; i<m_MoveMap.size(); i++)
	{
		SAFE_DELETE(m_MoveMap[i].m_pMesh);
		SAFE_DELETE(m_MoveMap[i].m_pColMesh);
	}
	for (DWORD i = 0; i < m_EventMap.size(); i++)   // -- 2021.2.4
	{
		SAFE_DELETE(m_EventMap[i].m_pBBox);
	}
	SAFE_DELETE(m_pColMesh);

	// vectorの削除
	m_SkyMap.clear();					// 空のマップ  配列削除
	m_SkyMap.shrink_to_fit();			// 空のマップ  不要メモリ解放
	m_StageMap.clear();					// ステージのマップ  配列削除
	m_StageMap.shrink_to_fit();			// ステージのマップ 不要メモリ解放
	m_MoveMap.clear();					// 移動マップ  配列削除
	m_MoveMap.shrink_to_fit();			// 移動マップ 不要メモリ解放
	m_NavMap.clear();					// ナビゲーションマップ配列削除
	m_NavMap.shrink_to_fit();			// ナビゲーションマップ不要メモリ解放
	m_EventMap.clear();					// イベントマップ配列削除
	m_EventMap.shrink_to_fit();			// イベントマップ不要メモリ解放

}

//-----------------------------------------------------------------------------
// マッププロシージャのあたり判定
//
// ・相手（主にＰＣの武器）とコリジョンマップとのあたり判定
//
//   CBaseObj*    pObj      相手のオブジェクト
//   VECTOR3* pHit		接触点の座標（出力）
//   VECTOR3* pNormal	接触点の法線ベクトル（出力）wwwwwwwwwwwwwwwwwwwww

//
//   戻り値　bool
//           true:ヒットしたとき       false：ヒットしていないとき
//
//-----------------------------------------------------------------------------
bool   CMapProc::Hitcheck(CBaseObj* pObj, VECTOR3* pHit, VECTOR3* pNormal)
{
	return  Hitcheck(GetPositionVector(pObj->GetWorld()), GetPositionVector(pObj->GetWorldOld()), pHit, pNormal);
}
//-----------------------------------------------------------------------------
// マッププロシージャのあたり判定
//
// ・相手（主にＰＣの武器）とコリジョンマップとのあたり判定
//
//   VECTOR3 vNow       相手の現在位置
//   VECTOR3 vOld       相手の一つ前の位置
//   VECTOR3* vHit		接触点の座標（出力）
//   VECTOR3* vNormal	接触点の法線ベクトル（出力）
//
//   戻り値　bool
//           true:ヒットしたとき       false：ヒットしていないとき
//
//-----------------------------------------------------------------------------
bool   CMapProc::Hitcheck(VECTOR3 vNow, VECTOR3 vOld, VECTOR3* pHit, VECTOR3* pNormal)
{
	bool  bRet;
	for (int i = 0; i < m_MoveMap.size(); i++)
	{
		if (m_MoveMap[i].m_pColMesh && m_MoveMap[i].m_bActive)
		{
			bRet = m_MoveMap[i].m_pColMesh->isCollisionLay(vNow, vOld, *pHit, *pNormal);
			if (bRet) return bRet;
		}
	}

	if (m_pColMesh && m_pColMesh->isCollisionLay(vNow, vOld, *pHit, *pNormal))
	{
		return true;
	}
	else {
		return false;
	}

}
//-----------------------------------------------------------------------------  // -- 2020.12.11
// マッププロシージャのあたり判定
//
// ・相手（主にＰＣの武器）の球とコリジョンマップとのあたり判定
//
//   VECTOR3 vNow       相手の現在のオブジェクト中心位置
//   VECTOR3 vOld       相手の一つ前のオブジェクト中心位置
//   float& fRadius     球の半径
//   VECTOR3 &vHit      接触時のオブジェクト中心位置の座標（出力）
//   VECTOR3 &vNormal   接触点の法線ベクトル（出力）
//
//   戻り値　bool
//           true:ヒットしたとき       false：ヒットしていないとき
//
//-----------------------------------------------------------------------------
bool   CMapProc::Hitcheck(VECTOR3 vNow, VECTOR3 vOld, float fRadius, VECTOR3* pHit, VECTOR3* pNormal)
{
	bool  bRet;
	for (int i = 0; i < m_MoveMap.size(); i++)
	{
		if (m_MoveMap[i].m_pColMesh && m_MoveMap[i].m_bActive)
		{
			bRet = m_MoveMap[i].m_pColMesh->isCollisionSphere(vNow, vOld, fRadius, *pHit, *pNormal);
			if (bRet) return bRet;
		}
	}

	if (m_pColMesh && m_pColMesh->isCollisionSphere(vNow, vOld, fRadius, *pHit, *pNormal))
	{
		return true;
	}
	else {
		return false;
	}

}

//-----------------------------------------------------------------------------
// オブジェクトのレイとメッシュ接触判定用配列との接触判定とスリスリ動かす制御
//	高低差と重力を考慮した、接触判定を行う									2022.11.14
//  
//  MATRIX4X4* pWorld     オブジェクトの現在のマトリックス(in,out)
//  MATRIX4X4  mWorldOld  オブジェクトの一つ前のマトリックス		
//  float fRadius          オブジェクトの半径（省略値は0.2）
//  
//  戻り値　int
//		エラー		= -1
//		面上を移動	= 1
//		着地		= 2
//		落下中		= 3
//-----------------------------------------------------------------------------
int  CMapProc::isCollisionMoveGravity(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld, float fRadius)
{
	VECTOR3 vHit, vNormal;
	return isCollisionMoveGravity(pWorld, mWorldOld, vHit, vNormal, fRadius);
}
//-----------------------------------------------------------------------------
// オブジェクトのレイとメッシュ接触判定用配列との接触判定とスリスリ動かす制御
//	高低差と重力を考慮した、接触判定を行う									2022.11.14
//  
//  MATRIX4X4* pWorld     オブジェクトの現在のマトリックス(in,out)
//  MATRIX4X4  mWorldOld  オブジェクトの一つ前のマトリックス		
//  VECTOR3    &vHit	  接触点の座標（出力）
//  VECTOR3    &vNormal	  接触点の法線ベクトル（出力）
//  float fRadius         オブジェクトの半径（省略値は0.2）
//  
//  戻り値　int
//		エラー		= -1
//		面上を移動	= 1
//		着地		= 2
//		落下中		= 3
//-----------------------------------------------------------------------------
int  CMapProc::isCollisionMoveGravity(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld, VECTOR3& vHit, VECTOR3& vNormal, float fRadius)
{
	int  nRet = 0, nRetMove = 0;  // -- 2019.9.3

	// 移動マップとの接触判定と移動
	for (int i = 0; i < m_MoveMap.size(); i++)
	{
		if (m_MoveMap[i].m_pColMesh && m_MoveMap[i].m_bActive)
		{
			nRetMove = m_MoveMap[i].m_pColMesh->isCollisionMoveGravity(*pWorld, mWorldOld, vHit, vNormal, fRadius);  // -- 2022.11.14
			if (nRetMove == 1 || nRetMove == 2) break;   // 移動マップと接触したとき
		}
	}

	// 通常のマップとの接触判定と移動
	if (m_pColMesh)
	{
		nRet = m_pColMesh->isCollisionMoveGravity(*pWorld, mWorldOld, vHit, vNormal, fRadius);  // -- 2022.11.14
	}

	if (nRetMove == 1 || nRetMove == 2)  // 移動マップと接触していたとき   // -- 2019.9.3
	{
		return nRetMove;
	}
	else {
		return nRet;
	}
}
//-----------------------------------------------------------------------------
// オブジェクトのレイとメッシュ接触判定用配列との接触判定とスリスリ動かす制御
//	重力を考えず、接触判定を行う											2022.11.14
//  
//  MATRIX4X4* pWorld     オブジェクトの現在のマトリックス(in,out)
//  MATRIX4X4  mWorldOld  オブジェクトの一つ前のマトリックス		
//  float fRadius          オブジェクトの半径（省略値は0.2）
//  
//  戻り値　int
//		接触したとき　		１
//		接触していないとき	０
//-----------------------------------------------------------------------------
int CMapProc::isCollisionMove(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld, float fRadius)
{
	VECTOR3 vHit, vNormal;
	return isCollisionMove(pWorld, mWorldOld, vHit, vNormal, fRadius);
}
//-----------------------------------------------------------------------------
// オブジェクトのレイとメッシュ接触判定用配列との接触判定とスリスリ動かす制御
//	重力を考えず、接触判定を行う											2022.11.14
//  
//  MATRIX4X4* pWorld     オブジェクトの現在のマトリックス(in,out)
//  MATRIX4X4  mWorldOld  オブジェクトの一つ前のマトリックス		
//  VECTOR3    &vHit	  接触点の座標（出力）
//  VECTOR3    &vNormal	  接触点の法線ベクトル（出力）
//  float fRadius          オブジェクトの半径（省略値は0.2）
//  
//  戻り値　int
//		接触したとき　		１
//		接触していないとき	０
//-----------------------------------------------------------------------------
int CMapProc::isCollisionMove(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld, VECTOR3& vHit, VECTOR3& vNormal, float fRadius)
{
	int  nRet = 0, nRetMove = 0;  // -- 2019.9.3

	// 移動マップとの接触判定と移動
	for (int i = 0; i < m_MoveMap.size(); i++)
	{
		if (m_MoveMap[i].m_pColMesh && m_MoveMap[i].m_bActive)
		{
			nRetMove = m_MoveMap[i].m_pColMesh->isCollisionMove(*pWorld, mWorldOld, vHit, vNormal, fRadius);  // -- 2022.11.14
			if (nRetMove == 1) break;
		}
	}

	// 通常のマップとの接触判定と移動
	if (m_pColMesh)
	{
		nRet = m_pColMesh->isCollisionMove(*pWorld, mWorldOld, vHit, vNormal, fRadius);  // -- 2022.11.14
	}

	if (nRetMove == 1)  // 移動マップと接触していたとき     // -- 2019.9.3
	{
		return nRetMove;
	}
	else {
		return nRet;
	}
}


//-----------------------------------------------------------------------------
//
// マッププロシージャの更新
//
//-----------------------------------------------------------------------------
void CMapProc::Update()
{
	CDirectInput* pDI = GameDevice()->m_pDI;
	const float MAP_SKYROTSPEED = MAP_SKYROTSPEED_X1000 / 1000.0f;

	// イベントの更新処理                         // -- 2021.2.4
	UpdateEvent();

	// 空の更新　　カメラを中心とした位置に置き、Ｙ軸回転させる
	if (m_SkyMap.size() > 0)
	{
		MATRIX4X4 mRot;
		mRot = XMMatrixRotationY(XMConvertToRadians(MAP_SKYROTSPEED));
		mRot = mRot * GetRotateMatrix(m_SkyMap[0].m_mWorld);
		m_SkyMap[0].m_mWorld = XMMatrixTranslation(GameDevice()->m_vEyePt.x, GameDevice()->m_vEyePt.y, GameDevice()->m_vEyePt.z);
		m_SkyMap[0].m_mWorld = mRot * m_SkyMap[0].m_mWorld;
	}

	// 移動マップ更新処理
	UpdateMoveMap();

}
//-----------------------------------------------------------------------------   // -- 2021.2.4
//
// イベントのセット
//
// 引数
//   VECTOR3 vMin         : バウンディングボックス最小値
//   VECTOR3 vMax         : バウンディングボックス最大値
//   MATRIX4X4 mWorld     : バウンディングボックスのワールドマトリックス
//   EVENTKIND nEvtKind   : イベントの種類 eEvtChangeMap:マップ移動, eEvtMoveMap:移動マップの制御
//   int nEvtNo           : イベント番号 eEvtChangeMapのときは移動先のマップ番号、eEvtMoveMapのときは移動マップの要素番号
//   int m_nEvtOpe1       : eEvtMoveMapのみ指定する。1:Activeの指定。2:移動ON・OFFの指定
//   int m_nEvtOpe2       : eEvtMoveMapのみ指定する。0:OFF　1:ON
//   int nEvtKeyPush      : 0:バウンディングボックスに接触するとイベント発動、 1:バウンディングボックスに接触して、ENTERキーを押すとイベント発動(省略値0)
//
// 戻り値
//   int セットしたイベント配列の要素番号
//
//-----------------------------------------------------------------------------
int  CMapProc::SetEvent(VECTOR3 vMin, VECTOR3 vMax, MATRIX4X4 mWorld, EVENTKIND nEvtKind, int nEvtNo, int nEvtOpe1, int nEvtOpe2, int nEvtKeyPush)
{
	const EVENTMAP      em;

	m_EventMap.push_back(em);

	// バウンディングボックスの設定
	m_EventMap[m_nEvtIdx].m_pBBox = new CBBox(GameDevice()->m_pShader, vMin, vMax);
	m_EventMap[m_nEvtIdx].m_pBBox->m_mWorld = mWorld;

	// 各項目の設定
	m_EventMap[m_nEvtIdx].m_nEvtCycle = 0;
	m_EventMap[m_nEvtIdx].m_nEvtKind = nEvtKind;
	m_EventMap[m_nEvtIdx].m_nEvtNo = nEvtNo;
	m_EventMap[m_nEvtIdx].m_nEvtOpe1 = nEvtOpe1;
	m_EventMap[m_nEvtIdx].m_nEvtOpe2 = nEvtOpe2;
	m_EventMap[m_nEvtIdx].m_nEvtKeyPush = nEvtKeyPush;

	m_nEvtIdx++;
	return  m_nEvtIdx - 1;
}

//-----------------------------------------------------------------------------   // -- 2021.2.4
//
// イベントの更新・実行
//
//-----------------------------------------------------------------------------
void  CMapProc::UpdateEvent()
{
	VECTOR3 vHit, vNrm;
	CPcProc* pPc = ObjectManager::FindGameObject<CPcProc>();

	for (int i = 0; i < m_EventMap.size(); i++)
	{
		// PCのバウンディングボックスに接触しているかの判定
		if (m_EventMap[i].m_pBBox && m_EventMap[i].m_pBBox->OBBCollisionDetection(pPc->Obj()->GetBBox(), &vHit, &vNrm))
		{
			// PCのバウンディングボックスに接触しているとき
			if (m_EventMap[i].m_nEvtCycle == 0)  // イベントサイクルが０のとき(まだ接触していなかったとき)
			{
				if (m_EventMap[i].m_nEvtKeyPush == 1 && !(GameDevice()->m_pDI->CheckKey(KD_DAT, DIK_RETURN) || GameDevice()->m_pDI->CheckJoy(KD_DAT, DIJ_A)))  // Enterキープッシュが必要なとき
				{
					VECTOR3 vPc = GetPositionVector(pPc->Obj()->GetWorld());
					vPc.y += 2.0f;
					// PCの頭上に、Enterキープッシュが行われていない事の表示をする
					GameDevice()->m_pFont->Draw3D(vPc, GameDevice()->m_mView, GameDevice()->m_mProj, GameDevice()->m_vEyePt, _T("Push Enter Key!"), VECTOR2(0.8f, 0.2f), RGB(255, 0, 0), 1.0f, _T("HGP創英角ｺﾞｼｯｸUB"));
				}
				else {
					// イベント実行
					RunEvent(m_EventMap[i]);
				}
			}
		}
		else {
			// PCのバウンディングボックスに接触していないとき
			if (m_EventMap[i].m_nEvtCycle == 2)  // イベントサイクルが２のとき(既に接触していて終了待ちのとき)
			{
				m_EventMap[i].m_nEvtCycle = 0;  // イベントサイクルを０に戻す
			}
		}
	}
}

//-----------------------------------------------------------------------------   // -- 2021.2.4
//
// イベントの実行
//
// 引数  EVENTMAP& EventMap:イベントマップ
//
//-----------------------------------------------------------------------------
void  CMapProc::RunEvent(EVENTMAP& EventMap)
{
	int i;

	if (EventMap.m_nEvtKind == eEvtChangeMap)   // マップ移動のとき
	{
		if (!LoadMap(EventMap.m_nEvtNo))
		{
			MessageBox(nullptr, _T("■□■ CMapProc::RunEvent() ■□■"), _T("■□■ マップ移動番号のマップがありません ■□■"), MB_OK);
		}
	}
	else if (EventMap.m_nEvtKind == eEvtMoveMap)  // 移動マップの制御のとき
	{
		i = EventMap.m_nEvtNo;
		if (EventMap.m_nEvtOpe1 == 1)   // 表示有無に関する処理
		{
			m_MoveMap[i].m_bActive = EventMap.m_nEvtOpe2;
		}
		else if (EventMap.m_nEvtOpe1 == 2)   // 移動に関する処理
		{
			m_MoveMap[i].m_bMoveOn = EventMap.m_nEvtOpe2;           // -- 2022.11.14
		}
		EventMap.m_nEvtCycle = 2;  // イベントサイクルを２にする   // -- 2021.4.4
	}
}

//-----------------------------------------------------------------------------// -- 2022.11.14
//
// 移動マップの更新
//
// 移動マップの平行移動や回転の更新を行う
// 限界値（上端下端等）に達したときは、反転（change）を行う
// 反転（change）をしたときは、m_nChangeFlagに１が返る
// ループをしないときは反転のタイミングで停止する 
//
//-----------------------------------------------------------------------------
void CMapProc::UpdateMoveMap()
{
	for (DWORD i = 0; i < m_MoveMap.size(); i++)
	{
		if (m_MoveMap[i].m_pColMesh && m_MoveMap[i].m_bActive && m_MoveMap[i].m_bMoveOn)   // 移動マップの更新処理  // -- 2022.11.14
		{
			m_MoveMap[i].m_pColMesh->m_mWorldOld = m_MoveMap[i].m_pColMesh->m_mWorld;   // ワールドマトリックス一つ前
			m_MoveMap[i].m_nChangeFlag = 0;      // チェンジフラグのリセット
			if (m_MoveMap[i].m_nMoveFlag == 1)   // 平行移動の処理
			{
				MATRIX4X4 mOffset;
				m_MoveMap[i].m_pColMesh->SetWorldMatrix(XMMatrixTranslationFromVector(m_MoveMap[i].m_vUp) * m_MoveMap[i].m_pColMesh->m_mWorld);  // 移動増分の処理   // -- 2022.11.14
				mOffset = m_MoveMap[i].m_pColMesh->m_mWorld * XMMatrixInverse(nullptr, m_MoveMap[i].m_pColMesh->m_mWorldBase);  // 移動後位置を原点を基準とした位置にする   // -- 2022.11.14
				if (m_MoveMap[i].m_vUp.x != 0)  // 左右に動かす
				{
					if (GetPositionVector(mOffset).x < m_MoveMap[i].m_vMinOffset.x ||  // 左右に動かすため右端左端で反転
						GetPositionVector(mOffset).x > m_MoveMap[i].m_vMaxOffset.x)
					{
						m_MoveMap[i].m_vUp.x *= -1;
						m_MoveMap[i].m_nChangeFlag = 1;
					}
				}
				if (m_MoveMap[i].m_vUp.y != 0)  // 上下に動かす
				{
					if (GetPositionVector(mOffset).y < m_MoveMap[i].m_vMinOffset.y ||  // 上下に動かすため上端下端で反転
						GetPositionVector(mOffset).y > m_MoveMap[i].m_vMaxOffset.y)
					{
						m_MoveMap[i].m_vUp.y *= -1;
						m_MoveMap[i].m_nChangeFlag = 1;
					}
				}
				if (m_MoveMap[i].m_vUp.z != 0)  // 前後に動かす
				{
					if (GetPositionVector(mOffset).z < m_MoveMap[i].m_vMinOffset.z ||  // 前後に動かすため前端後端で反転
						GetPositionVector(mOffset).z > m_MoveMap[i].m_vMaxOffset.z)
					{
						m_MoveMap[i].m_vUp.z *= -1;
						m_MoveMap[i].m_nChangeFlag = 1;
					}
				}
			}
			else if (m_MoveMap[i].m_nMoveFlag == 2) {   // 回転の処理
				MATRIX4X4 mOffset;
				if (m_MoveMap[i].m_vUp.x != 0)  // Ｘ回転
				{
					m_MoveMap[i].m_pColMesh->SetWorldMatrix(XMMatrixRotationX(XMConvertToRadians(m_MoveMap[i].m_vUp.x)) * m_MoveMap[i].m_pColMesh->m_mWorld);  // 移動増分の処理   // -- 2022.11.14
					mOffset = m_MoveMap[i].m_pColMesh->m_mWorld * XMMatrixInverse(nullptr, m_MoveMap[i].m_pColMesh->m_mWorldBase);  // 回転後角度を原点を基準とした角度にする   // -- 2022.11.14

					if (GetRotateVector3(mOffset).x < m_MoveMap[i].m_vMinOffset.x ||  // Ｘ回転するため端で反転
						GetRotateVector3(mOffset).x > m_MoveMap[i].m_vMaxOffset.x)
					{
						m_MoveMap[i].m_vUp.x *= -1;  // Ｘ回転するため端で反転
						m_MoveMap[i].m_nChangeFlag = 1;
					}
				}
				else if (m_MoveMap[i].m_vUp.y != 0)  // Ｙ回転
				{
					m_MoveMap[i].m_pColMesh->SetWorldMatrix(XMMatrixRotationY(XMConvertToRadians(m_MoveMap[i].m_vUp.y)) * m_MoveMap[i].m_pColMesh->m_mWorld);  // 移動増分の処理   // -- 2022.11.14
					mOffset = m_MoveMap[i].m_pColMesh->m_mWorld * XMMatrixInverse(nullptr, m_MoveMap[i].m_pColMesh->m_mWorldBase);  // 回転後角度を原点を基準とした角度にする   // -- 2022.11.14

					if (GetRotateVector3(mOffset).y < m_MoveMap[i].m_vMinOffset.y ||  // Ｙ回転するため端で反転
						GetRotateVector3(mOffset).y > m_MoveMap[i].m_vMaxOffset.y)
					{
						m_MoveMap[i].m_vUp.y *= -1;  // Ｙ回転するため端で反転
						m_MoveMap[i].m_nChangeFlag = 1;
					}
				}
				else if (m_MoveMap[i].m_vUp.z != 0)  // Ｚ回転
				{
					m_MoveMap[i].m_pColMesh->SetWorldMatrix(XMMatrixRotationZ(XMConvertToRadians(m_MoveMap[i].m_vUp.z)) * m_MoveMap[i].m_pColMesh->m_mWorld);  // 移動増分の処理   // -- 2022.11.14
					mOffset = m_MoveMap[i].m_pColMesh->m_mWorld * XMMatrixInverse(nullptr, m_MoveMap[i].m_pColMesh->m_mWorldBase);  // 回転後角度を原点を基準とした角度にする   // -- 2022.11.14

					if (GetRotateVector3(mOffset).z < m_MoveMap[i].m_vMinOffset.z ||  // Ｚ回転するため端で反転
						GetRotateVector3(mOffset).z > m_MoveMap[i].m_vMaxOffset.z)
					{
						m_MoveMap[i].m_vUp.z *= -1;  // Ｚ回転するため端で反転
						m_MoveMap[i].m_nChangeFlag = 1;
					}
				}
			}
			else if (m_MoveMap[i].m_nMoveFlag == 3) {   // 拡大縮小の処理      // -- 2019.12.30
				MATRIX4X4 mOffset;
				m_MoveMap[i].m_pColMesh->SetWorldMatrix(XMMatrixScaling(m_MoveMap[i].m_vUp.x, m_MoveMap[i].m_vUp.y, m_MoveMap[i].m_vUp.z)
					* m_MoveMap[i].m_pColMesh->m_mWorld);  // 拡大縮小増分の処理
				mOffset = m_MoveMap[i].m_pColMesh->m_mWorld * XMMatrixInverse(nullptr, m_MoveMap[i].m_pColMesh->m_mWorldBase);  // 拡大縮小を原点を基準とした拡大縮小にする   // -- 2022.11.14

				VECTOR3 vScaleNow = GetScaleVector(mOffset);     // 現在の拡大率を得る
				if (vScaleNow.x < m_MoveMap[i].m_vMinOffset.x ||      // 規定の拡大縮小に達したか
					vScaleNow.x > m_MoveMap[i].m_vMaxOffset.x ||
					vScaleNow.y < m_MoveMap[i].m_vMinOffset.y ||
					vScaleNow.y > m_MoveMap[i].m_vMaxOffset.y ||
					vScaleNow.z < m_MoveMap[i].m_vMinOffset.z ||
					vScaleNow.z > m_MoveMap[i].m_vMaxOffset.z)
				{
					m_MoveMap[i].m_vUp.x = 1 / avoidZero(m_MoveMap[i].m_vUp.x);  // 拡大縮小の反転
					m_MoveMap[i].m_vUp.y = 1 / avoidZero(m_MoveMap[i].m_vUp.y);  // 拡大縮小の反転
					m_MoveMap[i].m_vUp.z = 1 / avoidZero(m_MoveMap[i].m_vUp.z);  // 拡大縮小の反転
					m_MoveMap[i].m_nChangeFlag = 1;
				}
			}
			// ループをしないときの停止判断。反転のタイミングで停止する
			if (m_MoveMap[i].m_nLoop == 0 && m_MoveMap[i].m_nChangeFlag == 1)
			{
				m_MoveMap[i].m_bMoveOn = false;    // 移動しない    // -- 2022.11.14
			}
		}
	}
}

//============================================================================
//  マッププロシージャのレンダリング
// 
//    引数　　なし
// 
//    戻り値　なし
//============================================================================
void  CMapProc::Draw()
{
	if (m_bActive) {

		// 空のレンダリング
		if (m_SkyMap.size() > 0)
		{
			// 空のレンダリング   陰影をつけないレンダリング 
			// Zバッファを無効化
			GameDevice()->m_pD3D->SetZBuffer(false);
			m_SkyMap[0].m_pMesh->Render(m_SkyMap[0].m_mWorld, GameDevice()->m_mView, GameDevice()->m_mProj, VECTOR3(0, 0, 0), GameDevice()->m_vEyePt);  // 陰影をつけないレンダリング 
			// Zバッファを有効化
			GameDevice()->m_pD3D->SetZBuffer(true);
		}

		// マップレンダリング
		for (DWORD i = 0; i < m_StageMap.size(); i++)
		{
			if (m_StageMap[i].m_nMaterialFlag == 0)  // 通常のブレンドステート
			{
				if (m_StageMap[i].m_pMesh)
					m_StageMap[i].m_pMesh->Render(m_StageMap[i].m_mWorld, GameDevice()->m_mView, GameDevice()->m_mProj, GameDevice()->m_vLightDir, GameDevice()->m_vEyePt);

			}
			else if (m_StageMap[i].m_nMaterialFlag == 2)  // ディスプレースメントマッピング   // -- 2020.12.15
			{
				if (m_StageMap[i].m_pMesh)
					m_StageMap[i].m_pMesh->RenderDisplace(m_StageMap[i].m_mWorld, GameDevice()->m_mView, GameDevice()->m_mProj, GameDevice()->m_vLightDir, GameDevice()->m_vEyePt);

			}
			else if (m_StageMap[i].m_nMaterialFlag == 3) // 波のレンダリング
			{
				if (m_StageMap[i].m_pWave)
					m_StageMap[i].m_pWave->Render(m_StageMap[i].m_mWorld, GameDevice()->m_mView, GameDevice()->m_mProj, GameDevice()->m_vLightDir, GameDevice()->m_vEyePt);
			}
		}

		// 移動マップレンダリング     * このプログラムでは使用していない
		for (DWORD i = 0; i < m_MoveMap.size(); i++)
		{
			if (m_MoveMap[i].m_pMesh && m_MoveMap[i].m_bActive)
				m_MoveMap[i].m_pMesh->Render(m_MoveMap[i].m_pColMesh->m_mWorld, GameDevice()->m_mView, GameDevice()->m_mProj, GameDevice()->m_vLightDir, GameDevice()->m_vEyePt);
		}

	}
}

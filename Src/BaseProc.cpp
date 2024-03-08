//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１１                             ver 3.2        2023.1.31
//
//		基本プロシージャ・基本オブジェクトクラス処理
//																BaseProc.cpp
//=============================================================================
#include "BaseProc.h"
#include "BBox.h"
#include "FbxMesh.h"
#include "FbxMeshAnim.h"
#include "GameMain.h"

CBaseProc::CBaseProc()
{
	m_pMeshArray.clear();
	m_pObjArray.clear();
}

//------------------------------------------------------------------------
//
//	基本プロシージャクラスのデストラクタ	
//  （全てのプロシージャやオブジェクトを読み下して削除する）
//
//  引数　なし
//
//------------------------------------------------------------------------
CBaseProc::~CBaseProc()
{
	// メッシュポインタ配列の削除                     // -- 2022.12.20
	for (DWORD i = 0; i < m_pMeshArray.size(); i++)
	{
		SAFE_DELETE(m_pMeshArray[i]);
	}
	// オブジェクトポインタ配列の削除
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		SAFE_DELETE(m_pObjArray[i]);
	}
}
void CBaseProc::Draw()
{
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		m_pObjArray[i]->Draw();          // オブジェクトの更新処理
	}


}
//------------------------------------------------------------------------
//
//	基本プロシージャクラスの全体更新処理	
//  （全てのプロシージャやオブジェクトを読み下して更新処理をする）
//
//  引数　なし
//
//------------------------------------------------------------------------
void CBaseProc::UpdateAll()
{

//	Update();                              // プロシージャの更新処理

	// オブジェクトポインタ配列の更新
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		m_pObjArray[i]->Update();          // オブジェクトの更新処理
	}
}
//============================================================================   // -- 2022.12.20
//   
//	メッシュポインタのアドレスを返す
//   
//	引数　	int idx  メッシュポインタ配列の添字
//
//	戻り値  メッシュポインタのアドレス
//============================================================================
CFbxMesh* CBaseProc::GetMesh(int idx)
{
	if (idx < 0 || idx >= m_pMeshArray.size())
	{
		MessageBox(nullptr, _T("■ GetMesh( idx) ■"), _T("指定要素番号のメッシュがありません"), MB_OK);
		return nullptr;
	}
	return m_pMeshArray[idx];
}
//============================================================================   // -- 2022.12.20
//   
//	手に持つアイテムの値を返す
//   
//	引数　	int idx  手に持つアイテム配列の添字
//
//	戻り値  手に持つアイテムの値
//============================================================================
BASEHOLDITEM  CBaseProc::GetHoldItem(int idx)
{
	BASEHOLDITEM nullptrHI = {};

	if (idx < 0 || idx >= m_HoldItemArray.size())
	{
		MessageBox(nullptr, _T("■ GetHoldItem( idx) ■"), _T("指定要素番号の手に持つアイテムがありません"), MB_OK);
		return nullptrHI;
	}
	return m_HoldItemArray[idx];
}

//-----------------------------------------------------------------------------
// 基本プロシージャクラスのあたり判定(移動直線)
//
// ・全ての相手プロシージャと相手オブジェクトを読み下し
// ・自オブジェクトのバウンディングボックスと相手の移動直線とのあたり判定処理をする
//
//   CBaseObj* pOtherObj    相手のオブジェクト
//   VECTOR3 vNow       相手の現在位置
//   VECTOR3 vOld       相手の一つ前の位置
//
//   戻り値　bool
//           true:ヒットしたとき       false：ヒットしていないとき
//
//   判定結果　　
//           ヒットしたときは　　　　相手と自分のオブジェクトのm_pHitObjとm_vHitPosとm_vHitNormalに値をセット
//                                   相手と自分オブジェクトのm_dwStatusにDAMAGEを設定する
//           ヒットしていないときは　相手と自分のオブジェクトのm_pHitObjにnullptrをセット
//
//-----------------------------------------------------------------------------
bool   CBaseProc::Hitcheck(CBaseObj* pOtherObj, VECTOR3 vNow, VECTOR3 vOld)
{
	bool  bRet = false;

	// 全ての相手とのあたり判定
	for (DWORD i = 0; i < m_pObjArray.size(); i++)  // 全ての相手オブジェクト
	{
		bRet = m_pObjArray[i]->Hitcheck(pOtherObj, vNow, vOld);  // 相手オブジェクトとのあたり判定
		if (bRet) return bRet;
	}
	return bRet;
}

//-----------------------------------------------------------------------------
// 基本プロシージャクラスのあたり判定（バウンディングボックス）
//
// ・全ての相手プロシージャと相手オブジェクトを読み下し
// ・自オブジェクトのバウンディングボックスと相手の攻撃バウンディングボックスとのあたり判定
//
//   CBaseObj* pOtherObj      相手のオブジェクト
//   CBBox*    pAttackBBox    対象となるバウンディングボックス
//
//   戻り値　bool
//           true:ヒットしたとき       false：ヒットしていないとき
//
//   判定結果　　
//           ヒットしたときは　　　　相手と自分のオブジェクトのm_pHitObjとm_vHitPosとm_vHitNormalに値をセット
//                                   相手と自分のオブジェクトのm_dwStatusにDAMAGEを設定する
//           ヒットしていないときは　相手と自分のオブジェクトのm_pHitObjにnullptrをセット
//
//-----------------------------------------------------------------------------
bool   CBaseProc::Hitcheck(CBaseObj* pOtherObj, CBBox* pBBoxAtack)
{
	bool  bRet = false;

	// 全ての相手とのあたり判定
	for (DWORD i = 0; i < m_pObjArray.size(); i++)  // 全ての相手オブジェクト
	{
		bRet = m_pObjArray[i]->Hitcheck(pOtherObj, pBBoxAtack);  // 相手オブジェクトとのあたり判定
		if (bRet) return bRet;
	}

//	for (DWORD i = 0; i < m_pProcArray.size(); i++)  // 下位の相手プロシージャ
//	{
//		bRet = m_pProcArray[i]->Hitcheck(pOtherObj, pBBoxAtack);  // 相手プロシージャとのあたり判定
//		if (bRet) return bRet;
//	}

	return bRet;
}

//============================================================================
//   
//	プロシージャとオブジェクトを探索し全てのオブジェクトをノンアクティブにする
//   
//	引数　	なし
//
//	戻り値  なし
//============================================================================
void  CBaseProc::SetNonActive()
{

	// 敵のオブジェクトポインタ配列の探索
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		m_pObjArray[i]->SetActive(false);   // アクティブフラグをfalseに
	}
}


//------------------------------------------------------------------------  // -- 2022.2.16
//
//	基本オブジェクトクラスのコンストラクタ	
//
//  引数　CBaseProc* pProc   // 親のプロシージャ
//
//------------------------------------------------------------------------
CBaseObj::CBaseObj(CBaseProc* pProc)
{
	m_pProc  = pProc;					// 親のプロシージャ
	m_bActive = false;					// true:表示  false:非表示
	m_nMeshIdx = 0;						// メッシュ配列の添字           // -- 2022.12.20
	m_pBBox = nullptr;						// バウンディングボックスクラス
	m_mWorld = XMMatrixIdentity();		// ワールドマトリクス
	m_mWorldOld = XMMatrixIdentity();	// ワールドマトリクス（一つ前）
	m_pHitObj = 0;						// 当たった相手のオブジェクト
	m_vHitPos = VECTOR3(0, 0, 0);		// 当たった場所の座標
	m_vHitNormal = VECTOR3(0, 0, 0);	// 当たった場所の法線座標
	m_nAtc = 0;							// 攻撃力

	m_AnimStatus.playAnim = true;		// アニメーションを動作させる
}
//------------------------------------------------------------------------
//
//	基本オブジェクトクラスのデストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CBaseObj::~CBaseObj()
{
	SAFE_DELETE(m_pBBox);
}
//============================================================================   // -- 2022.12.20
//   
//	親プロシージャのメッシュポインタ配列[m_nMeshIdx]のアドレスを返す
//   
//	引数　	なし
//
//	戻り値  メッシュポインタのアドレス
//============================================================================
CFbxMesh* CBaseObj::GetMesh()
{
	return m_pProc->GetMesh(m_nMeshIdx);
}
//============================================================================   // -- 2022.12.20
//   
//	親プロシージャの手に持つアイテム配列[m_nMeshIdx]を返す
//   
//	引数　	なし
//
//	戻り値  手に持つアイテム
//============================================================================
BASEHOLDITEM CBaseObj::GetHoldItem()
{
	return m_pProc->GetHoldItem(m_nMeshIdx);
}


//-----------------------------------------------------------------------------
//
// 基本オブジェクトクラスのあたり判定(移動直線)
//
// ・自オブジェクトのバウンディングボックスと相手の移動直線とのあたり判定
//
//   CBaseObj* pOtherObj  相手のオブジェクト
//   VECTOR3 vNow     相手の現在位置
//   VECTOR3 vOld     相手の一つ前の位置
//
//   戻り値　bool
//           true:ヒットしたとき       false：ヒットしていないとき
//
//   判定結果　　
//           ヒットしたときは　　　　相手と敵のオブジェクトのm_pHitObjとm_vHitPosとm_vHitNormalに値をセット
//                                   敵オブジェクトのm_dwStatusにDAMAGEを設定する
//           ヒットしていないときは　相手と敵のオブジェクトのm_pHitObjにnullptrをセット
//
//-----------------------------------------------------------------------------
bool   CBaseObj::Hitcheck(CBaseObj* pOtherObj, VECTOR3 vNow, VECTOR3 vOld)
{
	bool bRet = false;
	VECTOR3 vHit = VECTOR3(0.0f, 0.0f, 0.0f), vNrm = VECTOR3(0.0f, 1.0f, 0.0f);

	// バウンディングボックスと移動直線（Lay）による判定
	if ((m_bActive && this != pOtherObj) &&
		m_pBBox->OBBCollisionLay(vNow, vOld, &vHit, &vNrm))
	{
		m_pHitObj = pOtherObj;
		pOtherObj->m_pHitObj = this;
		m_vHitPos = vHit;
		m_vHitNormal = vNrm;
		pOtherObj->m_vHitPos = vHit;
		pOtherObj->m_vHitNormal = vNrm;
		OnCollision(pOtherObj);
		pOtherObj->OnCollision(this);
		bRet = true;
	}
	return bRet;
}
//-----------------------------------------------------------------------------
//
// 基本オブジェクトクラスのあたり判定（バウンディングボックス）
//
// ・自オブジェクトのバウンディングボックスと相手のバウンディングボックスとのあたり判定
//
//   CBaseObj* pOtherObj  相手のオブジェクト
//   CBBox*      pBBoxAtack   バウンディングボックスの判定をするとき
//
//   戻り値　bool
//           true:ヒットしたとき       false：ヒットしていないとき
//
//   判定結果　　
//           ヒットしたときは　　　　相手と敵のオブジェクトのm_pHitObjとm_vHitPosとm_vHitNormalに値をセット
//                                   敵オブジェクトのm_dwStatusにDAMAGEを設定する
//           ヒットしていないときは　相手と敵のオブジェクトのm_pHitObjにnullptrをセット
//
//-----------------------------------------------------------------------------
bool   CBaseObj::Hitcheck(CBaseObj* pOtherObj, CBBox* pBBoxAtack)
{
	bool bRet = false;
	VECTOR3 vHit = VECTOR3(0.0f, 0.0f, 0.0f), vNrm = VECTOR3(0.0f, 1.0f, 0.0f);

	// バウンディングボックス同士による判定
	if ((m_bActive && this != pOtherObj) &&
		m_pBBox->OBBCollisionDetection(pBBoxAtack, &vHit, &vNrm))
	{
		m_pHitObj = pOtherObj;
		pOtherObj->m_pHitObj = this;
		m_vHitPos = vHit;
		m_vHitNormal = vNrm;
		pOtherObj->m_vHitPos = vHit;
		pOtherObj->m_vHitNormal = vNrm;
		OnCollision(pOtherObj);
		pOtherObj->OnCollision(this);
		bRet = true;
	}
	return bRet;
}

//-----------------------------------------------------------------------------  // -- 2018.8.2
// オブジェクトのmWorldと引数位置との距離を求める
//
//   引数　　：　vPos :位置
//   戻り値　：　距離
//-----------------------------------------------------------------------------
float CBaseObj::GetDistance(VECTOR3 vPos)
{
	VECTOR3 vVec;
	vVec = vPos - GetPositionVector(m_mWorld);

	return  magnitude(vVec);
}

//============================================================================
//  オブジェクト同士が重ならないようにするメンバ関数
//
//	引数　	CBaseProc* pProj　対象とする基本プロシージャ
//
//	戻り値CBaseObj* 	オブジェクトアドレス:強制移動の相手オブジェクト　nullptr:移強制動していない
//============================================================================
CBaseObj*  CBaseObj::SetKeepOffset(CBaseProc* pProc)
{
	float	fMyRadius, fOtherRadius, fAddRadius, fLen, fMvMax = 0.0f;
	VECTOR3  vMy, vOther;
	VECTOR2  vMy2, vOther2;
	MATRIX4X4	 matWk1, matWk2;
	CBaseObj     *pOtherObj, *pTargetObj = nullptr;
	CBBox		 *pOtherBBox;

	if (m_pBBox == nullptr) return nullptr;
	vMy = GetPositionVector(m_mWorld);
	vMy2.x = vMy.x;
	vMy2.y = vMy.z;

	// 自分の半径をバウンディングボックスから算出する（前と右幅の大きい方を採用）
	fMyRadius = (m_pBBox->m_vMax.x > m_pBBox->m_vMax.z) ? m_pBBox->m_vMax.x : m_pBBox->m_vMax.z;


	// オブジェクト配列の探索
	for (DWORD i = 0; i < pProc->GetObjArrayPtr().size(); i++)
	{
		pOtherObj = pProc->GetObjArrayPtr()[i];

		if (!pOtherObj->m_bActive) continue;	// 現在生きていなければ対象外
		if (pOtherObj == this) continue;	// 自分自身は対象外
		pOtherBBox = pOtherObj->m_pBBox;
		if (pOtherBBox == nullptr) continue;	// バウンディングボックスがなければ対象外
		vOther = GetPositionVector(pOtherObj->m_mWorld);
		vOther2.x = vOther.x;
		vOther2.y = vOther.z;

		// バウンディングボックス同士の高さが一致しているか。範囲内に入っていなければ対象外
		if ((vMy.y + m_pBBox->m_vMin.y) > (vOther.y + pOtherObj->m_pBBox->m_vMax.y) ||
			(vMy.y + m_pBBox->m_vMax.y) < (vOther.y + pOtherObj->m_pBBox->m_vMin.y)) {
			continue;
		}

		// 相手の半径をバウンディングボックスから算出する（前と右幅の大きい方を採用）
		fOtherRadius = (pOtherBBox->m_vMax.x > pOtherBBox->m_vMax.z) ? pOtherBBox->m_vMax.x : pOtherBBox->m_vMax.z;

		fAddRadius = fMyRadius + fOtherRadius;
		if (fabs(vMy2.x - vOther2.x) < fAddRadius && fabs(vMy2.y - vOther2.y) < fAddRadius) {		// まず、ラフに水平方向（ＸＺ方向）で半径の範囲内に入っているか
			fLen = magnitude(vMy2 - vOther2);		// 水平方向（ＸＺ方向）で半径の距離内に入っているか
			if (fLen < fAddRadius) {
				fLen = fAddRadius - fLen;	// くい込み距離にする
				if (fLen > fMvMax) {		// 今までの中で、一番接近しているか
					fMvMax = fLen;
					pTargetObj = pOtherObj;
				}
			}
		}
	}

	if (pTargetObj) {	// 半径内に入った相手がいた場合
		vOther = GetPositionVector(pTargetObj->m_mWorld);
		vOther.y = vMy.y;
		matWk1 = GetLookatMatrix( vMy, vOther);					// 相手の方向を向かせるマトリックスを作成する
		matWk2 = XMMatrixTranslation(0.0f, 0.0f, -fMvMax);		// くい込み値だけ、Ｚ方向の反対方向に移動するマトリックスを作成する
		matWk1 = matWk2 * matWk1;								// くい込み値の反対方向に移動する
		vMy.x = 0.0f - vMy.x;
		vMy.y = 0.0f - vMy.y;
		vMy.z = 0.0f - vMy.z;
		matWk2 = XMMatrixTranslation(vMy.x, vMy.y, vMy.z);		// 自分の位置の逆数の位置
		matWk2 = m_mWorld * matWk2;								// 自分の原点位置での角度のみにする
		vMy = GetPositionVector(matWk1);						// くい込み値の反対方向に移動した位置
		matWk1 = XMMatrixTranslation(vMy.x, vMy.y, vMy.z);		// くい込み値の反対方向に移動した位置のみのマトリックス
		m_mWorld = matWk2 * matWk1;								// 自分の新しい位置と角度のワールドマトリックス
	}


	// 下位のプロシージャ配列の探索
//	if (pTargetObj == nullptr)
//	{
//		for (DWORD i = 0; i < pProc->GetProcArrayPtr().size(); i++)
//		{
//			pTargetObj = SetKeepOffset(pProc->GetProcArrayPtr()[i]);      // 下位のプロシージャの処理（再帰処理）
//			if (pTargetObj) break;
//		}
//	}

	return pTargetObj;
}



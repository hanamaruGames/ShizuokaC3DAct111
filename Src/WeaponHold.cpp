//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１１　　　　　　                 ver 3.2        2023.1.31
//
//		武器・手に持つアイテムの処理
//															WeaponHold.cpp
//=============================================================================
#include  "WeaponHold.h"

#include  "Playchar.h"
#include  "Effect.h"

//============================================================================
//
// 武器・手に持つアイテムプロシージャのコンストラクタ
//
// ・直接攻撃する武器ではなく、武器を表示したり、位置情報を返したりする
//
//   メッシュはプロシージャではなく、オブジェクトで読み込む
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CWeaponHoldProc::CWeaponHoldProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (int i = 0; i < WEAPON_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponHoldObj(this));	// m_pObjArrayにオブジェクトを生成する
		((CWeaponHoldObj*)m_pObjArray.back())->Init();   // オブジェクトの初期化
	}
}
// ---------------------------------------------------------------------------
//
// 武器・手に持つアイテムプロシージャのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponHoldProc::~CWeaponHoldProc()
{
	;
}

// ---------------------------------------------------------------------------
//
// 武器・手に持つアイテムプロシージャの情報を得る
//
//     MATRIX4X4  mHold       ：剣の位置
//     BASEHOLDITEM HoldItem  :手に持つ武器の情報
//     MATRIX4X4& mMat        :手に持つ武器のマトリックス(Out)
//     VECTOR3& vMin          :バウンディングボックスのMin(Out)
//     VECTOR3& vMax          :バウンディングボックスのMax(Out)
//
//     戻り値　　なし
// ---------------------------------------------------------------------------
void  CWeaponHoldProc::GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vMin, VECTOR3& vMax)
{
	((CWeaponHoldObj*)m_pObjArray[HoldItem.m_nHoldObjNo])->GetInfo(mHold, HoldItem, mMat, vMin, vMax);	// 武器・剣オブジェクト

	return;
}
// ---------------------------------------------------------------------------
//
// 武器・手に持つアイテムプロシージャの情報を得る
//
//     MATRIX4X4  mHold       ：剣の位置
//     BASEHOLDITEM HoldItem  :手に持つ武器の情報
//     MATRIX4X4& mMat        :手に持つ武器のマトリックス(Out)
//     VECTOR3& vOffset       :銃口までのオフセット(Out)
//
//     戻り値　　なし
// ---------------------------------------------------------------------------
void  CWeaponHoldProc::GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vOffset)
{
	((CWeaponHoldObj*)m_pObjArray[HoldItem.m_nHoldObjNo])->GetInfo(mHold, HoldItem, mMat, vOffset);	// 武器・銃オブジェクト

	return;
}

// ---------------------------------------------------------------------------
//
// 武器・手に持つアイテムプロシージャのバウンディングボックスを得る
//
//     MATRIX4X4  mHold       ：剣の位置
//     BASEHOLDITEM HoldItem  :手に持つ武器の情報
//
//     戻り値　　CBBox* バウンディングボックス
// ---------------------------------------------------------------------------
CBBox* CWeaponHoldProc::GetBBox(MATRIX4X4 mHold, BASEHOLDITEM HoldItem)
{
	return ((CWeaponHoldObj*)m_pObjArray[HoldItem.m_nHoldObjNo])->GetBBox(mHold, HoldItem);	// 武器・剣オブジェクト
}

// ---------------------------------------------------------------------------
//
// 武器・手に持つアイテムプロシージャの表示
//
//     MATRIX4X4  mHold       ：剣の位置
//     BASEHOLDITEM HoldItem  :手に持つ武器の情報
//
//     戻り値　　なし
// ---------------------------------------------------------------------------
BOOL CWeaponHoldProc::Disp(MATRIX4X4 mHold, BASEHOLDITEM HoldItem)
{

	((CWeaponHoldObj*)m_pObjArray[HoldItem.m_nHoldObjNo])->Disp(mHold, HoldItem);	// 武器・剣オブジェクト

	return TRUE;
}

// ---------------------------------------------------------------------------   // -- 2023.1.31
//
// 武器・手に持つアイテムプロシージャのオブジェクト番号を返す
//
//     BASEHOLDITEM HoldItem  :手に持つ武器の情報
//
//     戻り値　　int オブジェクト番号
// ---------------------------------------------------------------------------
int CWeaponHoldProc::GetKind(BASEHOLDITEM HoldItem)
{
	return ((CWeaponHoldObj*)m_pObjArray[HoldItem.m_nHoldObjNo])->GetKind();
}

//============================================================================
//
// 武器・手に持つアイテムオブジェクトのコンストラクタ
//
// ・直接攻撃する武器ではなく、武器を表示したり、位置情報を返したりする
//
// ---------------------------------------------------------------------------
CWeaponHoldObj::CWeaponHoldObj(CBaseProc* pProc) : CBaseObj(pProc)
{
	m_nKindNo = 0;
	m_pMesh = NULL;
	m_vOffset = VECTOR3(0.0f, 0.0f, 0.0f);   // オフセットの設定
}
//============================================================================
//
// 武器・手に持つアイテムオブジェクトの初期化
//
// ・メッシュは、プロシージャではなくオブジェクトの中に設定する
//
// ---------------------------------------------------------------------------
void CWeaponHoldObj::Init()
{

	switch (m_dwObjNo)
	{
	case 0:     // 未設定
		m_nKindNo = 0;
		m_pMesh = NULL; // オブジェクトは無し
		m_pBBox = NULL; // BBoxの設定
		m_vOffset = VECTOR3(0.0f, 0.0f, 0.0f);   // オフセットなし
		break;

	case 1:     // 透明な剣の設定
		m_nKindNo = 1;  // 1:種別　剣
		m_pMesh = NULL; // オブジェクトは無し
		m_pBBox = new CBBox(m_pGMain->m_pShader, VECTOR3(-0.15f, -0.15f, -0.15f), VECTOR3(0.15f, 1.8f, 0.15f));// BBoxの設定
		m_vOffset = VECTOR3(0.0f, 0.0f, 0.0f);   // 銃口までのオフセットの設定
		break;

	case 2:     // 剣（日本刀）メッシュの設定
		m_nKindNo = 1;  // 1:種別　剣
		m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Sword.mesh"));
		m_pBBox = new CBBox(m_pGMain->m_pShader, VECTOR3(-0.15f, 0.1f, -0.15f), VECTOR3(0.15f, 1.8f, 0.15f));// BBoxの設定
		m_vOffset = VECTOR3(0.0f, 0.0f, 0.0f);   // 銃口までのオフセットの設定
		break;

	case 3:     // 剣（ソード）メッシュの設定
		m_nKindNo = 1;  // 1:種別　剣
		//m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Sword2.mesh"));
		m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Swordm.mesh"));                   // -- 2022.12.20
		m_pBBox = new CBBox(m_pGMain->m_pShader, VECTOR3(-0.15f, 0.1f, -0.15f), VECTOR3(0.15f, 1.8f, 0.15f));// BBoxの設定
		m_vOffset = VECTOR3(0.0f, 0.0f, 0.0f);   // 銃口までのオフセットの設定
		break;

	case 4:     // 透明な銃の設定
		m_nKindNo = 2;  // 2:種別　銃
		m_pMesh = NULL; // オブジェクトは無し
		m_vOffset = VECTOR3(0.0f, 0.0f, 0.51f);   // 銃口までのオフセットの設定
		break;

	case 5:     // 銃（ライフル）メッシュの設定
		m_nKindNo = 2;  // 2:種別　銃
		m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Gun.mesh"));
		m_vOffset = VECTOR3(0.0f, 0.0f, 0.51f);   // 銃口までのオフセットの設定
		break;

	case 6:     // 銃（ピストル）メッシュの設定
		m_nKindNo = 2;  // 2:種別　銃
		m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Pistol.mesh"));
		m_vOffset = VECTOR3(0.0f, 0.07f, 0.17f);   // 銃口までのオフセットの設定
		break;

	case 7:     // 透明な盾の設定
		m_nKindNo = 1;  // 1:種別　剣
		m_pMesh = NULL; // オブジェクトは無し
		m_pBBox = new CBBox(m_pGMain->m_pShader, VECTOR3(-1.0f, -1.5f, -0.3f), VECTOR3(1.0f, 1.5f, 0.3f));// BBoxの設定
		m_vOffset = VECTOR3(0.0f, 0.0f, 0.0f);   // 銃口までのオフセットの設定
		break;

	default:
		m_nKindNo = 0;
		m_pMesh = NULL; // オブジェクトは無し
		m_pBBox = NULL; // BBoxの設定
		m_vOffset = VECTOR3(0.0f, 0.0f, 0.0f);   // オフセットなし
		break;
	}

	m_bActive = FALSE;
	m_dwStatus = NORMAL;

}
// ---------------------------------------------------------------------------
//
// 武器・手に持つアイテムオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponHoldObj::~CWeaponHoldObj()
{
	SAFE_DELETE(m_pMesh);
}

// ---------------------------------------------------------------------------
//
// 武器・手に持つアイテムオブジェクトの情報を得る
//
//     MATRIX4X4  mHold       ：剣の位置
//     BASEHOLDITEM HoldItem  :手に持つ武器の情報
//     MATRIX4X4& mMat        :手に持つ武器のマトリックス(Out)
//     VECTOR3& vMin          :バウンディングボックスのMin(Out)
//     VECTOR3& vMax          :バウンディングボックスのMax(Out)
//
//     戻り値　　なし
// ---------------------------------------------------------------------------
void  CWeaponHoldObj::GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vMin, VECTOR3& vMax)
{
	// オフセットマトリックスの計算
	MATRIX4X4 mPos = XMMatrixTranslation(HoldItem.m_nOffsetPos.x, HoldItem.m_nOffsetPos.y, HoldItem.m_nOffsetPos.z);

	MATRIX4X4 mRotX = XMMatrixRotationX(XMConvertToRadians(HoldItem.m_nOffsetRot.x));
	MATRIX4X4 mRotY = XMMatrixRotationY(XMConvertToRadians(HoldItem.m_nOffsetRot.y));
	MATRIX4X4 mRotZ = XMMatrixRotationZ(XMConvertToRadians(HoldItem.m_nOffsetRot.z));

	MATRIX4X4 mOffset = mRotY * mRotX * mRotZ;
	mOffset = mOffset * mPos;

	// 
	// ワールドマトリックスの計算
	// 
	// 但し、このときm_mWorldやm_pBBox->m_mWorldの設定は行っていない!!
	// 
	mMat = mOffset * mHold;     // 剣の位置のワールドマトリックス

	vMin = m_pBBox->m_vMin;
	vMax = m_pBBox->m_vMax;

	return;
}

// ---------------------------------------------------------------------------
//
// 武器・手に持つアイテムオブジェクトの情報を得る
//
//     MATRIX4X4  mHold       ：銃の位置
//     BASEHOLDITEM HoldItem  :手に持つ武器の情報
//     MATRIX4X4& mMat        :手に持つ武器のマトリックス(Out)
//     VECTOR3& vOffset       :銃口までのオフセット(Out)
//
//     戻り値　　なし
// ---------------------------------------------------------------------------
void  CWeaponHoldObj::GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vOffset)
{
	// オフセットマトリックスの計算
	MATRIX4X4 mPos = XMMatrixTranslation(HoldItem.m_nOffsetPos.x, HoldItem.m_nOffsetPos.y, HoldItem.m_nOffsetPos.z);

	MATRIX4X4 mRotX = XMMatrixRotationX(XMConvertToRadians(HoldItem.m_nOffsetRot.x));
	MATRIX4X4 mRotY = XMMatrixRotationY(XMConvertToRadians(HoldItem.m_nOffsetRot.y));
	MATRIX4X4 mRotZ = XMMatrixRotationZ(XMConvertToRadians(HoldItem.m_nOffsetRot.z));

	MATRIX4X4 mOffset = mRotY * mRotX * mRotZ;
	mOffset = mOffset * mPos;

	// ワールドマトリックスの計算
	// 
	// 但し、このときm_mWorldの設定は行っていない!!
	// 
	mMat = mOffset * mHold;     // 銃の位置のワールドマトリックス

	vOffset = m_vOffset;

	return;
}

// ---------------------------------------------------------------------------
//
// 武器・手に持つアイテムオブジェクトのバウンディングボックスを得る
//
//     MATRIX4X4  mHold       ：剣の位置
//     BASEHOLDITEM HoldItem  :手に持つ武器の情報
//
//     戻り値　　CBBox* バウンディングボックス
// ---------------------------------------------------------------------------
CBBox* CWeaponHoldObj::GetBBox(MATRIX4X4 mHold, BASEHOLDITEM HoldItem)
{

	// オフセットマトリックスの計算
	MATRIX4X4 mPos = XMMatrixTranslation(HoldItem.m_nOffsetPos.x, HoldItem.m_nOffsetPos.y, HoldItem.m_nOffsetPos.z);

	MATRIX4X4 mRotX = XMMatrixRotationX(XMConvertToRadians(HoldItem.m_nOffsetRot.x));
	MATRIX4X4 mRotY = XMMatrixRotationY(XMConvertToRadians(HoldItem.m_nOffsetRot.y));
	MATRIX4X4 mRotZ = XMMatrixRotationZ(XMConvertToRadians(HoldItem.m_nOffsetRot.z));

	MATRIX4X4 mOffset = mRotY * mRotX * mRotZ;
	mOffset = mOffset * mPos;

	// ワールドマトリックスの計算
	// 
	// 但し、このときm_mWorldとm_pBBox->m_mWorldの設定を行っている!!
	// 
	m_mWorld = mOffset * mHold;     // 剣の位置のワールドマトリックス
	m_pBBox->m_mWorld = m_mWorld;   // バウンディングボックスのワールドマトリックスをセット

	return m_pBBox;

}


// ---------------------------------------------------------------------------
//
// 武器・手に持つアイテムオブジェクトの描画
//
//     MATRIX4X4  mHold        ：アイテムの位置
//     VECTOR3    vPos         :位置のオフセット
//     VECTOR3    vRot         :角度のオフセット
//
//     戻り値　　なし
// ---------------------------------------------------------------------------
BOOL CWeaponHoldObj::Disp(MATRIX4X4 mHold, BASEHOLDITEM HoldItem)
{
	m_bActive = TRUE;  // スタート時に表示開始

	// オフセットマトリックスの計算
	MATRIX4X4 mPos = XMMatrixTranslation(HoldItem.m_nOffsetPos.x, HoldItem.m_nOffsetPos.y, HoldItem.m_nOffsetPos.z);

	MATRIX4X4 mRotX = XMMatrixRotationX(XMConvertToRadians(HoldItem.m_nOffsetRot.x));
	MATRIX4X4 mRotY = XMMatrixRotationY(XMConvertToRadians(HoldItem.m_nOffsetRot.y));
	MATRIX4X4 mRotZ = XMMatrixRotationZ(XMConvertToRadians(HoldItem.m_nOffsetRot.z));

	MATRIX4X4 mOffset = mRotY * mRotX * mRotZ;
	mOffset = mOffset * mPos;

	// ワールドマトリックスの計算
	m_mWorld = mOffset * mHold;     // 剣の位置のワールドマトリックス
	if (m_pBBox) m_pBBox->m_mWorld = m_mWorld;   // バウンディングボックスのワールドマトリックスをセット

	// レンダリング
	Render();

	m_bActive = FALSE;  // １回処理したら、消す

	return TRUE;
}

// ---------------------------------------------------------------------------
//
// 武器・手に持つアイテムオブジェクトの更新
//
//     引数　　　なし
//     戻り値　　なし
// ---------------------------------------------------------------------------
void CWeaponHoldObj::Update()
{
	;
}
// ---------------------------------------------------------------------------
//
// 武器・手に持つアイテムオブジェクトの描画
//
//     引数　　　なし
//     戻り値　　なし
// ---------------------------------------------------------------------------
void CWeaponHoldObj::Render()
{

	// 手に持つアイテムのレンダリング
	if (m_pMesh) m_pMesh->Render(m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);

	// バウンディングボックスレンダリング
	//if (m_pBBox) m_pBBox->Render(m_pGMain->m_mView, m_pGMain->m_mProj, VECTOR3(0, 0, 0), m_pGMain->m_vEyePt);
}

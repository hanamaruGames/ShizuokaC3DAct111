//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１１                             ver 3.2        2023.1.31
//		マップ　ヘッダファイル											Map.h
//=============================================================================
#pragma once
#include "GameMain.h"


// ゲームの中で使用する重力の加速度   // -- 2023.1.31
#define  GAMEGRAVITY  (0.5f * GRAVITY * 0.00005f)

// --------------------------------------------------------------------
//
// ステージマップ
//
// --------------------------------------------------------------------
struct STAGEMAP
{
	CFbxMesh* m_pMesh;			// スタティックメッシュへのポインタ
	CWave* m_pWave;			// 波のメッシュへのポインタ
	MATRIX4X4				m_mWorld;			// メッシュのワールドマトリックス
	int						m_nMaterialFlag;	// マテリアルフラグ　0:通常　1:透明色　2:ディスプレイスメントマッピング 3:波

	STAGEMAP()    // コンストラクタ
	{
		Init();
	}
	~STAGEMAP()    // デストラクタ
	{
		// この中でメッシュのDELETEをしてはならない
	}
	void Init()    // 初期化メソッド
	{
		m_pMesh = NULL;
		m_pWave = NULL;
		m_mWorld = XMMatrixIdentity();
		m_nMaterialFlag = 0;
	}
};
// --------------------------------------------------------------------
//
// 移動マップ            ＊このプログラム中では、使用しない
//
// --------------------------------------------------------------------
struct MOVEMAP
{
	BOOL					m_bActive;			// 表示の可否
	CFbxMesh*				m_pMesh;			// スタティックメッシュへのポインタ
	int						m_nMaterialFlag;	// マテリアルフラグ　0:通常　1:透明色　2:ディスプレイスメントマッピング
	CCollision*				m_pColMesh;			// 移動コリジョンメッシュへのポインタ
	BOOL					m_bMoveOn;			// 移動ON      FALSE:移動停止　TRUE:移動実行          // -- 2022.11.14
	int						m_nMoveFlag;		// 移動区分    1:平行移動　2:回転　3:拡大縮小         // -- 2022.11.14
	VECTOR3					m_vUp;				// 移動増分
	VECTOR3					m_vMinOffset;		// 移動増分最小値                                     // -- 2022.11.14
	VECTOR3					m_vMaxOffset;		// 移動増分最大値                                     // -- 2022.11.14
	int						m_nChangeFlag;		// 移動が限界値に到達して方向が入れ替わるとき(出力)　0:移動中　1:方向チェンジ
	int						m_nLoop;			// 移動を繰り返すか  0:チェンジの箇所で停止し移動ONを0:移動停止に戻す。 1:移動を繰り返す

	MOVEMAP()    // コンストラクタ
	{
		Init();
	}
	~MOVEMAP()    // デストラクタ
	{
		// この中でメッシュのDELETEをしてはならない
	}
	void Init()
	{
		m_bActive = FALSE;
		m_pMesh = NULL;
		m_nMaterialFlag = 0;
		m_pColMesh = NULL;
		m_bMoveOn = TRUE;    // 初期設定は移動実行
		m_nMoveFlag = 1;       // 初期設定は平行移動
		m_vUp = VECTOR3(0, 0, 0);
		m_vMinOffset = VECTOR3(-9999, -9999, -9999);
		m_vMaxOffset = VECTOR3(9999, 9999, 9999);
		m_nChangeFlag = 0;
		m_nLoop = 1;           // 初期設定はループ
	}
};

// --------------------------------------------------------------------
//
// ナビゲーションマップ
//
// --------------------------------------------------------------------
struct NAVIGATIONMAP
{
	VECTOR3 vMin;
	VECTOR3 vMax;
	std::vector<DWORD>  m_dwEnmID;  // 対象となる敵のＩＤ
	NAVIGATIONMAP()    // コンストラクタ
	{
		Init();
	}
	void Init()
	{
		vMin = VECTOR3(0.0f, 0.0f, 0.0f);
		vMax = VECTOR3(0.0f, 0.0f, 0.0f);
	}
	// 次の目的地を求めるときの最低距離を求める     // -- 2023.1.31
	float GetNearLimit()
	{
		float lx = vMax.x - vMin.x;      // Ｘ方向の長さ
		float lz = vMax.z - vMin.z;      // Ｚ方向の長さ
		float len = (lx < lz) ? lx : lz;  // 狭い方の長さを求める
		len = len * 0.5f * 0.99f;        // 狭い方の長さの半分弱を求める
		if (len > 10.0f) len = 10.0f;    // 10ｍを標準値とする。それより大きければ標準値とする。
		return len;
	}
};

// --------------------------------------------------------------------    // -- 2021.2.4
//
// イベント
//
// --------------------------------------------------------------------
// イベント種類
enum EVENTKIND
{
	eEvtKindNone = 0,
	eEvtChangeMap = 1,
	eEvtMoveMap = 2
};

struct EVENTMAP
{
	CBBox* m_pBBox;       // バウンディングボックス
	int       m_nEvtCycle;   // イベントサイクル 0:イベント実行していない 1:イベント実行中（使用していない） 2:イベント終了チェック（接触終わったか）
	EVENTKIND m_nEvtKind;    // イベントの種類 eEvtChangeMap:マップ移動, eEvtMoveMap:移動マップの制御
	int       m_nEvtNo;      // イベント番号 eEvtChangeMapのときは移動先のマップ番号、eEvtMoveMapのときは移動マップの要素番号
	int       m_nEvtOpe1;    // eEvtMoveMapのみ指定する。移動マップの動作指定　1:Activeの指定。2:移動ON・OFFの指定
	int       m_nEvtOpe2;    // eEvtMoveMapのみ指定する。移動マップの動作指定の動作内容　0:OFF　1:ON
	int       m_nEvtKeyPush; // 0:バウンディングボックスに接触するとイベント発動、 1:バウンディングボックスに接触して、ENTERキーを押すとイベント発動

	EVENTMAP()    // コンストラクタ
	{
		m_pBBox = NULL;
		m_nEvtCycle = 0;
		m_nEvtKind = eEvtKindNone;
		m_nEvtNo = 0;
		m_nEvtOpe1 = 0;
		m_nEvtOpe2 = 0;
		m_nEvtKeyPush = 0;
	}
	~EVENTMAP()    // デストラクタ
	{
		// この中でメッシュのCBBoxのDELETEをしてはならない
	}
};

//======================================================================
// マップ　プロシージャクラス
//
// (注意)マップ　プロシージャクラスは、基本プロシージャクラスを継承していない
// 
//======================================================================
class CMapProc
{
protected:
	// 定数定義 -------------------------------------------------
	static const int MAP_NOMAX = 100;              // マップNOの最大値を仮に100とする
	static const int MAP_SKYROTSPEED_X1000 = 5;    // 空の回転スピードの1000倍

	// -----------------------------------------------------------
	CGameMain* m_pGMain;

	DWORD								m_dwMapNo;
	BOOL								m_bActive;

	std::vector<STAGEMAP>				m_SkyMap;			// 空のマップ
	std::vector<STAGEMAP>				m_StageMap;			// ステージのマップ
	CCollision*							m_pColMesh;			// コリジョンメッシュ
	std::vector<MOVEMAP>				m_MoveMap;			// 移動マップ  *このプログラム中では、使用しない
	std::vector<NAVIGATIONMAP>			m_NavMap;			// ナビゲーションマップ
	std::vector<EVENTMAP>				m_EventMap;			// イベントマップ    // -- 2021.2.4
	int									m_nEvtIdx;			// イベント要素番号  // -- 2021.2.4


protected:
	// マップ作成関数
	// （この関数は外部からアクセス不可）
	void MakeMap1();

public:
	// メンバー関数
	void Update();
	void Render();
	void DestroyAll();
	BOOL LoadMap(int mapbo);

	void UpdateMoveMap();
	int  SetEvent(VECTOR3 vMin, VECTOR3 vMax, MATRIX4X4 mWorld, EVENTKIND nEvtKind, int nEvtNo, int nEvtOpe1 = 0, int nEvtOpe2 = 0, int nEvtKeyPush = 0);    // -- 2021.2.4
	void UpdateEvent();                                                                           // -- 2021.2.4
	void RunEvent(EVENTMAP& EventMap);                                                             // -- 2021.2.4

	BOOL Hitcheck(CBaseObj* pObj, VECTOR3* pHit, VECTOR3* pNormal);
	BOOL Hitcheck(VECTOR3 vNow, VECTOR3 vOld, VECTOR3* pHit, VECTOR3* pNormal);
	BOOL Hitcheck(VECTOR3 vNow, VECTOR3 vOld, float fRadius, VECTOR3* pHit, VECTOR3* pNormal);    // -- 2020.12.11

	int  isCollisionMoveGravity(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld, float fRadius = 0.2f);
	int  isCollisionMoveGravity(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld, VECTOR3& vHit, VECTOR3& vNormal, float fRadius = 0.2f);  // -- 2022.11.14
	int  isCollisionMove(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld, float fRadius = 0.2f);
	int  isCollisionMove(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld, VECTOR3& vHit, VECTOR3& vNormal, float fRadius = 0.2f);  // -- 2022.11.14

	// アクセス関数
	std::vector<NAVIGATIONMAP> GetNavMap() { return m_NavMap; }
	DWORD GetMapNo() { return m_dwMapNo; }

	// コンストラクタ（プロシージャの初期化）
	CMapProc(CGameMain* m_pGMain);
	~CMapProc();
};
//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１１                             ver 3.2        2023.1.31
//
//		カメラ制御
//
//		(視点変更処理・障害物回避処理が入っている)
//
//																Camera.h
//=============================================================================
#pragma once
#include "GameMain.h"

//======================================================================
// カメラ　オブジェクトクラス
//======================================================================
class CCameraObj : public CBaseObj
{
protected:
	int     m_nCtrl;                       // カメラ制御（0:ＴＰＳ視点  1:ＦＰＳ視点  2:固定視点）
	VECTOR3 m_vBaseLocalLookat;            // 基準ローカル注視点ベクトル
	VECTOR3 m_vBaseLocalEye;               // 基準ローカル視点ベクトル
	float   m_fBaseRotUp;                  // 角度増分
	float   m_fBaseDistUp;                 // 移動増分

	MATRIX4X4 m_mBaseWorld;                // 注視点・視点の基点となる基点ワールドマトリックス
	VECTOR3 m_vLocalLookat;                // ローカル注視点ベクトル
	VECTOR3 m_vLocalEye;                   // ローカル視点ベクトル

public:
	void Update() override;
	void InitCam(int ctrl, VECTOR3 lookat, VECTOR3 eye, float rot, float dist);
	void EvasiveObstacle();
	void ManualOperation();
	void SetLocalEyeTPS(float fRotY, float fRotX, float fDist);
	void SetCamBase();
	int  GetCtrl() { return m_nCtrl; }

	CCameraObj(CBaseProc* pProc);	// コンストラクタ
	virtual	~CCameraObj();
};


//======================================================================
// カメラ　プロシージャクラス
//======================================================================
class CCameraProc : public CBaseProc
{
protected:
	int  m_nCamObjNo;                         // カメラオブジェクトの要素番号

public:
	void Update() override;
	int GetCtrl() { return ((CCameraObj*)GetObjArrayPtr()[m_nCamObjNo])->GetCtrl(); }
	int GetCamObjNo() { return m_nCamObjNo; }
	void SetCamObjNo(int no) { m_nCamObjNo = no; }
	void InitCam(int no, int ctrl, VECTOR3 lookat, VECTOR3 eye, float rot, float dist);

	CCameraProc(CGameMain* pGMain);	// コンストラクタ
	virtual	~CCameraProc() { ; }
};


//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１１　　　　　　                 ver 3.2        2023.1.31
//		前景・背景							                   BackFore.cpp
//=============================================================================
#include "BackFore.h"
#include "Playchar.h"

//============================================================================
//
// 前景・背景プロシージャのコンストラクタ
//
// ---------------------------------------------------------------------------
CBackForeProc::CBackForeProc()
{
	m_pImageForegrd = new CSpriteImage(_T("Data/Image/foregrd3.png")); // スプライトイメージのロード
	m_pSprite       = new CSprite(); // スプライトの生成

}
// ---------------------------------------------------------------------------
//
// 前景・背景プロシージャのデストラクタ
//
// ---------------------------------------------------------------------------
CBackForeProc::~CBackForeProc()
{

	SAFE_DELETE(m_pImageForegrd);
	SAFE_DELETE(m_pSprite);

}
//------------------------------------------------------------------------
//
//	前景・背景プロシージャの更新	
//
//------------------------------------------------------------------------
void CBackForeProc::Draw()
{
	int DestX = 10;
	int DestY = 10;

	CPcProc* pPc = ObjectManager::FindGameObject<CPcProc>();
	// ステータスバーの表示
	float h = (float)pPc->Obj()->HpNow() / pPc->Obj()->HpMax();
	if (h < 0) h = 0;
	m_pSprite->Draw(m_pImageForegrd, DestX, DestY, 0, 0, 213, 31);
	m_pSprite->Draw(m_pImageForegrd, DestX + 59, DestY + 6, 59, 32, (DWORD)(144 * h), 6);

	// ＨＰとＰＣ残数の表示
	char str[256] = { 0 };
	sprintf_s<256>(str, "%d", pPc->Obj()->Remain());
	GameDevice()->m_pFont->Draw(DestX + 6, DestY + 15, str, 16, RGB(255, 0, 0));
	sprintf_s<256>(str, "%06d", pPc->Obj()->HpNow());
	GameDevice()->m_pFont->Draw(DestX + 26, DestY + 16, str, 12, RGB(0, 0, 0));
};
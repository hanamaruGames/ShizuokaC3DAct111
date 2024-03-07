//=============================================================================
//		３Ｄゲームプログラム
//		Ｃ３ＤＡｃｔ１１１　　　　　　                 ver 3.2        2023.1.31
//		前景・背景							                   BackFore.cpp
//=============================================================================
#include  "BackFore.h"
#include  "Playchar.h"


//============================================================================
//
// 前景・背景プロシージャのコンストラクタ
//
// ---------------------------------------------------------------------------
CBackForeProc::CBackForeProc(CGameMain* pGMain)
{
	m_pGMain		= pGMain;
	m_pImageForegrd = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/foregrd3.png")); // スプライトイメージのロード
	m_pSprite       = new CSprite(m_pGMain->m_pShader); // スプライトの生成

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
void CBackForeProc::Update()
{
	float h = 0;
	TCHAR str[256] = { 0 };
	int   DestX, DestY;

	// ステータスバーの表示
	h = (float)m_pGMain->m_pPcProc->GetPcObjPtr()->GetHp() / m_pGMain->m_pPcProc->GetPcObjPtr()->GetMaxHp();
	if (h < 0) h = 0;

	DestX = 10;
	DestY = 10;
	m_pSprite->Draw(m_pImageForegrd, DestX, DestY, 0, 0, 213, 31);
	m_pSprite->Draw(m_pImageForegrd, DestX + 59, DestY + 6, 59, 32, (DWORD)(144 * h), 6);

	// ＨＰとＰＣ残数の表示
	_stprintf_s(str, _T("%d"), m_pGMain->m_pPcProc->GetNum());
	m_pGMain->m_pFont->Draw(DestX + 6, DestY + 15, str, 16, RGB(255, 0, 0));
	_stprintf_s(str, _T("%06d"), m_pGMain->m_pPcProc->GetPcObjPtr()->GetHp());
	m_pGMain->m_pFont->Draw(DestX + 26, DestY + 16, str, 12, RGB(0, 0, 0));

};
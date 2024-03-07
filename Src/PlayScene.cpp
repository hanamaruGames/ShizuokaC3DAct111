#include "PlayScene.h"
#include "Playchar.h"
#include "Map.h"
#include "Camera.h"
#include "Weapon.h"
#include "Effect.h"
#include "BackFore.h"

PlayScene::PlayScene()
{
	// 各プロシージャの初期化
	CMapProc* pMap = Instantiate<CMapProc>();
	Instantiate<CPcProc>();
	Instantiate<CCameraProc>();
	Instantiate<CEffectProc>();
	Instantiate<CWeaponProc>();
	Instantiate<CBackForeProc>();
	// マップのロード
	//（ 最初はマップ１をロードする）
	pMap->LoadMap(1);

	// ＢＧＭの再生
	GameDevice()->m_pBgm1->Play(AUDIO_LOOP);
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (GameDevice()->m_pDI->CheckKey(KD_TRG, DIK_T)) {
		GameDevice()->m_pBgm1->Stop();
		SceneManager::ChangeScene("TitleScene");
	}
}

void PlayScene::Draw()
{
	GameDevice()->m_pFont->Draw(400, 15, _T("PLAY SCENE"), 16, RGB(255, 0, 0));
}
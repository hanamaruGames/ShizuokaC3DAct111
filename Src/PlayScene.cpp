#include "PlayScene.h"
#include "Playchar.h"
#include "Map.h"
#include "Camera.h"
#include "Weapon.h"
#include "Effect.h"
#include "BackFore.h"

PlayScene::PlayScene()
{
	// �e�v���V�[�W���̏�����
	CMapProc* pMap = Instantiate<CMapProc>();
	Instantiate<CPcProc>();
	Instantiate<CCameraProc>();
	Instantiate<CEffectProc>();
	Instantiate<CWeaponProc>();
	Instantiate<CBackForeProc>();
	// �}�b�v�̃��[�h
	//�i �ŏ��̓}�b�v�P�����[�h����j
	pMap->LoadMap(1);

	// �a�f�l�̍Đ�
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
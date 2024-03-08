//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�P                             ver 3.2        2023.1.31
// 
//		  �}�b�v���쐬�����[�h���鏈��
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
// �}�b�v�����[�h����֐�
//
// �E�쐬�����}�b�v�͕K�����̊֐��ɓo�^���A
// �@���̊֐�����Ăяo����Ȃ���΂Ȃ�Ȃ�
//
// ����   int mapno : ���[�h����}�b�v�̔ԍ�
// �߂�l bool  true:�}�b�v�L��   false:�}�b�v�Ȃ�
//
//-----------------------------------------------------------------------------
bool CMapProc::LoadMap(int mapno)
{
	switch (mapno)
	{
	case  1:			// �}�b�v�m�n�P
		MakeMap1();
		break;


	default:
		// �Y���ԍ��̃}�b�v����
		return false;
	}

	m_dwMapNo = mapno;    // �}�b�v�m�n�̐ݒ�
	m_bActive = true;     // �}�b�v�\��
	return true;
}
//-----------------------------------------------------------------------------
//
// �}�b�v�P�̍쐬����
//
// map50Field1
//
//-----------------------------------------------------------------------------
void CMapProc::MakeMap1()
{
	// vector�������p�̍\����
	const STAGEMAP      sm;
	const NAVIGATIONMAP nv;

	// �S�}�b�v�̍폜 -----------------------------------------------
	DestroyAll();

	// �S�Ă̌��ʂ̔�\���� 
	ObjectManager::FindGameObject<CEffectProc>()->SetNonActive();

	CPcProc* pPc = ObjectManager::FindGameObject<CPcProc>();

	// �o�b��(0,0,-20)�̈ʒu�ɒu�� -------------------------------------
	pPc->GetPcObjPtr()->SetWorld(XMMatrixTranslation(0.0f, 0.05f, -20.0f));
	pPc->GetPcObjPtr()->SetWorldOld(pPc->GetPcObjPtr()->GetWorld());
	pPc->GetPcObjPtr()->SetLocalRotY(0.0f);  // ���[�J����(Y��)��0�x�ɂ���

	// �X�e�[�W�}�b�v�̐ݒ�E�R���W�����}�b�v�̐ݒ� -----------------------------------------
	m_pColMesh = new CCollision(GameDevice()->m_pFbxMeshCtrl);     // �R���W�����}�b�v�̐���

	// �}�b�v���b�V���̐ݒ�[0]
	m_StageMap.push_back(sm);
	//m_StageMap.back().m_pMesh = new CFbxMesh(GameDevice()->m_pFbxMeshCtrl, _T("Data/Map/MapClsc/map40.mesh"));
	m_StageMap.back().m_pMesh = new CFbxMesh(GameDevice()->m_pFbxMeshCtrl, _T("Data/Map/MapTkr/map50Field1.mesh"));       // -- 2022.2.16
	m_StageMap.back().m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	//m_pColMesh->AddFbxLoad(_T("Data/Map/MapClsc/map40_CHK.mesh"), m_StageMap.back().m_mWorld); // �}�b�v���b�V���R���W�����̐ݒ�
	m_pColMesh->AddFbxLoad(_T("Data/Map/MapTkr/map50Field1.mesh"), m_StageMap.back().m_mWorld); // �}�b�v���b�V���R���W�����̐ݒ�

	// �h�A���b�V���̐ݒ�[1]
	m_StageMap.push_back(sm);
	m_StageMap.back().m_pMesh = new CFbxMesh(GameDevice()->m_pFbxMeshCtrl, _T("Data/Map/MapItem/DOOR1.mesh"));
	m_StageMap.back().m_mWorld = XMMatrixTranslation(-80.0f, 0.0f, 80.0f);
	m_pColMesh->AddFbxLoad(_T("Data/Map/MapItem/DOOR1.mesh"), m_StageMap.back().m_mWorld); // �h�A���b�V���R���W�����̐ݒ�

	// ���ʂ̐ݒ�[2]
	m_StageMap.push_back(sm);
	m_StageMap.back().m_pWave = new CWave(GameDevice()->m_pShader, 50, 70, _T("Data/Map/MapItem/WaterNM.png"));             // ���ʂ̑傫���i���[�g���P�ʁj�ƃm�[�}���}�b�v�e�N�X�`���̎w��
	m_StageMap.back().m_mWorld = XMMatrixTranslation(38.0f, -0.5f, -5.0f);      // ���ʂ�u���ʒu�i�쐬�������ʂ̍��[�A��O�[�̈ʒu���w�肷��j
	m_StageMap.back().m_nMaterialFlag = 3;   // ���ʂ̃f�B�X�v���C�X�����g�}�b�s���O

	// �n�◬�̐ݒ�[2]
	//m_StageMap.push_back(sm);
	//m_StageMap.back().m_pWave = new CWave(GameDevice()->m_pShader, 50,70, _T("Data/Map/MapItem/lava03_NM.png"), _T("Data/Map/MapItem/lava03.png"), _T("Data/Map/MapItem/lava03.png"));      // �n�◬�̑傫���i���[�g���P�ʁj�Ɗe��e�N�X�`���̎w��
	//m_StageMap.back().m_pWave->m_fMaxDistance = 40.0f;
	//m_StageMap.back().m_pWave->m_fMinDistance = 20.0f;
	//m_StageMap.back().m_pWave->m_fWaveHeight = 0.15f;
	//m_StageMap.back().m_mWorld = XMMatrixTranslation(38.0f, -0.5f, -5.0f);      // �n�◬��u���ʒu�i�쐬�����n�◬�̍��[�A��O�[�̈ʒu���w�肷��j
	//m_StageMap.back().m_nMaterialFlag = 3;   // �n�◬�̃f�B�X�v���C�X�����g�}�b�s���O

	// ��p  -----------------------------------------------------------
	// ��}�b�v�̐ݒ�[0]
	m_SkyMap.push_back(sm);
	m_SkyMap.back().m_pMesh = new CFbxMesh(GameDevice()->m_pFbxMeshCtrl, _T("Data/Map/Sky/sky2.mesh"));
	m_SkyMap.back().m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 0.0f);

	// �i�r�Q�[�V�����}�b�v�̐ݒ� --------------------------------------
	// �i�r�}�b�v�̐ݒ�[0]
	m_NavMap.push_back(nv);
	m_NavMap.back().vMin = VECTOR3(-30.0f, 0.05f, 10.0f);
	m_NavMap.back().vMax = VECTOR3(30.0f, 0.05f, 30.0f);

}


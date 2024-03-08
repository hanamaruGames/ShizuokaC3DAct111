//=============================================================================
// 
// 		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�P                             ver 3.2       2022.11.14
//		  �}�b�v�̏���
//																	Map.cpp
//=============================================================================
#include  "BaseProc.h"
#include  "Map.h"
#include  "Playchar.h"
#include  "Weapon.h"


//=============================================================================
//
// �}�b�v�v���V�[�W���̃R���X�g���N�^
//
//-----------------------------------------------------------------------------
CMapProc::CMapProc()
{
	// �N���X�S�̂̃N�����[
	// (vector�N���X�͏������s�v)
//	GameDevice() = pGMain;
	m_dwMapNo = 0;
	m_bActive = false;
	m_pColMesh   = nullptr;					// �R���W�������b�V���ւ̃|�C���^
	m_nEvtIdx = 0;							// -- 2021.2.4

}

//-----------------------------------------------------------------------------
//
// �}�b�v�v���V�[�W���̃f�X�g���N�^
//
//-----------------------------------------------------------------------------
CMapProc::~CMapProc()
{
	DestroyAll();
}

//-----------------------------------------------------------------------------
//
// �}�b�v�̍폜
//
//-----------------------------------------------------------------------------
void CMapProc::DestroyAll()
{
	m_dwMapNo = 0;
	m_bActive = false;
	m_nEvtIdx = 0;							// -- 2021.2.4

	// ���b�V���̃f���[�g
	for(DWORD i = 0; i<m_SkyMap.size(); i++)
	{
		SAFE_DELETE(m_SkyMap[i].m_pMesh);
		SAFE_DELETE(m_SkyMap[i].m_pWave);    // �g�p���Ă��Ȃ����O�̂��ߍ폜
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

	// vector�̍폜
	m_SkyMap.clear();					// ��̃}�b�v  �z��폜
	m_SkyMap.shrink_to_fit();			// ��̃}�b�v  �s�v���������
	m_StageMap.clear();					// �X�e�[�W�̃}�b�v  �z��폜
	m_StageMap.shrink_to_fit();			// �X�e�[�W�̃}�b�v �s�v���������
	m_MoveMap.clear();					// �ړ��}�b�v  �z��폜
	m_MoveMap.shrink_to_fit();			// �ړ��}�b�v �s�v���������
	m_NavMap.clear();					// �i�r�Q�[�V�����}�b�v�z��폜
	m_NavMap.shrink_to_fit();			// �i�r�Q�[�V�����}�b�v�s�v���������
	m_EventMap.clear();					// �C�x���g�}�b�v�z��폜
	m_EventMap.shrink_to_fit();			// �C�x���g�}�b�v�s�v���������

}

//-----------------------------------------------------------------------------
// �}�b�v�v���V�[�W���̂����蔻��
//
// �E����i��ɂo�b�̕���j�ƃR���W�����}�b�v�Ƃ̂����蔻��
//
//   CBaseObj*    pObj      ����̃I�u�W�F�N�g
//   VECTOR3* pHit		�ڐG�_�̍��W�i�o�́j
//   VECTOR3* pNormal	�ڐG�_�̖@���x�N�g���i�o�́jwwwwwwwwwwwwwwwwwwwww

//
//   �߂�l�@bool
//           true:�q�b�g�����Ƃ�       false�F�q�b�g���Ă��Ȃ��Ƃ�
//
//-----------------------------------------------------------------------------
bool   CMapProc::Hitcheck(CBaseObj* pObj, VECTOR3* pHit, VECTOR3* pNormal)
{
	return  Hitcheck(GetPositionVector(pObj->GetWorld()), GetPositionVector(pObj->GetWorldOld()), pHit, pNormal);
}
//-----------------------------------------------------------------------------
// �}�b�v�v���V�[�W���̂����蔻��
//
// �E����i��ɂo�b�̕���j�ƃR���W�����}�b�v�Ƃ̂����蔻��
//
//   VECTOR3 vNow       ����̌��݈ʒu
//   VECTOR3 vOld       ����̈�O�̈ʒu
//   VECTOR3* vHit		�ڐG�_�̍��W�i�o�́j
//   VECTOR3* vNormal	�ڐG�_�̖@���x�N�g���i�o�́j
//
//   �߂�l�@bool
//           true:�q�b�g�����Ƃ�       false�F�q�b�g���Ă��Ȃ��Ƃ�
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
// �}�b�v�v���V�[�W���̂����蔻��
//
// �E����i��ɂo�b�̕���j�̋��ƃR���W�����}�b�v�Ƃ̂����蔻��
//
//   VECTOR3 vNow       ����̌��݂̃I�u�W�F�N�g���S�ʒu
//   VECTOR3 vOld       ����̈�O�̃I�u�W�F�N�g���S�ʒu
//   float& fRadius     ���̔��a
//   VECTOR3 &vHit      �ڐG���̃I�u�W�F�N�g���S�ʒu�̍��W�i�o�́j
//   VECTOR3 &vNormal   �ڐG�_�̖@���x�N�g���i�o�́j
//
//   �߂�l�@bool
//           true:�q�b�g�����Ƃ�       false�F�q�b�g���Ă��Ȃ��Ƃ�
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
// �I�u�W�F�N�g�̃��C�ƃ��b�V���ڐG����p�z��Ƃ̐ڐG����ƃX���X������������
//	���፷�Əd�͂��l�������A�ڐG������s��									2022.11.14
//  
//  MATRIX4X4* pWorld     �I�u�W�F�N�g�̌��݂̃}�g���b�N�X(in,out)
//  MATRIX4X4  mWorldOld  �I�u�W�F�N�g�̈�O�̃}�g���b�N�X		
//  float fRadius          �I�u�W�F�N�g�̔��a�i�ȗ��l��0.2�j
//  
//  �߂�l�@int
//		�G���[		= -1
//		�ʏ���ړ�	= 1
//		���n		= 2
//		������		= 3
//-----------------------------------------------------------------------------
int  CMapProc::isCollisionMoveGravity(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld, float fRadius)
{
	VECTOR3 vHit, vNormal;
	return isCollisionMoveGravity(pWorld, mWorldOld, vHit, vNormal, fRadius);
}
//-----------------------------------------------------------------------------
// �I�u�W�F�N�g�̃��C�ƃ��b�V���ڐG����p�z��Ƃ̐ڐG����ƃX���X������������
//	���፷�Əd�͂��l�������A�ڐG������s��									2022.11.14
//  
//  MATRIX4X4* pWorld     �I�u�W�F�N�g�̌��݂̃}�g���b�N�X(in,out)
//  MATRIX4X4  mWorldOld  �I�u�W�F�N�g�̈�O�̃}�g���b�N�X		
//  VECTOR3    &vHit	  �ڐG�_�̍��W�i�o�́j
//  VECTOR3    &vNormal	  �ڐG�_�̖@���x�N�g���i�o�́j
//  float fRadius         �I�u�W�F�N�g�̔��a�i�ȗ��l��0.2�j
//  
//  �߂�l�@int
//		�G���[		= -1
//		�ʏ���ړ�	= 1
//		���n		= 2
//		������		= 3
//-----------------------------------------------------------------------------
int  CMapProc::isCollisionMoveGravity(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld, VECTOR3& vHit, VECTOR3& vNormal, float fRadius)
{
	int  nRet = 0, nRetMove = 0;  // -- 2019.9.3

	// �ړ��}�b�v�Ƃ̐ڐG����ƈړ�
	for (int i = 0; i < m_MoveMap.size(); i++)
	{
		if (m_MoveMap[i].m_pColMesh && m_MoveMap[i].m_bActive)
		{
			nRetMove = m_MoveMap[i].m_pColMesh->isCollisionMoveGravity(*pWorld, mWorldOld, vHit, vNormal, fRadius);  // -- 2022.11.14
			if (nRetMove == 1 || nRetMove == 2) break;   // �ړ��}�b�v�ƐڐG�����Ƃ�
		}
	}

	// �ʏ�̃}�b�v�Ƃ̐ڐG����ƈړ�
	if (m_pColMesh)
	{
		nRet = m_pColMesh->isCollisionMoveGravity(*pWorld, mWorldOld, vHit, vNormal, fRadius);  // -- 2022.11.14
	}

	if (nRetMove == 1 || nRetMove == 2)  // �ړ��}�b�v�ƐڐG���Ă����Ƃ�   // -- 2019.9.3
	{
		return nRetMove;
	}
	else {
		return nRet;
	}
}
//-----------------------------------------------------------------------------
// �I�u�W�F�N�g�̃��C�ƃ��b�V���ڐG����p�z��Ƃ̐ڐG����ƃX���X������������
//	�d�͂��l�����A�ڐG������s��											2022.11.14
//  
//  MATRIX4X4* pWorld     �I�u�W�F�N�g�̌��݂̃}�g���b�N�X(in,out)
//  MATRIX4X4  mWorldOld  �I�u�W�F�N�g�̈�O�̃}�g���b�N�X		
//  float fRadius          �I�u�W�F�N�g�̔��a�i�ȗ��l��0.2�j
//  
//  �߂�l�@int
//		�ڐG�����Ƃ��@		�P
//		�ڐG���Ă��Ȃ��Ƃ�	�O
//-----------------------------------------------------------------------------
int CMapProc::isCollisionMove(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld, float fRadius)
{
	VECTOR3 vHit, vNormal;
	return isCollisionMove(pWorld, mWorldOld, vHit, vNormal, fRadius);
}
//-----------------------------------------------------------------------------
// �I�u�W�F�N�g�̃��C�ƃ��b�V���ڐG����p�z��Ƃ̐ڐG����ƃX���X������������
//	�d�͂��l�����A�ڐG������s��											2022.11.14
//  
//  MATRIX4X4* pWorld     �I�u�W�F�N�g�̌��݂̃}�g���b�N�X(in,out)
//  MATRIX4X4  mWorldOld  �I�u�W�F�N�g�̈�O�̃}�g���b�N�X		
//  VECTOR3    &vHit	  �ڐG�_�̍��W�i�o�́j
//  VECTOR3    &vNormal	  �ڐG�_�̖@���x�N�g���i�o�́j
//  float fRadius          �I�u�W�F�N�g�̔��a�i�ȗ��l��0.2�j
//  
//  �߂�l�@int
//		�ڐG�����Ƃ��@		�P
//		�ڐG���Ă��Ȃ��Ƃ�	�O
//-----------------------------------------------------------------------------
int CMapProc::isCollisionMove(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld, VECTOR3& vHit, VECTOR3& vNormal, float fRadius)
{
	int  nRet = 0, nRetMove = 0;  // -- 2019.9.3

	// �ړ��}�b�v�Ƃ̐ڐG����ƈړ�
	for (int i = 0; i < m_MoveMap.size(); i++)
	{
		if (m_MoveMap[i].m_pColMesh && m_MoveMap[i].m_bActive)
		{
			nRetMove = m_MoveMap[i].m_pColMesh->isCollisionMove(*pWorld, mWorldOld, vHit, vNormal, fRadius);  // -- 2022.11.14
			if (nRetMove == 1) break;
		}
	}

	// �ʏ�̃}�b�v�Ƃ̐ڐG����ƈړ�
	if (m_pColMesh)
	{
		nRet = m_pColMesh->isCollisionMove(*pWorld, mWorldOld, vHit, vNormal, fRadius);  // -- 2022.11.14
	}

	if (nRetMove == 1)  // �ړ��}�b�v�ƐڐG���Ă����Ƃ�     // -- 2019.9.3
	{
		return nRetMove;
	}
	else {
		return nRet;
	}
}


//-----------------------------------------------------------------------------
//
// �}�b�v�v���V�[�W���̍X�V
//
//-----------------------------------------------------------------------------
void CMapProc::Update()
{
	CDirectInput* pDI = GameDevice()->m_pDI;
	const float MAP_SKYROTSPEED = MAP_SKYROTSPEED_X1000 / 1000.0f;

	// �C�x���g�̍X�V����                         // -- 2021.2.4
	UpdateEvent();

	// ��̍X�V�@�@�J�����𒆐S�Ƃ����ʒu�ɒu���A�x����]������
	if (m_SkyMap.size() > 0)
	{
		MATRIX4X4 mRot;
		mRot = XMMatrixRotationY(XMConvertToRadians(MAP_SKYROTSPEED));
		mRot = mRot * GetRotateMatrix(m_SkyMap[0].m_mWorld);
		m_SkyMap[0].m_mWorld = XMMatrixTranslation(GameDevice()->m_vEyePt.x, GameDevice()->m_vEyePt.y, GameDevice()->m_vEyePt.z);
		m_SkyMap[0].m_mWorld = mRot * m_SkyMap[0].m_mWorld;
	}

	// �ړ��}�b�v�X�V����
	UpdateMoveMap();

}
//-----------------------------------------------------------------------------   // -- 2021.2.4
//
// �C�x���g�̃Z�b�g
//
// ����
//   VECTOR3 vMin         : �o�E���f�B���O�{�b�N�X�ŏ��l
//   VECTOR3 vMax         : �o�E���f�B���O�{�b�N�X�ő�l
//   MATRIX4X4 mWorld     : �o�E���f�B���O�{�b�N�X�̃��[���h�}�g���b�N�X
//   EVENTKIND nEvtKind   : �C�x���g�̎�� eEvtChangeMap:�}�b�v�ړ�, eEvtMoveMap:�ړ��}�b�v�̐���
//   int nEvtNo           : �C�x���g�ԍ� eEvtChangeMap�̂Ƃ��͈ړ���̃}�b�v�ԍ��AeEvtMoveMap�̂Ƃ��͈ړ��}�b�v�̗v�f�ԍ�
//   int m_nEvtOpe1       : eEvtMoveMap�̂ݎw�肷��B1:Active�̎w��B2:�ړ�ON�EOFF�̎w��
//   int m_nEvtOpe2       : eEvtMoveMap�̂ݎw�肷��B0:OFF�@1:ON
//   int nEvtKeyPush      : 0:�o�E���f�B���O�{�b�N�X�ɐڐG����ƃC�x���g�����A 1:�o�E���f�B���O�{�b�N�X�ɐڐG���āAENTER�L�[�������ƃC�x���g����(�ȗ��l0)
//
// �߂�l
//   int �Z�b�g�����C�x���g�z��̗v�f�ԍ�
//
//-----------------------------------------------------------------------------
int  CMapProc::SetEvent(VECTOR3 vMin, VECTOR3 vMax, MATRIX4X4 mWorld, EVENTKIND nEvtKind, int nEvtNo, int nEvtOpe1, int nEvtOpe2, int nEvtKeyPush)
{
	const EVENTMAP      em;

	m_EventMap.push_back(em);

	// �o�E���f�B���O�{�b�N�X�̐ݒ�
	m_EventMap[m_nEvtIdx].m_pBBox = new CBBox(GameDevice()->m_pShader, vMin, vMax);
	m_EventMap[m_nEvtIdx].m_pBBox->m_mWorld = mWorld;

	// �e���ڂ̐ݒ�
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
// �C�x���g�̍X�V�E���s
//
//-----------------------------------------------------------------------------
void  CMapProc::UpdateEvent()
{
	VECTOR3 vHit, vNrm;
	CPcProc* pPc = ObjectManager::FindGameObject<CPcProc>();

	for (int i = 0; i < m_EventMap.size(); i++)
	{
		// PC�̃o�E���f�B���O�{�b�N�X�ɐڐG���Ă��邩�̔���
		if (m_EventMap[i].m_pBBox && m_EventMap[i].m_pBBox->OBBCollisionDetection(pPc->Obj()->GetBBox(), &vHit, &vNrm))
		{
			// PC�̃o�E���f�B���O�{�b�N�X�ɐڐG���Ă���Ƃ�
			if (m_EventMap[i].m_nEvtCycle == 0)  // �C�x���g�T�C�N�����O�̂Ƃ�(�܂��ڐG���Ă��Ȃ������Ƃ�)
			{
				if (m_EventMap[i].m_nEvtKeyPush == 1 && !(GameDevice()->m_pDI->CheckKey(KD_DAT, DIK_RETURN) || GameDevice()->m_pDI->CheckJoy(KD_DAT, DIJ_A)))  // Enter�L�[�v�b�V�����K�v�ȂƂ�
				{
					VECTOR3 vPc = GetPositionVector(pPc->Obj()->GetWorld());
					vPc.y += 2.0f;
					// PC�̓���ɁAEnter�L�[�v�b�V�����s���Ă��Ȃ����̕\��������
					GameDevice()->m_pFont->Draw3D(vPc, GameDevice()->m_mView, GameDevice()->m_mProj, GameDevice()->m_vEyePt, _T("Push Enter Key!"), VECTOR2(0.8f, 0.2f), RGB(255, 0, 0), 1.0f, _T("HGP�n�p�p�޼��UB"));
				}
				else {
					// �C�x���g���s
					RunEvent(m_EventMap[i]);
				}
			}
		}
		else {
			// PC�̃o�E���f�B���O�{�b�N�X�ɐڐG���Ă��Ȃ��Ƃ�
			if (m_EventMap[i].m_nEvtCycle == 2)  // �C�x���g�T�C�N�����Q�̂Ƃ�(���ɐڐG���Ă��ďI���҂��̂Ƃ�)
			{
				m_EventMap[i].m_nEvtCycle = 0;  // �C�x���g�T�C�N�����O�ɖ߂�
			}
		}
	}
}

//-----------------------------------------------------------------------------   // -- 2021.2.4
//
// �C�x���g�̎��s
//
// ����  EVENTMAP& EventMap:�C�x���g�}�b�v
//
//-----------------------------------------------------------------------------
void  CMapProc::RunEvent(EVENTMAP& EventMap)
{
	int i;

	if (EventMap.m_nEvtKind == eEvtChangeMap)   // �}�b�v�ړ��̂Ƃ�
	{
		if (!LoadMap(EventMap.m_nEvtNo))
		{
			MessageBox(nullptr, _T("������ CMapProc::RunEvent() ������"), _T("������ �}�b�v�ړ��ԍ��̃}�b�v������܂��� ������"), MB_OK);
		}
	}
	else if (EventMap.m_nEvtKind == eEvtMoveMap)  // �ړ��}�b�v�̐���̂Ƃ�
	{
		i = EventMap.m_nEvtNo;
		if (EventMap.m_nEvtOpe1 == 1)   // �\���L���Ɋւ��鏈��
		{
			m_MoveMap[i].m_bActive = EventMap.m_nEvtOpe2;
		}
		else if (EventMap.m_nEvtOpe1 == 2)   // �ړ��Ɋւ��鏈��
		{
			m_MoveMap[i].m_bMoveOn = EventMap.m_nEvtOpe2;           // -- 2022.11.14
		}
		EventMap.m_nEvtCycle = 2;  // �C�x���g�T�C�N�����Q�ɂ���   // -- 2021.4.4
	}
}

//-----------------------------------------------------------------------------// -- 2022.11.14
//
// �ړ��}�b�v�̍X�V
//
// �ړ��}�b�v�̕��s�ړ����]�̍X�V���s��
// ���E�l�i��[���[���j�ɒB�����Ƃ��́A���]�ichange�j���s��
// ���]�ichange�j�������Ƃ��́Am_nChangeFlag�ɂP���Ԃ�
// ���[�v�����Ȃ��Ƃ��͔��]�̃^�C�~���O�Œ�~���� 
//
//-----------------------------------------------------------------------------
void CMapProc::UpdateMoveMap()
{
	for (DWORD i = 0; i < m_MoveMap.size(); i++)
	{
		if (m_MoveMap[i].m_pColMesh && m_MoveMap[i].m_bActive && m_MoveMap[i].m_bMoveOn)   // �ړ��}�b�v�̍X�V����  // -- 2022.11.14
		{
			m_MoveMap[i].m_pColMesh->m_mWorldOld = m_MoveMap[i].m_pColMesh->m_mWorld;   // ���[���h�}�g���b�N�X��O
			m_MoveMap[i].m_nChangeFlag = 0;      // �`�F���W�t���O�̃��Z�b�g
			if (m_MoveMap[i].m_nMoveFlag == 1)   // ���s�ړ��̏���
			{
				MATRIX4X4 mOffset;
				m_MoveMap[i].m_pColMesh->SetWorldMatrix(XMMatrixTranslationFromVector(m_MoveMap[i].m_vUp) * m_MoveMap[i].m_pColMesh->m_mWorld);  // �ړ������̏���   // -- 2022.11.14
				mOffset = m_MoveMap[i].m_pColMesh->m_mWorld * XMMatrixInverse(nullptr, m_MoveMap[i].m_pColMesh->m_mWorldBase);  // �ړ���ʒu�����_����Ƃ����ʒu�ɂ���   // -- 2022.11.14
				if (m_MoveMap[i].m_vUp.x != 0)  // ���E�ɓ�����
				{
					if (GetPositionVector(mOffset).x < m_MoveMap[i].m_vMinOffset.x ||  // ���E�ɓ��������߉E�[���[�Ŕ��]
						GetPositionVector(mOffset).x > m_MoveMap[i].m_vMaxOffset.x)
					{
						m_MoveMap[i].m_vUp.x *= -1;
						m_MoveMap[i].m_nChangeFlag = 1;
					}
				}
				if (m_MoveMap[i].m_vUp.y != 0)  // �㉺�ɓ�����
				{
					if (GetPositionVector(mOffset).y < m_MoveMap[i].m_vMinOffset.y ||  // �㉺�ɓ��������ߏ�[���[�Ŕ��]
						GetPositionVector(mOffset).y > m_MoveMap[i].m_vMaxOffset.y)
					{
						m_MoveMap[i].m_vUp.y *= -1;
						m_MoveMap[i].m_nChangeFlag = 1;
					}
				}
				if (m_MoveMap[i].m_vUp.z != 0)  // �O��ɓ�����
				{
					if (GetPositionVector(mOffset).z < m_MoveMap[i].m_vMinOffset.z ||  // �O��ɓ��������ߑO�[��[�Ŕ��]
						GetPositionVector(mOffset).z > m_MoveMap[i].m_vMaxOffset.z)
					{
						m_MoveMap[i].m_vUp.z *= -1;
						m_MoveMap[i].m_nChangeFlag = 1;
					}
				}
			}
			else if (m_MoveMap[i].m_nMoveFlag == 2) {   // ��]�̏���
				MATRIX4X4 mOffset;
				if (m_MoveMap[i].m_vUp.x != 0)  // �w��]
				{
					m_MoveMap[i].m_pColMesh->SetWorldMatrix(XMMatrixRotationX(XMConvertToRadians(m_MoveMap[i].m_vUp.x)) * m_MoveMap[i].m_pColMesh->m_mWorld);  // �ړ������̏���   // -- 2022.11.14
					mOffset = m_MoveMap[i].m_pColMesh->m_mWorld * XMMatrixInverse(nullptr, m_MoveMap[i].m_pColMesh->m_mWorldBase);  // ��]��p�x�����_����Ƃ����p�x�ɂ���   // -- 2022.11.14

					if (GetRotateVector3(mOffset).x < m_MoveMap[i].m_vMinOffset.x ||  // �w��]���邽�ߒ[�Ŕ��]
						GetRotateVector3(mOffset).x > m_MoveMap[i].m_vMaxOffset.x)
					{
						m_MoveMap[i].m_vUp.x *= -1;  // �w��]���邽�ߒ[�Ŕ��]
						m_MoveMap[i].m_nChangeFlag = 1;
					}
				}
				else if (m_MoveMap[i].m_vUp.y != 0)  // �x��]
				{
					m_MoveMap[i].m_pColMesh->SetWorldMatrix(XMMatrixRotationY(XMConvertToRadians(m_MoveMap[i].m_vUp.y)) * m_MoveMap[i].m_pColMesh->m_mWorld);  // �ړ������̏���   // -- 2022.11.14
					mOffset = m_MoveMap[i].m_pColMesh->m_mWorld * XMMatrixInverse(nullptr, m_MoveMap[i].m_pColMesh->m_mWorldBase);  // ��]��p�x�����_����Ƃ����p�x�ɂ���   // -- 2022.11.14

					if (GetRotateVector3(mOffset).y < m_MoveMap[i].m_vMinOffset.y ||  // �x��]���邽�ߒ[�Ŕ��]
						GetRotateVector3(mOffset).y > m_MoveMap[i].m_vMaxOffset.y)
					{
						m_MoveMap[i].m_vUp.y *= -1;  // �x��]���邽�ߒ[�Ŕ��]
						m_MoveMap[i].m_nChangeFlag = 1;
					}
				}
				else if (m_MoveMap[i].m_vUp.z != 0)  // �y��]
				{
					m_MoveMap[i].m_pColMesh->SetWorldMatrix(XMMatrixRotationZ(XMConvertToRadians(m_MoveMap[i].m_vUp.z)) * m_MoveMap[i].m_pColMesh->m_mWorld);  // �ړ������̏���   // -- 2022.11.14
					mOffset = m_MoveMap[i].m_pColMesh->m_mWorld * XMMatrixInverse(nullptr, m_MoveMap[i].m_pColMesh->m_mWorldBase);  // ��]��p�x�����_����Ƃ����p�x�ɂ���   // -- 2022.11.14

					if (GetRotateVector3(mOffset).z < m_MoveMap[i].m_vMinOffset.z ||  // �y��]���邽�ߒ[�Ŕ��]
						GetRotateVector3(mOffset).z > m_MoveMap[i].m_vMaxOffset.z)
					{
						m_MoveMap[i].m_vUp.z *= -1;  // �y��]���邽�ߒ[�Ŕ��]
						m_MoveMap[i].m_nChangeFlag = 1;
					}
				}
			}
			else if (m_MoveMap[i].m_nMoveFlag == 3) {   // �g��k���̏���      // -- 2019.12.30
				MATRIX4X4 mOffset;
				m_MoveMap[i].m_pColMesh->SetWorldMatrix(XMMatrixScaling(m_MoveMap[i].m_vUp.x, m_MoveMap[i].m_vUp.y, m_MoveMap[i].m_vUp.z)
					* m_MoveMap[i].m_pColMesh->m_mWorld);  // �g��k�������̏���
				mOffset = m_MoveMap[i].m_pColMesh->m_mWorld * XMMatrixInverse(nullptr, m_MoveMap[i].m_pColMesh->m_mWorldBase);  // �g��k�������_����Ƃ����g��k���ɂ���   // -- 2022.11.14

				VECTOR3 vScaleNow = GetScaleVector(mOffset);     // ���݂̊g�嗦�𓾂�
				if (vScaleNow.x < m_MoveMap[i].m_vMinOffset.x ||      // �K��̊g��k���ɒB������
					vScaleNow.x > m_MoveMap[i].m_vMaxOffset.x ||
					vScaleNow.y < m_MoveMap[i].m_vMinOffset.y ||
					vScaleNow.y > m_MoveMap[i].m_vMaxOffset.y ||
					vScaleNow.z < m_MoveMap[i].m_vMinOffset.z ||
					vScaleNow.z > m_MoveMap[i].m_vMaxOffset.z)
				{
					m_MoveMap[i].m_vUp.x = 1 / avoidZero(m_MoveMap[i].m_vUp.x);  // �g��k���̔��]
					m_MoveMap[i].m_vUp.y = 1 / avoidZero(m_MoveMap[i].m_vUp.y);  // �g��k���̔��]
					m_MoveMap[i].m_vUp.z = 1 / avoidZero(m_MoveMap[i].m_vUp.z);  // �g��k���̔��]
					m_MoveMap[i].m_nChangeFlag = 1;
				}
			}
			// ���[�v�����Ȃ��Ƃ��̒�~���f�B���]�̃^�C�~���O�Œ�~����
			if (m_MoveMap[i].m_nLoop == 0 && m_MoveMap[i].m_nChangeFlag == 1)
			{
				m_MoveMap[i].m_bMoveOn = false;    // �ړ����Ȃ�    // -- 2022.11.14
			}
		}
	}
}

//============================================================================
//  �}�b�v�v���V�[�W���̃����_�����O
// 
//    �����@�@�Ȃ�
// 
//    �߂�l�@�Ȃ�
//============================================================================
void  CMapProc::Draw()
{
	if (m_bActive) {

		// ��̃����_�����O
		if (m_SkyMap.size() > 0)
		{
			// ��̃����_�����O   �A�e�����Ȃ������_�����O 
			// Z�o�b�t�@�𖳌���
			GameDevice()->m_pD3D->SetZBuffer(false);
			m_SkyMap[0].m_pMesh->Render(m_SkyMap[0].m_mWorld, GameDevice()->m_mView, GameDevice()->m_mProj, VECTOR3(0, 0, 0), GameDevice()->m_vEyePt);  // �A�e�����Ȃ������_�����O 
			// Z�o�b�t�@��L����
			GameDevice()->m_pD3D->SetZBuffer(true);
		}

		// �}�b�v�����_�����O
		for (DWORD i = 0; i < m_StageMap.size(); i++)
		{
			if (m_StageMap[i].m_nMaterialFlag == 0)  // �ʏ�̃u�����h�X�e�[�g
			{
				if (m_StageMap[i].m_pMesh)
					m_StageMap[i].m_pMesh->Render(m_StageMap[i].m_mWorld, GameDevice()->m_mView, GameDevice()->m_mProj, GameDevice()->m_vLightDir, GameDevice()->m_vEyePt);

			}
			else if (m_StageMap[i].m_nMaterialFlag == 2)  // �f�B�X�v���[�X�����g�}�b�s���O   // -- 2020.12.15
			{
				if (m_StageMap[i].m_pMesh)
					m_StageMap[i].m_pMesh->RenderDisplace(m_StageMap[i].m_mWorld, GameDevice()->m_mView, GameDevice()->m_mProj, GameDevice()->m_vLightDir, GameDevice()->m_vEyePt);

			}
			else if (m_StageMap[i].m_nMaterialFlag == 3) // �g�̃����_�����O
			{
				if (m_StageMap[i].m_pWave)
					m_StageMap[i].m_pWave->Render(m_StageMap[i].m_mWorld, GameDevice()->m_mView, GameDevice()->m_mProj, GameDevice()->m_vLightDir, GameDevice()->m_vEyePt);
			}
		}

		// �ړ��}�b�v�����_�����O     * ���̃v���O�����ł͎g�p���Ă��Ȃ�
		for (DWORD i = 0; i < m_MoveMap.size(); i++)
		{
			if (m_MoveMap[i].m_pMesh && m_MoveMap[i].m_bActive)
				m_MoveMap[i].m_pMesh->Render(m_MoveMap[i].m_pColMesh->m_mWorld, GameDevice()->m_mView, GameDevice()->m_mProj, GameDevice()->m_vLightDir, GameDevice()->m_vEyePt);
		}

	}
}

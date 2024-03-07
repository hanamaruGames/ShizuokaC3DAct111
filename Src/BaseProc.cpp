//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�P                             ver 3.2        2023.1.31
//
//		��{�v���V�[�W���E��{�I�u�W�F�N�g�N���X����
//																BaseProc.cpp
//=============================================================================
#include  "BaseProc.h"

//------------------------------------------------------------------------
//
//	��{�v���V�[�W���N���X�̃f�X�g���N�^	
//  �i�S�Ẵv���V�[�W����I�u�W�F�N�g��ǂ݉����č폜����j
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CBaseProc::~CBaseProc()
{
	// ���b�V���|�C���^�z��̍폜                     // -- 2022.12.20
	for (DWORD i = 0; i < m_pMeshArray.size(); i++)
	{
		SAFE_DELETE(m_pMeshArray[i]);
	}
	// �v���V�[�W���|�C���^�z��̍폜
	for (DWORD i = 0; i < m_pProcArray.size(); i++)
	{
		SAFE_DELETE(m_pProcArray[i]);
	}
	// �I�u�W�F�N�g�|�C���^�z��̍폜
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		SAFE_DELETE(m_pObjArray[i]);
	}
}
//------------------------------------------------------------------------
//
//	��{�v���V�[�W���N���X�̑S�̍X�V����	
//  �i�S�Ẵv���V�[�W����I�u�W�F�N�g��ǂ݉����čX�V����������j
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
void CBaseProc::UpdateAll()
{

	Update();                              // �v���V�[�W���̍X�V����
	if (m_nWaitTime > 0) m_nWaitTime--;    // �E�F�C�g�^�C�}�[�̃J�E���g�_�E��

	// �I�u�W�F�N�g�|�C���^�z��̍X�V
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		m_pObjArray[i]->Update();          // �I�u�W�F�N�g�̍X�V����
	}

	// ���ʂ̃v���V�[�W���|�C���^�z��̍X�V
	for (DWORD i = 0; i < m_pProcArray.size(); i++)
	{
		m_pProcArray[i]->UpdateAll();      // ���ʂ̃v���V�[�W���̑S�̍X�V�����i�ċA�����j
	}

}
//============================================================================   // -- 2022.12.20
//   
//	���b�V���|�C���^�̃A�h���X��Ԃ�
//   
//	�����@	int idx  ���b�V���|�C���^�z��̓Y��
//
//	�߂�l  ���b�V���|�C���^�̃A�h���X
//============================================================================
CFbxMesh* CBaseProc::GetMesh(int idx)
{
	if (idx < 0 || idx >= m_pMeshArray.size())
	{
		MessageBox(NULL, _T("�� GetMesh( idx) ��"), _T("�w��v�f�ԍ��̃��b�V��������܂���"), MB_OK);
		return NULL;
	}
	return m_pMeshArray[idx];
}
//============================================================================   // -- 2022.12.20
//   
//	��Ɏ��A�C�e���̒l��Ԃ�
//   
//	�����@	int idx  ��Ɏ��A�C�e���z��̓Y��
//
//	�߂�l  ��Ɏ��A�C�e���̒l
//============================================================================
BASEHOLDITEM  CBaseProc::GetHoldItem(int idx)
{
	BASEHOLDITEM nullHI = {};

	if (idx < 0 || idx >= m_HoldItemArray.size())
	{
		MessageBox(NULL, _T("�� GetHoldItem( idx) ��"), _T("�w��v�f�ԍ��̎�Ɏ��A�C�e��������܂���"), MB_OK);
		return nullHI;
	}
	return m_HoldItemArray[idx];
}

//-----------------------------------------------------------------------------
// ��{�v���V�[�W���N���X�̂����蔻��(�ړ�����)
//
// �E�S�Ă̑���v���V�[�W���Ƒ���I�u�W�F�N�g��ǂ݉���
// �E���I�u�W�F�N�g�̃o�E���f�B���O�{�b�N�X�Ƒ���̈ړ������Ƃ̂����蔻�菈��������
//
//   CBaseObj* pOtherObj    ����̃I�u�W�F�N�g
//   VECTOR3 vNow       ����̌��݈ʒu
//   VECTOR3 vOld       ����̈�O�̈ʒu
//
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F�q�b�g���Ă��Ȃ��Ƃ�
//
//   ���茋�ʁ@�@
//           �q�b�g�����Ƃ��́@�@�@�@����Ǝ����̃I�u�W�F�N�g��m_pHitObj��m_vHitPos��m_vHitNormal�ɒl���Z�b�g
//                                   ����Ǝ����I�u�W�F�N�g��m_dwStatus��DAMAGE��ݒ肷��
//           �q�b�g���Ă��Ȃ��Ƃ��́@����Ǝ����̃I�u�W�F�N�g��m_pHitObj��NULL���Z�b�g
//
//-----------------------------------------------------------------------------
BOOL   CBaseProc::Hitcheck(CBaseObj* pOtherObj, VECTOR3 vNow, VECTOR3 vOld)
{
	BOOL  bRet = FALSE;

	// �S�Ă̑���Ƃ̂����蔻��
	for (DWORD i = 0; i < m_pObjArray.size(); i++)  // �S�Ă̑���I�u�W�F�N�g
	{
		bRet = m_pObjArray[i]->Hitcheck(pOtherObj, vNow, vOld);  // ����I�u�W�F�N�g�Ƃ̂����蔻��
		if (bRet) return bRet;
	}

	for (DWORD i = 0; i < m_pProcArray.size(); i++)  // ���ʂ̑���v���V�[�W��
	{
		bRet = m_pProcArray[i]->Hitcheck(pOtherObj, vNow, vOld);  // ����v���V�[�W���Ƃ̂����蔻��
		if (bRet) return bRet;
	}

	return bRet;
}

//-----------------------------------------------------------------------------
// ��{�v���V�[�W���N���X�̂����蔻��i�o�E���f�B���O�{�b�N�X�j
//
// �E�S�Ă̑���v���V�[�W���Ƒ���I�u�W�F�N�g��ǂ݉���
// �E���I�u�W�F�N�g�̃o�E���f�B���O�{�b�N�X�Ƒ���̍U���o�E���f�B���O�{�b�N�X�Ƃ̂����蔻��
//
//   CBaseObj* pOtherObj      ����̃I�u�W�F�N�g
//   CBBox*    pAttackBBox    �ΏۂƂȂ�o�E���f�B���O�{�b�N�X
//
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F�q�b�g���Ă��Ȃ��Ƃ�
//
//   ���茋�ʁ@�@
//           �q�b�g�����Ƃ��́@�@�@�@����Ǝ����̃I�u�W�F�N�g��m_pHitObj��m_vHitPos��m_vHitNormal�ɒl���Z�b�g
//                                   ����Ǝ����̃I�u�W�F�N�g��m_dwStatus��DAMAGE��ݒ肷��
//           �q�b�g���Ă��Ȃ��Ƃ��́@����Ǝ����̃I�u�W�F�N�g��m_pHitObj��NULL���Z�b�g
//
//-----------------------------------------------------------------------------
BOOL   CBaseProc::Hitcheck(CBaseObj* pOtherObj, CBBox* pBBoxAtack)
{
	BOOL  bRet = FALSE;

	// �S�Ă̑���Ƃ̂����蔻��
	for (DWORD i = 0; i < m_pObjArray.size(); i++)  // �S�Ă̑���I�u�W�F�N�g
	{
		bRet = m_pObjArray[i]->Hitcheck(pOtherObj, pBBoxAtack);  // ����I�u�W�F�N�g�Ƃ̂����蔻��
		if (bRet) return bRet;
	}

	for (DWORD i = 0; i < m_pProcArray.size(); i++)  // ���ʂ̑���v���V�[�W��
	{
		bRet = m_pProcArray[i]->Hitcheck(pOtherObj, pBBoxAtack);  // ����v���V�[�W���Ƃ̂����蔻��
		if (bRet) return bRet;
	}

	return bRet;
}

//============================================================================
//   
//	�v���V�[�W���ƃI�u�W�F�N�g��T�����S�ẴI�u�W�F�N�g���m���A�N�e�B�u�ɂ���
//   
//	�����@	�Ȃ�
//
//	�߂�l  �Ȃ�
//============================================================================
void  CBaseProc::SetNonActive()
{

	// �G�̃I�u�W�F�N�g�|�C���^�z��̒T��
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		m_pObjArray[i]->SetActive(FALSE);   // �A�N�e�B�u�t���O��FALSE��
		m_pObjArray[i]->ResetStatus();      // �e��X�e�[�^�X�����Z�b�g
	}

	// ���ʂ̃v���V�[�W���|�C���^�z��̒T��
	for (DWORD i = 0; i < m_pProcArray.size(); i++)
	{
		m_pProcArray[i]->SetMaxWaitTime();    // �E�F�C�g�^�C�����Z�b�g����
		m_pProcArray[i]->SetNonActive();      // ���ʂ̃v���V�[�W���̏����i�ċA�����j
	}
}


//------------------------------------------------------------------------  // -- 2022.2.16
//
//	��{�I�u�W�F�N�g�N���X�̃R���X�g���N�^	
//
//  �����@CBaseProc* pProc   // �e�̃v���V�[�W��
//
//------------------------------------------------------------------------
CBaseObj::CBaseObj(CBaseProc* pProc)
{
	m_pGMain = pProc->GetGMain();		// �Q�[�����C���N���X
	m_pProc  = pProc;					// �e�̃v���V�[�W��
	ResetStatus();						// �e��X�e�[�^�X�����Z�b�g
	m_bActive = FALSE;					// TRUE:�\��  FALSE:��\��
	m_dwObjID = pProc->GetProcID();		// �I�u�W�F�N�g�h�c
	m_dwObjNo = pProc->GetObjArrayPtr().size();	// �I�u�W�F�N�g�m�n  �v�b�V���o�b�N�O�̔z��T�C�Y���I�u�W�F�N�g�m�n�ƂȂ�
	m_nMeshIdx = 0;						// ���b�V���z��̓Y��           // -- 2022.12.20
	m_pBBox = NULL;						// �o�E���f�B���O�{�b�N�X�N���X
	m_mWorld = XMMatrixIdentity();		// ���[���h�}�g���N�X
	m_mWorldOld = XMMatrixIdentity();	// ���[���h�}�g���N�X�i��O�j
	m_vPosUp = VECTOR3(0, 0, 0);		// �ړ�����
	m_vRotUp = VECTOR3(0, 0, 0);		// ��]����
	m_fJumpY = 0.0f;					// �W�����v����
	m_fJumpTime = 0.0f;					// �W�����v����
	m_pOyaObj = 0;						// �e�I�u�W�F�N�g�i����I�u�W�F���j
	m_pHitObj = 0;						// ������������̃I�u�W�F�N�g
	m_vHitPos = VECTOR3(0, 0, 0);		// ���������ꏊ�̍��W
	m_vHitNormal = VECTOR3(0, 0, 0);	// ���������ꏊ�̖@�����W
	m_nCnt1 = 0;						// �J�E���^�[�P
	m_nCnt2 = 0;						// �J�E���^�[�Q
	m_nMaxHp = 0;						// �ő�̗�
	m_nHp = 0;							// �̗�
	m_nAtc = 0;							// �U����

	m_AnimStatus.playAnim = true;		// �A�j���[�V�����𓮍삳����
}
//------------------------------------------------------------------------
//
//	��{�I�u�W�F�N�g�N���X�̃f�X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CBaseObj::~CBaseObj()
{
	SAFE_DELETE(m_pBBox);
}
//============================================================================   // -- 2022.12.20
//   
//	�e�v���V�[�W���̃��b�V���|�C���^�z��[m_nMeshIdx]�̃A�h���X��Ԃ�
//   
//	�����@	�Ȃ�
//
//	�߂�l  ���b�V���|�C���^�̃A�h���X
//============================================================================
CFbxMesh* CBaseObj::GetMesh()
{
	return m_pProc->GetMesh(m_nMeshIdx);
}
//============================================================================   // -- 2022.12.20
//   
//	�e�v���V�[�W���̎�Ɏ��A�C�e���z��[m_nMeshIdx]��Ԃ�
//   
//	�����@	�Ȃ�
//
//	�߂�l  ��Ɏ��A�C�e��
//============================================================================
BASEHOLDITEM CBaseObj::GetHoldItem()
{
	return m_pProc->GetHoldItem(m_nMeshIdx);
}


//-----------------------------------------------------------------------------
//
// ��{�I�u�W�F�N�g�N���X�̂����蔻��(�ړ�����)
//
// �E���I�u�W�F�N�g�̃o�E���f�B���O�{�b�N�X�Ƒ���̈ړ������Ƃ̂����蔻��
//
//   CBaseObj* pOtherObj  ����̃I�u�W�F�N�g
//   VECTOR3 vNow     ����̌��݈ʒu
//   VECTOR3 vOld     ����̈�O�̈ʒu
//
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F�q�b�g���Ă��Ȃ��Ƃ�
//
//   ���茋�ʁ@�@
//           �q�b�g�����Ƃ��́@�@�@�@����ƓG�̃I�u�W�F�N�g��m_pHitObj��m_vHitPos��m_vHitNormal�ɒl���Z�b�g
//                                   �G�I�u�W�F�N�g��m_dwStatus��DAMAGE��ݒ肷��
//           �q�b�g���Ă��Ȃ��Ƃ��́@����ƓG�̃I�u�W�F�N�g��m_pHitObj��NULL���Z�b�g
//
//-----------------------------------------------------------------------------
BOOL   CBaseObj::Hitcheck(CBaseObj* pOtherObj, VECTOR3 vNow, VECTOR3 vOld)
{
	BOOL bRet = FALSE;
	VECTOR3 vHit = VECTOR3(0.0f, 0.0f, 0.0f), vNrm = VECTOR3(0.0f, 1.0f, 0.0f);

	// �o�E���f�B���O�{�b�N�X�ƈړ������iLay�j�ɂ�锻��
	if ((m_bActive && m_dwStatus != DAMAGE && m_dwStatus != DEAD && m_dwStatus != FLASH && this != pOtherObj) &&
		m_pBBox->OBBCollisionLay(vNow, vOld, &vHit, &vNrm))
	{
		m_pHitObj = pOtherObj;
		pOtherObj->m_pHitObj = this;
		m_vHitPos = vHit;
		m_vHitNormal = vNrm;
		pOtherObj->m_vHitPos = vHit;
		pOtherObj->m_vHitNormal = vNrm;
		m_dwStatus = DAMAGE;
		pOtherObj->m_dwStatus = DAMAGE;
		bRet = TRUE;
	}
	return bRet;
}
//-----------------------------------------------------------------------------
//
// ��{�I�u�W�F�N�g�N���X�̂����蔻��i�o�E���f�B���O�{�b�N�X�j
//
// �E���I�u�W�F�N�g�̃o�E���f�B���O�{�b�N�X�Ƒ���̃o�E���f�B���O�{�b�N�X�Ƃ̂����蔻��
//
//   CBaseObj* pOtherObj  ����̃I�u�W�F�N�g
//   CBBox*      pBBoxAtack   �o�E���f�B���O�{�b�N�X�̔��������Ƃ�
//
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F�q�b�g���Ă��Ȃ��Ƃ�
//
//   ���茋�ʁ@�@
//           �q�b�g�����Ƃ��́@�@�@�@����ƓG�̃I�u�W�F�N�g��m_pHitObj��m_vHitPos��m_vHitNormal�ɒl���Z�b�g
//                                   �G�I�u�W�F�N�g��m_dwStatus��DAMAGE��ݒ肷��
//           �q�b�g���Ă��Ȃ��Ƃ��́@����ƓG�̃I�u�W�F�N�g��m_pHitObj��NULL���Z�b�g
//
//-----------------------------------------------------------------------------
BOOL   CBaseObj::Hitcheck(CBaseObj* pOtherObj, CBBox* pBBoxAtack)
{
	BOOL bRet = FALSE;
	VECTOR3 vHit = VECTOR3(0.0f, 0.0f, 0.0f), vNrm = VECTOR3(0.0f, 1.0f, 0.0f);

	// �o�E���f�B���O�{�b�N�X���m�ɂ�锻��
	if ((m_bActive && m_dwStatus != DAMAGE && m_dwStatus != DEAD && m_dwStatus != FLASH && this != pOtherObj) &&
		m_pBBox->OBBCollisionDetection(pBBoxAtack, &vHit, &vNrm))
	{
		m_pHitObj = pOtherObj;
		pOtherObj->m_pHitObj = this;
		m_vHitPos = vHit;
		m_vHitNormal = vNrm;
		pOtherObj->m_vHitPos = vHit;
		pOtherObj->m_vHitNormal = vNrm;
		m_dwStatus = DAMAGE;
		pOtherObj->m_dwStatus = DAMAGE;
		bRet = TRUE;
	}
	return bRet;
}

//-----------------------------------------------------------------------------  // -- 2023.1.14
// �ړI�n�ivTargetX,Z�j�ւ̈ړ�����  �ėp�֐�
//
//   ����
//               VECTOR3           :vTarget :�s����
//               float fSpeedIn    :���̈ړ���
//               float fRotSpeed   :���̉�]�X�s�[�h�B�傫���قǉs�p�ŋȂ���(�ȗ��l��3.0f)
//               float fNearLimit  :�ړI�n�Ƃ̋ߐڃ��~�b�g�B���̔��a�͈͓��ɓ������Ƃ������Ƃ���(�ȗ��l��0.1f)
//
//   �߂�l�@�F�@TRUE�F�ړI�n�ɒB�����@�@FALSE:�܂��ړI�n�ɒB���Ă��Ȃ�
//               ������Am_vPosUp, m_vRotUp�Ɉړ��ʂ��ݒ肳���
//-----------------------------------------------------------------------------
BOOL CBaseObj::TargetMove(VECTOR3 vTarget, float fSpeedIn, float fRotSpeed, float fNearLimit)
{
	BOOL ret = FALSE;
	VECTOR3 vMove, vObjPos, vObjPosOld;
	float fLen, fSpeed;

	vObjPos = GetPositionVector(m_mWorld);
	vObjPosOld = GetPositionVector(m_mWorldOld);

	vTarget.y = m_mWorld._42;		// �^�[�Q�b�g�̓I�u�W�F�N�g�Ɠ��ꍂ���Ƃ���

	if ((vObjPos.x <= vTarget.x + fNearLimit && vObjPos.x >= vTarget.x - fNearLimit) &&		// �ړI�n�ɋߐڂ����Ƃ�
		(vObjPos.z <= vTarget.z + fNearLimit && vObjPos.z >= vTarget.z - fNearLimit))
	{  // �ړI�n�ɒB�����Ƃ�
		m_vPosUp.x = 0;
		m_vPosUp.y = 0;
		m_vPosUp.z = 0;
		m_vRotUp = VECTOR3(0, 0, 0);
		ret = TRUE; // �ړI�n�ɒB����

	}
	else {    // �ړI�n�ւ̈ړ�����

		vMove = vTarget - vObjPos;
		fLen = magnitude(vMove);
		if (fLen < fSpeedIn)
		{
			fSpeed = fSpeedIn - fLen;
		}
		else {
			fSpeed = fSpeedIn;
		}

		m_vRotUp.y = GetTargetRotateVector(m_mWorld, vTarget).y;	// �^�[�Q�b�g�̕�������������Y���p�x�����߂�
		if (m_vRotUp.y >= 180) m_vRotUp.y -= 360;
		if (m_vRotUp.y <= -180) m_vRotUp.y += 360;
		if (m_vRotUp.y >  fRotSpeed) m_vRotUp.y = fRotSpeed;		// fRotSpeed�x�ȏ�̕����ϊ��͍s��Ȃ�
		if (m_vRotUp.y < -fRotSpeed) m_vRotUp.y = -fRotSpeed;		// fRotSpeed�x�ȏ�̕����ϊ��͍s��Ȃ�

		m_vPosUp.x = 0;
		//m_vPosUp.y = -0.01f;		// �������֏d��
		m_vPosUp.y = 0;
		m_vPosUp.z = fSpeed;

		ret = FALSE;    // �܂��ړI�n�ɒB���Ă��Ȃ�
	}

	return ret;
}
//-----------------------------------------------------------------------------  // -- 2018.8.2
// �I�u�W�F�N�g��mWorld�ƈ����ʒu�Ƃ̋��������߂�
//
//   �����@�@�F�@vPos :�ʒu
//   �߂�l�@�F�@����
//-----------------------------------------------------------------------------
float CBaseObj::GetDistance(VECTOR3 vPos)
{
	VECTOR3 vVec;
	vVec = vPos - GetPositionVector(m_mWorld);

	return  magnitude(vVec);
}
//-----------------------------------------------------------------------------  // -- 2019.6.8
// �X�e�[�^�X�����Z�b�g����
//
//   �����@�@�F�@�Ȃ�
//   �߂�l�@�F�@�Ȃ�
//-----------------------------------------------------------------------------
void CBaseObj::ResetStatus()
{
	m_dwStatus = NORMAL;			// �X�e�[�^�X
	m_dwStatusSub = ATTACKNONE;		// �X�e�[�^�X�T�u
	m_dwStatusPhase = 0;			// �X�e�[�^�X�t�F�[�Y
}

//============================================================================
//  �I�u�W�F�N�g���m���d�Ȃ�Ȃ��悤�ɂ��郁���o�֐�
//
//	�����@	CBaseProc* pProj�@�ΏۂƂ����{�v���V�[�W��
//
//	�߂�lCBaseObj* 	�I�u�W�F�N�g�A�h���X:�����ړ��̑���I�u�W�F�N�g�@NULL:�ڋ��������Ă��Ȃ�
//============================================================================
CBaseObj*  CBaseObj::SetKeepOffset(CBaseProc* pProc)
{
	float	fMyRadius, fOtherRadius, fAddRadius, fLen, fMvMax = 0.0f;
	VECTOR3  vMy, vOther;
	VECTOR2  vMy2, vOther2;
	MATRIX4X4	 matWk1, matWk2;
	CBaseObj     *pOtherObj, *pTargetObj = NULL;
	CBBox		 *pOtherBBox;

	if (m_pBBox == NULL) return NULL;
	vMy = GetPositionVector(m_mWorld);
	vMy2.x = vMy.x;
	vMy2.y = vMy.z;

	// �����̔��a���o�E���f�B���O�{�b�N�X����Z�o����i�O�ƉE���̑傫�������̗p�j
	fMyRadius = (m_pBBox->m_vMax.x > m_pBBox->m_vMax.z) ? m_pBBox->m_vMax.x : m_pBBox->m_vMax.z;


	// �I�u�W�F�N�g�z��̒T��
	for (DWORD i = 0; i < pProc->GetObjArrayPtr().size(); i++)
	{
		pOtherObj = pProc->GetObjArrayPtr()[i];

		if (!pOtherObj->m_bActive) continue;	// ���ݐ����Ă��Ȃ���ΑΏۊO
		if (pOtherObj == this) continue;	// �������g�͑ΏۊO
		pOtherBBox = pOtherObj->m_pBBox;
		if (pOtherBBox == NULL) continue;	// �o�E���f�B���O�{�b�N�X���Ȃ���ΑΏۊO
		vOther = GetPositionVector(pOtherObj->m_mWorld);
		vOther2.x = vOther.x;
		vOther2.y = vOther.z;

		// �o�E���f�B���O�{�b�N�X���m�̍�������v���Ă��邩�B�͈͓��ɓ����Ă��Ȃ���ΑΏۊO
		if ((vMy.y + m_pBBox->m_vMin.y) > (vOther.y + pOtherObj->m_pBBox->m_vMax.y) ||
			(vMy.y + m_pBBox->m_vMax.y) < (vOther.y + pOtherObj->m_pBBox->m_vMin.y)) {
			continue;
		}

		// ����̔��a���o�E���f�B���O�{�b�N�X����Z�o����i�O�ƉE���̑傫�������̗p�j
		fOtherRadius = (pOtherBBox->m_vMax.x > pOtherBBox->m_vMax.z) ? pOtherBBox->m_vMax.x : pOtherBBox->m_vMax.z;

		fAddRadius = fMyRadius + fOtherRadius;
		if (fabs(vMy2.x - vOther2.x) < fAddRadius && fabs(vMy2.y - vOther2.y) < fAddRadius) {		// �܂��A���t�ɐ��������i�w�y�����j�Ŕ��a�͈͓̔��ɓ����Ă��邩
			fLen = magnitude(vMy2 - vOther2);		// ���������i�w�y�����j�Ŕ��a�̋������ɓ����Ă��邩
			if (fLen < fAddRadius) {
				fLen = fAddRadius - fLen;	// �������݋����ɂ���
				if (fLen > fMvMax) {		// ���܂ł̒��ŁA��Ԑڋ߂��Ă��邩
					fMvMax = fLen;
					pTargetObj = pOtherObj;
				}
			}
		}
	}

	if (pTargetObj) {	// ���a���ɓ��������肪�����ꍇ
		vOther = GetPositionVector(pTargetObj->m_mWorld);
		vOther.y = vMy.y;
		matWk1 = GetLookatMatrix( vMy, vOther);					// ����̕�������������}�g���b�N�X���쐬����
		matWk2 = XMMatrixTranslation(0.0f, 0.0f, -fMvMax);		// �������ݒl�����A�y�����̔��Ε����Ɉړ�����}�g���b�N�X���쐬����
		matWk1 = matWk2 * matWk1;								// �������ݒl�̔��Ε����Ɉړ�����
		vMy.x = 0.0f - vMy.x;
		vMy.y = 0.0f - vMy.y;
		vMy.z = 0.0f - vMy.z;
		matWk2 = XMMatrixTranslation(vMy.x, vMy.y, vMy.z);		// �����̈ʒu�̋t���̈ʒu
		matWk2 = m_mWorld * matWk2;								// �����̌��_�ʒu�ł̊p�x�݂̂ɂ���
		vMy = GetPositionVector(matWk1);						// �������ݒl�̔��Ε����Ɉړ������ʒu
		matWk1 = XMMatrixTranslation(vMy.x, vMy.y, vMy.z);		// �������ݒl�̔��Ε����Ɉړ������ʒu�݂̂̃}�g���b�N�X
		m_mWorld = matWk2 * matWk1;								// �����̐V�����ʒu�Ɗp�x�̃��[���h�}�g���b�N�X
	}


	// ���ʂ̃v���V�[�W���z��̒T��
	if (pTargetObj == NULL)
	{
		for (DWORD i = 0; i < pProc->GetProcArrayPtr().size(); i++)
		{
			pTargetObj = SetKeepOffset(pProc->GetProcArrayPtr()[i]);      // ���ʂ̃v���V�[�W���̏����i�ċA�����j
			if (pTargetObj) break;
		}
	}

	return pTargetObj;
}



//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�P                             ver 3.2        2023.1.31
//
//		��{�v���V�[�W���E��{�I�u�W�F�N�g�N���X����
//																BaseProc.cpp
//=============================================================================
#include "BaseProc.h"
#include "BBox.h"
#include "FbxMesh.h"
#include "FbxMeshAnim.h"
#include "GameMain.h"

CBaseProc::CBaseProc()
{
	m_pMeshArray.clear();
	m_pObjArray.clear();
}

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
	// �I�u�W�F�N�g�|�C���^�z��̍폜
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		SAFE_DELETE(m_pObjArray[i]);
	}
}
void CBaseProc::Draw()
{
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		m_pObjArray[i]->Draw();          // �I�u�W�F�N�g�̍X�V����
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

//	Update();                              // �v���V�[�W���̍X�V����

	// �I�u�W�F�N�g�|�C���^�z��̍X�V
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		m_pObjArray[i]->Update();          // �I�u�W�F�N�g�̍X�V����
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
		MessageBox(nullptr, _T("�� GetMesh( idx) ��"), _T("�w��v�f�ԍ��̃��b�V��������܂���"), MB_OK);
		return nullptr;
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
	BASEHOLDITEM nullptrHI = {};

	if (idx < 0 || idx >= m_HoldItemArray.size())
	{
		MessageBox(nullptr, _T("�� GetHoldItem( idx) ��"), _T("�w��v�f�ԍ��̎�Ɏ��A�C�e��������܂���"), MB_OK);
		return nullptrHI;
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
//   �߂�l�@bool
//           true:�q�b�g�����Ƃ�       false�F�q�b�g���Ă��Ȃ��Ƃ�
//
//   ���茋�ʁ@�@
//           �q�b�g�����Ƃ��́@�@�@�@����Ǝ����̃I�u�W�F�N�g��m_pHitObj��m_vHitPos��m_vHitNormal�ɒl���Z�b�g
//                                   ����Ǝ����I�u�W�F�N�g��m_dwStatus��DAMAGE��ݒ肷��
//           �q�b�g���Ă��Ȃ��Ƃ��́@����Ǝ����̃I�u�W�F�N�g��m_pHitObj��nullptr���Z�b�g
//
//-----------------------------------------------------------------------------
bool   CBaseProc::Hitcheck(CBaseObj* pOtherObj, VECTOR3 vNow, VECTOR3 vOld)
{
	bool  bRet = false;

	// �S�Ă̑���Ƃ̂����蔻��
	for (DWORD i = 0; i < m_pObjArray.size(); i++)  // �S�Ă̑���I�u�W�F�N�g
	{
		bRet = m_pObjArray[i]->Hitcheck(pOtherObj, vNow, vOld);  // ����I�u�W�F�N�g�Ƃ̂����蔻��
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
//   �߂�l�@bool
//           true:�q�b�g�����Ƃ�       false�F�q�b�g���Ă��Ȃ��Ƃ�
//
//   ���茋�ʁ@�@
//           �q�b�g�����Ƃ��́@�@�@�@����Ǝ����̃I�u�W�F�N�g��m_pHitObj��m_vHitPos��m_vHitNormal�ɒl���Z�b�g
//                                   ����Ǝ����̃I�u�W�F�N�g��m_dwStatus��DAMAGE��ݒ肷��
//           �q�b�g���Ă��Ȃ��Ƃ��́@����Ǝ����̃I�u�W�F�N�g��m_pHitObj��nullptr���Z�b�g
//
//-----------------------------------------------------------------------------
bool   CBaseProc::Hitcheck(CBaseObj* pOtherObj, CBBox* pBBoxAtack)
{
	bool  bRet = false;

	// �S�Ă̑���Ƃ̂����蔻��
	for (DWORD i = 0; i < m_pObjArray.size(); i++)  // �S�Ă̑���I�u�W�F�N�g
	{
		bRet = m_pObjArray[i]->Hitcheck(pOtherObj, pBBoxAtack);  // ����I�u�W�F�N�g�Ƃ̂����蔻��
		if (bRet) return bRet;
	}

//	for (DWORD i = 0; i < m_pProcArray.size(); i++)  // ���ʂ̑���v���V�[�W��
//	{
//		bRet = m_pProcArray[i]->Hitcheck(pOtherObj, pBBoxAtack);  // ����v���V�[�W���Ƃ̂����蔻��
//		if (bRet) return bRet;
//	}

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
		m_pObjArray[i]->SetActive(false);   // �A�N�e�B�u�t���O��false��
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
	m_pProc  = pProc;					// �e�̃v���V�[�W��
	m_bActive = false;					// true:�\��  false:��\��
	m_nMeshIdx = 0;						// ���b�V���z��̓Y��           // -- 2022.12.20
	m_pBBox = nullptr;						// �o�E���f�B���O�{�b�N�X�N���X
	m_mWorld = XMMatrixIdentity();		// ���[���h�}�g���N�X
	m_mWorldOld = XMMatrixIdentity();	// ���[���h�}�g���N�X�i��O�j
	m_pHitObj = 0;						// ������������̃I�u�W�F�N�g
	m_vHitPos = VECTOR3(0, 0, 0);		// ���������ꏊ�̍��W
	m_vHitNormal = VECTOR3(0, 0, 0);	// ���������ꏊ�̖@�����W
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
//   �߂�l�@bool
//           true:�q�b�g�����Ƃ�       false�F�q�b�g���Ă��Ȃ��Ƃ�
//
//   ���茋�ʁ@�@
//           �q�b�g�����Ƃ��́@�@�@�@����ƓG�̃I�u�W�F�N�g��m_pHitObj��m_vHitPos��m_vHitNormal�ɒl���Z�b�g
//                                   �G�I�u�W�F�N�g��m_dwStatus��DAMAGE��ݒ肷��
//           �q�b�g���Ă��Ȃ��Ƃ��́@����ƓG�̃I�u�W�F�N�g��m_pHitObj��nullptr���Z�b�g
//
//-----------------------------------------------------------------------------
bool   CBaseObj::Hitcheck(CBaseObj* pOtherObj, VECTOR3 vNow, VECTOR3 vOld)
{
	bool bRet = false;
	VECTOR3 vHit = VECTOR3(0.0f, 0.0f, 0.0f), vNrm = VECTOR3(0.0f, 1.0f, 0.0f);

	// �o�E���f�B���O�{�b�N�X�ƈړ������iLay�j�ɂ�锻��
	if ((m_bActive && this != pOtherObj) &&
		m_pBBox->OBBCollisionLay(vNow, vOld, &vHit, &vNrm))
	{
		m_pHitObj = pOtherObj;
		pOtherObj->m_pHitObj = this;
		m_vHitPos = vHit;
		m_vHitNormal = vNrm;
		pOtherObj->m_vHitPos = vHit;
		pOtherObj->m_vHitNormal = vNrm;
		OnCollision(pOtherObj);
		pOtherObj->OnCollision(this);
		bRet = true;
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
//   �߂�l�@bool
//           true:�q�b�g�����Ƃ�       false�F�q�b�g���Ă��Ȃ��Ƃ�
//
//   ���茋�ʁ@�@
//           �q�b�g�����Ƃ��́@�@�@�@����ƓG�̃I�u�W�F�N�g��m_pHitObj��m_vHitPos��m_vHitNormal�ɒl���Z�b�g
//                                   �G�I�u�W�F�N�g��m_dwStatus��DAMAGE��ݒ肷��
//           �q�b�g���Ă��Ȃ��Ƃ��́@����ƓG�̃I�u�W�F�N�g��m_pHitObj��nullptr���Z�b�g
//
//-----------------------------------------------------------------------------
bool   CBaseObj::Hitcheck(CBaseObj* pOtherObj, CBBox* pBBoxAtack)
{
	bool bRet = false;
	VECTOR3 vHit = VECTOR3(0.0f, 0.0f, 0.0f), vNrm = VECTOR3(0.0f, 1.0f, 0.0f);

	// �o�E���f�B���O�{�b�N�X���m�ɂ�锻��
	if ((m_bActive && this != pOtherObj) &&
		m_pBBox->OBBCollisionDetection(pBBoxAtack, &vHit, &vNrm))
	{
		m_pHitObj = pOtherObj;
		pOtherObj->m_pHitObj = this;
		m_vHitPos = vHit;
		m_vHitNormal = vNrm;
		pOtherObj->m_vHitPos = vHit;
		pOtherObj->m_vHitNormal = vNrm;
		OnCollision(pOtherObj);
		pOtherObj->OnCollision(this);
		bRet = true;
	}
	return bRet;
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

//============================================================================
//  �I�u�W�F�N�g���m���d�Ȃ�Ȃ��悤�ɂ��郁���o�֐�
//
//	�����@	CBaseProc* pProj�@�ΏۂƂ����{�v���V�[�W��
//
//	�߂�lCBaseObj* 	�I�u�W�F�N�g�A�h���X:�����ړ��̑���I�u�W�F�N�g�@nullptr:�ڋ��������Ă��Ȃ�
//============================================================================
CBaseObj*  CBaseObj::SetKeepOffset(CBaseProc* pProc)
{
	float	fMyRadius, fOtherRadius, fAddRadius, fLen, fMvMax = 0.0f;
	VECTOR3  vMy, vOther;
	VECTOR2  vMy2, vOther2;
	MATRIX4X4	 matWk1, matWk2;
	CBaseObj     *pOtherObj, *pTargetObj = nullptr;
	CBBox		 *pOtherBBox;

	if (m_pBBox == nullptr) return nullptr;
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
		if (pOtherBBox == nullptr) continue;	// �o�E���f�B���O�{�b�N�X���Ȃ���ΑΏۊO
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
//	if (pTargetObj == nullptr)
//	{
//		for (DWORD i = 0; i < pProc->GetProcArrayPtr().size(); i++)
//		{
//			pTargetObj = SetKeepOffset(pProc->GetProcArrayPtr()[i]);      // ���ʂ̃v���V�[�W���̏����i�ċA�����j
//			if (pTargetObj) break;
//		}
//	}

	return pTargetObj;
}



//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�P                             ver 3.2        2023.1.31
//
//		�J��������
//
//		(���_�ύX�����E��Q����������������Ă���)
//
//																Camera.cpp
//=============================================================================
#include  "Camera.h"
#include  "Playchar.h"
#include  "Map.h"

//==========================================================================================================================
//
// �J�����v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// -------------------------------------------------------------------------------------------------------------------------
CCameraProc::CCameraProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_nCamObjNo = 0;    // �I������J�����I�u�W�F�N�g�m�n�����l�O

	// -------------------------------------------------------------------------------------
	// �I�u�W�F�N�g�̐���
	// 
	// -------------------------------------------------------------------------------------
	// �J�����I�u�W�F�N�g[0]     Ctrl:0 TPS
	m_pObjArray.push_back(new CCameraObj(this));     // m_pObjArray�ɃI�u�W�F�N�g��o�^����
	((CCameraObj*)m_pObjArray.back())->InitCam(      // �I�u�W�F�N�g�ɏ����l��ݒ肷��
		0,                                           // �J��������i0:TPS)
		VECTOR3(0.0f, 2.0f, 0.0f),                   // TPS ������_
		VECTOR3(0.0f, 2.2f, -6.7f),                  // TPS ����_
		1.5f,                                        // �J������]�����l
		0.05f                                        // �J�����ړ������l
	);

}
// ---------------------------------------------------------------------------
//
// �J�����v���V�[�W���̍X�V����
//
//
// ---------------------------------------------------------------------------
void CCameraProc::Update()
{
	// �J��������̕ύX
	// �\������I�u�W�F�N�g��؂�ւ���
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_F)) // F�L�[
	{
		m_nCamObjNo = (m_nCamObjNo + 1) % m_pObjArray.size();   // �\������I�u�W�F�N�g��؂�ւ���
		//((CCameraObj*)m_pObjArray[m_nCamObjNo])->SetCamBase();  // �J�����ψʏ����l��ݒ肷��
	}
}
//-----------------------------------------------------------------------------
// �J�����v���V�[�W������J�����I�u�W�F�N�g�̊�l�ɏ����l��ݒ肷�鏈��
//
// �E�J��������A����[�J���x�N�g���A�����l�Ȃǂ��J�����I�u�W�F�N�g�ɐݒ肷�鏈��
//   ���̏����̓I�u�W�F�N�g��InitCam()���g�p���Đݒ肷��
//
//   ����
//      int no           �I�u�W�F�N�g�m��
//      int ctrl         �J��������i0:�s�o�r���_  1:�e�o�r���_  2:�Œ莋�_�j
//      VECTOR3 lookat   ����[�J�������_�x�N�g��
//      VECTOR3 eye      ����[�J�����_�x�N�g��
//      float rot        �p�x����
//      float dis        �ړ�����
//
//-----------------------------------------------------------------------------
void CCameraProc::InitCam(int no, int ctrl, VECTOR3 lookat, VECTOR3 eye, float rot, float dist)
{
	if (no < 0 || no >= m_pObjArray.size())
	{
		MessageBox(nullptr, _T("�� InitCam( No,�@�E�E�E�E�E) ��"), _T("�w��v�f�ԍ��̃I�u�W�F�N�g������܂���"), MB_OK);
		return;
	}

	((CCameraObj*)m_pObjArray[no])->InitCam(ctrl, lookat, eye, rot, dist);
}

// ============================================================================================================
// ---------------------------------------------------------------------------
//
// �J�����I�u�W�F�N�g�̃R���X�g���N�^
//
// ---------------------------------------------------------------------------
CCameraObj::CCameraObj(CBaseProc* pProc) : CBaseObj(pProc)
{
	// ��_���[���h�}�g���b�N�X�̏����l
	m_mBaseWorld = XMMatrixTranslation(0, 0, 0);

}
// ---------------------------------------------------------------------------
//
// �J�����I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CCameraObj::~CCameraObj()
{
	;
}
//----------------------------------------------------------------------------- 
// �J�����I�u�W�F�N�g�̐���
//
//�@�o�b�̓����ɍ��킹�ăJ�����𐧌䂷��
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CCameraObj::Update()
{
	// �v���V�[�W���Ŏw�肵���I�u�W�F�N�g�m�n�̃I�u�W�F�N�g�̂ݏ������s��
	if (((CCameraProc*)m_pProc)->GetCamObjNo() != m_dwObjNo) return;

	// �����_�E���_�̊�_�ƂȂ��_���[���h�}�g���b�N�X�̐ݒ�
	if (m_nCtrl == 0)  // TPS
	{
		// TPS�́A�o�b�̃��[�J�����}�g���b�N�X��ݒ肷��
		m_mBaseWorld = m_pGMain->m_pPcProc->GetPcObjPtr()->GetLocalMatrix();
	}
	else if (m_nCtrl == 1) {  // FPS
		// FPS�́A�o�b�̃��[���h�}�g���b�N�X��ݒ肷��
		m_mBaseWorld = m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld();
	}
	else {  // �Œ�J����
		// �Œ�J�����͐�΍��W�̌��_��ݒ肷��
		m_mBaseWorld = XMMatrixTranslation(0, 0, 0);
	}

	// �J�����I�u�W�F�N�g�̈ʒu���蓮����
	ManualOperation();

	// �����_�̃x�N�g�����쐬���鏈��
	// (�����_�̃��[�J�����W�Ɗ�_���[���h�}�g���b�N�X���|�����킹�A�����_�}�g���b�N�X�𓾂�)
	MATRIX4X4 mLookat = XMMatrixTranslationFromVector(m_vLocalLookat) * m_mBaseWorld;
	m_pGMain->m_vLookatPt = GetPositionVector(mLookat);    // �����_�}�g���b�N�X���璍���_�ʒu�𓾂�

	// �J�����i���_�j�x�N�g�����쐬���鏈��
	// (�J�����i���_�j�̃��[�J�����W�Ɗ�_���[���h�}�g���b�N�X���|�����킹�A���_�}�g���b�N�X�𓾂�)
	MATRIX4X4 mEye = XMMatrixTranslationFromVector(m_vLocalEye) * m_mBaseWorld;
	m_pGMain->m_vEyePt = GetPositionVector(mEye);        // ���_�}�g���b�N�X���王�_�ʒu�𓾂�

	// TPS���_�̎��A��Q����������鏈��
	if (m_nCtrl == 0) EvasiveObstacle();

	// ���_�x�N�g���ƒ����_�x�N�g������J�����̃��[���h�}�g���b�N�X�𓾂�i���͎g�p���Ă��Ȃ��j
	m_mWorld = GetLookatMatrix(m_pGMain->m_vEyePt, m_pGMain->m_vLookatPt);

	// �r���[�}�g���b�N�X�̍쐬
	VECTOR3 vUpVec(0.0f, 1.0f, 0.0f);    // ����ʒu���΍��W�̏�����Ƃ���
	// �J����(���_)�̈ʒu�A������A����ђ����_���g�p���āA������W�n�̃r���[�s����쐬
	m_pGMain->m_mView = XMMatrixLookAtLH(m_pGMain->m_vEyePt, m_pGMain->m_vLookatPt, vUpVec);

	// �J�����̈ʒu�A������A����уJ�����̌������g�p���āA������W�n�̃r���[�s����쐬�i�g�p���Ă��Ȃ��j
	//VECTOR3 vEyeDir = XMVector3TransformCoord(VECTOR3(0, 0, 1), GetRotateMatrix(m_mWorld));
	//m_pGMain->m_mView = XMMatrixLookToLH(m_pGMain->m_vEyePt, vEyeDir, vUpVec);

	// ���C�g���_����̃r���[�g�����X�t�H�[���iShadowMap�p�j���C�g���_���o�b�̈ʒu�ɍ��킹��Ƃ��i�g�p���Ă��Ȃ��j
	//m_pGMain->m_vLightEye = m_pGMain->m_vLookatPt + m_pGMain->m_vLightDir * 100.0f;	        // �J�����i���_�j�ʒu�������̕���100���̈ʒu�ɂ���
	//m_pGMain->m_mLightView = XMMatrixLookAtLH(m_pGMain->m_vLightEye, m_pGMain->m_vLookatPt, vUpVec);

}

//-----------------------------------------------------------------------------
// �J�����I�u�W�F�N�g�̊�l�ɏ����l��ݒ肷�鏈��
//
// �E�J��������A����[�J���x�N�g���A�����l�Ȃǂ�ݒ肷�鏈��
//
//   ����
//      int ctrl         �J��������i0:�s�o�r���_  1:�e�o�r���_  2:�Œ莋�_�j
//      VECTOR3 lookat   ����[�J�������_�x�N�g��
//      VECTOR3 eye      ����[�J�����_�x�N�g��
//      float rot        �p�x����
//      float dis        �ړ�����
//
//-----------------------------------------------------------------------------
void CCameraObj::InitCam(int ctrl, VECTOR3 lookat, VECTOR3 eye, float rot, float dist)
{
	m_nCtrl = ctrl;
	m_vBaseLocalLookat = lookat;
	m_vBaseLocalEye = eye;
	m_fBaseRotUp = rot;
	m_fBaseDistUp = dist;

	SetCamBase();   // �J�����ψʏ����l��ݒ肷��
}
//-----------------------------------------------------------------------------
// ��Q����������鏈��
//
// �E���_�ƒ����_�Ƃ̊Ԃɏ�Q�����������ꍇ�A���_����Q���̑O�Ɉړ����鏈��
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CCameraObj::EvasiveObstacle()
{
	VECTOR3 vHit;
	VECTOR3 vNorm;
	if (m_pGMain->m_pMapProc->Hitcheck(m_pGMain->m_vEyePt, m_pGMain->m_vLookatPt, &vHit, &vNorm))   // ��Q���Ƃ̐ڐG�`�F�b�N
	{
		MATRIX4X4 mTemp;
		mTemp = GetLookatMatrix(vHit, m_pGMain->m_vLookatPt);        // ��Q���Ƃ̐ڐG�_���璍���ʒu������}�g���b�N�X
		mTemp = XMMatrixTranslation(0.0f, 0.0f, 0.01f) * mTemp;      // ��Q���Ƃ̐ڐG�_����1cm���������Ɉړ��������_�ʒu�𓾂�
		m_pGMain->m_vEyePt = GetPositionVector(mTemp);
	}
}
//----------------------------------------------------------------------------- 
// �J�����I�u�W�F�N�g�̎蓮���쐧��
//
//   �J�����I�u�W�F�N�g�̈ʒu���蓮�ő��삷��
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CCameraObj::ManualOperation()
{
	CDirectInput* pDI = m_pGMain->m_pDI;

	// �J�������_�̑��Έʒu�̕ύX
	if (m_nCtrl == 0)   // TPS���_�̎�
	{
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD6) || pDI->CheckKey(KD_DAT, DIK_RBRACKET)) // ��  ]
		{
			SetLocalEyeTPS(m_fBaseRotUp, 0, 0);
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD4) || pDI->CheckKey(KD_DAT, DIK_SEMICOLON)) // ��  ;
		{
			SetLocalEyeTPS(-m_fBaseRotUp, 0, 0);
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD8) || pDI->CheckKey(KD_DAT, DIK_AT)) // ��  @
		{
			SetLocalEyeTPS(0, m_fBaseRotUp, 0);
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD2) || pDI->CheckKey(KD_DAT, DIK_COLON)) // ��  :
		{
			SetLocalEyeTPS(0, -m_fBaseRotUp, 0);
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD7) || pDI->CheckKey(KD_DAT, DIK_P)) // �߂Â���  P
		{
			SetLocalEyeTPS(0, 0, -m_fBaseDistUp);
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD9) || pDI->CheckKey(KD_DAT, DIK_LBRACKET)) // ��������  [
		{
			SetLocalEyeTPS(0, 0, m_fBaseDistUp);
		}
	}
	else if (m_nCtrl == 1) {    // FPS���_�̎�

		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD6) || pDI->CheckKey(KD_DAT, DIK_RBRACKET)) // ��  ]
		{
			m_vLocalEye.x -= m_fBaseDistUp;
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD4) || pDI->CheckKey(KD_DAT, DIK_SEMICOLON)) // ��  ;
		{
			m_vLocalEye.x += m_fBaseDistUp;
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD8) || pDI->CheckKey(KD_DAT, DIK_AT)) // ��  @
		{
			m_vLocalLookat.y += m_fBaseDistUp;
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD2) || pDI->CheckKey(KD_DAT, DIK_COLON)) // ��  :
		{
			m_vLocalLookat.y -= m_fBaseDistUp;
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD7) || pDI->CheckKey(KD_DAT, DIK_P)) // �߂Â���  P
		{
			m_vLocalEye.z += m_fBaseDistUp;
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD9) || pDI->CheckKey(KD_DAT, DIK_LBRACKET)) // ��������  [
		{
			m_vLocalEye.z -= m_fBaseDistUp;
		}
	}
	else {    // �Œ�J�����̎�

		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD6) || pDI->CheckKey(KD_DAT, DIK_RBRACKET)) // �E�ړ�  ]
		{
			m_vLocalLookat.x += m_fBaseDistUp;
			m_vLocalEye.x += m_fBaseDistUp;
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD4) || pDI->CheckKey(KD_DAT, DIK_SEMICOLON)) // ���ړ�  ;
		{
			m_vLocalLookat.x -= m_fBaseDistUp;
			m_vLocalEye.x -= m_fBaseDistUp;
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD8) || pDI->CheckKey(KD_DAT, DIK_AT)) // �O�ړ�  @
		{
			m_vLocalLookat.z += m_fBaseDistUp;
			m_vLocalEye.z += m_fBaseDistUp;
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD2) || pDI->CheckKey(KD_DAT, DIK_COLON)) // ��ړ�  :
		{
			m_vLocalLookat.z -= m_fBaseDistUp;
			m_vLocalEye.z -= m_fBaseDistUp;
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD7) || pDI->CheckKey(KD_DAT, DIK_P)) // ��  P
		{
			m_vLocalLookat.x -= m_fBaseDistUp;
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD9) || pDI->CheckKey(KD_DAT, DIK_LBRACKET)) // ��  [
		{
			m_vLocalLookat.x += m_fBaseDistUp;
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD3) || pDI->CheckKey(KD_DAT, DIK_BACKSLASH)) // ��  �o�b�N�X���b�V��
		{
			m_vLocalLookat.z += m_fBaseDistUp;
		}
		if (pDI->CheckKey(KD_DAT, DIK_NUMPAD1) || pDI->CheckKey(KD_DAT, DIK_SLASH)) // ��  /
		{
			m_vLocalLookat.z -= m_fBaseDistUp;
		}
	}

	// ��l�ɖ߂�����
	if (pDI->CheckKey(KD_DAT, DIK_HOME) || pDI->CheckKey(KD_DAT, DIK_H))
	{
		SetCamBase();    // �J�����ψʏ����l��ݒ肷��
	}
}

//-----------------------------------------------------------------------------
// �s�o�r�̂Ƃ��J�����ʒu�̎蓮�ݒ菈��
//
//   m_vRotUp.x��m_vRotUp.y�ɉ�]�p�x�ψʒl�A
//   m_vPosUp.z�ɒ����_���王�_�܂ł̒��������ψʒl�������Ă���A
//   ���̒l����ɁA�ψʒl���v�Z���A���̌��ʂ�m_vLocalEye�ɐݒ肷��
//
//   ����	float fRotY : �x��]
//			float fRotX : �w��]
//			float fDist : ����
//
//   �߂�l�@�Ȃ�
//-----------------------------------------------------------------------------
void	CCameraObj::SetLocalEyeTPS(float fRotY, float fRotX, float fDist)
{
	m_vRotUp.x += fRotX;
	m_vRotUp.y += fRotY;
	m_vPosUp.z += fDist;

	MATRIX4X4 mRotY = XMMatrixRotationY(XMConvertToRadians(m_vRotUp.y));
	MATRIX4X4 mRotX = XMMatrixRotationX(XMConvertToRadians(m_vRotUp.x));
	m_vLocalEye = GetPositionVector(XMMatrixTranslationFromVector(m_vBaseLocalEye + m_vPosUp) * mRotX * mRotY);
}
//-----------------------------------------------------------------------------
// �J�����ψʏ����l��ݒ肷�鏈��
//
// �E����[�J���x�N�g�������[�J���x�N�g���ɐݒ肷��B
// �E�p�x�ƈʒu�̕ψʒl�̃N�����[
//
//   ����	�Ȃ�
//
//   �߂�l�@�Ȃ�
//-----------------------------------------------------------------------------
void	CCameraObj::SetCamBase()
{
	// �J�����ψʂ̏����l��ݒ肷��
	m_vLocalLookat = m_vBaseLocalLookat;      // ����[�J�������_�x�N�g�������[�J�������_�x�N�g���ɐݒ肷��
	m_vLocalEye = m_vBaseLocalEye;            // ����[�J�����_�x�N�g�������[�J�����_�x�N�g���ɐݒ肷��
	m_vRotUp = VECTOR3(0, 0, 0);     // �p�x�ψʒl�̃N�����[
	m_vPosUp = VECTOR3(0, 0, 0);     // �ʒu�ψʒl�̃N�����[

}
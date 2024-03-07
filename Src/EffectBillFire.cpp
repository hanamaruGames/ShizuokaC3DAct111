//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�P�@�@�@�@�@�@                 ver 3.2        2023.1.31
//
//		�r���{�[�h���̏���
//															EffectBillFire.cpp
//=============================================================================
#include  "EffectBillFire.h"

//------------------------------------------------------------------------
//
//	�r���{�[�h�@���v���V�[�W���N���X�̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CEffectBillFireProc::CEffectBillFireProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	BILLBOARDBASE bb = {};

	// ------------------------------------------------------------------------------------------
	// �r���{�[�h�\���̔z��̐ݒ�

	// 0:���r���{�[�h
	m_BillboardArray.push_back(bb);
	Load(_T("Data/Image/sparklen3.png"), &m_BillboardArray.back());
	m_BillboardArray.back().m_fDestWidth = 0.7f;      // �\����
	m_BillboardArray.back().m_fDestHeight = 0.7f;     // �\������
	m_BillboardArray.back().m_fDestCenterX = m_BillboardArray.back().m_fDestWidth / 2;  // �\�����S�ʒu�w(�^��)
	m_BillboardArray.back().m_fDestCenterY = m_BillboardArray.back().m_fDestHeight / 2; // �\�����S�ʒu�x(�^��)
	m_BillboardArray.back().m_dwSrcX = 0;             // �p�^�[���̈ʒu�@�w���W
	m_BillboardArray.back().m_dwSrcY = 0;             // �p�^�[���̈ʒu�@�x���W
	m_BillboardArray.back().m_dwSrcWidth = 85;        // �p�^�[���̕�
	m_BillboardArray.back().m_dwSrcHeight = 85;       // �p�^�[���̍���
	m_BillboardArray.back().m_dwNumX = 3;             // �A�j���[�V����������p�^�[���̐��@�w����
	m_BillboardArray.back().m_dwNumY = 1;             // �A�j���[�V����������p�^�[���̐��@�x����
	m_BillboardArray.back().m_fAlpha = 0.9f;          // �����x
	m_BillboardArray.back().m_nBlendFlag = 1;         // �u�����h�X�e�[�g�t���O(0:�ʏ�`��@1:���Z�����F�`��)
	m_BillboardArray.back().m_nDrawFlag = 0;          // �`��t���O(0:�r���{�[�h�̂�)
	SetSrc(&m_BillboardArray.back());                 // �o�[�e�b�N�X�o�b�t�@�̍쐬


	// ------------------------------------------------------------------------------------------
	// �I�u�W�F�N�g�̐���
	for (DWORD i = 0; i < EFFECT_MAX; i++)
	{
		m_pObjArray.push_back(new CEffectBillFireObj(this));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
	}
};

//------------------------------------------------------------------------
//
//	�r���{�[�h�@���v���V�[�W���N���X�̃f�X�g���N�^	
//
//------------------------------------------------------------------------
CEffectBillFireProc::~CEffectBillFireProc()
{
	for (int i = 0; i < m_BillboardArray.size(); i++)
	{
		SAFE_RELEASE(m_BillboardArray[i].m_pTexture);
		SAFE_RELEASE(m_BillboardArray[i].m_pVertexBuffer);
	}
};

//------------------------------------------------------------------------
//
//	�r���{�[�h�\���̔z��̃A�h���X��Ԃ�	
//
//  Bint idx �r���{�[�h�\���̔z��̗v�f�ԍ�
//
//	�߂�l BILLBOARDBASE*�@�@�z��̃A�h���X
//
//------------------------------------------------------------------------
BILLBOARDBASE* CEffectBillFireProc::GetBillArrayPtr(int idx)
{
	if (idx < 0 || idx >= m_BillboardArray.size())
	{
		MessageBox(nullptr, _T("�� GetBillArrayPtr( idx) ��"), _T("�w��v�f�ԍ��̔z�񂪂���܂���"), MB_OK);
		return nullptr;
	}
	return &m_BillboardArray[idx];
}


//------------------------------------------------------------------------
//
//	�X�v���C�g�C���[�W�̓ǂݍ���	
//
//  TCHAR* szFName            �r���{�[�h�̃e�N�X�`���t�@�C����
//  BILLBOARDBASE* pBillBase  �r���{�[�h�\���̃A�h���X
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �ُ�
//
//------------------------------------------------------------------------
HRESULT CEffectBillFireProc::Load(TCHAR* szFName, BILLBOARDBASE* pBillBase)
{

	//�e�N�X�`���[�ǂݍ���	
	if (FAILED(m_pGMain->m_pD3D->CreateShaderResourceViewFromFile(szFName, &pBillBase->m_pTexture,
		pBillBase->m_dwImageWidth, pBillBase->m_dwImageHeight, 3)))
	{
		MessageBox(0, _T("�r���{�[�h�@�e�N�X�`���[��ǂݍ��߂܂���"), szFName, MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

//------------------------------------------------------------------------
//
//	�r���{�[�h�@���v���V�[�W���̃o�[�e�B�N�X�o�b�t�@�쐬	
//	�i�W�I���g���֘A���������j	
//
//	BILLBOARDBASE* pBillBase
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �ُ�
//
//------------------------------------------------------------------------
HRESULT CEffectBillFireProc::SetSrc(BILLBOARDBASE* pBillBase)
{
	// �r���{�[�h�p�̔|���S�����쐬���A�o�[�e�b�N�X�o�b�t�@���쐬����

	//�o�[�e�b�N�X�o�b�t�@�[�쐬(�������̍��W�ō쐬)
	BILLBOARD_VERTEX vertices[] =
	{
		VECTOR3(-pBillBase->m_fDestWidth / 2,  pBillBase->m_fDestHeight / 2, 0), VECTOR2((float)(pBillBase->m_dwSrcX + pBillBase->m_dwSrcWidth) / pBillBase->m_dwImageWidth, (float)pBillBase->m_dwSrcY / pBillBase->m_dwImageHeight),                     //���_1  ����
		VECTOR3(pBillBase->m_fDestWidth / 2,  pBillBase->m_fDestHeight / 2, 0), VECTOR2((float)pBillBase->m_dwSrcX / pBillBase->m_dwImageWidth,                (float)pBillBase->m_dwSrcY / pBillBase->m_dwImageHeight),                        //���_2�@�E��
		VECTOR3(-pBillBase->m_fDestWidth / 2, -pBillBase->m_fDestHeight / 2, 0), VECTOR2((float)(pBillBase->m_dwSrcX + pBillBase->m_dwSrcWidth) / pBillBase->m_dwImageWidth, (float)(pBillBase->m_dwSrcY + pBillBase->m_dwSrcHeight) / pBillBase->m_dwImageHeight),   //���_3�@����
		VECTOR3(pBillBase->m_fDestWidth / 2, -pBillBase->m_fDestHeight / 2, 0), VECTOR2((float)pBillBase->m_dwSrcX / pBillBase->m_dwImageWidth,                (float)(pBillBase->m_dwSrcY + pBillBase->m_dwSrcHeight) / pBillBase->m_dwImageHeight),      //���_4�@�E��
	};

	// �Q�x�ڈȍ~�ɏ���������邱�Ƃ̑΍�
	SAFE_RELEASE(pBillBase->m_pVertexBuffer);

	// �o�[�e�b�N�X�o�b�t�@�[�쐬
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(BILLBOARD_VERTEX) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	if (FAILED(m_pGMain->m_pD3D->m_pDevice->CreateBuffer(&bd, &InitData, &pBillBase->m_pVertexBuffer)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//------------------------------------------------------------------------
//
//	�r���{�[�h�@���v���V�[�W���̊J�n	
//
//	�E�r���{�[�h�@���I�u�W�F�N�g�z��̒�����A�󂢂Ă���r���{�[�h��T���ĊJ�n����
//    �Ȃ��A�r���{�[�h�\���̔z��̗v�f�ԍ��O���J�n����
//
//  VECTOR3 vPos          �r���{�[�h�̔����ʒu(�\�����S�ʒu)
//
//	�߂�l BOOL
//		TRUE	= ����
//		FALSE	= �ُ�
//
//------------------------------------------------------------------------
BOOL CEffectBillFireProc::Start(VECTOR3 vPos)
{
	return Start(0, vPos);    //  �r���{�[�h�\���̔z��̗v�f�ԍ��O���J�n����
}
//------------------------------------------------------------------------
//
//	�r���{�[�h�@���v���V�[�W���̊J�n	
//
//	�E�r���{�[�h�@���I�u�W�F�N�g�z��̒�����A�󂢂Ă���r���{�[�h��T���ĊJ�n����
//
//  int     nBillIdx      �r���{�[�h�\���̔z��̗v�f�ԍ�
//  VECTOR3 vPos          �r���{�[�h�̔����ʒu(�\�����S�ʒu)
//
//	�߂�l BOOL
//		TRUE	= ����
//		FALSE	= �ُ�
//
//------------------------------------------------------------------------
BOOL CEffectBillFireProc::Start(int  nBillIdx, VECTOR3 vPos)
{
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			((CEffectBillFireObj*)m_pObjArray[i])->Start(nBillIdx, vPos);
			return TRUE;
		}
	}
	return FALSE;
};

//------------------------------------------------------------------------
//
//	�r���{�[�h�@���v���V�[�W���̊J�n	
//  (���̐�����v�������������̐e���s���Ƃ�)
//
//	�E�r���{�[�h�@���I�u�W�F�N�g�z��̒�����A�󂢂Ă���r���{�[�h�@����T���ĊJ�n����
//
//  int     nBillIdx      �r���{�[�h�\���̔z��̗v�f�ԍ��i�ȗ��l�O�j�B
//
//	�߂�l CEffectBillFireObj*
//		�����ł����Ƃ��@�@�r���{�[�h�@���I�u�W�F�N�g�A�h���X
//		�����ł��Ȃ��Ƃ��@nullptr
//
//------------------------------------------------------------------------
CEffectBillFireObj* CEffectBillFireProc::Start(int  nBillIdx)
{
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->SetActive(TRUE);
			((CEffectBillFireObj*)(m_pObjArray[i]))->m_bAuto = FALSE;  // ���̐�����v�������������̐e���s��
			((CEffectBillFireObj*)(m_pObjArray[i]))->m_nBillIdx = nBillIdx;
			((CEffectBillFireObj*)(m_pObjArray[i]))->m_dwFrame = 0;
			return ((CEffectBillFireObj*)(m_pObjArray[i]));
		}
	}
	return nullptr;
};



// ============================================================================================

//------------------------------------------------------------------------
//
//	�r���{�[�h�@���I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CEffectBillFireObj::CEffectBillFireObj(CBaseProc* pProc) : CBaseObj(pProc)
{
	m_pD3D = m_pGMain->m_pD3D;
	m_pShader = m_pGMain->m_pShader;

	m_vPos = VECTOR3(0, 0, 0);
	m_vUVOffset = VECTOR2(0, 0);
	m_dwFrame = 0;

	m_nBillIdx = 0;

	//	������
	Init();
}

//------------------------------------------------------------------------
//
//	�r���{�[�h�@���I�u�W�F�N�g�̃f�X�g���N�^	
//
//------------------------------------------------------------------------
CEffectBillFireObj::~CEffectBillFireObj()
{
	;
}
//------------------------------------------------------------------------
//	�r���{�[�h�@���I�u�W�F�N�g�̏������֐�
//
//  �e��ݒ�l�̏�����
//
//  �����@�@�Ȃ�
//
//  �߂�l�@�@�@�Ȃ�
//------------------------------------------------------------------------
void CEffectBillFireObj::Init()
{
	m_bActive = FALSE;
	m_bAuto = FALSE;
}

//------------------------------------------------------------------------
//	�r���{�[�h�@���I�u�W�F�N�g�̃r���{�[�h�\���̔z��̃A�h���X��Ԃ��֐�
//
//  �����@�@�Ȃ�
//
//  �߂�l�@�@�@BILLBOARDBASE*   �z��̃A�h���X
//------------------------------------------------------------------------
BILLBOARDBASE* CEffectBillFireObj::GetBillArrayPtr()
{
	return  ((CEffectBillFireProc*)m_pProc)->GetBillArrayPtr(m_nBillIdx);
}

//------------------------------------------------------------------------
//
//	�r���{�[�h�@���I�u�W�F�N�g�̊J�n	
//
//  int       nBillIdx �r���{�[�h�\���̔z��̗v�f�ԍ��B
//  VECTOR3   vPos     �\���ʒu�i�r���{�[�h�̒��S�_�ʒu���w��j
//
//	�߂�l BOOL
//		TRUE      �\���p��
//		FALSE     �\���I��
//
//------------------------------------------------------------------------
BOOL CEffectBillFireObj::Start(int nBillIdx, VECTOR3 vPos)
{
	if (m_bActive) return FALSE;  // ���łɊJ�n��

	m_bActive = TRUE;
	m_nBillIdx = nBillIdx;   // �r���{�[�h�\���̔z��̗v�f�ԍ�
	m_bAuto = TRUE;          // �������[�h
	m_dwFrame = 0;
	m_vPos = vPos;

	return TRUE;
}

//------------------------------------------------------------------------
//
//	�r���{�[�h�@���I�u�W�F�N�g�̍X�V	
//
//	�߂�l �Ȃ�
//
//------------------------------------------------------------------------
void CEffectBillFireObj::Update()
{
	DWORD dwIdx;

	if (!m_bActive) return;

	m_dwFrame++;
	dwIdx = m_dwFrame / EFFECT_ANIM_SPEED;

	if (dwIdx >= GetBillArrayPtr()->m_dwNumX * GetBillArrayPtr()->m_dwNumY)	// �p�^�[���̍Ō�ɒB�����Ƃ�
	{
		if (m_bAuto) {  // �������[�h�̂Ƃ��͏I��
			m_bActive = FALSE;
			return;
		}
		else {
			dwIdx = 0; // ���̐�����v�������������̐e���s���Ƃ��́A�A�j���[�V�������J��Ԃ�
		}
	}

	// �A�j���[�V�����̂��߂̃e�N�X�`���I�t�Z�b�g��ݒ肷��
	m_vUVOffset.x = (float)(dwIdx % GetBillArrayPtr()->m_dwNumX * GetBillArrayPtr()->m_dwSrcWidth);   // �w�����̕ψ�
	m_vUVOffset.y = (float)(dwIdx / GetBillArrayPtr()->m_dwNumX * GetBillArrayPtr()->m_dwSrcHeight);  // �x�����̕ψ�


	Render(); // �����_�����O

}
//------------------------------------------------------------------------
//
//	�r���{�[�h�@���I�u�W�F�N�g����ʂɃ����_�����O	
//
//	�߂�l BOOL
//		TRUE      �\���p��
//		FALSE     �\���I��
//
//------------------------------------------------------------------------
BOOL CEffectBillFireObj::Render()
{

	if (!m_bActive) return FALSE;

	//�r���{�[�h�́A���_���������[���h�g�����X�t�H�[�������߂�
	MATRIX4X4 mWorld = GetLookatMatrix(m_vPos, m_pGMain->m_vEyePt);
	// �`�撆�S�ʒu�̈ړ�������
	MATRIX4X4 mPosUp = XMMatrixTranslation(GetBillArrayPtr()->m_fDestCenterX - GetBillArrayPtr()->m_fDestWidth / 2,
		GetBillArrayPtr()->m_fDestCenterY - GetBillArrayPtr()->m_fDestHeight / 2, 0);
	mWorld = mPosUp * mWorld;

	//�g�p����V�F�[�_�[�̃Z�b�g
	m_pD3D->m_pDeviceContext->VSSetShader(m_pShader->m_pEffect3D_VS_BILL, nullptr, 0);
	m_pD3D->m_pDeviceContext->PSSetShader(m_pShader->m_pEffect3D_PS, nullptr, 0);

	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g
	UINT stride = sizeof(BILLBOARD_VERTEX);
	UINT offset = 0;
	ID3D11Buffer* pVertexBuffer = GetBillArrayPtr()->m_pVertexBuffer;   // �o�[�e�b�N�X�o�b�t�@
	m_pD3D->m_pDeviceContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);

	UINT mask = 0xffffffff;
	if (GetBillArrayPtr()->m_nBlendFlag == 1)   // ���Z�����F�w��
	{
		// ���Z�����F�̃u�����f�B���O��ݒ�
		m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateAdd, nullptr, mask);
	}

	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��
	D3D11_MAPPED_SUBRESOURCE pData;
	CONSTANT_BUFFER_EFFECT cb;
	ZeroMemory(&cb, sizeof(cb));

	if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pShader->m_pConstantBufferEffect, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//���[���h�A�J�����A�ˉe�s��A�e�N�X�`���[�I�t�Z�b�g��n��
		cb.mWVP = XMMatrixTranspose(mWorld * m_pGMain->m_mView * m_pGMain->m_mProj);

		cb.vUVOffset.x = m_vUVOffset.x / GetBillArrayPtr()->m_dwImageWidth;		// �e�N�X�`���A�j���[�V�����̃I�t�Z�b�g
		cb.vUVOffset.y = m_vUVOffset.y / GetBillArrayPtr()->m_dwImageHeight;		// �e�N�X�`���A�j���[�V�����̃I�t�Z�b�g
		cb.vUVScale.x = 1;
		cb.vUVScale.y = 1;
		cb.fAlpha = GetBillArrayPtr()->m_fAlpha;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pD3D->m_pDeviceContext->Unmap(m_pShader->m_pConstantBufferEffect, 0);
	}
	//���̃R���X�^���g�o�b�t�@�[���ǂ̃V�F�[�_�[�Ŏg����
	m_pD3D->m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	m_pD3D->m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	//���_�C���v�b�g���C�A�E�g���Z�b�g
	m_pD3D->m_pDeviceContext->IASetInputLayout(m_pShader->m_pEffect3D_VertexLayout_BILL);
	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	m_pD3D->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//�e�N�X�`���[���V�F�[�_�[�ɓn��
	m_pD3D->m_pDeviceContext->PSSetSamplers(0, 1, &m_pD3D->m_pSampleLinear);
	m_pD3D->m_pDeviceContext->PSSetShaderResources(0, 1, &GetBillArrayPtr()->m_pTexture);
	//�v���~�e�B�u�������_�����O
	m_pD3D->m_pDeviceContext->Draw(4, 0);

	if (GetBillArrayPtr()->m_nBlendFlag == 1)   // ���Z�����F�w��
	{
		// �ʏ�̃u�����f�B���O�ɖ߂�
		m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateTrapen, nullptr, mask);
	}

	return TRUE;
}



//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�P�@�@�@�@�@�@                 ver 3.2        2023.1.31
//
//		�p�[�e�B�N���̏���
//															EffectParticle.cpp
//=============================================================================
#include  "EffectParticle.h"

//------------------------------------------------------------------------
//
//	�p�[�e�B�N���v���V�[�W���N���X�̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CEffectParticleProc::CEffectParticleProc()
{
	PARTICLEBASE pb = {};

	// ------------------------------------------------------------------------------------------
	// �p�[�e�B�N���\���̂̐ݒ�

	// 0:�Ήԃp�[�e�B�N��
	m_ParticleArray.push_back(pb);
	Load(_T("Data/Image/particle3.png"), &m_ParticleArray.back());// �p�[�e�B�N���e�N�X�`��
	m_ParticleArray.back().m_nNum = 100;             // ��̃I�u�W�F�N�g���̃p�[�e�B�N�����BPARTICLE_NUM_MAX�ȉ��ł��邱�ƁB
	m_ParticleArray.back().m_fDestSize = 0.1f;       // �\���T�C�Y(��̃p�[�e�B�N���̑傫��)
	m_ParticleArray.back().m_FrameEnd = 60;          // �p�[�e�B�N����\�����Ă��鎞��
	m_ParticleArray.back().m_fSpeed = 0.015f;        // �p�[�e�B�N���̈ړ��X�s�[�h�B�����_��
	m_ParticleArray.back().m_iBarthFrame = 20;       // �p�[�e�B�N���̊J�n�܂ł̍ő�҂����ԁB�����_���ŊJ�n�B�O�͑҂�����
	m_ParticleArray.back().m_ifBound = 0;            // �n�ʂŃo�E���h�����邩�i0:�o�E���h�Ȃ� 1:�n�ʂŃo�E���h�j
	m_ParticleArray.back().m_fAlpha = 0.9f;          // �����x
	m_ParticleArray.back().m_nBlendFlag = 1;         // �u�����h�X�e�[�g�t���O(0:�ʏ�`��@1:���Z�����F�`��)
	SetSrc(&m_ParticleArray.back());                 // �o�[�e�b�N�X�o�b�t�@�̍쐬

	// 1:�Ήԃp�[�e�B�N���E��
	//m_ParticleArray.push_back(pb);
	//Load(_T("Data/Image/particle2.png"), &m_ParticleArray.back());// �p�[�e�B�N���e�N�X�`��
	//m_ParticleArray.back().m_nNum = 10;              // ��̃I�u�W�F�N�g���̃p�[�e�B�N�����BPARTICLE_NUM_MAX�ȉ��ł��邱�ƁB
	//m_ParticleArray.back().m_fDestSize = 0.5f;       // �\���T�C�Y(��̃p�[�e�B�N���̑傫��)
	//m_ParticleArray.back().m_FrameEnd = 60;          // �p�[�e�B�N����\�����Ă��鎞��
	//m_ParticleArray.back().m_fSpeed = 0.015f;        // �p�[�e�B�N���̈ړ��X�s�[�h�B�����_��
	//m_ParticleArray.back().m_iBarthFrame = 0;        // �p�[�e�B�N���̊J�n�܂ł̍ő�҂����ԁB�����_���ŊJ�n�B�O�͑҂�����
	//m_ParticleArray.back().m_ifBound = 0;            // �n�ʂŃo�E���h�����邩�i0:�o�E���h�Ȃ� 1:�n�ʂŃo�E���h�j
	//m_ParticleArray.back().m_fAlpha = 0.9f;          // �����x
	//m_ParticleArray.back().m_nBlendFlag = 1;         // �u�����h�X�e�[�g�t���O(0:�ʏ�`��@1:���Z�����F�`��)
	//SetSrc(&m_ParticleArray.back());                 // �o�[�e�b�N�X�o�b�t�@�̍쐬


	// ---------------------------------------------------------------------------------------------
	// �I�u�W�F�N�g�̐���
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		m_pObjArray.push_back(new CEffectParticleObj(this));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
	}

};
//------------------------------------------------------------------------
//
//	�p�[�e�B�N���v���V�[�W���N���X�̃f�X�g���N�^	
//
//------------------------------------------------------------------------
CEffectParticleProc::~CEffectParticleProc()
{
	for (int i = 0; i < m_ParticleArray.size(); i++)
	{
		SAFE_RELEASE(m_ParticleArray[i].m_pTexture);
		SAFE_RELEASE(m_ParticleArray[i].m_pVertexBuffer);
	}
};

//------------------------------------------------------------------------
//
//	�p�[�e�B�N���\���̔z��̃A�h���X��Ԃ�	
//
//  idx  �p�[�e�B�N���\���̔z��̗v�f�ԍ�
//
//	�߂�l PARTICLEBASE*�@�@�z��̃A�h���X
//
//------------------------------------------------------------------------
PARTICLEBASE* CEffectParticleProc::GetPartArrayPtr(int idx)
{
	if (idx < 0 || idx >= m_ParticleArray.size())
	{
		MessageBox(nullptr, _T("�� GetPartArrayPtr( idx) ��"), _T("�w��v�f�ԍ��̔z�񂪂���܂���"), MB_OK);
		return nullptr;
	}
	return &m_ParticleArray[idx];
}

//------------------------------------------------------------------------
//
//	�X�v���C�g�C���[�W�̓ǂݍ���	
//
//  TCHAR* szFName            �p�[�e�B�N���̃e�N�X�`���t�@�C����
//  PARTICLEBASE* pPartBase   �p�[�e�B�N��	�\���̃A�h���X
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �ُ�
//
//------------------------------------------------------------------------
HRESULT CEffectParticleProc::Load(TCHAR* szFName, PARTICLEBASE* pPartBase)
{

	//�e�N�X�`���[�ǂݍ���	
	if (FAILED(GameDevice()->m_pD3D->CreateShaderResourceViewFromFile(szFName, &pPartBase->m_pTexture,
		pPartBase->m_dwImageWidth, pPartBase->m_dwImageHeight, 3)))
	{
		MessageBox(0, _T("�p�[�e�B�N���@�e�N�X�`���[��ǂݍ��߂܂���"), szFName, MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

//------------------------------------------------------------------------
//
//	�p�[�e�B�N���v���V�[�W���̃o�[�e�B�N�X�o�b�t�@�쐬	
//	�i�W�I���g���֘A���������D�����ł́h�_�h�p�j	
//
//	PARTICLEBASE* pPartBase
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �ُ�
//
//------------------------------------------------------------------------
HRESULT CEffectParticleProc::SetSrc(PARTICLEBASE* pPartBase)
{
	//�o�[�e�b�N�X
	PARTICLE_VERTEX vertices[] =
	{
		VECTOR3(0.0f, 0.0f, 0.0f)
	};

	// �Q�x�ڈȍ~�ɏ���������邱�Ƃ̑΍�
	SAFE_RELEASE(pPartBase->m_pVertexBuffer);

	// �o�[�e�b�N�X�o�b�t�@�[�쐬
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(PARTICLE_VERTEX) * 1;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	if (FAILED(GameDevice()->m_pD3D->m_pDevice->CreateBuffer(&bd, &InitData, &pPartBase->m_pVertexBuffer)))
	{
		return E_FAIL;
	}

	return S_OK;

}
//------------------------------------------------------------------------
//
//	�p�[�e�B�N���v���V�[�W���N���X�̊J�n	
//
//	�E�p�[�e�B�N���I�u�W�F�N�g�z��̒�����A�󂢂Ă���p�[�e�B�N����T���ĊJ�n����
//�@�@�p�[�e�B�N���\���̔z��̗v�f�ԍ����O�Ƃ��ĊJ�n����
// 
//  VECTOR3 vEmitPos          �p�[�e�B�N���̔����ʒu
//  VECTOR3 vNormal           �p�[�e�B�N���̔����ʂ̖@���i�ȗ��j
//
//	�߂�l bool
//		true	= ����
//		false	= �ُ�
//
//------------------------------------------------------------------------
bool CEffectParticleProc::Start(VECTOR3 vEmitPos, VECTOR3 vNormal)
{
	return Start(0, vEmitPos, vNormal);
}
//------------------------------------------------------------------------
//
//	�p�[�e�B�N���v���V�[�W���N���X�̊J�n	
//
//	�E�p�[�e�B�N���I�u�W�F�N�g�z��̒�����A�󂢂Ă���p�[�e�B�N����T���ĊJ�n����
//
//  int nPartIdx              �p�[�e�B�N���\���̔z��̗v�f�ԍ�
//  VECTOR3 vEmitPos          �p�[�e�B�N���̔����ʒu
//  VECTOR3 vNormal           �p�[�e�B�N���̔����ʂ̖@���i�ȗ��j
//
//	�߂�l bool
//		true	= ����
//		false	= �ُ�
//
//------------------------------------------------------------------------
bool CEffectParticleProc::Start(int nPartIdx, VECTOR3 vEmitPos, VECTOR3 vNormal)
{

	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			((CEffectParticleObj*)m_pObjArray[i])->Start(nPartIdx, vEmitPos, vNormal);
			return true;
		}
	}
	return false;
};


// ============================================================================================


// ========================================================================================
//
//	�p�[�e�B�N���I�u�W�F�N�g�N���X
//�i�|�C���g�X�v���C�g�Ńp�[�e�B�N���������j
//
// ========================================================================================
//------------------------------------------------------------------------
//
//	�p�[�e�B�N���I�u�W�F�N�g�̃R���X�g���N�^	
//
//  int MaxParticle          �p�[�e�B�N���̐�
//
//------------------------------------------------------------------------
CEffectParticleObj::CEffectParticleObj(CBaseProc* pProc) : CBaseObj(pProc)
{
	m_pD3D = GameDevice()->m_pD3D;
	m_pShader = GameDevice()->m_pShader;

	m_nPartIdx = 0;
	m_MaxParticle = 0;
	m_vEmitPos = VECTOR3(0, 0, 0);
	m_pPtArray = nullptr;
	m_Frame = 0;

	//	������
	Init();

}
//------------------------------------------------------------------------
//
//	�p�[�e�B�N���I�u�W�F�N�g�̃f�X�g���N�^	
//
//------------------------------------------------------------------------
CEffectParticleObj::~CEffectParticleObj()
{
	SAFE_DELETE_ARRAY(m_pPtArray);
}

//------------------------------------------------------------------------
//	�p�[�e�B�N���I�u�W�F�N�g�̏������֐�
//
//  �e��ݒ�l�̏�����
//
//
//  �߂�l�@�@�@�Ȃ�
//------------------------------------------------------------------------
void CEffectParticleObj::Init()
{
	m_bActive = false;
	m_MaxParticle = EFFECT_NUM_MAX;           // �����l�Ƃ��ăp�[�e�B�N���z��v�f�������Ēu��
	m_pPtArray = new PART[EFFECT_NUM_MAX];    // ��̃I�u�W�F�N�g�̒��̃p�[�e�B�N���z��̐���
}

//------------------------------------------------------------------------
//	�p�[�e�B�N���I�u�W�F�N�g�̃p�[�e�B�N���\���̔z��̃A�h���X��Ԃ��֐�
//
//  �����@�@�Ȃ�
//
//  �߂�l�@�@�@PARTICLEBASE*   �z��̃A�h���X
//------------------------------------------------------------------------
PARTICLEBASE* CEffectParticleObj::GetPartArrayPtr()
{
	return  ((CEffectParticleProc*)m_pProc)->GetPartArrayPtr(m_nPartIdx);
}

//------------------------------------------------------------------------
//
//	�p�[�e�B�N���I�u�W�F�N�g�̊J�n	
//  �E�p�[�e�B�N�����w��ʒu���甭��������B
//  �E����������@�����W�Ŏw��ł���B�ȗ�����ƑS�����֔�������B
// 
//  int     nPartIdx          �p�[�e�B�N���\���̔z��̗v�f�ԍ�
//  VECTOR3 vEmitPos          �p�[�e�B�N���̔����ʒu
//  VECTOR3 vNormal           �p�[�e�B�N���̔����ʂ̖@���i�ȗ��j
//
//	�߂�l bool
//		true	= ����
//		false	= �ُ�
//
//------------------------------------------------------------------------
bool CEffectParticleObj::Start(int nPartIdx, VECTOR3 vEmitPos, VECTOR3 vNormal)
{
	if (m_bActive)
	{
		// ���łɕ\�����̂Ƃ�
		return false;

	}
	else {
		// �J�n����
		m_bActive = true;
		m_nPartIdx = nPartIdx;
		m_MaxParticle = GetPartArrayPtr()->m_nNum;  // �p�[�e�B�N���\���̂̃p�[�e�B�N������ݒ肷��
		if (m_MaxParticle > EFFECT_NUM_MAX) m_MaxParticle = EFFECT_NUM_MAX; // �������v�f�����I�[�o�[���Ă�����v�f���ɒ�������
		m_vEmitPos = vEmitPos;
		m_Frame = 0;

		// �ړ������B�@�������𒆐S�Ƃ��ă����_�������ɔ���������
		VECTOR3 vDist, vMin, vMax;
		vDist.x = (1.0f - fabsf(vNormal.x)) / 2;
		vDist.y = (1.0f - fabsf(vNormal.y)) / 2;
		vDist.z = (1.0f - fabsf(vNormal.z)) / 2;

		if (vNormal.x < 0)
		{
			vMin.x = vNormal.x - vDist.x;
			vMax.x = 0.0f + vDist.x;
		}
		else {
			vMin.x = 0.0f - vDist.x;
			vMax.x = vNormal.x + vDist.x;
		}
		if (vNormal.y < 0)
		{
			vMin.y = vNormal.y - vDist.y;
			vMax.y = 0.0f + vDist.y;
		}
		else {
			vMin.y = 0.0f - vDist.y;
			vMax.y = vNormal.y + vDist.y;
		}
		if (vNormal.z < 0)
		{
			vMin.z = vNormal.z - vDist.z;
			vMax.z = 0.0f + vDist.z;
		}
		else {
			vMin.z = 0.0f - vDist.z;
			vMax.z = vNormal.z + vDist.z;
		}

		// �p�[�e�B�N���̊J�n
		for (int i = 0; i < m_MaxParticle; i++)
		{
			m_pPtArray[i].Pos = m_vEmitPos;
			m_pPtArray[i].Dir.x = ((float)rand() / (float)RAND_MAX) * (vMax.x - vMin.x) + vMin.x;
			m_pPtArray[i].Dir.y = ((float)rand() / (float)RAND_MAX) * (vMax.y - vMin.y) + vMin.y;
			m_pPtArray[i].Dir.z = ((float)rand() / (float)RAND_MAX) * (vMax.z - vMin.z) + vMin.z;
			m_pPtArray[i].Dir = normalize(m_pPtArray[i].Dir);
			m_pPtArray[i].Speed = (5 + ((float)rand() / (float)RAND_MAX)) * GetPartArrayPtr()->m_fSpeed;      // �ړ��X�s�[�h�B�����_��
			m_pPtArray[i].BirthFrame = (int)(((float)rand() / RAND_MAX) * GetPartArrayPtr()->m_iBarthFrame);  // �J�n�܂ł̑҂����ԁB�����_��
		}
		return true;
	}
}

//------------------------------------------------------------------------
//
//	�p�[�e�B�N���I�u�W�F�N�g�̈ړ��E�X�V����	
//  �E�p�[�e�B�N�����X�V����
//
//	�߂�l �Ȃ�
//
//------------------------------------------------------------------------
void CEffectParticleObj::Update()
{
	if (m_bActive)
	{
		m_Frame++;	// �t���[����i�߂�
		for (int i = 0; i < m_MaxParticle; i++)
		{
			if (m_Frame > m_pPtArray[i].BirthFrame) // ��̃p�[�e�B�N�����\���J�n���ԂɂȂ����Ƃ�
			{
				// �ړ�
				m_pPtArray[i].Pos = m_pPtArray[i].Pos + m_pPtArray[i].Dir * m_pPtArray[i].Speed;

				// �d�͂̌v�Z
				m_pPtArray[i].Dir = m_pPtArray[i].Dir + VECTOR3(0, -0.049f, 0);

				// �n�ʂł̃o�E���h
				if (GetPartArrayPtr()->m_ifBound == 1)
				{
					if (m_pPtArray[i].Pos.y < 0)
					{
						m_pPtArray[i].Dir.y = -m_pPtArray[i].Dir.y;
						m_pPtArray[i].Speed /= 1.8f;
					}
				}
			}
		}

		if (m_Frame >= GetPartArrayPtr()->m_FrameEnd) // �\�����ԏI����
		{
			m_bActive = false;
		}

	}
}

//------------------------------------------------------------------------
//
//	�p�[�e�B�N���I�u�W�F�N�g����ʂɃ����_�����O	
//  �E�p�[�e�B�N����\������
//
//	�߂�l �Ȃ�
//
//------------------------------------------------------------------------
void CEffectParticleObj::Draw()
{
	// �\����ԂłȂ��Ƃ�
	if (!m_bActive)  return;

	//�g�p����V�F�[�_�[�̃Z�b�g
	m_pD3D->m_pDeviceContext->VSSetShader(m_pShader->m_pEffect3D_VS_POINT, nullptr, 0);
	m_pD3D->m_pDeviceContext->GSSetShader(m_pShader->m_pEffect3D_GS_POINT, nullptr, 0);
	m_pD3D->m_pDeviceContext->PSSetShader(m_pShader->m_pEffect3D_PS, nullptr, 0);

	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g
	UINT stride = sizeof(PARTICLE_VERTEX);
	UINT offset = 0;
	m_pD3D->m_pDeviceContext->IASetVertexBuffers(0, 1, &GetPartArrayPtr()->m_pVertexBuffer, &stride, &offset);

	// ���Z�����F�̃u�����f�B���O��ݒ�
	UINT mask = 0xffffffff;
	if (GetPartArrayPtr()->m_nBlendFlag == 1)   // ���Z�����F�w��
	{
		m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateAdd, nullptr, mask);
	}

	// �p�[�e�B�N���P�����P���|�C���g�X�v���C�g�Ƃ���m_MaxParticle���`��
	for (int i = 0; i < m_MaxParticle; i++)
	{
		// �`��J�n�O�̂��̂ƕ`��t���[���A�E�g�̂��͕̂`�悵�Ȃ�
		if (GetPartArrayPtr()->m_FrameEnd < m_Frame + (GetPartArrayPtr()->m_iBarthFrame - m_pPtArray[i].BirthFrame)) continue;

		//�X�̃p�[�e�B�N���́A���_���������[���h�g�����X�t�H�[�������߂�
		MATRIX4X4 mWorld = GetLookatMatrix(m_pPtArray[i].Pos, GameDevice()->m_vEyePt);

		RenderParticle(mWorld, GameDevice()->m_mView, GameDevice()->m_mProj);  // �p�[�e�B�N���������_�����O
	}

	if (GetPartArrayPtr()->m_nBlendFlag == 1)   // ���Z�����F�w��
	{
		// �ʏ�̃u�����f�B���O�ɖ߂�
		m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateTrapen, nullptr, mask);
	}

	//�W�I���g���V�F�[�_�[�̃��Z�b�g
	m_pD3D->m_pDeviceContext->GSSetShader(nullptr, nullptr, 0);

	return;
}
//------------------------------------------------------------------------
//
//	�p�[�e�B�N���������_�����O����	
//
//  MATRIX4X4    W    ���[���h�}�g���b�N�X
//  MATRIX4X4    V    �r���[�}�g���b�N�X
//  MATRIX4X4    P    �v���W�F�N�V�����}�g���b�N�X
//
//	�߂�l �Ȃ�
//
//------------------------------------------------------------------------
void CEffectParticleObj::RenderParticle(MATRIX4X4 W, MATRIX4X4 V, MATRIX4X4 P)
{

	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��
	D3D11_MAPPED_SUBRESOURCE pData;
	CONSTANT_BUFFER_EFFECT cb;
	ZeroMemory(&cb, sizeof(cb));
	if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pShader->m_pConstantBufferEffect, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//���[���h�A�J�����A�ˉe�s���n�� // -- 2017.8.25
		cb.mW = XMMatrixTranspose(W);
		cb.mV = XMMatrixTranspose(V);
		cb.mP = XMMatrixTranspose(P);

		cb.fAlpha = GetPartArrayPtr()->m_fAlpha;            // �p�[�e�B�N���̓����x
		cb.fSize = GetPartArrayPtr()->m_fDestSize;          // �p�[�e�B�N���̃T�C�Y 
		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pD3D->m_pDeviceContext->Unmap(m_pShader->m_pConstantBufferEffect, 0);
	}

	//���̃R���X�^���g�o�b�t�@�[���ǂ̃V�F�[�_�[�Ŏg����
	m_pD3D->m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	m_pD3D->m_pDeviceContext->GSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	m_pD3D->m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	//���_�C���v�b�g���C�A�E�g���Z�b�g
	m_pD3D->m_pDeviceContext->IASetInputLayout(m_pShader->m_pEffect3D_VertexLayout);
	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	m_pD3D->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	//�e�N�X�`���[���V�F�[�_�[�ɓn��
	m_pD3D->m_pDeviceContext->PSSetSamplers(0, 1, &m_pD3D->m_pSampleLinear);
	m_pD3D->m_pDeviceContext->PSSetShaderResources(0, 1, &GetPartArrayPtr()->m_pTexture);
	//�v���~�e�B�u�������_�����O
	m_pD3D->m_pDeviceContext->Draw(1, 0);

}


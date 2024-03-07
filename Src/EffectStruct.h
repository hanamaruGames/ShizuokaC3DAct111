//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�P                             ver 3.2        2023.1.31
//
//		�G�t�F�N�g�̍\���̒�`
//																EffectStruct.h
//=============================================================================
#pragma once
#include "GameMain.h"

// ========================================================================================
//
// ���_�̍\����
//
// ========================================================================================
struct PARTICLE_VERTEX
{
	VECTOR3 Pos; //�ʒu
};
struct BILLBOARD_VERTEX
{
	VECTOR3 Pos; //�ʒu
	VECTOR2 UV;  //�e�N�X�`���[���W
};

// ========================================================================================
//
// ��̃I�u�W�F�N�g�̒��̃p�[�e�B�N���\����
//
// ========================================================================================
struct PART
{
	VECTOR3     Pos;
	VECTOR3     Dir;
	float       Speed;
	int         BirthFrame;
	PART()
	{
		ZeroMemory(this, sizeof(PART));
	}
};

// ========================================================================================
//
//	�p�[�e�B�N���z��p�\����
// 
// ========================================================================================
struct PARTICLEBASE
{
	ID3D11ShaderResourceView* m_pTexture;        // �e�N�X�`���[(�P�̃e�N�X�`���[�ɂ�1�̃p�[�e�B�N���̂�)
	DWORD						m_dwImageWidth;    // �e�N�X�`���[�̕�
	DWORD						m_dwImageHeight;   // �e�N�X�`���[�̍���
	ID3D11Buffer* m_pVertexBuffer;   // �o�[�e�b�N�X�o�b�t�@
	int							m_nNum;            // ��̃I�u�W�F�N�g���̃p�[�e�B�N����
	float						m_fDestSize;       // �\���T�C�Y(���ƍ����͓���)
	int							m_FrameEnd;        // �p�[�e�B�N����\�����Ă��鎞��
	float						m_fSpeed;          // �p�[�e�B�N���̈ړ��X�s�[�h
	int							m_iBarthFrame;     // �p�[�e�B�N���̊J�n�܂ł̍ő�҂����ԁB�O�͑҂�����
	int							m_ifBound;         // �n�ʂŃo�E���h�����邩�i0:�o�E���h�Ȃ� 1:�n�ʂŃo�E���h�j
	float						m_fAlpha;          // �����x
	int							m_nBlendFlag;      // 0:�ʏ� 1:���Ȕ���
};

// ========================================================================================
//
//	�r���{�[�h�\����
// 
// ========================================================================================
struct BILLBOARDBASE
{
	ID3D11ShaderResourceView* m_pTexture;        // �e�N�X�`���[
	DWORD						m_dwImageWidth;    // �e�N�X�`���[�̕�
	DWORD						m_dwImageHeight;   // �e�N�X�`���[�̍���
	ID3D11Buffer* m_pVertexBuffer;   // �o�[�e�b�N�X�o�b�t�@
	float						m_fDestWidth;      // �\����
	float						m_fDestHeight;     // �\������
	float						m_fDestCenterX;    // �\�����S�ʒu�w
	float						m_fDestCenterY;    // �\�����S�ʒu�x
	DWORD						m_dwSrcX;          // �p�^�[���̈ʒu�w
	DWORD						m_dwSrcY;          // �p�^�[���̈ʒu�x
	DWORD						m_dwSrcWidth;      // �P�̃p�^�[���̕�
	DWORD						m_dwSrcHeight;     // �P�̃p�^�[���̍���
	DWORD						m_dwNumX;          // �p�^�[���̉��̐�
	DWORD						m_dwNumY;          // �p�^�[���̏c�̐�
	float						m_fAlpha;          // �����x
	int							m_nBlendFlag;      // 0:�ʏ�  1:���Ȕ���
	int							m_nDrawFlag;       // 0:�r���{�[�h  1:�r���{�[�h���b�V��
};


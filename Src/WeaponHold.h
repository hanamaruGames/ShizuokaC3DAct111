//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�P                             ver 3.2        2023.1.31
// 
//		����@��Ɏ��A�C�e��
//														WeaponHold.h
//=============================================================================
#pragma once
#include "GameMain.h"

// --------------------------------------------------------------------
//����@��Ɏ��A�C�e���@�I�u�W�F�N�g�N���X
// --------------------------------------------------------------------
class CWeaponHoldObj : public CBaseObj
{
protected:
	int                      m_nKindNo;			// ��Ɏ��A�C�e���̎��(1:���@2:�e)
	CFbxMesh* m_pMesh;			// Fbx���b�V��(�v���V�[�W���ł͂Ȃ��I�u�W�F�N�g�Ƀ��b�V������������)
	VECTOR3                  m_vOffset;			// �e���܂ł̃I�t�Z�b�g�i�e�̂݁j
public:
	void Init();
	bool Disp(MATRIX4X4 mHold, BASEHOLDITEM HoldItem);
	void GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vOffset);
	void GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vMin, VECTOR3& vMax);
	CBBox* GetBBox(MATRIX4X4 mHold, BASEHOLDITEM HoldItem);

	void Update() override;
	void Render();

	int GetKind() { return m_nKindNo; }

	CWeaponHoldObj(CBaseProc* pProc);	// �R���X�g���N�^        // -- 2022.2.16
	virtual	~CWeaponHoldObj();
};
// --------------------------------------------------------------------
//����@��Ɏ��A�C�e���@�v���V�[�W���N���X
// --------------------------------------------------------------------
class CWeaponHoldProc : public CBaseProc
{
protected:
	// �萔��`  ------------------------------------------
	static const int WEAPON_MAX = 15;    // MAX :����I�u�W�F�N�g�̐��B�i�����������j

public:
	bool Disp(MATRIX4X4 mHold, BASEHOLDITEM HoldItem); // ����@�̕\��
	void GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vOffset);
	void GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vMin, VECTOR3& vMax);
	CBBox* GetBBox(MATRIX4X4 mHold, BASEHOLDITEM HoldItem);
	int GetKind(BASEHOLDITEM HoldItem);
	CWeaponHoldProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponHoldProc();
};

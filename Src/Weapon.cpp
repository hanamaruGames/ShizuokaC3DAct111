//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�P                             ver 3.2        2023.1.31
//		����E�S�̂̏���
//															Weapon.cpp
//=============================================================================
#include  "Weapon.h"

//=============================================================================================================================
//
// ���탁�C���v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ----------------------------------------------------------------------------------------------------------------------------
CWeaponProc::CWeaponProc()
{
	Instantiate<CWeaponLaserProc>();
//	m_pWeaponLaserProc = new CWeaponLaserProc();		// ����E���[�U�[�v���V�[�W��
//	m_pProcArray.push_back(m_pWeaponLaserProc);				// �v���V�[�W�����v���V�[�W���z��ɓo�^����

	Instantiate<CWeaponHoldProc>();
//	m_pWeaponHoldProc = new CWeaponHoldProc();		// ����E��Ɏ��A�C�e���̃v���V�[�W��
//	m_pProcArray.push_back(m_pWeaponHoldProc);				// �v���V�[�W�����v���V�[�W���z��ɓo�^����
}

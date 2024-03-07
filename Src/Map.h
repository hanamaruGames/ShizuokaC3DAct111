//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�P                             ver 3.2        2023.1.31
//		�}�b�v�@�w�b�_�t�@�C��											Map.h
//=============================================================================
#pragma once
#include "GameMain.h"


// �Q�[���̒��Ŏg�p����d�͂̉����x   // -- 2023.1.31
#define  GAMEGRAVITY  (0.5f * GRAVITY * 0.00005f)

// --------------------------------------------------------------------
//
// �X�e�[�W�}�b�v
//
// --------------------------------------------------------------------
struct STAGEMAP
{
	CFbxMesh* m_pMesh;			// �X�^�e�B�b�N���b�V���ւ̃|�C���^
	CWave* m_pWave;			// �g�̃��b�V���ւ̃|�C���^
	MATRIX4X4				m_mWorld;			// ���b�V���̃��[���h�}�g���b�N�X
	int						m_nMaterialFlag;	// �}�e���A���t���O�@0:�ʏ�@1:�����F�@2:�f�B�X�v���C�X�����g�}�b�s���O 3:�g

	STAGEMAP()    // �R���X�g���N�^
	{
		Init();
	}
	~STAGEMAP()    // �f�X�g���N�^
	{
		// ���̒��Ń��b�V����DELETE�����Ă͂Ȃ�Ȃ�
	}
	void Init()    // ���������\�b�h
	{
		m_pMesh = NULL;
		m_pWave = NULL;
		m_mWorld = XMMatrixIdentity();
		m_nMaterialFlag = 0;
	}
};
// --------------------------------------------------------------------
//
// �ړ��}�b�v            �����̃v���O�������ł́A�g�p���Ȃ�
//
// --------------------------------------------------------------------
struct MOVEMAP
{
	BOOL					m_bActive;			// �\���̉�
	CFbxMesh*				m_pMesh;			// �X�^�e�B�b�N���b�V���ւ̃|�C���^
	int						m_nMaterialFlag;	// �}�e���A���t���O�@0:�ʏ�@1:�����F�@2:�f�B�X�v���C�X�����g�}�b�s���O
	CCollision*				m_pColMesh;			// �ړ��R���W�������b�V���ւ̃|�C���^
	BOOL					m_bMoveOn;			// �ړ�ON      FALSE:�ړ���~�@TRUE:�ړ����s          // -- 2022.11.14
	int						m_nMoveFlag;		// �ړ��敪    1:���s�ړ��@2:��]�@3:�g��k��         // -- 2022.11.14
	VECTOR3					m_vUp;				// �ړ�����
	VECTOR3					m_vMinOffset;		// �ړ������ŏ��l                                     // -- 2022.11.14
	VECTOR3					m_vMaxOffset;		// �ړ������ő�l                                     // -- 2022.11.14
	int						m_nChangeFlag;		// �ړ������E�l�ɓ��B���ĕ���������ւ��Ƃ�(�o��)�@0:�ړ����@1:�����`�F���W
	int						m_nLoop;			// �ړ����J��Ԃ���  0:�`�F���W�̉ӏ��Œ�~���ړ�ON��0:�ړ���~�ɖ߂��B 1:�ړ����J��Ԃ�

	MOVEMAP()    // �R���X�g���N�^
	{
		Init();
	}
	~MOVEMAP()    // �f�X�g���N�^
	{
		// ���̒��Ń��b�V����DELETE�����Ă͂Ȃ�Ȃ�
	}
	void Init()
	{
		m_bActive = FALSE;
		m_pMesh = NULL;
		m_nMaterialFlag = 0;
		m_pColMesh = NULL;
		m_bMoveOn = TRUE;    // �����ݒ�͈ړ����s
		m_nMoveFlag = 1;       // �����ݒ�͕��s�ړ�
		m_vUp = VECTOR3(0, 0, 0);
		m_vMinOffset = VECTOR3(-9999, -9999, -9999);
		m_vMaxOffset = VECTOR3(9999, 9999, 9999);
		m_nChangeFlag = 0;
		m_nLoop = 1;           // �����ݒ�̓��[�v
	}
};

// --------------------------------------------------------------------
//
// �i�r�Q�[�V�����}�b�v
//
// --------------------------------------------------------------------
struct NAVIGATIONMAP
{
	VECTOR3 vMin;
	VECTOR3 vMax;
	std::vector<DWORD>  m_dwEnmID;  // �ΏۂƂȂ�G�̂h�c
	NAVIGATIONMAP()    // �R���X�g���N�^
	{
		Init();
	}
	void Init()
	{
		vMin = VECTOR3(0.0f, 0.0f, 0.0f);
		vMax = VECTOR3(0.0f, 0.0f, 0.0f);
	}
	// ���̖ړI�n�����߂�Ƃ��̍Œ዗�������߂�     // -- 2023.1.31
	float GetNearLimit()
	{
		float lx = vMax.x - vMin.x;      // �w�����̒���
		float lz = vMax.z - vMin.z;      // �y�����̒���
		float len = (lx < lz) ? lx : lz;  // �������̒��������߂�
		len = len * 0.5f * 0.99f;        // �������̒����̔���������߂�
		if (len > 10.0f) len = 10.0f;    // 10����W���l�Ƃ���B������傫����ΕW���l�Ƃ���B
		return len;
	}
};

// --------------------------------------------------------------------    // -- 2021.2.4
//
// �C�x���g
//
// --------------------------------------------------------------------
// �C�x���g���
enum EVENTKIND
{
	eEvtKindNone = 0,
	eEvtChangeMap = 1,
	eEvtMoveMap = 2
};

struct EVENTMAP
{
	CBBox* m_pBBox;       // �o�E���f�B���O�{�b�N�X
	int       m_nEvtCycle;   // �C�x���g�T�C�N�� 0:�C�x���g���s���Ă��Ȃ� 1:�C�x���g���s���i�g�p���Ă��Ȃ��j 2:�C�x���g�I���`�F�b�N�i�ڐG�I��������j
	EVENTKIND m_nEvtKind;    // �C�x���g�̎�� eEvtChangeMap:�}�b�v�ړ�, eEvtMoveMap:�ړ��}�b�v�̐���
	int       m_nEvtNo;      // �C�x���g�ԍ� eEvtChangeMap�̂Ƃ��͈ړ���̃}�b�v�ԍ��AeEvtMoveMap�̂Ƃ��͈ړ��}�b�v�̗v�f�ԍ�
	int       m_nEvtOpe1;    // eEvtMoveMap�̂ݎw�肷��B�ړ��}�b�v�̓���w��@1:Active�̎w��B2:�ړ�ON�EOFF�̎w��
	int       m_nEvtOpe2;    // eEvtMoveMap�̂ݎw�肷��B�ړ��}�b�v�̓���w��̓�����e�@0:OFF�@1:ON
	int       m_nEvtKeyPush; // 0:�o�E���f�B���O�{�b�N�X�ɐڐG����ƃC�x���g�����A 1:�o�E���f�B���O�{�b�N�X�ɐڐG���āAENTER�L�[�������ƃC�x���g����

	EVENTMAP()    // �R���X�g���N�^
	{
		m_pBBox = NULL;
		m_nEvtCycle = 0;
		m_nEvtKind = eEvtKindNone;
		m_nEvtNo = 0;
		m_nEvtOpe1 = 0;
		m_nEvtOpe2 = 0;
		m_nEvtKeyPush = 0;
	}
	~EVENTMAP()    // �f�X�g���N�^
	{
		// ���̒��Ń��b�V����CBBox��DELETE�����Ă͂Ȃ�Ȃ�
	}
};

//======================================================================
// �}�b�v�@�v���V�[�W���N���X
//
// (����)�}�b�v�@�v���V�[�W���N���X�́A��{�v���V�[�W���N���X���p�����Ă��Ȃ�
// 
//======================================================================
class CMapProc
{
protected:
	// �萔��` -------------------------------------------------
	static const int MAP_NOMAX = 100;              // �}�b�vNO�̍ő�l������100�Ƃ���
	static const int MAP_SKYROTSPEED_X1000 = 5;    // ��̉�]�X�s�[�h��1000�{

	// -----------------------------------------------------------
	CGameMain* m_pGMain;

	DWORD								m_dwMapNo;
	BOOL								m_bActive;

	std::vector<STAGEMAP>				m_SkyMap;			// ��̃}�b�v
	std::vector<STAGEMAP>				m_StageMap;			// �X�e�[�W�̃}�b�v
	CCollision*							m_pColMesh;			// �R���W�������b�V��
	std::vector<MOVEMAP>				m_MoveMap;			// �ړ��}�b�v  *���̃v���O�������ł́A�g�p���Ȃ�
	std::vector<NAVIGATIONMAP>			m_NavMap;			// �i�r�Q�[�V�����}�b�v
	std::vector<EVENTMAP>				m_EventMap;			// �C�x���g�}�b�v    // -- 2021.2.4
	int									m_nEvtIdx;			// �C�x���g�v�f�ԍ�  // -- 2021.2.4


protected:
	// �}�b�v�쐬�֐�
	// �i���̊֐��͊O������A�N�Z�X�s�j
	void MakeMap1();

public:
	// �����o�[�֐�
	void Update();
	void Render();
	void DestroyAll();
	BOOL LoadMap(int mapbo);

	void UpdateMoveMap();
	int  SetEvent(VECTOR3 vMin, VECTOR3 vMax, MATRIX4X4 mWorld, EVENTKIND nEvtKind, int nEvtNo, int nEvtOpe1 = 0, int nEvtOpe2 = 0, int nEvtKeyPush = 0);    // -- 2021.2.4
	void UpdateEvent();                                                                           // -- 2021.2.4
	void RunEvent(EVENTMAP& EventMap);                                                             // -- 2021.2.4

	BOOL Hitcheck(CBaseObj* pObj, VECTOR3* pHit, VECTOR3* pNormal);
	BOOL Hitcheck(VECTOR3 vNow, VECTOR3 vOld, VECTOR3* pHit, VECTOR3* pNormal);
	BOOL Hitcheck(VECTOR3 vNow, VECTOR3 vOld, float fRadius, VECTOR3* pHit, VECTOR3* pNormal);    // -- 2020.12.11

	int  isCollisionMoveGravity(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld, float fRadius = 0.2f);
	int  isCollisionMoveGravity(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld, VECTOR3& vHit, VECTOR3& vNormal, float fRadius = 0.2f);  // -- 2022.11.14
	int  isCollisionMove(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld, float fRadius = 0.2f);
	int  isCollisionMove(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld, VECTOR3& vHit, VECTOR3& vNormal, float fRadius = 0.2f);  // -- 2022.11.14

	// �A�N�Z�X�֐�
	std::vector<NAVIGATIONMAP> GetNavMap() { return m_NavMap; }
	DWORD GetMapNo() { return m_dwMapNo; }

	// �R���X�g���N�^�i�v���V�[�W���̏������j
	CMapProc(CGameMain* m_pGMain);
	~CMapProc();
};
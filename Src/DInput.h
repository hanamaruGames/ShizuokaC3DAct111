//-----------------------------------------------------------------------------
// DInput.h : DirectInput���ȒP�ɗ��p���邽�߂̃��C�u����(�w�b�_)
//
//  								                    ver 2.8        2023.1.3
//
// Copyright (c) 2019 �É��Y�ƋZ�p���w�Z �Q�[���N���G�C�g�� All rights reserved.
//-----------------------------------------------------------------------------
#pragma  warning(disable : 4996)

#ifndef _DINPUT_H_
#define _DINPUT_H_

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>
#include <tchar.h>

//�K�v�ȃ��C�u�����t�@�C���̃��[�h
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dinput8.lib")

//-----------------------------------------------------------------------------
// key mode (ALL)
//-----------------------------------------------------------------------------
#define KD_DAT	0						// ���ڃf�[�^(���݂̃L�[�������)
#define KD_TRG	1						// �L�[���������u��
#define KD_UTRG	2						// �L�[�𗣂����u��

#define BufferSize	20
//-----------------------------------------------------------------------------
// mouse
//-----------------------------------------------------------------------------
#define DIM_LBUTTON	0
#define DIM_RBUTTON	1
#define DIM_MBUTTON	2

#define DIM_LEFT	10
#define DIM_RIGHT	11
#define DIM_UP		12
#define DIM_DOWN	13

//-----------------------------------------------------------------------------
// Joystick (�ő哯���ڑ���)
//-----------------------------------------------------------------------------
#define JOYSTICK_COUNT	(4)
#define JOY_PLAYER1		(0)
#define JOY_PLAYER2		(1)
#define JOY_PLAYER3		(2)
#define JOY_PLAYER4		(3)

//-----------------------------------------------------------------------------
// ForceFeedback Joystick ���ʁ@�R�Q��ނ܂�
//-----------------------------------------------------------------------------
#define JOY_EF_COUNT    32	

#define DIJ_VOLUME	850
//-----------------------------------------------------------------------------
// DirectInput scan code (Microsoft SideWinder game pad)
//-----------------------------------------------------------------------------
#define DIJ_A		0
#define DIJ_B		1
#define DIJ_C		2
#define DIJ_X		3
#define DIJ_Y		4
#define DIJ_Z		5
#define DIJ_L		6
#define DIJ_R		7
#define DIJ_START	8
#define DIJ_M		9
//-----------------------------------------------------------------------------
// ���E�㉺ (for Microsoft SideWinder game pad)
//-----------------------------------------------------------------------------
#define DIJ_LEFT	10
#define DIJ_RIGHT	11
#define DIJ_UP		12
#define DIJ_DOWN	13
//-----------------------------------------------------------------------------
// DirectInput scan code (Microsoft ForceFeedback Joystick)
//-----------------------------------------------------------------------------
#define DIF_FIRE		0
#define DIF_SHIELD		1
#define DIF_STOP		2
#define DIF_STOPD		3				// STOP�{�^���̉��̃{�^��
#define DIF_A			4
#define DIF_B			5
#define DIF_C			6
#define DIF_D			7
#define DIF_RESERVED	8
#define DIF_ARROW		9				// ���{�^��
#define DIF_THROW		-1				// �s��

#define DIF_LEFT		10
#define DIF_RIGHT		11
#define DIF_UP			12
#define DIF_DOWN		13
//-----------------------------------------------------------------------------
// �������f�o�C�X
//-----------------------------------------------------------------------------
#define INIT_KEYBOARD	1
#define INIT_MOUSE		2
#define INIT_JOYSTICK	4

#define DIMOFS_BUTTON(n) (FIELD_OFFSET(DIMOUSESTATE, rgbButtons) + (n))

#define DEADZONE		2500			// 25% of the axis range
#define RANGE_MAX		1000			// maximum positive axis value
#define RANGE_MIN		-1000			// minimum negative axis value
#define FF_CHILD		5000			// "Child" gain == 50%
#define FF_ADULT		7500			// "Adult" gain == 75%
#define FF_BODYBUILDER	10000			// "Bodybuilder" gain == 100%
//-----------------------------------------------------------------------------
// "effect flags" - these are internal identifiers and in no way map to DirectInput
//-----------------------------------------------------------------------------
#define EF_BOUNCE   0
#define EF_EXPLODE  1
#define EF_FIRE     2



// �c�����������h���������N���X
class CDirectInput
{
protected:
	//-----------------------------------------------------------------------------
	// common
	//-----------------------------------------------------------------------------
	HWND           m_hWnd;
	HRESULT        m_hr;
	float          m_ViewWidth;				// ��ʃT�C�Y�@��
	float          m_ViewHeight;			// ��ʃT�C�Y�@����
	LPDIRECTINPUT8 m_pDI8;					// DirectInput �I�u�W�F�N�g
	BYTE           m_diKeyState[256];		// DirectInput keyboard state
	DIMOUSESTATE   m_dims;				    // DirectInput mouse state
	DIJOYSTATE2    m_js[JOYSTICK_COUNT];	// DirectInput joystick state  2005.11.30
	BOOL           m_bInputActive;
	//-----------------------------------------------------------------------------
	// Keyboard
	//-----------------------------------------------------------------------------
	LPDIRECTINPUTDEVICE8 m_pKey;
	DWORD m_BufferRestKey;
	DWORD m_BufferRestBackupKey;
	DIDEVICEOBJECTDATA* m_pBufferKey;
	DIDEVICEOBJECTDATA* m_pBufferPositionKey;
	LPDIDEVICEOBJECTDATA m_didodKey;
	//-----------------------------------------------------------------------------
	// Mouse
	//-----------------------------------------------------------------------------
	LPDIRECTINPUTDEVICE8 m_pMouse;
	DWORD m_BufferRestMouse;
	DWORD m_BufferRestBackupMouse;
	DIDEVICEOBJECTDATA* m_pBufferMouse;
	DIDEVICEOBJECTDATA* m_pBufferPositionMouse;
	LPDIDEVICEOBJECTDATA m_didodMouse;
	//-----------------------------------------------------------------------------
	// Joystick
	//-----------------------------------------------------------------------------
	LPDIRECTINPUTDEVICE8 m_pJoy[JOYSTICK_COUNT];
	BOOL m_bJoyFF[JOYSTICK_COUNT];
	DWORD m_BufferRestJoy;
	DWORD m_BufferRestBackupJoy[JOYSTICK_COUNT];
	DIDEVICEOBJECTDATA* m_pBufferJoy[JOYSTICK_COUNT];
	DIDEVICEOBJECTDATA* m_pBufferPositionJoy;
	LPDIDEVICEOBJECTDATA m_didodJoy[JOYSTICK_COUNT];
	LPDIRECTINPUTEFFECT m_pJoyEffect[JOYSTICK_COUNT][JOY_EF_COUNT];
	int m_nJoySum;
	int m_nJoyFFNum;
	int m_nJoyEFSum;
	int m_nJoyEFI;

public:
	//-----------------------------------------------------------------------------
	// ����
	//-----------------------------------------------------------------------------
	CDirectInput(void);
	~CDirectInput();

	BOOL StartDirectInput(HINSTANCE, HWND, int, DWORD, DWORD);
	BOOL EndDirectInput(void);
	void SetAcquire(void);
	BOOL GetInput(void);
	//-----------------------------------------------------------------------------
	// Keyboard
	//-----------------------------------------------------------------------------
	BOOL GetKey(void);
	BOOL CheckKey(const int&, const DWORD&);
	BOOL InitKey(HWND);
	BOOL SetPropertyKey(void);
	//-----------------------------------------------------------------------------
	// Mouse
	//-----------------------------------------------------------------------------
	BOOL GetMouse(void);
	BOOL CheckMouse(const int&, const DWORD&);
	DIMOUSESTATE GetMouseState( void );
	POINT GetMousePos(); //�}�E�X�̌��݂̍��W���擾����
	void ShowMouseCursor(BOOL bFlag);
	BOOL InitMouse(HWND);
	BOOL SetPropertyMouse(void);
	//-----------------------------------------------------------------------------
	// Joystick
	//-----------------------------------------------------------------------------
	BOOL GetJoy(void);
	BOOL IfJoyFF(int nSum=JOY_PLAYER1);
	DIJOYSTATE2 GetJoyState(int nSum=JOY_PLAYER1);
	int  GetJoyNum(void);                                // -- 2018.8.27
	BOOL CheckJoy(const int&, const DWORD&, int nSum=JOY_PLAYER1);
	BOOL CheckUpDownLeftRight(int, DWORD, int nSum=JOY_PLAYER1);
	BOOL InitJoy(HWND);
	BOOL InitJoyNormal(HWND);
	BOOL InitJoyFF(HWND);
	BOOL SetPropertyJoy(void);
	BOOL CheckJoyImm(DWORD, int nSum=JOY_PLAYER1);
	BOOL PlayJoyEffect(int, int nNum=1, int nSum=JOY_PLAYER1);
	BOOL CreateJoyEffectStandard(void);
	BOOL ReadJoyEffect(TCHAR* szFName, int &nEffectNo, int &nNum);
	//-----------------------------------------------------------------------------
	// CALLBACK
	//-----------------------------------------------------------------------------
	BOOL EnumJoysticksCb(LPCDIDEVICEINSTANCE pInst, LPVOID lpvContext);
	BOOL EnumEffectsInFileCb(LPCDIFILEEFFECT lpdife, LPVOID pvRef );

};

#endif

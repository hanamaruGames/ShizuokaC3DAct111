//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�P�@�@�@�@�@�@                 ver 3.2        2023.1.31
//
//		���C������
//																Main.h
//=============================================================================

#pragma once

//�x����\��
#pragma warning(disable : 4005)
#pragma warning(disable : 4244)
#pragma warning(disable : 4018)
#pragma warning(disable : 4267)


//�w�b�_�[�t�@�C���̃C���N���[�h
#include <stdio.h>
#include <windows.h>

#include "resource.h"
#include "GameMain.h"


//�萔��`
//#define WINDOW_WIDTH   1920 //�E�B���h�E��
//#define WINDOW_HEIGHT  1080 //�E�B���h�E����

#define WINDOW_WIDTH   1366   //�E�B���h�E��
#define WINDOW_HEIGHT  768    //�E�B���h�E����

#define APP_NAME _T("C3DAct111 ��{�R�c�A�N�V�����Q�[��    ver3.2")

class CGameMain;

//  ---------------------------------------------------------
//  Windows���C���N���X
//  ---------------------------------------------------------
class CMain
{
public:
	// �����o�ϐ�
	CGameMain*	   m_pGMain;		  // �Q�[�����C���N���X
	HINSTANCE      m_hInstance;
	HWND           m_hWnd;
	BOOL           m_bLoopFlag;       // ���[�v�t���O�@TRUE:���[�v�@FALSE:���[�v�I��
	double         m_MainLoopTime;    // ���[�v�X�s�[�h�@1/60Sec

public:
	// ���\�b�h
	HRESULT InitWindow(HINSTANCE,INT,INT,INT,INT,LPCTSTR);
	LRESULT MsgProc(HWND,UINT,WPARAM,LPARAM);
	HRESULT Init();
	void    MessageLoop();
	BOOL    MessageProcess(MSG* msg);
	void    Loop();
	void    DispFps();
	void    Quit();
	CMain();
	~CMain();
};
// �֐��v���g�^�C�v�̐錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// imGUI2�̃v���g�^�C�v                                                       // -- 2020.8.7
LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

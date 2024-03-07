// =========================================================================================
//
//  �w�`���������Q�@
//																   ver 2.8        2019.2.25
// =========================================================================================

#pragma once

#define _WIN32_DCOM
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <xaudio2.h>
#include <tchar.h>

//�}�N����`
#define SAFE_RELEASE(x) if(x){x->Release(); x=0;}
#define SAFE_DELETE(x) if(x){delete x; x=0;}
#define SAFE_DELETE_ARRAY(p){ if(p){ delete[] (p);   (p)=NULL;}}

#define AUDIO_LOOP         1          // ���[�v�Đ�
#define AUDIO_SOURCE_MAX  10          // �����ɍĐ����铯��I�[�f�B�I�\�[�X�̍ő吔

// 
//  XAudio �}�X�^�[�N���X	
//  �A�v���Ɉ�K�v
// 
class CXAudio
{
public:
	// �����o�ϐ�
	HWND                    m_hWnd;
	IXAudio2*               m_pXAudio2;
	IXAudio2MasteringVoice* m_pMasteringVoice;

	// ���\�b�h
	HRESULT     InitAudio(HWND);

	CXAudio();
	~CXAudio();

};
// 
//  XAudio �\�[�X�{�C�X�N���X	
//  ��̃T�E���h�i�v�`�u�j�Ɉ�K�v
// 
class CXAudioSource
{
public:
	CXAudio*				m_pXAudio;			// XAudio �}�X�^�[�N���X�A�h���X	
	BOOL					m_bWav;				// �\�[�X���v�������t�@�C�����@TRUE:XAudio(WAV)�@FALSE:MCI(MP3��MID) 
	TCHAR                   m_szAliasName[256]; // Mci�̕ʖ�������

	DWORD                   m_dwSourceIndex;					//	�I�[�f�B�I�\�[�X�C���f�b�N�X
	DWORD                   m_dwSourceNum;						//	�I�[�f�B�I�\�[�X�̌�	
	IXAudio2SourceVoice*    m_pSourceVoice[AUDIO_SOURCE_MAX];  // �I�[�f�B�I�\�[�X
	BYTE*                   m_pWavBuffer[AUDIO_SOURCE_MAX];    // �g�`�f�[�^�i�t�H�[�}�b�g�����܂܂Ȃ��A�����ɔg�`�f�[�^�̂݁j
	DWORD                   m_dwWavSize[AUDIO_SOURCE_MAX];     // �g�`�f�[�^�̃T�C�Y

	HRESULT      Load(TCHAR* szFileName, DWORD dwNum=1);
	HRESULT      LoadAudio(TCHAR* szFileName, DWORD dwNum);
	HRESULT      LoadAudioSub(TCHAR* szFileName, DWORD dwIndex);
	HRESULT      LoadMci(TCHAR* szFileName);
	void         Play(int loop=0);
	void         PlayAudio(int loop=0);
	void         PlayMci(int loop=0);
	void         Stop();
	void         StopAudio();
	void         StopMci();
	void         Volume(float fVol);
	void         VolumeAudio(float fVol);
	void         VolumeMci(int nVol);
	
	CXAudioSource(CXAudio*	pXAudio);
	CXAudioSource(CXAudio*	pXAudio, TCHAR* szFileName, DWORD dwNum=1);
	~CXAudioSource();

};
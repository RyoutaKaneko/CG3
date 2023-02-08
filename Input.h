#pragma once
#include<windows.h>
#include<wrl.h>
#include"WinApp.h"

#define DIRECTINPUT_VERSION  0x0800 //DirectInput�̃o�[�W�����w��
#include <dinput.h>

class Input
{
public:
	//namespace�ȗ�
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: //�����o�֐�
	//������
	void Initialize(WinApp*winApp);
	//�X�V
	void Update();

	//������
	bool PushKey(BYTE keyNumber);

	//�������u��
	bool TriggerKey(BYTE keyNumber);

	//�������u��
	bool ReleasedKey(BYTE keyNumber);
private: //�����o�ϐ�

	// DirectInput�̃C���X�^���X
	ComPtr<IDirectInput8> directInput = nullptr;

	//�L�[�{�[�h�̃f�o�C�X
	ComPtr<IDirectInputDevice8> keyboard = nullptr;

	//�S�L�[�̏��
	BYTE key[256] = {};

	// �O��̑S�L�[�̏��
	BYTE keyPre[256] = {};

	//WindowsAPI
	WinApp* winApp = nullptr;
};


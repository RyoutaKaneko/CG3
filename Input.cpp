#include "Input.h"
#include <cassert>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

void Input::Initialize(WinApp*winApp)
{
	this->winApp = winApp;

	HRESULT result;

	//DirectInput�̏�����
	result = DirectInput8Create(
		winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	//�L�[�{�[�h�f�o�C�X�̐���
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));

	//���̓f�[�^�`���̃Z�b�g
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);  //�W���`��
	assert(SUCCEEDED(result));

	//�r�����䃌�x���̃Z�b�g
	result = keyboard->SetCooperativeLevel(
		winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
}

void Input::Update()
{

	//�O��̃L�[���͂�ۑ�
	memcpy(keyPre, key, sizeof(key));

	//�L�[�{�[�h���̎擾�J�n
	keyboard->Acquire();

	//�S�L�[�̓��͏�Ԃ��擾����
	keyboard->GetDeviceState(sizeof(key), key);
}

bool Input::PushKey(BYTE keyNumber)
{
	//�w��L�[�������Ă����true��Ԃ�
	if (key[keyNumber]) {
		return true;
	}
	//�����łȂ����false��Ԃ�
	return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
	// �w��L�[��O�t���[���ŉ����Ă��Ȃ��A���̃t���[���ŉ����Ă����true��Ԃ�
	if (!keyPre[keyNumber] && key[keyNumber]) {
		return true;
	}

	// �����łȂ����false��Ԃ�
	return false;
}

bool Input::ReleasedKey(BYTE keyNumber)
{
	// �w��L�[��O�t���[���ŉ����Ă��āA���̃t���[���ŉ����Ă��Ȃ����true��Ԃ�
	if (keyPre[keyNumber] && !key[keyNumber]) {
		return true;
	}

	// �����łȂ����false��Ԃ�
	return false;
}

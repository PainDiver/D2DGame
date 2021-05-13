#include "InputKeyboard.h"

InputKeyboard::InputKeyboard(HWND hWnd)
{
	di = NULL;
	diKeyboard = NULL;

	init(hWnd);
}

InputKeyboard::~InputKeyboard()
{
	release();
}

void InputKeyboard::release()
{
	if (diKeyboard != NULL) {
		diKeyboard->Unacquire();
		diKeyboard->Release();
		diKeyboard = NULL;
	}
	if (di != NULL) {
		di->Release();
		di = NULL;
	}
}

bool InputKeyboard::init(HWND hWnd)
{
	// DirectInput ��ü�� ������.

	if (FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&di, NULL))) {
		::MessageBox(NULL, "DirectInput8Create() failed!", "ERROR", MB_OK);
		return false;
	}

	// Ű���� ��ġ�� �ʱ�ȭ��.

	if (FAILED(di->CreateDevice(GUID_SysKeyboard, &diKeyboard, NULL))) {
		::MessageBox(NULL, "CreateDevice() failed!", "ERROR", MB_OK);
		return false;
	}

	if (FAILED(diKeyboard->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE))) {
		::MessageBox(NULL, "SetCooperativeLevel() failed!", "ERROR", MB_OK);
		return false;
	}

	if (FAILED(diKeyboard->SetDataFormat(&c_dfDIKeyboard))) {
		::MessageBox(NULL, "SetDataFormat() failed!", "ERROR", MB_OK);
		return false;
	}

	if (FAILED(diKeyboard->Acquire())) {
		::MessageBox(NULL, "Acquire() failed!", "ERROR", MB_OK);
		return false;
	}

	return true;
}

bool InputKeyboard::update()
{
	//Ű���� ��ġ�� ���¸� ������.
	if (FAILED(diKeyboard->GetDeviceState(sizeof(keyBuffer), (void*)&keyBuffer))) {
		::MessageBox(NULL,"GetDeviceState() failed!", "ERROR", MB_OK);
		return false;
	}

	return true;
}

bool InputKeyboard::keyPressed(int key)
{
	// Ű�� ������������ Ȯ����.
	if (keyBuffer[key] & 0x80) {
		return true;
	} else {
		return false;
	}
}

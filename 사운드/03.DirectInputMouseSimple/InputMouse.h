#pragma once

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#define DIMOUSE_LEFTBUTTON		0
#define DIMOUSE_RIGHTBUTTON		1
#define DIMOUSE_MIDDLEBUTTON	2
#define DIMOUSE_4BUTTON			3
#define DIMOUSE_5BUTTON			4
#define DIMOUSE_6BUTTON			5
#define DIMOUSE_7BUTTON			6
#define DIMOUSE_8BUTTON			7

class InputMouse
{
private:
	HWND hWnd; //WIN32
	DWORD screenWidth; //copy. ��ũ�� ũ��.
	DWORD screenHeight;

	IDirectInput8* di;
	IDirectInputDevice8* diMouse;
	DIMOUSESTATE2 mouseState; //���콺 ����.

	// ���콺 ����.
	DWORD mouseNumAxes; //���콺 ���� ����.
	DWORD mouseNumButtons; //���콺 ��ư�� ����.

	float mouseSensitivity; // ���콺 �ΰ���.

public:
	InputMouse(HWND _hWnd);
	~InputMouse();
	bool update();
	bool mouseButtonDown(int Button);

	// Ŀ���� ��� ����.
	float getRelativeX() { return (float)mouseState.lX * mouseSensitivity; }
	float getRelativeY() { return (float)mouseState.lY * mouseSensitivity; }
	float getRelativeZ() { return (float)mouseState.lZ * mouseSensitivity; }

	bool setScreenSize(DWORD _screenWidth, DWORD _screenHeight);

	// Ŀ���� ������ġ ����.
	void setCursorPos(POINT* pos);
	void getCursorPos(POINT* pos);
	void getString(char str[]);

private:
	bool init(HWND _hWnd);
	void release();

};

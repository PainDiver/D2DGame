#pragma once
#include <windows.h>

// �ڿ� ���� ��ȯ ��ũ��.
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p); (p)=NULL; } }
#define SAFE_DELETE(p) { if(p) { delete (p); (p)=NULL; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
#define SAFE_FREE(p) { if (p) { free(p); (p)=NULL; } }

namespace d2d
{
	// WIN32 ���� �Լ�.
	HWND initWin32(HINSTANCE hInstance, int width, int height);
	bool releaseWin32(HINSTANCE hInstance);
	int doMessageLoop( bool (*renderFunction)(float timeDelta));
}

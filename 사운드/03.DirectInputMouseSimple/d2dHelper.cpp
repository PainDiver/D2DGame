#include "d2dHelper.h"

HWND d2d::initWin32(HINSTANCE hInstance, int width, int height)
{
	HWND hWnd; //��ȯ�� ������ �ڵ�.
	WNDCLASSEX wc; //������ Ŭ���� ��ü.
	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
	// ������ Ŭ���� �Ӽ��� �ʱ�ȭ��.
	wc.cbSize = sizeof(WNDCLASSEX); //WNDCLASSEX ����ü�� ũ��.
	wc.style = CS_HREDRAW | CS_VREDRAW; //������ ��Ÿ��.
	wc.lpfnWndProc = (WNDPROC)WndProc; //������ ���ν��� �ּ�.
	wc.cbClsExtra = 0; //Ŭ���� �߰� ����.
	wc.cbWndExtra = 0; //������ �߰� ����.
	wc.hInstance = hInstance; //���� �ν��Ͻ��� �ڵ�.
	wc.hIcon = ::LoadIcon(NULL, IDI_APPLICATION); //������ ������.
	wc.hCursor = ::LoadCursor(NULL, IDC_ARROW); //���콺 Ŀ��.
	wc.hbrBackground = NULL; //��� ��.
	wc.lpszMenuName = NULL; //�޴�.
	wc.lpszClassName = "WinAppClass"; //������ Ŭ���� �̸�.
	wc.hIconSm = ::LoadIcon(NULL, IDI_APPLICATION); //�ּ�ȭ�� ������ ������.

	// ������ Ŭ������ �����.
	if (! ::RegisterClassEx(&wc)) {
		::MessageBox(NULL, "RegisterClassEx() - Failed", "ERROR", NULL);
		return false;
	}

	// â�� ũ�⸦ ������.
	RECT screenrect;
	DWORD dwWindowStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	::SetRect(&screenrect, 0, 0, width, height);
	::AdjustWindowRect(&screenrect, dwWindowStyle, false);
	
	// �� â�� ������.
	hWnd = ::CreateWindowEx(NULL, //Ȯ��� ��Ÿ��.
		"WinAppClass", //������ Ŭ����.
		"My Win Application", //������ �̸�.
		WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_SYSMENU | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, //������ ��Ÿ��.
		CW_USEDEFAULT, CW_USEDEFAULT, //X,Y��ǥ.
		screenrect.right - screenrect.left, screenrect.bottom - screenrect.top, //������ ũ��.
		NULL, //�θ� �������� �ڵ�.
		NULL, //�޴�.
		hInstance, //���� �ν��Ͻ��� �ڵ�.
		NULL); //�������� ������.
	if (! hWnd) {
		::MessageBox(NULL, "CreateWindowEx() - Failed", "ERROR", NULL);
		return 0;
	}

	::ShowWindow(hWnd, SW_SHOW);
	::UpdateWindow(hWnd);

	return hWnd;
}

bool d2d::releaseWin32(HINSTANCE hInstance)
{
	// ������ Ŭ������ unregister�Ѵ�.
	::UnregisterClass("WinAppClass", hInstance);
	return true;
}

int d2d::doMessageLoop(bool (*renderFunction)(float timeDelta))
{
	MSG msg;
	::ZeroMemory(&msg, sizeof(MSG));

	static float lastTime = (float)::timeGetTime(); 

	while (msg.message != WM_QUIT) {
		if (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else {
			float currTime = (float)timeGetTime();
			float timeDelta = (currTime - lastTime)*0.001f;

			if (! renderFunction(timeDelta)) {
				return 0;
			}

			lastTime = currTime;
		}
	}
	return (int)(msg.wParam);
}

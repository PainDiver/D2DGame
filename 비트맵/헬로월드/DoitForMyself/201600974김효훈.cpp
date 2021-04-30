#include <time.h>
#include <memory>
#include "DemoApp.h"

#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")

#define PI 3.141592
#define DEFAULTSCALEX 1280 
#define DEFAULTSCALEY 800

float scalex = 1;
float scaley = 1;
//201600974 �����а� ��ȿ��


// ���� ���α׷��� ������ �Լ�.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int /*nCmdShow*/)
{
	if (SUCCEEDED(CoInitialize(NULL)))
	{
		{
			DemoApp app;

			if (SUCCEEDED(app.Initialize(hInstance)))
			{
				app.RunMessageLoop();
			}
		}
		CoUninitialize();
	}

	return 0;
}

// ������. ��� �������� �ʱ�ȭ��.
DemoApp::DemoApp() :
	m_hwnd(NULL),
	m_pD2DFactory(NULL),
	m_pDWriteFactory(NULL),
	m_pRenderTarget(NULL),
	m_pTextFormat(NULL),
	m_pBlackBrush(NULL)
{

}

// �Ҹ���. ���� ���α׷��� �ڿ��� �ݳ���.
DemoApp::~DemoApp()
{
	SAFE_RELEASE(m_pD2DFactory);
	SAFE_RELEASE(m_pDWriteFactory);
	SAFE_RELEASE(m_pRenderTarget);
	SAFE_RELEASE(m_pTextFormat);
	SAFE_RELEASE(m_pBlackBrush);

}

// ���� ���α׷��� �����츦 ������. ��ġ ������ �ڿ��� ������.
HRESULT DemoApp::Initialize(HINSTANCE hInstance)
{
	HRESULT hr;

	// ��ġ ������ �ڿ��� ������.
	hr = CreateDeviceIndependentResources();
	if (SUCCEEDED(hr))
	{
		// Register the window class.
		WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = DemoApp::WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = sizeof(LONG_PTR);
		wcex.hInstance = hInstance;
		wcex.hbrBackground = NULL;
		wcex.lpszMenuName = NULL;
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.lpszClassName = L"D2DDemoApp";
		RegisterClassEx(&wcex);

		// �����츦 ������.
		m_hwnd = CreateWindow(
			L"D2DDemoApp", L"Direct2D Demo Application",
			WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
			640, 480, NULL, NULL, hInstance, this
		);
		hr = m_hwnd ? S_OK : E_FAIL;
		if (SUCCEEDED(hr))
		{
			ShowWindow(m_hwnd, SW_SHOWNORMAL);
			UpdateWindow(m_hwnd);
		}
	}

	return hr;
}


// ��ġ ������ �ڿ����� ������. �̵� �ڿ��� ������ ���� ���α׷��� ����Ǳ� ������ ��ȿ��.
HRESULT DemoApp::CreateDeviceIndependentResources()
{
	static const WCHAR msc_fontName[] = L"Verdana";
	static const FLOAT msc_fontSize = 50;
	HRESULT hr;

	// D2D ���丮�� ������.
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
	if (SUCCEEDED(hr))
	{
		// DirectWrite ���丮�� ������.
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(m_pDWriteFactory),
			reinterpret_cast<IUnknown**>(&m_pDWriteFactory)
		);
	}
	if (SUCCEEDED(hr))
	{
		//DirectWrite �ؽ�Ʈ ���� ��ü�� ������.
		hr = m_pDWriteFactory->CreateTextFormat(
			msc_fontName,
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			msc_fontSize,
			L"", //locale
			&m_pTextFormat
		);
	}
	if (SUCCEEDED(hr))
	{
		// �ؽ�Ʈ�� �������� �߾� �����ϰ� �������ε� �߾� ������.
		m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}

	return hr;
}

// ��ġ ������ �ڿ����� ������. ��ġ�� �ҽǵǴ� ��쿡�� �̵� �ڿ��� �ٽ� �����ؾ� ��.
HRESULT DemoApp::CreateDeviceResources()
{
	HRESULT hr = S_OK;

	if (!m_pRenderTarget)
	{

		RECT rc;
		GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top
		);

		// D2D ����Ÿ���� ������.
		hr = m_pD2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hwnd, size),
			&m_pRenderTarget
		);
		if (SUCCEEDED(hr))
		{
			// ������ ���� ������.
			hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBlackBrush);
		}

	}

	return hr;
}

// ��ġ ������ �ڿ����� �ݳ���. ��ġ�� �ҽǵǸ� �̵� �ڿ��� �ٽ� �����ؾ� ��.
void DemoApp::DiscardDeviceResources()
{
	SAFE_RELEASE(m_pRenderTarget);
	SAFE_RELEASE(m_pBlackBrush);
}

// ���� ������ �޽��� ������ ������.
void DemoApp::RunMessageLoop()
{
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

// Ŭ���̾�Ʈ ������ ȭ���� �׸�.
// ����: �� �Լ��� ����Ǵ� ���ȿ� ��ġ�� �ҽǵǸ� ��ġ ������ �ڿ����� �ݳ���. �� ���� ȣ�� �ÿ� �� �ڿ����� �ٽ� ������.
HRESULT DemoApp::OnRender()
{
	HRESULT hr;

	hr = CreateDeviceResources();

	// ȭ�鿡 "Hello, World"�� ǥ����.
	if (SUCCEEDED(hr))
	{
		static const WCHAR sc_helloWorld[] = L"Hello, World!";

		// ����Ÿ���� ũ�⸦ ����.
		D2D1_SIZE_F renderTargetSize = m_pRenderTarget->GetSize();

		m_pRenderTarget->BeginDraw();

		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

		m_pRenderTarget->DrawText(
			sc_helloWorld,
			ARRAYSIZE(sc_helloWorld) - 1,
			m_pTextFormat,
			D2D1::RectF(0, 0, renderTargetSize.width, renderTargetSize.height),
			m_pBlackBrush
		);

		hr = m_pRenderTarget->EndDraw();
		if (hr == D2DERR_RECREATE_TARGET)
		{
			hr = S_OK;
			DiscardDeviceResources();
		}
	}

	return hr;
}

// ���� ���α׷����� WM_SIZE �޽����� �߻��Ǹ� �� �Լ��� ����Ÿ���� ũ�⸦ �ٽ� ������.
void DemoApp::OnResize(UINT width, UINT height)
{
	if (m_pRenderTarget)
	{
		D2D1_SIZE_U size;
		size.width = width;
		size.height = height;

		// ����: �Ʒ��� �Լ��� ���� �ÿ� ������ ���� ������, ���⿡�� ���� ������ üũ���� �ʰ� �Ѿ�� ��. ������ EndDraw �Լ��� ȣ��� ���� ������ Ȯ�ε� ���̹Ƿ� �׶� ó���ϸ� ��.
		m_pRenderTarget->Resize(size);
	}
}

// The window message handler.
LRESULT CALLBACK DemoApp::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;

	if (message == WM_CREATE)
	{
		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
		DemoApp* pDemoApp = (DemoApp*)pcs->lpCreateParams;

		SetWindowLongPtrW(hwnd, GWLP_USERDATA, PtrToUlong(pDemoApp));

		result = 1;
	}
	else
	{
		DemoApp* pDemoApp = reinterpret_cast<DemoApp*>(static_cast<LONG_PTR>(GetWindowLongPtrW(hwnd, GWLP_USERDATA)));

		bool wasHandled = false;

		if (pDemoApp)
		{
			switch (message)
			{
			case WM_SIZE:
			{
				UINT width = LOWORD(lParam);
				UINT height = HIWORD(lParam);
				pDemoApp->OnResize(width, height);
			}
			wasHandled = true;
			result = 0;
			break;

			case WM_DISPLAYCHANGE:
			{
				InvalidateRect(hwnd, NULL, FALSE);
			}
			wasHandled = true;
			result = 0;
			break;

			case WM_PAINT:
			{
				pDemoApp->OnRender();

				ValidateRect(hwnd, NULL);
			}
			wasHandled = true;
			result = 0;
			break;

			case WM_DESTROY:
			{
				PostQuitMessage(0);
			}
			wasHandled = true;
			result = 1;
			break;
			}
		}

		if (!wasHandled)
		{
			result = DefWindowProc(hwnd, message, wParam, lParam);
		}
	}

	return result;
}

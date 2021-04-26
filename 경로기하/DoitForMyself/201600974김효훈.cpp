#include <time.h>
#include <memory>
#include "SecondHomeWork.h"

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
			SecondHomeWork app;
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
SecondHomeWork::SecondHomeWork() :
	m_hwnd(NULL),
	m_pDirect2dFactory(NULL),
	m_pRenderTarget(NULL),
	m_pSceneBrush(NULL),
	m_pGridPatternBitmapBrush(NULL),
	m_pLeftMountainGeometry(NULL),
	m_pRightMountainGeometry(NULL),
	m_pSunGeometry(NULL),
	m_pRiverGeometry(NULL),
	m_pRadialGradientBrush(NULL)
{
}

// �Ҹ���. ���� ���α׷��� �ڿ��� �ݳ���.
SecondHomeWork::~SecondHomeWork()
{
	DiscardDeviceResources();
	SAFE_RELEASE(m_pDirect2dFactory);
}

// ���� ���α׷��� �����츦 ������. ��ġ ������ �ڿ��� ������.
HRESULT SecondHomeWork::Initialize(HINSTANCE hInstance)
{
	HRESULT hr;

	// ��ġ ������ �ڿ��� ������.
	hr = CreateDeviceIndependentResources();

	if (SUCCEEDED(hr))
	{
		// ������ Ŭ������ �����..
		WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = SecondHomeWork::WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = sizeof(LONG_PTR);
		wcex.hInstance = hInstance;
		wcex.hbrBackground = NULL;
		wcex.lpszMenuName = NULL;
		wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
		wcex.lpszClassName = L"201600974�����а���ȿ��HW_2";
		RegisterClassEx(&wcex);

		// �����츦 ������.
		m_hwnd = CreateWindow(
			L"201600974�����а���ȿ��HW_2", L"201600974�����а���ȿ��HW_2",
			WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
			DEFAULTSCALEX, DEFAULTSCALEY, NULL, NULL, hInstance, this
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
HRESULT SecondHomeWork::CreateDeviceIndependentResources()
{
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);

	if (SUCCEEDED(hr))
	{
		hr = m_pDirect2dFactory->CreatePathGeometry(&m_pLeftMountainGeometry);
		if (SUCCEEDED(hr))
		{
			ID2D1GeometrySink* pSink = NULL;
			hr = m_pLeftMountainGeometry->Open(&pSink);
			if (SUCCEEDED(hr))
			{
				pSink->SetFillMode(D2D1_FILL_MODE_WINDING);

				pSink->BeginFigure(D2D1::Point2F(346, 255), D2D1_FIGURE_BEGIN_FILLED);
				D2D1_POINT_2F points[5] = {
				   D2D1::Point2F(267, 177),
				   D2D1::Point2F(236, 192),
				   D2D1::Point2F(212, 160),
				   D2D1::Point2F(156, 255),
				   D2D1::Point2F(346, 255),
				};
				pSink->AddLines(points, ARRAYSIZE(points));
				pSink->EndFigure(D2D1_FIGURE_END_CLOSED);

			}
			hr = pSink->Close();

			SAFE_RELEASE(pSink);
		}
	}

	if (SUCCEEDED(hr))
	{
		hr = m_pDirect2dFactory->CreatePathGeometry(&m_pRightMountainGeometry);
		if (SUCCEEDED(hr))
		{
			ID2D1GeometrySink* pSink = NULL;

			hr = m_pRightMountainGeometry->Open(&pSink);
			if (SUCCEEDED(hr))
			{
				pSink->SetFillMode(D2D1_FILL_MODE_WINDING);

				pSink->BeginFigure(D2D1::Point2F(575, 263), D2D1_FIGURE_BEGIN_FILLED);
				D2D1_POINT_2F points[] = {
				   D2D1::Point2F(481, 146),
				   D2D1::Point2F(449, 181),
				   D2D1::Point2F(433, 159),
				   D2D1::Point2F(401, 214),
				   D2D1::Point2F(381, 199),
				   D2D1::Point2F(323, 263),
				   D2D1::Point2F(575, 263)
				};
				pSink->AddLines(points, ARRAYSIZE(points));
				pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
			}
			hr = pSink->Close();

			SAFE_RELEASE(pSink);
		}
	}

	if (SUCCEEDED(hr))
	{

		hr = m_pDirect2dFactory->CreatePathGeometry(&m_pSunGeometry);
		if (SUCCEEDED(hr))
		{
			ID2D1GeometrySink* pSink = NULL;

			hr = m_pSunGeometry->Open(&pSink);
			if (SUCCEEDED(hr))
			{
				pSink->SetFillMode(D2D1_FILL_MODE_WINDING);

				pSink->BeginFigure(
					D2D1::Point2F(270, 255),
					D2D1_FIGURE_BEGIN_FILLED
				);
				pSink->AddArc(
					D2D1::ArcSegment(
						D2D1::Point2F(440, 255),
						D2D1::SizeF(85, 85),
						0.0f,
						D2D1_SWEEP_DIRECTION_CLOCKWISE,
						D2D1_ARC_SIZE_SMALL
					));
				pSink->EndFigure(D2D1_FIGURE_END_CLOSED);

				pSink->BeginFigure(
					D2D1::Point2F(299, 182),
					D2D1_FIGURE_BEGIN_HOLLOW
				);
				pSink->AddBezier(
					D2D1::BezierSegment(
						D2D1::Point2F(299, 182),
						D2D1::Point2F(294, 176),
						D2D1::Point2F(285, 178)
					));
				pSink->AddBezier(
					D2D1::BezierSegment(
						D2D1::Point2F(276, 179),
						D2D1::Point2F(272, 173),
						D2D1::Point2F(272, 173)
					));
				pSink->EndFigure(D2D1_FIGURE_END_OPEN);

				pSink->BeginFigure(
					D2D1::Point2F(354, 156),
					D2D1_FIGURE_BEGIN_HOLLOW
				);
				pSink->AddBezier(
					D2D1::BezierSegment(
						D2D1::Point2F(354, 156),
						D2D1::Point2F(358, 149),
						D2D1::Point2F(354, 142)
					));
				pSink->AddBezier(
					D2D1::BezierSegment(
						D2D1::Point2F(349, 134),
						D2D1::Point2F(354, 127),
						D2D1::Point2F(354, 127)
					));
				pSink->EndFigure(D2D1_FIGURE_END_OPEN);

				pSink->BeginFigure(
					D2D1::Point2F(322, 164),
					D2D1_FIGURE_BEGIN_HOLLOW
				);
				pSink->AddBezier(
					D2D1::BezierSegment(
						D2D1::Point2F(322, 164),
						D2D1::Point2F(322, 156),
						D2D1::Point2F(314, 152)
					));
				pSink->AddBezier(
					D2D1::BezierSegment(
						D2D1::Point2F(306, 149),
						D2D1::Point2F(305, 141),
						D2D1::Point2F(305, 141)
					));
				pSink->EndFigure(D2D1_FIGURE_END_OPEN);

				pSink->BeginFigure(
					D2D1::Point2F(385, 164),
					D2D1_FIGURE_BEGIN_HOLLOW
				);
				pSink->AddBezier(
					D2D1::BezierSegment(
						D2D1::Point2F(385, 164),
						D2D1::Point2F(392, 161),
						D2D1::Point2F(394, 152)
					));
				pSink->AddBezier(
					D2D1::BezierSegment(
						D2D1::Point2F(395, 144),
						D2D1::Point2F(402, 141),
						D2D1::Point2F(402, 142)
					));
				pSink->EndFigure(D2D1_FIGURE_END_OPEN);

				pSink->BeginFigure(
					D2D1::Point2F(408, 182),
					D2D1_FIGURE_BEGIN_HOLLOW
				);
				pSink->AddBezier(
					D2D1::BezierSegment(
						D2D1::Point2F(408, 182),
						D2D1::Point2F(416, 184),
						D2D1::Point2F(422, 178)
					));
				pSink->AddBezier(
					D2D1::BezierSegment(
						D2D1::Point2F(428, 171),
						D2D1::Point2F(435, 173),
						D2D1::Point2F(435, 173)
					));
				pSink->EndFigure(D2D1_FIGURE_END_OPEN);
			}
			hr = pSink->Close();

			SAFE_RELEASE(pSink);
		}
	}

	if (SUCCEEDED(hr))
	{
		hr = m_pDirect2dFactory->CreatePathGeometry(&m_pRiverGeometry);

		if (SUCCEEDED(hr))
		{
			ID2D1GeometrySink* pSink = NULL;

			hr = m_pRiverGeometry->Open(&pSink);
			if (SUCCEEDED(hr))
			{
				pSink->SetFillMode(D2D1_FILL_MODE_WINDING);
				pSink->BeginFigure(
					D2D1::Point2F(183, 392),
					D2D1_FIGURE_BEGIN_FILLED
				);
				pSink->AddBezier(
					D2D1::BezierSegment(
						D2D1::Point2F(238, 284),
						D2D1::Point2F(472, 345),
						D2D1::Point2F(356, 303)
					));
				pSink->AddBezier(
					D2D1::BezierSegment(
						D2D1::Point2F(237, 261),
						D2D1::Point2F(333, 256),
						D2D1::Point2F(333, 256)
					));
				pSink->AddBezier(
					D2D1::BezierSegment(
						D2D1::Point2F(335, 257),
						D2D1::Point2F(241, 261),
						D2D1::Point2F(411, 306)
					));
				pSink->AddBezier(
					D2D1::BezierSegment(
						D2D1::Point2F(574, 350),
						D2D1::Point2F(288, 324),
						D2D1::Point2F(296, 392)
					));
				pSink->EndFigure(D2D1_FIGURE_END_OPEN);
			}
			hr = pSink->Close();
			SAFE_RELEASE(pSink);
		}
	}
	return hr;
}


// ��ġ ������ �ڿ����� ������. ��ġ�� �ҽǵǴ� ��쿡�� �̵� �ڿ��� �ٽ� �����ؾ� ��.
HRESULT SecondHomeWork::CreateDeviceResources()
{
	HRESULT hr = S_OK;

	if (!m_pRenderTarget)
	{
		RECT rc;
		GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

		hr = m_pDirect2dFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hwnd, size),
			&m_pRenderTarget
		);

		if (SUCCEEDED(hr))
		{
			hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black, 1.f), &m_pSceneBrush);
		}

		// ����� ���� ���� ������.
		if (SUCCEEDED(hr))
		{
			// D2D1_GRADIENT_STOP ����ü �迭�� ������.
			ID2D1GradientStopCollection* pGradientStops = NULL;

			D2D1_GRADIENT_STOP gradientStops[3];
			gradientStops[0].color = D2D1::ColorF(D2D1::ColorF::Gold, 1);
			gradientStops[0].position = 0.0f;
			gradientStops[1].color = D2D1::ColorF(D2D1::ColorF::Orange, 0.8f);
			gradientStops[1].position = 0.85f;
			gradientStops[2].color = D2D1::ColorF(D2D1::ColorF::OrangeRed, 0.7f);
			gradientStops[2].position = 1.0f;

			// D2D1_GRADIENT_STOP ����ü �迭�κ��� ID2D1GradientStopCollection�� ������.
			hr = m_pRenderTarget->CreateGradientStopCollection(
				gradientStops,
				3,
				D2D1_GAMMA_2_2,
				D2D1_EXTEND_MODE_CLAMP,
				&pGradientStops
			);

			// ID2D1GradientStopCollection�κ��� ����� ���� ���� ������.
			if (SUCCEEDED(hr))
			{
				hr = m_pRenderTarget->CreateRadialGradientBrush(
					D2D1::RadialGradientBrushProperties(
						D2D1::Point2F(330, 330),
						D2D1::Point2F(140, 140),
						140,
						140),
					pGradientStops,
					&m_pRadialGradientBrush
				);
			}

			SAFE_RELEASE(pGradientStops);
		}

		if (SUCCEEDED(hr))
		{
			hr = CreateGridPatternBrush(m_pRenderTarget, &m_pGridPatternBitmapBrush);
		}

	}
	return hr;
}

// ��ġ ������ �ڿ����� �ݳ���. ��ġ�� �ҽǵǸ� �̵� �ڿ��� �ٽ� �����ؾ� ��.
void SecondHomeWork::DiscardDeviceResources()
{
	SAFE_RELEASE(m_pRenderTarget);
	SAFE_RELEASE(m_pSceneBrush);
	SAFE_RELEASE(m_pGridPatternBitmapBrush);
	SAFE_RELEASE(m_pRadialGradientBrush);
}

// ���� ������ �޽��� ������ ������.
void SecondHomeWork::RunMessageLoop()
{
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}



HRESULT SecondHomeWork::CreateGridPatternBrush(ID2D1RenderTarget* pRenderTarget, ID2D1BitmapBrush** ppBitmapBrush)
{
	HRESULT hr = S_OK;

	ID2D1BitmapRenderTarget* pCompatibleRenderTarget = NULL;
	hr = pRenderTarget->CreateCompatibleRenderTarget(D2D1::SizeF(10, 10), &pCompatibleRenderTarget);

	if (SUCCEEDED(hr))
	{
		ID2D1SolidColorBrush* pGridBrush = NULL;
		hr = pCompatibleRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(0.93f, 0.94f, 0.96f, 1)), &pGridBrush);

		if (SUCCEEDED(hr))
		{
			pCompatibleRenderTarget->BeginDraw();
			pCompatibleRenderTarget->FillRectangle(D2D1::RectF(0, 0, 10, 1), pGridBrush);
			pCompatibleRenderTarget->FillRectangle(D2D1::RectF(0, 0, 1, 10), pGridBrush);
			hr = pCompatibleRenderTarget->EndDraw();

			if (hr == D2DERR_RECREATE_TARGET)
			{
				SecondHomeWork::DiscardDeviceResources();
			}
			if (SUCCEEDED(hr))
			{
				ID2D1Bitmap* pGridBitmap = NULL;
				hr = pCompatibleRenderTarget->GetBitmap(&pGridBitmap);

				if (SUCCEEDED(hr))
				{
					hr = m_pRenderTarget->CreateBitmapBrush(
						pGridBitmap,
						D2D1::BitmapBrushProperties(D2D1_EXTEND_MODE_WRAP, D2D1_EXTEND_MODE_WRAP),
						ppBitmapBrush
					);

					pGridBitmap->Release();
				}
			}

			pGridBrush->Release();
		}

		pCompatibleRenderTarget->Release();
	}

	return hr;
}

// Ŭ���̾�Ʈ ������ ȭ���� �׸�.
// ����: �� �Լ��� ����Ǵ� ���ȿ� ��ġ�� �ҽǵǸ� ��ġ ������ �ڿ����� �ݳ���. �� ���� ȣ�� �ÿ� �� �ڿ����� �ٽ� ������.
HRESULT SecondHomeWork::OnRender()
{
	HRESULT hr = CreateDeviceResources();

	if (SUCCEEDED(hr))
	{
		m_pRenderTarget->BeginDraw();

		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

		D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();
		m_pRenderTarget->FillRectangle(D2D1::RectF(0, 0, rtSize.width, rtSize.height), m_pGridPatternBitmapBrush);

		m_pRenderTarget->FillGeometry(m_pSunGeometry, m_pRadialGradientBrush);

		m_pSceneBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Black, 1.f));
		m_pRenderTarget->DrawGeometry(m_pSunGeometry, m_pSceneBrush, 1.f);

		m_pSceneBrush->SetColor(D2D1::ColorF(D2D1::ColorF::OliveDrab, 1.f));
		m_pRenderTarget->FillGeometry(m_pLeftMountainGeometry, m_pSceneBrush);

		m_pSceneBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Black, 1.f));
		m_pRenderTarget->DrawGeometry(m_pLeftMountainGeometry, m_pSceneBrush, 1.f);

		m_pSceneBrush->SetColor(D2D1::ColorF(D2D1::ColorF::LightSkyBlue, 1.f));
		m_pRenderTarget->FillGeometry(m_pRiverGeometry, m_pSceneBrush);

		m_pSceneBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Black, 1.f));
		m_pRenderTarget->DrawGeometry(m_pRiverGeometry, m_pSceneBrush, 1.f);

		m_pSceneBrush->SetColor(D2D1::ColorF(D2D1::ColorF::YellowGreen, 1.f));
		m_pRenderTarget->FillGeometry(m_pRightMountainGeometry, m_pSceneBrush);

		m_pSceneBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Black, 1.f));
		m_pRenderTarget->DrawGeometry(m_pRightMountainGeometry, m_pSceneBrush, 1.f);

		hr = m_pRenderTarget->EndDraw();
	}

	if (hr == D2DERR_RECREATE_TARGET)
	{
		hr = S_OK;
		DiscardDeviceResources();
	}
	return hr;
}




// ���� ���α׷����� WM_SIZE �޽����� �߻��Ǹ� �� �Լ��� ����Ÿ���� ũ�⸦ �ٽ� ������.
void SecondHomeWork::OnResize(UINT width, UINT height)
{
	if (m_pRenderTarget)
	{
		// ����: �Ʒ��� �Լ��� ���� �ÿ� ������ ���� ������, ���⿡�� ���� ������ üũ���� �ʰ� �Ѿ�� ��. ������ EndDraw �Լ��� ȣ��� ���� ������ Ȯ�ε� ���̹Ƿ� �׶� ó���ϸ� ��.
		m_pRenderTarget->Resize(D2D1::SizeU(width, height));

		int x = (width) / 2;
		int y = (height) / 2;

		scalex = (float)(width) / DEFAULTSCALEX;
		scaley = (float)(height) / DEFAULTSCALEY;
	}
}

LRESULT CALLBACK SecondHomeWork::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;

	if (message == WM_CREATE)
	{
		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
		SecondHomeWork* pDemoApp = (SecondHomeWork*)pcs->lpCreateParams;
		
		SetWindowLongPtrW(hwnd, GWLP_USERDATA, PtrToUlong(pDemoApp));

		result = 1;
	}
	else
	{
		SecondHomeWork* pDemoApp = reinterpret_cast<SecondHomeWork*>(static_cast<LONG_PTR>(GetWindowLongPtrW(hwnd, GWLP_USERDATA)));

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

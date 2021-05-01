#include <time.h>
#include <vector>
#include <memory>
#include "Bullet.h"
#include "DemoApp.h"
#include "Character.h"

//#include <time.h>

#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")

//201600974 무역학과 김효훈

#define DEFAULTWIDTH 1920
#define DEFAULTHEIGHT 1024

#define BULLETATONCE 50

std::unique_ptr<Character> mainCharacter;
bool gameStart = true;
std::unique_ptr<Bullet[]> bullets;
std::vector<Bullet> bulletQueue;
bool shot = false;

// 응용 프로그램의 진입점 함수.
int WINAPI WinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int /*nCmdShow*/)
{
	if (SUCCEEDED(CoInitialize(NULL)))
	{
		{
			DemoApp app;

			if (SUCCEEDED(app.Initialize()))
			{
				app.RunMessageLoop();
			}
		}
		CoUninitialize();
	}
	return 0;
}

DemoApp::DemoApp() :
	m_hwnd(NULL),
	m_pD2DFactory(NULL),
	m_pRT(NULL),
	m_pPathGeometry(NULL),
	m_pObjectGeometry(NULL),
	m_pGradientBlackBrush(NULL),
	m_pYellowBrush(NULL),
	m_Animation(),
	m_pBuildingBitmap(NULL),
	m_pBuildingBitMask(NULL),
	m_pBuildingBitmapBrush(NULL),
	m_pFireBitmap(NULL),
	m_pFireBitmapBrush(NULL),
	m_pFireBitMask(NULL),
	m_pSkyBitmap(NULL),
	m_pWallBitmap(NULL),
	m_pLampostBitmap(NULL),
	m_pLampostBitmapBrush(NULL),
	m_pLampostBitMask(NULL),
	m_pCharacterBitmap(NULL),
	m_pCharacterBitmapBrush(NULL),
	m_pCharacterBitMask(NULL)
{
}

DemoApp::~DemoApp()
{
	SAFE_RELEASE(m_pD2DFactory);
	SAFE_RELEASE(m_pRT);
	SAFE_RELEASE(m_pPathGeometry);
	SAFE_RELEASE(m_pObjectGeometry);
	SAFE_RELEASE(m_pGradientBlackBrush);
	SAFE_RELEASE(m_pYellowBrush);

	SAFE_RELEASE(m_pBuildingBitmap);
	SAFE_RELEASE(m_pBuildingBitMask);
	SAFE_RELEASE(m_pBuildingBitmapBrush);

	SAFE_RELEASE(m_pFireBitmap);
	SAFE_RELEASE(m_pFireBitmapBrush);
	SAFE_RELEASE(m_pFireBitMask);

	SAFE_RELEASE(m_pSkyBitmap);
	SAFE_RELEASE(m_pWallBitmap);

	SAFE_RELEASE(m_pLampostBitmap);
	SAFE_RELEASE(m_pLampostBitmapBrush);
	SAFE_RELEASE(m_pLampostBitMask);

	SAFE_RELEASE(m_pCharacterBitmap);
	SAFE_RELEASE(m_pCharacterBitmapBrush);
	SAFE_RELEASE(m_pCharacterBitMask)
}

HRESULT DemoApp::Initialize()
{
	HRESULT hr;

	//register window class
	WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = DemoApp::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = sizeof(LONG_PTR);
	wcex.hInstance = HINST_THISCOMPONENT;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = NULL;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"D2DDemoApp";
	RegisterClassEx(&wcex);

	mainCharacter = std::make_unique<Character>();
	bullets = std::make_unique<Bullet[]>(20);
	for (int i = 0; i < BULLETATONCE; i++)
	{
		bulletQueue.push_back(bullets[i]);
	}

	hr = CreateDeviceIndependentResources();
	if (SUCCEEDED(hr))
	{
		m_hwnd = CreateWindow(
			L"D2DDemoApp", L"Direct2D Demo Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
			1920, 1024, NULL, NULL, HINST_THISCOMPONENT, this);
		hr = m_hwnd ? S_OK : E_FAIL;
		if (SUCCEEDED(hr))
		{
			float length = 0;
			hr = m_pPathGeometry->ComputeLength(NULL, &length);

			if (SUCCEEDED(hr))
			{
				m_Animation.SetStart(0); //start at beginning of path
				m_Animation.SetEnd(length); //length at end of path
				m_Animation.SetDuration(10.0f); //seconds

				ShowWindow(m_hwnd, SW_SHOWNORMAL);
				UpdateWindow(m_hwnd);
			}
		}
	}

	return hr;
}

HRESULT DemoApp::CreateDeviceIndependentResources()
{
	HRESULT hr;
	ID2D1GeometrySink* pSink = NULL;

	// D2D 팩토리를 생성함.
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);

	if (SUCCEEDED(hr))
	{
		hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pWICFactory));
	}

	if (SUCCEEDED(hr))
	{
		hr = m_pD2DFactory->CreatePathGeometry(&m_pPathGeometry);
	}
	if (SUCCEEDED(hr))
	{
		hr = m_pPathGeometry->Open(&pSink);
	}
	if (SUCCEEDED(hr))
	{
		D2D1_POINT_2F currentLocation = { 0, 0 };

		pSink->BeginFigure(D2D1::Point2F(0, 0), D2D1_FIGURE_BEGIN_FILLED);

		pSink->AddLine(D2D1::Point2F(0, 0));
		pSink->AddLine(D2D1::Point2F(14000, 0));

		pSink->EndFigure(D2D1_FIGURE_END_OPEN);

		hr = pSink->Close();
	}


	SAFE_RELEASE(pSink);

	// 간단한 삼각형 모양의 경로 기하를 생성함.
	if (SUCCEEDED(hr))
	{
		hr = m_pD2DFactory->CreatePathGeometry(&m_pObjectGeometry);
	}
	if (SUCCEEDED(hr))
	{
		hr = m_pObjectGeometry->Open(&pSink);
	}
	if (SUCCEEDED(hr))
	{
		pSink->BeginFigure(D2D1::Point2F(0.0f, 0.0f), D2D1_FIGURE_BEGIN_FILLED);

		const D2D1_POINT_2F ptBullet[] = { {-10.0f, -7.0f}, {-10.0f, 7.0f}, {0.f, 7.0f},{10.f,0.f },{0.f,-7.f},{-10.0f,-7.0f} };
		
		pSink->AddLines(ptBullet, 6);

		pSink->EndFigure(D2D1_FIGURE_END_OPEN);

		hr = pSink->Close();
	}

	SAFE_RELEASE(pSink);

	return hr;
}

HRESULT DemoApp::CreateDeviceResources()
{
	HRESULT hr = S_OK;

	if (!m_pRT)
	{
		RECT rc;
		GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);
		ID2D1GeometrySink* pGeometrySink = NULL;


		// D2D 렌더타겟을 생성함.
		hr = m_pD2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(m_hwnd, size), &m_pRT);


		//  첫 번째 기하를 생성함.
		const D2D1_ELLIPSE circle1 = D2D1::Ellipse(D2D1::Point2F(75.0f, 75.0f), 50.0f, 50.0f);
		hr = m_pD2DFactory->CreateEllipseGeometry(circle1, &m_pCircle1);

		// 두 번째 기하를 생성함.
		if (SUCCEEDED(hr))
		{
			const D2D1_ELLIPSE circle2 = D2D1::Ellipse(D2D1::Point2F(125.0f, 75.0f), 50.0f, 50.0f);
			hr = m_pD2DFactory->CreateEllipseGeometry(circle2, &m_pCircle2);
		}

		if (SUCCEEDED(hr))
		{
			hr = m_pD2DFactory->CreatePathGeometry(&m_pMoon);
			if (SUCCEEDED(hr))
			{
				hr = m_pMoon->Open(&pGeometrySink);
				if (SUCCEEDED(hr))
				{
					hr = m_pCircle1->CombineWithGeometry(m_pCircle2, D2D1_COMBINE_MODE_EXCLUDE, NULL, NULL, pGeometrySink);
				}
				if (SUCCEEDED(hr))
				{
					hr = pGeometrySink->Close();
				}
				SAFE_RELEASE(pGeometrySink);
			}
		}



		if (SUCCEEDED(hr))
		{
			hr = LoadBitmapFromFile(m_pRT, m_pWICFactory, L".\\building.png", 100, 0, &m_pBuildingBitmap);
		}

		if (SUCCEEDED(hr))
		{
			hr = LoadBitmapFromFile(m_pRT, m_pWICFactory, L".\\buildingMask.png", 100, 0, &m_pBuildingBitMask);
		}

		if (SUCCEEDED(hr))
		{
			hr = LoadBitmapFromFile(m_pRT, m_pWICFactory, L".\\Sky.jpg", 100, 0, &m_pSkyBitmap);
		}

		if (SUCCEEDED(hr))
		{
			hr = LoadBitmapFromFile(m_pRT, m_pWICFactory, L".\\Wall.jpg", 100, 0, &m_pWallBitmap);
		}
		if (SUCCEEDED(hr))
		{
			hr = LoadBitmapFromFile(m_pRT, m_pWICFactory, L".\\Lampost.png", 100, 0, &m_pLampostBitmap);
		}
		if (SUCCEEDED(hr))
		{
			hr = LoadBitmapFromFile(m_pRT, m_pWICFactory, L".\\LampostMask.png", 100, 0, &m_pLampostBitMask);
		}
		if (SUCCEEDED(hr))
		{
			hr = LoadBitmapFromFile(m_pRT, m_pWICFactory, L".\\Fire.png", 100, 0, &m_pFireBitmap);
		}
		if (SUCCEEDED(hr))
		{
			hr = LoadBitmapFromFile(m_pRT, m_pWICFactory, L".\\FireMask.png", 100, 0, &m_pFireBitMask);
		}

		if (SUCCEEDED(hr))
		{
			hr = LoadBitmapFromFile(m_pRT, m_pWICFactory, L".\\Character.png", 100, 0, &m_pCharacterBitmap);
		}
		if (SUCCEEDED(hr))
		{
			hr = LoadBitmapFromFile(m_pRT, m_pWICFactory, L".\\CharacterMask.png", 100, 0, &m_pCharacterBitMask);
		}


		if (SUCCEEDED(hr))
		{
			// 계조 명세 지점 구조체인 D2D1_GRADIENT_STOP 구조체의 배열을 생성.
			ID2D1GradientStopCollection* pGradientStops = NULL;

			D2D1_GRADIENT_STOP gradientStops[2];
			gradientStops[0].color = D2D1::ColorF(D2D1::ColorF::Yellow, 1);
			gradientStops[0].position = 0.0f;
			gradientStops[1].color = D2D1::ColorF(D2D1::ColorF::DimGray, 1);
			gradientStops[1].position = 1.0f;
			// D2D1_GRADIENT_STOP 구조체의 배열로부터 ID2D1GradientStopCollection 객체 생성.
			hr = m_pRT->CreateGradientStopCollection(gradientStops, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &pGradientStops);

			// ID2D1GradientStopCollection 객체로부터 선형 계조 붓 생성. 계조 축은 사각형의 왼쪽 상단 모서리에서 시작해서 오른쪽 하단 모서리에서 끝남.

			if (SUCCEEDED(hr))
			{
				hr = m_pRT->CreateRadialGradientBrush(D2D1::RadialGradientBrushProperties(D2D1::Point2F(0, 0), D2D1::Point2F(0, 0), 200, 200), pGradientStops, &m_pGradientBlackBrush);
			}

			SAFE_RELEASE(pGradientStops);
		}

		// 노란색 붓을 생성함.
		if (SUCCEEDED(hr))
		{
			hr = m_pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow), &m_pYellowBrush);
		}

		if (SUCCEEDED(hr))
		{
			D2D1_BITMAP_BRUSH_PROPERTIES propertiesXClampYClamp = D2D1::BitmapBrushProperties(D2D1_EXTEND_MODE_WRAP, D2D1_EXTEND_MODE_WRAP, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
			hr = m_pRT->CreateBitmapBrush(m_pBuildingBitmap, propertiesXClampYClamp, &m_pBuildingBitmapBrush);

			if (SUCCEEDED(hr))
			{
				hr = m_pRT->CreateBitmapBrush(m_pLampostBitmap, propertiesXClampYClamp, &m_pLampostBitmapBrush);
			}

			if (SUCCEEDED(hr))
			{
				hr = m_pRT->CreateBitmapBrush(m_pFireBitmap, propertiesXClampYClamp, &m_pFireBitmapBrush);
			}

			if (SUCCEEDED(hr))
			{
				hr = m_pRT->CreateBitmapBrush(m_pCharacterBitmap, propertiesXClampYClamp, &m_pCharacterBitmapBrush);
			}

		}
	}

	return hr;
}

void DemoApp::DiscardDeviceResources()
{
	SAFE_RELEASE(m_pRT);
	SAFE_RELEASE(m_pGradientBlackBrush);
	SAFE_RELEASE(m_pYellowBrush);

	SAFE_RELEASE(m_pBuildingBitmap);
	SAFE_RELEASE(m_pBuildingBitMask);
	SAFE_RELEASE(m_pBuildingBitmapBrush);

	SAFE_RELEASE(m_pLampostBitmap);
	SAFE_RELEASE(m_pLampostBitmapBrush);
	SAFE_RELEASE(m_pLampostBitMask);

	SAFE_RELEASE(m_pFireBitmap);
	SAFE_RELEASE(m_pFireBitmapBrush);
	SAFE_RELEASE(m_pFireBitMask);

	SAFE_RELEASE(m_pSkyBitmap);
	SAFE_RELEASE(m_pWallBitmap);

	SAFE_RELEASE(m_pCharacterBitmap);
	SAFE_RELEASE(m_pCharacterBitmapBrush);
	SAFE_RELEASE(m_pCharacterBitMask)
}

void DemoApp::RunMessageLoop()
{
	MSG msg;

	bool bdone = false;

	D2D1_SIZE_F characterSize = m_pCharacterBitmap->GetSize();
	mainCharacter->SetFirst(0, 0, characterSize.width, characterSize.height);

	while (!bdone)
	{
		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				bdone = true;
			}
			else
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
		}
	}
}

static float anim_time = 0.0f;
HRESULT DemoApp::OnRender()
{
	HRESULT hr;

	hr = CreateDeviceResources();
	if (SUCCEEDED(hr))
	{

		if (GetAsyncKeyState(VK_LEFT) < 0)
		{
			mainCharacter->lookLeft = true;
			if ((mainCharacter->GetLocation()->left >= -1000.f))
				mainCharacter->Move(false, -5.f);
		}
		if (GetAsyncKeyState(VK_RIGHT) < 0)
		{
			mainCharacter->lookLeft = false;
			if ((mainCharacter->GetLocation()->right <= 950.f))
				mainCharacter->Move(false, 5.f);
		}
		if (GetAsyncKeyState(VK_UP) < 0)
		{
			if ((mainCharacter->GetLocation()->top >= -150.f))
				mainCharacter->Move(true, -4.f);
		}
		if (GetAsyncKeyState(VK_DOWN) < 0)
		{
			if ((mainCharacter->GetLocation()->bottom <= 400.f))
				mainCharacter->Move(true, 4.f);
		}



		D2D1_POINT_2F point;
		D2D1_POINT_2F tangent;

		D2D1_SIZE_F rtSize = m_pRT->GetSize();
		float WidthScale = rtSize.width / 1920.f;
		float HeightScale = rtSize.height / 1280.f;

		D2D1_SIZE_F lampostSize = m_pLampostBitmap->GetSize();
		D2D1_SIZE_F buildingSize = m_pBuildingBitmap->GetSize();
		D2D1_SIZE_F wallSize = m_pWallBitmap->GetSize();
		D2D1_SIZE_F FireSize = m_pFireBitmap->GetSize();
		D2D1_SIZE_F characterSize = m_pCharacterBitmap->GetSize();

		D2D1::Matrix3x2F scale = D2D1::Matrix3x2F::Scale(WidthScale, HeightScale);
		D2D1::Matrix3x2F scale2 = D2D1::Matrix3x2F::Scale(2.f, 5.f);
		D2D1::Matrix3x2F translation = D2D1::Matrix3x2F::Translation(0, rtSize.height / 4.f);
		D2D1::Matrix3x2F spawn = D2D1::Matrix3x2F::Translation(rtSize.width / 2.f, rtSize.height / 1.5f);
		// 그리기를 준비함.
		m_pRT->BeginDraw();
		// 렌더타겟을 클리어함.

		m_pRT->Clear(D2D1::ColorF(D2D1::ColorF::DimGray));
		m_pRT->SetTransform(D2D1::Matrix3x2F::Identity());

		D2D1_ELLIPSE light = D2D1::Ellipse(D2D1::Point2F(0, 0), 200.f, 200.f);
		m_pRT->SetTransform(scale * translation * D2D1::Matrix3x2F::Translation(rtSize.width / 20.f, rtSize.height / 2.8f));
		for (int i = 1; i < 5; i++)
		{
			m_pRT->FillEllipse(&light, m_pGradientBlackBrush);
			m_pRT->SetTransform(scale * translation * D2D1::Matrix3x2F::Translation(rtSize.width / 20.f + (WidthScale * i * 600.f), rtSize.height / 2.8f));
		}

		m_pRT->SetTransform(scale);
		// 이동 동선 기하 경로가 화면 중심에 그려지도록 함.
		m_pRT->DrawBitmap(m_pSkyBitmap, D2D1::RectF(0, 0, 2000.f, 700.f));


		m_pRT->SetTransform(scale * scale2 * translation);
		D2D1_RECT_F rcBrushRect = D2D1::RectF(0, 0, FireSize.width, FireSize.height / 2);
		for (int i = 1; i < 7; i++)
		{
			m_pRT->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
			m_pRT->FillOpacityMask(m_pFireBitMask, m_pFireBitmapBrush, D2D1_OPACITY_MASK_CONTENT_GRAPHICS, &rcBrushRect);
			m_pRT->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
			rcBrushRect = D2D1::RectF(FireSize.width * i * 3.f, 0, FireSize.width * i * 4.f + FireSize.width, FireSize.height / 2);
		}

		m_pRT->SetTransform(scale * scale2 * translation);
		rcBrushRect = D2D1::RectF(0, 0, buildingSize.width, buildingSize.height);
		for (int i = 1; i < 15; i++)
		{
			m_pRT->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
			m_pRT->FillOpacityMask(m_pBuildingBitMask, m_pBuildingBitmapBrush, D2D1_OPACITY_MASK_CONTENT_GRAPHICS, &rcBrushRect);
			m_pRT->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
			rcBrushRect = D2D1::RectF(buildingSize.width * i, 0, buildingSize.width * i + buildingSize.width, buildingSize.height);
		}

		m_pRT->SetTransform(scale * D2D1::Matrix3x2F::Translation(0, rtSize.height / 2.2f));
		for (int i = 0; i < 20; i++)
			m_pRT->DrawBitmap(m_pWallBitmap, D2D1::RectF(wallSize.width * 1.5f * i, 0, wallSize.width * 1.5f * i + wallSize.width * 1.5f, wallSize.height * 2.5f));


		m_pRT->SetTransform(scale * D2D1::Matrix3x2F::Translation(rtSize.width / 4.f, rtSize.height / 15.f));
		m_pRT->FillGeometry(m_pMoon, m_pYellowBrush, NULL);


		m_pRT->SetTransform(scale * scale2 * translation);
		rcBrushRect = D2D1::RectF(0, 0, lampostSize.width, lampostSize.height);
		for (int i = 1; i < 5; i++)
		{
			m_pRT->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
			m_pRT->FillOpacityMask(m_pLampostBitMask, m_pLampostBitmapBrush, D2D1_OPACITY_MASK_CONTENT_GRAPHICS, &rcBrushRect);
			m_pRT->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
			rcBrushRect = D2D1::RectF(lampostSize.width * i * 3.f, 0.f, lampostSize.width * i * 3.f + lampostSize.width, lampostSize.height);
		}

		D2D1_MATRIX_3X2_F flip = D2D1::Matrix3x2F(-1.f, 0.f, 0.f, 1.f, 0.f, 0.f);		//이미지 반전을 위해 반전행렬을 만든다.
		D2D1_MATRIX_3X2_F restore = D2D1::Matrix3x2F::Translation(rtSize.width + characterSize.width * WidthScale, 0.f);	//반전행렬을 곱하면 x값이 전환되므로, 다시 이를 복원시켜줄 복원행렬을 만들어줌	
		m_pRT->SetTransform(scale * spawn * D2D1::Matrix3x2F::Translation(mainCharacter->GetLocation()->left * WidthScale, mainCharacter->GetLocation()->top * HeightScale));
		m_pRT->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);

		if (mainCharacter->lookLeft)
		{
			m_pRT->FillOpacityMask(m_pCharacterBitMask, m_pCharacterBitmapBrush, D2D1_OPACITY_MASK_CONTENT_GRAPHICS);
		}
		else if (!mainCharacter->lookLeft)
		{
			m_pRT->SetTransform(scale * spawn * flip * restore * D2D1::Matrix3x2F::Translation((mainCharacter->GetLocation()->left * WidthScale), mainCharacter->GetLocation()->top * HeightScale));
			m_pRT->FillOpacityMask(m_pCharacterBitMask, m_pCharacterBitmapBrush, D2D1_OPACITY_MASK_CONTENT_GRAPHICS);
		}
		m_pRT->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);



		D2D1::Matrix3x2F FirstLoc;
		for (int i = 0; i < bulletQueue.size(); i++)
		{
			QueryPerformanceFrequency(&m_nFrequency);
			QueryPerformanceCounter(&m_nPrevTime);
			if (shot == true && bulletQueue[i].isFlying==false)
			{
				bulletQueue[i].isFlying = true;
				shot = false;
			}
			if (bulletQueue[i].isFlying == true)
			{
				float length = m_Animation.GetValue(bulletQueue[i].anim_time);
				if (bulletQueue[i].anim_time == 0.f)
				{
					bulletQueue[i].y = mainCharacter->GetLocation()->bottom - 50.f;
					if (mainCharacter->lookLeft)
					{
						bulletQueue[i].flip = D2D1::Matrix3x2F(-1.f, 0.f, 0.f, 1.f, 0.f, 0.f);
						bulletQueue[i].restore = D2D1::Matrix3x2F::Translation(rtSize.width * WidthScale, 0.f);
						bulletQueue[i].x = mainCharacter->GetLocation()->left;
						bulletQueue[i].isLeft = true;
					}
					else
					{
						bulletQueue[i].x = mainCharacter->GetLocation()->right;
						bulletQueue[i].restore = D2D1::Matrix3x2F(1.f, 0.f, 0.f, 1.f, 0.f, 0.f);
						bulletQueue[i].flip = D2D1::Matrix3x2F(1.f, 0.f, 0.f, 1.f, 0.f, 0.f);
						bulletQueue[i].isLeft = false;
					}
				}
				if (bulletQueue[i].isLeft)
					bulletQueue[i].direction = D2D1::Matrix3x2F::Translation(-length, 0);
				else
					bulletQueue[i].direction = D2D1::Matrix3x2F::Translation(length, 0);

				FirstLoc = D2D1::Matrix3x2F::Translation(bulletQueue[i].x * WidthScale, bulletQueue[i].y * HeightScale);
				m_pRT->SetTransform(scale * spawn * bulletQueue[i].flip * bulletQueue[i].restore * FirstLoc * bulletQueue[i].direction);
				m_pRT->FillGeometry(m_pObjectGeometry, m_pGradientBlackBrush);

				LARGE_INTEGER CurrentTime;
				QueryPerformanceCounter(&CurrentTime);
				float elapsedTime = (float)((double)(CurrentTime.QuadPart - m_nPrevTime.QuadPart) / (double)(m_nFrequency.QuadPart));
				m_nPrevTime = CurrentTime;
				bulletQueue[i].anim_time += elapsedTime * 10000;

				if (bulletQueue[i].anim_time > 3.f)
				{
					bulletQueue[i].anim_time = 0.0f;
					bulletQueue[i].isFlying = false;
				}
			}
		}

		hr = m_pRT->EndDraw();

		if (hr == D2DERR_RECREATE_TARGET)
		{
			hr = S_OK;
			DiscardDeviceResources();

		}
		// 애니메이션의 끝에 도달하면 다시 처음으로 되돌려서 반복되도록 함.
	}
	return hr;
}

void DemoApp::OnResize(UINT width, UINT height)
{
	if (m_pRT)
	{
		D2D1_SIZE_U size;
		size.width = width;
		size.height = height;

		m_pRT->Resize(size);
	}
}

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
			result = 0;
			wasHandled = true;
			break;

			case WM_KEYUP:
			{
				if (wParam == 0x41)
				{
					shot = true;
					for (int i = 0; i < bulletQueue.size(); i++)
					{
						if (bulletQueue[i].isFlying == false)
							bulletQueue[i].anim_time = 0.0f;
					}
				}
			}
			result = 0;
			wasHandled = true;
			break;

			case WM_DISPLAYCHANGE:
			{
				InvalidateRect(hwnd, NULL, FALSE);
			}
			result = 0;
			wasHandled = true;
			break;

			case WM_PAINT:
			{
				pDemoApp->OnRender();

				// 여기에서 ValidateRect를 호출하지 말아야 OnRender 함수가 계속 반복 호출됨.
			}
			result = 0;
			wasHandled = true;
			break;

			case WM_DESTROY:
			{
				PostQuitMessage(0);
			}
			result = 1;
			wasHandled = true;
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

// Creates a Direct2D bitmap from the specified file name.
HRESULT DemoApp::LoadBitmapFromFile(ID2D1RenderTarget* pRenderTarget, IWICImagingFactory* pIWICFactory, PCWSTR uri, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap** ppBitmap)
{
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICStream* pStream = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICBitmapScaler* pScaler = NULL;

	HRESULT hr = pIWICFactory->CreateDecoderFromFilename(uri, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder);

	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}
	if (SUCCEEDED(hr))
	{
		// Convert the image format to 32bppPBGRA (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = pIWICFactory->CreateFormatConverter(&pConverter);
	}

	if (SUCCEEDED(hr))
	{
		// If a new width or height was specified, create an IWICBitmapScaler and use it to resize the image.
		if (destinationWidth != 0 || destinationHeight != 0)
		{
			UINT originalWidth, originalHeight;
			hr = pSource->GetSize(&originalWidth, &originalHeight);
			if (SUCCEEDED(hr))
			{
				if (destinationWidth == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationHeight) / static_cast<FLOAT>(originalHeight);
					destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
				}
				else if (destinationHeight == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationWidth) / static_cast<FLOAT>(originalWidth);
					destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
				}

				hr = pIWICFactory->CreateBitmapScaler(&pScaler);
				if (SUCCEEDED(hr))
				{
					hr = pScaler->Initialize(pSource, destinationWidth, destinationHeight, WICBitmapInterpolationModeCubic);
				}
				if (SUCCEEDED(hr))
				{
					hr = pConverter->Initialize(pScaler, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeMedianCut);
				}
			}
		}
		else // Don't scale the image.
		{
			hr = pConverter->Initialize(pSource, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeMedianCut);
		}
	}
	if (SUCCEEDED(hr))
	{
		// Create a Direct2D bitmap from the WIC bitmap.
		hr = pRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, ppBitmap);
	}

	SAFE_RELEASE(pDecoder);
	SAFE_RELEASE(pSource);
	SAFE_RELEASE(pStream);
	SAFE_RELEASE(pConverter);
	SAFE_RELEASE(pScaler);

	return hr;
}

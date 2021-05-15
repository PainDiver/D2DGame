#include <time.h>
#include <vector>
#include <memory>
#include "Bullet.h"
#include "ThirdHomework.h"
#include "Character.h"
#include "SoundManager.h"
//#include <time.h>

//201600974 무역학과 김효훈

#define DEFAULTWIDTH 1920
#define DEFAULTHEIGHT 1200

#define BULLETATONCE 50
#define MONSTERATONCE 40


std::shared_ptr<Character> g_MainCharacter;

std::vector<Bullet*> g_BulletVector;

std::vector<Monster*> g_MonsterVector;

CSoundManager* g_soundManager;
D2D1_SIZE_F g_rtSize;

bool g_Shot = false;
bool g_start;
int g_mNumber = 0;
bool g_musicInitialized;
bool g_volume = 0;
long g_SoundVolume = 0x8000;
int g_difficulty = 1;
unsigned int g_point = 0;

void ReleaseFSM();
bool UpdateFSM(float timeDelta);
void Spawn(std::vector<Monster*>* mv, int i);
void HitCheck(std::vector<Bullet*> bv, std::vector<Monster*> mv, ID2D1SolidColorBrush* bulletBrush);
void Move();

// 응용 프로그램의 진입점 함수.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int /*nCmdShow*/)
{
	waveOutSetVolume(0, g_SoundVolume);
	if (SUCCEEDED(CoInitialize(NULL)))
	{
		ForthHomework app;
		if (SUCCEEDED(app.Initialize()))
		{
			app.RunMessageLoop();
		}
		CoUninitialize();
	}
	ReleaseFSM();
	return 0;
}

ForthHomework::ForthHomework() :
	m_hwnd(NULL),
	m_pD2DFactory(NULL),
	m_pWICFactory(NULL),
	m_pMoon(NULL),
	m_pCircle1(NULL),
	m_pCircle2(NULL),
	m_pRT(NULL),
	m_pBulletPathgeometry(NULL),
	m_pGradientYellowBrush(NULL),
	m_pYellowBrush(NULL),
	m_pBlackBrush(NULL),
	m_pGrayBrush(NULL),
	m_Animation(),
	m_pTitleBitmap(NULL),
	m_pStreetBitmap(NULL),
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
	m_pCharacterBitMask(NULL),
	m_pCharacter2Bitmap(NULL),
	m_pCharacter2BitmapBrush(NULL),
	m_pCharacter2BitMask(NULL),
	m_pCharacter3Bitmap(NULL),
	m_pCharacter3BitmapBrush(NULL),
	m_pCharacter3BitMask(NULL),
	m_pCharacter4Bitmap(NULL),
	m_pCharacter4BitmapBrush(NULL),
	m_pCharacter4BitMask(NULL),
	m_pCharacter5Bitmap(NULL),
	m_pCharacter5BitmapBrush(NULL),
	m_pCharacter5BitMask(NULL),
	m_pCharacter6Bitmap(NULL),
	m_pCharacter6BitmapBrush(NULL),
	m_pCharacter6BitMask(NULL),
	m_pCharacter7Bitmap(NULL),
	m_pCharacter7BitmapBrush(NULL),
	m_pCharacter7BitMask(NULL),
	m_pMonster1Bitmap(NULL),
	m_pMonster1BitmapBrush(NULL),
	m_pMonster1BitMask(NULL),
	m_pMonster2Bitmap(NULL),
	m_pMonster2BitmapBrush(NULL),
	m_pMonster2BitMask(NULL),
	m_pMonster3Bitmap(NULL),
	m_pMonster3BitmapBrush(NULL),
	m_pMonster3BitMask(NULL),
	m_pBulletBrush(NULL)
{
}

ForthHomework::~ForthHomework()
{
	SAFE_RELEASE(m_pD2DFactory);
	SAFE_RELEASE(m_pRT);
	SAFE_RELEASE(m_pBulletPathgeometry);
	SAFE_RELEASE(m_pGradientYellowBrush);
	SAFE_RELEASE(m_pYellowBrush);
	SAFE_RELEASE(m_pBlackBrush);
	SAFE_RELEASE(m_pGrayBrush);
	SAFE_RELEASE(m_pBulletBrush);

	SAFE_RELEASE(m_pTitleBitmap);
	SAFE_RELEASE(m_pBuildingBitmap);
	SAFE_RELEASE(m_pBuildingBitMask);
	SAFE_RELEASE(m_pBuildingBitmapBrush);

	SAFE_RELEASE(m_pFireBitmap);
	SAFE_RELEASE(m_pFireBitmapBrush);
	SAFE_RELEASE(m_pFireBitMask);

	SAFE_RELEASE(m_pSkyBitmap);
	SAFE_RELEASE(m_pWallBitmap);
	SAFE_RELEASE(m_pStreetBitmap);

	SAFE_RELEASE(m_pLampostBitmap);
	SAFE_RELEASE(m_pLampostBitmapBrush);
	SAFE_RELEASE(m_pLampostBitMask);

	SAFE_RELEASE(m_pCharacterBitmap);
	SAFE_RELEASE(m_pCharacterBitmapBrush);
	SAFE_RELEASE(m_pCharacterBitMask)

	SAFE_RELEASE(m_pCharacter2Bitmap);
	SAFE_RELEASE(m_pCharacter2BitmapBrush);
	SAFE_RELEASE(m_pCharacter2BitMask)

	SAFE_RELEASE(m_pCharacter3Bitmap);
	SAFE_RELEASE(m_pCharacter3BitmapBrush);
	SAFE_RELEASE(m_pCharacter3BitMask);

	SAFE_RELEASE(m_pCharacter4Bitmap);
	SAFE_RELEASE(m_pCharacter4BitmapBrush);
	SAFE_RELEASE(m_pCharacter4BitMask);

	SAFE_RELEASE(m_pCharacter5Bitmap);
	SAFE_RELEASE(m_pCharacter5BitmapBrush);
	SAFE_RELEASE(m_pCharacter5BitMask);

	SAFE_RELEASE(m_pCharacter6Bitmap);
	SAFE_RELEASE(m_pCharacter6BitmapBrush);
	SAFE_RELEASE(m_pCharacter6BitMask);

	SAFE_RELEASE(m_pCharacter7Bitmap);
	SAFE_RELEASE(m_pCharacter7BitmapBrush);
	SAFE_RELEASE(m_pCharacter7BitMask);

	SAFE_RELEASE(m_pMonster1Bitmap);
	SAFE_RELEASE(m_pMonster1BitmapBrush);
	SAFE_RELEASE(m_pMonster1BitMask);

	SAFE_RELEASE(m_pMonster2Bitmap);
	SAFE_RELEASE(m_pMonster2BitmapBrush);
	SAFE_RELEASE(m_pMonster2BitMask)

	SAFE_RELEASE(m_pMonster3Bitmap);
	SAFE_RELEASE(m_pMonster3BitmapBrush);
	SAFE_RELEASE(m_pMonster3BitMask);

	SAFE_DELETE(g_soundManager);
}

void ReleaseFSM()
{
	for (std::vector <Monster*>::iterator iter = g_MonsterVector.begin(); iter != g_MonsterVector.end(); iter++)
	{
		Monster* ch = *iter;
		SAFE_DELETE(ch);
	}
	g_MonsterVector.clear();

	for (std::vector <Bullet*>::iterator iter = g_BulletVector.begin(); iter != g_BulletVector.end(); iter++)
	{
		Bullet* bl = *iter;
		SAFE_DELETE(bl);
	}
	g_BulletVector.clear();
}



HRESULT ForthHomework::Initialize()
{
	HRESULT hr;

	//register window class
	WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = ForthHomework::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = sizeof(LONG_PTR);
	wcex.hInstance = HINST_THISCOMPONENT;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = NULL;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"D2DDemoApp";
	RegisterClassEx(&wcex);


	hr = CreateDeviceIndependentResources();
	if (SUCCEEDED(hr))
	{
		m_hwnd = CreateWindow(
			L"D2DDemoApp", L"Direct2D Demo Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
			DEFAULTWIDTH, DEFAULTHEIGHT, NULL, NULL, HINST_THISCOMPONENT, this);
		hr = m_hwnd ? S_OK : E_FAIL;
	}

	g_MainCharacter = std::make_shared<Character>();

	for (int i = 0; i < BULLETATONCE; i++)
	{
		g_BulletVector.push_back(new Bullet());
	}

	for (int i = 0; i < MONSTERATONCE; i++)
	{
		DWORD enemyStateTransitions[][3] = {
			{ Monster::STATE_STAND, Monster::EVENT_FINDTARGET, Monster::STATE_FOLLOW },
			{ Monster::STATE_MOVE, Monster::EVENT_FINDTARGET, Monster::STATE_FOLLOW },
			{ Monster::STATE_ATTACK, Monster::EVENT_OUTOFATTACK, Monster::STATE_FOLLOW },
			{ Monster::STATE_FOLLOW, Monster::EVENT_WITHINATTACK, Monster::STATE_ATTACK },
			{ Monster::STATE_FOLLOW, Monster::EVENT_GOTHIT,Monster::STATE_RAGE},
			{ Monster::STATE_RAGE, Monster::EVENT_FINDTARGET, Monster::STATE_FOLLOW}
		};
		g_MonsterVector.push_back(new Monster(Monster::TYPE_AI, enemyStateTransitions, 6));
	}


	if (SUCCEEDED(hr))
	{
		m_Animation.SetStart(0); //start at beginning of path
		m_Animation.SetEnd(DEFAULTWIDTH); //length at end of path
		m_Animation.SetDuration(2.0f); //seconds

		ShowWindow(m_hwnd, SW_SHOWNORMAL);
		UpdateWindow(m_hwnd);
	}
	if (SUCCEEDED(hr))
	{
		D2D1_SIZE_F characterSize = m_pCharacterBitmap->GetSize();
		g_rtSize = m_pRT->GetSize();
		g_MainCharacter->SetLocation((g_rtSize.width / 2.f) - (characterSize.width / 2), g_rtSize.height / 1.45f - (characterSize.height / 2), (g_rtSize.width / 2.f) + (characterSize.width / 2), g_rtSize.height / 1.45f + (characterSize.height / 2));
		g_MainCharacter->SetAlive(true);

	}


	g_soundManager = new CSoundManager;
	if (!g_soundManager->init(m_hwnd))
		return FALSE;

	// 사운드 파일을 추가함.
	int id;
	LPWSTR name = new TCHAR[20];

	wsprintf(name, L"start.wav");
	if (!g_soundManager->add(name, &id))
		return FALSE;

	wsprintf(name, L"bgm1.wav");
	if (!g_soundManager->add(name, &id))
		return FALSE;

	wsprintf(name, L"bgm2.wav");
	if (!g_soundManager->add(name, &id))
		return FALSE;

	wsprintf(name, L"bgm3.wav");
	if (!g_soundManager->add(name, &id))
		return FALSE;

	wsprintf(name, L"bgm4.wav");
	if (!g_soundManager->add(name, &id))
		return FALSE;

	wsprintf(name, L"bgm5.wav");
	if (!g_soundManager->add(name, &id))
		return FALSE;

	wsprintf(name, L"gunShot.wav");
	if (!g_soundManager->add(name, &id)) 
		return FALSE;

	wsprintf(name, L"monsterAttack.wav");
	if (!g_soundManager->add(name, &id)) 
		return FALSE;

	wsprintf(name, L"GameOver.wav");
	if (!g_soundManager->add(name, &id)) 
		return FALSE;
	wsprintf(name, L"CharacterDead.wav");
	if (!g_soundManager->add(name, &id)) 
		return FALSE;

	wsprintf(name, L"ZombieDead.wav");
	if (!g_soundManager->add(name, &id))
		return FALSE;

	wsprintf(name, L"ZombieRage.wav");
	if (!g_soundManager->add(name, &id))
		return FALSE;
	wsprintf(name, L"ZombieHit.wav");
	if (!g_soundManager->add(name, &id)) 
		return FALSE;


	g_musicInitialized = true;

	return hr;
}

HRESULT ForthHomework::CreateDeviceIndependentResources()
{
	HRESULT hr;
	ID2D1GeometrySink* pSink = NULL;
	static const WCHAR msc_fontName[] = L"Verdana";
	static const FLOAT msc_fontSize = 25;

	// D2D 팩토리를 생성함.
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);

	if (SUCCEEDED(hr))
	{
		hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pWICFactory));
	}

	// 총알 생성
	if (SUCCEEDED(hr))
	{
		hr = m_pD2DFactory->CreatePathGeometry(&m_pBulletPathgeometry);
	}
	if (SUCCEEDED(hr))
	{
		hr = m_pBulletPathgeometry->Open(&pSink);
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

	if (SUCCEEDED(hr))
	{
		// DirectWrite 팩토리를 생성함.
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(m_pDWriteFactory),
			reinterpret_cast<IUnknown**>(&m_pDWriteFactory)
		);
	}
	if (SUCCEEDED(hr))
	{
		//DirectWrite 텍스트 포맷 객체를 생성함.
		hr = m_pDWriteFactory->CreateTextFormat(
			msc_fontName,
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			msc_fontSize,
			L"ko-kr", //locale
			&m_pTextFormat
		);
	}
	if (SUCCEEDED(hr))
	{
		// 텍스트를 수평으로 중앙 정렬하고 수직으로도 중앙 정렬함.
		m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}

	return hr;
}

HRESULT ForthHomework::CreateDeviceResources()
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
			hr = LoadBitmapFromFile(m_pRT, m_pWICFactory, L".\\Sky.png", 100, 0, &m_pSkyBitmap);
		}

		if (SUCCEEDED(hr))
		{
			hr = LoadBitmapFromFile(m_pRT, m_pWICFactory, L".\\Wall.png", 100, 0, &m_pWallBitmap);
		}
		if (SUCCEEDED(hr))
		{
			hr = LoadBitmapFromFile(m_pRT, m_pWICFactory, L".\\Street.png", 100, 0, &m_pStreetBitmap);
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
			hr = LoadBitmapFromFile(m_pRT, m_pWICFactory, L".\\Character2.png", 100, 0, &m_pCharacter2Bitmap);
		}
		if (SUCCEEDED(hr))
		{
			hr = LoadBitmapFromFile(m_pRT, m_pWICFactory, L".\\Character2Mask.png", 100, 0, &m_pCharacter2BitMask);
		}

		if (SUCCEEDED(hr))
		{
			hr = LoadBitmapFromFile(m_pRT, m_pWICFactory, L".\\Character3.png", 100, 0, &m_pCharacter3Bitmap);
		}
		if (SUCCEEDED(hr))
		{
			hr = LoadBitmapFromFile(m_pRT, m_pWICFactory, L".\\Character3Mask.png", 100, 0, &m_pCharacter3BitMask);
		}

		if (SUCCEEDED(hr))
		{
			hr = LoadBitmapFromFile(m_pRT, m_pWICFactory, L".\\Character4.png", 100, 0, &m_pCharacter4Bitmap);
		}
		if (SUCCEEDED(hr))
		{
			hr = LoadBitmapFromFile(m_pRT, m_pWICFactory, L".\\Character4Mask.png", 100, 0, &m_pCharacter4BitMask);
		}

		if (SUCCEEDED(hr))
		{
			hr = LoadBitmapFromFile(m_pRT, m_pWICFactory, L".\\Character5.png", 100, 0, &m_pCharacter5Bitmap);
		}
		if (SUCCEEDED(hr))
		{
			hr = LoadBitmapFromFile(m_pRT, m_pWICFactory, L".\\Character5Mask.png", 100, 0, &m_pCharacter5BitMask);
		}
		if (SUCCEEDED(hr))
		{
			hr = LoadBitmapFromFile(m_pRT, m_pWICFactory, L".\\Character6.png", 100, 0, &m_pCharacter6Bitmap);
		}
		if (SUCCEEDED(hr))
		{
			hr = LoadBitmapFromFile(m_pRT, m_pWICFactory, L".\\Character6Mask.png", 100, 0, &m_pCharacter6BitMask);
		}
		if (SUCCEEDED(hr))
		{
			hr = LoadBitmapFromFile(m_pRT, m_pWICFactory, L".\\Character7.png", 100, 0, &m_pCharacter7Bitmap);
		}
		if (SUCCEEDED(hr))
		{
			hr = LoadBitmapFromFile(m_pRT, m_pWICFactory, L".\\Character7Mask.png", 100, 0, &m_pCharacter7BitMask);
		}
		if (SUCCEEDED(hr))
		{
			hr = LoadBitmapFromFile(m_pRT, m_pWICFactory, L".\\Title.png", 100, 0, &m_pTitleBitmap);
		}

		if (SUCCEEDED(hr))
		{
			hr = LoadBitmapFromFile(m_pRT, m_pWICFactory, L".\\Monster1.png", 100, 0, &m_pMonster1Bitmap);
		}
		if (SUCCEEDED(hr))
		{
			hr = LoadBitmapFromFile(m_pRT, m_pWICFactory, L".\\Monster1Mask.png", 100, 0, &m_pMonster1BitMask);
		}

		if (SUCCEEDED(hr))
		{
			hr = LoadBitmapFromFile(m_pRT, m_pWICFactory, L".\\Monster2.png", 100, 0, &m_pMonster2Bitmap);
		}
		if (SUCCEEDED(hr))
		{
			hr = LoadBitmapFromFile(m_pRT, m_pWICFactory, L".\\Monster2Mask.png", 100, 0, &m_pMonster2BitMask);
		}
		if (SUCCEEDED(hr))
		{
			hr = LoadBitmapFromFile(m_pRT, m_pWICFactory, L".\\Monster3.png", 100, 0, &m_pMonster3Bitmap);
		}
		if (SUCCEEDED(hr))
		{
			hr = LoadBitmapFromFile(m_pRT, m_pWICFactory, L".\\Monster3Mask.png", 100, 0, &m_pMonster3BitMask);
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
				hr = m_pRT->CreateRadialGradientBrush(D2D1::RadialGradientBrushProperties(D2D1::Point2F(0, 0), D2D1::Point2F(0, 0), 200, 200), pGradientStops, &m_pGradientYellowBrush);
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
			hr = m_pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBlackBrush);
		}

		if (SUCCEEDED(hr))
		{
			hr = m_pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &m_pGrayBrush);
		}

		if (SUCCEEDED(hr))
		{
			hr = m_pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow), &m_pBulletBrush);
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

			if (SUCCEEDED(hr))
			{
				hr = m_pRT->CreateBitmapBrush(m_pCharacter2Bitmap, propertiesXClampYClamp, &m_pCharacter2BitmapBrush);
			}

			if (SUCCEEDED(hr))
			{
				hr = m_pRT->CreateBitmapBrush(m_pCharacter3Bitmap, propertiesXClampYClamp, &m_pCharacter3BitmapBrush);
			}

			if (SUCCEEDED(hr))
			{
				hr = m_pRT->CreateBitmapBrush(m_pCharacter4Bitmap, propertiesXClampYClamp, &m_pCharacter4BitmapBrush);
			}
			if (SUCCEEDED(hr))
			{
				hr = m_pRT->CreateBitmapBrush(m_pCharacter5Bitmap, propertiesXClampYClamp, &m_pCharacter5BitmapBrush);
			}
			if (SUCCEEDED(hr))
			{
				hr = m_pRT->CreateBitmapBrush(m_pCharacter6Bitmap, propertiesXClampYClamp, &m_pCharacter6BitmapBrush);
			}
			if (SUCCEEDED(hr))
			{
				hr = m_pRT->CreateBitmapBrush(m_pCharacter7Bitmap, propertiesXClampYClamp, &m_pCharacter7BitmapBrush);
			}
			if (SUCCEEDED(hr))
			{
				hr = m_pRT->CreateBitmapBrush(m_pMonster1Bitmap, propertiesXClampYClamp, &m_pMonster1BitmapBrush);
			}
			if (SUCCEEDED(hr))
			{
				hr = m_pRT->CreateBitmapBrush(m_pMonster2Bitmap, propertiesXClampYClamp, &m_pMonster2BitmapBrush);
			}
			if (SUCCEEDED(hr))
			{
				hr = m_pRT->CreateBitmapBrush(m_pMonster3Bitmap, propertiesXClampYClamp, &m_pMonster3BitmapBrush);
			}
		}
	}

	return hr;
}

void ForthHomework::DiscardDeviceResources()
{
	SAFE_RELEASE(m_pRT);
	SAFE_RELEASE(m_pGradientYellowBrush);
	SAFE_RELEASE(m_pYellowBrush);
	SAFE_RELEASE(m_pBlackBrush);
	SAFE_RELEASE(m_pGrayBrush);
	SAFE_RELEASE(m_pBulletBrush);

	SAFE_RELEASE(m_pTitleBitmap);
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
	SAFE_RELEASE(m_pStreetBitmap);

	SAFE_RELEASE(m_pCharacterBitmap);
	SAFE_RELEASE(m_pCharacterBitmapBrush);
	SAFE_RELEASE(m_pCharacterBitMask)

		SAFE_RELEASE(m_pCharacter2Bitmap);
	SAFE_RELEASE(m_pCharacter2BitmapBrush);
	SAFE_RELEASE(m_pCharacter2BitMask)

		SAFE_RELEASE(m_pCharacter3Bitmap);
	SAFE_RELEASE(m_pCharacter3BitmapBrush);
	SAFE_RELEASE(m_pCharacter3BitMask)

		SAFE_RELEASE(m_pCharacter4Bitmap);
	SAFE_RELEASE(m_pCharacter4BitmapBrush);
	SAFE_RELEASE(m_pCharacter4BitMask);

	SAFE_RELEASE(m_pCharacter5Bitmap);
	SAFE_RELEASE(m_pCharacter5BitmapBrush);
	SAFE_RELEASE(m_pCharacter5BitMask);

	SAFE_RELEASE(m_pCharacter6Bitmap);
	SAFE_RELEASE(m_pCharacter6BitmapBrush);
	SAFE_RELEASE(m_pCharacter6BitMask);

	SAFE_RELEASE(m_pCharacter7Bitmap);
	SAFE_RELEASE(m_pCharacter7BitmapBrush);
	SAFE_RELEASE(m_pCharacter7BitMask);

	SAFE_RELEASE(m_pMonster1Bitmap);
	SAFE_RELEASE(m_pMonster1BitmapBrush);
	SAFE_RELEASE(m_pMonster1BitMask);

	SAFE_RELEASE(m_pMonster2Bitmap);
	SAFE_RELEASE(m_pMonster2BitmapBrush);
	SAFE_RELEASE(m_pMonster2BitMask)

		SAFE_RELEASE(m_pMonster3Bitmap);
	SAFE_RELEASE(m_pMonster3BitmapBrush);
	SAFE_RELEASE(m_pMonster3BitMask);
}

void ForthHomework::RunMessageLoop()
{
	MSG msg;
	bool bdone = false;
	srand(time(NULL));
	static float lastTime = (float)::timeGetTime();
	float delay = 0;
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
				float currTime = (float)timeGetTime();
				float timeDelta = (currTime - lastTime) * 0.001f;
				int random = rand() % MONSTERATONCE;
				int percent = rand() % 100000 / g_difficulty;
				if (percent < 1000)
					Spawn(&g_MonsterVector, random);

				if (g_MainCharacter->GetAlive() == false)
				{
					g_soundManager->play((int)track::CharacterDead, false);
					g_soundManager->play((int)track::GameOver, false);
					Sleep(3500);
					return;
				}

				UpdateFSM(timeDelta);
				lastTime = currTime;
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);

			}
		}
	}
}

void Move()
{
	if (g_MainCharacter->GetAlive())
	{
		if (g_MainCharacter->m_IsMoving == false && g_MainCharacter->m_AnimTime[g_MainCharacter->m_AnimPose] == 0.f)
		{
			for (int i = 0; i < 7; i++)
			{
				g_MainCharacter->m_AnimTime[i] = 0.f;
			}
			g_MainCharacter->m_AnimPose = (int)m_state::idle;
		}

		if (GetAsyncKeyState(VK_LEFT) < 0)
		{
			g_MainCharacter->m_LookLeft = true;
			if ((g_MainCharacter->GetLocation().left >= 0))
				g_MainCharacter->Move(false, -5.f);
			if (g_MainCharacter->m_IsMoving == false)
				g_MainCharacter->m_AnimPose = (int)m_state::step;
			g_MainCharacter->m_IsMoving = true;

		}
		if (GetAsyncKeyState(VK_RIGHT) < 0)
		{
			g_MainCharacter->m_LookLeft = false;
			if ((g_MainCharacter->GetLocation().right <= DEFAULTWIDTH))
				g_MainCharacter->Move(false, 5.f);
			if (g_MainCharacter->m_IsMoving == false)
				g_MainCharacter->m_AnimPose = (int)m_state::step;
			g_MainCharacter->m_IsMoving = true;

		}
		if (GetAsyncKeyState(VK_UP) < 0)
		{
			if ((g_MainCharacter->GetLocation().bottom >= (DEFAULTHEIGHT / 1.6f)))
				g_MainCharacter->Move(true, -4.f);
			if (g_MainCharacter->m_IsMoving == false)
				g_MainCharacter->m_AnimPose = (int)m_state::step;
			g_MainCharacter->m_IsMoving = true;

		}
		if (GetAsyncKeyState(VK_DOWN) < 0)
		{
			if ((g_MainCharacter->GetLocation().bottom <= (DEFAULTHEIGHT) / 1.1f))
				g_MainCharacter->Move(true, 4.f);
			if (g_MainCharacter->m_IsMoving == false)
				g_MainCharacter->m_AnimPose = (int)m_state::step;
			g_MainCharacter->m_IsMoving = true;

		}

	}
	else
	{
		//죽었을 때,


	}

}


void HitCheck(std::vector<Bullet*> bv, std::vector<Monster*> mv, ID2D1SolidColorBrush* bulletBrush)
{
	
	for (std::vector<Bullet*>::iterator iterB = bv.begin(); iterB != bv.end(); iterB++)
	{
		if ((*iterB)->m_IsFlying == true)
		{
			for (std::vector<Monster*>::iterator iterM = mv.begin(); iterM != mv.end(); iterM++)
			{
				if ((*iterM)->GetAlive() == true)
				{
					D2D1_POINT_2F rt = (*iterM)->GetPosition();
					D2D1_POINT_2F brt = (*iterB)->m_CurrentXY;
					if (rt.x - 40 < brt.x && rt.x + 100 > brt.x && rt.y - 80 < brt.y && rt.y + 100 > brt.y)
					{
						(*iterB)->m_IsFlying = false;
						(*iterB)->m_AnimTime = 0;
						(*iterM)->CheckHP(g_MainCharacter->GetDamage());
						(*iterM)->m_gothit = true;
						g_soundManager->play((int)track::ZombieHit, false);
						if ((*iterM)->GetAlive() == false)
						{
							(*iterM)->InitialzeSpeed();
							g_MainCharacter->SetEXP(25);
							g_point += 50;
							g_soundManager->play((int)track::ZombieDead, false);

							if (g_MainCharacter->GetLevel() == 3)
							{
								g_difficulty -= 15;
								bulletBrush->SetColor(D2D1_COLOR_F(D2D1::ColorF(D2D1::ColorF::Red)));
							}
							if (g_MainCharacter->GetLevel() == 6)
							{
								g_difficulty -= 20;
								bulletBrush->SetColor(D2D1_COLOR_F(D2D1::ColorF(D2D1::ColorF::Violet)));
							}
							if (g_MainCharacter->GetLevel() == 10)
							{
								g_difficulty -= 25;
								bulletBrush->SetColor(D2D1_COLOR_F(D2D1::ColorF(D2D1::ColorF::Purple)));
							}
						}
					}
					if ((*iterB)->m_CurrentXY.x < 0 || (*iterB)->m_CurrentXY.x > 1920)
					{
						(*iterB)->m_AnimTime = 0.0f;
						(*iterB)->m_IsFlying = false;
					}
				}
			}
		}
	}

}


HRESULT ForthHomework::OnRender()
{
	HRESULT hr;


	hr = CreateDeviceResources();
	if (SUCCEEDED(hr))
	{
		g_rtSize = m_pRT->GetSize();
		float WidthScale = g_rtSize.width / DEFAULTWIDTH;
		float HeightScale = g_rtSize.height / DEFAULTHEIGHT;

		Move();


		D2D1_SIZE_F lampostSize = m_pLampostBitmap->GetSize();
		D2D1_SIZE_F buildingSize = m_pBuildingBitmap->GetSize();
		D2D1_SIZE_F wallSize = m_pWallBitmap->GetSize();
		D2D1_SIZE_F FireSize = m_pFireBitmap->GetSize();
		D2D1_SIZE_F characterSize = m_pCharacterBitmap->GetSize();
		D2D1_SIZE_F monster1Size = m_pMonster1Bitmap->GetSize();
		D2D1_SIZE_F monster2Size = m_pMonster1Bitmap->GetSize();
		D2D1_SIZE_F monster3Size = m_pMonster1Bitmap->GetSize();

		D2D1::Matrix3x2F scale = D2D1::Matrix3x2F::Scale(WidthScale, HeightScale);
		D2D1::Matrix3x2F scale2 = D2D1::Matrix3x2F::Scale(2.f, 5.f);
		D2D1_MATRIX_3X2_F flip = D2D1::Matrix3x2F(-1.f, 0.f, 0.f, 1.f, 1.f, 1.f);		//이미지 반전을 위해 반전행렬을 만든다.

		// 그리기를 준비함.
		m_pRT->BeginDraw();
		// 렌더타겟을 클리어함.
		m_pRT->SetTransform(D2D1::Matrix3x2F::Identity());

		m_pRT->SetTransform(scale);

		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 20; j++)
				m_pRT->DrawBitmap(m_pStreetBitmap, D2D1::RectF(100.f * j, 1000.f - 150.f * i, 105.f + 100 * j, 1200.f - 100 * i));


		D2D1_ELLIPSE light = D2D1::Ellipse(D2D1::Point2F(0, 0), 200.f, 200.f);
		for (int i = 0; i < 4; i++)
		{
			m_pRT->SetTransform(D2D1::Matrix3x2F::Translation(100 + 600.f * i, lampostSize.height * 7.f) * scale);
			m_pRT->FillEllipse(&light, m_pGradientYellowBrush);
		}

		m_pRT->SetTransform(scale);
		// 이동 동선 기하 경로가 화면 중심에 그려지도록 함.
		m_pRT->DrawBitmap(m_pSkyBitmap, D2D1::RectF(0, 0, 2000.f, 700.f));


		m_pRT->SetTransform(D2D1::Matrix3x2F::Translation(0, FireSize.height / 2.f) * scale2 * scale);
		D2D1_RECT_F rcBrushRect = D2D1::RectF(0, 0, FireSize.width, FireSize.height);
		for (int i = 1; i < 5; i++)
		{
			m_pRT->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
			m_pRT->FillOpacityMask(m_pFireBitMask, m_pFireBitmapBrush, D2D1_OPACITY_MASK_CONTENT_GRAPHICS, &rcBrushRect);
			m_pRT->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
			rcBrushRect = D2D1::RectF(FireSize.width * i * 3.f, 0, FireSize.width * i * 4.f + FireSize.width, FireSize.height);
		}


		m_pRT->SetTransform((D2D1::Matrix3x2F::Translation(0, buildingSize.height / 1.3f) * scale2 * scale));
		rcBrushRect = D2D1::RectF(0, 0, buildingSize.width, buildingSize.height);
		for (int i = 1; i < 11; i++)
		{
			m_pRT->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
			m_pRT->FillOpacityMask(m_pBuildingBitMask, m_pBuildingBitmapBrush, D2D1_OPACITY_MASK_CONTENT_GRAPHICS, &rcBrushRect);
			m_pRT->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
			rcBrushRect = D2D1::RectF(buildingSize.width * i, 0, buildingSize.width * i + buildingSize.width, buildingSize.height);
		}


		m_pRT->SetTransform(scale);
		for (int i = 0; i < 15; i++)
			m_pRT->DrawBitmap(m_pWallBitmap, D2D1::RectF(wallSize.width * 1.5f * i, wallSize.height * 8.f, wallSize.width * 1.5f * i + wallSize.width * 1.5f, wallSize.height * 11.f));

		m_pRT->FillGeometry(m_pMoon, m_pYellowBrush, NULL);


		m_pRT->SetTransform(D2D1::Matrix3x2F::Translation(0, lampostSize.height / 1.5f) * scale2 * scale);
		rcBrushRect = D2D1::RectF(0, 0, lampostSize.width, lampostSize.height);
		for (int i = 1; i < 5; i++)
		{
			m_pRT->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
			m_pRT->FillOpacityMask(m_pLampostBitMask, m_pLampostBitmapBrush, D2D1_OPACITY_MASK_CONTENT_GRAPHICS, &rcBrushRect);
			m_pRT->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
			rcBrushRect = D2D1::RectF(lampostSize.width * i * 3.f, 0, lampostSize.width * i * 3.f + lampostSize.width, lampostSize.height);
		}


		LARGE_INTEGER CurrentTime;
		QueryPerformanceCounter(&CurrentTime);
		float elapsedTime = (float)((double)(CurrentTime.QuadPart - m_nPrevTime.QuadPart) / (double)(m_nFrequency.QuadPart));
		m_nPrevTime = CurrentTime;


		// 캐릭터 관련 애니메이션,그림자 렌더링 구간
		D2D1_MATRIX_3X2_F restore = D2D1::Matrix3x2F::Translation(characterSize.width, 0);	//반전행렬을 곱하면 x값이 반전되므로, 다시 이를 복원시켜줄 복원행렬을 만들어줌	
		D2D1_MATRIX_3X2_F adjustLocation = D2D1::Matrix3x2F::Translation((g_MainCharacter->GetLocation().left + g_MainCharacter->GetLocation().right) / 2, (g_MainCharacter->GetLocation().top + g_MainCharacter->GetLocation().bottom) / 2);

		D2D1_ELLIPSE shadow = D2D1::Ellipse(D2D1::Point2F(0, 10), 50.f, 15.f);
		m_pRT->SetTransform(D2D1::Matrix3x2F::Translation(65.f + (-25.f * (g_MainCharacter->m_LookLeft == false ? 1 : 0)), 100.f) * adjustLocation * scale);
		m_pRT->FillEllipse(&shadow, m_pBlackBrush);

		m_pRT->SetTransform(adjustLocation * scale);
		if (g_MainCharacter->m_IsShooting == true && g_MainCharacter->m_IsMoving == false)
			g_MainCharacter->m_AnimPose = (int)m_state::shoot;
		else if (g_MainCharacter->m_IsShooting == true && g_MainCharacter->m_IsMoving == true)
			g_MainCharacter->m_AnimPose = (int)m_state::runningShoot;

		g_MainCharacter->m_preAnimPose = g_MainCharacter->m_AnimPose;
		m_pRT->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);

		if (g_MainCharacter->m_LookLeft)
		{
			switch (g_MainCharacter->m_AnimPose)
			{
			case (int)m_state::idle:
			{
				m_pRT->FillOpacityMask(m_pCharacterBitMask, m_pCharacterBitmapBrush, D2D1_OPACITY_MASK_CONTENT_GRAPHICS);
				break;
			}
			case (int)m_state::step:
			{
				m_pRT->FillOpacityMask(m_pCharacter2BitMask, m_pCharacter2BitmapBrush, D2D1_OPACITY_MASK_CONTENT_GRAPHICS);
				break;
			}
			case (int)m_state::run:
			{
				m_pRT->FillOpacityMask(m_pCharacter3BitMask, m_pCharacter3BitmapBrush, D2D1_OPACITY_MASK_CONTENT_GRAPHICS);
				break;
			}
			case (int)m_state::shoot:
			{
				m_pRT->SetTransform(D2D1::Matrix3x2F::Translation(-25.f, -5.f) * D2D1::Matrix3x2F::Scale(1.35f, 1.35f) * adjustLocation * scale);
				m_pRT->FillOpacityMask(m_pCharacter4BitMask, m_pCharacter4BitmapBrush, D2D1_OPACITY_MASK_CONTENT_GRAPHICS);
				break;
			}
			case (int)m_state::runningShoot:
			{
				m_pRT->SetTransform(D2D1::Matrix3x2F::Translation(-40.f, -5.f) * D2D1::Matrix3x2F::Scale(1.5f, 1.5f) * adjustLocation * scale);
				m_pRT->FillOpacityMask(m_pCharacter5BitMask, m_pCharacter5BitmapBrush, D2D1_OPACITY_MASK_CONTENT_GRAPHICS);
				break;
			}
			case (int)m_state::runningShoot2:
			{
				m_pRT->SetTransform(D2D1::Matrix3x2F::Translation(-40.f, -5.f) * D2D1::Matrix3x2F::Scale(1.5f, 1.5f) * adjustLocation * scale);
				m_pRT->FillOpacityMask(m_pCharacter6BitMask, m_pCharacter6BitmapBrush, D2D1_OPACITY_MASK_CONTENT_GRAPHICS);
				break;
			}
			case (int)m_state::runningShoot3:
			{
				m_pRT->SetTransform(D2D1::Matrix3x2F::Translation(-20.f, -5.f) * D2D1::Matrix3x2F::Scale(1.2f, 1.2f) * adjustLocation * scale);
				m_pRT->FillOpacityMask(m_pCharacter7BitMask, m_pCharacter7BitmapBrush, D2D1_OPACITY_MASK_CONTENT_GRAPHICS);
				break;
			}
			}
		}
		else if (!g_MainCharacter->m_LookLeft)
		{
			m_pRT->SetTransform(flip * restore * adjustLocation * scale);
			switch (g_MainCharacter->m_AnimPose)
			{
			case (int)m_state::idle:
			{
				m_pRT->FillOpacityMask(m_pCharacterBitMask, m_pCharacterBitmapBrush, D2D1_OPACITY_MASK_CONTENT_GRAPHICS);
				break;
			}
			case (int)m_state::step:
			{
				m_pRT->FillOpacityMask(m_pCharacter2BitMask, m_pCharacter2BitmapBrush, D2D1_OPACITY_MASK_CONTENT_GRAPHICS);
				break;
			}
			case (int)m_state::run:
			{
				m_pRT->FillOpacityMask(m_pCharacter3BitMask, m_pCharacter3BitmapBrush, D2D1_OPACITY_MASK_CONTENT_GRAPHICS);
				break;
			}
			case (int)m_state::shoot:
			{
				m_pRT->SetTransform(D2D1::Matrix3x2F::Translation(-25.f, -5.f) * D2D1::Matrix3x2F::Scale(1.35f, 1.35f) * flip * restore * adjustLocation * scale);
				m_pRT->FillOpacityMask(m_pCharacter4BitMask, m_pCharacter4BitmapBrush, D2D1_OPACITY_MASK_CONTENT_GRAPHICS);
				break;
			}
			case (int)m_state::runningShoot:
			{
				m_pRT->SetTransform(D2D1::Matrix3x2F::Translation(-40.f, -5.f) * D2D1::Matrix3x2F::Scale(1.5f, 1.5f) * flip * restore * adjustLocation * scale);
				m_pRT->FillOpacityMask(m_pCharacter5BitMask, m_pCharacter5BitmapBrush, D2D1_OPACITY_MASK_CONTENT_GRAPHICS);
				break;
			}
			case (int)m_state::runningShoot2:
			{
				m_pRT->SetTransform(D2D1::Matrix3x2F::Translation(-40.f, -5.f) * D2D1::Matrix3x2F::Scale(1.5f, 1.5f) * flip * restore * adjustLocation * scale);
				m_pRT->FillOpacityMask(m_pCharacter6BitMask, m_pCharacter6BitmapBrush, D2D1_OPACITY_MASK_CONTENT_GRAPHICS);
				break;
			}
			case (int)m_state::runningShoot3:
			{
				m_pRT->SetTransform(D2D1::Matrix3x2F::Translation(-20.f, -5.f) * D2D1::Matrix3x2F::Scale(1.2f, 1.2f) * flip * restore * adjustLocation * scale);
				m_pRT->FillOpacityMask(m_pCharacter7BitMask, m_pCharacter7BitmapBrush, D2D1_OPACITY_MASK_CONTENT_GRAPHICS);
				break;
			}
			}
		}
		m_pRT->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);

		g_MainCharacter->m_AnimTime[g_MainCharacter->m_AnimPose] += elapsedTime * 15.f;
		if (g_MainCharacter->m_AnimTime[g_MainCharacter->m_AnimPose] > 2.f && g_MainCharacter->m_AnimPose != (int)m_state::idle)
		{
			g_MainCharacter->m_AnimTime[g_MainCharacter->m_AnimPose] = 0.f;
			if (g_MainCharacter->m_preAnimPose == (int)m_state::idle || g_MainCharacter->m_preAnimPose == (int)m_state::step || g_MainCharacter->m_preAnimPose == (int)m_state::run)
				g_MainCharacter->m_AnimPose = (g_MainCharacter->m_preAnimPose + 1) % 3;
			else if (g_MainCharacter->m_preAnimPose == (int)m_state::shoot)
				g_MainCharacter->m_AnimPose = (int)m_state::idle;
			else
				g_MainCharacter->m_AnimPose = (g_MainCharacter->m_preAnimPose + 1) % 7;

			if (g_MainCharacter->m_AnimPose == (int)m_state::idle)
				g_MainCharacter->m_AnimPose = (int)m_state::step;

			g_MainCharacter->m_IsShooting = false;
		}
		//


		// 몬스터 애니메이션, 렌더링 구간

		WCHAR stateBuf[40];
		memset(stateBuf, '\0', sizeof(stateBuf));
		restore = D2D1::Matrix3x2F::Translation(monster1Size.width, 0);	//반전행렬을 곱하면 x값이 반전되므로, 다시 이를 복원시켜줄 복원행렬을 만들어줌
		m_pRT->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);

		for (int i = 0; i < g_MonsterVector.size(); i++)
		{
			if (g_MonsterVector[i]->GetAlive() == true)
			{
				m_pRT->SetTransform(D2D1::Matrix3x2F::Identity());
				wsprintf(stateBuf,L"%s",g_MonsterVector[i]->GetState());
				D2D1_RECT_F rt = { g_MonsterVector[i]->GetPosition().x - 50,g_MonsterVector[i]->GetPosition().y - 200,g_MonsterVector[i]->GetPosition().x + 50,g_MonsterVector[i]->GetPosition().y - 100 };
				m_pRT->DrawText(stateBuf, ARRAYSIZE(stateBuf) - 1, m_pTextFormat,rt, m_pYellowBrush);
				D2D1_ELLIPSE range = D2D1::Ellipse(D2D1::Point2F(0, 0), g_MonsterVector[i]->GetRange(), g_MonsterVector[i]->GetRange());
				
				
				adjustLocation = D2D1::Matrix3x2F::Translation(g_MonsterVector[i]->GetPosition().x, g_MonsterVector[i]->GetPosition().y);
				shadow = D2D1::Ellipse(D2D1::Point2F(0, 10), 50.f, 10.f);
				m_pRT->SetTransform(D2D1::Matrix3x2F::Translation(65.f + (-25.f * (g_MonsterVector[i]->m_LookLeft == false ? 1 : 0)), 115.f) * adjustLocation * scale);
				m_pRT->FillEllipse(&shadow, m_pBlackBrush);
				m_pRT->DrawEllipse(range, m_pYellowBrush, 3.f);	//사정거리

				if (g_MonsterVector[i]->m_LookLeft == false)
					m_pRT->SetTransform(flip * restore * adjustLocation * scale);
				else
					m_pRT->SetTransform(adjustLocation * scale);

				switch (g_MonsterVector[i]->m_monsterKind)
				{
				case (int)Monster::species::zombie:
				{
					m_pRT->FillOpacityMask(m_pMonster1BitMask, m_pMonster1BitmapBrush, D2D1_OPACITY_MASK_CONTENT_GRAPHICS);
					break;
				}
				case (int)Monster::species::mutent:
				{
					m_pRT->FillOpacityMask(m_pMonster2BitMask, m_pMonster2BitmapBrush, D2D1_OPACITY_MASK_CONTENT_GRAPHICS);
					break;
				}
				case (int)Monster::species::alien:
				{
					m_pRT->FillOpacityMask(m_pMonster3BitMask, m_pMonster3BitmapBrush, D2D1_OPACITY_MASK_CONTENT_GRAPHICS);
					break;
				}
				}
			}
		}
		m_pRT->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
		//

		QueryPerformanceFrequency(&m_nFrequency);
		HitCheck(g_BulletVector, g_MonsterVector, m_pBulletBrush);
		// 총알관련 렌더링 구간
		float length = 0.f;
		D2D1::Matrix3x2F FirstLoc;
		LARGE_INTEGER CurrentTime2;
		for (size_t i = 0; i < g_BulletVector.size(); i++)
		{
			QueryPerformanceCounter(&m_nPrevTime2);
			if (g_Shot == true && g_BulletVector[i]->m_IsFlying == false)
			{
				g_BulletVector[i]->m_IsFlying = true;
				g_Shot = false;
			}
			if (g_BulletVector[i]->m_IsFlying == true)
			{
				length = m_Animation.GetValue(g_BulletVector[i]->m_AnimTime);
				if (g_BulletVector[i]->m_AnimTime == 0.f)
				{
					g_BulletVector[i]->m_FirstY = (g_MainCharacter->GetLocation().bottom + g_MainCharacter->GetLocation().top) / 2 + 45.f;
					g_BulletVector[i]->m_CurrentXY.y = g_BulletVector[i]->m_FirstY;
					if (g_MainCharacter->m_LookLeft)
					{
						g_BulletVector[i]->m_Flip = D2D1::Matrix3x2F(-1.f, 0.f, 0.f, 1.f, 1.f, 1.f);
						g_BulletVector[i]->m_FirstX = g_MainCharacter->GetLocation().left + 15.f;
						g_BulletVector[i]->m_CurrentXY.x = g_BulletVector[i]->m_FirstX;
						g_BulletVector[i]->m_IsLeft = true;
					}
					else
					{
						g_BulletVector[i]->m_FirstX = g_MainCharacter->GetLocation().right + 80.f;
						g_BulletVector[i]->m_CurrentXY.x = g_BulletVector[i]->m_FirstX;
						g_BulletVector[i]->m_Flip = D2D1::Matrix3x2F::Identity();
						g_BulletVector[i]->m_IsLeft = false;
					}
				}
				g_BulletVector[i]->m_Direction = D2D1::Matrix3x2F::Translation(g_BulletVector[i]->m_IsLeft ? -length : length, 0.f);
				g_BulletVector[i]->m_CurrentXY.x = g_BulletVector[i]->m_FirstX + (g_BulletVector[i]->m_IsLeft ? -length : length);

				FirstLoc = D2D1::Matrix3x2F::Translation(g_BulletVector[i]->m_FirstX, g_BulletVector[i]->m_FirstY);
				m_pRT->SetTransform(g_BulletVector[i]->m_Flip * FirstLoc * g_BulletVector[i]->m_Direction * scale);
				m_pRT->FillGeometry(m_pBulletPathgeometry, m_pBulletBrush);


				QueryPerformanceCounter(&CurrentTime2);
				float elapsedTime2 = (float)((double)(CurrentTime2.QuadPart - m_nPrevTime2.QuadPart) / (double)(m_nFrequency.QuadPart));
				m_nPrevTime2 = CurrentTime2;
				g_BulletVector[i]->m_AnimTime += elapsedTime2 * 5000;


				//충돌판정 여기에 추가
			}
		}


		m_pRT->SetTransform(scale);
		//인터페이스 구간
		D2D1_RECT_F rt = { DEFAULTWIDTH/2,0,DEFAULTWIDTH,DEFAULTHEIGHT / 8 };
		WCHAR EXP[40];
		memset(EXP, '\0', sizeof(EXP));
		wsprintf(EXP, L"HP:%d LV:%d EXP:%d\n점수:%d", g_MainCharacter->m_HP, g_MainCharacter->GetLevel(), g_MainCharacter->GetEXP(), g_point);
		m_pRT->DrawText(EXP, ARRAYSIZE(EXP) - 1, m_pTextFormat, rt, m_pYellowBrush);


		m_pRT->SetTransform(D2D1::Matrix3x2F::Identity());
		if (g_MainCharacter->GetAlive() == false)
		{
			wsprintf(EXP, L"GAME OVER\n점수:%d", g_point);
			rt = { 0,0,DEFAULTWIDTH,DEFAULTHEIGHT };
			m_pRT->DrawText(EXP, ARRAYSIZE(EXP) - 1, m_pTextFormat, rt, m_pYellowBrush);
		}
		
		if (g_start == false)
		{
			const WCHAR gameStart[] = L"게임 시작";
			const WCHAR gameEnd[] = L"종료";

			rt = { g_rtSize.width / 2.3f,g_rtSize.height / 10.f,g_rtSize.width / 1.8f,g_rtSize.height / 2.f };
			m_pRT->Clear(D2D1::ColorF(D2D1::ColorF::White));
			m_pRT->DrawBitmap(m_pTitleBitmap, rt);
			rt = { g_rtSize.width / 3.f,g_rtSize.height / 1.8f,g_rtSize.width / 1.5f,g_rtSize.height / 1.4f };
			m_pRT->FillRectangle(&rt, m_pGrayBrush);
			m_pRT->DrawText(gameStart, ARRAYSIZE(gameStart) - 1, m_pTextFormat, rt, m_pBlackBrush);
			rt = { g_rtSize.width / 3.f,g_rtSize.height / 1.3f,g_rtSize.width / 1.5f,g_rtSize.height / 1.1f };
			m_pRT->FillRectangle(&rt, m_pGrayBrush);
			m_pRT->DrawText(gameEnd, ARRAYSIZE(gameEnd) - 1, m_pTextFormat, rt, m_pBlackBrush);
		}
		
		hr = m_pRT->EndDraw();

		if (hr == D2DERR_RECREATE_TARGET)
		{
			hr = S_OK;
			DiscardDeviceResources();

		}
		// 
	}
	return hr;
}

void Spawn(std::vector<Monster*>* mv, int i)
{
	if ((*mv)[i]->GetAlive() == false)
	{
		(*mv)[i]->m_monsterKind = rand() % 10;
		if ((*mv)[i]->m_monsterKind > 3)
		{
			(*mv)[i]->m_monsterKind = (int)Monster::species::zombie;
			(*mv)[i]->m_HP = 10;
			(*mv)[i]->m_Damage = 10;
		}
		else if ((*mv)[i]->m_monsterKind >= 1)
		{
			(*mv)[i]->m_monsterKind = (int)Monster::species::mutent;
			(*mv)[i]->m_HP = 15;
			(*mv)[i]->m_Damage = 15;
		}
		else
		{
			(*mv)[i]->m_monsterKind = (int)Monster::species::alien;
			(*mv)[i]->m_HP = 25;
			(*mv)[i]->m_Damage = 20;
		}
		(*mv)[i]->InitializedPos();
		(*mv)[i]->SetAlive(true);
	}
}

bool UpdateFSM(float timeDelta)
{
	for (std::vector<Monster*>::iterator iter = g_MonsterVector.begin(); iter != g_MonsterVector.end(); iter++)
	{
		Monster* mon = *iter;
		if (mon->GetAlive() == true)
		{
			mon->Update(g_MainCharacter, timeDelta, g_soundManager);
		}
	}

	return true;
}


void ForthHomework::OnResize(UINT width, UINT height)
{
	if (m_pRT)
	{
		D2D1_SIZE_U size;
		size.width = width;
		size.height = height;

		m_pRT->Resize(size);
	}
}

LRESULT CALLBACK ForthHomework::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	int x = LOWORD(lParam);
	int y = HIWORD(lParam);
	if (message == WM_CREATE)
	{
		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
		ForthHomework* pDemoApp = (ForthHomework*)pcs->lpCreateParams;
		SetWindowLongPtrW(hwnd, GWLP_USERDATA, PtrToUlong(pDemoApp));

		result = 1;
	}
	else
	{
		ForthHomework* pDemoApp = reinterpret_cast<ForthHomework*>(static_cast<LONG_PTR>(GetWindowLongPtrW(hwnd, GWLP_USERDATA)));
		bool wasHandled = false;
		if (pDemoApp)
		{

			if (g_musicInitialized && g_start && !g_soundManager->IsPlaying(g_mNumber))
			{
				g_mNumber = g_mNumber + 1 % 5;
				if (g_mNumber == 0)
					g_mNumber = (int)track::bgm1;
				g_soundManager->play(g_mNumber, FALSE);
			}

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
				if (g_start)
				{
					if (g_MainCharacter->GetAlive())
					{
						if (wParam == 0x41)
						{
							g_soundManager->stop((int)track::gunShot);
							g_MainCharacter->m_IsShooting = true;
							g_Shot = true;
							g_soundManager->play((int)track::gunShot, FALSE);
						}
						if (wParam == VK_UP || wParam == VK_DOWN || wParam == VK_LEFT || wParam == VK_RIGHT)
							g_MainCharacter->m_IsMoving = false;
					}
				}
				if (wParam == VK_DECIMAL)
				{
					if (g_volume == true)
					{
						g_volume = false;
						g_SoundVolume = 0x0000;
					}
					else
					{
						g_volume = true;
						g_SoundVolume = 0x8000;
					}
				}
				else if (wParam == VK_ADD)
				{
					g_SoundVolume += 0x1000;
					if (g_SoundVolume >= 0x10000)
						g_SoundVolume = 0xFFFF;
				}
				else if (wParam == VK_SUBTRACT)
				{
					g_SoundVolume -= 0x1000;
					if (g_SoundVolume <= 0x0000)
						g_SoundVolume = 0x0000;
				}
				waveOutSetVolume(0, g_SoundVolume);
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
			case WM_LBUTTONUP:
			{
				if (x<(g_rtSize.width / 1.5f) && x>(g_rtSize.width / 3.f) && y<(g_rtSize.height / 1.4f) && y >(g_rtSize.height / 1.8f))
				{
					g_soundManager->play((int)track::start, FALSE); //시작
					g_start = true;
				}
				
				if (x<(g_rtSize.width / 1.5f) && x>(g_rtSize.width / 3.f) && y < (g_rtSize.height / 1.1f) && y >(g_rtSize.height / 1.3f))
					exit(0);
			}
			result = 1;
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
HRESULT ForthHomework::LoadBitmapFromFile(ID2D1RenderTarget* pRenderTarget, IWICImagingFactory* pIWICFactory, PCWSTR uri, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap** ppBitmap)
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




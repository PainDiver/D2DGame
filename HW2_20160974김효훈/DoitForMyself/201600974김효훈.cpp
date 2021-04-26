#include <time.h>
#include <memory>
#include "BoxManager.h"
#include "SecondHomeWork.h"


#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")

#define NUMOFSTUDENTS 64
#define PI 3.141592
#define DEFAULTSCALEX 1280 
#define DEFAULTSCALEY 800

#define HALFRECTX 160
#define HALFRECTY 40
#define STACKSTEP 80

std::unique_ptr<BoxManager>manager;
std::unique_ptr<StudentBox[]> students;
bool ispop = false;
bool drag = false;

long long bit = 0;

D2D1_RECT_F ori;
D2D1_RECT_F info;
D2D1_RECT_F floors;



float scalex = 1;
float scaley = 1;
//201600974 무역학과 김효훈


// 응용 프로그램의 진입점 함수.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int /*nCmdShow*/)
{

	const TCHAR* first[] = { L"김",L"이", L"박", L"최", L"정", L"강", L"조", L"윤", L"장", L"임", L"한", L"오",
						L"서", L"신", L"권", L"황", L"안", L"송", L"류", L"전", L"홍", L"고", L"문", L"양", L"손", L"배",
L"조", L"백", L"허", L"유", L"남", L"심", L"노", L"정", L"하", L"곽", L"성", L"차", L"주", L"우",
L"구", L"신", L"임", L"나", L"전", L"민", L"유", L"진", L"지", L"엄", L"채", L"원", L"천", L"방",
L"공", L"강", L"현", L"함", L"변", L"염", L"양", L"변", L"여", L"추", L"노", L"도", L"소", L"신",
L"석", L"선", L"설", L"마", L"길", L"주", L"연", L"방", L"위", L"표", L"명", L"기", L"반", L"왕",
L"금", L"옥", L"육", L"인", L"맹", L"제", L"모", L"장", L"남", L"탁", L"국", L"여", L"진", L"어",
L"은", L"편", L"구", L"용" };

	const TCHAR* second[] = { L"가", L"강", L"건", L"경", L"고", L"관", L"광", L"구", L"규", L"근", L"기", L"길", L"나", L"남",
		L"노", L"누", L"다", L"단", L"달", L"담", L"대", L"덕", L"도", L"동", L"두", L"라", L"래", L"로", L"루", L"리", L"마",
		L"만", L"명", L"무", L"문", L"미", L"민", L"바", L"박", L"백", L"범", L"별", L"병", L"보", L"빛", L"사", L"산", L"상",
		L"새", L"서", L"석", L"선", L"설", L"섭", L"성", L"세", L"소", L"솔", L"수", L"숙", L"순", L"숭", L"슬", L"승", L"시",
		L"신", L"아", L"안", L"애", L"엄", L"여", L"연", L"영", L"예", L"오", L"옥", L"완", L"요", L"용", L"우", L"원", L"월",
		L"위", L"유", L"윤", L"율", L"으", L"은", L"의", L"이", L"익", L"인", L"일", L"잎", L"자", L"잔", L"장", L"재", L"전",
		L"정", L"제", L"조", L"종", L"주", L"준", L"중", L"지", L"진", L"찬", L"창", L"채", L"천", L"철", L"초", L"춘", L"충",
		L"치", L"탐", L"태", L"택", L"판", L"하", L"한", L"해", L"혁", L"현", L"형", L"혜", L"호", L"홍", L"화", L"환", L"회",
		L"효", L"훈", L"휘", L"희", L"운", L"모", L"배", L"부", L"림", L"봉", L"혼", L"황", L"량", L"린", L"을", L"비", L"솜",
		L"공", L"면", L"탁", L"온", L"디", L"항", L"후", L"려", L"균", L"묵", L"송", L"욱", L"휴", L"언", L"령", L"섬", L"들",
		L"견", L"추", L"걸", L"삼", L"열", L"웅", L"분", L"변", L"양", L"출", L"타", L"흥", L"겸", L"곤", L"번", L"식", L"란",
		L"더", L"손", L"술", L"훔", L"반", L"빈", L"실", L"직", L"흠", L"흔", L"악", L"람", L"뜸", L"권", L"복", L"심", L"헌",
		L"엽", L"학", L"개", L"롱", L"평", L"늘", L"늬", L"랑", L"얀", L"향", L"울", L"련" };

	const TCHAR* third[] = { L"가", L"강", L"건", L"경", L"고", L"관", L"광", L"구", L"규", L"근", L"기", L"길", L"나", L"남",
		L"노", L"누", L"다", L"단", L"달", L"담", L"대", L"덕", L"도", L"동", L"두", L"라", L"래", L"로", L"루", L"리", L"마",
		L"만", L"명", L"무", L"문", L"미", L"민", L"바", L"박", L"백", L"범", L"별", L"병", L"보", L"빛", L"사", L"산", L"상",
		L"새", L"서", L"석", L"선", L"설", L"섭", L"성", L"세", L"소", L"솔", L"수", L"숙", L"순", L"숭", L"슬", L"승", L"시",
		L"신", L"아", L"안", L"애", L"엄", L"여", L"연", L"영", L"예", L"오", L"옥", L"완", L"요", L"용", L"우", L"원", L"월",
		L"위", L"유", L"윤", L"율", L"으", L"은", L"의", L"이", L"익", L"인", L"일", L"잎", L"자", L"잔", L"장", L"재", L"전",
		L"정", L"제", L"조", L"종", L"주", L"준", L"중", L"지", L"진", L"찬", L"창", L"채", L"천", L"철", L"초", L"춘", L"충",
		L"치", L"탐", L"태", L"택", L"판", L"하", L"한", L"해", L"혁", L"현", L"형", L"혜", L"호", L"홍", L"화", L"환", L"회",
		L"효", L"훈", L"휘", L"희", L"운", L"모", L"배", L"부", L"림", L"봉", L"혼", L"황", L"량", L"린", L"을", L"비", L"솜",
		L"공", L"면", L"탁", L"온", L"디", L"항", L"후", L"려", L"균", L"묵", L"송", L"욱", L"휴", L"언", L"령", L"섬", L"들",
		L"견", L"추", L"걸", L"삼", L"열", L"웅", L"분", L"변", L"양", L"출", L"타", L"흥", L"겸", L"곤", L"번", L"식", L"란",
		L"더", L"손", L"술", L"훔", L"반", L"빈", L"실", L"직", L"흠", L"흔", L"악", L"람", L"뜸", L"권", L"복", L"심", L"헌",
		L"엽", L"학", L"개", L"롱", L"평", L"늘", L"늬", L"랑", L"얀", L"향", L"울", L"련" };


	TCHAR* name[NUMOFSTUDENTS];
	for (int i = 0; i < NUMOFSTUDENTS; i++)
		name[i] = new TCHAR();

	int size1 = sizeof(first) / sizeof(first[0]);
	int size2 = sizeof(second) / sizeof(second[0]);
	int size3 = sizeof(third) / sizeof(third[0]);

	for (int i = 0; i < sizeof(name) / sizeof(name[0]); i++)
	{
		srand(time(NULL) + i);
		wsprintf(name[i], L"%s%s%s", first[rand() % (size1)], second[rand() % (size2)], third[rand() % (size3)]);
	}

	manager = std::make_unique<BoxManager>();
	students = std::make_unique<StudentBox[]>(NUMOFSTUDENTS);

	for (int i = 0; i < NUMOFSTUDENTS; i++)
	{
		students[i].SetBit(1<<i);
		students[i].SetNameGrade(name[i], 50 + rand() % 50);
	}


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

// 생성자. 멤버 변수들을 초기화함.
SecondHomeWork::SecondHomeWork() :
	m_hwnd(NULL),
	m_pDirect2dFactory(NULL),
	m_pRenderTarget(NULL),
	m_pDWriteFactory(NULL),
	m_pLightSlateGrayBrush(NULL),
	m_pCornflowerBlueBrush(NULL),
	m_pRandomBrush(NULL),
	m_pTextFormat(NULL),
	m_pStrokeStyleDash(NULL),
	m_pBlackBrush(NULL)
{
}

// 소멸자. 응용 프로그램의 자원을 반납함.
SecondHomeWork::~SecondHomeWork()
{
	DiscardDeviceResources();
	SAFE_RELEASE(m_pDirect2dFactory);
}

// 응용 프로그램의 원도우를 생성함. 장치 독립적 자원을 생성함.
HRESULT SecondHomeWork::Initialize(HINSTANCE hInstance)
{
	HRESULT hr;

	// 장치 독립적 자원을 생성함.
	hr = CreateDeviceIndependentResources();

	if (SUCCEEDED(hr))
	{
		// 윈도우 클래스를 등록함..
		WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = SecondHomeWork::WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = sizeof(LONG_PTR);
		wcex.hInstance = hInstance;
		wcex.hbrBackground = NULL;
		wcex.lpszMenuName = NULL;
		wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
		wcex.lpszClassName = L"201600974무역학과김효훈HW_2";
		RegisterClassEx(&wcex);

		// 윈도우를 생성함.
		m_hwnd = CreateWindow(
			L"201600974무역학과김효훈HW_2", L"201600974무역학과김효훈HW_2",
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

// 장치 독립적 자원들을 생성함. 이들 자원의 수명은 응용 프로그램이 종료되기 전까지 유효함.
HRESULT SecondHomeWork::CreateDeviceIndependentResources()
{
	HRESULT hr = S_OK;

	static const WCHAR msc_fontName[] = L"Verdana";
	static const FLOAT msc_fontSize = 12;

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);

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
			L"", //locale
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


// 장치 의존적 자원들을 생성함. 장치가 소실되는 경우에는 이들 자원을 다시 생성해야 함.
HRESULT SecondHomeWork::CreateDeviceResources()
{
	HRESULT hr = S_OK;

	if (!m_pRenderTarget)
	{
		RECT rc;
		GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

		// D2D 렌더타겟을 생성함.
		hr = m_pDirect2dFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(m_hwnd, size), &m_pRenderTarget);

		if (SUCCEEDED(hr))
		{
			// 회색 붓을 생성함.
			hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightSlateGray), &m_pLightSlateGrayBrush);
		}
		if (SUCCEEDED(hr))
		{
			// 파란색 붓을 생성함.
			hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::CornflowerBlue), &m_pCornflowerBlueBrush);
		}
		if (SUCCEEDED(hr))
		{
			hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &m_pRandomBrush);
		}
		if (SUCCEEDED(hr))
		{
			hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBlackBrush);
		}
	}

	return hr;
}

// 장치 의존적 자원들을 반납함. 장치가 소실되면 이들 자원을 다시 생성해야 함.
void SecondHomeWork::DiscardDeviceResources()
{
	SAFE_RELEASE(m_pRenderTarget);
	SAFE_RELEASE(m_pLightSlateGrayBrush);
	SAFE_RELEASE(m_pCornflowerBlueBrush);
	SAFE_RELEASE(m_pRandomBrush);
	SAFE_RELEASE(m_pBlackBrush);
}

// 메인 윈도우 메시지 루프를 실행함.
void SecondHomeWork::RunMessageLoop()
{
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}


// 클라이언트 윈도우 화면을 그림.
// 참고: 이 함수는 실행되는 동안에 장치가 소실되면 장치 의존적 자원들을 반납함. 그 다음 호출 시에 그 자원들을 다시 생성함.
HRESULT SecondHomeWork::OnRender(const float& x,const float& y,const float& scalex,const float& scaley)
{

	HRESULT hr = S_OK;

	hr = CreateDeviceResources();

	if (SUCCEEDED(hr))
	{
		m_pRenderTarget->BeginDraw();
		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

		D2D1_RECT_F rectangle;
		TCHAR arry[64];
		if (drag == true)
		{
			rectangle = D2D1::Rect(x - HALFRECTX * scalex, y - HALFRECTY * scaley, x + HALFRECTX * scalex, y + HALFRECTY * scaley);

			float desx = (manager->GetLeft() + manager->GetRight()) / 2;
			float desy = (manager->GetTop() + manager->GetBottom()) / 2;
			float dis = 0;

			float orix = (ori.left + ori.right) / 2;
			float oriy = (ori.bottom + ori.top) / 2;
			float disoriginal = 0;
			
			float angle = 0;

			float odesx = pow(desx - orix, 2);
			float odesy = pow(desy - oriy, 2);
			disoriginal = sqrt(odesx + odesy);

			desx = pow(desx - x, 2);
			desy = pow(desy - y, 2);
			dis = sqrt(desx + desy);

			angle = cos((dis / disoriginal) * (PI / 2));

			dis = 30/ (dis);

			if (dis > 0.5f)
				dis = 0.5f;
			if (dis < 0.1f)
				dis = 0;


			D2D1_MATRIX_3X2_F scale = D2D1::Matrix3x2F::Scale(D2D1::Size(1.f * scalex, 1.f * scaley), D2D1::Point2F(info.right + info.left / 2, info.bottom + info.top / 2));
			m_pRenderTarget->SetTransform(scale);
			
			_stprintf_s(arry, 64, L"마우스:%.1f,%.1f\n스케일:%.1f\n회전:%.1f\n", x, y, dis + 0.5f, angle * 360);
			m_pRenderTarget->DrawText(arry, wcslen(arry) - 1, m_pTextFormat, info, m_pBlackBrush);
			
			scale = D2D1::Matrix3x2F::Scale(D2D1::Size((0.5f + dis), 1.f), D2D1::Point2F(x, y));
			D2D1_MATRIX_3X2_F rotation = D2D1::Matrix3x2F::Rotation(-angle * 360, D2D1::Point2F(x, y));

			TCHAR arr[14];
			m_pRenderTarget->SetTransform(scale * rotation);
			StudentBox* tmpJustPut = &manager->_boxManager[manager->_boxManager.size() - 1];
			if (tmpJustPut->_colorSet != true)
			{
				tmpJustPut->_colorSet = true;
				tmpJustPut->SetColor(D2D1::ColorF(rand() % 255 + 1 << 16 | rand() % 255 + 1 << 8 | rand() % 255 + 1));
			}
			wsprintf(arr, L"이름:%s\n%성적:%d", tmpJustPut->GetName(), tmpJustPut->GetGrade());
			m_pRandomBrush->SetColor(tmpJustPut->GetColor());
			m_pRenderTarget->FillRectangle(&rectangle, m_pRandomBrush);
			m_pRenderTarget->DrawText(arr, ARRAYSIZE(arr) - 1, m_pTextFormat, rectangle, m_pBlackBrush);

		}
		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		if (manager->_boxManager.size() == 8)
		{
			_stprintf_s(arry, 64, L"더 이상 쌓을 수 없음\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			m_pRenderTarget->DrawText(arry, ARRAYSIZE(arry) - 1, m_pTextFormat, info, m_pBlackBrush);
		}
		else 
		{
			_stprintf_s(arry, 64, L"쌓을 수 있음\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			m_pRenderTarget->DrawText(arry, ARRAYSIZE(arry) - 1, m_pTextFormat, info, m_pBlackBrush);
		}
		
		RenderBoxstacks(floors);

		hr = m_pRenderTarget->EndDraw();


		if (hr == D2DERR_RECREATE_TARGET)
		{
			hr = S_OK;
			DiscardDeviceResources();
		}

		return hr;
	}
}



void SecondHomeWork::RenderBoxstacks(D2D1_RECT_F floors)
{
	m_pRenderTarget->FillRectangle(&ori, m_pLightSlateGrayBrush);

	TCHAR arry[14];

	//쌓는영역
	for (int i = 0; i < manager->_boxManager.size() - drag; i++)
	{
		m_pRandomBrush->SetColor(manager->_boxManager[i].GetColor());
		m_pRenderTarget->FillRectangle(&floors, m_pRandomBrush);

		D2D1_MATRIX_3X2_F scale = D2D1::Matrix3x2F::Scale(D2D1::Size(1.f * scalex, 1.f * scaley), D2D1::Point2F((floors.right + floors.left) / 2, (floors.bottom + floors.top) / 2));
		m_pRenderTarget->SetTransform(scale);
		wsprintf(arry, L"이름:%s\n%성적:%d", manager->_boxManager[i].GetName(), manager->_boxManager[i].GetGrade());
		m_pRenderTarget->DrawText(arry, ARRAYSIZE(arry) - 1, m_pTextFormat, floors, m_pBlackBrush);
		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		floors.top -= STACKSTEP * scaley;
		floors.bottom -= STACKSTEP * scaley;
	}
	manager->SetEdge(floors.left, floors.right, floors.top, floors.bottom);
	D2D1_RECT_F topbox = D2D1::Rect(manager->GetLeft(), manager->GetTop(), manager->GetRight(), manager->GetBottom());
	if (manager->_boxManager.size() != 8)
		m_pRenderTarget->DrawRectangle(topbox, m_pBlackBrush);
}


// 응용 프로그램에서 WM_SIZE 메시지가 발생되면 이 함수가 렌더타겟의 크기를 다시 설정함.
void SecondHomeWork::OnResize(UINT width, UINT height)
{
	if (m_pRenderTarget)
	{
		// 참고: 아래의 함수는 실행 시에 실패할 수도 있지만, 여기에서 실행 에러를 체크하지 않고 넘어가도 됨. 다음번 EndDraw 함수가 호출될 때에 에러가 확인될 것이므로 그때 처리하면 됨.
		m_pRenderTarget->Resize(D2D1::SizeU(width, height));

		int x = (width) / 2;
		int y = (height) / 2;

		scalex = (float)(width) / DEFAULTSCALEX;
		scaley = (float)(height) / DEFAULTSCALEY;

		ori = D2D1::Rect((LONG)(x - (HALFRECTX/2) * scalex), (LONG)(y - 380 * scaley), (LONG)(x + (HALFRECTX/2) * scalex), (LONG)(y - 300 * scaley));
		info = D2D1::Rect((LONG)(x - 700 * scalex), (LONG)(y + 160 * scaley), (LONG)(x - 400 * scalex), (LONG)(y + 480 * scaley));
		floors = D2D1::Rect((LONG)(x - HALFRECTX * scalex), (LONG)(y + 280 * scaley), (LONG)(x +HALFRECTX * scalex), (LONG)(y + 360 * scaley));

	}
}

LRESULT CALLBACK SecondHomeWork::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	int mx = 0;
	int my = 0;
	mx = LOWORD(lParam);
	my = HIWORD(lParam);


	if (message == WM_CREATE)
	{
		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
		SecondHomeWork* pSecondHomeWork = (SecondHomeWork*)pcs->lpCreateParams;

		SetWindowLongPtrW(hwnd, GWLP_USERDATA, PtrToUlong(pSecondHomeWork));

		result = 1;
	}
	else
	{
		SecondHomeWork* homeWork2 = reinterpret_cast<SecondHomeWork*>(static_cast<LONG_PTR>(GetWindowLongPtrW(hwnd, GWLP_USERDATA)));

		bool wasHandled = false;

		if (homeWork2)
		{
			switch (message)
			{
			case WM_SIZE:
			{
				UINT width = LOWORD(lParam);
				UINT height = HIWORD(lParam);
				homeWork2->OnResize(width, height);
			}
			result = 0;
			wasHandled = true;
			break;

			case WM_LBUTTONDOWN:
			{
				if (manager->_boxManager.size() != 8)
				{
					if (drag == false) {
						if ((ori.top < my) && (ori.bottom > my) && (ori.left < mx) && (ori.right > mx))
						{
							drag = true;
							int random = rand() % NUMOFSTUDENTS;
							while (true)
							{
								if (((bit & (1 << random)) == (1 << random)))
								{
									random = rand() % NUMOFSTUDENTS;
								}
								else
								{
									manager->Insert(students[random]);
									bit += (1 << random);
									break;
								}
							}
						}
					}
				}
				if (!manager->_boxManager.empty() && (manager->GetTop() + STACKSTEP * scaley < my) && (manager->GetBottom() + STACKSTEP * scaley > my) && (manager->GetLeft() < mx) && (manager->GetRight() > mx))
				{
					drag = true;
					ispop = true;
				}
				InvalidateRect(hwnd, NULL, FALSE);
			}
			result = 0;
			wasHandled = true;
			break;

			case WM_MOUSEMOVE:
			{
				if (drag && !ispop && ((manager->GetTop() < my) && (manager->GetBottom() > my) && (manager->GetLeft() < mx) && (manager->GetRight() > mx)))
				{
					manager->sort();
					drag = false;
				}
				if (ispop && drag && ((ori.top < my) && (ori.bottom > my) && (ori.left < mx) && (ori.right > mx)))
				{
					bit -= 1 << (manager->_boxManager[manager->_boxManager.size() - 1].GetBit());
					manager->Pop();
					ispop = false;
					drag = false;
				}
				homeWork2->OnRender(mx, my, scalex, scaley);
			}
			result = 0;
			wasHandled = true;
			break;

			case WM_LBUTTONUP:
			{
				if (drag && !ispop)
				{
					bit -= 1 << (manager->_boxManager[manager->_boxManager.size() - 1].GetBit());
					manager->Pop();
				}
				if (drag && ispop)
				{
					ispop = false;
				}
				InvalidateRect(hwnd, NULL, FALSE);
				drag = false;
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
				homeWork2->OnRender(mx, my, scalex, scaley);
				ValidateRect(hwnd, NULL);
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

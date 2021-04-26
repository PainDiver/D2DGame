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
//201600974 �����а� ��ȿ��


// ���� ���α׷��� ������ �Լ�.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int /*nCmdShow*/)
{

	const TCHAR* first[] = { L"��",L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��",
						L"��", L"��", L"��", L"Ȳ", L"��", L"��", L"��", L"��", L"ȫ", L"��", L"��", L"��", L"��", L"��",
L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��",
L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"ä", L"��", L"õ", L"��",
L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��",
L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"ǥ", L"��", L"��", L"��", L"��",
L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"Ź", L"��", L"��", L"��", L"��",
L"��", L"��", L"��", L"��" };

	const TCHAR* second[] = { L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��",
		L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��",
		L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��",
		L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��",
		L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��",
		L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��",
		L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"â", L"ä", L"õ", L"ö", L"��", L"��", L"��",
		L"ġ", L"Ž", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"ȣ", L"ȫ", L"ȭ", L"ȯ", L"ȸ",
		L"ȿ", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"ȥ", L"Ȳ", L"��", L"��", L"��", L"��", L"��",
		L"��", L"��", L"Ź", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��",
		L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"Ÿ", L"��", L"��", L"��", L"��", L"��", L"��",
		L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��",
		L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��" };

	const TCHAR* third[] = { L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��",
		L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��",
		L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��",
		L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��",
		L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��",
		L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��",
		L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"â", L"ä", L"õ", L"ö", L"��", L"��", L"��",
		L"ġ", L"Ž", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"ȣ", L"ȫ", L"ȭ", L"ȯ", L"ȸ",
		L"ȿ", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"ȥ", L"Ȳ", L"��", L"��", L"��", L"��", L"��",
		L"��", L"��", L"Ź", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��",
		L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"Ÿ", L"��", L"��", L"��", L"��", L"��", L"��",
		L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��",
		L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��", L"��" };


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

// ������. ��� �������� �ʱ�ȭ��.
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
	HRESULT hr = S_OK;

	static const WCHAR msc_fontName[] = L"Verdana";
	static const FLOAT msc_fontSize = 12;

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);

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
HRESULT SecondHomeWork::CreateDeviceResources()
{
	HRESULT hr = S_OK;

	if (!m_pRenderTarget)
	{
		RECT rc;
		GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

		// D2D ����Ÿ���� ������.
		hr = m_pDirect2dFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(m_hwnd, size), &m_pRenderTarget);

		if (SUCCEEDED(hr))
		{
			// ȸ�� ���� ������.
			hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightSlateGray), &m_pLightSlateGrayBrush);
		}
		if (SUCCEEDED(hr))
		{
			// �Ķ��� ���� ������.
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

// ��ġ ������ �ڿ����� �ݳ���. ��ġ�� �ҽǵǸ� �̵� �ڿ��� �ٽ� �����ؾ� ��.
void SecondHomeWork::DiscardDeviceResources()
{
	SAFE_RELEASE(m_pRenderTarget);
	SAFE_RELEASE(m_pLightSlateGrayBrush);
	SAFE_RELEASE(m_pCornflowerBlueBrush);
	SAFE_RELEASE(m_pRandomBrush);
	SAFE_RELEASE(m_pBlackBrush);
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


// Ŭ���̾�Ʈ ������ ȭ���� �׸�.
// ����: �� �Լ��� ����Ǵ� ���ȿ� ��ġ�� �ҽǵǸ� ��ġ ������ �ڿ����� �ݳ���. �� ���� ȣ�� �ÿ� �� �ڿ����� �ٽ� ������.
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
			
			_stprintf_s(arry, 64, L"���콺:%.1f,%.1f\n������:%.1f\nȸ��:%.1f\n", x, y, dis + 0.5f, angle * 360);
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
			wsprintf(arr, L"�̸�:%s\n%����:%d", tmpJustPut->GetName(), tmpJustPut->GetGrade());
			m_pRandomBrush->SetColor(tmpJustPut->GetColor());
			m_pRenderTarget->FillRectangle(&rectangle, m_pRandomBrush);
			m_pRenderTarget->DrawText(arr, ARRAYSIZE(arr) - 1, m_pTextFormat, rectangle, m_pBlackBrush);

		}
		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		if (manager->_boxManager.size() == 8)
		{
			_stprintf_s(arry, 64, L"�� �̻� ���� �� ����\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			m_pRenderTarget->DrawText(arry, ARRAYSIZE(arry) - 1, m_pTextFormat, info, m_pBlackBrush);
		}
		else 
		{
			_stprintf_s(arry, 64, L"���� �� ����\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
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

	//�״¿���
	for (int i = 0; i < manager->_boxManager.size() - drag; i++)
	{
		m_pRandomBrush->SetColor(manager->_boxManager[i].GetColor());
		m_pRenderTarget->FillRectangle(&floors, m_pRandomBrush);

		D2D1_MATRIX_3X2_F scale = D2D1::Matrix3x2F::Scale(D2D1::Size(1.f * scalex, 1.f * scaley), D2D1::Point2F((floors.right + floors.left) / 2, (floors.bottom + floors.top) / 2));
		m_pRenderTarget->SetTransform(scale);
		wsprintf(arry, L"�̸�:%s\n%����:%d", manager->_boxManager[i].GetName(), manager->_boxManager[i].GetGrade());
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

#pragma once

// Windows Header Files:
#include <windows.h>
// C RunTime Header Files:
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <TCHAR.h>
#include <math.h>
// DX Header Files:
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

// 자원 안전 반환 매크로.
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }

class SecondHomeWork
{
public:
	SecondHomeWork();
	~SecondHomeWork();
	HRESULT Initialize(HINSTANCE hInstance);  // Register the window class and call methods for instantiating drawing resources
	void RunMessageLoop();  // Process and dispatch messages

private:
	HRESULT CreateDeviceIndependentResources();  // Initialize device-independent resources.
	HRESULT CreateDeviceResources();  // Initialize device-dependent resources.
	void DiscardDeviceResources();  // Release device-dependent resource.
	HRESULT CreateGridPatternBrush(ID2D1RenderTarget* pRenderTarget, ID2D1BitmapBrush** ppBitmapBrush);
	HRESULT OnRender();   // Draw content.

	void RenderBoxstacks(D2D1_RECT_F);

	void OnResize(UINT width, UINT height);  // Resize the render target.

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);  // The windows procedure.

private:
	HWND m_hwnd;
	ID2D1Factory* m_pDirect2dFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;

	ID2D1StrokeStyle* m_pStrokeStyleDash;

	ID2D1SolidColorBrush* m_pLightSlateGrayBrush;
	ID2D1SolidColorBrush* m_pCornflowerBlueBrush;
	ID2D1SolidColorBrush* m_pRandomBrush;
	ID2D1SolidColorBrush* m_pSceneBrush;
	ID2D1SolidColorBrush* m_pBlackBrush;

	ID2D1BitmapBrush* m_pGridPatternBitmapBrush;

	ID2D1PathGeometry* m_pSunGeometry;
	ID2D1PathGeometry* m_pLeftMountainGeometry;
	ID2D1PathGeometry* m_pRightMountainGeometry;
	ID2D1PathGeometry* m_pRiverGeometry;
	ID2D1RadialGradientBrush* m_pRadialGradientBrush;

	IDWriteTextFormat* m_pTextFormat;
	IDWriteFactory* m_pDWriteFactory;
};

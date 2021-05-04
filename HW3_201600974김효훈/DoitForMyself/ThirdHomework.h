#pragma once

// Windows Header Files:
#include <windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>
// DX Header Files
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

#include "Animation.h"

// 자원 안전 반환 매크로.
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }

// 현재 모듈의 시작주소 얻기.
#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

class ThirdHomework
{
public:
	ThirdHomework();
	~ThirdHomework();
	HRESULT Initialize();
	void RunMessageLoop();

private:
	HRESULT CreateDeviceIndependentResources();
	HRESULT CreateDeviceResources();
	void DiscardDeviceResources();
	HRESULT OnRender();
	void OnResize(UINT width, UINT height);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	HRESULT LoadBitmapFromFile(ID2D1RenderTarget* pRenderTarget, IWICImagingFactory* pIWICFactory, PCWSTR uri, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap** ppBitmap);


private:
	HWND m_hwnd;
	ID2D1Factory* m_pD2DFactory;
	IWICImagingFactory* m_pWICFactory;
	ID2D1HwndRenderTarget* m_pRT;
	
	ID2D1PathGeometry* m_pBulletPathgeometry;
	ID2D1PathGeometry* m_pMoon;

	ID2D1RadialGradientBrush* m_pGradientYellowBrush;
	ID2D1SolidColorBrush* m_pYellowBrush;
	ID2D1SolidColorBrush* m_pBlackBrush;

	ID2D1Bitmap* m_pSkyBitmap;
	ID2D1Bitmap* m_pWallBitmap;
	ID2D1Bitmap* m_pStreetBitmap;

	ID2D1Bitmap* m_pBuildingBitmap;
	ID2D1Bitmap* m_pBuildingBitMask;
	ID2D1BitmapBrush* m_pBuildingBitmapBrush;


	ID2D1Bitmap* m_pLampostBitmap;
	ID2D1Bitmap* m_pLampostBitMask;
	ID2D1BitmapBrush* m_pLampostBitmapBrush;


	ID2D1Bitmap* m_pFireBitmap;
	ID2D1Bitmap* m_pFireBitMask;
	ID2D1BitmapBrush* m_pFireBitmapBrush;

	ID2D1EllipseGeometry* m_pCircle1;
	ID2D1EllipseGeometry* m_pCircle2;

	AnimationLinear<float> m_Animation;

	LARGE_INTEGER m_nPrevTime;
	LARGE_INTEGER m_nFrequency;


	ID2D1Bitmap* m_pCharacterBitmap;
	ID2D1Bitmap* m_pCharacterBitMask;
	ID2D1BitmapBrush* m_pCharacterBitmapBrush;

	ID2D1Bitmap* m_pCharacter2Bitmap;
	ID2D1Bitmap* m_pCharacter2BitMask;
	ID2D1BitmapBrush* m_pCharacter2BitmapBrush;

	ID2D1Bitmap* m_pCharacter3Bitmap;
	ID2D1Bitmap* m_pCharacter3BitMask;
	ID2D1BitmapBrush* m_pCharacter3BitmapBrush;

	ID2D1Bitmap* m_pCharacter4Bitmap;
	ID2D1Bitmap* m_pCharacter4BitMask;
	ID2D1BitmapBrush* m_pCharacter4BitmapBrush;

	ID2D1Bitmap* m_pCharacter5Bitmap;
	ID2D1Bitmap* m_pCharacter5BitMask;
	ID2D1BitmapBrush* m_pCharacter5BitmapBrush;

	ID2D1Bitmap* m_pCharacter6Bitmap;
	ID2D1Bitmap* m_pCharacter6BitMask;
	ID2D1BitmapBrush* m_pCharacter6BitmapBrush;

	ID2D1Bitmap* m_pCharacter7Bitmap;
	ID2D1Bitmap* m_pCharacter7BitMask;
	ID2D1BitmapBrush* m_pCharacter7BitmapBrush;
};


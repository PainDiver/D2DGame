#pragma once
#include <Windows.h>
#include <TCHAR.h>
#include <d2d1.h>
#include <dwrite.h>

class StudentBox
{
	const TCHAR* _name;
	int _grade;
	D2D1::ColorF _color = 0;
	long long _bitpos;


public:
	bool _colorSet = false;

	StudentBox(const TCHAR* name = L"", int grade = 50);

	void SetNameGrade(const TCHAR* name, int grade);
	void SetColor(D2D1::ColorF color);
	void SetBit(const long long& n);

	const TCHAR* GetName()const;
	D2D1::ColorF GetColor()const;
	int GetGrade()const;
	int GetBit()const;

	~StudentBox();

	friend class BoxManager;
};


#include "StudentBox.h"



StudentBox::StudentBox(const TCHAR* name, int grade)
{
	this->_name = name;
	this->_grade = grade;
}

StudentBox::~StudentBox()
{
}

void StudentBox::SetNameGrade(const TCHAR* name, int grade)
{
	this->_name = name;
	this->_grade = grade;
}

void StudentBox::SetColor(D2D1::ColorF color)
{
	this->_color = color;
	this->_colorSet = true;
}

void StudentBox::SetBit(const long long& n)
{
	this->_bitpos = n;
}


const TCHAR* StudentBox::GetName()const
{
	return this->_name;
}

int StudentBox::GetGrade()const
{
	return this->_grade;
}



D2D1::ColorF StudentBox::GetColor()const
{
	return this->_color;
}

int StudentBox::GetBit()const
{
	return this->_bitpos;
}

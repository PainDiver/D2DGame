#include "BoxManager.h"

struct MyCompare
{
	bool operator()(const StudentBox& n1, const StudentBox& n2) const
	{
		return n1.GetGrade() > n2.GetGrade();
	}
};

BoxManager::BoxManager()
{
}

BoxManager::~BoxManager()
{
	this->_boxManager.erase(this->_boxManager.begin(), this->_boxManager.end());
}


void BoxManager::SetEdge(int l, int r, int t, int b)
{
	this->_left = l;
	this->_right = r;
	this->_top = t;
	this->_bottom = b;
}

int BoxManager::GetLeft()const
{
	return this->_left;
}

int BoxManager::GetRight()const
{
	return this->_right;
}

int BoxManager::GetBottom()const
{
	return this->_bottom;
}

int BoxManager::GetTop()const
{
	return this->_top;
}

void BoxManager::Insert(const StudentBox& st)
{
	this->_boxManager.push_back(st);
}

void BoxManager::sort()
{
	std::sort(this->_boxManager.begin(), this->_boxManager.end(), MyCompare());
}

void BoxManager::Pop()
{
	this->_boxManager.pop_back();
	
}
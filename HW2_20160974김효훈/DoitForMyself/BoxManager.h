#pragma once
#include <vector>
#include <algorithm>
#include "StudentBox.h"


class BoxManager
{
	int _left = 500;
	int _right = _left + 500;
	int _top = 600;
	int _bottom = _top + 80;

public:
	BoxManager();
	std::vector<StudentBox> _boxManager;
	void Insert(const StudentBox&);
	void sort();
	void Pop();
	
	void SetEdge(int l, int r, int t, int b);
	int GetLeft()const;
	int GetRight()const;
	int GetBottom()const;
	int GetTop()const;



	~BoxManager();
};


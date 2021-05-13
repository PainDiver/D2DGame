#include "Bullet.h"

Bullet::Bullet() 
{
	this-> m_AnimTime = 0.f;
	this->m_IsFlying = false;
	this->m_FirstX = 0.f;
	this->m_FirstY = 0.f;
	this->m_IsLeft = false;

	this->m_CurrentXY = { 0 };
	this->m_Flip = D2D1::Matrix3x2F::Identity();
	this->m_Direction = D2D1::Matrix3x2F::Identity();
}

Bullet::~Bullet() 
{
}

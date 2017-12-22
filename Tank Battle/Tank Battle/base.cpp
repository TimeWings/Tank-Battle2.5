#include "stdafx.h"
#include "base.h"

point::point(int x, int y)  //���캯��
{
	this->x = x; 
	this->y = y;
}

point point::makepoint(int x, int y)   //����һ����(x,y)������
{
	point p(x, y);
	return p;
}



rec::rec(int left, int right, int up, int down)  //���캯��
{
	this->left = left;
	this->right = right;
	this->up = up;
	this->down = down;
}

void rec::setrec(int left, int right, int up, int down)  //���þ���
{
	this->left = left;
	this->right = right;
	this->up = up;
	this->down = down;
}

rec rec::makerec(int left, int right, int up, int down)  //����һ�����β�����
{
	rec r(left, right, up, down);
	return r;
}


object::object(int x,int y):pos(x,y)
{
	
}

bool object::if_point_in_rec(const point &p, const rec &r)      //�жϵ�p�Ƿ��ھ���r��
{
	if (p.x<r.left || p.x>r.right || p.y<r.up || p.y>r.down)
		return false;
	else
		return true;
}

bool object::ifcrash(const rec &r1, const rec &r2)             //�жϾ���r1�;���r2�Ƿ��ص�
{
	if (if_point_in_rec(point(r1.left, r1.up), r2) || if_point_in_rec(point(r1.right, r1.up), r2)        //�жϾ���r1���ĸ����Ƿ���r2��
		|| if_point_in_rec(point(r1.left, r1.down), r2) || if_point_in_rec(point(r1.right, r1.down), r2))
		return true;
	else if (if_point_in_rec(point(r2.left, r2.up), r1) || if_point_in_rec(point(r2.right, r2.up), r1)   //�жϾ���r2���ĸ����Ƿ���r1��
		|| if_point_in_rec(point(r2.left, r2.down), r1) || if_point_in_rec(point(r2.right, r2.down), r1))
		return true;
	else
		return false;
}
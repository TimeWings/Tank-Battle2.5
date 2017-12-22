#include "stdafx.h"
#include "base.h"

point::point(int x, int y)  //构造函数
{
	this->x = x; 
	this->y = y;
}

point point::makepoint(int x, int y)   //生成一个点(x,y)并返回
{
	point p(x, y);
	return p;
}



rec::rec(int left, int right, int up, int down)  //构造函数
{
	this->left = left;
	this->right = right;
	this->up = up;
	this->down = down;
}

void rec::setrec(int left, int right, int up, int down)  //设置矩形
{
	this->left = left;
	this->right = right;
	this->up = up;
	this->down = down;
}

rec rec::makerec(int left, int right, int up, int down)  //生成一个矩形并返回
{
	rec r(left, right, up, down);
	return r;
}


object::object(int x,int y):pos(x,y)
{
	
}

bool object::if_point_in_rec(const point &p, const rec &r)      //判断点p是否在矩形r中
{
	if (p.x<r.left || p.x>r.right || p.y<r.up || p.y>r.down)
		return false;
	else
		return true;
}

bool object::ifcrash(const rec &r1, const rec &r2)             //判断矩形r1和矩形r2是否重叠
{
	if (if_point_in_rec(point(r1.left, r1.up), r2) || if_point_in_rec(point(r1.right, r1.up), r2)        //判断矩形r1的四个点是否在r2中
		|| if_point_in_rec(point(r1.left, r1.down), r2) || if_point_in_rec(point(r1.right, r1.down), r2))
		return true;
	else if (if_point_in_rec(point(r2.left, r2.up), r1) || if_point_in_rec(point(r2.right, r2.up), r1)   //判断矩形r2的四个点是否在r1中
		|| if_point_in_rec(point(r2.left, r2.down), r1) || if_point_in_rec(point(r2.right, r2.down), r1))
		return true;
	else
		return false;
}
#pragma once

class point             //点类
{
public:
	int x, y;

	point(int x = 0, int y = 0);  //构造函数，默认为(0,0)
    static point makepoint(int x, int y);   //生成一个点(x,y)并返回 
};

class rec                //矩形类
{
public:
	int left, right, up, down;

	rec(int left = 0, int right = 0, int up = 0, int down = 0);  //构造函数
	void setrec(int left, int right, int up, int down);          //重新设置该矩形
	static rec makerec(int left, int right, int up, int down);   //生成一个矩形并返回
};

class object               //物体类，同时是坦克类，子弹类，道具类，障碍物类的基类
{
public:
	point pos;             //位置
	rec shape;             //形状，所有物体均视作矩形

	static bool if_point_in_rec(const point &p, const rec &r);      //判断点p是否在矩形r中
	static bool ifcrash(const rec &r1, const rec &r2);             //判断矩形r1和矩形r2是否重叠

protected:
	object(int x = 0, int y = 0);              //构造函数
	int width;             //宽度
	int height;            //高度
};


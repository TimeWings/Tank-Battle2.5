#pragma once

#include "base.h"
#include "enum.h"
#include "interfaces.h"

class barrier:public object      //障碍物类，继承自物体类
{
	friend void interfaces::load_all_image(); //友元函数
public:
	barrier(int x, int y, barrier_type type);   //构造函数
	barrier();  //无参构造函数
	~barrier(); //析构函数
	void drawbarrier();         //绘制障碍物
	barrier_type gettype();      //返回障碍物类型

	static void destroy_all_barriers();   //摧毁所有障碍物
	static void initbarrier(int level);  //初始化所有障碍物
    static std::vector<barrier*> barriers;//数组存放全部障碍物

protected:
	barrier_type type;  //障碍物类型，包括钢铁，砖块，水面，草从
	
	//障碍物图片
	static IMAGE img;
	static IMAGE steelimg;
	static IMAGE brickimg;
	static IMAGE grassimg;
	static IMAGE waterimg;

	static IMAGE steeltimg;
	static IMAGE bricktimg;
	static IMAGE grasstimg;
	static IMAGE watertimg;
};

class camp :public barrier       //基地类，继承自障碍物类
{
	friend void interfaces::load_all_image(); //友元函数
public:
	bool destroyed;           //是否已被摧毁
	camp(int x, int y);       //构造函数
	~camp();                  //析构函数
	void drawcamp();          //绘制基地
	void initcamp(int x, int y);  //初始化基地
	static camp mycamp;       //玩家需要保护的基地

private:
	//基地图片
	static IMAGE camp0img;
	static IMAGE camp1img;
};

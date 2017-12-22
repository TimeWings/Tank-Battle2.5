#pragma once
#include "barrier.h"
#include "stdafx.h"
#include "player.h"

class builder:public player, public barrier   //建造者，用于自定义地图，继承自玩家类和障碍物类
{
private:
	point pos;   //位置
	rec shape;   //形状
	int width;   //宽度
	int height;  //高度
	/*以上4个成员数据覆盖两个父类的共同父类（object类）的对应成员
	因为builder继承的两个父类都共同继承了object类，具有以上四个共同成员，
	如果不覆盖，编译器将无法确认使用哪一个*/

	IMAGE image;//当前障碍物的图片

	builder();   //构造函数
	~builder();  //析构函数
	void change_image();//更改障碍物类型及图片

	void move(); //移动
	void newpos();//新位置
	void newshape();//新形状
	void toborder();//边界判断
    /*以上四个函数为重写函数，覆盖tank类的对应函数
	如果不重写，调用函数时调用的是tank类的函数，将只能改变tank类的成员数据，
	无法改变本类成员数据*/

	void control_builder(); //控制建造者进行移动和放置障碍物等操作
	static void putbarrier(int x, int y, barrier_type type);//放置障碍物
	static void draw_all_barriers();//绘制全部障碍物
    static void readtxt(int No);   //读取地图txt文件，No为所读取的序号
	static void savetxt(int number);  //保存新建的自定义地图到txt文件中，number为保存前的地图总数加一
	static bool build_custom_map();//开始建造自定义地图，返回值为是否保存该地图，若要保存则返回true，否则返回false

public:
	static void load_custom_sum();         //加载已经建好的自定义地图个数
	static bool check_custom_map();  //检测是否有自定义地图，没有返回false，有返回true并让玩家进行选择
};

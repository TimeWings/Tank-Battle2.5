#pragma once
#include "base.h"
#include "enum.h"

class tank:public object      //坦克类，继承自物体类
{
public:
	void be_hit(int damage);  //被子弹击中
	int getlife();            //返回生命值
	void reload_time_reduce();//子弹装填时间减少
	
protected:
	tank(int x, int y);                   //构造函数
	~tank();                  //虚构函数
	direction tank_direction; //坦克方向
	int attack;               //攻击力
	int speed;                //移动速度
	int life;                 //生命值
	int reload_time;          //子弹装填时间，为0时才可射击，单位：帧
	int reset_reload_time;    //用于重置子弹装填时间，可表示坦克的攻速

	void newpos();            //移动后新的位置
	void newshape();          //移动后更新形状
	void toborder();          //边界判断
	void shoot();             //射击
	void virtual move() = 0;  //移动，纯虚函数，在派生类中实现
};


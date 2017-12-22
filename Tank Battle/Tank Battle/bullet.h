#pragma once
#include "enum.h"
#include "base.h"
#include "interfaces.h"

class bullet:public object     //子弹类，继承自物体类
{
	friend class linklist;     //友元类
	friend void interfaces::load_all_image();//友元函数
public:
	bullet(int x = 0, int y = 0, int damage = 5, 
		direction tank_direction = up, from bfrom= fromplayer);//构造函数
	~bullet();                    //析构函数

	void drawbullet();            //绘制子弹
	void move(bool &exist);       //移动
	bullet* getnext();            //得到下一发子弹的地址

	static void destroy_all_bullet();//删除所有子弹

private:
	int damage;                   //子弹伤害
	int speed;                    //子弹速度
	from bfrom;                   //子弹来源
	direction bullet_direction;   //子弹方向
	bullet *front;                //指向前一发子弹
	bullet *next;                 //指向下一发子弹

	void newpos();                //移动后新的位置
	void newshape();              //移动后更新形状
	bool toborder();              //边界判断

	//子弹图片
	static IMAGE player_bulletimg;
	static IMAGE enemy_bulletimg;
	static IMAGE enemy_bulletimgt;
};


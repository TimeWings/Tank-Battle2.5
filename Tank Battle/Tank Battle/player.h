#pragma once
#include "enum.h"
#include "tank.h"
#include "barrier.h"
#include "interfaces.h"

class player :public tank   //玩家类，继承自坦克类
{
	friend void interfaces::load_all_image();  //友元函数
public:
	player(int x = 390, int y = 812, direction dir = up); //构造函数
	~player(); //析构函数
	void initplayer(int x = 390, int y = 812, direction dir = up);//初始化玩家
	void drawplayer();       //绘制玩家
	void die();              //死亡
	bool ifdead();           //获取死亡状态
	void lifeup(int up);     //生命值上升
	void levelup();          //等级提升
	int getmaxlife();        //返回玩家最大生命值
	int get_reload_time();   //返回子弹装填时间
	int get_reset_reload_time();//返回玩家攻速
	void control_player();   //操纵玩家

	static player p1;               //玩家一

private:
	int level;              //等级
	int maxlife;            //最大生命值
	bool dead;              //是否死亡
	void move();            //移动
	void shoot();           //射击

	//玩家坦克图片（四个方向）
	static IMAGE playerimgU;
	static IMAGE playerimgD;
	static IMAGE playerimgL;
	static IMAGE playerimgR;
};


#pragma once
#include "enum.h"
#include "base.h"
#include "interfaces.h"

class item:public object
{
	friend void interfaces::load_all_image();//友元函数
public:
	item(int x = 0, int y = 0, item_type type = bomb);//构造函数
	~item();                      //析构函数
	void setitem(int x, int y, item_type type); //放置道具
	void drawitem();             //绘制道具
	void builditem();            //随机生成道具
	void destroyitem();          //摧毁道具
	void getitem();              //拾取道具
	int staytime;                //道具持续时间

	static item item1;           //实例化

private:
	item_type type;              //道具类型
	bool exist;                  //道具是否存在

	void getbomb();              //全体爆炸
	void gettimestop();          //时间停止
	void getstar();              //提高等级
	void getprotect();           //基地保护
	void getlife();              //生命增加

	//道具图片
	static IMAGE bombimg;
	static IMAGE timerimg;
	static IMAGE starimg;
	static IMAGE protectimg;
	static IMAGE lifeimg;
};


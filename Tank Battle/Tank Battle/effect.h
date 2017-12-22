#pragma once

#include"base.h"
#include"enum.h"
#include "interfaces.h"

class effect            //特效类
{
	friend void interfaces::load_all_image();//友元函数
public:
	effect(int x, int y, effect_type type);//构造函数
	~effect();//析构函数
	void play();       //播放该特效
	static void new_effect(int x, int y, effect_type type);//构造新特效并放入数组
	static void destroy_all_effect();                      //删除所有特效
    bool exist;        //该特效是否存在

	static std::vector<effect*> eff;  //数组存储所有特效

private:
	effect_type type;   //特效类型
	point pos;         //特效位置
	double imgnum;     //当前播放第几张图片

	void blast();      //爆炸
	void born();       //生成坦克
	void hit();        //子弹击中

	static IMAGE blast1img;
	static IMAGE blast2img;
	static IMAGE blast3img;
	static IMAGE blast4img;
	static IMAGE blast5img;
	static IMAGE blast6img;
	static IMAGE blast7img;
	static IMAGE blast8img;
	static IMAGE born1img;
	static IMAGE born2img;
	static IMAGE born3img;
	static IMAGE born4img;
	static IMAGE hit1img;
	static IMAGE hit2img;
	static IMAGE hit3img;
	static IMAGE hit4img;
	static IMAGE hit5img;
};


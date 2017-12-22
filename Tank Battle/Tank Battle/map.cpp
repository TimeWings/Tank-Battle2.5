#include "stdafx.h"
#include "map.h"
#include "barrier.h"
#include "player.h"
#include "enemy.h"
#include "effect.h"
#include "item.h"
#include "bullet.h"
#include "builder.h"

int map::level = 1;
game_difficulty map::difficulty = easy;

void map::init_custom_map(bool save)  
//初始化自定义地图，此函数在初次进入时和重新开始时调用，初次进入时传入true，重新开始时传入false
{
	map::level = 0;//自定义地图为第零关
	map::difficulty = normal;//默认为一般难度

	static std::vector<int> x, y, type;  //用于存储障碍物位置和类型
	if (save == true)   //初次进入时，参数为true，存储当前地图
	{
		x.clear();  //清空原来的数据
		y.clear();
		type.clear();
		for (int i = 0; i < barrier::barriers.size(); i++)  //保存自定义地图的障碍物类型和位置，以便在重新开始后读取
		{
			x.push_back(barrier::barriers[i]->pos.x);
			y.push_back(barrier::barriers[i]->pos.y);
			type.push_back(barrier::barriers[i]->gettype());
		}
	}//如果没有这个if语句，在玩家重新开始时，已被摧毁的砖块将无法还原

	barrier::destroy_all_barriers();   //重新开始后，删除所有障碍物，然后重新构造全部障碍物（利用之前存储的类型和位置）
	for (int i = 0; i < x.size(); i++)
	{
		barrier *b = new barrier(x[i], y[i], (barrier_type)type[i]);
		barrier::barriers.push_back(b);
	}

	effect::destroy_all_effect();      //摧毁所有特效
	bullet::destroy_all_bullet();      //删除所有子弹
	camp::mycamp.initcamp(480, 821);  //初始化基地
	player::p1.initplayer(390, 821, up);   //初始化玩家坦克
	effect::new_effect(390, 821, born_effect);
	enemy::initenemy();          //初始化敌人
	item::item1.destroyitem();   //摧毁道具
}

void map::init_level()
{
	effect::destroy_all_effect();      //摧毁所有特效
	bullet::destroy_all_bullet();      //删除所有子弹
	barrier::initbarrier(level);             //初始化障碍物
	camp::mycamp.initcamp(480, 821);  //初始化基地
	player::p1.initplayer(390, 821, up);   //初始化玩家坦克
	effect::new_effect(390, 821, born_effect);
	enemy::initenemy();          //初始化敌人
	item::item1.destroyitem();   //摧毁道具
	if (difficulty == easy)
		camp_protect();          //简单难度有基地保护
	//item::item1.setitem(500, 700, timestop);
}

void map::camp_protect()
{
	barrier *w1 = new barrier(450, 851, steel);
	barrier::barriers.push_back(w1);
	barrier *w2 = new barrier(450, 821, steel);
	barrier::barriers.push_back(w2);
	barrier *w3 = new barrier(450, 791, steel);
	barrier::barriers.push_back(w3);
	barrier *w4 = new barrier(480, 791, steel);
	barrier::barriers.push_back(w4);
	barrier *w5 = new barrier(510, 791, steel);
	barrier::barriers.push_back(w5);
	barrier *w6 = new barrier(540, 791, steel);
	barrier::barriers.push_back(w6);
	barrier *w7 = new barrier(540, 821, steel);
	barrier::barriers.push_back(w7);
	barrier *w8 = new barrier(540, 851, steel);
	barrier::barriers.push_back(w8);
}

void map::camp_protect2()
{
	barrier *w1 = new barrier(450, 851, brick);
	barrier::barriers.push_back(w1);
	barrier *w2 = new barrier(450, 821, brick);
	barrier::barriers.push_back(w2);
	barrier *w3 = new barrier(450, 791, brick);
	barrier::barriers.push_back(w3);
	barrier *w4 = new barrier(480, 791, brick);
	barrier::barriers.push_back(w4);
	barrier *w5 = new barrier(510, 791, brick);
	barrier::barriers.push_back(w5);
	barrier *w6 = new barrier(540, 791, brick);
	barrier::barriers.push_back(w6);
	barrier *w7 = new barrier(540, 821, brick);
	barrier::barriers.push_back(w7);
	barrier *w8 = new barrier(540, 851, brick);
	barrier::barriers.push_back(w8);
}


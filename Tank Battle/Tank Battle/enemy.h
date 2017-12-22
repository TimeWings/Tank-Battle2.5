#pragma once

#include "enum.h"
#include "tank.h"
#include "interfaces.h"

class enemy:public tank            //敌人类，继承自坦克类
{
	friend void interfaces::load_all_image();  //友元函数
public:
	enemy(int x = 0, int y = 0, enemyColor color = green, int id = 0);//构造函数
	~enemy();                      //析构函数
	void drawenemy();              //绘制敌人
	void random_act();             //随机行为（简单，一般模式）
	void attack_act();             //攻击行为（困难模式）
	void destroy();                //摧毁该敌人（生命值为零时调用）
	void life_to_zero();           //生命值归零（由炸弹道具调用）

	static void initenemy();       //初始化所有敌人
	static void enemyNewborn();    //随机生成新的敌人
	static void delete_all_enemy();//摧毁所有敌人

	static std::vector<enemy*> enemies;   //数组存放所有敌人
	static bool timestop;                 //时间停止道具是否生效
	static int stoptime;                  //时停道具持续时间，单位：帧
	static int killed;                    //已死亡的敌人数

private:
	int id;                          //编号，用于区分不同的敌人
	enemyColor color;                //颜色

	void move();                     //移动
	void shoot();                    //射击

	static int count_enemyNum;            //已经生成的敌人数量

	//敌人图片
	static IMAGE enemyimg1U;	// white
	static IMAGE enemyimg1D;
	static IMAGE enemyimg1L;
	static IMAGE enemyimg1R;

	static IMAGE enemyimg2U;	// green
	static IMAGE enemyimg2D;
	static IMAGE enemyimg2L;
	static IMAGE enemyimg2R;

	static IMAGE enemyimg3U;	// yellow
	static IMAGE enemyimg3D;
	static IMAGE enemyimg3L;
	static IMAGE enemyimg3R;

	static IMAGE enemyimg1Ut;	// white
	static IMAGE enemyimg1Dt;
	static IMAGE enemyimg1Lt;
	static IMAGE enemyimg1Rt;

	static IMAGE enemyimg2Ut;	// green
	static IMAGE enemyimg2Dt;
	static IMAGE enemyimg2Lt;
	static IMAGE enemyimg2Rt;

	static IMAGE enemyimg3Ut;	// yellow
	static IMAGE enemyimg3Dt;
	static IMAGE enemyimg3Lt;
	static IMAGE enemyimg3Rt;
};

const point born_pos[5] = { point::makepoint(481,41), point::makepoint(1,41), point::makepoint(961,41), point::makepoint(1,402), point::makepoint(961,402) };//敌人出生位置        

const int init_enemy_number = 3; //初始敌人数量

const int max_enemy_number_level[11] = { 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};  //每关最大敌军数量

const int total_enemy_number_level[11] = { 15, 15, 20, 20, 25, 25, 30, 30, 35, 35, 40};  //每关敌军总数

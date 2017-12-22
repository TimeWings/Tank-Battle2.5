#pragma once
#include"enum.h"

class map
{
public:
	static int level;           //当前关卡
	static game_difficulty difficulty;  //难度
	static void init_custom_map(bool save);    
	//初始化自定义地图,传入true表示存储临时地图到内存中，以便在重新开始游戏时读取
	static void init_level();   //初始化关卡
	static void camp_protect(); //基地保护（钢铁）
	static void camp_protect2();//基地保护（砖块）
};


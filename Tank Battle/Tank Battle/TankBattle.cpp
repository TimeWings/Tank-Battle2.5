// TankBattle.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "enum.h"
#include "player.h"
#include "bullet.h"
#include "linklist.h"
#include "barrier.h"
#include "enemy.h"
#include "item.h"
#include "effect.h"
#include "map.h"
#include "interfaces.h"
#include "sound.h"
#include "builder.h"

#pragma comment (lib,"winmm.lib")
#pragma comment( lib, "MSIMG32.LIB")

linklist bulletlist;

int main()
{
	initgraph(window_width, window_height);       // 绘图环境初始化
	interfaces::load_all_image();   //加载所有图片
	sound::open_all_music();
	sound::open_all_sound();

	srand((unsigned)time(NULL));
	int timer = 0;               //计时器
	int wait_time = 500;         //通关或gameover后先等待一段时间
	interfaces::into_mainmenu = true;  //进入主菜单
	
	BeginBatchDraw(); //开始批量绘图

	while (true)      //游戏主循环
	{
		if (interfaces::into_mainmenu == true)   //是否进入主菜单（游戏启动时默认为true）
		{
			interfaces::into_mainmenu = false;   //进入一次后变为false，之后可以从其他界面（如暂停界面）再次变为true
			sound::stop_music(bgm);
			sound::playmusic(title);
			interfaces::mainmenu();
			if (interfaces::into_mainmenu == true)
				continue;
		}

		if (player::p1.ifdead() == false && camp::mycamp.destroyed == false)   //操作玩家（未死亡且基地未被摧毁）
			player::p1.control_player();

		srand((unsigned)time(NULL));
		if ((timer % 500) == 499)         //每隔500帧随机生成新敌人
			enemy::enemyNewborn();

		if ((timer % 2500) == 2499)
			item::item1.builditem();        //每隔2500帧随机生成道具

		if (object::ifcrash(player::p1.shape, item::item1.shape) == true)  //判断是否吃到道具
			item::item1.getitem();
		
		for (int i = 0; i < enemy::enemies.size(); i++)     //遍历敌人判断是否有死亡
			if (enemy::enemies[i]->getlife() <= 0)
			{
				enemy::enemies[i]->destroy();
				enemy::enemies.erase(enemy::enemies.begin() + i);
			}

		if (player::p1.getlife() <= 0 && player::p1.ifdead() == false)  //判断玩家是否死亡
			player::p1.die();

		interfaces::draw_all();                //绘制下一帧所有存在的对象      
		
		FlushBatchDraw(); //执行绘图
		
		//Sleep(1);
		cleardevice();   //清屏

		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)   //按ESC暂停
		{
			sound::playsound(pause_sound);
			interfaces::pause();
		}

		if (GetAsyncKeyState(VK_SUBTRACT) & 0x8000)  //减号键直接gameover（调试用）
			interfaces::gameover();

		if (GetAsyncKeyState(VK_ADD) & 0x8000)       //加号键直接过关（调试用）
			if (map::level == 10 || map::level == 0)
				interfaces::victory();
			else
				interfaces::stage_clear();

		if (player::p1.ifdead() == true ||camp::mycamp.destroyed == true)    //若玩家死亡或基地被毁，则游戏结束
		{
			if (camp::mycamp.destroyed == true && wait_time == 500)
				sound::playsound(camp_destroyed_sound);                    //播放一次基地被摧毁的声音
			if (player::p1.ifdead() == true == true && wait_time == 500)
				sound::playsound(player_blast_sound);                      //播放一次玩家爆炸的声音
			wait_time--;
			if (wait_time <= 0)
			{
				interfaces::gameover();    
				wait_time = 500;
			}
		}

		if (enemy::killed == total_enemy_number_level[map::level])          //若击杀所有敌人
		{
			wait_time--;
			if (wait_time <= 0)
			{
				if (map::level == 10 || map::level == 0)         //若当前是最后一关，则游戏胜利
					interfaces::victory();
				else
				    interfaces::stage_clear();       //若不是最后一关，则关卡通过，可进入下一关
				wait_time = 500;
			}
		}
		timer++;   //计时器加一
		interfaces::time_reduce();     //有关倒计时的变量减一
	}
	EndBatchDraw();  //结束批量绘图
	//_getch();                  // 按任意键退出
	closegraph();
	return 0;
}

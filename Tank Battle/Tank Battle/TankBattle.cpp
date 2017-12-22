// TankBattle.cpp: �������̨Ӧ�ó������ڵ㡣
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
	initgraph(window_width, window_height);       // ��ͼ������ʼ��
	interfaces::load_all_image();   //��������ͼƬ
	sound::open_all_music();
	sound::open_all_sound();

	srand((unsigned)time(NULL));
	int timer = 0;               //��ʱ��
	int wait_time = 500;         //ͨ�ػ�gameover���ȵȴ�һ��ʱ��
	interfaces::into_mainmenu = true;  //�������˵�
	
	BeginBatchDraw(); //��ʼ������ͼ

	while (true)      //��Ϸ��ѭ��
	{
		if (interfaces::into_mainmenu == true)   //�Ƿ�������˵�����Ϸ����ʱĬ��Ϊtrue��
		{
			interfaces::into_mainmenu = false;   //����һ�κ��Ϊfalse��֮����Դ��������棨����ͣ���棩�ٴα�Ϊtrue
			sound::stop_music(bgm);
			sound::playmusic(title);
			interfaces::mainmenu();
			if (interfaces::into_mainmenu == true)
				continue;
		}

		if (player::p1.ifdead() == false && camp::mycamp.destroyed == false)   //������ң�δ�����һ���δ���ݻ٣�
			player::p1.control_player();

		srand((unsigned)time(NULL));
		if ((timer % 500) == 499)         //ÿ��500֡��������µ���
			enemy::enemyNewborn();

		if ((timer % 2500) == 2499)
			item::item1.builditem();        //ÿ��2500֡������ɵ���

		if (object::ifcrash(player::p1.shape, item::item1.shape) == true)  //�ж��Ƿ�Ե�����
			item::item1.getitem();
		
		for (int i = 0; i < enemy::enemies.size(); i++)     //���������ж��Ƿ�������
			if (enemy::enemies[i]->getlife() <= 0)
			{
				enemy::enemies[i]->destroy();
				enemy::enemies.erase(enemy::enemies.begin() + i);
			}

		if (player::p1.getlife() <= 0 && player::p1.ifdead() == false)  //�ж�����Ƿ�����
			player::p1.die();

		interfaces::draw_all();                //������һ֡���д��ڵĶ���      
		
		FlushBatchDraw(); //ִ�л�ͼ
		
		//Sleep(1);
		cleardevice();   //����

		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)   //��ESC��ͣ
		{
			sound::playsound(pause_sound);
			interfaces::pause();
		}

		if (GetAsyncKeyState(VK_SUBTRACT) & 0x8000)  //���ż�ֱ��gameover�������ã�
			interfaces::gameover();

		if (GetAsyncKeyState(VK_ADD) & 0x8000)       //�Ӻż�ֱ�ӹ��أ������ã�
			if (map::level == 10 || map::level == 0)
				interfaces::victory();
			else
				interfaces::stage_clear();

		if (player::p1.ifdead() == true ||camp::mycamp.destroyed == true)    //�������������ر��٣�����Ϸ����
		{
			if (camp::mycamp.destroyed == true && wait_time == 500)
				sound::playsound(camp_destroyed_sound);                    //����һ�λ��ر��ݻٵ�����
			if (player::p1.ifdead() == true == true && wait_time == 500)
				sound::playsound(player_blast_sound);                      //����һ����ұ�ը������
			wait_time--;
			if (wait_time <= 0)
			{
				interfaces::gameover();    
				wait_time = 500;
			}
		}

		if (enemy::killed == total_enemy_number_level[map::level])          //����ɱ���е���
		{
			wait_time--;
			if (wait_time <= 0)
			{
				if (map::level == 10 || map::level == 0)         //����ǰ�����һ�أ�����Ϸʤ��
					interfaces::victory();
				else
				    interfaces::stage_clear();       //���������һ�أ���ؿ�ͨ�����ɽ�����һ��
				wait_time = 500;
			}
		}
		timer++;   //��ʱ����һ
		interfaces::time_reduce();     //�йص���ʱ�ı�����һ
	}
	EndBatchDraw();  //����������ͼ
	//_getch();                  // ��������˳�
	closegraph();
	return 0;
}

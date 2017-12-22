#include "stdafx.h"
#include "interfaces.h"
#include "barrier.h"
#include "map.h"
#include "enemy.h"
#include "bullet.h"
#include "linklist.h"
#include "player.h"
#include "effect.h"
#include "item.h"
#include "sound.h"
#include "builder.h"

int interfaces::public_readcd = 0;
bool interfaces::into_mainmenu = false;
extern linklist bulletlist;
IMAGE interfaces::selecttankimg;
IMAGE interfaces::titleimg;
IMAGE interfaces::bgimg;
IMAGE interfaces::bg2img;
IMAGE interfaces::clockbgimg;
IMAGE interfaces::buttonimg;

IMAGE interfaces::startimg;
IMAGE interfaces::exitimg;
IMAGE interfaces::settingimg;
IMAGE interfaces::restartimg;
IMAGE interfaces::nextimg;
IMAGE interfaces::continueimg;
IMAGE interfaces::menuimg;
IMAGE interfaces::customimg;
IMAGE interfaces::newimg;
IMAGE interfaces::loadimg;

IMAGE interfaces::clearimg;
IMAGE interfaces::gameoverimg;
IMAGE interfaces::pauseimg;
IMAGE interfaces::victoryimg;
IMAGE interfaces::stageimg;

IMAGE interfaces::musicimg;
IMAGE interfaces::soundimg;
IMAGE interfaces::openimg;
IMAGE interfaces::closeimg;
IMAGE interfaces::backimg;

IMAGE interfaces::easyimg;
IMAGE interfaces::normalimg;
IMAGE interfaces::hardimg;

IMAGE interfaces::number0img;
IMAGE interfaces::number1img;
IMAGE interfaces::number2img;
IMAGE interfaces::number3img;
IMAGE interfaces::number4img;
IMAGE interfaces::number5img;
IMAGE interfaces::number6img;
IMAGE interfaces::number7img;
IMAGE interfaces::number8img;
IMAGE interfaces::number9img;
IMAGE interfaces::slashimg;
IMAGE interfaces::timestopimg;

void Putimage(int x, int y, IMAGE& img)
{
	// 获取绘图窗口和 IMAGE 对象的句柄，TransparentBlt 函数需要用
	HDC dstDC = GetImageHDC();
	HDC srcDC = GetImageHDC(&img);

	// 使用 Windows GDI 函数实现透明位图
	TransparentBlt(dstDC, x, y, img.getwidth(), img.getheight(), srcDC, 0, 0, img.getwidth(), img.getheight(), BLACK);     // 最后一个参数是表示透明色为黒色
}

void interfaces::drawnumber(int x, int y, int number)
{
	switch (number)
	{
	case 1:Putimage(x, y, number1img); break;
	case 2:Putimage(x, y, number2img); break;
	case 3:Putimage(x, y, number3img); break;
	case 4:Putimage(x, y, number4img); break;
	case 5:Putimage(x, y, number5img); break;
	case 6:Putimage(x, y, number6img); break;
	case 7:Putimage(x, y, number7img); break;
	case 8:Putimage(x, y, number8img); break;
	case 9:Putimage(x, y, number9img); break;
	case 0:Putimage(x, y, number0img); break;
	case 10:Putimage(x, y, slashimg); break;
	default:
		break;
	}
}

void interfaces::show_version()
{
	settextcolor(WHITE);
	RECT r = { 950,860,1020,880 };
	drawtext(_T("Ver2.5"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void interfaces::show_panel()
{
	line(0, panel_height, window_width, panel_height);      //上边界
	
	rectangle(9, 9, 11 + player::p1.getmaxlife() * 4, 31);
	setfillcolor(RGB(255, 0, 0));
	solidrectangle(10, 10, 10 + player::p1.getlife() * 4, 30);     //血条

	rectangle(139, 9, 141 + player::p1.get_reset_reload_time(), 31);
	setfillcolor(RGB(100, 250, 100));
	solidrectangle(140, 10, 140 + player::p1.get_reset_reload_time() - player::p1.get_reload_time(), 30); //装填时间条

	drawnumber(930, 0, 10);   //斜线
	if ((enemy::killed / 10) != 0)
		drawnumber(870, 0, (enemy::killed / 10));   //击杀数
	drawnumber(900, 0, (enemy::killed % 10));

	int level = map::level;
	if (total_enemy_number_level[level] / 10 != 0)
		drawnumber(960, 0, total_enemy_number_level[level] / 10);    //总敌人数
	drawnumber(990, 0, total_enemy_number_level[level] % 10);

	//Putimage(400, 0, stageimg);
	if ((map::level / 10) != 0)
		drawnumber(480, 0, (map::level / 10));
	drawnumber(510, 0, (map::level % 10));
}

void interfaces::load_all_image()    //加载所有图片
{
	loadimage(&(barrier::steelimg), _T("./img/steel.gif"));
	loadimage(&(barrier::brickimg), _T("./img/wall.gif"));
	loadimage(&(barrier::grassimg), _T("./img/grass.gif"));
	loadimage(&(barrier::waterimg), _T("./img/water.gif"));

	loadimage(&(barrier::steeltimg), _T("./img/steelt.gif"));
	loadimage(&(barrier::bricktimg), _T("./img/wallt.gif"));
	loadimage(&(barrier::grasstimg), _T("./img/grasst.gif"));
	loadimage(&(barrier::watertimg), _T("./img/watert.gif"));

	loadimage(&(camp::camp0img), _T("./img/camp0.gif"), 60, 60, true);
	loadimage(&(camp::camp1img), _T("./img/camp1.gif"), 60, 60, true);

	loadimage(&(bullet::player_bulletimg), _T("./img/tankmissile.gif"));
	loadimage(&(bullet::enemy_bulletimg), _T("./img/enemymissile.gif"));
	loadimage(&(bullet::enemy_bulletimgt), _T("./img/enemymissilet.gif"));

	loadimage(&(player::playerimgU), _T("./img/p1tankU.gif"), 55, 55, true);
	loadimage(&(player::playerimgD), _T("./img/p1tankD.gif"), 55, 55, true);
	loadimage(&(player::playerimgL), _T("./img/p1tankL.gif"), 55, 55, true);
	loadimage(&(player::playerimgR), _T("./img/p1tankR.gif"), 55, 55, true);

	loadimage(&(enemy::enemyimg1U), _T("./img/enemy1U.gif"), 55, 55, true);	// white
	loadimage(&(enemy::enemyimg1D), _T("./img/enemy1D.gif"), 55, 55, true);
	loadimage(&(enemy::enemyimg1L), _T("./img/enemy1L.gif"), 55, 55, true);
	loadimage(&(enemy::enemyimg1R), _T("./img/enemy1R.gif"), 55, 55, true);

	loadimage(&(enemy::enemyimg2U), _T("./img/enemy2U.gif"), 55, 55, true);	// green
	loadimage(&(enemy::enemyimg2D), _T("./img/enemy2D.gif"), 55, 55, true);
	loadimage(&(enemy::enemyimg2L), _T("./img/enemy2L.gif"), 55, 55, true);
	loadimage(&(enemy::enemyimg2R), _T("./img/enemy2R.gif"), 55, 55, true);

	loadimage(&(enemy::enemyimg3U), _T("./img/enemy3U.gif"), 55, 55, true);	// yellow
	loadimage(&(enemy::enemyimg3D), _T("./img/enemy3D.gif"), 55, 55, true);
	loadimage(&(enemy::enemyimg3L), _T("./img/enemy3L.gif"), 55, 55, true);
	loadimage(&(enemy::enemyimg3R), _T("./img/enemy3R.gif"), 55, 55, true);

	loadimage(&(enemy::enemyimg1Ut), _T("./img/enemy1Ut.gif"), 55, 55, true);	// white
	loadimage(&(enemy::enemyimg1Dt), _T("./img/enemy1Dt.gif"), 55, 55, true);
	loadimage(&(enemy::enemyimg1Lt), _T("./img/enemy1Lt.gif"), 55, 55, true);
	loadimage(&(enemy::enemyimg1Rt), _T("./img/enemy1Rt.gif"), 55, 55, true);

	loadimage(&(enemy::enemyimg2Ut), _T("./img/enemy2Ut.gif"), 55, 55, true);	// green
	loadimage(&(enemy::enemyimg2Dt), _T("./img/enemy2Dt.gif"), 55, 55, true);
	loadimage(&(enemy::enemyimg2Lt), _T("./img/enemy2Lt.gif"), 55, 55, true);
	loadimage(&(enemy::enemyimg2Rt), _T("./img/enemy2Rt.gif"), 55, 55, true);

	loadimage(&(enemy::enemyimg3Ut), _T("./img/enemy3Ut.gif"), 55, 55, true);	// yellow
	loadimage(&(enemy::enemyimg3Dt), _T("./img/enemy3Dt.gif"), 55, 55, true);
	loadimage(&(enemy::enemyimg3Lt), _T("./img/enemy3Lt.gif"), 55, 55, true);
	loadimage(&(enemy::enemyimg3Rt), _T("./img/enemy3Rt.gif"), 55, 55, true);

	loadimage(&(item::bombimg), _T("./img/bomb.gif"));
	loadimage(&(item::timerimg), _T("./img/timer.gif"));
	loadimage(&(item::starimg), _T("./img/star.gif"));
	loadimage(&(item::protectimg), _T("./img/protect.gif"), 40, 40, true);
	loadimage(&(item::lifeimg), _T("./img/life.gif"), 40, 40, true);
	loadimage(&(interfaces::clockbgimg), _T("./img/clock3.jpg"), 1020, 880, true);

	loadimage(&(effect::blast1img), _T("./img/blast1.gif"), 60, 60, true);
	loadimage(&(effect::blast2img), _T("./img/blast2.gif"), 60, 60, true);
	loadimage(&(effect::blast3img), _T("./img/blast3.gif"), 60, 60, true);
	loadimage(&(effect::blast4img), _T("./img/blast4.gif"), 60, 60, true);
	loadimage(&(effect::blast5img), _T("./img/blast5.gif"), 60, 60, true);
	loadimage(&(effect::blast6img), _T("./img/blast6.gif"), 60, 60, true);
	loadimage(&(effect::blast7img), _T("./img/blast7.gif"), 60, 60, true);
	loadimage(&(effect::blast8img), _T("./img/blast8.gif"), 60, 60, true);

	loadimage(&(effect::born1img), _T("./img/born1.gif"), 60, 60, true);
	loadimage(&(effect::born2img), _T("./img/born2.gif"), 60, 60, true);
	loadimage(&(effect::born3img), _T("./img/born3.gif"), 60, 60, true);
	loadimage(&(effect::born4img), _T("./img/born4.gif"), 60, 60, true);

	loadimage(&(effect::hit1img), _T("./img/hit1.gif"), 16, 16, true);
	loadimage(&(effect::hit2img), _T("./img/hit2.gif"), 16, 16, true);
	loadimage(&(effect::hit3img), _T("./img/hit3.gif"), 16, 16, true);
	loadimage(&(effect::hit4img), _T("./img/hit4.gif"), 16, 16, true);
	loadimage(&(effect::hit5img), _T("./img/hit5.gif"), 16, 16, true);

	loadimage(&(interfaces::selecttankimg), _T("./img/selecttank.gif"));
	loadimage(&(interfaces::buttonimg), _T("./img/button.gif"), 200, 100, true);

	loadimage(&(interfaces::startimg), _T("./img/text/start.gif"), 145, 45, true);
	loadimage(&(interfaces::exitimg), _T("./img/text/exit.gif"), 145, 45, true);
	loadimage(&(interfaces::settingimg), _T("./img/text/setting.gif"), 145, 45, true);
	loadimage(&(interfaces::menuimg), _T("./img/text/menu.gif"), 145, 45, true);
	loadimage(&(interfaces::continueimg), _T("./img/text/continue.gif"), 145, 45, true);
	loadimage(&(interfaces::nextimg), _T("./img/text/next.gif"), 145, 45, true);
	loadimage(&(interfaces::restartimg), _T("./img/text/restart.gif"), 145, 45, true);
	loadimage(&(interfaces::customimg), _T("./img/text/custom.gif"), 145, 45, true);
	loadimage(&(interfaces::easyimg), _T("./img/text/easy.gif"), 145, 45, true);
	loadimage(&(interfaces::normalimg), _T("./img/text/normal.gif"), 145, 45, true);
	loadimage(&(interfaces::hardimg), _T("./img/text/hard.gif"), 145, 45, true);
	loadimage(&(interfaces::backimg), _T("./img/text/back.gif"), 145, 45, true);
	loadimage(&(interfaces::newimg), _T("./img/text/new.gif"), 145, 45, true);
	loadimage(&(interfaces::loadimg), _T("./img/text/load.gif"), 145, 45, true);

	loadimage(&(interfaces::musicimg), _T("./img/text/music.gif"), 145, 45, true);
	loadimage(&(interfaces::soundimg), _T("./img/text/sound.gif"), 145, 45, true);
	loadimage(&(interfaces::openimg), _T("./img/text/open.gif"), 145, 45, true);
	loadimage(&(interfaces::closeimg), _T("./img/text/close.gif"), 145, 45, true);

	loadimage(&(interfaces::clearimg), _T("./img/clear.gif"));
	loadimage(&(interfaces::pauseimg), _T("./img/pause.gif"));
	loadimage(&(interfaces::gameoverimg), _T("./img/gameover.gif"));
	loadimage(&(interfaces::victoryimg), _T("./img/victory.gif"));
	loadimage(&(interfaces::gameoverimg), _T("./img/gameover.gif"));
	loadimage(&(interfaces::stageimg), _T("./img/text/stage.gif"));

	loadimage(&(interfaces::bgimg), _T("./img/bg.jpg"), 1020, 880, true);
	loadimage(&(interfaces::bg2img), _T("./img/bg2.jpg"), 1020, 880, true);
	loadimage(&(interfaces::titleimg), _T("./img/title.gif"));

	loadimage(&(interfaces::number0img), _T("./img//numbers/0.gif"));
	loadimage(&(interfaces::number1img), _T("./img//numbers/1.gif"));
	loadimage(&(interfaces::number2img), _T("./img//numbers/2.gif"));
	loadimage(&(interfaces::number3img), _T("./img//numbers/3.gif"));
	loadimage(&(interfaces::number4img), _T("./img//numbers/4.gif"));
	loadimage(&(interfaces::number5img), _T("./img//numbers/5.gif"));
	loadimage(&(interfaces::number6img), _T("./img//numbers/6.gif"));
	loadimage(&(interfaces::number7img), _T("./img//numbers/7.gif"));
	loadimage(&(interfaces::number8img), _T("./img//numbers/8.gif"));
	loadimage(&(interfaces::number9img), _T("./img//numbers/9.gif"));
	loadimage(&(interfaces::slashimg), _T("./img//numbers/slash.gif"));
}

void interfaces::choose_difficulty()
{
	cleardevice();
	enum select { Easy, Normal, Hard, Back}  myselect = Easy;
	int readcd = reset_readcd;
	public_readcd = 100;
	while (true)
	{
		Putimage(0, 0, bgimg);
        show_version();

		Putimage(305, 200, titleimg);

		Putimage(410, 360, buttonimg);
		Putimage(410, 420, buttonimg);
		Putimage(410, 480, buttonimg);
		Putimage(410, 540, buttonimg);
		Putimage(438, 395, easyimg);
		Putimage(438, 455, normalimg);
		Putimage(438, 515, hardimg);
		Putimage(438, 575, backimg);
		if (GetAsyncKeyState(VK_UP) & 0x8000 && readcd == 0)
		{
			myselect = (select)((myselect - 1) % 4);
			readcd = reset_readcd;
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000 && readcd == 0)
		{
			myselect = (select)((myselect + 1) % 4);
			readcd = reset_readcd;
		}

		if (myselect == -1)
			myselect = Back;

		switch (myselect)
		{
		case Easy:Putimage(350, 385, selecttankimg); break;
		case Normal:Putimage(350, 445, selecttankimg); break;
		case Hard: Putimage(350, 505, selecttankimg); break;
		case Back:Putimage(350, 565, selecttankimg); break;
		default:break;
		}

		if (GetAsyncKeyState(VK_RETURN) & 0x8000 && public_readcd == 0)
		{
			public_readcd = 100;
			switch (myselect)
			{
			case Easy: map::difficulty = easy; return;
			case Normal:map::difficulty = normal; return;
			case Hard:map::difficulty = hard; return;
			case Back:into_mainmenu = true; return;
			default:break;
			}
		}
		FlushBatchDraw(); //执行绘图

		//Sleep(1);
		cleardevice();

		if (readcd > 0)
			readcd--;
		if (public_readcd > 0)
			public_readcd--;
	}
}

void interfaces::custom_map_choose()
{
	cleardevice();
	enum select { New, Load, Back }  myselect = New;
	int readcd = reset_readcd;
	public_readcd = 100;
	while (true)
	{
		Putimage(0, 0, bgimg);
		show_version();

		Putimage(305, 200, titleimg);

		Putimage(410, 360, buttonimg);
		Putimage(410, 420, buttonimg);
		Putimage(410, 480, buttonimg);
		Putimage(438, 395, newimg);
		Putimage(438, 455, loadimg);
		Putimage(438, 515, backimg);
		if (GetAsyncKeyState(VK_UP) & 0x8000 && readcd == 0)
		{
			myselect = (select)((myselect - 1) % 3);
			readcd = reset_readcd;
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000 && readcd == 0)
		{
			myselect = (select)((myselect + 1) % 3);
			readcd = reset_readcd;
		}

		if (myselect == -1)
			myselect = Back;

		switch (myselect)
		{
		case New:Putimage(350, 385, selecttankimg); break;
		case Load:Putimage(350, 445, selecttankimg); break;
		case Back:Putimage(350, 505, selecttankimg); break;
		default:break;
		}

		if (GetAsyncKeyState(VK_RETURN) & 0x8000 && public_readcd == 0)
		{
			public_readcd = 0;
			switch (myselect)
			{
			case New: 
				builder::load_custom_sum(); 
				map::init_custom_map(true);
				return;
			case Load:
			{
				bool ifexist = builder::check_custom_map();
				if (ifexist == false)
					continue;
				else
				{
					map::init_custom_map(true);
					return;
				}
			}
			case Back:into_mainmenu = true; return;
			default:break;
			}
		}
		FlushBatchDraw(); //执行绘图

						  //Sleep(1);
		cleardevice();

		if (readcd > 0)
			readcd--;
		if (public_readcd > 0)
			public_readcd--;
	}
}

void interfaces::draw_all()      //绘制下一帧所有存在的对象
{
	if (enemy::timestop == true)//背景
		Putimage(0, 0, (interfaces::clockbgimg));
	else
		Putimage(0, 0, (interfaces::bg2img));

	show_panel();//游戏上方的面板

	if (player::p1.ifdead() == false)
		player::p1.drawplayer();  //绘制当前的p1

	//srand((unsigned)time(NULL));
	for (int i = 0; i < enemy::enemies.size(); i++) //遍历所有敌人
	{
		if (map::difficulty != hard)
			enemy::enemies[i]->random_act();       //敌军随机行动（简单或一般难度）
		else
			enemy::enemies[i]->attack_act();       //困难模式，敌军主动攻击玩家
		enemy::enemies[i]->drawenemy();           //绘制当前第i个敌人
	}

	bullet *p = bulletlist.head, *nextp;   //指向头结点，从头开始遍历
	while (p != NULL)          //遍历子弹链表
	{
		bullet *temp = p;       
		/*子弹运动过程中可能击中敌人，若击中敌人，则
		该子弹被删除，地址丢失，故用临时指针temp来存储该地址*/
		nextp = p->getnext();
		bool exist = true;      //若子弹击中敌人，则改子弹被删除，exist变为false
		temp->move(exist);      //子弹运动，exist为引用参数
		if (exist == true)
		{
			temp->drawbullet();   //绘制当前的子弹
			p = nextp;
		}
		else
			p = nextp;
	}

	for (int i = 0; i < effect::eff.size(); i++)  //遍历特效
	{
		effect::eff[i]->play();                   //播放第i个特效
		if (effect::eff[i]->exist == false)       //若播放完毕，则删除之
		{
			delete effect::eff[i];
			effect::eff.erase(effect::eff.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < barrier::barriers.size(); i++) //遍历所有障碍物
		barrier::barriers[i]->drawbarrier();           //绘制第i个障碍物

	camp::mycamp.drawcamp();                        //绘制基地

	item::item1.drawitem();                    //绘制道具
}

void interfaces::gameover()     //游戏结束界面
{
	cleardevice();

	enum select { Restart, Menu, Exit }  myselect = Restart;
	int readcd = reset_readcd;
	public_readcd = 0;
	while (true)
	{
		Putimage(0, 0, bg2img);
		Putimage(310, 200, gameoverimg);

		Putimage(410, 360, buttonimg);
		Putimage(410, 420, buttonimg);
		Putimage(410, 480, buttonimg);
		Putimage(438, 395, restartimg);
		Putimage(438, 455, menuimg);
		Putimage(438, 515, exitimg);
		if (GetAsyncKeyState(VK_UP) & 0x8000 && readcd == 0)
		{
			myselect = (select)((myselect - 1) % 3);
			readcd = reset_readcd;
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000 && readcd == 0)
		{
			myselect = (select)((myselect + 1) % 3);
			readcd = reset_readcd;
		}

		if (myselect == -1)
			myselect = Exit;

		switch (myselect)
		{
		case Restart:Putimage(350, 385, selecttankimg); break;
		case Menu:Putimage(350, 445, selecttankimg); break;
		case Exit: Putimage(350, 505, selecttankimg); break;
		default:break;
		}

		if (GetAsyncKeyState(VK_RETURN) & 0x8000 && public_readcd == 0)
		{
			public_readcd = 100;
			switch (myselect)
			{
			case Restart:
				if (map::level == 0)
				{
					map::init_custom_map(false);
					return;
				}
				else
				{
					map::level = 1;
					map::init_level(); 
					return;
				}
			case Menu:  into_mainmenu = true; return;
			case Exit:exit_game();
			default:break;
			}
		}
		FlushBatchDraw(); //执行绘图

		//Sleep(1);
		cleardevice();
		
		if (readcd > 0)
			readcd--;
		if (public_readcd > 0)
			public_readcd--;
	}
}

void interfaces::mainmenu()
{
	cleardevice();
	enum select{ Start, Custom, Setting, Exit}  myselect= Start;
	int readcd = reset_readcd;
	public_readcd = 100;
	while (true)
	{
		Putimage(0, 0, bgimg);
		show_version();

		Putimage(305, 200, titleimg);
		Putimage(410, 360, buttonimg);
		Putimage(410, 420, buttonimg);
		Putimage(410, 480, buttonimg);
		Putimage(410, 540, buttonimg);

		Putimage(438, 395, startimg);
		Putimage(438, 455, customimg);
		Putimage(438, 515, settingimg);
		Putimage(438, 575, exitimg);
		if (GetAsyncKeyState(VK_UP) & 0x8000 && readcd == 0)
		{
			myselect = (select)((myselect - 1) % 4);
			readcd = reset_readcd;
		}
		
		if (GetAsyncKeyState(VK_DOWN) & 0x8000 && readcd == 0)
		{
			myselect = (select)((myselect + 1) % 4);
			readcd = reset_readcd;
		}

		if (myselect == -1)
		    myselect = Exit;

		switch (myselect)
		{
		case Start:Putimage(350, 385, selecttankimg); break;
		case Custom:Putimage(350, 445, selecttankimg); break;
		case Setting:Putimage(350, 505, selecttankimg); break;
		case Exit: Putimage(350, 565, selecttankimg); break;
		default:break;
		}
			
		if (GetAsyncKeyState(VK_RETURN) & 0x8000 && public_readcd == 0)
		{
			public_readcd = 100;
			switch (myselect)
			{
			case Start:
				interfaces::choose_difficulty();
				map::level = 1;
				map::init_level();
				sound::stop_music(title);
				sound::playmusic(bgm);
				return;
			case Custom:
				//interfaces::choose_difficulty();
				custom_map_choose();
				sound::stop_music(title);
				sound::playmusic(bgm);
				return;
			case Setting:setting();
				break;
			case Exit:exit_game();
			default:break;
			}
		}
		FlushBatchDraw(); //执行绘图
		
		//Sleep(1);
		cleardevice();

		if (readcd > 0)
			readcd--;
		if (public_readcd > 0)
			public_readcd--;
	}
}

void interfaces::setting()
{
	cleardevice();
	enum select { Music, Sound_Effect, Back }  myselect = Music;
	int readcd = reset_readcd;
	while (true)
	{
		Putimage(0, 0, bgimg);
		show_version();

		Putimage(305, 200, titleimg);
		Putimage(410, 360, buttonimg);
		Putimage(410, 420, buttonimg);
		Putimage(410, 480, buttonimg);
		Putimage(418, 395, musicimg);
		Putimage(418, 455, soundimg);

		if (sound::music_on == true)
			Putimage(468, 395, openimg);
		else
			Putimage(468, 395, closeimg);
		if (sound::sound_on == true)
			Putimage(468, 455, openimg);
		else
			Putimage(468, 455, closeimg);

		Putimage(438, 515, backimg);
		if (GetAsyncKeyState(VK_UP) & 0x8000 && readcd == 0)
		{
			myselect = (select)((myselect - 1) % 3);
			readcd = reset_readcd;
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000 && readcd == 0)
		{
			myselect = (select)((myselect + 1) % 3);
			readcd = reset_readcd;
		}

		if (myselect == -1)
			myselect = Back;

		switch (myselect)
		{
		case Music:Putimage(350, 385, selecttankimg); break;
		case Sound_Effect:Putimage(350, 445, selecttankimg); break;
		case Back: Putimage(350, 505, selecttankimg); break;
		default:break;
		}

		if (GetAsyncKeyState(VK_RETURN) & 0x8000 && public_readcd == 0)
		{
			public_readcd = 100;
			switch (myselect)
			{
			case Music:
				if (sound::music_on == false)
				{
					sound::music_on = true;
					sound::resume_music(title);
				}
				else
				{
					sound::music_on = false;
					sound::pause_music(title);
				}
				break;
			case Sound_Effect:
				if (sound::sound_on == false)
					sound::sound_on = true;
				else
					sound::sound_on = false; 
				break;
			case Back:return;
			default:break;
			}
		}
		FlushBatchDraw(); //执行绘图

						  //Sleep(1);
		cleardevice();

		if (readcd > 0)
			readcd--;
		if (public_readcd > 0)
			public_readcd--;
	}
}

void interfaces::pause()
{
	sound::pause_music(bgm);
	cleardevice();
	enum select { Continue, Menu, Exit }  myselect = Continue;
	int readcd = reset_readcd;
	public_readcd = 0;
	while (true)
	{
		Putimage(0, 0, bg2img);
		Putimage(380, 250, pauseimg);

		Putimage(410, 360, buttonimg);
		Putimage(410, 420, buttonimg);
		Putimage(410, 480, buttonimg);
		Putimage(438, 395, continueimg);
		Putimage(438, 455, menuimg);
		Putimage(438, 515, exitimg);
		if (GetAsyncKeyState(VK_UP) & 0x8000 && readcd == 0)
		{
			myselect = (select)((myselect - 1) % 3);
			readcd = reset_readcd;
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000 && readcd == 0)
		{
			myselect = (select)((myselect + 1) % 3);
			readcd = reset_readcd;
		}

		if (myselect == -1)
			myselect = Exit;

		switch (myselect)
		{
		case Continue:Putimage(350, 385, selecttankimg); break;
		case Menu:Putimage(350, 445, selecttankimg); break;
		case Exit: Putimage(350, 505, selecttankimg); break;
		default:break;
		}

		if (GetAsyncKeyState(VK_RETURN) & 0x8000 && public_readcd == 0)
		{
			public_readcd = 100;
			switch (myselect)
			{
			case Continue: sound::resume_music(bgm); return;
			case Menu:into_mainmenu = true; return;
			case Exit:exit_game();
			default:break;
			}
		}
		FlushBatchDraw(); //执行绘图

		//Sleep(1);
		cleardevice();

		//Putimage(0, 0, item::clockimg);
		if (readcd > 0)
			readcd--;
		if (public_readcd > 0)
			public_readcd--;
	}
}

void interfaces::stage_clear()
{
	cleardevice();
	enum select { Next, Menu, Exit }  myselect = Next;
	int readcd = reset_readcd;
	public_readcd = 0;
	while (true)
	{
		Putimage(0, 0, bg2img);
		Putimage(390, 200, clearimg);

		Putimage(410, 360, buttonimg);
		Putimage(410, 420, buttonimg);
		Putimage(410, 480, buttonimg);
		Putimage(438, 395, nextimg);
		Putimage(438, 455, menuimg);
		Putimage(438, 515, exitimg);
		if (GetAsyncKeyState(VK_UP) & 0x8000 && readcd == 0)
		{
			myselect = (select)((myselect - 1) % 3);
			readcd = reset_readcd;
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000 && readcd == 0)
		{
			myselect = (select)((myselect + 1) % 3);
			readcd = reset_readcd;
		}

		if (myselect == -1)
			myselect = Exit;

		switch (myselect)
		{
		case Next:Putimage(350, 385, selecttankimg); break;
		case Menu:Putimage(350, 445, selecttankimg); break;
		case Exit: Putimage(350, 505, selecttankimg); break;
		default:break;
		}

		if (GetAsyncKeyState(VK_RETURN) & 0x8000 && public_readcd == 0)
		{
			public_readcd = 100;
			switch (myselect)
			{
			case Next:next_level(); return;
			case Menu: into_mainmenu = true; return;
			case Exit:exit_game();
			default:break;
			}
		}
		FlushBatchDraw(); //执行绘图

		//Sleep(1);
		cleardevice();

		if (readcd > 0)
			readcd--;
		if (public_readcd > 0)
			public_readcd--;
	}
}

void interfaces::victory()    //胜利
{
	cleardevice();
	enum select { Restart, Menu, Exit }  myselect = Restart;
	int readcd = reset_readcd;
	public_readcd = 0;
	while (true)
	{
		Putimage(0, 0, bg2img);
		Putimage(369, 200, victoryimg);

		Putimage(410, 360, buttonimg);
		Putimage(410, 420, buttonimg);
		Putimage(410, 480, buttonimg);
		Putimage(438, 395, restartimg);
		Putimage(438, 455, menuimg);
		Putimage(438, 515, exitimg);
		if (GetAsyncKeyState(VK_UP) & 0x8000 && readcd == 0)
		{
			myselect = (select)((myselect - 1) % 3);
			readcd = reset_readcd;
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000 && readcd == 0)
		{
			myselect = (select)((myselect + 1) % 3);
			readcd = reset_readcd;
		}

		if (myselect == -1)
			myselect = Exit;

		switch (myselect)
		{
		case Restart:Putimage(350, 385, selecttankimg); break;
		case Menu:Putimage(350, 445, selecttankimg); break;
		case Exit: Putimage(350, 505, selecttankimg); break;
		default:break;
		}

		if (GetAsyncKeyState(VK_RETURN) & 0x8000 && public_readcd == 0)
		{
			public_readcd = 100;
			switch (myselect)
			{
			case Restart:
				if (map::level == 0)
					map::init_custom_map(false);
				else
				{
					map::level = 1;
					map::init_level();
				}
				return;
			case Menu:  into_mainmenu = true; return;
			case Exit:exit_game();
			default:break;
			}
		}
		FlushBatchDraw(); //执行绘图

		//Sleep(1);
		cleardevice();

		if (readcd > 0)
			readcd--;
		if (public_readcd > 0)
			public_readcd--;
	}
}   

void interfaces::next_level()
{
	map::level++;
	map::init_level();
}

void interfaces::time_reduce()     //时间减一
{
	player::p1.reload_time_reduce();   //玩家装填时间减一

	for (int i = 0; i < enemy::enemies.size(); i++)    //所有敌人装填时间减一
	{
		enemy::enemies[i]->reload_time_reduce();
	}

	if (enemy::timestop == true)          //时停道具持续时间减一
		enemy::stoptime--;
	if (enemy::stoptime <= 0)
		enemy::timestop = false;

	if (item::item1.staytime>0)           //道具停留时间减一
		item::item1.staytime--;
	if (item::item1.staytime == 0)
		item::item1.destroyitem();
}

void interfaces::exit_game()
{
	effect::destroy_all_effect();      //摧毁所有特效
	bullet::destroy_all_bullet();      //删除所有子弹
	barrier::destroy_all_barriers();
	enemy::delete_all_enemy();
	sound::close_all_music();
	sound::close_all_sound();
	closegraph();
	exit(0);
}
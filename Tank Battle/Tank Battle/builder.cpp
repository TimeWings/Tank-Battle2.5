#include "stdafx.h"
#include "barrier.h"
#include "builder.h"
#include "sound.h"

builder::builder()
{
	type = steel;
	image = steelimg;
	pos = point::makepoint(0, 41);
	width = image.getwidth();
	height = image.getheight();
	shape.setrec(pos.x, pos.x + width, pos.y, pos.y + height);
	speed = width;
}

builder::~builder()
{

}

void builder::move()             //移动一格
{
	newpos();
	newshape();

	toborder();
	newshape();
}

void builder::newpos()
{
	switch (tank_direction)
	{
	case up:this->pos.y -= this->speed;
		break;
	case down:this->pos.y += this->speed;
		break;
	case left:this->pos.x -= this->speed;
		break;
	case right:this->pos.x += this->speed;
		break;
	default:
		break;
	}
}

void builder::newshape()
{
	shape.setrec(pos.x, pos.x + width, pos.y, pos.y + height);
}

void builder::toborder()    //防止坦克出界
{
	switch (tank_direction)
	{
	case up:
		if (this->pos.y < panel_height + 1)
			this->pos.y = panel_height + 1;
		break;
	case down:
		if (this->pos.y + this->height > window_height)
			this->pos.y = window_height - this->height;
		break;
	case left:
		if (this->pos.x < 1)
			this->pos.x = 1;
		break;
	case right:
		if (this->pos.x + this->width > window_width)      //防止坦克出界
			this->pos.x = window_width - this->width;
		break;
	default:
		break;
	}
}

void builder::control_builder()
{
	int type = barrier_type(this->type);
	static int readcd = 0;
	static int readcd2 = 0;
	const int reset_readcd = 60;
	if (GetAsyncKeyState(VK_UP) & 0x8000 && readcd2 == 0)   //向上移动
	{
		tank_direction = up;
		move();
		readcd2 = reset_readcd;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000 && readcd2 == 0)  //向下移动
	{
		tank_direction = down;
		move();
		readcd2 = reset_readcd;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000 && readcd2 == 0)  //向左移动
	{
		tank_direction = left;
		move();
		readcd2 = reset_readcd;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && readcd2 == 0)  //向右移动
	{
		tank_direction = right;
		move();
		readcd2 = reset_readcd;
	}

	if (GetAsyncKeyState('Z') & 0x8000 && readcd == 0)
	{
		type--;
		if (type < 0)
			type = 3;
		this->type = (barrier_type)type;
		change_image();
		readcd = reset_readcd;
	}

	if (GetAsyncKeyState('X') & 0x8000 && readcd == 0)
	{
		type++;
		if (type > 3)
			type = 0;
		this->type = (barrier_type)type;
		change_image();
		readcd = reset_readcd;
	}

	if (GetAsyncKeyState('C') & 0x8000 && readcd == 0)
	{
		putbarrier(pos.x, pos.y, (barrier_type)type);
		readcd = reset_readcd;
	}
	if (readcd > 0)
		readcd--;
	if (readcd2 > 0)
		readcd2--;
}

void builder::change_image()
{
	switch (type)
	{
	case steel:	image = barrier::steelimg; break;
	case grass:	image = barrier::grassimg; break;
	case water:	image = barrier::waterimg; break;
	case brick:	image = barrier::brickimg; break;
	default:break;
	}
	width = image.getwidth();
	height = image.getheight();
	newshape();
}

void builder::draw_all_barriers()
{
	for (int i = 0; i < barrier::barriers.size(); i++)
		barrier::barriers[i]->drawbarrier();
}

void builder::putbarrier(int x, int y, barrier_type type)
{
	barrier *newbarrier = new barrier(x, y, (barrier_type)type);
	barrier::barriers.push_back(newbarrier);
}

bool builder::build_custom_map()
{
	cleardevice();
	
	bool ifsave = false;
	builder builder1;
	barrier::destroy_all_barriers();
	camp::mycamp.initcamp(480, 821);
	player::p1.initplayer(390, 821, up);
	int readcd = 0;
	int type = 0;
	while (true)
	{
		builder1.control_builder();
		
		Putimage(0, 0, (interfaces::bg2img));
		line(0, panel_height, window_width, panel_height);      //上边界
		RECT r = { 0, 0, window_width, panel_height };
		drawtext(_T("Z / X：切换类型  C：放置障碍物  S： 保存  空格：开始游戏"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		player::p1.drawplayer();
		camp::mycamp.drawcamp();
		draw_all_barriers();
		Putimage(builder1.pos.x, builder1.pos.y, builder1.image);

		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)   //按ESC暂停
		{
			sound::playsound(pause_sound);
			interfaces::pause();
			if (interfaces::into_mainmenu == true)
				break;
		}
		if (GetAsyncKeyState(' ') & 0x8000)
			break;
		if (GetAsyncKeyState('S') & 0x8000)
		{
			ifsave = true;
			RECT r = { 0, 0, 100, panel_height };
			drawtext(_T("保存成功"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			Sleep(10);
		}

		FlushBatchDraw();
		//Sleep(1);
		cleardevice();
		if (readcd > 0)
			readcd--;
	}
	return ifsave;
}

void builder::load_custom_sum() //加载已经建好的自定义地图个数
{
	int sum = 0;
	FILE *fp = NULL;
	fopen_s(&fp, "./map/custom/data.txt", "r"); //打开data文件，data存储了已建好的地图总数
	if (fp == NULL)
		fopen_s(&fp, "./map/custom/data.txt", "w");//如果不存在data文件，则创建之

	if (fp != NULL)
		fscanf_s(fp, "%d", &sum); //sum指的是玩家总共建造的图的个数
	fclose(fp);
	sum++;//新建地图，sum+1

	bool ifsave = builder::build_custom_map();//开始建造地图，返回值为是否保存所建造的地图
	if (ifsave == true)    
		savetxt(sum);      //保存地图到txt文件中
}

void builder::savetxt(int number)
{
	FILE *fp = NULL;
	fopen_s(&fp, "./map/custom/data.txt", "w+");//再次打开data输入number，更新地图的总数
	if (fp != NULL)
		fprintf(fp, "%d", number);
	fclose(fp);

	FILE *fp2 = NULL;
	char map[50];
	sprintf_s(map, "./map/custom/custom%d.txt", number);
	fopen_s(&fp2, map, "w+"); //保存玩家的自定义地图

	for (int i = 0; i < barrier::barriers.size(); i++)
	{
		if (fp2 == NULL)
			break;
		fprintf(fp2, "%d %d %d\n", (int)barriers[i]->gettype(), barriers[i]->pos.x, barriers[i]->pos.y);
	}
	fclose(fp2);
}


bool builder::check_custom_map()
{
	camp::mycamp.initcamp(480, 821);
	player::p1.initplayer(390, 821, up);
	int Sum = 0;
	FILE *fp = NULL;
	fopen_s(&fp, "./map/custom/data.txt", "r");
	if (fp != NULL)
		fscanf_s(fp, "%d", &Sum); //Sum指的是玩家总共建造的图的个数,先读取Sum
	fclose(fp);
	if (Sum == 0)
	{
		RECT r = { 0, 300, window_width, 300 + panel_height };
		drawtext(_T("当前没有自定义地图"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		FlushBatchDraw(); //执行绘图
		Sleep(50);
		return false;
	}
	else //如果存在自定义地图
	{
		readtxt(Sum); //读取最近做的地图
		//draw_all_barriers();
		int No = Sum; //地图序号,初始化为最后做的地图序号
		int readcd = 0;
		while (true)
		{
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)   //按ESC暂停
			{
				sound::playsound(pause_sound);
				interfaces::pause();
				if (interfaces::into_mainmenu == true)
					return true;
			}

			if (GetAsyncKeyState(VK_LEFT) & 0x8000 &&readcd == 0)
			{
				if (--No == 0) //向左切换，序号减1
					No = Sum; //循环播放地图
				readtxt(No); //读取地图
				readcd = 100;
			}
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && readcd == 0)
			{
				if (++No > Sum)  //向右切换，序号加1
					No = 1; //循环播放地图
				readtxt(No); //读取地图
				readcd = 100;
			}
			if (GetAsyncKeyState(' ') & 0x8000)
				return true;

			Putimage(0, 0, (interfaces::bg2img));
			line(0, panel_height, window_width, panel_height);      //上边界
			RECT r = { 0, 0, window_width, panel_height };
			drawtext(_T("左/右：切换地图  空格：开始游戏"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			interfaces::drawnumber(930, 0, 10);

			if (No / 10 != 0)
				interfaces::drawnumber(870, 0, No / 10);
			interfaces::drawnumber(900, 0, No % 10);

			if (Sum / 10 != 0)
				interfaces::drawnumber(960, 0, Sum / 10);
			interfaces::drawnumber(990, 0, Sum % 10);

			player::p1.drawplayer();
			camp::mycamp.drawcamp();

			draw_all_barriers();
			FlushBatchDraw(); //执行绘图

			//Sleep(1);
			cleardevice();   //清屏
			if (readcd > 0)
				readcd--;
		}
	}

}

void builder::readtxt(int No)//No是当前加载的图序号
{
	int type, x, y; //种类，坐标x,y

	FILE *fp = NULL; //文件
	char map[50]; //记录地图txt文档的名字
	barrier::destroy_all_barriers();

	sprintf_s(map, "./map/custom/custom%d.txt", No);
	fopen_s(&fp, map, "r");

	if (fp == NULL)
		return;
	while (fscanf_s(fp, "%d", &type) == 1) 
	{
		fscanf_s(fp, "%d%d", &x, &y);
		barrier *w = new barrier(x, y, (barrier_type)type);
		barrier::barriers.push_back(w);
	}
	fclose(fp);
}
#include "stdafx.h"
#include "player.h"
#include "enemy.h"
#include "effect.h"
#include "bullet.h"
#include "linklist.h"
#include "interfaces.h"
#include "sound.h"
#include "map.h"

IMAGE player::playerimgU;
IMAGE player::playerimgD;
IMAGE player::playerimgL;
IMAGE player::playerimgR;
player player::p1;
extern linklist bulletlist;

player::player(int x,int y,direction dir) :tank(x, y)
{
    //this->pos = point::makepoint(x,y);
	this->tank_direction = dir;
	this->level = 1;
	this->attack = 5;
	this->life = 20;
	this->maxlife = 20;
	this->speed = 2;
	this->reload_time = 0;
	this->reset_reload_time = 80;
	this->dead = false;
	this->width = playerimgU.getwidth();
	this->height = playerimgU.getheight();
	this->shape = rec::makerec(x, x + width, y, y + height);
}


player::~player()
{
}

void player::initplayer(int x, int y, direction dir)
{
	this->pos = point::makepoint(x, y);
	this->tank_direction = dir;
	this->level = 1;
	this->attack = 5;
	this->life = 20;
	this->maxlife = 20;
	this->speed = 2;
	this->reload_time = 0;
	this->reset_reload_time = 80;
	this->dead = false;
	this->width = playerimgU.getwidth();
	this->height = playerimgU.getheight();
	this->shape = rec::makerec(x, x + width, y, y + height);

	if (map::difficulty == hard)      //困难难度提升玩家属性
	{
		level = 3;
		reset_reload_time = 40;
		maxlife = 30;
		life = 30;
	}
}

/*
void player::newpos()
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

void player::newshape()
{
	shape.setrec(pos.x, pos.x + width, pos.y, pos.y + height);
}

void player::toborder()    //防止坦克出界
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

*/

void player::control_player()
{
	if (GetAsyncKeyState(' ') & 0x8000)    //空格键发射子弹
	{
		shoot();
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)   //向上移动
	{
		tank_direction = up;
		move();
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)  //向下移动
	{
		tank_direction = down;
		move();
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)  //向左移动
	{
		tank_direction = left;
		move();
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)  //向右移动
	{
		tank_direction = right;
		move();
	}
}

void player::move()              //移动一格
{
	point oldpos = pos;          //纪录原来的位置
	newpos();                    //移动后新的位置
	newshape();                  //新的形状

	
	for (int i = 0; i < barrier::barriers.size(); i++)          //判断是否撞墙
		if (ifcrash(shape, barrier::barriers[i]->shape) == true)
		{
			if (barrier::barriers[i]->gettype() != grass)   //除了草丛，其它均不可通过
			{
				pos = oldpos;            //回到原来的位置
				newshape();
				break;
			}
		}
		

	for (int i = 0; i < enemy::enemies.size(); i++)          //判断是否撞到敌人坦克
		if (ifcrash(shape, enemy::enemies[i]->shape) == true)
		{
			pos = oldpos;
			newshape();
			break;
		}

	if (ifcrash(shape, camp::mycamp.shape))      //判断是否撞到基地
	{
		pos = oldpos;
		newshape();
	}

	toborder();     //防止移动到屏幕外面
	newshape();
}

void player::shoot()
{
	if (reload_time > 0)
		return;
	bullet *p = new bullet(pos.x, pos.y, attack, tank_direction, fromplayer);  //新建子弹对象
	bulletlist.insert(p);     //插入到链表中
	this->reload_time = reset_reload_time;  //重置装填时间
}

void player::drawplayer()
{
	switch (tank_direction)
	{
	case up:Putimage(pos.x, pos.y, playerimgU); break;
	case down:Putimage(pos.x, pos.y, playerimgD); break;
	case left:Putimage(pos.x, pos.y, playerimgL); break;
	case right:Putimage(pos.x, pos.y, playerimgR); break;
	}
}

void player::die()
{
	life = 0;
	dead = true;
	this->shape = rec::makerec(0, 0, 0, 0);
	effect::new_effect(pos.x, pos.y, blast_effect);
}

bool player::ifdead()
{
	return dead;
}

void player::lifeup(int up)
{
	life += up;
	if (life > maxlife)
		life = maxlife;
}

void player::levelup()
{
	level = level++;
	if (level > 3)
		level = 3;

	attack += 3;
	if (attack > 11)
		attack = 11;

	reset_reload_time -= 20;
	if (p1.reset_reload_time < 40)
		p1.reset_reload_time = 40;

	maxlife += 5;
	if (maxlife > 30)
		maxlife = 30;
	life = maxlife;
}

int player::getmaxlife()
{
	return maxlife;
}

int player::get_reload_time()
{
	return reload_time;
}

int player::get_reset_reload_time()
{
	return reset_reload_time;
}
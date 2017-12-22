#include "stdafx.h"
#include "tank.h"
#include "interfaces.h"
#include "bullet.h"
#include "linklist.h"

extern linklist bulletlist;

tank::tank(int x, int y) :object(x, y)
{
}


tank::~tank()
{
}

void tank::newpos()
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

void tank::newshape()
{
	shape.setrec(pos.x, pos.x + width, pos.y, pos.y + height);
}

void tank::toborder()    //防止坦克出界
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

void tank::shoot()
{
	if (reload_time > 0)
		return;
	bullet *p = new bullet(pos.x, pos.y, attack, tank_direction, fromenemy);
	bulletlist.insert(p);
	this->reload_time = reset_reload_time;
}

void tank::be_hit(int damage)
{
	life -= damage;
}

int tank::getlife()
{
	return life;
}

void tank::reload_time_reduce()
{
	if (reload_time > 0)
		reload_time--;
}
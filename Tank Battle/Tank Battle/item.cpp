#include "stdafx.h"
#include "item.h"
#include "enemy.h"
#include "player.h"
#include "map.h"
#include "interfaces.h"
#include "sound.h"

IMAGE item::bombimg;
IMAGE item::timerimg;
IMAGE item::starimg;
IMAGE item::protectimg;
IMAGE item::lifeimg;
item item::item1;

item::item(int x, int y, item_type type):object(x, y)
{
	this->exist = false;
	this->pos = point::makepoint(x, y);
	this->type = type;
	this->staytime = 0;
	this->width = bombimg.getwidth();
	this->height = bombimg.getheight();
	this->shape = rec::makerec(0, 0, 0, 0);
}


item::~item()
{
}

void item::setitem(int x, int y, item_type type)
{
	this->exist = true;
	this->pos = point::makepoint(x, y);
	this->type = type;
	this->staytime = 1500;
	this->width = bombimg.getwidth();
	this->height = bombimg.getheight();
	this->shape = rec::makerec(x, x + width, y, y + height);
}

void item::drawitem()
{
	if (exist == false)
		return;
	switch (type)
	{
	case bomb:Putimage(pos.x, pos.y, bombimg); break;
	case star:Putimage(pos.x, pos.y, starimg); break;
	case timestop:Putimage(pos.x, pos.y, timerimg); break;
	case protect:Putimage(pos.x, pos.y, protectimg); break;
	case life:Putimage(pos.x, pos.y, lifeimg); break;
	default:break;
	}
}

void item::builditem()
{
	int x = rand() % (window_width-width) + 1;
	int y = rand() % (window_height-height-panel_height) + panel_height + 1;
	item_type type =(item_type) (rand() % 5);
	setitem(x, y, type);
	sound::playsound(build_item_sound);
}

void item::destroyitem()
{
	this->exist = false;
	this->pos = point::makepoint(0, 0);
	this->staytime = 0;
	this->shape = rec::makerec(0, 0, 0, 0);
}

void item::getitem()
{
	if (exist == false)
		return;
	destroyitem();
	sound::playsound(get_item_sound);
	switch (type)
	{
	case bomb:getbomb(); break;
	case star:getstar(); break;
	case timestop:gettimestop(); break;
	case protect:getprotect(); break;
	case life:getlife(); break;
	}
}

void item::getbomb()
{
	for (int i = 0; i< enemy::enemies.size(); i++)
	{
		enemy::enemies[i]->life_to_zero();
	}
}

void item::gettimestop()
{
	enemy::timestop = true;
	enemy::stoptime = 1500;
}

void item::getstar()
{
	player::p1.levelup();
}

void item::getprotect()
{
	map::camp_protect();
}

void item::getlife()
{
	player::p1.lifeup(10);
}
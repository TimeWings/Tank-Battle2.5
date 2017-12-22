#include "stdafx.h"
#include "barrier.h"
#include "interfaces.h"
#include "map.h"
#include "enemy.h"

IMAGE barrier::img;
IMAGE barrier::steelimg;
IMAGE barrier::brickimg;
IMAGE barrier::grassimg;
IMAGE barrier::waterimg;

IMAGE barrier::steeltimg;
IMAGE barrier::bricktimg;
IMAGE barrier::grasstimg;
IMAGE barrier::watertimg;

IMAGE camp::camp0img;
IMAGE camp::camp1img;
std::vector<barrier*> barrier::barriers;
camp camp::mycamp(480, 821);

barrier::barrier(int x, int y, barrier_type type):object(x, y)
{
	switch (type)
	{
	case steel:img = steelimg; break;
	case brick:img = brickimg; break;
	case grass:img = grassimg; break;
	case water:img = waterimg; break;
	default:break;
	}
	//this->pos = point::makepoint(x, y);
	this->width = img.getwidth();
	this->height = img.getheight();
	this->shape = rec::makerec(x, x + width, y, y + height);
	this->type = type;
}

barrier::barrier()
{

}

camp::camp(int x, int y) :barrier(x, y, steel)
{
	//this->pos = point::makepoint(x, y);
	this->width = camp0img.getwidth();
	this->height = camp0img.getheight();
	this->shape = rec::makerec(x, x + width, y, y + height);
	this->destroyed = false;
}

barrier::~barrier()
{

}

camp::~camp()
{

}

void barrier::drawbarrier()
{
	if (enemy::timestop == true)
	{
		switch (type)
		{
		case steel:Putimage(pos.x, pos.y, steeltimg); break;
		case brick:Putimage(pos.x, pos.y, bricktimg); break;
		case grass:Putimage(pos.x, pos.y, grasstimg); break;
		case water:Putimage(pos.x, pos.y, watertimg); break;
		default:break;
		}
	}
	else
	{
		switch (type)
		{
		case steel:Putimage(pos.x, pos.y, steelimg); break;
		case brick:Putimage(pos.x, pos.y, brickimg); break;
		case grass:Putimage(pos.x, pos.y, grassimg); break;
		case water:Putimage(pos.x, pos.y, waterimg); break;
		default:break;
		}
	}
}

barrier_type barrier::gettype()
{
	return type;
}

void camp::drawcamp()
{
	if (destroyed == true)
		Putimage(pos.x, pos.y, camp1img);
	else
		Putimage(pos.x, pos.y, camp0img);
}

/*
void wall::setwall(int x, int y, walltype type)
{
	switch (type)
	{
	case steel:img = steelimg; break;
	case dwall:img = dwallimg; break;
	case grass:img = grassimg; break;
	case water:img = waterimg; break;
	default:break;
	}
	this->pos = point::makepoint(x, y);
	this->width = img.getwidth();
	this->height = img.getheight();
	this->shape = rec::makerec(x, x + width, y, y + height);
	this->type = type;
}
*/

void camp::initcamp(int x, int y)
{
	this->pos = point::makepoint(x, y);
	this->width = camp0img.getwidth();
	this->height = camp0img.getheight();
	this->shape = rec::makerec(x, x + width, y, y + height);
	this->destroyed = false;
}


void barrier::initbarrier(int level)
{
	destroy_all_barriers();
	int type, x, y;
	FILE *fp = NULL;
	char path[30];
	sprintf_s(path,"./map/map_level%d.txt",level);
	fopen_s(&fp, path, "r");
	if (fp == NULL)
		return;

	while (fscanf_s(fp, "%d", &type) == 1)
	{
		fscanf_s(fp, "%d%d", &x, &y); 
		barrier *w = new barrier(x, y, (barrier_type)type);
		barriers.push_back(w);
	}
	fclose(fp);
	//map::camp_protect();
}

void barrier::destroy_all_barriers()
{
	for (int i = 0; i < barriers.size(); i++)
		delete barriers[i];
	barriers.clear();
}
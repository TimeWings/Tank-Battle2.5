#include "stdafx.h"
#include "effect.h"
#include "interfaces.h"

std::vector<effect*> effect::eff;
IMAGE effect:: blast1img;
IMAGE effect:: blast2img;
IMAGE effect:: blast3img;
IMAGE effect:: blast4img;
IMAGE effect:: blast5img;
IMAGE effect:: blast6img;
IMAGE effect:: blast7img;
IMAGE effect:: blast8img;
IMAGE effect::born1img;
IMAGE effect::born2img;
IMAGE effect::born3img;
IMAGE effect::born4img;
IMAGE effect::hit1img;
IMAGE effect::hit2img;
IMAGE effect::hit3img;
IMAGE effect::hit4img;
IMAGE effect::hit5img;

effect::effect(int x, int y, effect_type type)
{
	this->pos = point::makepoint(x, y);
	this->imgnum = 1;
	this->type = type;
	this->exist = true;
}


effect::~effect()
{
}

void effect::new_effect(int x, int y, effect_type type)
{
	effect *e = new effect(x, y, type);
	eff.push_back(e);
}

void effect::play()
{
	switch (type)
	{
	case blast_effect:blast();
		break;
	case born_effect:born();
		break;
	case hit_effect:hit();
		break;
	default:
		break;
	}
}

void effect::blast()
{
	switch ((int)imgnum)
	{
	case 1:Putimage(pos.x, pos.y, blast1img); break;
	case 2:Putimage(pos.x, pos.y, blast2img); break;
	case 3:Putimage(pos.x, pos.y, blast3img); break;
	case 4:Putimage(pos.x, pos.y, blast4img); break;
	case 5:Putimage(pos.x, pos.y, blast5img); break;
	case 6:Putimage(pos.x, pos.y, blast6img); break;
	case 7:Putimage(pos.x, pos.y, blast7img); break;
	case 8:Putimage(pos.x, pos.y, blast8img); break;
	}
	imgnum += 0.15;
	if (imgnum >= 9)
		exist = false;
}

void effect::born()
{
	switch ((int)imgnum)
	{
	case 1:Putimage(pos.x, pos.y, born1img); break;
	case 2:Putimage(pos.x, pos.y, born2img); break;
	case 3:Putimage(pos.x, pos.y, born3img); break;
	case 4:Putimage(pos.x, pos.y, born4img); break;
	}
	imgnum += 0.15;
	if (imgnum >= 5)
		exist = false;
}

void effect::hit()
{
	switch ((int)imgnum)
	{
	case 1:Putimage(pos.x, pos.y, hit1img); break;
	case 2:Putimage(pos.x, pos.y, hit2img); break;
	case 3:Putimage(pos.x, pos.y, hit3img); break;
	case 4:Putimage(pos.x, pos.y, hit4img); break;
	case 5:Putimage(pos.x, pos.y, hit5img); break;
	}
	imgnum += 0.15;
	if (imgnum >= 6)
		exist = false;
}

void effect::destroy_all_effect()
{
	for (int i = 0; i < eff.size(); i++)
	{
		delete eff[i];
	}
	eff.clear();
}
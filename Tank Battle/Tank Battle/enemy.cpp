#include "stdafx.h"
#include "enemy.h"
#include "linklist.h"
#include "player.h"
#include "effect.h"
#include "interfaces.h"
#include "map.h"
#include "item.h"
#include "sound.h"

extern linklist bulletlist;
IMAGE enemy::enemyimg1U;
IMAGE enemy::enemyimg1D;
IMAGE enemy::enemyimg1L;
IMAGE enemy::enemyimg1R;

IMAGE enemy::enemyimg2U;
IMAGE enemy::enemyimg2D;
IMAGE enemy::enemyimg2L;
IMAGE enemy::enemyimg2R;

IMAGE enemy::enemyimg3U;
IMAGE enemy::enemyimg3D;
IMAGE enemy::enemyimg3L;
IMAGE enemy::enemyimg3R;

IMAGE enemy::enemyimg1Ut;
IMAGE enemy::enemyimg1Dt;
IMAGE enemy::enemyimg1Lt;
IMAGE enemy::enemyimg1Rt;

IMAGE enemy::enemyimg2Ut;
IMAGE enemy::enemyimg2Dt;
IMAGE enemy::enemyimg2Lt;
IMAGE enemy::enemyimg2Rt;

IMAGE enemy::enemyimg3Ut;
IMAGE enemy::enemyimg3Dt;
IMAGE enemy::enemyimg3Lt;
IMAGE enemy::enemyimg3Rt;

int enemy::count_enemyNum = 0;
bool enemy::timestop = false;
int enemy::stoptime = 0;
std::vector<enemy*> enemy::enemies;
int enemy::killed = 0;

enemy::enemy(int x, int y, enemyColor color, int id) :tank(x, y)
{
	this->id = id;
	//this->pos = point::makepoint(x, y);
	//this->pos = point(x, y);
	this->tank_direction = (direction)(rand() % 4);
	this->color = color;

	this->attack = 5;
	this->life = 5;
	this->speed = 1;
	this->reload_time = 0;
	this->reset_reload_time = 100;

	switch (color)
	{
	case white:
		this->attack = 8;
		this->life = 8;
		break;
	case green:
		this->speed = 2;
		this->reset_reload_time = 70;
		break;
	case yellow:
		this->life = 15;
		this->attack = 4;
		break;
	default:
		break;
	}

	this->width = enemyimg1U.getwidth();
	this->height = enemyimg1U.getheight();
	this->shape = rec::makerec(x, x + width, y, y + height);
}

enemy::~enemy()
{
}

/*
void enemy::setenemy(int x, int y, enemyColor color, direction dir, int id)
{
	this->id = id;
	this->pos = point::makepoint(x, y);
	this->tank_direction = dir;
	this->color = color;

	this->attack = 5;
	this->life = 5;
	this->speed = 1;
	this->shootcd = 0;
	this->reset_shootcd = 120;

	switch (color)
	{
	case white:
		this->attack = 8;
		this->life = 10;
		break;
	case green:
		this->speed = 2;
		this->reset_shootcd = 50;
		break;
	case yellow:
		this->life = 20;
		break;
	default:
		break;
	}

	this->width = enemyimg1U.getwidth();		// �����Сһ����ͳһ��ʼ��
	this->height = enemyimg1U.getheight();
	this->shape = rec::makerec(x, x + width, y, y + height);
}
*/

void enemy::initenemy()
{
	delete_all_enemy();
	killed = 0;           //���û�ɱ��
	timestop = false;
	stoptime = 0;

	for (count_enemyNum = 0; count_enemyNum < init_enemy_number; count_enemyNum++)    //�ڳ�ʼ����λ�����ɵ���
	{
		enemy* a = new enemy(born_pos[count_enemyNum].x, born_pos[count_enemyNum].y, (enemyColor)(rand() % 3), count_enemyNum);
		enemies.push_back(a);
		effect::new_effect(a->pos.x, a->pos.y, born_effect);
	}
}

void enemy::enemyNewborn()
{
	int level = map::level;       //�õ���ǰ�ؿ�
	int random_pos = rand() % 5;  // ���������λ��
	enemyColor random_color = (enemyColor)(rand() % 3);   //�����ɫ

	if (enemies.size() < max_enemy_number_level[level] && count_enemyNum < total_enemy_number_level[level])   //��ǰ������С�������ҳ��ֵĵ�����С���ܵ�����ʱ
	{
		enemy* a = new enemy(born_pos[random_pos].x, born_pos[random_pos].y, random_color, count_enemyNum);   //���ù��캯�������ɶ���
		for (int i = 0; i < enemies.size(); i++)      //����ǰλ���Ѿ���������������ɾ���ո����ɵĵл�����
		{
			if (ifcrash(a->shape, enemies[i]->shape))
			{
				delete a;
				return;
			}
		}
		if (ifcrash(a->shape, player::p1.shape))
		{
			delete a;
			return;
		}

		effect::new_effect(a->pos.x, a->pos.y, born_effect);  //�������ɵ���Ч
		enemies.push_back(a);    //����������
		count_enemyNum++;        //�����ɵĵ�����+1
	}
}

/*
void enemy::newpos()
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

void enemy::newshape()
{
	shape.setrec(pos.x, pos.x + width, pos.y, pos.y + height);
}

void enemy::toborder()    //��ֹ̹�˳���
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
		if (this->pos.x + this->width > window_width) 
			this->pos.x = window_width - this->width;
		break;
	default:
		break;
	}
}

*/

void enemy::move()              //�ƶ�һ��
{
	point oldpos = pos;
	newpos();
	newshape();
	
	for (int i = 0; i < barrier::barriers.size(); i++)     //�ж��Ƿ�ײǽ
		if (ifcrash(shape, barrier::barriers[i]->shape) == true)
		{
			if (barrier::barriers[i]->gettype() != grass)
			{
				pos = oldpos;
				newshape();
				break;
			}
		}
		
	for (int i = 0; i < enemy::enemies.size(); i++)     //�ж��Ƿ�ײ����������̹��
		if (id != enemy::enemies[i]->id && ifcrash(shape, enemies[i]->shape) == true)
		{//id���������Լ�����������̹�ˣ��Է�ֹ���Լ�ײ���Լ���
			pos = oldpos;
			newshape();
			break;
		}

	if (ifcrash(shape, player::p1.shape) == true)    //�ж��Ƿ�ײ�����̹��
	{
		pos = oldpos;
		newshape();
	}

	if (ifcrash(shape, camp::mycamp.shape))      //�ж��Ƿ�ײ������
	{
		pos = oldpos;
		newshape();
	}

	toborder();
	newshape();
}

void enemy::shoot()
{
	if (reload_time > 0)
		return;
	bullet *p = new bullet(pos.x, pos.y, attack, tank_direction, fromenemy);
	bulletlist.insert(p);
	this->reload_time = reset_reload_time;
}

void enemy::drawenemy()
{
	if (timestop == true)
	{
		switch (color)
		{
		case white:
			switch (tank_direction)
			{
			case up:	Putimage(pos.x, pos.y, enemyimg1Ut); break;
			case down:	Putimage(pos.x, pos.y, enemyimg1Dt); break;
			case left:	Putimage(pos.x, pos.y, enemyimg1Lt); break;
			case right:	Putimage(pos.x, pos.y, enemyimg1Rt); break;
			}
			break;
		case green:
			switch (tank_direction)
			{
			case up:	Putimage(pos.x, pos.y, enemyimg2Ut); break;
			case down:	Putimage(pos.x, pos.y, enemyimg2Dt); break;
			case left:	Putimage(pos.x, pos.y, enemyimg2Lt); break;
			case right:	Putimage(pos.x, pos.y, enemyimg2Rt); break;
			}
			break;
		case yellow:
			switch (tank_direction)
			{
			case up:	Putimage(pos.x, pos.y, enemyimg3Ut); break;
			case down:	Putimage(pos.x, pos.y, enemyimg3Dt); break;
			case left:	Putimage(pos.x, pos.y, enemyimg3Lt); break;
			case right:	Putimage(pos.x, pos.y, enemyimg3Rt); break;
			}
			break;
		default:
			break;
		}
	}
	else
	{
		switch (color)
		{
		case white:
			switch (tank_direction)
			{
			case up:	Putimage(pos.x, pos.y, enemyimg1U); break;
			case down:	Putimage(pos.x, pos.y, enemyimg1D); break;
			case left:	Putimage(pos.x, pos.y, enemyimg1L); break;
			case right:	Putimage(pos.x, pos.y, enemyimg1R); break;
			}
			break;
		case green:
			switch (tank_direction)
			{
			case up:	Putimage(pos.x, pos.y, enemyimg2U); break;
			case down:	Putimage(pos.x, pos.y, enemyimg2D); break;
			case left:	Putimage(pos.x, pos.y, enemyimg2L); break;
			case right:	Putimage(pos.x, pos.y, enemyimg2R); break;
			}
			break;
		case yellow:
			switch (tank_direction)
			{
			case up:	Putimage(pos.x, pos.y, enemyimg3U); break;
			case down:	Putimage(pos.x, pos.y, enemyimg3D); break;
			case left:	Putimage(pos.x, pos.y, enemyimg3L); break;
			case right:	Putimage(pos.x, pos.y, enemyimg3R); break;
			}
			break;
		default:
			break;
		}
	}
}

void enemy::destroy()
{
	effect::new_effect(pos.x, pos.y, blast_effect);
	killed++;
	sound::playsound(blast_sound);
	delete this;
}

void enemy::random_act()       //��������ж�
{
	if (timestop == true)
		return;

	command cm;
	cm = (command)(rand() % 5);  //�����
	
	switch (cm)
	{
	case moveup: //��
	{
		this->tank_direction = up;
		this->move();
		break;
	}
	case movedown: //��
	{
		this->tank_direction = down;
		this->move();
		break;
	}
	case moveleft: //��
	{
		this->tank_direction = left;
		this->move();
		break;
	}
	case moveright: //��
	{
		this->tank_direction = right;
		this->move();
		break;
	}
	case shoot_bullet: //�����ӵ�
	{
		shoot();
		break;
	}
	}
}

void enemy::attack_act()   //����������ң�����ģʽ��
{
	//player::p1.levelup();
	if (timestop == true)
		return;
	if (player::p1.ifdead() == true)  //������������������ж�
		return;

	if (pos.x > player::p1.pos.x)     //���������ߣ��������ƶ�
	{
		this->tank_direction = left;
		this->move();
	}
	if (pos.x < player::p1.pos.x)     //��������ұߣ��������ƶ�
	{
		this->tank_direction = right;
		this->move();
	}
	if (pos.y < player::p1.pos.y)     //��������±ߣ��������ƶ�
	{
		this->tank_direction = down;
		this->move();
	}
	if (pos.y > player::p1.pos.y)     //��������ϱߣ��������ƶ�
	{
		this->tank_direction = up;
		this->move();
	}
	//this->move();
	if (abs(pos.x - player::p1.pos.x) < 20)  //ˮƽλ�ò�С��20ʱ�����
	{
		if (pos.y < player::p1.pos.y)
			tank_direction = down;
		else
			tank_direction = up;

		shoot();
	}
	if (abs(pos.y - player::p1.pos.y) < 20)  //��ֱλ�ò�С��20ʱ�����
	{
		if (pos.x < player::p1.pos.x)
			tank_direction = right;
		else
			tank_direction = left;

		shoot();
	}
}

void enemy::life_to_zero()
{
	life = 0;
}

void enemy::delete_all_enemy()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		delete enemies[i];
	}
	enemies.clear();
}



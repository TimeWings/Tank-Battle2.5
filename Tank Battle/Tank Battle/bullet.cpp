#include "stdafx.h"
#include "bullet.h"
#include "linklist.h"
#include "player.h"
#include "enemy.h"
#include "barrier.h"
#include "sound.h"
#include "effect.h"
#include "interfaces.h"

extern linklist bulletlist;
IMAGE bullet::player_bulletimg;
IMAGE bullet::enemy_bulletimg;
IMAGE bullet::enemy_bulletimgt;

bullet::bullet(int x, int y, int damage, direction tank_direction, from bfrom) :object(x, y)
{
	//this->pos=point::makepoint(x,y);
	this->damage = damage;
	this->bullet_direction = tank_direction;
	this->speed = 5;
	this->bfrom = bfrom;
	this->width = player_bulletimg.getwidth();
	this->height = player_bulletimg.getheight();
	switch (tank_direction)   //�ӵ�����λ������
	{
	case up:pos.y -= 17; pos.x += 22; break;
	case down:pos.y += 60; pos.x += 22; break;
	case left:pos.x -= 17; pos.y += 22; break;
	case right:pos.x += 60; pos.y += 22; break;
	};
	this->shape = rec::makerec(pos.x, pos.x + width, pos.y, pos.y + height);
	this->next = NULL;
}


bullet::~bullet()
{
	if (bulletlist.tail == this)   //�����ǰ�ӵ�Ϊ����β��㣬��tailָ��ָ��ǰ����ǰ�����
		bulletlist.tail = this->front;
	if (bulletlist.head == this)   //�����ǰ�ӵ�Ϊ����ͷ��㣬��headָ��ָ��ǰ���ĺ��ý��
		bulletlist.head = this->next;
	if (this->front != NULL)       //�����ǰ�ӵ���ǰ����㣬��ǰ����nextָ��ָ����ý��
		this->front->next = this->next;
	if (this->next != NULL)        //�����ǰ�ӵ��к��ý�㣬����õ�frontָ��ָ��ǰ�����
		this->next->front = this->front;
	effect::new_effect(pos.x, pos.y, hit_effect);//�����ӵ����е���Ч
	bulletlist.length--;  //�����ȼ�һ
}

void bullet::drawbullet()
{
	switch (bfrom)
	{
	case fromplayer:
		Putimage(pos.x, pos.y, player_bulletimg);
		break;
	case fromenemy:
		if (enemy::timestop == true)
			Putimage(pos.x, pos.y, enemy_bulletimgt);
		else
		    Putimage(pos.x, pos.y, enemy_bulletimg);
		break;
	default:
		break;
	}
}

void bullet::newpos()
{
	switch (bullet_direction)
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

void bullet::newshape()
{
	shape.setrec(pos.x, pos.x + width, pos.y, pos.y + height);
}

bool bullet::toborder()
{
	switch (bullet_direction)
	{
	case up:
		if (this->pos.y < panel_height)
			return true;
		break;
	case down:
		if (this->pos.y + this->height > window_height)
			return true;
		break;
	case left:
		if (this->pos.x < 1)
			return true;
		break;
	case right:
		if (this->pos.x + this->width > window_width)
			return true;
		break;
	default:
		break;
	}
	return false;
}

void bullet::move(bool &exist)              //�ƶ�һ��
{
	if (enemy::timestop == true && bfrom == fromenemy)
		return;

	newpos();
	newshape();

	for (int i = 0; i < barrier::barriers.size(); i++)             //�ж��Ƿ�ײ���ϰ�
		if (ifcrash(shape, barrier::barriers[i]->shape) == true)
		{
			if (barrier::barriers[i]->gettype() == brick || barrier::barriers[i]->gettype() == steel)
			{
				if (barrier::barriers[i]->gettype() == brick)    //����ש��
				{
					delete barrier::barriers[i];
					barrier::barriers.erase(barrier::barriers.begin() + i);
					i--;
				}
				delete this;                     //�����ӵ�
				exist = false;
				return;
			}
		}

	for (int i = 0; i< enemy::enemies.size(); i++)             //�ж��Ƿ�ײ������
		if (ifcrash(shape, enemy::enemies[i]->shape) == true)
		{
			if (bfrom == fromplayer)
			{
				enemy::enemies[i]->be_hit(damage);//����ӵ�������ң���Ե�������˺�
			}
			delete this;                     //��ײ�����������ӵ�
			exist = false;
			return;
		}
           
		if (ifcrash(shape, player::p1.shape) == true)  //�ж��Ƿ�ײ�����
		{
			if (bfrom == fromenemy)    //����ӵ����Ե��ˣ�����������˺�
				player::p1.be_hit(damage);
			delete this;       //��ײ�����������ӵ�
			exist = false;     //exist�Ǹú��������ò�������ʾ���ӵ��Ƿ���Ȼ����
			return;
		}

		if (ifcrash(shape, camp::mycamp.shape))      //�ж��Ƿ�ײ������
		{
			if (bfrom == fromenemy)
			{
				camp::mycamp.destroyed = true;
			}
			delete this;                     //��ײ�����������ӵ�
			exist = false;
			return;
		}
		

	if (toborder()==true)                 //��ֹ�ӵ�����
	{
		delete this;
		exist = false;
		return;
	}
}

bullet* bullet::getnext()
{
	return next;
}

void bullet::destroy_all_bullet()
{
	bullet *p = bulletlist.head, *pn;
	while (p != NULL)          //�����ӵ�����
	{
		pn = p->next;
		delete p;
		p = pn;
	}
}
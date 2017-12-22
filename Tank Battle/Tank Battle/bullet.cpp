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
	switch (tank_direction)   //子弹生成位置修正
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
	if (bulletlist.tail == this)   //如果当前子弹为链表尾结点，则tail指针指向当前结点的前驱结点
		bulletlist.tail = this->front;
	if (bulletlist.head == this)   //如果当前子弹为链表头结点，则head指针指向当前结点的后置结点
		bulletlist.head = this->next;
	if (this->front != NULL)       //如果当前子弹有前驱结点，则前驱的next指针指向后置结点
		this->front->next = this->next;
	if (this->next != NULL)        //如果当前子弹有后置结点，则后置的front指针指向前驱结点
		this->next->front = this->front;
	effect::new_effect(pos.x, pos.y, hit_effect);//生成子弹击中的特效
	bulletlist.length--;  //链表长度减一
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

void bullet::move(bool &exist)              //移动一格
{
	if (enemy::timestop == true && bfrom == fromenemy)
		return;

	newpos();
	newshape();

	for (int i = 0; i < barrier::barriers.size(); i++)             //判断是否撞到障碍
		if (ifcrash(shape, barrier::barriers[i]->shape) == true)
		{
			if (barrier::barriers[i]->gettype() == brick || barrier::barriers[i]->gettype() == steel)
			{
				if (barrier::barriers[i]->gettype() == brick)    //销毁砖块
				{
					delete barrier::barriers[i];
					barrier::barriers.erase(barrier::barriers.begin() + i);
					i--;
				}
				delete this;                     //销毁子弹
				exist = false;
				return;
			}
		}

	for (int i = 0; i< enemy::enemies.size(); i++)             //判断是否撞到敌人
		if (ifcrash(shape, enemy::enemies[i]->shape) == true)
		{
			if (bfrom == fromplayer)
			{
				enemy::enemies[i]->be_hit(damage);//如果子弹来自玩家，则对敌人造成伤害
			}
			delete this;                     //若撞到，则销毁子弹
			exist = false;
			return;
		}
           
		if (ifcrash(shape, player::p1.shape) == true)  //判断是否撞到玩家
		{
			if (bfrom == fromenemy)    //如果子弹来自敌人，则对玩家造成伤害
				player::p1.be_hit(damage);
			delete this;       //若撞到，则销毁子弹
			exist = false;     //exist是该函数的引用参数，表示该子弹是否仍然存在
			return;
		}

		if (ifcrash(shape, camp::mycamp.shape))      //判断是否撞到基地
		{
			if (bfrom == fromenemy)
			{
				camp::mycamp.destroyed = true;
			}
			delete this;                     //若撞到，则销毁子弹
			exist = false;
			return;
		}
		

	if (toborder()==true)                 //防止子弹出界
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
	while (p != NULL)          //遍历子弹链表
	{
		pn = p->next;
		delete p;
		p = pn;
	}
}
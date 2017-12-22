#include "stdafx.h"
#include "map.h"
#include "barrier.h"
#include "player.h"
#include "enemy.h"
#include "effect.h"
#include "item.h"
#include "bullet.h"
#include "builder.h"

int map::level = 1;
game_difficulty map::difficulty = easy;

void map::init_custom_map(bool save)  
//��ʼ���Զ����ͼ���˺����ڳ��ν���ʱ�����¿�ʼʱ���ã����ν���ʱ����true�����¿�ʼʱ����false
{
	map::level = 0;//�Զ����ͼΪ�����
	map::difficulty = normal;//Ĭ��Ϊһ���Ѷ�

	static std::vector<int> x, y, type;  //���ڴ洢�ϰ���λ�ú�����
	if (save == true)   //���ν���ʱ������Ϊtrue���洢��ǰ��ͼ
	{
		x.clear();  //���ԭ��������
		y.clear();
		type.clear();
		for (int i = 0; i < barrier::barriers.size(); i++)  //�����Զ����ͼ���ϰ������ͺ�λ�ã��Ա������¿�ʼ���ȡ
		{
			x.push_back(barrier::barriers[i]->pos.x);
			y.push_back(barrier::barriers[i]->pos.y);
			type.push_back(barrier::barriers[i]->gettype());
		}
	}//���û�����if��䣬��������¿�ʼʱ���ѱ��ݻٵ�ש�齫�޷���ԭ

	barrier::destroy_all_barriers();   //���¿�ʼ��ɾ�������ϰ��Ȼ�����¹���ȫ���ϰ������֮ǰ�洢�����ͺ�λ�ã�
	for (int i = 0; i < x.size(); i++)
	{
		barrier *b = new barrier(x[i], y[i], (barrier_type)type[i]);
		barrier::barriers.push_back(b);
	}

	effect::destroy_all_effect();      //�ݻ�������Ч
	bullet::destroy_all_bullet();      //ɾ�������ӵ�
	camp::mycamp.initcamp(480, 821);  //��ʼ������
	player::p1.initplayer(390, 821, up);   //��ʼ�����̹��
	effect::new_effect(390, 821, born_effect);
	enemy::initenemy();          //��ʼ������
	item::item1.destroyitem();   //�ݻٵ���
}

void map::init_level()
{
	effect::destroy_all_effect();      //�ݻ�������Ч
	bullet::destroy_all_bullet();      //ɾ�������ӵ�
	barrier::initbarrier(level);             //��ʼ���ϰ���
	camp::mycamp.initcamp(480, 821);  //��ʼ������
	player::p1.initplayer(390, 821, up);   //��ʼ�����̹��
	effect::new_effect(390, 821, born_effect);
	enemy::initenemy();          //��ʼ������
	item::item1.destroyitem();   //�ݻٵ���
	if (difficulty == easy)
		camp_protect();          //���Ѷ��л��ر���
	//item::item1.setitem(500, 700, timestop);
}

void map::camp_protect()
{
	barrier *w1 = new barrier(450, 851, steel);
	barrier::barriers.push_back(w1);
	barrier *w2 = new barrier(450, 821, steel);
	barrier::barriers.push_back(w2);
	barrier *w3 = new barrier(450, 791, steel);
	barrier::barriers.push_back(w3);
	barrier *w4 = new barrier(480, 791, steel);
	barrier::barriers.push_back(w4);
	barrier *w5 = new barrier(510, 791, steel);
	barrier::barriers.push_back(w5);
	barrier *w6 = new barrier(540, 791, steel);
	barrier::barriers.push_back(w6);
	barrier *w7 = new barrier(540, 821, steel);
	barrier::barriers.push_back(w7);
	barrier *w8 = new barrier(540, 851, steel);
	barrier::barriers.push_back(w8);
}

void map::camp_protect2()
{
	barrier *w1 = new barrier(450, 851, brick);
	barrier::barriers.push_back(w1);
	barrier *w2 = new barrier(450, 821, brick);
	barrier::barriers.push_back(w2);
	barrier *w3 = new barrier(450, 791, brick);
	barrier::barriers.push_back(w3);
	barrier *w4 = new barrier(480, 791, brick);
	barrier::barriers.push_back(w4);
	barrier *w5 = new barrier(510, 791, brick);
	barrier::barriers.push_back(w5);
	barrier *w6 = new barrier(540, 791, brick);
	barrier::barriers.push_back(w6);
	barrier *w7 = new barrier(540, 821, brick);
	barrier::barriers.push_back(w7);
	barrier *w8 = new barrier(540, 851, brick);
	barrier::barriers.push_back(w8);
}


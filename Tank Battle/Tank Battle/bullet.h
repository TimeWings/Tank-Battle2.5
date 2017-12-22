#pragma once
#include "enum.h"
#include "base.h"
#include "interfaces.h"

class bullet:public object     //�ӵ��࣬�̳���������
{
	friend class linklist;     //��Ԫ��
	friend void interfaces::load_all_image();//��Ԫ����
public:
	bullet(int x = 0, int y = 0, int damage = 5, 
		direction tank_direction = up, from bfrom= fromplayer);//���캯��
	~bullet();                    //��������

	void drawbullet();            //�����ӵ�
	void move(bool &exist);       //�ƶ�
	bullet* getnext();            //�õ���һ���ӵ��ĵ�ַ

	static void destroy_all_bullet();//ɾ�������ӵ�

private:
	int damage;                   //�ӵ��˺�
	int speed;                    //�ӵ��ٶ�
	from bfrom;                   //�ӵ���Դ
	direction bullet_direction;   //�ӵ�����
	bullet *front;                //ָ��ǰһ���ӵ�
	bullet *next;                 //ָ����һ���ӵ�

	void newpos();                //�ƶ����µ�λ��
	void newshape();              //�ƶ��������״
	bool toborder();              //�߽��ж�

	//�ӵ�ͼƬ
	static IMAGE player_bulletimg;
	static IMAGE enemy_bulletimg;
	static IMAGE enemy_bulletimgt;
};


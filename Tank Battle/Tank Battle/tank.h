#pragma once
#include "base.h"
#include "enum.h"

class tank:public object      //̹���࣬�̳���������
{
public:
	void be_hit(int damage);  //���ӵ�����
	int getlife();            //��������ֵ
	void reload_time_reduce();//�ӵ�װ��ʱ�����
	
protected:
	tank(int x, int y);                   //���캯��
	~tank();                  //�鹹����
	direction tank_direction; //̹�˷���
	int attack;               //������
	int speed;                //�ƶ��ٶ�
	int life;                 //����ֵ
	int reload_time;          //�ӵ�װ��ʱ�䣬Ϊ0ʱ�ſ��������λ��֡
	int reset_reload_time;    //���������ӵ�װ��ʱ�䣬�ɱ�ʾ̹�˵Ĺ���

	void newpos();            //�ƶ����µ�λ��
	void newshape();          //�ƶ��������״
	void toborder();          //�߽��ж�
	void shoot();             //���
	void virtual move() = 0;  //�ƶ������麯��������������ʵ��
};


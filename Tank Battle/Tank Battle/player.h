#pragma once
#include "enum.h"
#include "tank.h"
#include "barrier.h"
#include "interfaces.h"

class player :public tank   //����࣬�̳���̹����
{
	friend void interfaces::load_all_image();  //��Ԫ����
public:
	player(int x = 390, int y = 812, direction dir = up); //���캯��
	~player(); //��������
	void initplayer(int x = 390, int y = 812, direction dir = up);//��ʼ�����
	void drawplayer();       //�������
	void die();              //����
	bool ifdead();           //��ȡ����״̬
	void lifeup(int up);     //����ֵ����
	void levelup();          //�ȼ�����
	int getmaxlife();        //��������������ֵ
	int get_reload_time();   //�����ӵ�װ��ʱ��
	int get_reset_reload_time();//������ҹ���
	void control_player();   //�������

	static player p1;               //���һ

private:
	int level;              //�ȼ�
	int maxlife;            //�������ֵ
	bool dead;              //�Ƿ�����
	void move();            //�ƶ�
	void shoot();           //���

	//���̹��ͼƬ���ĸ�����
	static IMAGE playerimgU;
	static IMAGE playerimgD;
	static IMAGE playerimgL;
	static IMAGE playerimgR;
};


#pragma once

#include "enum.h"
#include "tank.h"
#include "interfaces.h"

class enemy:public tank            //�����࣬�̳���̹����
{
	friend void interfaces::load_all_image();  //��Ԫ����
public:
	enemy(int x = 0, int y = 0, enemyColor color = green, int id = 0);//���캯��
	~enemy();                      //��������
	void drawenemy();              //���Ƶ���
	void random_act();             //�����Ϊ���򵥣�һ��ģʽ��
	void attack_act();             //������Ϊ������ģʽ��
	void destroy();                //�ݻٸõ��ˣ�����ֵΪ��ʱ���ã�
	void life_to_zero();           //����ֵ���㣨��ը�����ߵ��ã�

	static void initenemy();       //��ʼ�����е���
	static void enemyNewborn();    //��������µĵ���
	static void delete_all_enemy();//�ݻ����е���

	static std::vector<enemy*> enemies;   //���������е���
	static bool timestop;                 //ʱ��ֹͣ�����Ƿ���Ч
	static int stoptime;                  //ʱͣ���߳���ʱ�䣬��λ��֡
	static int killed;                    //�������ĵ�����

private:
	int id;                          //��ţ��������ֲ�ͬ�ĵ���
	enemyColor color;                //��ɫ

	void move();                     //�ƶ�
	void shoot();                    //���

	static int count_enemyNum;            //�Ѿ����ɵĵ�������

	//����ͼƬ
	static IMAGE enemyimg1U;	// white
	static IMAGE enemyimg1D;
	static IMAGE enemyimg1L;
	static IMAGE enemyimg1R;

	static IMAGE enemyimg2U;	// green
	static IMAGE enemyimg2D;
	static IMAGE enemyimg2L;
	static IMAGE enemyimg2R;

	static IMAGE enemyimg3U;	// yellow
	static IMAGE enemyimg3D;
	static IMAGE enemyimg3L;
	static IMAGE enemyimg3R;

	static IMAGE enemyimg1Ut;	// white
	static IMAGE enemyimg1Dt;
	static IMAGE enemyimg1Lt;
	static IMAGE enemyimg1Rt;

	static IMAGE enemyimg2Ut;	// green
	static IMAGE enemyimg2Dt;
	static IMAGE enemyimg2Lt;
	static IMAGE enemyimg2Rt;

	static IMAGE enemyimg3Ut;	// yellow
	static IMAGE enemyimg3Dt;
	static IMAGE enemyimg3Lt;
	static IMAGE enemyimg3Rt;
};

const point born_pos[5] = { point::makepoint(481,41), point::makepoint(1,41), point::makepoint(961,41), point::makepoint(1,402), point::makepoint(961,402) };//���˳���λ��        

const int init_enemy_number = 3; //��ʼ��������

const int max_enemy_number_level[11] = { 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};  //ÿ�����о�����

const int total_enemy_number_level[11] = { 15, 15, 20, 20, 25, 25, 30, 30, 35, 35, 40};  //ÿ�صо�����

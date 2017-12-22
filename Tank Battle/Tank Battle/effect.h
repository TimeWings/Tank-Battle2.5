#pragma once

#include"base.h"
#include"enum.h"
#include "interfaces.h"

class effect            //��Ч��
{
	friend void interfaces::load_all_image();//��Ԫ����
public:
	effect(int x, int y, effect_type type);//���캯��
	~effect();//��������
	void play();       //���Ÿ���Ч
	static void new_effect(int x, int y, effect_type type);//��������Ч����������
	static void destroy_all_effect();                      //ɾ��������Ч
    bool exist;        //����Ч�Ƿ����

	static std::vector<effect*> eff;  //����洢������Ч

private:
	effect_type type;   //��Ч����
	point pos;         //��Чλ��
	double imgnum;     //��ǰ���ŵڼ���ͼƬ

	void blast();      //��ը
	void born();       //����̹��
	void hit();        //�ӵ�����

	static IMAGE blast1img;
	static IMAGE blast2img;
	static IMAGE blast3img;
	static IMAGE blast4img;
	static IMAGE blast5img;
	static IMAGE blast6img;
	static IMAGE blast7img;
	static IMAGE blast8img;
	static IMAGE born1img;
	static IMAGE born2img;
	static IMAGE born3img;
	static IMAGE born4img;
	static IMAGE hit1img;
	static IMAGE hit2img;
	static IMAGE hit3img;
	static IMAGE hit4img;
	static IMAGE hit5img;
};


#pragma once
#include "enum.h"
#include "base.h"
#include "interfaces.h"

class item:public object
{
	friend void interfaces::load_all_image();//��Ԫ����
public:
	item(int x = 0, int y = 0, item_type type = bomb);//���캯��
	~item();                      //��������
	void setitem(int x, int y, item_type type); //���õ���
	void drawitem();             //���Ƶ���
	void builditem();            //������ɵ���
	void destroyitem();          //�ݻٵ���
	void getitem();              //ʰȡ����
	int staytime;                //���߳���ʱ��

	static item item1;           //ʵ����

private:
	item_type type;              //��������
	bool exist;                  //�����Ƿ����

	void getbomb();              //ȫ�屬ը
	void gettimestop();          //ʱ��ֹͣ
	void getstar();              //��ߵȼ�
	void getprotect();           //���ر���
	void getlife();              //��������

	//����ͼƬ
	static IMAGE bombimg;
	static IMAGE timerimg;
	static IMAGE starimg;
	static IMAGE protectimg;
	static IMAGE lifeimg;
};


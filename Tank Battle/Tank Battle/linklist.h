#pragma once
#include "bullet.h"

class linklist   //�ӵ�����
{
public:
	linklist();//���캯��
	~linklist();//��������
	void insert(bullet *p);  //���ӵ�p���뵽����β��

	bullet *head;//ͷ���
	bullet *tail;//β���
	int length;  //������
};


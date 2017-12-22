#include "stdafx.h"
#include "linklist.h"


linklist::linklist()
{
	this->head = NULL;
	this->tail = NULL;
	this->length = 0;
}


linklist::~linklist()
{
}

void linklist::insert(bullet *p)
{
	if (this->length == 0)  //�������Ϊ��
	{
		this->tail = p;   //βָ��ָ��p
		this->head = p;   //ͷָ��ָ��p
		this->length++;   //���ȼ�һ
		p->front = NULL;  //p��ǰ��ָ��NULL
	}
	else                   //�������Ϊ��
	{
		this->tail->next = p; //β����nextָ��p
		p->front = this->tail;//p��ǰ��ָ��β���
		this->tail = p;       //β����Ϊp
		this->length++;       //���ȼ�һ
	}
}

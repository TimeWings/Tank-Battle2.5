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
	if (this->length == 0)  //如果链表为空
	{
		this->tail = p;   //尾指针指向p
		this->head = p;   //头指针指向p
		this->length++;   //长度加一
		p->front = NULL;  //p的前驱指向NULL
	}
	else                   //如果链表不为空
	{
		this->tail->next = p; //尾结点的next指向p
		p->front = this->tail;//p的前驱指向尾结点
		this->tail = p;       //尾结点变为p
		this->length++;       //长度加一
	}
}

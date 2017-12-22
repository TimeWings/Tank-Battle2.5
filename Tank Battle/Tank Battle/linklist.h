#pragma once
#include "bullet.h"

class linklist   //子弹链表
{
public:
	linklist();//构造函数
	~linklist();//析构函数
	void insert(bullet *p);  //将子弹p插入到链表尾部

	bullet *head;//头结点
	bullet *tail;//尾结点
	int length;  //链表长度
};


#pragma once
#include"enum.h"

class map
{
public:
	static int level;           //��ǰ�ؿ�
	static game_difficulty difficulty;  //�Ѷ�
	static void init_custom_map(bool save);    
	//��ʼ���Զ����ͼ,����true��ʾ�洢��ʱ��ͼ���ڴ��У��Ա������¿�ʼ��Ϸʱ��ȡ
	static void init_level();   //��ʼ���ؿ�
	static void camp_protect(); //���ر�����������
	static void camp_protect2();//���ر�����ש�飩
};


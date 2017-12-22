#pragma once
#include "barrier.h"
#include "stdafx.h"
#include "player.h"

class builder:public player, public barrier   //�����ߣ������Զ����ͼ���̳����������ϰ�����
{
private:
	point pos;   //λ��
	rec shape;   //��״
	int width;   //���
	int height;  //�߶�
	/*����4����Ա���ݸ�����������Ĺ�ͬ���ࣨobject�ࣩ�Ķ�Ӧ��Ա
	��Ϊbuilder�̳е��������඼��ͬ�̳���object�࣬���������ĸ���ͬ��Ա��
	��������ǣ����������޷�ȷ��ʹ����һ��*/

	IMAGE image;//��ǰ�ϰ����ͼƬ

	builder();   //���캯��
	~builder();  //��������
	void change_image();//�����ϰ������ͼ�ͼƬ

	void move(); //�ƶ�
	void newpos();//��λ��
	void newshape();//����״
	void toborder();//�߽��ж�
    /*�����ĸ�����Ϊ��д����������tank��Ķ�Ӧ����
	�������д�����ú���ʱ���õ���tank��ĺ�������ֻ�ܸı�tank��ĳ�Ա���ݣ�
	�޷��ı䱾���Ա����*/

	void control_builder(); //���ƽ����߽����ƶ��ͷ����ϰ���Ȳ���
	static void putbarrier(int x, int y, barrier_type type);//�����ϰ���
	static void draw_all_barriers();//����ȫ���ϰ���
    static void readtxt(int No);   //��ȡ��ͼtxt�ļ���NoΪ����ȡ�����
	static void savetxt(int number);  //�����½����Զ����ͼ��txt�ļ��У�numberΪ����ǰ�ĵ�ͼ������һ
	static bool build_custom_map();//��ʼ�����Զ����ͼ������ֵΪ�Ƿ񱣴�õ�ͼ����Ҫ�����򷵻�true�����򷵻�false

public:
	static void load_custom_sum();         //�����Ѿ����õ��Զ����ͼ����
	static bool check_custom_map();  //����Ƿ����Զ����ͼ��û�з���false���з���true������ҽ���ѡ��
};

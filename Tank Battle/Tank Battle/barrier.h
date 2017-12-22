#pragma once

#include "base.h"
#include "enum.h"
#include "interfaces.h"

class barrier:public object      //�ϰ����࣬�̳���������
{
	friend void interfaces::load_all_image(); //��Ԫ����
public:
	barrier(int x, int y, barrier_type type);   //���캯��
	barrier();  //�޲ι��캯��
	~barrier(); //��������
	void drawbarrier();         //�����ϰ���
	barrier_type gettype();      //�����ϰ�������

	static void destroy_all_barriers();   //�ݻ������ϰ���
	static void initbarrier(int level);  //��ʼ�������ϰ���
    static std::vector<barrier*> barriers;//������ȫ���ϰ���

protected:
	barrier_type type;  //�ϰ������ͣ�����������ש�飬ˮ�棬�ݴ�
	
	//�ϰ���ͼƬ
	static IMAGE img;
	static IMAGE steelimg;
	static IMAGE brickimg;
	static IMAGE grassimg;
	static IMAGE waterimg;

	static IMAGE steeltimg;
	static IMAGE bricktimg;
	static IMAGE grasstimg;
	static IMAGE watertimg;
};

class camp :public barrier       //�����࣬�̳����ϰ�����
{
	friend void interfaces::load_all_image(); //��Ԫ����
public:
	bool destroyed;           //�Ƿ��ѱ��ݻ�
	camp(int x, int y);       //���캯��
	~camp();                  //��������
	void drawcamp();          //���ƻ���
	void initcamp(int x, int y);  //��ʼ������
	static camp mycamp;       //�����Ҫ�����Ļ���

private:
	//����ͼƬ
	static IMAGE camp0img;
	static IMAGE camp1img;
};

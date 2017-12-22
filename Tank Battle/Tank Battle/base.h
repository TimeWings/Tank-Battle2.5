#pragma once

class point             //����
{
public:
	int x, y;

	point(int x = 0, int y = 0);  //���캯����Ĭ��Ϊ(0,0)
    static point makepoint(int x, int y);   //����һ����(x,y)������ 
};

class rec                //������
{
public:
	int left, right, up, down;

	rec(int left = 0, int right = 0, int up = 0, int down = 0);  //���캯��
	void setrec(int left, int right, int up, int down);          //�������øþ���
	static rec makerec(int left, int right, int up, int down);   //����һ�����β�����
};

class object               //�����࣬ͬʱ��̹���࣬�ӵ��࣬�����࣬�ϰ�����Ļ���
{
public:
	point pos;             //λ��
	rec shape;             //��״�������������������

	static bool if_point_in_rec(const point &p, const rec &r);      //�жϵ�p�Ƿ��ھ���r��
	static bool ifcrash(const rec &r1, const rec &r2);             //�жϾ���r1�;���r2�Ƿ��ص�

protected:
	object(int x = 0, int y = 0);              //���캯��
	int width;             //���
	int height;            //�߶�
};


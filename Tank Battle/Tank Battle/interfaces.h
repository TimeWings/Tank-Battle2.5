#pragma once
class interfaces
{
public:
	void static load_all_image();     //��������ͼƬ
	void static choose_difficulty();  //ѡ���ѶȽ���
	void static custom_map_choose();   //�Զ����ͼѡ�����
	void static draw_all();           //������һ֡���д��ڵĶ���
	void static gameover();           //��Ϸ��������
	void static mainmenu();           //���˵�����
	void static setting();            //���ý���
	void static pause();              //��ͣ����
	void static stage_clear();        //���ؽ���
	void static next_level();         //��һ��
	void static victory();            //ʤ������
	void static exit_game();          //�˳���Ϸ
    void static time_reduce();        //ʱ���һ
	void static drawnumber(int x, int y, int number);  //��������
	void static show_version();       //��ʾ�汾��
	void static show_panel();         //��ʾ���

	static int public_readcd;         //��ȡ���̺����ȴʱ��
	static bool into_mainmenu;        //�Ƿ�������˵�

	//�����Ǵ���ͼƬ
	IMAGE static bgimg;
	IMAGE static bg2img;
private:
	IMAGE static selecttankimg;
	
	IMAGE static clockbgimg;
	IMAGE static buttonimg;

	IMAGE static titleimg;
	IMAGE static clearimg;
	IMAGE static pauseimg;
	IMAGE static gameoverimg;
	IMAGE static victoryimg;
	IMAGE static stageimg;

	IMAGE static settingimg;
	IMAGE static menuimg;
	IMAGE static exitimg;
	IMAGE static startimg;
	IMAGE static customimg;
	IMAGE static restartimg;
	IMAGE static continueimg;
	IMAGE static nextimg;
	IMAGE static newimg;
	IMAGE static loadimg;

	IMAGE static musicimg;
	IMAGE static soundimg;
	IMAGE static openimg;
	IMAGE static closeimg;
	IMAGE static backimg;

	IMAGE static easyimg;
	IMAGE static normalimg;
	IMAGE static hardimg;

	IMAGE static number0img;
	IMAGE static number1img;
	IMAGE static number2img;
	IMAGE static number3img;
	IMAGE static number4img;
	IMAGE static number5img;
	IMAGE static number6img;
	IMAGE static number7img;
	IMAGE static number8img;
	IMAGE static number9img;
	IMAGE static slashimg;
	IMAGE static timestopimg;
};

const int window_width = 1020;          //���ڿ��
const int window_height = 880;          //���ڸ߶�
const int panel_height = 40;            //��ʾ���߶�
const int reset_readcd = 80;            

void Putimage(int x, int y, IMAGE &img);//��ͼ����

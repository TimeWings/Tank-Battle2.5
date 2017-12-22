#pragma once
class interfaces
{
public:
	void static load_all_image();     //加载所有图片
	void static choose_difficulty();  //选择难度界面
	void static custom_map_choose();   //自定义地图选择界面
	void static draw_all();           //绘制下一帧所有存在的对象
	void static gameover();           //游戏结束界面
	void static mainmenu();           //主菜单界面
	void static setting();            //设置界面
	void static pause();              //暂停界面
	void static stage_clear();        //过关界面
	void static next_level();         //下一关
	void static victory();            //胜利界面
	void static exit_game();          //退出游戏
    void static time_reduce();        //时间减一
	void static drawnumber(int x, int y, int number);  //绘制数字
	void static show_version();       //显示版本号
	void static show_panel();         //显示面板

	static int public_readcd;         //读取键盘后的冷却时间
	static bool into_mainmenu;        //是否进入主菜单

	//以下是大量图片
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

const int window_width = 1020;          //窗口宽度
const int window_height = 880;          //窗口高度
const int panel_height = 40;            //显示面板高度
const int reset_readcd = 80;            

void Putimage(int x, int y, IMAGE &img);//绘图函数

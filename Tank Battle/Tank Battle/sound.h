#pragma once

enum music { title, bgm };

enum sound_effect { bomb_sound, camp_destroyed_sound, fire_sound, blast_sound, player_blast_sound, pause_sound, get_item_sound, build_item_sound};

class sound
{
public:
	static bool music_on, sound_on;      //音乐，音效是否开启
	static void open_all_music();        //打开所有音乐文件
	static void playmusic(music music_type);   //从头播放音乐
	static void pause_music(music music_type); //暂停播放音乐
	static void resume_music(music music_type);//继续播放音乐
	static void stop_music(music music_type);  //停止播放音乐
	static void close_all_music();       //关闭所有音乐

	static void open_all_sound();        //打开所有音效文件
	static void playsound(sound_effect sound_effect_type);  //从头播放音效
	static void close_all_sound();      //关闭所有音效
};



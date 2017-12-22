#pragma once

enum music { title, bgm };

enum sound_effect { bomb_sound, camp_destroyed_sound, fire_sound, blast_sound, player_blast_sound, pause_sound, get_item_sound, build_item_sound};

class sound
{
public:
	static bool music_on, sound_on;      //���֣���Ч�Ƿ���
	static void open_all_music();        //�����������ļ�
	static void playmusic(music music_type);   //��ͷ��������
	static void pause_music(music music_type); //��ͣ��������
	static void resume_music(music music_type);//������������
	static void stop_music(music music_type);  //ֹͣ��������
	static void close_all_music();       //�ر���������

	static void open_all_sound();        //��������Ч�ļ�
	static void playsound(sound_effect sound_effect_type);  //��ͷ������Ч
	static void close_all_sound();      //�ر�������Ч
};



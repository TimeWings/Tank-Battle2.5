#include "stdafx.h"
#include "sound.h"

bool sound::music_on = true;
bool sound::sound_on = true;

void sound::open_all_music()
{
	mciSendString(_T("open ./sound/title.mp3 alias title"), NULL, 0, NULL);
	mciSendString(_T("open ./sound/bgm.mp3 alias bgm"), NULL, 0, NULL);
}

void sound::playmusic(music music_type)
{
	switch (music_type)
	{
	case title:mciSendString(_T("play title from 0 repeat"), NULL, 0, NULL); break;
	case bgm:mciSendString(_T("play bgm from 0 repeat"), NULL, 0, NULL); break;
	default:break;
	}
	if (music_on == false)
		stop_music(music_type);
}

void sound::pause_music(music music_type)
{
	switch (music_type)
	{
	case title:mciSendString(_T("pause title"), NULL, 0, NULL);break;
	case bgm:mciSendString(_T("pause bgm"), NULL, 0, NULL); break;
	default:break;
	}
}

void sound::resume_music(music music_type)
{
	switch (music_type)
	{
	case title:mciSendString(_T("resume title"), NULL, 0, NULL); break;
	case bgm:mciSendString(_T("resume bgm"), NULL, 0, NULL); break;
	default:break;
	}
}

void sound::stop_music(music music_type)
{
	switch (music_type)
	{
	case title:mciSendString(_T("stop title"), NULL, 0, NULL); break;
	case bgm:mciSendString(_T("stop bgm"), NULL, 0, NULL); break;
	default:break;
	}
}

void sound::close_all_music()
{
	mciSendString(_T("close ./sound/title.mp3"), NULL, 0, NULL);
	mciSendString(_T("close ./sound/bgm.mp3"), NULL, 0, NULL);
}

void sound::open_all_sound()
{
	mciSendString(_T("open ./sound/bomb.wav alias bomb"), NULL, 0, NULL);
	mciSendString(_T("open ./sound/camp_destroyed.wav alias camp_destroyed"), NULL, 0, NULL);
	mciSendString(_T("open ./sound/blast.wav alias blast"), NULL, 0, NULL);
	mciSendString(_T("open ./sound/player_blast.wav alias player_blast"), NULL, 0, NULL);
	mciSendString(_T("open ./sound/fire.wav alias fire"), NULL, 0, NULL);
	mciSendString(_T("open ./sound/pause.wav alias pause"), NULL, 0, NULL);
	mciSendString(_T("open ./sound/get_item.wav alias get_item"), NULL, 0, NULL);
	mciSendString(_T("open ./sound/build_item.wav alias build_item"), NULL, 0, NULL);
}

void sound::playsound(sound_effect sound_effect_type)
{
	if (sound_on == false)
		return;
	switch (sound_effect_type)
	{
	case bomb_sound:mciSendString(_T("play bomb from 0"), NULL, 0, NULL); break;
	case camp_destroyed_sound:mciSendString(_T("play camp_destroyed from 0"), NULL, 0, NULL); break;
	case fire_sound:mciSendString(_T("play fire from 0 to 1000"), NULL, 0, NULL); break;
	case blast_sound:mciSendString(_T("play blast from 0"), NULL, 0, NULL); break;
	case player_blast_sound:mciSendString(_T("play player_blast from 0"), NULL, 0, NULL); break;
	case pause_sound:mciSendString(_T("play pause from 0"), NULL, 0, NULL); break;
	case get_item_sound:mciSendString(_T("play get_item from 0"), NULL, 0, NULL); break;
	case build_item_sound:mciSendString(_T("play build_item from 0"), NULL, 0, NULL); break;
	default:break;
	}
}

void sound::close_all_sound()
{
	mciSendString(_T("close ./sound/bomb.wav alias bomb"), NULL, 0, NULL);
	mciSendString(_T("close ./sound/camp_destroyed.wav alias camp_destroyed"), NULL, 0, NULL);
	mciSendString(_T("close ./sound/blast.wav alias blast"), NULL, 0, NULL);
	mciSendString(_T("close ./sound/player_blast.wav alias player_blast"), NULL, 0, NULL);
	mciSendString(_T("close ./sound/fire.wav alias fire"), NULL, 0, NULL);
	mciSendString(_T("close ./sound/pause.wav alias pause"), NULL, 0, NULL);
	mciSendString(_T("close ./sound/get_item.wav alias get_item"), NULL, 0, NULL);
	mciSendString(_T("close ./sound/build_item.wav alias build_item"), NULL, 0, NULL);
}
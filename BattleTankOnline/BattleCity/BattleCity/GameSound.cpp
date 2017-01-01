#include "GameSound.h"


GameSound* GameSound::Instance = NULL;

GameSound::GameSound()
{
}

GameSound::~GameSound()
{
}

GameSound* GameSound::GetInstance()
{
	if (Instance == NULL)
	{
		Instance = new GameSound();
	}
	return Instance;
}
void GameSound::InitSound()
{
	Add(BREAKING_BLOCK_SOUND, "Sound/breaking_block.wav");
	Add(BUMP_SOUND, "Sound/bump.wav");
	Add(JUMPING_SOUND, "Sound/jumping.wav");
	Add(DEAD_SOUND, "Sound/dead.wav");
	Add(SQUISH_SOUND,"Sound/squish.wav");
	Add(ENTERING_NEW_LAND_SOUND, "Sound/entering_new_land.wav");
	Add(FLYING_SOUND, "Sound/flying.wav");
	Add(COIN_OBTAINED_SOUND, "Sound/coin_obtained.wav");
	Add(ITEM_OBTAINED_SOUND, "Sound/item_obtained.wav");
	Add(MUSHROOM_OBTAINED_SOUND, "Sound/mushroom_obtained.wav");
	Add(LEAF_OBTAINED_SOUND, "Sound/leaf_obtained.wav");
	Add(ONEUP_OBTAINED_SOUND, "Sound/oneup_obtained.wav");
	Add(PAUSING_SOUND, "Sound/pausing.wav");
	Add(PIPE_MAZE_SOUND, "Sound/pipe_maze.wav");
	Add(KICK_SOUND, "Sound/kick.wav");
	Add(OVER_WORLD_SOUND, "Sound/over_world.wav");
	Add(ENTERING_NEW_LAND_SOUND, "Sound/entering_new_land.wav");
	Add(WARP_SOUND, "Sound/warp.wav");
	Add(TIME_WARNING_SOUND, "Sound/time_warning.wav");
	Add(LEVEL_CLEAR_SOUND, "Sound/level_clear.wav");
	Add(SKID_SOUND, "Sound/skid.wav");
	Add(TAIL_WHIP_SOUND, "Sound/tail_whip.wav");

	Add(BOSS_FIRED_SOUND, "Sound/boss_fired.wav");
	Add(BOSS_CLEAR_SOUND, "Sound/boss_clear.wav");
	Add(END_GAME_SOUND, "Sound/end_game.wav");
}
void GameSound::Add(Sound sound,LPTSTR patch)
{
	CSound* SoundFile = LoadSound(patch);
	Instance->_listSounds.insert(std::pair<Sound, CSound*>(sound, SoundFile));
}
void GameSound::Play(Sound sound)
{
	CSound* SoundFile = GetSound(sound);
	if (SoundFile != NULL)
	{
		SoundFile->Reset();
		PlaySound(SoundFile);
	}
}
void GameSound::Stop(Sound sound)
{
	CSound* SoundFile = GetSound(sound);
	if (SoundFile != NULL)
	{
		SoundFile->Stop();
	}
}
void GameSound::LoopSound(Sound sound)
{
	CSound* SoundFile = GetSound(sound);
	if (SoundFile != NULL)
	{
		SoundFile->Reset();
		SoundFile->Play(0, DSBPLAY_LOOPING);
	}
}

CSound* GameSound::GetSound(Sound sound)
{
	std::map<Sound, CSound* >::iterator i = Instance->_listSounds.find(sound);
	if (i != Instance->_listSounds.end())
	{
		return (i)->second;
	}
	return NULL;
}
int GameSound::IsSoundPlaying(Sound sound)
{
	CSound* SoundFile = GetSound(sound);
	if (SoundFile != NULL)
	{
		return SoundFile->IsSoundPlaying();
	}
	return 0;
}
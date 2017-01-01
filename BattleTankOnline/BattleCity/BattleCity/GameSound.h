#ifndef GAME_SOUND_H
#define GAME_SOUND_H

#include "dxaudio.h"
#include <map>


enum Sound
{
	BREAKING_BLOCK_SOUND,
	BUMP_SOUND,
	JUMPING_SOUND,
	DEAD_SOUND,
	COIN_OBTAINED_SOUND,
	ITEM_OBTAINED_SOUND,
	LEAF_OBTAINED_SOUND,
	MUSHROOM_OBTAINED_SOUND,
	ONEUP_OBTAINED_SOUND,
	PAUSING_SOUND,
	PIPE_MAZE_SOUND,
	SQUISH_SOUND,
	FLYING_SOUND,
	KICK_SOUND,
	OVER_WORLD_SOUND,
	ENTERING_NEW_LAND_SOUND,
	WARP_SOUND,
	LEVEL_CLEAR_SOUND,
	TIME_WARNING_SOUND,
	SKID_SOUND,
	TAIL_WHIP_SOUND,
	BOSS_FIRED_SOUND,
	BOSS_CLEAR_SOUND,
	END_GAME_SOUND,
};


class GameSound
{
private:
	static GameSound* Instance;
	GameSound();
	~GameSound();
	std::map<Sound, CSound*> _listSounds;
public:
	static GameSound* GetInstance();
	void InitSound();
	void Add(Sound sound, LPTSTR patch);
	void Play(Sound sound);
	void Stop(Sound sound);
	void LoopSound(Sound sound);
	CSound * GetSound(Sound sound);
	int IsSoundPlaying(Sound sound);
};


#endif
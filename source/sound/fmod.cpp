#include "fmod.hpp"
#include "common.h"

FMOD::System    *fmod_system;
FMOD::Sound     *sound0, *sound1, *sound2, *sound3, *sound4;
FMOD::Channel   *channel0 = 0, *channel1 = 0, *channel2 = 0, *channel3 = 0, *channel4 = 0;
FMOD_RESULT      result;

unsigned int     version;
void            *extradriverdata = 0;

int fmod_init()
{
	Common_Init(&extradriverdata);

	result = FMOD::System_Create(&fmod_system);
	ERRCHECK(result);

	result = fmod_system->getVersion(&version);
	ERRCHECK(result);

	if (FMOD_VERSION > version)
	{
	Common_Fatal("FMOD lib version %08x doesn't match header version %08x", version, FMOD_VERSION);
	}

	result = fmod_system->init(100, FMOD_INIT_NORMAL, extradriverdata);
	ERRCHECK(result);

	result = fmod_system->createSound(Common_MediaPath("piano.0.186s.ogg"), FMOD_2D, 0, &sound0);
	ERRCHECK(result);
	result = sound0->setMode(FMOD_LOOP_NORMAL);
	ERRCHECK(result); 

	result = fmod_system->createSound(Common_MediaPath("piano.3.29s.mp3"), FMOD_3D, 0, &sound1);
	ERRCHECK(result);
	result = sound1->setMode(FMOD_LOOP_NORMAL);
	ERRCHECK(result); 

	result = fmod_system->createSound(Common_MediaPath("piano.4.7s.techno.wav"), FMOD_3D, 0, &sound2);
	ERRCHECK(result);
	result = sound2->setMode(FMOD_LOOP_NORMAL);
	ERRCHECK(result); 

	result = fmod_system->createSound(Common_MediaPath("piano.1.6s.wav"), FMOD_2D, 0, &sound3);
	ERRCHECK(result);
	result = sound3->setMode(FMOD_LOOP_NORMAL);
	ERRCHECK(result); 

	result = fmod_system->createSound(Common_MediaPath("piano.2.11s.wav"), FMOD_3D, 0, &sound4);
	ERRCHECK(result);
	result = sound4->setMode(FMOD_LOOP_NORMAL);
	ERRCHECK(result); 

	Common_Update();

	return 0;
}

void fmod_play0()
{
	channel0->setPaused(false); 
	/*result = channel1->setVolume(0.5f);
	ERRCHECK(result);*/
	result = fmod_system->playSound(sound0, 0, false, &channel0);
}

void fmod_pause0()
{
	channel0->setPaused(true); 
}

void fmod_play1()
{
	channel1->setPaused(false); 
	/*result = channel1->setVolume(0.5f);
	ERRCHECK(result);*/
	result = fmod_system->playSound(sound1, 0, false, &channel1);
}

void fmod_pause1()
{
	channel1->setPaused(true); 
}

void fmod_play2()
{

	channel2->setPaused(false);
	result = fmod_system->playSound(sound2, 0, false, &channel2);
}

void fmod_pause2()
{
	channel2->setPaused(true);
}

void fmod_play3()
{
	channel3->setPaused(false);
	result = fmod_system->playSound(sound3, 0, false, &channel3);
}

void fmod_pause3()
{
	channel3->setPaused(true);
}

void fmod_play4()
{
	channel4->setPaused(false);
	result = fmod_system->playSound(sound4, 0, false, &channel4);
}

void fmod_pause4()
{
	channel4->setPaused(true);
}





void _2del_fmod_play1()
{
	channel1->setPaused(false); 
	result = fmod_system->playSound(sound1, 0, false, &channel1);
	ERRCHECK(result);

	getchar();
	channel1->setPaused(true); 
}

void _2del_fmod_play2()
{
	channel2->setPaused(false); 
	result = fmod_system->playSound(sound2, 0, false, &channel2);
	ERRCHECK(result);

	getchar();
	channel2->setPaused(true);
}

void _2del_fmod_play3()
{
	channel3->setPaused(false); 
	result = fmod_system->playSound(sound3, 0, false, &channel3);
	ERRCHECK(result);

	getchar();
	channel3->setPaused(true);
}

void _2del_fmod_play4()
{
	channel4->setPaused(false); 
	result = fmod_system->playSound(sound4, 0, false, &channel4);
	ERRCHECK(result);

	getchar();
	channel4->setPaused(true);
}

int fmod_dispose()
{
	result = sound1->release();
	ERRCHECK(result);
	result = sound2->release();
	ERRCHECK(result);
	result = sound3->release();
	ERRCHECK(result);
	result = sound4->release();
	ERRCHECK(result);

	result = fmod_system->close();
	ERRCHECK(result);
	result = fmod_system->release();
	ERRCHECK(result);

	Common_Close();

	return 0;
}



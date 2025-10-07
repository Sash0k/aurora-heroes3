/*
 * CAudioBase.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"
#include "CAudioBase.h"

#include <SDL_mixer.h>

#ifdef VCMI_AURORAOS
#include <glib.h>
static void on_audio_resource_acquired(audioresource_t *, bool, void *);
#endif

int CAudioBase::initializationCounter = 0;
bool CAudioBase::initializeSuccess = false;

CAudioBase::CAudioBase()
{
	if(initializationCounter == 0)
	{
#if !defined(DISABLE_LIBAUDIORESOURCE)
		// initialize libaudioresource
		audio_resource = audioresource_init(
			AUDIO_RESOURCE_GAME,
			on_audio_resource_acquired,
			this);
		audioresource_acquire(audio_resource);

		logGlobal->info("Wait libaudioresource initialization ");
		while (!is_audio_resource_acquired) {
			g_main_context_iteration(NULL, false);
		}
		initializeSuccess = true;
#else
		if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
			logGlobal->error("Mix_OpenAudio error: %s", Mix_GetError());
		else
			initializeSuccess = true;
#endif
	}
	++initializationCounter;
}

bool CAudioBase::isInitialized() const
{
	return initializeSuccess;
}

#ifdef VCMI_AURORAOS
void on_audio_resource_acquired(audioresource_t *, bool, void *audiobase) {
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		logGlobal->error("Mix_OpenAudio error: %s", Mix_GetError());
		return;
	}
	logGlobal->info("libaudioresource was initialized.");
	((CAudioBase*)audiobase)->is_audio_resource_acquired = true;
}
#endif

CAudioBase::~CAudioBase()
{
	--initializationCounter;

	if(initializationCounter == 0 && initializeSuccess)
		Mix_CloseAudio();

	initializeSuccess = false;
}

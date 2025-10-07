/*
 * CAudioBase.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#pragma once

#if defined(VCMI_AURORAOS)
#include <audioresource/audioresource.h>
#endif

class CAudioBase : boost::noncopyable
{
	static int initializationCounter;
	static bool initializeSuccess;

protected:
	bool isInitialized() const;

	CAudioBase();
	~CAudioBase();

#ifdef VCMI_AURORAOS
	audioresource_t *audio_resource;
public:
	bool is_audio_resource_acquired = false;
#endif
};


/* tube_snd.h -- sound wrapper
 * Copyright (C) 1996-1998 Markus F.X.J. Oberhumer
 * For conditions of distribution and use, see copyright notice in kb.h
 */


/***********************************************************************
// Seal 1.03 for DOS / Win32 / Linux
************************************************************************/

#if defined(USE_SEAL)
#define HAVE_SOUND

#include <audio.h>
static AUDIOINFO info;
static AUDIOCAPS caps;
static LPAUDIOMODULE mod;
#define md_driver   (info.nDeviceId > 0)

int snd_init(const char *modfile, unsigned sample_rate)
{
	if (modfile == NULL || sample_rate < 5000)
		return -1;

    /* initialize audio library */
    if (AInitialize() != AUDIO_ERROR_NONE)
		return -1;

    /* open audio device */
    info.nDeviceId = AUDIO_DEVICE_MAPPER;
    info.wFormat = AUDIO_FORMAT_16BITS | AUDIO_FORMAT_STEREO;
    info.nSampleRate = sample_rate;

#if 0
    /* enable antialias dynamic filtering */
    info.wFormat |= AUDIO_FORMAT_FILTER;
#endif

    if (AOpenAudio(&info) != AUDIO_ERROR_NONE)
		return -1;

    /* get device information */
    if (AGetAudioDevCaps(info.nDeviceId, &caps) != AUDIO_ERROR_NONE)
		return -1;

    /* load module file */
    if (ALoadModuleFile((char *)modfile, &mod, 0) != 0 || mod == 0)
		return -1;

    /* open voices and play module */
    if (AOpenVoices(mod->nTracks) != AUDIO_ERROR_NONE)
		return -1;
	if (APlayModule(mod) != AUDIO_ERROR_NONE)
		return -1;

	printf("SEAL: using %s for %d bit %s sound at %u Hz\n",
			caps.szProductName,
			(info.wFormat & AUDIO_FORMAT_16BITS) ? 16 : 8,
			(info.wFormat & AUDIO_FORMAT_STEREO) ? "stereo" : "mono",
    		info.nSampleRate);
	printf("SEAL: song `%s', %u voices, %u patterns, %u orders\n",
			mod->szModuleName, mod->nTracks, mod->nPatterns, mod->nOrders);

	return 0;
}


void snd_exit(void)
{
	/* stop module and close voices */
	AStopModule();
	ACloseVoices();
	/* release module file */
	if (mod)
		AFreeModuleFile(mod);
	mod = 0;
	/* close audio device */
	ACloseAudio();
}


void snd_update(void)
{
	BOOL stopped;

	/* check if the module is stopped */
	AGetModuleStatus(&stopped);
	if (stopped)
		APlayModule(mod);
	else
		AUpdateAudio(); 	/* update audio system */
}


#endif


/***********************************************************************
//
************************************************************************/

void exit_snd(void)
{
	if (in_sound)
	{
		in_sound = 0;
#if defined(HAVE_SOUND)
		snd_exit();
#endif
	}
}


/*
vi:ts=4
*/


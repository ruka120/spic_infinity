#ifndef INCLUDED_AUDIO
#define INCLUDED_AUDIO
#define MUSIC_VOLUME    (0.2f)
enum
{
	title02=0,
	play02,
	clear01,
	over01,
	Music_Max
};
void audio_init();
void audio_uninit();
#endif // !INCLUDED_AUDIO
#ifndef INCLUDED_AUDIO
#define INCLUDED_AUDIO
#define MUSIC_VOLUME    (0.2f)
enum
{
	bgm1=0,
	Music_Max
};
void audio_init();
void audio_uninit();
#endif // !INCLUDED_AUDIO
#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <iostream>
#include "miniaudio.h"
#include <cstring>


static void AudioCallbackWrap(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);

struct TimeStruct
{
	double audio_time = 0.0;
};

class AudioManager
{
private:
	double(*m_userFunction)(double);
	TimeStruct time_struct;

	ma_result result;
	ma_decoder decoder;
	ma_device_config deviceConfig;
	
	ma_device device;

public:
	AudioManager();
	static AudioManager* s_Instance;
	double GetTime();
	void SetUserFunction(double(*func)(double));

	void AudioCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);

	void Clear();
	
};

#endif // !AUDIOMANAGER_H

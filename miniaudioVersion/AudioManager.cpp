#include "AudioManager.h"

AudioManager* AudioManager::s_Instance = nullptr;

static void AudioCallbackWrap(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    AudioManager::s_Instance->AudioCallback(pDevice, pOutput, pInput, frameCount);
    pDevice->pUserData;
}

AudioManager::AudioManager()
{
    s_Instance = this;
}

void AudioManager::AudioCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    TimeStruct* time_struct = (TimeStruct*)pDevice->pUserData;

    if (frameCount == 0)
        return;

    int audioIndex;

    size_t streamLen = frameCount * 1 * sizeof(float);

    memset(pOutput, 0, streamLen);
    float* stream_float = (float*)pOutput;

    for(audioIndex = 0;audioIndex < (streamLen /sizeof(float)); audioIndex++)
    {
        stream_float[audioIndex] = (float)(m_userFunction(time_struct->audio_time + (double)audioIndex / (double)44100)); //Hier nahher vielliecht probleme
    }

    time_struct->audio_time += (double)audioIndex / 44100.0;
    pDevice->pUserData;
    
}

double AudioManager::GetTime()
{
    return time_struct.audio_time;
}

void AudioManager::SetUserFunction(double(*func)(double))
{
	m_userFunction = func;

    deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format = ma_format_f32;
    deviceConfig.playback.channels = 1;
    deviceConfig.sampleRate = 48000;
    deviceConfig.periodSizeInFrames = 1024;
   
    deviceConfig.dataCallback = AudioCallbackWrap;
    deviceConfig.pUserData = &time_struct;

    if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) 
    {
        std::cout << "Failed to open playback device.\n" << std::endl; 
    }

    if (ma_device_start(&device) != MA_SUCCESS) 
    {
        std::cout << "Failed to start playback device" << std::endl;
        ma_device_uninit(&device);
        ma_decoder_uninit(&decoder);
    }
}

void AudioManager::Clear()
{
    ma_device_uninit(&device);
    ma_decoder_uninit(&decoder);
}
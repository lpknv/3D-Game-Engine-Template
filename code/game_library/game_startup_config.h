struct game_startup_config
{
    uint32_t SoundSamplesPerSecond;
    uint32_t SoundBytesPerSample;
    uint32_t SoundBufferSize;
};

#define GAME_GET_STARTUP_CONFIG(name) game_startup_config name()
typedef GAME_GET_STARTUP_CONFIG(game_get_startup_config);

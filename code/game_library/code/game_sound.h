struct game_sound_output_buffer 
{
    uint32_t SamplesPerSecond;
    uint32_t SamplesToWriteThisFrame;
    uint32_t SamplesWrittenThisFrame;
    int16_t *Samples;
};

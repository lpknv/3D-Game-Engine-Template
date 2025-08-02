
struct game_texture
{
    void *Data;
    uint32_t Width;
    uint32_t Height;
};

struct game_texture_buffer
{
    game_texture *Textures;
    uint32_t Count;
    uint32_t Max;
};

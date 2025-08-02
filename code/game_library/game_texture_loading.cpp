
struct game_texture_description
{
    uint32_t Width;
    uint32_t Height;
    char *Filename;
};

internal int32_t
LoadTexture(game_memory *Memory, memory_arena *Arena, thread_context *Thread,
            game_texture *Texture, game_texture_description Description)
{
    int32_t LoadedTexture = false;

#if WINDOWS
    read_file_result Result = PlatformReadPNGFile(Description.Filename);
#elif MACOS
    read_file_result Result = Memory->PlatformReadPNGFile(Description.Filename);
#endif

    if (Result.ContentsSize > 0)
    {
        Texture->Width = Description.Width;
        Texture->Height = Description.Height;
        uint32_t PixelCount = Texture->Width*Texture->Height;

        Texture->Data = PushArray(Arena, PixelCount, uint32_t);
        uint8_t *Src = (uint8_t *)Result.Contents;
        uint8_t *Dest = (uint8_t *)Texture->Data;

        for(uint32_t ByteIndex = 0;
            ByteIndex < Result.ContentsSize;
            ByteIndex++)
        {
            *Dest++ = *Src++;
        }

        LoadedTexture = true;
    } 

    Memory->PlatformFreeFileMemory(Thread, Result.Contents);

    return LoadedTexture;
}

extern "C"
GAME_LOAD_TEXTURES(GameLoadTextures)
{
    game_state *GameState = (game_state *)Memory->PermanentStorage;
    memory_arena *ScratchArena = &GameState->ScratchArena;
    memory_partition *SecondaryPartition = &Memory->TransientPartition.SecondaryGeneric;

    InitializeArena(ScratchArena, SecondaryPartition->Size, SecondaryPartition->Data);
    TextureBuffer->Textures = PushArray(ScratchArena, TextureBuffer->Max, game_texture);

    thread_context Thread = {};
    
    game_texture_description Descriptions[2];
    Descriptions[0].Width = 942;
    Descriptions[0].Height = 942;
    Descriptions[0].Filename = "game_character.png";

    Descriptions[1].Width = 16;
    Descriptions[1].Height = 16;
    Descriptions[1].Filename = "grid_surface.png";

    for (uint32_t Index = 0;
         Index < TextureBuffer->Max;
         Index++)
    {
        if (LoadTexture(Memory, ScratchArena, &Thread, 
            &TextureBuffer->Textures[Index], Descriptions[Index]))
        {
            TextureBuffer->Count++;
        }
    }
}

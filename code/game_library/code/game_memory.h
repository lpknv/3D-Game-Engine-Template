
typedef size_t size_t;

struct memory_arena
{
    size_t Size;
    uint8_t* Base;
    size_t Used; 
};

internal void
InitializeArena(memory_arena *Arena, size_t Size, uint8_t* Base)
{
    Arena->Size = Size;
    Arena->Base = Base;
    Arena->Used = 0; 
}

#define PushStruct(Arena, type) (type *)PushSize_(Arena, sizeof(type)) 
#define PushArray(Arena, Count, type) (type *)PushSize_(Arena, (Count)*sizeof(type)) 

void *
PushSize_(memory_arena *Arena, size_t Size)
{
    Assert((Arena->Used + Size) <= Arena->Size);
    void *Result = Arena->Base + Arena->Used;
    Arena->Used += Size;
    return (Result);
}


struct memory_partition
{
    uint64_t Size;
    uint8_t* Data; 
};

struct game_permanent_storage_partition
{
    memory_partition Sound;
};

struct game_transient_storage_partition
{
    memory_partition FileReadResult;
    memory_partition SecondaryGeneric;
};

struct game_memory 
{
    int32_t IsInitialized;

    uint64_t PermanentStorageSize;
    void *PermanentStorage;

    uint64_t TransientStorageSize;
    void *TransientStorage;
    
    platform_read_entire_file *PlatformReadEntireFile;
    platform_free_file_memory *PlatformFreeFileMemory;
    platform_read_png_file *PlatformReadPNGFile;
    platform_write_entire_file *PlatformWriteEntireFile;
    platform_log_message *PlatformLogMessage;

    game_permanent_storage_partition PermanentPartition;
    game_transient_storage_partition TransientPartition;
};

void 
ClearMemoryPartition(memory_partition *Partition)
{
    uint8_t* Byte = (uint8_t *)Partition->Data;
    for (uint32_t Index = 0; Index < Partition->Size; 
         Index++)
    {
        *Byte++ = 0;
    }
}

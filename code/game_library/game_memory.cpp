
extern "C"
GAME_CLEAR_MEMORY_ARENA(GameClearMemoryArena)
{
    Assert(sizeof(game_state) <= Memory->PermanentStorageSize);
    game_state *GameState = (game_state *)Memory->PermanentStorage;
    ClearMemoryPartition(&Memory->TransientPartition.SecondaryGeneric);
    GameState->ScratchArena = {};
}

extern "C"
GAME_SETUP_MEMORY_PARTITIONS(GameSetupMemoryPartitions)
{
    uint64_t SecondaryPartitionSize = Megabytes(64);
    Memory->TransientPartition.SecondaryGeneric.Size = SecondaryPartitionSize;
    Memory->TransientPartition.SecondaryGeneric.Data = 
        (uint8_t *)Memory->TransientStorage + SecondaryPartitionSize;
}

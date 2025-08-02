
struct read_file_result 
{
    void *Contents;
    uint64_t ContentsSize;
    char *Filename;
};

#define PLATFORM_READ_PNG_FILE(name) read_file_result name(char *Filename)
typedef PLATFORM_READ_PNG_FILE(platform_read_png_file);

#define PLATFORM_READ_ENTIRE_FILE(name) read_file_result name(thread_context *Thread, char *Filename)
typedef PLATFORM_READ_ENTIRE_FILE(platform_read_entire_file);

#define PLATFORM_FREE_FILE_MEMORY(name) void name(thread_context *Thread, void *Memory)
typedef PLATFORM_FREE_FILE_MEMORY(platform_free_file_memory);

#define PLATFORM_WRITE_ENTIRE_FILE(name) int32_t name(thread_context *Thread, char *Filename, uint64_t FileSize, void *Memory)
typedef PLATFORM_WRITE_ENTIRE_FILE(platform_write_entire_file);

#define PLATFORM_LOG_MESSAGE(name) void name(char *Message, uint32_t Count) 
typedef PLATFORM_LOG_MESSAGE(platform_log_message);

#define PLATFORM_QUIT_GAME(name) void name()
typedef PLATFORM_QUIT_GAME(platform_quit_game);

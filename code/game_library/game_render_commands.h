
#if WINDOWS
struct game_constants
{
    matrix Transform;
    matrix View;
    matrix Projection;
    vector_float_3 LightVector;
};

struct game_flat_color_vertex
{
    float Position[3];
    float Normal[3];
    float Color[3];
};

// TODO: (Ted)  See if there is a way to simplify this on Windows
struct game_texture_vertex
{
    float Position[3];
    float Normal[3];
    float UV[2];
};

#elif MACOS
struct game_constants
{
    matrix_float4x4 View;
    matrix_float4x4 Projection;
    vector_float3 LightVector;
};

struct instance_uniforms
{
    matrix_float4x4 Transform;
};

struct game_flat_color_vertex
{
    vector_float3 Position;
    vector_float3 Normal;
    vector_float3 Color;
};

struct game_texture_vertex
{
    vector_float3 Position;
    vector_float3 Normal;
    vector_float2 UV;
};

#endif


#define MAX_MODELS  3

struct model_range
{
    uint32_t StartVertex;
    uint32_t VertexCount;
};

struct model_range_indexed
{
    uint32_t StartIndex;
    uint32_t IndexCount;
};

struct game_vertex_buffer
{
    void *Vertices;
    uint32_t VertexCount;

    model_range ModelRanges[MAX_MODELS];
    uint32_t ModelCount;
};

struct game_indexed_vertex_buffer
{
    void *Vertices;
    uint32_t VertexCount;

    void *Indices;
    uint32_t IndexCount;

    // TODO: (Ted)  Clearly this will need some notion of multiple models.
    float ModelHeight;
};

struct clear_color
{
    float RGBA[4];
};

struct mesh_instance
{
#if WINDOWS
    game_constants Constants;
#elif MACOS
    instance_uniforms Uniforms;
#endif
    uint32_t ModelIndex;
};

struct mesh_instance_buffer
{
    mesh_instance *Meshes;
    uint32_t MeshCount;
    uint32_t MeshMax;
};

struct push_buffer
{
    vector_float_3 Translations[CUBE_MAP_SIZE];
    uint32_t DrawCount;
};

struct game_render_commands
{

#if MACOS
    uint32_t FrameIndex;
    float ScreenScaleFactor; 
    game_constants Constants;
#endif

    int32_t ViewportWidth;
    int32_t ViewportHeight;
    clear_color ClearColor;

    game_vertex_buffer FlatColorVertexBuffer;
    game_vertex_buffer TextureVertexBuffer;
    game_indexed_vertex_buffer LoadedModelVertexBuffer;

    mesh_instance_buffer FlatColorMeshInstances;
    mesh_instance_buffer TexturedMeshInstances;
    mesh_instance_buffer LoadedModelMeshInstances;

    push_buffer ColoredCubePushBuffer;
    push_buffer TexturedCubePushBuffer;
};

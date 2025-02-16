// #define IMPORT(module, name) __attribute__((import_module(module), import_name(name)))

// IMPORT("env", "print_line")
// double print_line(char *str);

float sinf(float x)
{
    const float A = -0.16666667f; // -1/3!
    const float B = 0.00833333f;  //  1/5!
    const float C = -0.00019841f; // -1/7!

    const float PI = 3.1415927f;
    const float TWO_PI = 6.2831855f;
    const float INV_TWO_PI = 1.0f / TWO_PI;

    int k = (int)(x * INV_TWO_PI);
    x -= k * TWO_PI;

    if (x > PI)
    {
        x -= TWO_PI;
    }
    else if (x < -PI)
    {
        x += TWO_PI;
    }

    if (x > PI / 2)
    {
        x = PI - x;
    }
    else if (x < -PI / 2)
    {
        x = -PI - x;
    }

    float x2 = x * x;
    return x * (1.0f + x2 * (A + x2 * (B + x2 * C)));
}

int clamp(int value, int min, int max)
{
    if (value < min)
    {
        return min;
    }
    if (value > max)
    {
        return max;
    }
    return value;
}

typedef struct
{
    void *memory;
    unsigned int offset;
} Arena;

Arena frameArena = {};

void setup_frame_arena(void *memory)
{
    frameArena.memory = memory;
}

void *push_size(Arena *arena, unsigned int size)
{
    void *result = (char *)arena->memory + arena->offset;
    arena->offset += size;
    return result;
}

typedef struct
{
    int x;
    int y;
    int width;
    int height;
    int color;
} Rect;

void draw_rect(Arena *arena, Rect rect)
{
    Rect *rect_ptr = (Rect *)push_size(arena, sizeof(Rect));
    *rect_ptr = rect;
}

int calculate_color(int cur_time, float phase_shift)
{
    float s = sinf((cur_time / 1000.0f) + phase_shift);
    float t = (s + 1.0f) / 2.0f;
    int red = (int)(t * 255.0f);
    int green = (int)((1.0f - t) * 255.0f);
    int blue = (phase_shift == 0) ? (int)(t * 255.0f) : 255;
    return (red << 16) | (green << 8) | blue;
}

void on_render(int canvas_width, int canvas_height, int cur_time)
{
    frameArena.offset = 0;

    float t = (sinf(cur_time / 1000.0f) + 1.0f) / 2.0f;
    int column_width = clamp(canvas_width * t, 0, canvas_width);

    Rect column1 = {0, 0, column_width, canvas_height, calculate_color(cur_time, 0)};
    draw_rect(&frameArena, column1);

    Rect column2 = {column_width, 0, canvas_width - column_width, canvas_height, calculate_color(cur_time, 1.5708f)};
    draw_rect(&frameArena, column2);
}

#define IMPORT(module, name) __attribute__((import_module(module), import_name(name)))

IMPORT("env", "fill_rect")
void fill_rect(int x, int y, int width, int height, int color);

IMPORT("env", "sinf")
double sinf(double x);

IMPORT("env", "cosf")
double cosf(double x);

IMPORT("env", "print_line")
double print_line(char *str);

int layout[8];
int column_colors[2] = {0xFF0000, 0x00FF00};

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

void on_render(int canvas_width, int canvas_height, int dt)
{
    double t = (sinf(dt / 1000.0) + 1.0) / 2.0;
    int column_width = clamp(canvas_width * t, 0, canvas_width);

    layout[0] = 0;             // x position of first column
    layout[1] = 0;             // y position of first column
    layout[2] = column_width;  // width of first column
    layout[3] = canvas_height; // height of first column

    layout[4] = column_width;                // x position of second column
    layout[5] = 0;                           // y position of second column
    layout[6] = canvas_width - column_width; // width of second column
    layout[7] = canvas_height;               // height of second column

    double s1 = sinf(dt / 1000.0);
    double t1 = (s1 + 1.0) / 2.0;
    int red1 = (int)((1.0 - t1) * 255.0);
    int green1 = (int)((1.0 - t1) * 255.0);
    int blue1 = (int)(t1 * 255.0);
    column_colors[0] = (red1 << 16) | (green1 << 8) | blue1;

    double s2 = sinf((dt / 1000.0) + 1.5708);
    double t2 = (s2 + 1.0) / 2.0;
    int red2 = (int)(t2 * 255.0);
    int green2 = (int)((1.0 - t2) * 255.0);
    int blue2 = 255;
    column_colors[1] = (red2 << 16) | (green2 << 8) | blue2;

    fill_rect(layout[0], layout[1], layout[2], layout[3], column_colors[0]);
    fill_rect(layout[4], layout[5], layout[6], layout[7], column_colors[1]);
}

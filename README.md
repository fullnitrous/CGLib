# CGlib

This is a chart / graph generation library written in C only using the standard C library. The program takes as input values filled in various structs and outputs .svg files. The structs define everything about the chart that is going to be generated.

Below are all the structs for each type of graph which currently are the following.

* Bar charts
  * vertical
  * horizontal
* Percentage charts
  * Pie charts
  * Doughnut charts
* Line charts
  * Continous line
  * Dots

```c
struct theme_data
{
  uint8_t start_color_rgb[3];
  uint8_t stop_color_rgb[3];
  uint8_t out_color_rgb[3];
  float   percentage;
};

struct general_data
{
  char* file_name;
  int   stroke_width;
  float margin;
  float viewport_x; 
  float viewport_y;
  int   font_size;
};

struct axel_data
{
  uint8_t axel_rgb[3];
  uint8_t axel_lines_rgb[3];
  int     n_measure_points;
  float   w[2];
  float   h[2];
  uint8_t vertical_lines;
  uint8_t horizontal_lines;
  float   x_axel_text_angle;
  uint8_t y_axel_text_right;
  uint8_t numbered_x;
  uint8_t numbered_y;
  float axel_number_offset;
};

struct point
{
  float x;
  float y;
} point;

struct line
{
  struct point*  points;
  int     graph_type;
  int     n_points;
  char*   name;
  uint8_t stroke_rgb[3];
};

struct graph_data
{
  struct line*   lines;
  int     n_lines;
  struct general_data* general;
  struct axel_data* axel_data;
};

struct pie_slice
{
  float percentage;
  char* name;
};

struct pie_data
{
  struct axel_data* axel_data;
  struct general_data* general;
  struct pie_slice* slices;
  struct theme_data* theme;
  int               n_slices;
  char* doughnut_header;
  char* doughnut_sub_header;
};

struct bar
{
  float value;
  char* name;
};

struct bar_data
{
  struct general_data* general;
  struct theme_data* theme;
  struct axel_data* axel_data;
  struct bar*  bars;
  int   n_bars;
  float spacing;
};
```
*Code snipped taken from `src/cgraphlib.h`*

The following pictures are snapshots of the various graphs configured to look like they do in the main.c file.

![line chart](./bin/graph.svg)
*line chart*

![pie chart](./bin/pie.svg)
*pie chart*

![doughnut chart](./bin/doughnut.svg)
*doughnut chart*

![vertical bar chart](./bin/vbar.svg)
*vertical bar chart*

![horizontal bar chart](./bin/hbar.svg)
*horizontal bar chart*
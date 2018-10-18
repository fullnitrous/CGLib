#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>
#include <math.h>
#include <time.h>


#ifndef C_GRAPH_LIB
  #define C_GRAPH_LIB

  #define PI 3.14159265

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
    float   axel_number_offset;
  };

  struct point
  {
    float x;
    float y;
  };

  struct line
  {
    struct point*  points;
    int            graph_type;
    int            n_points;
    char*          name;
    uint8_t        stroke_rgb[3];
  };

  struct graph_data
  {
    struct line*         lines;
    int                  n_lines;
    struct general_data* general;
    struct axel_data*    axel_data;
  };

  struct pie_slice
  {
    float percentage;
    char* name;
  };
  
  struct pie_data
  {
    struct axel_data*    axel_data;
    struct general_data* general;
    struct pie_slice*    slices;
    struct theme_data*   theme;
    int                  n_slices;
    char*                doughnut_header;
    char*                doughnut_sub_header;
  };

  struct bar
  {
    float value;
    char* name;
  };

  struct bar_data
  {
    struct general_data* general;
    struct theme_data*   theme;
    struct axel_data*    axel_data;
    struct bar*          bars;
    int                  n_bars;
    float                spacing;
  };

  void graph   (struct graph_data* gd);
  void pie     (struct pie_data*   pd);
  void vbar    (struct bar_data*   bd);
  void hbar    (struct bar_data*   bd);
  void doughnut(struct pie_data*   pd);
#endif
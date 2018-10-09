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

  struct general_data
  {
    char* file_name;
    int   stroke_width;
    float margin;
    float viewport_x; 
    float viewport_y;
  };

  struct axel_data
  {
    uint8_t axel_rgb[3];
    int     n_measure_points;
    float   w[2];
    float   h[2];
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

  typedef struct pieSlice
  {
    float percentage;
  } PieSlice;
  
  typedef struct pieData
  {
    PieSlice* slices;
    int       nSlices;
  } PieData;

  typedef struct bar
  {
    float value;
    char* name;
  } Bar;

  typedef struct BarData
  {
    Bar*      bars;
    int       nBars;
    float     standardRatio;
  } BarData;

  void graph(struct graph_data* gd);
  void pie  (PieData*     pd);
  void bar  (BarData*     bd);
#endif
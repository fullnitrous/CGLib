#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>
#include <math.h>
#include <time.h>


#ifndef SVG_GRAPH_LIB
  #define SVG_GRAPH_LIB

  #define PI 3.14159265

  typedef struct point
  {
    float x;
    float y;
  } Point;

  typedef struct line
  {
    Point*  line;
    int     graphType;
    int     points;
    char*   name;
    uint8_t strokeRGBA[3];
  } Line;

  typedef struct graphData
  {
    Line*   lines;
    char*   fileName;
    int     nLines;
    int     strokeWidth;
    float   viewportX; 
    float   viewportY;
    float   xInterval;
    float   yInterval;
    float   quadPercent[2];
    uint8_t bgRGBA[3];
    uint8_t axelRGBA[3];
    float   margin;
  } GraphData;

  typedef struct pieSlice
  {
    float percentage;
  } PieSlice;
  
  typedef struct pieData
  {
    PieSlice* slices;
    int       nSlices;
    char*     fileName;
    int       strokeWidth;
    float     viewportX; 
    float     viewportY;
    uint8_t   bgRGBA[3];
    float     margin;
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
    char*     fileName;
    int       strokeWidth;
    float     viewportX; 
    float     viewportY;
    float     standardRatio;
    float     minW;
    float     maxW;
    float     yInterval;
    float     yMax;
    uint8_t   bgRGBA[3];
    uint8_t   axelRGBA[3];
    float     margin;
  } BarData;

  void graph(GraphData* gd);
  void pie(PieData*     pd);
  void bar(BarData*     bd);
#endif
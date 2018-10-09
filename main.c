#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/cgraphlib.h"

int main(void)
{
  //add color to axels

  struct general_data* general = malloc(sizeof(struct general_data));
  general->stroke_width = 1;
  general->margin = 20;
  general->viewport_x = 640;
  general->viewport_y = 360;

  struct axel_data* axel = malloc(sizeof(struct axel_data));
  axel->axel_rgb[0] = 0;
  axel->axel_rgb[1] = 0;
  axel->axel_rgb[2] = 0;
  
  axel->n_measure_points = 10;

  axel->w[0] = 0;
  axel->w[1] = 50;
  axel->h[0] = -100;
  axel->h[1] = 200;

  struct graph_data* gp = malloc(sizeof(struct graph_data));
  gp->general = general;
  gp->axel_data = axel;
  general->file_name = malloc(sizeof(char) * 14);
  strcpy(general->file_name, "bin/graph.svg\0");

  gp->n_lines = 2;
  gp->lines = malloc(sizeof(struct line) * 2);

  gp->lines[0].n_points = 80;
  gp->lines[1].n_points = 80;

  gp->lines[0].graph_type = 0;
  gp->lines[1].graph_type = 1;

  gp->lines[0].stroke_rgb[0] = gp->lines[0].stroke_rgb[1] = gp->lines[0].stroke_rgb[2] =
  gp->lines[1].stroke_rgb[0] = gp->lines[1].stroke_rgb[1] = gp->lines[1].stroke_rgb[2] = 0;

  gp->lines[0].points = malloc(sizeof(struct point) * gp->lines[0].n_points);
  gp->lines[1].points = malloc(sizeof(struct point) * gp->lines[1].n_points);

  float count = -20;
  for(int i = -40; i < 40; i++)
  {
    count += 0.5;
    gp->lines[0].points[i + 40].x = count;
    gp->lines[0].points[i + 40].y = count * count;
  }
  count = -20;
  for(int i = -40; i < 40; i++)
  {
    count += 0.5;
    gp->lines[1].points[i + 40].x = count;
    gp->lines[1].points[i + 40].y = -count * count;
  }

  graph(gp);
  //maybe care to free later


















  /*


  PieData* pd = malloc(sizeof(PieData));
  pd->fileName = malloc(sizeof(char) * 12);
  strcpy(pd->fileName, "bin/pie.svg");
  pd->margin = 20;
  pd->viewportX = 500.0;
  pd->viewportY = 300.0;
  pd->strokeWidth = 10;
  pd->nSlices = 4;
  pd->slices = malloc(sizeof(PieSlice) * pd->nSlices);
  pd->slices[0].percentage = 0.25;
  pd->slices[1].percentage = 0.25;
  pd->slices[2].percentage = 0.25;
  pd->slices[3].percentage = 0.25;
  pie(pd);
  free(pd);













  BarData* bd = malloc(sizeof(BarData));
  bd->fileName = malloc(sizeof(char) * 12);
  strcpy(bd->fileName, "bin/bar.svg");

  bd->margin = 20;

  bd->viewportX = 500.0;
  bd->viewportY = 500.0;

  bd->yMax = 500;

  bd->yInterval = 1;

  bd->axelRGBA[0] = 60;
  bd->axelRGBA[1] = 60;
  bd->axelRGBA[2] = 60;  

  bd->strokeWidth = 2;

  bd->nBars = 4;
  bd->bars = malloc(sizeof(Bar) * bd->nBars);
  
  bd->bars[0].value = 500.0;
  bd->bars[0].name = malloc(4);
  strcpy(bd->bars[0].name, "one");

  bd->bars[1].value = 400.0;
  bd->bars[1].name = malloc(4);
  strcpy(bd->bars[1].name, "two");

  bd->bars[2].value = 300.0;
  bd->bars[2].name = malloc(6);
  strcpy(bd->bars[2].name, "three");

  bd->bars[3].value = 200.0;
  bd->bars[3].name = malloc(4);
  strcpy(bd->bars[3].name, "one");
  
  bd->standardRatio = (1.0 / 3.0);

  bar(bd);

  free(bd);
  */
  

  printf("done...\n");
  return 0;
}
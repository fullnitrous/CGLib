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

  struct theme_data* theme = malloc(sizeof(struct theme_data));
  theme->start_color_rgb[0] = 134;
  theme->start_color_rgb[1] = 179;
  theme->start_color_rgb[2] = 249;

  theme->stop_color_rgb[0] = 0;
  theme->stop_color_rgb[0] = 87;
  theme->stop_color_rgb[0] = 224;




  /* normal line graph */
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







  /* pie chart */
  struct pie_data* pd = malloc(sizeof(struct pie_data));
  free(general->file_name);
  general->file_name = malloc(sizeof(char) * 12);
  strcpy(general->file_name, "bin/pie.svg\0");
  pd->general = general;
  pd->theme = theme;
  pd->n_slices = 5;
  pd->slices = malloc(sizeof(struct pie_slice) * pd->n_slices);

  for(int i = 0; i < pd->n_slices; i++)
  {
    pd->slices[i].percentage = 0.2;
    pd->slices[i].name = malloc(6);
    strcpy(pd->slices[i].name, "label\0");
  }

  pie(pd);



  //maybe care to free later

  printf("done...\n");
  return 0;
}
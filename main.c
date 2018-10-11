#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/cgraphlib.h"

int main(void)
{
  //add color to axels

  struct general_data* general = malloc(sizeof(struct general_data));
  general->stroke_width = 1;
  general->margin = 100;
  general->viewport_x = 640;
  general->viewport_y = 360;
  general->font_size = 12;

  struct axel_data* axel = malloc(sizeof(struct axel_data));
  axel->axel_rgb[0] = 100;
  axel->axel_rgb[1] = 100;
  axel->axel_rgb[2] = 100;

  axel->axel_lines_rgb[0] = 220;
  axel->axel_lines_rgb[1] = 220;
  axel->axel_lines_rgb[2] = 220;

  axel->horizontal_lines = 1;
  axel->vertical_lines = 1;
  axel->numbered_x = 1;
  axel->numbered_y = 1;

  axel->x_axel_text_angle = -30.0;

  axel->axel_number_offset = 5.0;
  
  axel->n_measure_points = 10;

  axel->w[0] = -25;
  axel->w[1] = 25;
  axel->h[0] = -100;
  axel->h[1] = 200;

  struct theme_data* theme = malloc(sizeof(struct theme_data));
  theme->stop_color_rgb[0] = 65;
  theme->stop_color_rgb[1] = 130;
  theme->stop_color_rgb[2] = 234;

  theme->start_color_rgb[0] = 234;
  theme->start_color_rgb[1] = 99;
  theme->start_color_rgb[2] = 175;




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
    gp->lines[0].points[i + 40].y = (2 * count * count * count) - (3 * count * count);
  }
  count = -20;
  for(int i = -40; i < 40; i++)
  {
    count += 0.5;
    gp->lines[1].points[i + 40].x = count;
    gp->lines[1].points[i + 40].y = -count * count * count;
  }
  graph(gp);







  /* pie chart */
  struct pie_data* pd = malloc(sizeof(struct pie_data));
  free(general->file_name);
  general->file_name = malloc(sizeof(char) * 12);
  strcpy(general->file_name, "bin/pie.svg\0");
  general->margin = 20.0;
  pd->general = general;
  pd->axel_data = axel;
  pd->theme = theme;
  pd->n_slices = 20;
  pd->slices = malloc(sizeof(struct pie_slice) * pd->n_slices);

  for(int i = 0; i < pd->n_slices; i++)
  {
    pd->slices[i].percentage = 0.05;
    pd->slices[i].name = malloc(6);
    strcpy(pd->slices[i].name, "label\0");
  }

  pie(pd);



  /* bar chart */
  struct bar_data* bd = malloc(sizeof(struct bar_data));
  strcpy(general->file_name, "bin/bar.svg\0");
  bd->general = general;
  general->margin = 100;
  bd->theme = theme;
  bd->axel_data = axel;
  bd->n_bars =  6;
  bd->spacing = 10;
  axel->numbered_x = 0;
  bd->bars = malloc(sizeof(struct bar) * bd->n_bars);

  axel->w[0] = 0;
  axel->w[1] = 50;
  axel->h[0] = -100;
  axel->h[1] = 100;

  for(int i = 0; i < bd->n_bars; i++)
  {
    bd->bars[i].value = 50.0 - i * 25.0;
    bd->bars[i].name = malloc(6);
    strcpy(bd->bars[i].name, "label\0");
  }

  bar(bd);

  //maybe care to free later

  printf("done...\n");
  return 0;
}
#include "cgraphlib.h"
#include "cgraphlib-other.h"

void hbar(struct bar_data* bd)
{
  char* ret;

  FILE* file = fopen(bd->general->file_name, "wb");

  print_top_header(file, bd->general);

  float y_axel_x_offset = (bd->axel_data->h[0] < 0) ? 
                          bd->general->viewport_y * (bd->axel_data->h[0] / (bd->axel_data->h[0] - bd->axel_data->h[1])) : 0;

  float x_axel_y_offset = (bd->axel_data->w[0] < 0) ?
                          bd->general->viewport_x * (bd->axel_data->w[0] / (bd->axel_data->w[0] - bd->axel_data->w[1])) : 0;

  draw_axis_horizontals(file, x_axel_y_offset, y_axel_x_offset, bd->general, bd->axel_data);

  float bar_height = (bd->general->viewport_y - bd->spacing * (bd->n_bars - 1))
                    / bd->n_bars;

  float bar_width;

  float width_offset;
  float middle;

  float x;
  float y;

  int yeet = 1;

  ret = sn_instant("dominant-baseline=\"middle\" font-size=\"%d\"", bd->general->font_size);
  
  fprintf(file, svg_custom_group, ret);

  struct group_switcher_data* gsd = malloc(sizeof(struct group_switcher_data));

  gsd->file = file;
  gsd->previous = -1;
  gsd->cmp_1_out = malloc(strlen("text-anchor=\"end\""));
  strcpy(gsd->cmp_1_out, "text-anchor=\"end\"");
  gsd->cmp_2_out = malloc(strlen("\0"));
  strcpy(gsd->cmp_2_out, "\0");

  int8_t m = 1;

  free(ret);

  for(int i = 0; i < bd->n_bars; i++)
  {
    y = (bar_height + bd->spacing) * i + bd->general->margin / 2.0;
    
    bar_width = (bd->bars[i].value / (bd->axel_data->w[1] - bd->axel_data->w[0])) * bd->general->viewport_x;

    width_offset = (bar_width < 0) ? bar_width : 0;
    yeet = (bar_width > 0) ? 0 : bar_width;

    bd->theme->percentage = (i + 1) / (bd->n_bars* 1.0);
    calculate_color(bd->theme);

    x = bd->general->margin / 2.0 + x_axel_y_offset + width_offset;

    gsd->cmp_1 = (gsd->previous == -1 || gsd->previous == 2) && bar_width <= 0;
    gsd->cmp_2 = (gsd->previous == -1 || gsd->previous == 1) && bar_width > 0;

    bar_width *= (bar_width > 0) ? 1 : -1;

    m = (group_switcher(gsd) == 1) ? -1 : 1; 

    fprintf(file, svg_box,
      bd->theme->out_color_rgb[0],
      bd->theme->out_color_rgb[1],
      bd->theme->out_color_rgb[2],
      x,
      y,
      bar_width,
      bar_height);

    ret = sn_instant("%9.1f", bd->bars[i].value);
    middle = bd->general->margin / 2.0 + x_axel_y_offset + width_offset;
    fprintf(file, svg_text, 
      x + bd->axel_data->axel_number_offset * m + bar_width + yeet, 
      y + bar_height / 2.0, 
      ret);
    free(ret);
    
  }

  fprintf(file, svg_group_stop);

  free(gsd->cmp_1_out);
  free(gsd->cmp_2_out);
  gsd->previous = -1;
  gsd->cmp_1_out = malloc(strlen("\0"));
  strcpy(gsd->cmp_1_out, "\0");
  gsd->cmp_2_out = malloc(strlen("text-anchor=\"end\""));
  strcpy(gsd->cmp_2_out, "text-anchor=\"end\"");

  for(int i = 0; i < bd->n_bars; i++)
  {
    y = (bar_height + bd->spacing) * i + bd->general->margin / 2.0;
    
    bar_width = (bd->bars[i].value / (bd->axel_data->w[1] - bd->axel_data->w[0])) * bd->general->viewport_x;

    width_offset = (bar_width < 0) ? bar_width : 0;
    yeet = (bar_width > 0) ? 0 : bar_width;

    gsd->cmp_1 = (gsd->previous == -1 || gsd->previous == 2) && bar_width <= 0;
    gsd->cmp_2 = (gsd->previous == -1 || gsd->previous == 1) && bar_width > 0;

    bar_width *= (bar_width > 0) ? 1 : -1;

    m = (group_switcher(gsd) == 2) ? -1 : 1;

    bar_width *= (bar_width > 0) ? 1 : -1;

    fprintf(file, svg_text, 
      bd->general->margin / 2.0 + x_axel_y_offset + bd->axel_data->axel_number_offset * m, 
      y + bar_height / 2.0, 
      bd->bars[i].name);
  }
  fprintf(file, svg_group_stop);
  fprintf(file, svg_group_stop);
  fprintf(file, svg_top_header_stop);
  free(gsd);
  return;
}
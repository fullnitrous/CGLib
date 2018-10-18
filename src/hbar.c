#include "cglib.h"
#include "cglib-other.h"

void hbar(struct bar_data* bd)
{
  char* ret;
  FILE* file = fopen(bd->general->file_name, "wb");
  float y_axel_x_offset = (bd->axel_data->h[0] < 0) ? 
                          bd->general->viewport_y * (bd->axel_data->h[0] / (bd->axel_data->h[0] - bd->axel_data->h[1])) : 0;
  float x_axel_y_offset = (bd->axel_data->w[0] < 0) ?
                          bd->general->viewport_x * (bd->axel_data->w[0] / (bd->axel_data->w[0] - bd->axel_data->w[1])) : 0;
  float bar_height = (bd->general->viewport_y - bd->spacing * (bd->n_bars - 1))
                    / bd->n_bars;
  float bar_width, width_offset, middle, x, y;
  int yeet = 1;
  print_top_header(file, bd->general);
  draw_axis_horizontals(file, x_axel_y_offset, y_axel_x_offset, bd->general, bd->axel_data);
  ret = stringify("dominant-baseline=\"middle\" font-size=\"%d\"", bd->general->font_size);
  fprintf(file, svg_custom_group, ret);
  free(ret);
  struct group_data* grp_dat = init_group_dat(file, "text-anchor=\"end\"", "\0");
  int8_t m = 1;
  for(int i = 0; i < bd->n_bars; i++)
  {
    y = (bar_height + bd->spacing) * i + bd->general->margin / 2.0;
    bar_width = (bd->bars[i].value / (bd->axel_data->w[1] - bd->axel_data->w[0])) * bd->general->viewport_x;
    width_offset = (bar_width < 0) ? bar_width : 0;
    yeet = (bar_width > 0) ? 0 : bar_width;
    bd->theme->percentage = (i + 1) / (bd->n_bars* 1.0);
    get_gradient(bd->theme);
    x = bd->general->margin / 2.0 + x_axel_y_offset + width_offset;
    grp_dat->cmp_1 = make_cmp_1(grp_dat, bar_width <= 0);
    grp_dat->cmp_2 = make_cmp_2(grp_dat, bar_width > 0);
    bar_width *= (bar_width > 0) ? 1 : -1;
    m = (print_group(grp_dat) == 1) ? -1 : 1; 
    fprintf(file, svg_box,
      bd->theme->out_color_rgb[0],
      bd->theme->out_color_rgb[1],
      bd->theme->out_color_rgb[2],
      x,
      y,
      bar_width,
      bar_height);
    ret = stringify("%9.1f", bd->bars[i].value);
    middle = bd->general->margin / 2.0 + x_axel_y_offset + width_offset;
    fprintf(file, svg_text, 
      x + bd->axel_data->axel_number_offset * m + bar_width + yeet, 
      y + bar_height / 2.0, 
      ret);
    free(ret); 
  }
  fprintf(file, svg_group_stop);
  destroy_group_dat(grp_dat);
  grp_dat = init_group_dat(file, "\0", "text-anchor=\"end\"");
  for(int i = 0; i < bd->n_bars; i++)
  {
    y = (bar_height + bd->spacing) * i + bd->general->margin / 2.0;
    bar_width = (bd->bars[i].value / (bd->axel_data->w[1] - bd->axel_data->w[0])) * bd->general->viewport_x;
    width_offset = (bar_width < 0) ? bar_width : 0;
    yeet = (bar_width > 0) ? 0 : bar_width;
    grp_dat->cmp_1 = make_cmp_1(grp_dat, bar_width <= 0);
    grp_dat->cmp_2 = make_cmp_2(grp_dat, bar_width > 0);
    bar_width *= (bar_width > 0) ? 1 : -1;
    m = (print_group(grp_dat) == 2) ? -1 : 1;
    bar_width *= (bar_width > 0) ? 1 : -1;
    fprintf(file, svg_text, 
      bd->general->margin / 2.0 + x_axel_y_offset + bd->axel_data->axel_number_offset * m, 
      y + bar_height / 2.0, 
      bd->bars[i].name);
  }
  fprintf(file, svg_group_stop);
  fprintf(file, svg_group_stop);
  fprintf(file, svg_top_header_stop);
  destroy_group_dat(grp_dat);
  return;
}
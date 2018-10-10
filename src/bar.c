#include "cgraphlib.h"
#include "cgraphlib-other.h"

void bar(struct bar_data* bd)
{
  FILE* file = fopen(bd->general->file_name, "wb");

  fprintf(file, svg_top_header_start, 
    bd->general->viewport_x + bd->general->margin, 
    bd->general->viewport_y + bd->general->margin, 
    bd->general->stroke_width);

  float y_axel_x_offset = (bd->axel_data->h[0] < 0) ? 
                          bd->general->viewport_y * (bd->axel_data->h[0] / (bd->axel_data->h[0] - bd->axel_data->h[1])) : 0;

  float x_axel_y_offset = (bd->axel_data->w[0] < 0) ?
                          bd->general->viewport_x * (bd->axel_data->w[0] / (bd->axel_data->w[0] - bd->axel_data->w[1])) : 0;

  draw_axis_horizontals(file, x_axel_y_offset, y_axel_x_offset, bd->general, bd->axel_data);

  float bar_width = (bd->general->viewport_x - bd->spacing * (bd->n_bars - 1))
                    / bd->n_bars;
  float x_bar_jump = bar_width + bd->spacing;

  float height;
  float height_offset;
  float height_offset_2;
  float middle;
  float label_offset = 20.0;

  int size;
  char* ret;

  for(int i = 0; i < bd->n_bars; i++)
  {
    height = (bd->bars[i].value / (bd->axel_data->h[1] - bd->axel_data->h[0])) * bd->general->viewport_y;

    height_offset = (height > 0) ? height : 0;
    height_offset_2 = (height > 0) ? height : height - 20.0;
    height *= (height > 0) ? 1 : -1;
    label_offset *= (height > 0) ? 1 : -1;

    fprintf(file, svg_box,
      0,
      0,
      0,
      bd->general->margin / 2.0 + i * x_bar_jump + x_axel_y_offset,
      bd->general->margin / 2.0 + bd->general->viewport_y - y_axel_x_offset - height_offset,
      bar_width,
      height);

    middle = (bd->general->margin / 2.0 + i * x_bar_jump + x_axel_y_offset + bar_width / 2);

    fprintf(file, svg_text,
      middle,
      bd->general->margin / 2.0 + bd->general->viewport_y - y_axel_x_offset + label_offset,
      bd->bars[i].name);

    size = snprintf(NULL, 0, "%9.1f",  bd->bars[i].value);
    ret = malloc(sizeof(char) * (size + 1));
    snprintf(ret, size, "%9.1f", bd->bars[i].value);
    ret[size] = '\0';

    fprintf(file, svg_text, 
      middle, 
      bd->general->margin / 2.0 + bd->general->viewport_y - y_axel_x_offset - height_offset_2, 
      ret);

    free(ret);
  }

  fprintf(file, svg_top_header_stop);
  return;
}
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
  uint8_t label_offset_multiplier = 1.0;

  int size;
  char* ret;

  size = snprintf(NULL, 0, "text-anchor = \"middle\" font-size=\"%d\"", bd->general->font_size);
  ret = malloc(sizeof(char) * (size + 1));
  snprintf(ret, size, "text-anchor = \"middle\" font-size=\"%d\"", bd->general->font_size);
  ret[size] = '\0';
  
  fprintf(file, svg_custom_group, ret);

  free(ret);

  for(int i = 0; i < bd->n_bars; i++)
  {
    height = (bd->bars[i].value / (bd->axel_data->h[1] - bd->axel_data->h[0])) * bd->general->viewport_y;

    height_offset = (height > 0) ? height : 0;
    height_offset_2 = (height > 0) ? height : height - 20.0;
    height *= (height > 0) ? 1 : -1;

    fprintf(file, svg_box,
      0,
      0,
      0,
      bd->general->margin / 2.0 + i * x_bar_jump + x_axel_y_offset,
      bd->general->margin / 2.0 + bd->general->viewport_y - y_axel_x_offset - height_offset,
      bar_width,
      height);

    size = snprintf(NULL, 0, "%9.1f",  bd->bars[i].value);
    ret = malloc(sizeof(char) * (size + 1));
    snprintf(ret, size, "%9.1f", bd->bars[i].value);
    ret[size] = '\0';

    middle = (bd->general->margin / 2.0 + i * x_bar_jump + x_axel_y_offset + bar_width / 2);

    fprintf(file, svg_text, 
      middle, 
      bd->general->margin / 2.0 + bd->general->viewport_y - y_axel_x_offset - height_offset_2 - bd->axel_data->axel_number_offset, 
      ret);

    free(ret);
  }

  uint8_t s = 1;
  int8_t m = 1;
  char* end_width = malloc(strlen(svg_group_stop));
  strcpy(end_width, svg_group_stop);

  fprintf(file, svg_custom_group, "dominant-baseline=\"hanging\""); 

  for(int i = 0; i < bd->n_bars; i++)
  {
    height = (bd->bars[i].value / (bd->axel_data->h[1] - bd->axel_data->h[0])) * bd->general->viewport_y;

    if(s == 1 && height <= 0)
    {
      fprintf(file, svg_group_stop);
      free(end_width);
      end_width = malloc(1);
      strcpy(end_width, "\0");
      s = 0;
      m = -1;
    }
    else if(s == 0 && height > 0.0)
    {
      fprintf(file, svg_custom_group, "dominant-baseline=\"hanging\""); 
      free(end_width);
      end_width = malloc(strlen(svg_group_stop));
      strcpy(end_width, svg_group_stop);
      s = 1;
      m = 1;
    }

    middle = (bd->general->margin / 2.0 + i * x_bar_jump + x_axel_y_offset + bar_width / 2);

    fprintf(file, svg_text,
      middle,
      bd->general->margin / 2.0 + bd->general->viewport_y - y_axel_x_offset + bd->axel_data->axel_number_offset * m,
      bd->bars[i].name);
  }

  fprintf(file, end_width);

  fprintf(file, svg_group_stop);

  fprintf(file, svg_top_header_stop);
  return;
}
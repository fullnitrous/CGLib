#include "cgraphlib.h"
#include "cgraphlib-other.h"

void hbar(struct bar_data* bd)
{
  int size;
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

  size = snprintf(NULL, 0, "dominant-baseline=\"middle\" font-size=\"%d\"", bd->general->font_size);
  ret = malloc(sizeof(char) * (size + 1));
  snprintf(ret, size, "dominant-baseline=\"middle\" font-size=\"%d\"", bd->general->font_size);
  ret[size] = '\0';
  
  fprintf(file, svg_custom_group, ret);

  fprintf(file, svg_custom_group, "dominant-baseline=\"middle\"");

  uint8_t s = 1;
  int8_t m = 1;
  char* end_width = malloc(1);
  strcpy(end_width, "\0");

  free(ret);

  for(int i = 0; i < bd->n_bars; i++)
  {
    y = (bar_height + bd->spacing) * i + bd->general->margin / 2.0;
    
    bar_width = (bd->bars[i].value / (bd->axel_data->w[1] - bd->axel_data->w[0])) * bd->general->viewport_x;

    width_offset = (bar_width < 0) ? bar_width : 0;
    yeet = (bar_width > 0) ? 0 : bar_width;
    bar_width *= (bar_width > 0) ? 1 : -1;

    bd->theme->percentage = (i + 1) / (bd->n_bars* 1.0);
    calculate_color(bd->theme);

    x = bd->general->margin / 2.0 + x_axel_y_offset + width_offset;

    if(s == 1 && bar_width <= 0.0)
    {
      fprintf(file, svg_group_stop);
      free(end_width);
      end_width = malloc(1);
      strcpy(end_width, "\0");
      s = 0;
      m = 1;
    }
    else if(s == 0 && bar_width > 0.0)
    {
      fprintf(file, svg_custom_group, "dominant-baseline=\"middle\" text-anchor=\"end\""); 
      free(end_width);
      end_width = malloc(strlen(svg_group_stop));
      strcpy(end_width, svg_group_stop);
      s = 1;
      m = -1;
    }

    fprintf(file, svg_box,
      bd->theme->out_color_rgb[0],
      bd->theme->out_color_rgb[1],
      bd->theme->out_color_rgb[2],
      x,
      y,
      bar_width,
      bar_height);

    size = snprintf(NULL, 0, "%9.1f",  bd->bars[i].value);
    ret = malloc(sizeof(char) * (size + 1));
    snprintf(ret, size, "%9.1f", bd->bars[i].value);
    ret[size] = '\0';

    middle = bd->general->margin / 2.0 + x_axel_y_offset + width_offset;

    fprintf(file, svg_text, 
      x + bd->axel_data->axel_number_offset * m + bar_width + yeet, 
      y + bar_height / 2.0, 
      ret);

    free(ret);
  }


  fprintf(file, svg_custom_group, "dominant-baseline=\"middle\" text-anchor=\"end\""); 
  for(int i = 0; i < bd->n_bars; i++)
  {
    y = (bar_height + bd->spacing) * i + bd->general->margin / 2.0;
    
    bar_width = (bd->bars[i].value / (bd->axel_data->w[1] - bd->axel_data->w[0])) * bd->general->viewport_x;

    width_offset = (bar_width < 0) ? bar_width : 0;
    yeet = (bar_width > 0) ? 0 : bar_width;
    bar_width *= (bar_width > 0) ? 1 : -1;

    x = bd->general->margin / 2.0 + x_axel_y_offset + width_offset;

    if(s == 1 && bar_width <= 0)
    {
      fprintf(file, svg_group_stop);
      free(end_width);
      end_width = malloc(1);
      strcpy(end_width, "\0");
      s = 0;
      m = -1;
    }
    else if(s == 0 && bar_width > 0.0)
    {
      fprintf(file, svg_custom_group, "dominant-baseline=\"middle\" text-anchor=\"start\""); 
      free(end_width);
      end_width = malloc(strlen(svg_group_stop));
      strcpy(end_width, svg_group_stop);
      s = 1;
      m = 1;
    }

    fprintf(file, svg_text, 
      x + (bd->axel_data->axel_number_offset * m) - yeet, 
      y + bar_height / 2.0, 
      bd->bars[i].name);
  }
  fprintf(file, svg_group_stop);
  fprintf(file, svg_group_stop);
  fprintf(file, svg_group_stop);
  fprintf(file, svg_top_header_stop);
  return;
}
#include "cgraphlib.h"
#include "cgraphlib-other.h"

void print_slice_pointers(FILE* file, struct pie_data* pd)
{
  float pointer_len = 120.0;

  int size;
  char* ret;

  float sum_counter;
  float radians_1;
  float radians_2;
  float radians_3;
  float x_start;
  float x_stop;
  float y_start;
  float y_stop;
  float x_pointer_start;
  float y_pointer_start;

  float current_pointer_len;

  float p_offset_x = pd->general->viewport_x / 2.0 + pd->general->margin / 2.0;
  float p_offset_y = pd->general->viewport_y / 2.0 + pd->general->margin / 2.0;

  float radius = (pd->general->viewport_y <= pd->general->viewport_x) ? (pd->general->viewport_y - pd->general->margin) / 2 : (pd->general->viewport_x - pd->general->margin) / 2;

  float origin[2];
  origin[0] = pd->general->viewport_x / 2.0 + pd->general->margin / 2.0;
  origin[1] = pd->general->viewport_y / 2.0 + pd->general->margin / 2.0;
  
  fprintf(file, svg_custom_group, "stroke=\"black\"");
  sum_counter = 0.0;

  uint8_t s = 1;
  char* end_width = malloc(strlen(svg_group_stop));
  strcpy(end_width, svg_group_stop);

  size = snprintf(NULL, 0, "stroke=\"#%02x%02x%02x\"", 
  pd->axel_data->axel_rgb[0],
  pd->axel_data->axel_rgb[1],
  pd->axel_data->axel_rgb[2]);
  ret = malloc(sizeof(char) * (size + 1));
  snprintf(ret, size, "stroke=\"#%02x%02x%02x\"", 
  pd->axel_data->axel_rgb[0],
  pd->axel_data->axel_rgb[1],
  pd->axel_data->axel_rgb[2]);
  ret[size] = '\0';

  fprintf(file, svg_custom_group, ret);

  free(ret);

  for(int i = 0; i < pd->n_slices; i++)
  {
    radians_3 = 2   * (pd->slices[i].percentage / 2 + sum_counter) * PI;
    sum_counter     += pd->slices[i].percentage;
    x_pointer_start = cos(radians_3) * radius + p_offset_x;
    y_pointer_start = sin(radians_3) * radius + p_offset_y;
    current_pointer_len = (origin[0] < x_pointer_start) ? pointer_len : -pointer_len;

    //pointer lol
    fprintf(file, svg_line, 
      x_pointer_start, 
      y_pointer_start,
      x_pointer_start + current_pointer_len,
      y_pointer_start);
  }
  fprintf(file, svg_group_stop);
  fprintf(file, svg_group_stop);

  sum_counter = 0.0;
  for(int i = 0; i < pd->n_slices; i++)
  {
    radians_3 = 2   * (pd->slices[i].percentage / 2 + sum_counter) * PI;
    sum_counter     += pd->slices[i].percentage;
    x_pointer_start = cos(radians_3) * radius + p_offset_x;
    y_pointer_start = sin(radians_3) * radius + p_offset_y;
    current_pointer_len = (origin[0] < x_pointer_start) ? pointer_len : -pointer_len;

    if(s == 1 && origin[0] < x_pointer_start)
    {
      fprintf(file, svg_custom_group, "text-anchor = \"end\""); 
      free(end_width);
      end_width = malloc(strlen(svg_group_stop));
      strcpy(end_width, svg_group_stop);
      s = 0;
    }
    else if(s == 0 && origin[0] > x_pointer_start)
    {
      fprintf(file, svg_group_stop);
      free(end_width);
      end_width = malloc(1);
      strcpy(end_width, "\0");
      s = 1;
    }

    fprintf(file, svg_text,
      x_pointer_start + current_pointer_len,
      y_pointer_start - pd->axel_data->axel_number_offset,
      pd->slices[i].name);
  }

  fprintf(file, end_width);

  sum_counter = 0.0;

  s = 1;
  end_width = malloc(strlen(svg_group_stop));
  strcpy(end_width, svg_group_stop);

  size = snprintf(NULL, 0, "fill=\"#%02x%02x%02x\" dominant-baseline=\"hanging\"", 
  pd->axel_data->axel_rgb[0],
  pd->axel_data->axel_rgb[1],
  pd->axel_data->axel_rgb[2]);
  ret = malloc(sizeof(char) * (size + 1));
  snprintf(ret, size, "fill=\"#%02x%02x%02x\" dominant-baseline=\"hanging\"", 
  pd->axel_data->axel_rgb[0],
  pd->axel_data->axel_rgb[1],
  pd->axel_data->axel_rgb[2]);
  ret[size] = '\0';

  fprintf(file, svg_custom_group,  ret);

  free(ret);
  
  for(int i = 0; i < pd->n_slices; i++)
  {
    radians_3 = 2   * (pd->slices[i].percentage / 2 + sum_counter) * PI;
    sum_counter     += pd->slices[i].percentage;
    x_pointer_start = cos(radians_3) * radius + p_offset_x;
    y_pointer_start = sin(radians_3) * radius + p_offset_y;
    current_pointer_len = (origin[0] < x_pointer_start) ? pointer_len : -pointer_len;

    size = snprintf(NULL, 0, "%9.1f%%", pd->slices[i].percentage * 100);
    ret = malloc(sizeof(char) * (size + 1));
    snprintf(ret, size, "%9.1f%%", pd->slices[i].percentage * 100);
    ret[size] = '\0';
    
    if(s == 1 && origin[0] < x_pointer_start)
    {
      fprintf(file, svg_custom_group, "text-anchor = \"end\""); 
      free(end_width);
      end_width = malloc(strlen(svg_group_stop));
      strcpy(end_width, svg_group_stop);
      s = 0;
    }
    else if(s == 0 && origin[0] > x_pointer_start)
    {
      fprintf(file, svg_group_stop);
      free(end_width);
      end_width = malloc(1);
      strcpy(end_width, "\0");
      s = 1;
    }

    fprintf(file, svg_text,   
      x_pointer_start + current_pointer_len, 
      y_pointer_start + pd->axel_data->axel_number_offset, ret);

    free(ret);
  }
  fprintf(file, svg_group_stop);
  fprintf(file, end_width);
}

void print_font_size_group(FILE* file, struct general_data* gd)
{
  int size = snprintf(NULL, 0, "font-size=\"%d\"", gd->font_size);
  char* ret = malloc(sizeof(char) * (size + 1));
  snprintf(ret, size, "font-size=\"%d\"", gd->font_size);
  ret[size] = '\0';
  fprintf(file, svg_custom_group, ret);
  free(ret);
  return;
}

void pie(struct pie_data* pd)
{
  //making this number 2 above or very near 2 can cause visual bugs
  float percentage_overlap_multiplier = 1.9;

  FILE* file = fopen(pd->general->file_name, "wb");

  print_top_header(file, pd->general);

  float radius = (pd->general->viewport_y <= pd->general->viewport_x) ? (pd->general->viewport_y - pd->general->margin) / 2 : (pd->general->viewport_x - pd->general->margin) / 2;
  
  float origin[2];
  origin[0] = pd->general->viewport_x / 2.0 + pd->general->margin / 2.0;
  origin[1] = pd->general->viewport_y / 2.0 + pd->general->margin / 2.0;

  float sum = 0.0;
  
  for(int i = 0; i < pd->n_slices; i++)
  {
    sum += pd->slices[i].percentage;
  }

  uint8_t large_arc_flag;
  float sum_counter;
  float radians_1;
  float radians_2;
  float x_start;
  float x_stop;
  float y_start;
  float y_stop;

  int size;
  char* ret;

  print_font_size_group(file, pd->general);

  float current_pointer_len;

  float p_offset_x = pd->general->viewport_x / 2.0 + pd->general->margin / 2.0;
  float p_offset_y = pd->general->viewport_y / 2.0 + pd->general->margin / 2.0;

  uint8_t calculated_rgb[3];

  if(roundf(sum * 100) / 100 == 1.0 && pd->n_slices >= 3)
  {
    sum_counter = 0.0;
    fprintf(file, svg_limiter_box);

    int i = 0;
    float store_slice_0 = pd->slices[0].percentage;
    int   store_n_slices = pd->n_slices;
    uint8_t print_first = 1;
    LOL:
    for(i; i < pd->n_slices; i++)
    {
      large_arc_flag  = (pd->slices[i].percentage > 0.5) ? 1 : 0;
      radians_1 = 2 * sum_counter * PI;
      radians_2 = 2 * (pd->slices[i].percentage * percentage_overlap_multiplier + sum_counter) * PI;
      sum_counter   += pd->slices[i].percentage;

      x_start         = cos(radians_1) * radius + p_offset_x;
      y_start         = sin(radians_1) * radius + p_offset_y;
      x_stop          = cos(radians_2) * radius + p_offset_x;
      y_stop          = sin(radians_2) * radius + p_offset_y;

      pd->theme->percentage = (i + 1) / (store_n_slices * 1.0);

      calculate_color(pd->theme);

      fprintf(file, svg_slice,
        x_start,
        y_start,
        radius,
        radius,
        large_arc_flag,
        x_stop,
        y_stop,
        origin[0],
        origin[1],
        pd->theme->out_color_rgb[0],
        pd->theme->out_color_rgb[1],
        pd->theme->out_color_rgb[2]);
    }

    if(print_first)
    {
      print_first = 0;
      i = 0;
      pd->n_slices = 1;
      sum_counter = 0.0;
      percentage_overlap_multiplier = 1.0;
      goto LOL;
    }
    else
    {
      pd->slices[0].percentage = store_slice_0;
      pd->n_slices = store_n_slices;
    }
    print_slice_pointers(file, pd);
    fprintf(file, svg_group_stop);
  }
  else
  {
    printf("error slices do not add up to 100%%, but %9.6f%%\n", sum);
  }
  fprintf(file, svg_group_stop);
  fprintf(file, svg_top_header_stop);
  fclose(file);
}
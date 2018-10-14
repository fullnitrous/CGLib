#include "cgraphlib.h"
#include "cgraphlib-other.h"

void doughnut(struct pie_data* pd)
{
  //making this number 2 above or very near 2 can cause visual bugs
  float percentage_overlap_multiplier = 1.9;
  float radius_divisior = 1.5;

  FILE* file = fopen(pd->general->file_name, "wb");

  print_top_header(file, pd->general);
  print_font_size_group(file, pd->general);

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
  float x_0;
  float y_0;
  float x_1;
  float y_1;
  float x_2;
  float y_2;
  float x_3;
  float y_3;
  

  int size;
  char* ret;

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

      x_0 = cos(radians_1) * radius + p_offset_x;
      y_0 = sin(radians_1) * radius + p_offset_y;
      x_1 = cos(radians_2) * radius + p_offset_x;
      y_1 = sin(radians_2) * radius + p_offset_y;
      x_2 = cos(radians_2) * (radius / radius_divisior) + p_offset_x;
      y_2 = sin(radians_2) * (radius / radius_divisior) + p_offset_y;
      x_3 = cos(radians_1) * (radius / radius_divisior) + p_offset_x;
      y_3 = sin(radians_1) * (radius / radius_divisior) + p_offset_y;

      pd->theme->percentage = (i + 1) / (store_n_slices * 1.0);

      get_gradient(pd->theme);

      fprintf(file, svg_doughnut_section,
        x_0,
        y_0,
        radius,
        radius,
        large_arc_flag,
        x_1,
        y_1,
        x_2,
        y_2,
        radius / radius_divisior,
        radius / radius_divisior,
        large_arc_flag,
        x_3,
        y_3,
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

    //ARBRITARY VALUES HERE, MUST BE ELIMINATED LATER

    fprintf(file, svg_custom_group, "text-anchor=\"middle\" font-size=\"50\"");
    fprintf(file, svg_text,
      origin[0],
      origin[1],
      pd->doughnut_header);
    fprintf(file, svg_custom_group, "dominant-baseline=\"hanging\" font-size=\"20\"");
    fprintf(file, svg_text,
      origin[0],
      origin[1] + pd->axel_data->axel_number_offset,
      pd->doughnut_sub_header);
    fprintf(file, svg_group_stop);
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
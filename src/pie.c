#include "cgraphlib.h"
#include "cgraphlib-other.h"

void pie(struct pie_data* pd)
{
  FILE* file = fopen(pd->general->file_name, "wb");

  fprintf(file, svg_top_header_start, 
    pd->general->viewport_x + pd->general->margin, pd->general->viewport_y + pd->general->margin, 
    pd->general->stroke_width);

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
  float radians_3;
  float x_start;
  float x_stop;
  float y_start;
  float y_stop;
  float x_pointer_start;
  float y_pointer_start;
  float x_percentage;
  float y_percentage;

  int size;
  char* ret;

  float  pointer_len = 120.0;
  float  current_pointer_len;

  float p_offset_x = pd->general->viewport_x / 2.0 + pd->general->margin / 2.0;
  float p_offset_y = pd->general->viewport_y / 2.0 + pd->general->margin / 2.0;

  if(roundf(sum * 100) / 100 == 1.0)
  {
    sum_counter = 0.0;

    for(int i = 0; i < pd->n_slices; i++)
    {
      large_arc_flag = (pd->slices[i].percentage > 0.5) ? 1 : 0;

      radians_1 = 2 * sum_counter * PI;
      radians_2 = 2 * (pd->slices[i].percentage + sum_counter) * PI;
      radians_3 = 2 * (pd->slices[i].percentage / 2 + sum_counter) * PI;

      sum_counter += pd->slices[i].percentage;

      x_start         = cos(radians_1) * radius + p_offset_x;
      y_start         = sin(radians_1) * radius + p_offset_y;
      x_stop          = cos(radians_2) * radius + p_offset_x;
      y_stop          = sin(radians_2) * radius + p_offset_y;
      x_pointer_start = cos(radians_3) * radius + p_offset_x;
      y_pointer_start = sin(radians_3) * radius + p_offset_y;
      x_percentage    = cos(radians_3) * radius * 0.85 + p_offset_x;
      y_percentage    = sin(radians_3) * radius * 0.85 + p_offset_y;


      

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
        getRandByte(),
        getRandByte(),
        getRandByte());
      
      current_pointer_len = (origin[0] < x_pointer_start) ? pointer_len : -pointer_len;

      //pointer lol
      fprintf(file, svg_line, 
        x_pointer_start, 
        y_pointer_start,
        x_pointer_start + current_pointer_len,
        y_pointer_start);

      fprintf(file, svg_text,
        x_pointer_start + current_pointer_len,
        y_pointer_start,
        pd->slices[i].name);

      size = snprintf(NULL, 0, "%9.1f%%", pd->slices[i].percentage * 100);
      ret = malloc(sizeof(char) * (size + 1));
      snprintf(ret, size, "%9.1f%%", pd->slices[i].percentage * 100);
      ret[size] = '\0';
      
      //start of the percentage lol
      fprintf(file, svg_text, x_percentage, y_percentage, ret);

      free(ret);
    }
  }
  else
  {
    printf("error slices do not add up to 100%%, but %9.6f%%\n", sum);
  }
  fprintf(file, svg_top_header_stop);
  fclose(file);
}
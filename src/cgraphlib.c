#include "cgraphlib.h"
#include "cgraphlib-other.h"

void WW(FILE* file, const char* format, ...)
{
  va_list args;
  va_start(args, format);
  int size = vsnprintf(NULL, 0, format, args);
  va_end(args);
  char* ret = malloc(sizeof(char) * (size + 1));
  va_start(args, format);
  vsnprintf(ret, size, format, args);
  va_end(args);
  ret[size] = '\0';
  fwrite(ret, size, 1, file);
  free(ret);
  return;
}

uint8_t getRandByte(void)
{
  return rand();
}

void draw_axis_horizontals(FILE* file, float x_axel_y_offset, float y_axel_x_offset, struct general_data* gd, struct axel_data* ad)
{
  int size;
  char* ret;

  //draw vertical lines with corresponding numbers
  float add = gd->viewport_x / ad->n_measure_points;
  float a_add = (ad->w[1] - ad->w[0]) / ad->n_measure_points;
  float counter = 0;
  float a_counter = ad->w[0];
  for(int i = 0; i < ad->n_measure_points + 1; i++)
  {
    fprintf(file, svg_line, 
      gd->margin / 2.0 + counter, 
      gd->margin / 2.0, 
      gd->margin / 2.0 + counter,
      gd->margin / 2.0 + gd->viewport_y);

    size = snprintf(NULL, 0, "%9.2f", a_counter);
    ret = malloc(sizeof(char) * (size + 1));
    snprintf(ret, size, "%9.2f", a_counter);
    ret[size] = '\0';
    
    fprintf(file, svg_text, 
      gd->margin / 2.0 + counter,
      gd->margin / 2.0 + gd->viewport_y - y_axel_x_offset,
      ret);
    
    free(ret);

    counter += add;
    a_counter += a_add;
  }

  a_add = (ad->h[1] - ad->h[0]) / ad->n_measure_points;
  a_counter = ad->h[0];

  //draw horizontal lines with corresponding numbers
  add = gd->viewport_y / ad->n_measure_points;
  counter = 0;
  for(int i = 0; i < ad->n_measure_points + 1; i++)
  {
    fprintf(file, svg_line, 
      gd->margin / 2.0, 
      gd->margin / 2.0 + gd->viewport_y - counter, 
      gd->margin / 2.0 + gd->viewport_x, 
      gd->margin / 2.0 + gd->viewport_y - counter);

    size = snprintf(NULL, 0, "%9.2f", a_counter);
    ret = malloc(sizeof(char) * (size + 1));
    snprintf(ret, size, "%9.2f", a_counter);
    ret[size] = '\0';

    fprintf(file, svg_text, 
      gd->margin / 2.0 + x_axel_y_offset,
      gd->margin / 2.0 + gd->viewport_y - counter,
      ret);

    counter += add;
    a_counter += a_add;
  }

  //draw the y axel
  fprintf(file, svg_axel, 
    gd->margin / 2.0 + x_axel_y_offset, 
    gd->margin / 2.0, 
    gd->margin / 2.0 + x_axel_y_offset,
    gd->margin / 2.0 + gd->viewport_y);

  //draw the x axel
  fprintf(file, svg_axel, 
    gd->margin / 2.0, 
    gd->margin / 2.0 + gd->viewport_y - y_axel_x_offset, 
    gd->margin / 2.0 + gd->viewport_x, 
    gd->margin / 2.0 + gd->viewport_y - y_axel_x_offset);
  return;
}
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
  char* ret_2;

  size = snprintf(NULL, 0, "stroke = \"#%02x%02x%02x\"", 
  ad->axel_lines_rgb[0],
  ad->axel_lines_rgb[1],
  ad->axel_lines_rgb[2]);
  ret = malloc(sizeof(char) * (size + 1));
  snprintf(ret, size, "stroke = \"#%02x%02x%02x\"", 
  ad->axel_lines_rgb[0],
  ad->axel_lines_rgb[1],
  ad->axel_lines_rgb[2]);
  ret[size] = '\0';

  fprintf(file, svg_custom_group, ret);

  free(ret);

  float add = gd->viewport_x / ad->n_measure_points;
  float counter = 0;

  if(ad->vertical_lines)
  {
    //draw vertical lines with corresponding numbers
    
    for(int i = 0; i < ad->n_measure_points + 1; i++)
    {
      fprintf(file, svg_line, 
        gd->margin / 2.0 + counter, 
        gd->margin / 2.0, 
        gd->margin / 2.0 + counter,
        gd->margin / 2.0 + gd->viewport_y);

      counter += add;
    }
  }

  if(ad->horizontal_lines)
  {
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

      counter += add;
    }
  }

  fprintf(file, svg_group_stop);

  float a_add = (ad->w[1] - ad->w[0]) / ad->n_measure_points;
  float a_counter = ad->w[0];
  counter =  0;
  add = gd->viewport_x / ad->n_measure_points;
  
  if(ad->numbered_x)
  {
    size = snprintf(NULL, 0, "text-anchor = \"end\" dominant-baseline=\"hanging\" font-size=\"%d\"", gd->font_size);
    ret = malloc(sizeof(char) * (size + 1));
    snprintf(ret, size, "text-anchor = \"end\" dominant-baseline=\"hanging\" font-size=\"%d\"", gd->font_size);
    ret[size] = '\0';

    fprintf(file, svg_custom_group, ret);
    for(int i = 0; i < ad->n_measure_points + 1; i++)
    {
      size = snprintf(NULL, 0, "%9.2f", a_counter);
      ret = malloc(sizeof(char) * (size + 1));
      snprintf(ret, size, "%9.2f", a_counter);
      ret[size] = '\0';

      size = snprintf(NULL, 0, "transform=\"rotate(%9.6f, %9.6f, %9.6f)\"", 
      ad->x_axel_text_angle,
      gd->margin / 2.0 + counter,
      gd->margin / 2.0 + gd->viewport_y - y_axel_x_offset);


      ret_2 = malloc(sizeof(char) * (size + 1));
      snprintf(ret_2, size, "transform=\"rotate(%9.6f, %9.6f, %9.6f)\"",
      ad->x_axel_text_angle,
      gd->margin / 2.0 + counter,
      gd->margin / 2.0 + gd->viewport_y - y_axel_x_offset);


      ret_2[size] = '\0';
      
      fprintf(file, svg_custom_text, 
        gd->margin / 2.0 + counter,
        gd->margin / 2.0 + gd->viewport_y - y_axel_x_offset + ad->axel_number_offset,
        ret_2,
        ret);

      counter += add;
      a_counter += a_add;
      
      free(ret);
      free(ret_2);
    }
    fprintf(file, svg_group_stop);
  }

  counter = 0;

  a_add = (ad->h[1] - ad->h[0]) / ad->n_measure_points;
  a_counter = ad->h[0];
  add = gd->viewport_y / ad->n_measure_points;

  if(ad->numbered_y)
  {
    size = snprintf(NULL, 0, "text-anchor = \"end\" font-size=\"%d\"", gd->font_size);
    ret = malloc(sizeof(char) * (size + 1));
    snprintf(ret, size, "text-anchor = \"end\" font-size=\"%d\"", gd->font_size);
    ret[size] = '\0';

    fprintf(file, svg_custom_group, ret);
    for(int i = 0; i < ad->n_measure_points + 1; i++)
    {
      size = snprintf(NULL, 0, "%9.2f", a_counter);
      ret = malloc(sizeof(char) * (size + 1));
      snprintf(ret, size, "%9.2f", a_counter);
      ret[size] = '\0';

      fprintf(file, svg_text, 
        gd->margin / 2.0 + x_axel_y_offset + ad->axel_number_offset * -1,
        gd->margin / 2.0 + gd->viewport_y - counter,
        ret);

      counter += add;
      a_counter += a_add;
      
      free(ret);
    }
    fprintf(file, svg_group_stop);
  }

  size = snprintf(NULL, 0, "stroke = \"#%02x%02x%02x\"", 
  ad->axel_rgb[0],
  ad->axel_rgb[1],
  ad->axel_rgb[2]);
  ret = malloc(sizeof(char) * (size + 1));
  snprintf(ret, size, "stroke = \"#%02x%02x%02x\"", 
  ad->axel_rgb[0],
  ad->axel_rgb[1],
  ad->axel_rgb[2]);
  ret[size] = '\0';

  fprintf(file, svg_custom_group, ret);

  free(ret);

  //draw the y axel
  fprintf(file, svg_line, 
    gd->margin / 2.0 + x_axel_y_offset, 
    gd->margin / 2.0, 
    gd->margin / 2.0 + x_axel_y_offset,
    gd->margin / 2.0 + gd->viewport_y);

  //draw the x axel
  fprintf(file, svg_line, 
    gd->margin / 2.0, 
    gd->margin / 2.0 + gd->viewport_y - y_axel_x_offset, 
    gd->margin / 2.0 + gd->viewport_x, 
    gd->margin / 2.0 + gd->viewport_y - y_axel_x_offset);

  fprintf(file, svg_group_stop);
  return;
}

void calculate_color(struct theme_data* td)
{
  int delta;
  int delta_index;
  int8_t flip = 1;

  for(int i = 0; i < 3; i++)
  {
    delta = td->stop_color_rgb[i] - td->start_color_rgb[i];
    delta *= (delta < 0) ? -1 : 1;
    flip = (td->start_color_rgb[i] > td->stop_color_rgb[i]) ? -1 : 1;
    delta_index = delta * td->percentage;
    td->out_color_rgb[i] = td->start_color_rgb[i] + delta_index * flip;
  }
  return;
}

void print_top_header(FILE* file, struct general_data* gd)
{
  fprintf(file, 
    svg_top_header_start, 
    gd->viewport_x + gd->margin, 
    gd->viewport_y + gd->margin, 
    gd->stroke_width,
    gd->margin / 2.0,
    gd->margin / 2.0,
    gd->viewport_x, 
    gd->viewport_y);
  return;
}
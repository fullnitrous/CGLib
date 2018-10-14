#include "cgraphlib.h"
#include "cgraphlib-other.h"

uint8_t getRandByte(void)
{
  return rand();
}

void draw_axis_horizontals(FILE* file, float x_axel_y_offset, float y_axel_x_offset, struct general_data* gd, struct axel_data* ad)
{
  char* ret;
  char* ret_2;

  ret = stringify("stroke = \"#%02x%02x%02x\"", 
    ad->axel_lines_rgb[0],
    ad->axel_lines_rgb[1],
    ad->axel_lines_rgb[2]);

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
    ret = stringify("text-anchor = \"end\" dominant-baseline=\"hanging\" font-size=\"%d\"", gd->font_size);

    fprintf(file, svg_custom_group, ret);
    for(int i = 0; i < ad->n_measure_points + 1; i++)
    {
      ret = stringify("%9.2f", a_counter);

      ret_2 = stringify("transform=\"rotate(%9.6f, %9.6f, %9.6f)\"", 
      ad->x_axel_text_angle,
      gd->margin / 2.0 + counter,
      gd->margin / 2.0 + gd->viewport_y - y_axel_x_offset);
      
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
    ret = stringify("text-anchor = \"end\" font-size=\"%d\"", gd->font_size);

    fprintf(file, svg_custom_group, ret);
    for(int i = 0; i < ad->n_measure_points + 1; i++)
    {
      ret = stringify("%9.2f", a_counter);

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

  ret = stringify("stroke = \"#%02x%02x%02x\"", 
    ad->axel_rgb[0],
    ad->axel_rgb[1],
    ad->axel_rgb[2]);

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

void get_gradient(struct theme_data* td)
{
  int rgb_delta;
  int rgb_delta_index;
  int8_t direction = 1;

  for(int i = 0; i < 3; i++)
  {
    rgb_delta = td->stop_color_rgb[i] - td->start_color_rgb[i];
    rgb_delta *= (rgb_delta < 0) ? -1 : 1;

    direction = (td->start_color_rgb[i] > td->stop_color_rgb[i]) ? -1 : 1;

    rgb_delta_index = rgb_delta * td->percentage;
    
    td->out_color_rgb[i] = td->start_color_rgb[i] + rgb_delta_index * direction;
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

char* stringify(const char* format, ...)
{
  char* str;
  int   len_str;

  va_list args;
  va_start(args, format);
  len_str = vsnprintf(NULL, 0, format, args);
  va_end(args);
  str = malloc(sizeof(char) * (len_str + 1));
  va_start(args, format);
  vsnprintf(str, len_str, format, args);
  va_end(args);
  str[len_str] = '\0';
  return str;
}

int print_group(struct group_data* grp_dat)
{
  if(grp_dat->cmp_1)
  {
    (grp_dat->previous != -1) ? fprintf(grp_dat->file, svg_group_stop) : 0;
    fprintf(grp_dat->file, svg_custom_group, grp_dat->cmp_1_out);
    grp_dat->previous = 1;
  }
  else if(grp_dat->cmp_2)
  {
    (grp_dat->previous != -1) ? fprintf(grp_dat->file, svg_group_stop) : 0;
    fprintf(grp_dat->file, svg_custom_group, grp_dat->cmp_2_out);
    grp_dat->previous = 2;
  }
  return grp_dat->previous;
}

struct group_data* init_group_dat(FILE* file, const char* cmp_1_out, const char* cmp_2_out)
{
  struct group_data* grp_dat;
  grp_dat = malloc(sizeof(struct group_data));
  grp_dat->file = file;
  grp_dat->previous = -1;
  grp_dat->cmp_1_out = malloc(strlen(cmp_1_out));
  strcpy(grp_dat->cmp_1_out, cmp_1_out);
  grp_dat->cmp_2_out = malloc(strlen(cmp_2_out));
  strcpy(grp_dat->cmp_2_out, cmp_2_out);
  return grp_dat;
}

void destroy_group_dat(struct group_data* grp_dat)
{
  free(grp_dat->cmp_1_out);
  free(grp_dat->cmp_2_out);
  free(grp_dat);
  return;
}
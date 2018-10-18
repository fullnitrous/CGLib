#include "cglib.h"
#include "cglib-other.h"

void print_slice_pointers(FILE* file, struct pie_data* pd)
{
  float pointer_len = 120.0;
  char* ret;

  float sum_counter, 
    radians,
    x_start,
    x_stop,
    y_start,
    y_stop,
    x_pointer_start,
    y_pointer_start;

  float current_pointer_len;

  float radius = (pd->general->viewport_y <= pd->general->viewport_x) ? (pd->general->viewport_y - pd->general->margin) / 2 : (pd->general->viewport_x - pd->general->margin) / 2;

  float origin[2];
  origin[0] = pd->general->viewport_x / 2.0 + pd->general->margin / 2.0;
  origin[1] = pd->general->viewport_y / 2.0 + pd->general->margin / 2.0;
  
  fprintf(file, svg_custom_group, "stroke=\"black\"");
  sum_counter = 0.0;

  uint8_t s = 1;
  char* end_width = malloc(strlen(svg_group_stop));
  strcpy(end_width, svg_group_stop);

  ret = stringify("stroke=\"#%02x%02x%02x\"", 
    pd->axel_data->axel_rgb[0],
    pd->axel_data->axel_rgb[1],
    pd->axel_data->axel_rgb[2]);
  fprintf(file, svg_custom_group, ret);
  free(ret);

  for(int i = 0; i < pd->n_slices; i++)
  {
    radians = 2*(pd->slices[i].percentage/2+sum_counter)*PI;
    sum_counter += pd->slices[i].percentage;
    x_pointer_start = cos(radians)*radius+origin[0];
    y_pointer_start = sin(radians)*radius+origin[1];
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

  struct group_data* grp_dat = init_group_dat(file, "text-anchor=\"end\"", "\0");  
  for(int i = 0; i < pd->n_slices; i++)
  {
    radians = 2   * (pd->slices[i].percentage / 2 + sum_counter) * PI;
    sum_counter     += pd->slices[i].percentage;
    x_pointer_start = cos(radians) * radius + origin[0];
    y_pointer_start = sin(radians) * radius + origin[1];
    current_pointer_len = (origin[0] < x_pointer_start) ? pointer_len : -pointer_len;

    grp_dat->cmp_1 = make_cmp_1(grp_dat, origin[0] < x_pointer_start);
    grp_dat->cmp_2 = make_cmp_2(grp_dat, origin[0] > x_pointer_start);
    print_group(grp_dat);

    fprintf(file, svg_text,
      x_pointer_start + current_pointer_len,
      y_pointer_start - pd->axel_data->axel_number_offset,
      pd->slices[i].name);
  }
  destroy_group_dat(grp_dat);
  fprintf(file, end_width);

  sum_counter = 0.0;

  s = 1;
  end_width = malloc(strlen(svg_group_stop));
  strcpy(end_width, svg_group_stop);

  ret = stringify("fill=\"#%02x%02x%02x\" dominant-baseline=\"hanging\"", 
    pd->axel_data->axel_rgb[0],
    pd->axel_data->axel_rgb[1],
    pd->axel_data->axel_rgb[2]);
  fprintf(file, svg_custom_group, ret);
  free(ret);
  
  grp_dat = init_group_dat(file, "text-anchor=\"end\"", "\0"); 
  for(int i = 0; i < pd->n_slices; i++)
  {
    radians = 2   * (pd->slices[i].percentage / 2 + sum_counter) * PI;
    sum_counter     += pd->slices[i].percentage;
    x_pointer_start = cos(radians) * radius + origin[0];
    y_pointer_start = sin(radians) * radius + origin[1];
    current_pointer_len = (origin[0] < x_pointer_start) ? pointer_len : -pointer_len;

    ret = stringify("%9.1f%%", pd->slices[i].percentage * 100);
    
    grp_dat->cmp_1 = make_cmp_1(grp_dat, origin[0] < x_pointer_start);
    grp_dat->cmp_2 = make_cmp_2(grp_dat, origin[0] > x_pointer_start);
    print_group(grp_dat);

    fprintf(file, svg_text,   
      x_pointer_start + current_pointer_len, 
      y_pointer_start + pd->axel_data->axel_number_offset, ret);

    free(ret);
  }
  destroy_group_dat(grp_dat);
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

void print_slice(FILE* file, struct pie_data* pd, float* origin, float* sum_counter, int i, float radius, float sum, uint8_t overlap)
{
  float percentage_overlap = ((i + 1 < pd->n_slices) && overlap) ? pd->slices[i + 1].percentage / 2 : 0;
  percentage_overlap = (percentage_overlap == 0 && sum == 1.0 && overlap) ? pd->slices[0].percentage / 2 : percentage_overlap;
  float radians[2];
  radians[0] = 2 * (*sum_counter)*PI;
  radians[1] = 2 * ((pd->slices[i].percentage + percentage_overlap) + (*sum_counter))*PI;
  *sum_counter   += pd->slices[i].percentage;
  uint8_t large_arc_flag = (pd->slices[i].percentage + percentage_overlap > 0.5) ? 1 : 0;

  float start[2], stop[2];
  start[0] = cos(radians[0]) * radius + origin[0];
  start[1] = sin(radians[0]) * radius + origin[1];
  stop[0] =  cos(radians[1]) * radius + origin[0];
  stop[1] =  sin(radians[1]) * radius + origin[1];

  pd->theme->percentage = (i + 1) / (pd->n_slices*1.0);

  get_gradient(pd->theme);

  fprintf(file, svg_slice,
    start[0],
    start[1],
    radius,
    radius,
    large_arc_flag,
    stop[0],
    stop[1],
    origin[0],
    origin[1],
    pd->theme->out_color_rgb[0],
    pd->theme->out_color_rgb[1],
    pd->theme->out_color_rgb[2]);
  return;
}

void pie(struct pie_data* pd)
{
  FILE* file;
  uint8_t large_arc_flag;
  float percentage_overlap, 
        radius, 
        origin[2], 
        radians[3], 
        start[2], 
        stop[2],
        origin_radius;

  origin_radius = 0.0;


  file = fopen(pd->general->file_name, "wb");
  print_top_header(file, pd->general);
  radius = (pd->general->viewport_y <= pd->general->viewport_x) ? (pd->general->viewport_y - pd->general->margin) / 2 : (pd->general->viewport_x - pd->general->margin) / 2;
  origin[0] = pd->general->viewport_x / 2.0 + pd->general->margin / 2.0;
  origin[1] = pd->general->viewport_y / 2.0 + pd->general->margin / 2.0;

  fprintf(file, svg_circle, origin[0], origin[1], origin_radius);

  float sum = 0.0;

  loop(pd->n_slices)
  {
    sum += pd->slices[i].percentage;
  }

  sum = roundf(sum * 100) / 100;

  print_font_size_group(file, pd->general);
  valid_pie_data(pd, sum)
  {
    float sum_counter;

    fprintf(file, svg_limiter_box);
    loop(pd->n_slices)
    {
      print_slice(file, pd, origin, &sum_counter, i, radius, sum, 1);
    }
    if(sum == 1.0)
    {
      sum_counter = 0.0;
      print_slice(file, pd, origin, &sum_counter, 0, radius, sum, 0);
    }
    print_slice_pointers(file, pd);
    fprintf(file, svg_group_stop);
  }
  fprintf(file, svg_group_stop);
  fprintf(file, svg_top_header_stop);
  fclose(file);
}
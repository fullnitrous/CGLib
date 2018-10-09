#include <stdio.h>
#include <stdint.h>

#ifndef C_GRAPH_LIB_OTHER
  #define C_GRAPH_LIB_OTHER
  
  static const char* svg_top_header_start = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?><svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" viewBox=\"0 0 %9.6f %9.6f\" stroke-width=\"%d\">";
  static const char* svg_top_header_stop = "</svg>";
  static const char* svg_points_group_start = "<g font-size=\"10\" text-anchor=\"start\" stroke-width=\"1\" stroke =\"#%02x%02x%02x\" fill=\"#%02x%02x%02x\">";
  static const char* svg_points_group_stop = "</g>";
  static const char* svg_point = "<circle cx=\"%9.6f\" cy=\"%9.6f\" r=\"2\"/>";
  static const char* svg_g_point = "<circle cx=\"%9.6f\" cy=\"%9.6f\" r=\"1\"/>";  
  static const char* svg_p_line_start = "<polyline fill=\"none\" stroke=\"#%02x%02x%02x\" points=\"";
  static const char* svg_p_line_stop = "\"/>";
  static const char* svg_line = "<line stroke = \"red\" x1=\"%9.6f\" y1=\"%9.6f\" x2=\"%9.6f\" y2=\"%9.6f\" stroke-opacity=\"0.5\"/>";
  static const char* svg_axel = "<line stroke = \"black\" x1=\"%9.6f\" y1=\"%9.6f\" x2=\"%9.6f\" y2=\"%9.6f\"/>";
  static const char* svg_slice = "<path d=\"M %9.6f %9.6f A %9.6f %9.6f 0 %d 1 %9.6f %9.6f L %9.6f %9.6f \" fill = \"#%02x%02x%02x\"></path>";
  static const char* svg_arc = "<path d=\"M %9.6f %9.6f A %9.6f %9.6f 0 %d 1 %9.6f %9.6f\" fill = \"none\" stroke = \"#%02x%02x%02x\"></path>";
  static const char* svg_box = "<rect fill=\"#%02x%02x%02x\" x=\"%9.6f\" y=\"%9.6f\" width=\"%9.6f\" height=\"%9.6f\"/>";
  static const char* svg_text = "<text x=\"%9.6f\" y=\"%9.6f\">%s</text>";
  static const char* svg_bd_text = "<text x=\"%9.6f\" y=\"%9.6f\">%s : %9.6f</text>";
  static const char* svg_p_line_point = "%9.6f, %9.6f ";

  uint8_t getRandByte(void);
  void draw_axis_horizontals(FILE* file, float x_axel_y_offset, float y_axel_x_offset, struct general_data* gd, struct axel_data* ad);  

#endif
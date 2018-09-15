#include <stdio.h>
#include <stdint.h>

#ifndef C_GRAPH_LIB_OTHER
  #define C_GRAPH_LIB_OTHER
  
  static const char* topHeaderFormat = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?><svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" viewBox=\"0 0 %9.6f %9.6f\" stroke-width=\"%d\"><rect stroke=\"none\" width=\"100%%\" height=\"100%%\" fill=\"#%02x%02x%02x\"/>";
  static const char* topHeaderFormatStop = "</svg>";
  static const char* pointsGroupStart = "<g font-size=\"10\" text-anchor=\"start\" stroke-width=\"1\" stroke =\"#%02x%02x%02x\" fill=\"#%02x%02x%02x\">";
  static const char* pointsGroupStop = "</g>";
  static const char* point = "<circle cx=\"%9.6f\" cy=\"%9.6f\" r=\"2\"/>";
  static const char* gpoint = "<circle cx=\"%9.6f\" cy=\"%9.6f\" r=\"1\"/>";  
  static const char* axel = "<polyline fill=\"none\" points=\"%9.6f, %9.6f %9.6f, %9.6f \" stroke = \"#%02x%02x%02x\"/>";
  static const char* lineStart = "<polyline fill=\"none\" stroke=\"#%02x%02x%02x\" points=\"";
  static const char* lineEnd = "\"/>";
  static const char* slice = "<path d=\"M %9.6f %9.6f A %9.6f %9.6f 0 %d 1 %9.6f %9.6f L %9.6f %9.6f \" fill = \"#%02x%02x%02x\" fill-opacity = \"%9.6f\"></path>";
  static const char* arc = "<path d=\"M %9.6f %9.6f A %9.6f %9.6f 0 %d 1 %9.6f %9.6f\" fill = \"none\" stroke = \"#%02x%02x%02x\"></path>";
  static const char* box = "<rect fill=\"#%02x%02x%02x\" x=\"%9.6f\" y=\"%9.6f\" width=\"%9.6f\" height=\"%9.6f\" stroke=\"#%02x%02x%02x\" fill-opacity=\"%9.6f\"/>";
  static const char* text = "<text x=\"%9.6f\" y=\"%9.6f\">%s</text>";
  static const char* bdText = "<text x=\"%9.6f\" y=\"%9.6f\">%s : %9.6f</text>";

  void WW(FILE* file, const char* format, ...);
  uint8_t getRandByte(void);

#endif
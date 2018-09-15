#include "grapher.h"

const char* topHeaderFormat = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?><svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" viewBox=\"0 0 %9.6f %9.6f\" stroke-width=\"%d\"><rect stroke=\"none\" width=\"100%%\" height=\"100%%\" fill=\"#%02x%02x%02x\"/>";
const char* topHeaderFormatStop = "</svg>";
const char* pointsGroupStart = "<g font-size=\"10\" text-anchor=\"start\" stroke-width=\"1\" stroke =\"#%02x%02x%02x\" fill=\"#%02x%02x%02x\">";
const char* pointsGroupStop = "</g>";
const char* point = "<circle cx=\"%9.6f\" cy=\"%9.6f\" r=\"2\"/>";
const char* gpoint = "<circle cx=\"%9.6f\" cy=\"%9.6f\" r=\"1\"/>";  
const char* axel = "<polyline fill=\"none\" points=\"%9.6f, %9.6f %9.6f, %9.6f \" stroke = \"#%02x%02x%02x\"/>";
const char* lineStart = "<polyline fill=\"none\" stroke=\"#%02x%02x%02x\" points=\"";
const char* lineEnd = "\"/>";
const char* slice = "<path d=\"M %9.6f %9.6f A %9.6f %9.6f 0 %d 1 %9.6f %9.6f L %9.6f %9.6f \" fill = \"#%02x%02x%02x\" fill-opacity = \"%9.6f\"></path>";
const char* arc = "<path d=\"M %9.6f %9.6f A %9.6f %9.6f 0 %d 1 %9.6f %9.6f\" fill = \"none\" stroke = \"#%02x%02x%02x\"></path>";
const char* box = "<rect fill=\"#%02x%02x%02x\" x=\"%9.6f\" y=\"%9.6f\" width=\"%9.6f\" height=\"%9.6f\" stroke=\"#%02x%02x%02x\" fill-opacity=\"%9.6f\"/>";
const char* text = "<text x=\"%9.6f\" y=\"%9.6f\">%s</text>";
const char* bdText = "<text x=\"%9.6f\" y=\"%9.6f\">%s : %9.6f</text>";

void WW(FILE* file, const char* format, ...)
{
  va_list args;
  va_start(args, format);
  int size = vsnprintf(NULL, 0, format, args);
  va_end(args);
  char* ret = malloc(sizeof(char) * (size + 1));
  va_start(args, format);
  vsnprintf(ret, size, format, args);
  ret[size] = '\0';
  fwrite(ret, size, 1, file);
  free(ret);
  return;
}

uint8_t getRandByte(void)
{
  return rand();
}

void graph(GraphData* gd)
{
  float margin = gd->margin;
  
  FILE* file = fopen(gd->fileName, "wb");

  WW(file, topHeaderFormat, 
    gd->viewportX + margin, gd->viewportY + margin, 
    gd->strokeWidth,
    gd->bgRGBA[0],
    gd->bgRGBA[1],
    gd->bgRGBA[2]); 

  gd->viewportY -= 40 * gd->nLines;

  WW(file, pointsGroupStart,
    gd->axelRGBA[0],
    gd->axelRGBA[1],
    gd->axelRGBA[2],
    gd->axelRGBA[0],
    gd->axelRGBA[1],
    gd->axelRGBA[2]);

  float yAxelxOffset = gd->viewportX * gd->quadPercent[0];
  float xAxelyOffset = gd->viewportY * gd->quadPercent[1];

  int n1 = gd->viewportX / gd->xInterval;

  float counter = margin / 2.0;
  float add     = (gd->viewportX) / (n1 * 1.0);

  //x axel
  for(int i = 0; i < n1 - 1; i++)
  {
    counter += add;
    WW(file, point, counter, gd->viewportY + margin / 2.0 - xAxelyOffset);
  }

  //y axel
  int n2  = gd->viewportY / gd->yInterval;
  counter = margin / 2.0;
  add = (gd->viewportY) / (n2 * 1.0);
  for(int i = 0; i < n2 - 1; i++)
  {
    counter += add;
    WW(file, point, margin / 2.0 + yAxelxOffset, counter);
  }

  WW(file, pointsGroupStop);

  //yaxel
  WW(file, axel,
    margin / 2.0 + yAxelxOffset, //x
    margin / 2.0, //y
    margin / 2.0 + yAxelxOffset, //x
    gd->viewportY + margin / 2.0,//y
    gd->axelRGBA[0],
    gd->axelRGBA[1],
    gd->axelRGBA[2]);

  //xaxel
  WW(file, axel,
    margin / 2.0, //x
    gd->viewportY + margin / 2.0 - xAxelyOffset, //y
    gd->viewportX + margin / 2.0, //x
    gd->viewportY + margin / 2.0 - xAxelyOffset, //y
    gd->axelRGBA[0],
    gd->axelRGBA[1],
    gd->axelRGBA[2]);
  
  //lines
  
  char* format;

  float step2 = 40.0;
  
  float yOffset = gd->viewportY;

  float xLegendOffset = 20.0;

  float count = step2;


  for(int i = 0; i < gd->nLines; i++)
  {
    float x = margin * 2;
    float y = yOffset + count;
    
    x += xLegendOffset;

    //add legend here

    WW(file, text,
      x,
      y,
      gd->lines[i].name // add later
      );
    count += step2;

    if(gd->lines[i].graphType == 0)
    {
      format = malloc(strlen("%9.6f, %9.6f "));
      strcpy(format, "%9.6f, %9.6f ");
      WW(file, lineStart, 
        gd->lines[i].strokeRGBA[0], 
        gd->lines[i].strokeRGBA[1], 
        gd->lines[i].strokeRGBA[2]);
    }
    else
    {
      format = malloc(strlen(gpoint));
      strcpy(format, gpoint);
      WW(file, pointsGroupStart,
        gd->lines[i].strokeRGBA[0], 
        gd->lines[i].strokeRGBA[1], 
        gd->lines[i].strokeRGBA[2],
        gd->lines[i].strokeRGBA[0],     
        gd->lines[i].strokeRGBA[1], 
        gd->lines[i].strokeRGBA[2]);
    }
    for(int k = 0; k < gd->lines[i].points; k++)
    {
      float x = margin / 2.0 + gd->lines[i].line[k].x * gd->xInterval + yAxelxOffset;
      float y = gd->viewportY - gd->lines[i].line[k].y * gd->yInterval + margin / 2.0 - xAxelyOffset;

      if(gd->viewportX >= x && 0 <= x && gd->viewportY >= y && 0 <= y)
      {
        WW(file, format, x, y);
      }
    }
    if(gd->lines[i].graphType == 0)
    {
      WW(file, lineEnd);
    }
    else
    {
      WW(file, pointsGroupStop);
    }
  }

  free(format);

  //generates the svg header stop
  WW(file, topHeaderFormatStop);
  
  fclose(file);
  return;
}

void pie(PieData* pd)
{
  FILE* file = fopen(pd->fileName, "wb");

  float margin = pd->margin;

  WW(file, topHeaderFormat, 
    pd->viewportX + margin, pd->viewportY + margin, 
    pd->strokeWidth,
    pd->bgRGBA[0],
    pd->bgRGBA[1],
    pd->bgRGBA[2]);

  pd->viewportX -= 200;

  float radius = (pd->viewportX - margin) / 2;
  float origin[2];
  origin[0] = pd->viewportX / 2.0 + margin / 2.0;
  origin[1] = pd->viewportY / 2.0 + margin / 2.0;

  float sum = 0.0;
  
  for(int i = 0; i < pd->nSlices; i++)
  {
    sum += pd->slices[i].percentage;
  }

  uint8_t largeArcFlag;

  if(sum == 1.0)
  {
    float sumSoFar = 0.0;

    for(int i = 0; i < pd->nSlices; i++)
    {
      if(pd->slices[i].percentage > 0.5)
      {
        largeArcFlag = 1;
      }
      else
      {
        largeArcFlag = 0;
      }

      double radians1 = 2 * sumSoFar * PI;
      double radians2 = 2 * (pd->slices[i].percentage + sumSoFar) * PI;

      sumSoFar += pd->slices[i].percentage;

      double xStart = cos(radians1) * radius + pd->viewportX / 2.0 + margin / 2.0;
      double yStart = sin(radians1) * radius + pd->viewportY / 2.0 + margin / 2.0;
      double xStop  = cos(radians2) * radius + pd->viewportX / 2.0 + margin / 2.0;
      double yStop  = sin(radians2) * radius + pd->viewportY / 2.0 + margin / 2.0;
      
      uint8_t RGB[3];
      RGB[0] = getRandByte();
      RGB[1] = getRandByte();
      RGB[2] = getRandByte();

      WW(file, slice,
        xStart,
        yStart,
        radius,
        radius,
        largeArcFlag,
        xStop,
        yStop,
        origin[0],
        origin[1],
        RGB[0],
        RGB[1],
        RGB[2],
        0.75);

      WW(file, arc,
        xStart,
        yStart,
        radius,
        radius,
        largeArcFlag,
        xStop,
        yStop,
        RGB[0],
        RGB[1],
        RGB[2]);
    }
  }
  else
  {
    printf("error slices do not add up to 100%%, but %9.6f%%\n", sum);
  }

  WW(file, topHeaderFormatStop);

  fclose(file);
}

void bar(BarData* bd)
{
  FILE* file = fopen(bd->fileName, "wb");
  
  float margin = bd->margin;

  WW(file, topHeaderFormat, 
    bd->viewportX + margin, bd->viewportY + margin, 
    bd->strokeWidth,
    bd->bgRGBA[0],
    bd->bgRGBA[1],
    bd->bgRGBA[2]);



  WW(file, pointsGroupStart,
    bd->axelRGBA[0],
    bd->axelRGBA[1],
    bd->axelRGBA[2],
    bd->axelRGBA[0],
    bd->axelRGBA[1],
    bd->axelRGBA[2]);

  bd->viewportY -= 40 * bd->nBars;

  float yAxelxOffset = bd->viewportX;
  float xAxelyOffset = bd->viewportY;

  //y axel
  int n2  = bd->viewportY / bd->yInterval;
  float counter = margin / 2.0;
  float add = (bd->viewportY) / (n2 * 1.0);
  for(int i = 0; i < n2 - 1; i++)
  {
    counter += add;
    WW(file, point, margin / 2.0, counter);
  }

  WW(file, pointsGroupStop);



  
  //yaxel
  WW(file, axel,
    margin / 2.0, //x
    margin / 2.0, //y
    margin / 2.0, //x
    bd->viewportY + margin / 2.0,//y
    bd->axelRGBA[0],
    bd->axelRGBA[1],
    bd->axelRGBA[2]);

  //xaxel
  WW(file, axel,
    margin / 2.0, //x
    bd->viewportY + margin / 2.0, //y
    bd->viewportX + margin / 2.0, //x
    bd->viewportY + margin / 2.0, //y
    bd->axelRGBA[0],
    bd->axelRGBA[1],
    bd->axelRGBA[2]);

  float barSection = 1 / bd->nBars;
  
  float step = bd->viewportX / (bd->nBars + 1);

  float step2 = 40.0;

  float prev = step;

  float yOffset = bd->viewportY;

  float xLegendOffset = 20.0;

  float count = step2;

  for(int i = 0; i < bd->nBars; i++)
  {
    float yPercent = bd->bars[i].value / bd->yMax;

    float width  = (bd->standardRatio * (bd->viewportX / bd->nBars));
    float height = (yPercent * bd->viewportY) / bd->yInterval;

    float y = margin / 2.0 + bd->viewportY - height;

    uint8_t RGB[3];
    RGB[0] = rand();
    RGB[1] = rand();
    RGB[2] = rand();

    float x = prev + margin / 2.0 - width / 2.0;

    prev += step;

    WW(file, box,
      RGB[0],
      RGB[1],
      RGB[2],
      x,
      y,
      width,
      height,
      RGB[0],
      RGB[1],
      RGB[2],
      0.6);

    x = margin * 2;
    y = yOffset + count;

    WW(file, box,
      RGB[0],
      RGB[1],
      RGB[2],
      x,
      y,
      5.0,
      5.0,
      RGB[0],
      RGB[1],
      RGB[2],
      0.6);
    
    x += xLegendOffset;

    WW(file, bdText,
      x,
      y,
      bd->bars[i].name,
      bd->bars[i].value);
    count += step2;
  }

  WW(file, topHeaderFormatStop);
  return;
} 
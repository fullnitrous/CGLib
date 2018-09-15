#include "cgraphlib.h"
#include "cgraphlib-other.h"

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
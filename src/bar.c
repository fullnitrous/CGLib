#include "cgraphlib.h"
#include "cgraphlib-other.h"

/*
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

  //bd->viewportY -= 40 * bd->nBars;

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
      RGB[2]);

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
      RGB[2]);
    
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
*/
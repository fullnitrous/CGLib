#include "cgraphlib.h"
#include "cgraphlib-other.h"

/*
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

  if(roundf(sum * 100) / 100 == 1.0)
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
        1.0);
    }
  }
  else
  {
    printf("error slices do not add up to 100%%, but %9.6f%%\n", sum);
  }

  WW(file, topHeaderFormatStop);

  fclose(file);
}
*/
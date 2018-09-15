#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sdb-dge/svg-grapher/grapher.h"

int main(void)
{
  GraphData* gp = malloc(sizeof(GraphData));

  gp->fileName = malloc(sizeof(char) * 12);
  strcpy(gp->fileName, "bin/graph.svg");

  gp->margin = 20;

  gp->nLines = 2;
  gp->lines = malloc(sizeof(Line) * 2);

  gp->lines[0].points = 80;
  gp->lines[1].points = 80;

  gp->lines[0].line = malloc(sizeof(Line) * gp->lines[0].points);
  gp->lines[0].line = malloc(sizeof(Line) * gp->lines[0].points);
  gp->lines[1].line = malloc(sizeof(Line) * gp->lines[1].points);
  gp->lines[1].line = malloc(sizeof(Line) * gp->lines[1].points);

  float count = -20;
  for(int i = -40; i < 40; i++)
  {
    count += 0.5;
    gp->lines[0].line[i + 40].x = count;
    gp->lines[0].line[i + 40].y = count * count;
  }

  count = -20;
  for(int i = -40; i < 40; i++)
  {
    count += 0.5;
    gp->lines[1].line[i + 40].x = count;
    gp->lines[1].line[i + 40].y = -count * count;
  }

  gp->viewportX = 500.0;
  gp->viewportY = 500.0;

  gp->xInterval = 25;
  gp->yInterval = 10;

  gp->lines[0].graphType = 0;
  gp->lines[1].graphType = 1;

  gp->lines[0].name = malloc(4);
  strcpy(gp->lines[0].name, "x^2");

  gp->lines[1].name = malloc(5);
  strcpy(gp->lines[1].name, "-x^2");

  gp->lines[0].strokeRGBA[0] = 255;
  gp->lines[0].strokeRGBA[1] = 45;
  gp->lines[0].strokeRGBA[2] = 40;

  gp->lines[1].strokeRGBA[0] = 200;
  gp->lines[1].strokeRGBA[1] = 200;
  gp->lines[1].strokeRGBA[2] = 90;

  gp->bgRGBA[0] = 30;
  gp->bgRGBA[1] = 30;
  gp->bgRGBA[2] = 30;

  gp->axelRGBA[0] = 60;
  gp->axelRGBA[1] = 60;
  gp->axelRGBA[2] = 60;  

  gp->quadPercent[0] = 0.3;
  gp->quadPercent[1] = 0.3;

  gp->strokeWidth = 2;

  graph(gp);

  free(gp);






  PieData* pd = malloc(sizeof(PieData));
  pd->fileName = malloc(sizeof(char) * 12);
  strcpy(pd->fileName, "bin/pie.svg");

  pd->margin = 20;

  pd->viewportX = 500.0;
  pd->viewportY = 300.0;

  pd->bgRGBA[0] = 30;
  pd->bgRGBA[1] = 30;
  pd->bgRGBA[2] = 30;

  pd->strokeWidth = 10;

  pd->nSlices = 3;
  pd->slices = malloc(sizeof(PieSlice) * pd->nSlices);

  pd->slices[0].percentage = 0.48;
  pd->slices[1].percentage = 0.48;
  pd->slices[2].percentage = 0.04;

  pie(pd);

  free(pd);













  BarData* bd = malloc(sizeof(BarData));
  bd->fileName = malloc(sizeof(char) * 12);
  strcpy(bd->fileName, "bin/bar.svg");

  bd->margin = 20;

  bd->viewportX = 500.0;
  bd->viewportY = 500.0;

  bd->yMax = 500;

  bd->yInterval = 1;

  bd->bgRGBA[0] = 30;
  bd->bgRGBA[1] = 30;
  bd->bgRGBA[2] = 30;

  bd->axelRGBA[0] = 60;
  bd->axelRGBA[1] = 60;
  bd->axelRGBA[2] = 60;  

  bd->strokeWidth = 2;

  bd->nBars = 6;
  bd->bars = malloc(sizeof(Bar) * bd->nBars);
  
  bd->bars[0].value = 500.0;
  bd->bars[0].name = malloc(4);
  strcpy(bd->bars[0].name, "one");

  bd->bars[1].value = 400.0;
  bd->bars[1].name = malloc(4);
  strcpy(bd->bars[1].name, "two");

  bd->bars[2].value = 300.0;
  bd->bars[2].name = malloc(6);
  strcpy(bd->bars[2].name, "three");

  bd->bars[3].value = 200.0;
  bd->bars[3].name = malloc(4);
  strcpy(bd->bars[3].name, "one");

  bd->bars[4].value = 100.0;
  bd->bars[4].name = malloc(4);
  strcpy(bd->bars[4].name, "two");

  bd->bars[5].value = 100.0;
  bd->bars[5].name = malloc(6);
  strcpy(bd->bars[5].name, "three");
  
  bd->standardRatio = (1.0 / 3.0);

  bar(bd);

  free(bd);

  
  printf("done...\n");

  return 0;
}
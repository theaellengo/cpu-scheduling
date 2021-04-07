#include "process.h"
#include <math.h>
#include <stdio.h>

void printprocess(Process process[], int n, float awt);
int getnumdigits(int num);

void printprocess(Process process[], int n, float awt)
{
  printf("\nProcess   Arrival   Burst   Start   End   Waiting   Turnaround\n");
  for (int i = 0; i < n; i++) {
    printf("%d%*c", process[i].pid, 9 - getnumdigits(process[i].pid), ' ');
    printf("%d%*c", process[i].arrival, 9 - getnumdigits(process[i].arrival), ' ');
    printf("%d%*c", process[i].burst, 7 - getnumdigits(process[i].burst), ' ');
    printf("%d%*c", process[i].start, 7 - getnumdigits(process[i].start), ' ');
    printf("%d%*c", process[i].completion, 5 - getnumdigits(process[i].completion), ' ');
    printf("%d%*c", process[i].waiting, 9 - getnumdigits(process[i].waiting), ' ');
    printf("%d\n", process[i].turnaround);
  }
  printf("-----------------------------------------------");
  printf("\nAverage Waiting Time: %.1f\n\n", awt);
}

int getnumdigits(int num)
{
  return (num == 0) ? 0 : floor(log10(num));
}
#include "display.h"
#include "process.h"
#include <stdio.h>

void nsjf(Process process[], int n)
{
  // init values
  Process queue[n];
  int clock = 0, idx = 0;
  float awt = 0;

  // while all slices not in queue
  while (idx < n) {
    int sum = 0;
    int flag = 0;

    int s = getshortestburst(process, n, clock);
    // if process has arrived and has not finsihed execution
    if (process[s].arrival <= clock && process[s].exectime > 0 && s >= 0) {
      flag = 1;
      queue[idx] = process[s];

      setprocess(&queue[idx], &clock, queue[idx].burst);

      // if process is done executing, add process waiting time to awt
      awt += queue[idx].waiting;
      sum += queue[idx].burst;
      process[s].exectime -= queue[idx].burst;
      idx++;
    }
    if (flag == 0) {
      clock++;
      sum++;
    }
    for (int j = 0; j < n; j++) {
      process[j].arrtime -= sum;
    }
  }

  awt /= n;
  printgnatt(queue, n);
  printprocess(process, n, queue, idx, awt);
}
#include "display.h"
#include "process.h"
#include <stdio.h>

void fcfs(Process process[], int n)
{
  Process queue[n];
  int clock = 0, idle = 0, idx = 0;
  float awt = 0;

  // while all processes not in queue
  while (idx < n) {
    for (int i = 0; i < n; i++) {
      if (process[i].arrtime <= 0 && process[i].exectime > 0) {
        // set to current process
        queue[idx] = process[i];

        // add idle time to clock
        if (clock - idle < 0) clock += idle - clock;

        // update and set values
        setprocess(&queue[idx], &clock, queue[idx].burst);
        process[i].exectime -= queue[idx].burst;
        awt += queue[idx].waiting;
        idx++;
      }
      process[i].arrtime--;
    }
    idle++;
  }

  awt /= n;
  printgnatt(queue, n);
  printprocess(queue, n, awt);
}
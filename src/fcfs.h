#include "display.h"
#include "process.h"
#include <stdio.h>

void fcfs(Process process[], int n)
{
  Process queue[n];
  int clock = 0;
  int count = 0;
  int idx = 0;
  float awt = 0;

  // while all processes not in queue
  while (idx < n) {
    for (int i = 0; i < n; i++) {
      if (process[i].arrtime <= 0 && process[i].exectime > 0) {
        // set tail to current process
        queue[idx] = process[i];

        // add idle time to clock
        if (clock - count < 0) clock += count - clock;

        // update and set values
        setprocess(&queue[idx], &clock, queue[idx].burst);
        process[i].exectime -= queue[idx].burst;
        awt += queue[idx].waiting;
        idx++;
      }
      process[i].arrtime--;
    }
    count++;
  }

  awt /= n;
  printgnatt(queue, n);
  printprocess(queue, n, awt);
}
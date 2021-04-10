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
    int sum = 0;
    for (int i = 0; i < n; i++) {
      if (process[i].arrtime <= 0 && process[i].exectime > 0) {

        // set head to current process
        queue[idx] = process[i];

        // add idle time to clock
        int idle = 0;
        while (queue[idx].waiting < 0) {
          idle++;
          clock++;
          queue[idx].waiting++;
        }

        // update and set values
        setprocess(&queue[idx], &clock, queue[idx].burst);
        process[i].exectime -= queue[idx].burst;
        awt += queue[idx].waiting;
        idx++;
      }
      process[i].arrtime--;
    }
    clock++;
    // subtract execution time from all processes
    for (int j = 0; j < n; j++) {
      process[j].arrtime -= sum;
    }
  }

  awt /= n;
  printgnatt(queue, n);
  printprocess(queue, n, awt);
}
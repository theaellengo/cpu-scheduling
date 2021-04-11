#include "display.h"
#include "process.h"
#include <stdio.h>

void nsjf(Process process[], int n)
{
  // init values
  Process queue[n];
  int clock = 0;
  int idx = 0;
  float awt = 0;

  // while all slices not in queue
  while (idx < n) {
    int sum = 0; // total execution time
    int flag = 0;
    sortbyburst(process, n);
    for (int i = 0; i < n; i++) {
      // if process has arrived and has not finsihed execution
      if (process[i].arrtime <= 0 && process[i].exectime > 0) {
        flag = 1;
        queue[idx] = process[i];

        // if remaining burst time > timeslice, execute process for timeslice units
        setprocess(&queue[idx], &clock, queue[idx].burst);

        // if process is done executing, add process waiting time to awt
        if (queue[idx].exectime <= 0) awt += queue[idx].waiting;

        sum += queue[idx].burst;
        process[i].exectime -= queue[idx].burst;
        process[i].arrtime = queue[idx].burst + 1;
        idx++;
      }
    }
    if (flag == 0) {
      clock++;
      sum++;
    }
    // subtract execution time from all processes
    for (int j = 0; j < n; j++) {
      process[j].arrtime -= sum;
    }
  }

  awt /= n;
  printgnatt(queue, n);
  printprocess(queue, n, awt);
}
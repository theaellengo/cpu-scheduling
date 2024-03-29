#include "display.h"
#include "process.h"
#include <math.h>
#include <stdio.h>

void rr(Process process[], int n, int timeslice)
{
  // calculate size of queue (amount of context switches)
  int qsize = 0;
  for (int i = 0; i < n; i++) {
    qsize += floor(process[i].burst / timeslice);
    qsize += (process[i].burst % timeslice != 0 ? 1 : 0);
  }

  // init values
  Process queue[qsize];
  int clock = 0, idx = 0, last = -1;
  float awt = 0;

  // while all slices not in queue
  while (idx < qsize) {
    int sum = 0; // total execution time
    int flag = 0;

    int s = getshortestarrival(process, n);
    if (process[s].arrtime <= 0 && process[s].exectime > 0 && s >= 0) {
      flag = 1;
      queue[idx] = process[s];

      // if remaining burst time > timeslice, execute process for timeslice units
      int exectime = (queue[idx].exectime > timeslice) ? timeslice : queue[idx].exectime;
      setprocess(&queue[idx], &clock, exectime);

      // if process is done executing, add process waiting time to awt
      if (queue[idx].exectime <= 0) awt += queue[idx].waiting;

      sum += exectime;
      process[s].exectime -= exectime;
      process[s].arrtime = exectime;
      last = process[s].pid;

      // add to end of queue
      Process temp = process[s];
      for (int j = s; j < n - 1; j++)
        process[j] = process[j + 1];
      process[n - 1] = temp;

      idx++;
    }
    if (flag == 0) {
      clock++;
      sum++;
    }
    // subtract execution time from all processes
    for (int i = 0; i < n; i++) {
      process[i].arrtime -= sum;
    }
  }

  awt /= n;
  printgnatt(queue, idx);
  printprocess(process, n, queue, idx, awt);
}

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
  int clock = 0;
  int arrival = 0;
  int idx = 0;
  float awt = 0;

  printlabel("\nGnatt Chart:\n");

  // while all slices not in queue
  while (idx < qsize) {
    for (int i = 0; i < n; i++) {
      // if process has arrived and has not finsihed execution
      if (process[i].arrival == 0 && process[i].burst > 0) {
        queue[idx] = process[i];
        if (clock - arrival < 0) clock -= clock - arrival; // idle

        int burst = (queue[idx].burst > 4) ? timeslice : queue[idx].burst;
        setrr(&queue[idx], &clock, arrival, burst);
        printgnatt(queue[idx]);

        process[i].burst -= burst;
        awt += queue[idx].waiting;
        idx++;
      } else {
        process[i].arrival--;
      }
    }
    arrival++;
  }

  awt /= qsize;
  printprocess(queue, qsize, awt);
}
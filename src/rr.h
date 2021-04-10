#include "display.h"
#include "process.h"
#include <math.h>
#include <stdio.h>

void sortbyarrival(Process process[], int n);

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
  int idx = 0;
  float awt = 0;

  // while all slices not in queue
  while (idx < qsize) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
      // if process has arrived and has not finsihed execution
      if (process[i].arrtime <= 0 && process[i].exectime > 0) {
        queue[idx] = process[i];
        int exectime = (queue[idx].exectime > timeslice) ? timeslice : queue[idx].exectime;

        setprocess(&queue[idx], &clock, exectime);
        int idle = 0;
        while (queue[idx].waiting < 0) {
          idle++;
          clock++;
          setprocess(&queue[idx], &clock, 1);
        } //idle time

        sum += exectime + idle;
        process[i].exectime -= exectime;
        process[i].arrtime = exectime + 1;
        awt += queue[idx].waiting;
        idx++;
      }
      process[i].arrtime--;
    }
    // subtract execution time from all processes
    for (int j = 0; j < n; j++)
      process[j].arrtime -= sum;
    sortbyarrival(process, n);
  }

  awt /= qsize;
  printgnatt(queue, qsize);
  printprocess(queue, qsize, awt);
}

void sortbyarrival(Process process[], int n)
{
  Process temp;
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      if (process[i].arrtime > process[j].arrtime) {
        temp = process[i];
        process[i] = process[j];
        process[j] = temp;
      }
}
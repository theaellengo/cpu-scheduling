#include "display.h"
#include "process.h"
#include <stdio.h>

void fcfs(Process process[], int n)
{
  Process queue[n];
  int clock = 0;
  int arrival = 0;
  int idx = 0;
  float awt = 0;

  printlabel("\nGnatt Chart:\n");

  // while all processes not in queue
  while (idx < n) {
    for (int i = 0; i < n; i++) {
      if (process[i].arrival == 0) {
        queue[idx] = process[i];
        if (clock - arrival < 0) {
          clock -= clock - arrival;
          printf("[///] "); // idle time
        }
        setprocess(&queue[idx], &clock, arrival);
        printgnatt(queue[idx]);
        awt += queue[idx].waiting;
        idx++;
      }
      process[i].arrival--;
    }
    arrival++; // arrival time of process == 0
  }

  awt /= n; // average waiting time = total waiting time / num processes
  printprocess(queue, n, awt);
}
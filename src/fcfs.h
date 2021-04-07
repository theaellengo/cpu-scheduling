#include "display.h"
#include "process.h"
#include <stdio.h>

void fcfs(Process process[], int n);
int setprocess(Process* process, int clock, int arrival);

void fcfs(Process process[], int n)
{
  Process queue[n];
  int clock, idx, arrival = 0;
  float awt = 0;

  // while all processes not in queue
  while (idx < n) {
    for (int i = 0; i < n; i++) {
      if (process[i].arrival == 0) {
        queue[idx] = process[i];
        while (clock - arrival < 0) {
          clock++; // idle time
        }
        clock = setprocess(&queue[idx], clock, arrival);
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

int setprocess(Process* process, int clock, int arrival)
{
  process->arrival = arrival;
  // start time
  process->start = clock;
  // completion start time + execution time
  process->completion = process->start + process->burst;
  // turnaround = completion time - arrival time
  process->turnaround = process->completion - arrival;
  // waiting = (tunraround - burst) || (start - arrival)
  process->waiting = process->turnaround - process->burst;

  return clock += process->burst;
}
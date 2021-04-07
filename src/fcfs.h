#include "process.h"
#include <stdio.h>

void fcfs(Process process[], int n);
int setprocess(Process* process, int clock, int arrival);
void printprocess(Process process[], int n, float awt);

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
        do {
          clock = setprocess(&queue[idx], clock, arrival);
        } while (queue[idx].waiting < 0); // idle time
        awt += queue[idx].waiting;
        clock += queue[idx].burst;
        idx++;
      }
      process[i].arrival--;
    }
    arrival++; // arrival time of process == 0
  }
  awt /= n;
  printprocess(queue, n, awt);
}

int setprocess(Process* process, int clock, int arrival)
{
  process->arrival = arrival;
  // start time
  process->start = clock;
  // start time + execution time
  process->completion = process->start + process->burst;
  // completion time - arrival time
  process->turnaround = process->completion - arrival;
  // start time - arrival time
  process->waiting = process->turnaround - process->burst;
  if (process->waiting < 0) clock++;
  return clock;
}

void printprocess(Process process[], int n, float awt)
{
  printf("\nProcess   Arrival   Burst   Start   End   Waiting   Turnaround\n");
  for (int j = 0; j < n; j++) {
    printf("%d%*c", process[j].pid, 9 - (process[j].pid / 10), ' ');
    printf("%d%*c", process[j].arrival, 9 - (process[j].arrival / 10), ' ');
    printf("%d%*c", process[j].burst, 7 - (process[j].burst / 10), ' ');
    printf("%d%*c", process[j].start, 7 - (process[j].start / 10), ' ');
    printf("%d%*c", process[j].completion, 5 - (process[j].completion / 10), ' ');
    printf("%d%*c", process[j].waiting, 9 - (process[j].waiting / 10), ' ');
    printf("%d\n", process[j].turnaround);
  }
  printf("-----------------------------------------------");
  printf("\nAverage Waiting Time: %.1f\n\n", awt);
}
#include <stdio.h>
#include "process.h"

void fcfs(Process process[], int n) {
  Process queue[n];
  int clock = 0;
  int idx = 0;
  int arrival = 0;

  // while all processes not in queue
  while (idx < n) {
    for (int i = 0; i < n; i++) {
      if (process[i].arrival == 0) {
        // start time
        process[i].start = clock;
        // start time + execution time
        process[i].completion = process[i].start + process[i].burst;
        // completion time - arrival time
        process[i].turnaround = process[i].completion - arrival;
        // start time - arrival time
        process[i].waiting = process[i].turnaround - process[i].burst;

        while (process[i].waiting < 0) {
          clock++;
          process[i].waiting++;
        }

        queue[idx] = process[i];
        clock += process[i].burst;
        idx++;
      }
      process[i].arrival--;
    }
    arrival++;  // arrival time of process == 0
  }

  // print processes
  float twt = 0;
  for (int i = 0; i < n; i++) {
    printf("P[%d]\n", queue[i].pid);
    printf("Start Time: %d\t End Time: %d\n", queue[i].start,
           queue[i].completion);
    printf("Waiting Time: %d\n", queue[i].waiting);
    printf("Turnaround Time: %d\n", queue[i].turnaround);
    printf("************************************\n");
    twt += queue[i].waiting;
  }
  printf("Average Waiting Time: %.1f\n", twt / n);
}
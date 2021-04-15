#include "process.h"
#include <limits.h>
#include <stdio.h>

Process execute(Process smallest, int clock, int exectime, float* awt);

void psjf(Process process[], int n)
{
  // initialize values
  sortbyburst(process, n);
  Process queue[process[n - 1].burst * n];
  Process smallest = { .pid = -1 };
  int rpro = n, clock = 0, idx = 0, exectime = 0, idle = 1;
  float awt = 0;

  sortbyarrival(process, n);
  while (rpro != 0) {
    int flag = 0;
    int sum = 0;

    int s = getshortestburst(process, n, clock);
    if (process[s].arrival <= clock && process[s].exectime > 0 && s >= 0) {
      flag = 1;
      // if current process has the smallest burst time
      if (process[s].pid == smallest.pid) {
        exectime++;
      } else {
        // if cpu was not idle
        if (exectime != 0 && idle != 1) {
          queue[idx++] = execute(smallest, clock, exectime, &awt);
        }
        idle = 0;
        exectime = 1;
        smallest = process[s];
      }
      process[s].exectime--;
      if (process[s].exectime == 0) rpro--;
    }

    // if no process in queue
    if (flag == 0) {
      // if cpu was not idle
      if (idle == 0) {
        queue[idx++] = execute(smallest, clock, exectime, &awt);
        exectime = 0;
      } else {
        exectime++;
      }
      idle = 1;
    }

    clock++;
  }

  // execute last process
  queue[idx++] = execute(smallest, clock, exectime, &awt);

  awt /= n;
  printgnatt(queue, idx);
  printprocess(process, n, queue, idx, awt);
}

Process execute(Process smallest, int clock, int exectime, float* awt)
{
  clock -= exectime;
  setprocess(&smallest, &clock, exectime);
  if (smallest.exectime == 0) *awt += smallest.waiting;
  return smallest;
}
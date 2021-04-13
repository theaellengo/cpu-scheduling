#include "process.h"
#include <limits.h>
#include <stdio.h>

void psjf(Process process[], int n)
{
  // initialize values
  sortbyburst(process, n);
  Process queue[process[n - 1].burst * n];
  Process smallest;
  smallest.pid = INT_MAX;
  int rpro = n, clock = 0, idx = 0, exectime = 0, idle = 1;
  float awt = 0;

  while (rpro != 0) {
    int flag = 0;
    int sum = 0;

    sortbyburst(process, n);
    for (int i = 0; i < n; i++) {
      if (process[i].arrival <= clock && process[i].exectime > 0) {
        flag = 1;

        // if current process has the smallest burst time
        if (process[i].pid == smallest.pid) {
          exectime++;
        } else {
          queue[idx] = smallest;

          // if cpu was not idle
          if (exectime != 0 && idle != 1) {
            clock -= exectime; // start = clock - exectime
            setprocess(&queue[idx], &clock, exectime);
            if (queue[idx].exectime == 0) awt += queue[idx].waiting;
            idx++;
          }

          idle = 0;
          exectime = 1;
          smallest = process[i];
        }
        process[i].exectime--;
        if (process[i].exectime == 0) rpro--;
        break;
      }
    }

    // if no process in queue
    if (flag == 0) {
      // if cpu was not idle
      if (idle == 0) {
        queue[idx] = smallest;
        clock -= exectime;
        setprocess(&queue[idx], &clock, exectime);
        exectime = 0;
        idx++;
      } else {
        exectime++;
      }

      idle = 1;
    }

    clock++;
  }

  // execute last process
  queue[idx] = smallest;
  clock -= exectime;
  setprocess(&queue[idx], &clock, exectime);
  awt += queue[idx].waiting;
  idx++;

  awt /= n;
  printgnatt(queue, idx);
  printprocess(queue, idx, awt);
}
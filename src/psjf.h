#include "process.h"
#include <limits.h>
#include <stdio.h>

void psjf(Process process[], int n)
{
  // initialize values
  sortbyburst(process, n);

  Process queue[process[n - 1].burst * n];
  Process smallest = process[0];
  int rpro = n, clock = 0, idx = 0, exectime = 0;
  float awt = 0;
  int idle = 0;

  while (rpro != 0) {
    int flag = 0;
    int sum = 0;

    sortbyburst(process, n);
    for (int i = 0; i < n; i++) {
      if (process[i].arrival <= clock && process[i].exectime > 0) {
        flag = 1;

        if (process[i].pid == smallest.pid) {
          exectime++;
        } else {
          queue[idx] = smallest;
          if (exectime != 0 && idle != 1) {
            clock -= exectime;
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

    if (flag == 0) {
      if (idle == 0) {
        queue[idx] = smallest;
        clock -= exectime;
        setprocess(&queue[idx], &clock, exectime);
        exectime = -1;
        idx++;
      }
      exectime++;
      idle = 1;
    }

    clock++;
  }

  // execute remaining process
  queue[idx] = smallest;
  clock -= exectime;
  setprocess(&queue[idx], &clock, exectime);
  awt += queue[idx].waiting;
  idx++;

  awt /= n;
  printgnatt(queue, idx);
  printprocess(queue, idx, awt);
}
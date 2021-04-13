#include "process.h"
#include <limits.h>
#include <stdio.h>

void psjf(Process process[], int n)
{
  // initialize values
  sortbyburst(process, n);
  for (int i = 0; i < n; i++) {
    printf("P%d\t%d\t%d\n", process[i].pid, process[i].burst, process[i].arrtime);
  }

  Process queue[process[n - 1].burst * n];
  Process smallest = process[0];
  int rpro = n, clock = 0, idx = 0, exectime = 0, idle = 0;
  float awt = 0;

  while (rpro != 0) {
    int flag = 0;
    int sum = 0;

    sortbyburst(process, n);
    for (int i = 0; i < n; i++) {
      // if process has arrived and has not finished execution
      if (process[i].arrival <= clock && process[i].exectime > 0) {
        flag = 1;
        // if current process has the smallest burst time
        if (process[i].pid == smallest.pid) {
          exectime++;
        } else {
          queue[idx] = smallest;
          // set execution
          printf("P%d\t%d\t%d\n", smallest.pid, smallest.exectime, smallest.arrtime);
          if (exectime != 0 && idle != 1) {
            clock -= exectime; // start time = current clock time - time executing
            setprocess(&queue[idx], &clock, exectime);
            if (queue[idx].exectime == 0) awt += queue[idx].waiting;
            idx++;
          }
          idle = 0; // means that cpu is not idle
          exectime = 1;
          smallest = process[i];
        }
        process[i].exectime--;
        // if process is done, decrement number of remaining processes
        if (process[i].exectime == 0) rpro--;
        break;
      }
    }

    // if no process in queue
    if (flag == 0) {
      // if cpu was not idle
      if (idle == 0 && rpro != n) {
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
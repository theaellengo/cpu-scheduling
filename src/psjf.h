#include "process.h"
#include <limits.h>
#include <stdio.h>

void execute(Process* queue, Process smallest, int* clock, int exectime, float* awt, int* idx);

void psjf(Process process[], int n)
{
  // initialize values
  sortbyburst(process, n);
  Process queue[process[n - 1].burst * n];
  Process smallest;
  smallest.pid = INT_MAX;
  int rpro = n, clock = 0, idx = 0, exectime = 0, idle = 0;
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
          if (exectime != 0 && idle != 1) {
            execute(&queue[idx], smallest, &clock, exectime, &awt, &idx);
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
      if (idle == 0 && rpro != n) {
        execute(&queue[idx], smallest, &clock, exectime, &awt, &idx);
        exectime = 0;
      } else {
        exectime++;
      }
      idle = 1;
    }

    clock++;
  }

  // execute last process
  execute(&queue[idx], smallest, &clock, exectime, &awt, &idx);

  awt /= n;
  printgnatt(queue, idx);
  printprocess(queue, idx, awt);
}

void execute(Process* queue, Process smallest, int* clock, int exectime, float* awt, int* idx)
{
  *queue = smallest;
  *clock -= exectime;
  setprocess(queue, clock, exectime);
  if (queue->exectime == 0) awt += queue->waiting;
  *idx++;
}
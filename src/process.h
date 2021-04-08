#include <math.h>
#include <stdio.h>

#ifndef PROCESS
#define PROCESS

typedef struct {
  // process id
  int pid;
  // arrival time
  int arrival;
  // execution time
  int burst;
  // time process starts execution
  int start;
  // time process finishes execution
  int completion;
  // waiting time
  int waiting;
  //turnaround time
  int turnaround;
} Process;

void setprocess(Process* process, int* clock, int arrival);
void setrr(Process* process, int* clock, int arrival, int timeslice);

void setprocess(Process* process, int* clock, int arrival)
{
  process->arrival = arrival;
  // start time
  process->start = *clock;
  // completion start time + execution time
  process->completion = process->start + process->burst;
  // turnaround = completion time - arrival time
  process->turnaround = process->completion - arrival;
  // waiting = (tunraround - burst) || (start - arrival)
  process->waiting = process->turnaround - process->burst;

  *clock += process->burst;
}

void setrr(Process* process, int* clock, int arrival, int timeslice)
{
  process->arrival = arrival;
  // start time
  process->start = *clock;
  // completion start time + execution time
  process->completion = process->start + process->burst;

  printf("%d\n", process->completion);
  // turnaround = completion time - arrival time
  process->turnaround = process->completion - arrival;
  // waiting = (tunraround - burst) || (start - arrival)
  process->waiting = process->turnaround - process->burst;

  *clock += (process->burst % (timeslice + 1));
}

#endif
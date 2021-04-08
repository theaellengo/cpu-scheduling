#include <math.h>
#include <stdio.h>

#ifndef PROCESS
#define PROCESS

/** Struct of Process**/
typedef struct {
  int pid;
  int arrival;
  int burst;
  int start;
  int completion;
  int waiting;
  int turnaround;
} Process;

/** Function Declarations **/
void setprocess(Process* process, int* clock, int arrival, int exectime);

void setprocess(Process* process, int* clock, int arrival, int exectime)
{
  process->arrival = arrival;
  process->start = *clock;
  process->completion = process->start + exectime;
  // turnaround = completion time - arrival time
  process->turnaround = process->completion - arrival;
  // waiting = (tunraround - burst) || (start - arrival)
  process->waiting = process->turnaround - exectime;
  *clock += exectime;
}

#endif
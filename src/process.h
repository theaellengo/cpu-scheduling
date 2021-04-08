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
void setprocess(Process* process, int* clock, int arrival);
void setrr(Process* process, int* clock, int arrival, int timeslice);

void setprocess(Process* process, int* clock, int arrival)
{
  process->arrival = arrival;
  process->start = *clock;
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
  process->start = *clock;
  process->completion = process->start + timeslice;
  process->turnaround = process->completion - arrival;
  process->waiting = process->turnaround - timeslice;
  *clock += timeslice;
}

#endif
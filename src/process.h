#include <math.h>
#include <stdio.h>

#ifndef PROCESS
#define PROCESS

/** Struct of Process**/
typedef struct {
  int pid;
  int arrival;
  int arrtime;
  int burst; // total execution time
  int exectime; // execution time left
  int start; // start time
  int completion; // end time
  int waiting;
  int turnaround;
} Process;

/** Function Declarations **/
void setprocess(Process* process, int* clock, int exectime);
void sortbyarrival(Process process[], int n);

void setprocess(Process* process, int* clock, int exectime)
{
  process->start = *clock;
  process->exectime -= exectime;
  process->completion = process->start + exectime;
  // turnaround = completion time - arrival time
  process->turnaround = process->completion - process->arrival;
  // waiting = (tunraround - burst) || (start - arrival)
  process->waiting = process->turnaround - (process->burst - process->exectime);
  *clock += exectime;
}

// sorts processes by arrival time
void sortbyarrival(Process process[], int n)
{
  Process temp;
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      if (process[i].arrtime > process[j].arrtime) {
        temp = process[i];
        process[i] = process[j];
        process[j] = temp;
      }
}

void sortbyburst(Process process[], int n)
{
  Process temp;
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      if (process[i].exectime > process[j].exectime) {
        temp = process[i];
        process[i] = process[j];
        process[j] = temp;
      }
}

#endif
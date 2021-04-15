#include <limits.h>
#include <math.h>
#include <stdio.h>

#ifndef PROCESS
#define PROCESS

/** Struct of Process**/
typedef struct process {
  int pid;
  int arrival;
  int burst;
  int arrtime; // arrival time left
  int exectime; // execution time left
  int start; // start time
  int completion; // end time
  int waiting;
  int turnaround;
} Process;

/** Function Declarations **/
void setprocess(Process* process, int* clock, int exectime);
void sortbyarrival(Process process[], int n);
void sortbyburst(Process process[], int n);
void sortbypid(Process process[], int n);
int getshortestarrival(Process process[], int n);
int getshortestburst(Process process[], int n, int clock);

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

// sort processes by remaining burst time
void sortbyburst(Process process[], int n)
{
  Process temp;
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++) {
      if (process[i].exectime > process[j].exectime) {
        temp = process[i];
        process[i] = process[j];
        process[j] = temp;
      }
      // if burst times are equal, sort by arrival time
      if (process[i].exectime == process[j].exectime) {
        if (process[i].arrtime > process[j].arrtime) {
          temp = process[i];
          process[i] = process[j];
          process[j] = temp;
        }
      }
    }
}

int getshortestburst(Process process[], int n, int clock)
{
  Process shortest = { .pid = -1, .exectime = INT_MAX };
  int s = -1;
  for (int i = 0; i < n; i++)
    if (process[i].arrival <= clock && process[i].exectime > 0 && process[i].exectime < shortest.exectime) {
      shortest = process[i];
      s = i;
    }
  return s;
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

int getshortestarrival(Process process[], int n)
{
  Process shortest = { .pid = -1, .arrtime = INT_MAX };
  int s = -1;
  for (int i = 0; i < n; i++)
    if (process[i].arrtime <= 0 && process[i].exectime > 0
        && process[i].arrtime < shortest.arrtime) {
      shortest = process[i];
      s = i;
    }
  return s;
}

void sortbypid(Process process[], int n)
{
  Process temp;
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      if (process[i].pid > process[j].pid) {
        temp = process[i];
        process[i] = process[j];
        process[j] = temp;
      }
}

#endif
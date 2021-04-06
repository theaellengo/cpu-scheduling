#ifndef PROCESS
#define PROCESS

typedef struct {
  int pid;
  int arrival;
  int burst;
  int start;
  int completion;
  int waiting;
  int turnaround;
} Process;

#endif

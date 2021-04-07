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

#endif

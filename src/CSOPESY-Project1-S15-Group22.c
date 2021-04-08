/***************************************************************
Name: Go, Thea Ellen
      Chong, Dianne
Group: 22
Section: S12
***************************************************************/

// include libraries
#include "fcfs.h"
#include "nsjf.h"
#include "process.h"
#include "psjf.h"
#include "rr.h"
#include <stdio.h>
#include <stdlib.h>

/** Function Declarations **/
void getprocess(FILE* fp, Process* process);

int main()
{
  char filename[FILENAME_MAX];
  FILE* fp;

  printf("Enter Filename: ");
  gets(filename);

  // open and read file
  fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("%s not found.\n", filename);
    exit(EXIT_FAILURE);
  }

  // get xyz (scheduling algo, num processes, timeslice val)
  int xyz[3];
  fscanf(fp, "%d %d %d", &xyz[0], &xyz[1], &xyz[2]);

  // get y processes
  Process process[xyz[1]];
  for (int i = 0; i < xyz[1]; i++)
    getprocess(fp, &process[i]);

  // close file
  fclose(fp);

  // check for errors
  if (xyz[1] < 3 || xyz[1] > 100)
    printf("Number of processes should be in range (3, 100).\n");
  else if (xyz[0] != 3 && xyz[2] != 1)
    printf("Timeslice value should be 1.\n");
  else if (xyz[2] < 1 || xyz[2] > 100)
    printf("Timeslice value should be in range (1, 100).\n");
  else {
    switch (xyz[0]) {
    case 0:
      fcfs(process, xyz[1]);
      break;
    case 1:
      nsjf(process, xyz[1]);
      break;
    case 2:
      psjf(process, xyz[1]);
      break;
    case 3:
      rr(process, xyz[1], xyz[2]);
      break;
    default:
      printf("Invalid scheduling algorithm.\n");
    }
  }

  return 0;
}

// scans processes from file
void getprocess(FILE* fp, Process* process)
{
  if (feof(fp)) {
    printf("Number of listed processes is less than the specfied amount.\n");
    exit(EXIT_FAILURE);
  }
  fscanf(fp, "%d %d %d", &process->pid, &process->arrival, &process->burst);
}

#include "process.h"
#include <math.h>
#include <stdio.h>
#include <windows.h>

#ifndef DISPLAY
#define DISPLAY

void printprocess(Process process[], int n, float awt);
void printgnatt(Process process);
void printlabel(char* str);
int getnumdigits(int num);

void printprocess(Process process[], int n, float awt)
{
  printlabel("\n\nProcess   Arrival   Burst   Start   End   Waiting   Turnaround\n");
  for (int i = 0; i < n; i++) {
    printf("%d%*c", process[i].pid, 9 - getnumdigits(process[i].pid), ' ');
    printf("%d%*c", process[i].arrival, 9 - getnumdigits(process[i].arrival), ' ');
    printf("%d%*c", process[i].burst, 7 - getnumdigits(process[i].burst), ' ');
    printf("%d%*c", process[i].start, 7 - getnumdigits(process[i].start), ' ');
    printf("%d%*c", process[i].completion, 5 - getnumdigits(process[i].completion), ' ');
    printf("%d%*c", process[i].waiting, 9 - getnumdigits(process[i].waiting), ' ');
    printf("%d\n", process[i].turnaround);
  }
  printf("---------------------------------------------------------------");
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
  printf("\nAverage Waiting Time: %.1f\n\n", awt);
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void printgnatt(Process process)
{
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, 15 * 16);
  printf(" %d", process.start);
  printf("%*c ", process.burst / 2, ' ');
  SetConsoleTextAttribute(hConsole, 15 * 16 + 4);
  printf("P%d", process.pid);
  SetConsoleTextAttribute(hConsole, 15 * 16);
  printf("%*c ", process.burst / 2, ' ');
  printf("%d ", process.completion);
  SetConsoleTextAttribute(hConsole, 15);
  printf(" ");
}

void printlabel(char* str)
{
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
  printf("%s", str);
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

int getnumdigits(int num)
{
  return (num == 0) ? 0 : floor(log10(num));
}

#endif
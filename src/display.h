#include "process.h"
#include <math.h>
#include <stdio.h>
#include <windows.h>

#ifndef DISPLAY
#define DISPLAY

void printprocess(Process process[], int n, float awt);
void printgnatt(Process process[], int n);
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

void printgnatt(Process process[], int n)
{
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  printlabel("\nGnatt Chart:\n");
  for (int i = 0; i < n; i++) {
    if (i > 0 && process[i - 1].completion != process[i].start) printf("[///] ");
    SetConsoleTextAttribute(hConsole, 15 * 16);
    printf(" %d", process[i].start);
    printf("%*c ", (process[i].completion - process[i].start) / 2, ' ');
    SetConsoleTextAttribute(hConsole, 15 * 16 + 4);
    printf("P%d", process[i].pid);
    SetConsoleTextAttribute(hConsole, 15 * 16);
    printf(" %*c", (process[i].completion - process[i].start) / 2, ' ');
    printf("%d ", process[i].completion);
    SetConsoleTextAttribute(hConsole, 15);
    printf(" ");
  }
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
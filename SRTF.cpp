#include <stdio.h>
#include <stdlib.h>
#define MAX_PROCESS 10

typedef struct {
    int iPID;
    int iArrival;
    int iBurst;
    int iRemainingTime;
    int iStart;
    int iFinish;
    int iWaiting;
    int iResponse;
    int iTaT;
} PCB;

void inputProcess(int n, PCB P[]) {
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &P[i].iArrival, &P[i].iBurst);
        P[i].iPID = i + 1;
        P[i].iRemainingTime = P[i].iBurst;  // Initialize remaining time as burst time
        P[i].iStart = -1;  // Start time initially set to -1 (not started)
    }
}

void printProcess(int n, PCB P[]) {
    printf("PID\tArrival\tBurst\tStart\tFinish\tWaiting\tResponse\tTaT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               P[i].iPID, P[i].iArrival, P[i].iBurst, P[i].iStart,
               P[i].iFinish, P[i].iWaiting, P[i].iResponse, P[i].iTaT);
    }
}

void calculateAWTandATaT(int n, PCB P[]) {
    int totalWaiting = 0, totalTaT = 0;
    for (int i = 0; i < n; i++) {
        totalWaiting += P[i].iWaiting;
        totalTaT += P[i].iTaT;
    }
    printf("Average Waiting Time: %.2f\n", (float)totalWaiting / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTaT / n);
}

void SRTF(int n, PCB P[]) {
    int currentTime = 0, completed = 0;
    int shortest = -1, minRemainingTime;
    
    while (completed < n) {
        // Find process with the shortest remaining time at currentTime
        minRemainingTime = 9999;
        shortest = -1;
        
        for (int i = 0; i < n; i++) {
            if (P[i].iArrival <= currentTime && P[i].iRemainingTime > 0 &&
                P[i].iRemainingTime < minRemainingTime) {
                minRemainingTime = P[i].iRemainingTime;
                shortest = i;
            }
        }

        if (shortest == -1) {
            currentTime++;  // Increment time if no process is available
            continue;
        }

        // Set start time if process is starting for the first time
        if (P[shortest].iStart == -1) {
            P[shortest].iStart = currentTime;
            P[shortest].iResponse = currentTime - P[shortest].iArrival;
        }

        // Execute the process for 1 unit of time
        P[shortest].iRemainingTime--;
        currentTime++;

        // Check if process is completed
        if (P[shortest].iRemainingTime == 0) {
            completed++;
            P[shortest].iFinish = currentTime;
            P[shortest].iTaT = P[shortest].iFinish - P[shortest].iArrival;
            P[shortest].iWaiting = P[shortest].iTaT - P[shortest].iBurst;
        }
    }
}

int main() {
    PCB P[MAX_PROCESS];
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    inputProcess(n, P);
    SRTF(n, P);

    printf("\n===== SRTF Scheduling Results =====\n");
    printProcess(n, P);
    calculateAWTandATaT(n, P);

    return 0;
}

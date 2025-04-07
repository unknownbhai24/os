#include <stdio.h>

typedef struct Process {
    int pid;
    int at;
    int bt;
    int tat;
    int wt;
    int ct;
} PCB;

void sortByArrival(PCB processes[], int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(processes[j].at > processes[j + 1].at) {
                PCB temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter the number of processes : \n");
    scanf("%d", &n);
    PCB processes[n];
    for(int i=0; i<n; i++) {
        processes[i].pid = i + 1;
        printf("Enter the arrival time and burst time for the pid %d : ", processes[i].pid);
        scanf("%d %d", &processes[i].at, &processes[i].bt);
    }

    sortByArrival(processes, n);

    double totalTAT = 0, totalWT = 0;
    int currentTime = 0;

    for(int i=0; i<n; i++) {
        if(currentTime < processes[i].at) {
            currentTime = processes[i].at;
        }

        processes[i].ct = currentTime + processes[i].bt;
        processes[i].tat = processes[i].ct - processes[i].at;        
        processes[i].wt = processes[i].tat - processes[i].bt;

        currentTime = processes[i].ct;
        totalTAT += processes[i].tat;
        totalWT += processes[i].wt;
    }

    printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].at, processes[i].bt, 
                processes[i].ct, processes[i].wt, processes[i].tat);
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);
}

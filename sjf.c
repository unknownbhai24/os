#include <stdio.h>

typedef struct Process {
    int pid;
    int at;
    int bt;
    int tat;
    int wt;
    int ct;
    int isCompleted;
} PCB;
int main() {
    int n;
    printf("Enter the number of processes : \n");
    scanf("%d", &n);
    PCB p[n];
    for(int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter the arrival time and burst time for the pid %d : ", p[i].pid);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].isCompleted = 0;
    }
    int currentTime = 0, completed = 0;
    float totalTAT = 0, totalWT = 0;

    while(completed != n) {
        int index = -1;
        int minBurst = 1000000000;

        for(int i = 0; i < n; i++) {
            if(p[i].at <= currentTime && p[i].isCompleted == 0) {
                if(p[i].bt < minBurst) {
                    minBurst = p[i].bt;
                    index = i;
                }
            }
        }

        if(index == -1) {
            currentTime++;
        } else {
            currentTime += p[index].bt;
            p[index].ct = currentTime;
            p[index].tat = p[index].ct - p[index].at;
            p[index].wt = p[index].tat - p[index].bt;

            totalTAT += p[index].tat;
            totalWT += p[index].wt;
            p[index].isCompleted = 1;
            completed++;
        }
    }
    printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].wt, p[i].tat);
    }
    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);
}

#include <stdio.h>

struct Process {
    int pid;
    int at;
    int bt;
    int priority;
    int ct;
    int wt;
    int tat;
    int isCompleted;
};

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time, Burst Time and Priority for Process %d: ", p[i].pid);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].priority);
        p[i].isCompleted = 0;
    }

    int currentTime = 0, completed = 0;
    float totalWT = 0, totalTAT = 0;

    while (completed != n) {
        int idx = -1;
        int minPriority = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && p[i].isCompleted == 0) {
                if (p[i].priority < minPriority) {
                    minPriority = p[i].priority;
                    idx = i;
                } else if (p[i].priority == minPriority) {
                    if (p[i].at < p[idx].at) {
                        idx = i;
                    }
                }
            }
        }

        if (idx == -1) {
            currentTime++;
        } else {
            currentTime += p[idx].bt;
            p[idx].ct = currentTime;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            totalWT += p[idx].wt;
            totalTAT += p[idx].tat;

            p[idx].isCompleted = 1;
            completed++;
        }
    }

    printf("\nProcess\tAT\tBT\tPriority\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt,
               p[i].priority, p[i].ct, p[i].wt, p[i].tat);
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);
    return 0;
}

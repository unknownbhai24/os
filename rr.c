#include <stdio.h>

struct Process {
    int at, bt, rt, ct, wt, tat,st, done;
};

int main() {
    int n, tq, time = 0, done = 0;
    printf("Enter number of processes and time quantum: ");
    scanf("%d %d", &n, &tq);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        printf("Enter AT and BT for P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
        p[i].done = p[i].st = -1;
    }

    int q[100], front = 0, rear = 0;
    float twt = 0, ttat = 0, trt = 0;
    int vis[n]; 
    for (int i = 0; i < n; i++) vis[i] = 0;
    for (int i = 0; i < n; i++) {
        if (p[i].at == 0) {
            q[rear++] = i;
            vis[i] = 1;
        }
    }
    while (done < n) {
        if (front == rear) {
            time++;
            for (int i = 0; i < n; i++)
                if (!vis[i] && p[i].at <= time) { q[rear++] = i; vis[i] = 1; }
            continue;
        }
        int i = q[front++];
        if (p[i].st == -1) p[i].st = time;
        int t = (p[i].rt > tq) ? tq : p[i].rt;
        time += t;
        p[i].rt -= t;
        for (int j = 0; j < n; j++) {
            if (!vis[j] && p[j].at <= time) {
                q[rear++] = j;
                vis[j] = 1;
            }
        }
        if (p[i].rt == 0) {
            p[i].ct = time;
            p[i].tat = p[i].ct - p[i].at;
            p[i].wt = p[i].tat - p[i].bt;
            ttat += p[i].tat;
            twt += p[i].wt;
            done++;
        } else {
            q[rear++] = i;
        }
    }

    printf("\nPID\tAT\tBT\tCT\tWT\tTAT\tRT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, p[i].at, p[i].bt, p[i].ct, p[i].wt, p[i].tat);

    printf("\nAvg WT: %.2f\nAvg TAT: %.2f\n", twt/n, ttat/n);
    return 0;
}

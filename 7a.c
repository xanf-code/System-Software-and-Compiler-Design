#include <stdio.h>
#include <stdlib.h>
int bt[10], rbt[10], at[10] = {0}, ct[10], wt[10], tat[10];
int choice, tq, n;
void roundRobin();
void srtf();
void readBT()
{
    printf("Enter Burst Time : ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &bt[i]);
        rbt[i] = bt[i];
    }
}
void readAT()
{
    printf("Enter Arrival Time : ");
    for (int i = 0; i < n; i++)
        scanf("%d", &at[i]);
}
void display()
{
    int swt = 0, stat = 0;
    for (int i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        swt += wt[i];
        stat += tat[i];
    }
    printf("PNO\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", i, at[i], bt[i], ct[i], tat[i], wt[i]);
    printf("Average TAT : %f\n", (float)stat / n);
    printf("Average WT : %f\n", (float)swt / n);
}
int main()
{
    setbuf(stdout, NULL);
    for (;;)
    {
        printf("1)RR\n2)SRTF\n3)EXIT\n");
        printf("Enter Choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("ROUND ROBIN\n");
            printf("Enter The Number Of Processes : ");
            scanf("%d", &n);
            readBT();
            printf("Enter Time Quantum : ");
            scanf("%d", &tq);
            roundRobin();
            break;
        case 2:
            printf("SRTF\n");
            printf("Enter The Number Of Processes : ");
            scanf("%d", &n);
            readBT();
            readAT();
            srtf();
            break;
        case 3:
            exit(0);
        }
    }
    return 0;
}
void roundRobin()
{
    int count = 0, i, time = 0;
    while (1)
    {
        for (i = 0; i < n; i++)
        {
            if (rbt[i] > tq)
            {
                rbt[i] -= tq;
                time += tq;
            }
            else if (rbt[i] != 0)
            {
                time += rbt[i];
                count++;
                rbt[i] = 0;
                ct[i] = time;
            }
        }
        if (count == n)
            break;
    }
    display();
}
void srtf()
{
    int count = 0, i, time;
    rbt[9] = 999;
    for (time = 0; count != n; time++)
    {
        int smallest = 9;
        for (i = 0; i < n; i++)
        {
            if (at[i] <= time && rbt[i] < rbt[smallest] && rbt[i] > 0)
                smallest = i;
        }
        rbt[smallest]--;
        if (rbt[smallest] == 0)
        {
            count++;
            ct[smallest] = time + 1;
        }
    }
    display();
}

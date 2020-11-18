#include <bits/stdc++.h>
using namespace std;
bool p = false;
void bankersAlgo(int process[], int n, int resource_array[], int maxim[][3], int allot[][3])
{
    int avail[3], rem[n][3];
    bool completion[n];
    fill(completion, completion + n, false);
    int order[n];
    for (int i = 0; i < 3; i++)
    {
        avail[i] = resource_array[i];
        order[i] = -1;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            avail[j] = avail[j] - allot[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            rem[i][j] = maxim[i][j] - allot[i][j];
        }
    }
    int val = 0;
    int index = 0;
    while (val <= n * n)
    {
        for (int i = 0; i < n; i++)
        {
            int cnt = 0;
            if (rem[i][0] <= avail[0] && rem[i][1] <= avail[1] && rem[i][2] <= avail[2] && completion[i] == false)
            {
                for (int j = 0; j < 3; j++)
                {
                    avail[j] += allot[i][j];
                    cnt = 1;
                    p = true;
                    completion[i] = true;
                }
            }
            if (cnt == 1)
            {
                order[index] = process[i];
                index++;
            }
            val++;
        }
    }
    if (p)
    {
        cout << "System in safe state,order of execution is: ";
        for (int i = 0; i < n; i++)
        {
            if (order[i] != -1)
                cout << order[i] << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "System is not safe!" << endl;
    }
}
int main()
{
    cout << "Enter total no. of processess: " << endl;
    int n;
    cin >> n;
    int processes[n];
    for (int i = 0; i < n; i++)
    {
        cin >> processes[i];
    }
    cout << "Enter how much maximum value of ith resource you have: " << endl;
    int resource_array[3];
    for (int i = 0; i < 3; i++)
    {
        cin >> resource_array[i];
    }
    cout << "Enter maximum resources required: " << endl;
    int maxim[n][3];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cin >> maxim[i][j];
        }
    }
    cout << "Enter initially allocated resources to the ith process: " << endl;
    int allot[n][3];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cin >> allot[i][j];
        }
    }
    bankersAlgo(processes, n, resource_array, maxim, allot);
    return 0;
}
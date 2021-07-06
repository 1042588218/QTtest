#include<stdio.h>
#include<iostream>
#include<math.h>
using namespace std;
int main()
{
    int num;
    cin >> num;
    double* in = (double*)malloc(sizeof(double) * num * 4);
    for (int i = 0; i < num * 4; i++)
    {
        cin >> in[i];
    }
    for (int i = 0; i < num; i++)
    {
        double k, midx, midy, dx, length;
        length = (sqrt(pow((in[i * 4 + 1] - in[i * 4 + 3]), 2) + pow((in[i * 4] - in[i * 4 + 2]), 2)) / 2) * sqrt(3);
        k = (in[i * 4 + 1] - in[i * 4 + 3]) / (in[i * 4] - in[i * 4 + 2]);
        midx = (in[i * 4] + in[i * 4 + 2]) / 2;
        midy = (in[i * 4 + 1] + in[i * 4 + 3]) / 2;
        dx = sqrt(pow(length, 2) / (1 + pow(k, 2)));
        if(k>0)
            printf("%.2lf %.2lf %.2lf %.2lf\n", (midx - dx),(midy+abs(k)*dx),(midx+dx),(midy-abs(k)*dx));
        if(k<0)
            printf("%.2lf %.2lf %.2lf %.2lf\n", (midx - dx), (midy - abs(k) * dx), (midx + dx), (midy + abs(k) * dx));
        
    }
}

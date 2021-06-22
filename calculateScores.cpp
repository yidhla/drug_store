#include <cstdio>
#include <iostream>
#include <cmath>
using namespace std;

const double tiny = 1e-6;

//fomulation:3.5 *(1-（教辅的收益-你的收益）/abs(教辅的收益))

int main ()
{
    FILE* teacherBestSimulation = fopen("teacherBestSimulation.txt", "r");
    FILE* myBestSimulation = fopen("myBestSimulation.txt", "r");
    if (teacherBestSimulation == NULL)
    {
        printf("Cannot read teacherBestSimulation.txt, scores calculation failed!\n");
        exit(0);
    }
    if (myBestSimulation == NULL)
    {
        printf("Cannot read myBestSimulation.txt, scores calculation failed!\n");
        exit(0);
    }
    double ans = 0;
    for (int i = 0; i < 10; ++i)
    {
        double tScore, mScore, tmp;
        fscanf(teacherBestSimulation, "%lf", &tScore);
        fscanf(myBestSimulation, "%lf", &mScore);
        if (mScore >= tScore)
        {
            tmp = 4.0;
            printf("my: %lf\tteacher: %lf\tscore: %lf\n", mScore, tScore, tmp);
            ans += tmp;
        }
        else if (mScore >= 0)
        {
            tmp = 3.5 * (1-abs(tScore-mScore)/tScore);
            printf("my: %lf\tteacher: %lf\tscore: %lf\n", mScore, tScore, tmp);
            ans += tmp;
        }
        else
		{
            tmp = 0;
            printf("my: %lf\tteacher: %lf\tscore: %lf\n", mScore, tScore, tmp);
            ans += tmp;
        }
    }
    printf("\ntotal scores: %lf\n", ans);
    getchar();
    return 0;
}

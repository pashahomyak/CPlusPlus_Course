#include <cstdio>
#include <math.h>

int main()
{
    std::puts("please enter a,b and c for 'ax^2+bx+c=0':");
    int a = 0;
    int b = 0;
    int c = 0;
    std::scanf("%d %d %d", &a, &b, &c);
    int d = (b * b) - (4 * a * c); 
    if (d < 0) {
        std::puts("No roots. 'd<0'");
    } else {
    float x1 = ((-b) - sqrt(d)) / (2 * a);
    float x2 = ((-b) + sqrt(d)) / (2 * a);
    std::printf("solution1: %f\n", x1);
    std::printf("solutoin2: %f\n", x2);
}}
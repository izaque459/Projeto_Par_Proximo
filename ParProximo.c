#include <stdio.h>
#include <stdlib.h>
#include <float.h> // Para DBL_MAX
#include <math.h>


typedef struct Point2D
{
	int x;
	int y;
}Point;

typedef struct Pair2Points
{
	Point p1;
	Point p2;
}Pair;

double dist(Point p1, Point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

Pair closestPairBaseCase(Point P[], int n) {
    Pair closest;
    double min_dist = DBL_MAX;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double d = dist(P[i], P[j]);
            if (d < min_dist) {
                min_dist = d;
                closest.p1 = P[i];
                closest.p2 = P[j];
            }
        }
    }
    return closest;
}

Pair closestPair(Point P[],int n)
{
	if (n<= 3)
	{
		return closestPairBaseCase(P, n);
	}
		
	
}


int main()
{
	Point points[] = {{2, 3}, {12, 30}, {40, 50}};
    int n = sizeof(points) / sizeof(points[0]);
	
	Pair closest = closestPair(points, n);
	
	printf("O par de pontos mais proximo eh: (%d, %d) e (%d, %d)\n", closest.p1.x, closest.p1.y, closest.p2.x, closest.p2.y);

    return 0;
	
	
}
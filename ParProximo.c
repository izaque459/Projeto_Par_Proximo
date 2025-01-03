//Data: 03/01/2025
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

double dist(Point p1, Point p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}


Pair closestPairBaseCase(Point P[], int n)
{
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

int compareX(const void* a, const void* b)
{
	if ( ((Point*)a)->x > ((Point*)b)->x )
	{
		return 1;
	}else if ( ((Point*)a)->x < ((Point*)b)->x )
	{
		return -1;
	}else
	{
		return 0;
	}
}

int compareY(const void* a, const void* b)
{
    if  ( ((Point*)a)->y > ((Point*)b)->y )
	{
		return 1;
	}else if  ( ((Point*)a)->y < ((Point*)b)->y )
	{
		return -1;
	}else
	{
		return 0;
	}
}

Pair closestSplitPair(Point P[],double delta,int n)
{
	int mid = n / 2;
    int medianX = P[mid].x;
	
	Point Sy[n];
	int l = 0;
	
	// Cria o conjunto Sy (pontos na faixa)
    for (int i = 0; i < n; i++) {
        if (abs(P[i].x - medianX) < delta) {
            Sy[l] = P[i];
            l++;
        }
    }
	
	qsort(Sy, l, sizeof(Point), compareY); // Ordena Sy por y

	
	double best = delta;
    Pair bestPair;
    bestPair.p1.x = bestPair.p1.y = bestPair.p2.x = bestPair.p2.y = -1; // Inicializa com valor inválido

    for (int i = 0; i < l - 1; i++) {
        for (int j = 1; j <= fmin(7, l - 1 - i); j++) { 
            double d = dist(Sy[i], Sy[i + j]);
            if (d < best) {
                best = d;
                bestPair.p1 = Sy[i];
                bestPair.p2 = Sy[i + j];
            }
        }
    }

    return bestPair;
}


Pair closestPair(Point P[],int n)
{
	int mid = 0;
	
	if (n<= 3)
	{
		return closestPairBaseCase(P, n);
	}
	
	qsort(P, n, sizeof(Point), compareX); // Ordena por x
		
	mid = n / 2;
	Point midPoint = P[mid];
	
	Pair dl = closestPair(P, mid);
    Pair dr = closestPair(P + mid, n - mid);
	
	double d = fmin(dist(dl.p1, dl.p2), dist(dr.p1, dr.p2));
	
	Pair s = closestSplitPair(P, d, n);
	
	if (s.p1.x != -1 && dist(s.p1, s.p2) < d) // Verifica se um par válido foi encontrado
        return s;
    else if (dist(dl.p1, dl.p2) < dist(dr.p1, dr.p2))
        return dl;
    else
        return dr;
}


int main(int argc, char *argv[])
{
	Point points[] = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4},{1,1},{1,0},
						{7, 8}, {15, 16}, {22, 23}, {9, 11},{1, 2}, {10, 19}, {10, 11}, 
						{100, 150}, {101, 101}, {99,99},{5,6},{5,90},{10,4},{10,13},{10,15}
    };
    int n = sizeof(points) / sizeof(points[0]);
	
	Pair closest = closestPair(points, n);
	
	printf("O par de pontos mais proximo eh: (%d, %d) e (%d, %d)\n", closest.p1.x, closest.p1.y, closest.p2.x, closest.p2.y);
	    
	printf("Distancia: %f\n", dist(closest.p1, closest.p2)); // Imprime a distância

    return 0;
	
	
}
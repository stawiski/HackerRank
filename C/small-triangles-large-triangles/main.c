#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct triangle
{
    int a;
    int b;
    int c;
};

typedef struct triangle triangle;

/* Return triangle area size. */
static double triangleArea(const triangle *tr)
{
    double p = ((double)(tr->a + tr->b + tr->c))/2.0;
    return sqrt(p*(p - ((double)tr->a))*(p - ((double)tr->b))*(p - ((double)tr->c)));
}

/* Compare triangle areas for qsort. */
static int triangleAreaCompare(const void *a, const void *b) {
    triangle *trA = (triangle*)a;
    triangle *trB = (triangle*)b;

    return (triangleArea(trA) > triangleArea(trB));
}

void sort_by_area(triangle* tr, int n) {
    if (n > 1) {
        /* Use built-in quick sort. */
        qsort(tr, n, sizeof(triangle), triangleAreaCompare);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    triangle *tr = malloc(n * sizeof(triangle));
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d", &tr[i].a, &tr[i].b, &tr[i].c);
    }
    sort_by_area(tr, n);
    for (int i = 0; i < n; i++) {
        printf("%d %d %d\n", tr[i].a, tr[i].b, tr[i].c);
    }
    return 0;
}
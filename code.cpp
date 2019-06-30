#include<iostream>
#include<math.h>
struct points
{
    char name;
    int x_c;
    int y_c;
};
float dist(struct points x, struct points y)
{
    int sumsq = pow(x.x_c - y.x_c, 2) + pow(x.y_c - y.y_c, 2);
    return sqrt(sumsq);
}
int main ()
{
    int i,n;
    printf("enter the number of cities/points:");
    scanf("%d", &n);
    struct points p[n];
    for(i = 0; i < n; i++)
    {
        printf ("enter name and the co-ordinates for the point(%d):\n", i + 1);
        scanf(" %c", &p[i].name);
        scanf("%d", &p[i].x_c);
        scanf("%d", &p[i].y_c);
    }
    printf ("enter starting point:");
    char cpn;
    struct points cp, ne, sp, ne1, ne2;
    scanf(" %c", &cpn);
    for (i = 0; i < n; i++)
    {
        if (cpn == p[i].name)
        {
        	cp = p[i];
        	sp = cp;
        	break;
        }
    }
    float total_dist = 0;
    int nl = n, cp_count;
    printf ("\nThe heuristic pathway is:");
    printf ("%c", cp.name);
    for (int i2 = 0; i2 < n - 1; i2++)
    {
        int temp_dist, temp_dist1 = INT_MAX,temp_dist2 = INT_MAX;
        #pragma omp parallel sections
        {
 	       #pragma omp section
    	    {
        		for (int i1 = 0; i1 <= nl / 2; i1++)
        		{
        			if (p[i1].name != cp.name)
        			{
        				if (dist (p[i1], cp) < temp_dist1)
        				{
        					temp_dist1 = dist (p[i1], cp);
        					ne1 = p[i1];
        				}
        			}
        			else
        			{
        				cp_count = i1;
        			}
        		}
        	}
        	#pragma omp section
        	{
        		for (int i1 = ((nl / 2) + 1); i1 < nl; i1++)
        		{
        			if (p[i1].name != cp.name)
        			{
        				if (dist (p[i1], cp) < temp_dist2)
        				{
        					temp_dist2 = dist (p[i1], cp);
        					ne2 = p[i1];
        				}
        			}
        			else
        			{
        				cp_count = i1;
        			}
        		}
        	}
        }
        if (temp_dist1 > temp_dist2)
        {
        	temp_dist = temp_dist2;
        	ne = ne2;
        	cp = ne;
        }
        else
        {
        	temp_dist = temp_dist1;
        	ne = ne1;
        	cp = ne;
        }
        total_dist = total_dist + temp_dist;
        printf ("-->%c", ne.name);
        for (int x1 = cp_count; x1 < nl; x1++)
        {
        	p[x1] = p[x1 + 1];
        }
        	nl = nl - 1;

    }
    printf ("-->%c\n", cpn);
    printf ("The total distance covered in the trip is:%f\n\n",total_dist + dist (sp, ne));
    return 0;
}

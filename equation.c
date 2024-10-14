#include <stdio.h>
#include <math.h>

void main() {
	int radius  = 1; 
	float x;
	float y;
	printf("Print X and Y\n");
	scanf("%f%f",&x,&y);
	
	if (pow(x,2) + pow(y,2) <= pow(radius,2) && y >= -x && y >= 0)
		{
		printf("YES\n");
		}
	else
		{
		printf("NO\n");
		}
}

#include <stdio.h>

void main() {

	int n = 0;
	printf("Print length of picture: \n");
	scanf("%d", &n);

	if ( n > 2 )
	{
	for ( int i = 0; i < n; i++ )
		{
			printf("*");
		}
		printf("\n");

		for ( int i = 0; i < n - 2; i++ )
		{
			printf("*");
			for ( int j = 0; j < n - 2; j++ )
			{
				printf(" ");
			}
			printf("*");
			printf("\n");
		}

		for ( int i = 0; i < n; i++ )
		{
			printf("*");
		}
		printf("\n");
	}

	else
	{
		printf("Error! Picture cannot be less then 3x3\n");
	}
}

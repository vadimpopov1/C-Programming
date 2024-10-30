#include <stdio.h>

int main() {
	int num;
	puts("1. #8 - Факториал\n2. #9 - Наибольшая цифра в числе\n3. #10 - Разворачивает число\n4. #11 - В какую степень 2 входит число\n5. #12");
	printf("Choose loop: ");
	scanf("%d", &num);

	if ( num == 1 ) // 1. #8
	{
		int n;
		int s = 1;
		printf("Enter N: ");
		scanf("%d", &n);
		if ( n > 0 )
		{
			for (int i = 1; i <= n; i++) {
				s = s * i;
			}

			printf("%d\n", s);
		}
		else
		{
			puts("Number is negative or 0");
		}
	}

	if ( num == 2 )
	{
		int a, nn, ss = 0;
		int k;
		printf("Enter N: ");
		scanf("%d", &nn);

		for ( a = nn; a != 0; a = a / 10)
		{
			k = a % 10;
			if ( k > ss )
			{
			ss = k;
			}
		}
		printf("%d\n", ss);
	}

	if ( num == 3)
	{
		int a3, n3, s3 = 0;
		int k3;
		printf("Enter N: ");
		scanf("%d", &n3);

		for ( a3 = n3; a3 != 0; a3 = a3 / 10 )
		{
			k3 = a3 % 10;
			s3 = s3 * 10 + k3;
		}

		printf("%d\n", s3);
	}

	if (num == 4)
	{
		int n4 = 0;
		printf("Enter N: ");
		scanf("%d", &n4);

		int k4;
		int m4;

		for (k4 = 0, m4 = 1; m4 <= n4; k4++, m4*= 2)
		{
			printf("!! %d\n", k4 - 1);
		}
		printf("%d\n", k4 - 1);
	}
	if (num == 5)
	{
		int n5 = 0;
		printf("Enter N: ");
		scanf("%d", &n5);


		int a5 = 0;
		int s5 = 0, k5 = 0;
		for ( a5 = n5; a5 != 0; a5 = a5 / 10)
		{
			k5 = a5 % 10;
			s5 = s5 + k5;
		}
		printf("%d\n", s5);
	}
}


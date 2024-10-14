#include <stdio.h>

void main() {

	int year;
	printf("Print year ");
	scanf("%d", &year);
	if ( year % 400 == 0)
		{
		 printf("YES\n");
		}
	else
		{
		if ( year % 100 == 0 && year % 4 != 0)
			{
			printf("NO\n");
			}
		if ( year % 4 == 0 && year % 100 != 0)
			{
			printf("YES\n");
			}
		else
			{
			printf("NO\n");
			}
		}
}

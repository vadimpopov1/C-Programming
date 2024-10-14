#include <stdio.h>

void main() {

	float temp;
	char value;
	
	printf("Print temperature (c/f)\n");
	scanf("%f %c", &temp, &value);

	if (value == 'f' || value == 'F')
		{
		float tempf = ((temp-32)/1.8);
		printf("%ff\n", tempf);
		}

	else if (value == 'c' || value == 'C')
		{
		float tempc = (temp*1.8+32);
		printf("%fc\n", tempc);
		}

	else
		{
		printf("Error\n");
		}
}

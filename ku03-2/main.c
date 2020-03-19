#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int process(const signed char *a, int b, signed char *c);

int myprocess(const signed char *a, int b, signed char *c)
{
	if(b*3 >= -2147483648 && b*3 <= 2147483647)
	{
		if(*a*2 >= -128 && *a*2 <= 127)
		{
			if(b*3 - *a*2 >= -128 && b*3-*a*2 <= 127)
			{
				*c = b*3 - *a*2;
				return 0;
			}
			else
				return 3;
		}
		else
			return 2;
	}
	else
		return 1;
}

int main()
{
	signed char ch = 100;
	signed char ch_2 = 100;
	signed char aa;
	int b;
	signed char *c = &ch;
	signed char *c_2 = &ch_2;
	scanf("%hhd%d", &aa, &b);
	const signed char *a = &aa;

	int res_1 = process(a,b,c);
	int res_2 = myprocess(a, b, c_2);
	printf("a=%d\nb=%d\n", *a, b);
	printf("your ans %d %d\n", res_1, *c);
	printf("c ans    %d %d\n\n", res_1, *c_2);

	return 0;
}

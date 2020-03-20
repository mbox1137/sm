#define UTF8 1

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#if UTF8
	int процесс(const signed char *a, int b, signed char *c);
#else
	int process(const signed char *a, int b, signed char *c);
#endif

int myprocess(const signed char *a, int b, signed char *c)
{
	if((int64_t)b*3 >= -2147483648 && (int64_t)b*3 <= 2147483647)
	{
		if((int64_t)(*a)*2 >= -128 && (int64_t)(*a)*2 <= 127)
		{
			if((int64_t)b*3 - *a*2 >= -128 && (int64_t)b*3-*a*2 <= 127)
			{
				*c = (char)(b*3 - *a*2);
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

int main(int argc, char **argv)
{
	signed char ch = 100;
	signed char ch_2 = 100;
	signed char aa;
	int b;
	signed char *c = &ch;
	signed char *c_2 = &ch_2;
//	scanf("%hhd%d", &aa, &b);
	if(argc==3) {
		sscanf(argv[1],"%hhd", &aa);
		sscanf(argv[2],"%d", &b);
	} else {
		aa=120;
		b=5;
	}

	const signed char *a = &aa;
#if UTF8
	int res_1 = процесс(a,b,c);
#else
	int res_1 = process(a,b,c);
#endif
	int res_2 = myprocess(a, b, c_2);
	printf("a=%d\nb=%d\n", *a, b);
	printf("your ans %d %d\n", res_1, *c);
	printf("c ans    %d %d\n\n", res_2, *c_2);

	return 0;
}

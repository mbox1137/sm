#include <stdio.h>

static int a,b,c,d;
static long int r;

long process(long a, long b, long c, long d); 

int main(int argc, char** atgv) {
	scanf("%d %d %d %d",&a,&b,&c,&d);
	r=process(a,b,c,d);
	printf("%d*%d + %d*%d = %ld\n",a,b,c,d,r);
	return(0);
}

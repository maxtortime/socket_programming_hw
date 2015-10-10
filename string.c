#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	char a[200] = "111111111145099999999999999999999999999999999999955555555555555555555555555555511111111111111111111111";
	char* ptr;
	long v = strtol(a,&ptr,10);

	if (sizeof(v)==sizeof(long)) {
		printf("overflow\n");
	}
	printf("%ld\n",v);
	printf("%ld\n",*ptr);
		
	
	return 0;
}

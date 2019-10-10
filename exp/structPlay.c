#include <stdio.h>
int main()
{
	struct play {
		int x;
		int y;
	};
	struct play location;

	location.x = 9;
	printf("This struct's ' x' value is: "); 
	printf("%d\n",location.x);
	printf("%d\n",location.y);
	return 0;
}


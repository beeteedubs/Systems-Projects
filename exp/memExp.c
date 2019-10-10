#import <stdio.h>

int main()
{

int a = 2;
int* ptr = &a;

printf("%d\n",ptr);
printf("%d\n",*ptr);
printf("%d\n",*a);

char b[] = "hello";
char *c = &b;
printf("%c, %c\n", b[0], *c);

return 0;
}


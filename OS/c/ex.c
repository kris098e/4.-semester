#include <stdio.h>

#define SQR(a)((a)*(a))
#define CUB(a)((a)*(a)*(a))


inline static int cub(int x) { return x*x*x; }

int main()
{
        int x;

        x=3;
        printf("square? :%d\n",SQR(x));
        printf("x:       %d\n",x);

        x=3;
        printf("square? :%d\n",SQR(++x));
        printf("x:       %d\n",x);

        x=3;
        printf("cub?    :%d\n",CUB(x++));
        printf("x:       %d\n",x);

        x=3;
        printf("cub?    :%d\n",CUB(++x));
        printf("x:       %d\n",x);

        x=3;
        printf("cub?    :%d\n",cub(++x));
        printf("x:       %d\n",x);

        return 0;
}
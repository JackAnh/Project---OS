#include<stdio.h>
#include<windows.h>

int main()
{
    int n = 12;
    //printf("Nhap vao so nguyen n = "); scanf("%d", &n);
    int i,j;
    int count=0;
    printf("Quat chay sau 5 s: "); Sleep(1000);
    printf("4 "); Sleep(1000);
    printf("3 "); Sleep(1000);
    printf("2 "); Sleep(1000);
    printf("1 "); Sleep(1000);
    printf("0 "); Sleep(500);

    while(count <= 1000)
    {
            for(i=1; i<=n; ++i)
    {
        for(j=1; j<=(2*n); ++j)
        {
            if(j<=n)
            {
                if(j<=i) printf("* ");
                else printf("  ");
            }
            else if(j == (2*n))
            {
                if(n <= (n-i+1)) printf("* ");
            }
            else
            {
                int k = j%n;
                if(k <= (n-i+1)) printf("* ");
                else printf("  ");
            }
         }
         printf("\n");
    }

    for(int a=1; a<=n; ++a)
    {
        for(int b=1; b<=(2*n); ++b)
        {
            if(b<=n)
            {
                if(b >= n-a+1) printf("* ");
                else
                    printf("  ");
            }
            else if(b >= n+1 && b < 2*n)
            {
                int c = b%n;
                if(c >= a)
                    printf("* ");
                else
                    printf("  ");
            }
            else
                printf("* ");
         }
         printf("\n");
    }
    ++count;

//    for(i=0;i<50000;i++);
//    for(i=0;i<50000;i++);
//    for(i=0;i<50000;i++);
//    for(i=0;i<50000;i++);
//    for(i=0;i<50000;i++);
//    for(i=0;i<50000;i++);
//    for(i=0;i<50000;i++);
//    for(i=0;i<320000;i++);
//    for(i=0;i<306000;i++);
//    for(i=0;i<390000;i++);
//    for(i=0;i<390000;i++);
//    for(i=0;i<3990000;i++);
//    for(i=0;i<3990000;i++);
//    for(i=0;i<3099000;i++);
//    for(i=0;i<3099000;i++);
//    for(i=0;i<39099000;i++);
//    for(i=0;i<30000;i++);
//    for(i=0;i<309000;i++);
    Sleep(80);
    system("cls");

    for(i=1; i<=n; ++i)
    {
        for(j=1; j<=(2*n); ++j)
        {
            if(j<=n)
            {
                if(i<=j) printf("* ");
                else printf("  ");
            }
            else if(j >= 2*n-i+1) printf("* ");
            else
                printf("  ");
         }
         printf("\n");
    }

    for(int a=1; a<=n; ++a)
    {
        for(int b=1; b<=(2*n); ++b)
        {
            if(b<=n)
            {
                if(b <= n-a+1) printf("* ");
                else
                    printf("  ");
            }
            else if(b <= n+a && b >=n)
                printf("* ");
            else
                printf("  ");
        }
         printf("\n");
    }
    ++count;
//    for(i=0;i<30000;i++);
//    for(i=0;i<30000;i++);
//    for(i=0;i<30000;i++);
//    for(i=0;i<30000;i++);
//    for(i=0;i<30000;i++);
//    for(i=0;i<390000;i++);
//    for(i=0;i<390000;i++);
//    for(i=0;i<390000;i++);
//    for(i=0;i<390000;i++);
//    for(i=0;i<390000;i++);
//    for(i=0;i<390000;i++);
//    for(i=0;i<390000;i++);
//    for(i=0;i<390000;i++);
//    for(i=0;i<390000;i++);
//    for(i=0;i<390000;i++);
//    for(i=0;i<390000;i++);
//    for(i=0;i<30000;i++);
//    for(i=0;i<30000;i++);
    Sleep(80);
    system("cls");
    }
    return 0;
}


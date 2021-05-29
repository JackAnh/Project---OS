#include<stdio.h>
#include<time.h>
#include<windows.h>

int main() {
    printf("STARTING COUNTDOWN \n");
    for(int i = 20; i >=0; --i) {
        printf("%d \n", i);
        Sleep(1000);
        system("cls");
    }
    printf("HAPPY NEW YEAR\n");
    return 0;
}

#include <stdio.h>
// 3 = 011
// 4 = 100

int main(){
    int a = 495;
    int b = 11;
    int a2 = a;
    int b2 = b;
    // printf("%d  %d\n", a, b);
    // for(int i = 0; i < 32; i++){
    //     printf("a:%d  b:%d\n", a2%2, b2%2);
    //     b2 /= 2; 
    //     a2 /= 2;
    // }
    for(int i = 1; i < 33; i++){
        printf("%d %d\n", 1 & (a >> ( 8*sizeof(int) - i)), 1 & (b >> (8*sizeof(int) - i)));
    }
    
}
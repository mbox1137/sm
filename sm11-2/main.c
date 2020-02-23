#include <stdio.h>

int main(int argc, char **argv) {
    int ic;
    unsigned char cm = 'A' ^ 'a';
//    while((ic=getchar())!=-1) {
    while(1) {
        ic=getchar();
        if(ic==EOF) {
            break;
        }
        if(ic>='a' && ic<='z')
            ic&=~cm;
        putchar(ic);
    }
    return(0);
}

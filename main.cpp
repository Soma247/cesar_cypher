#include <QCoreApplication>
#include <iostream>
#include <wchar.h>
#include <limits.h>

#define N 2
#define ruA 128
#define ruZ 159
#define rua 160
#define rup 175
#define rur 224
#define ruz 239

#define isrual(c) ((c)>=ruA&& (c)<=rup)||((c)>=rur&&(c)<=ruz)
#define isrupper(c) ((c)>=ruA&&(c)<=ruZ)
char getces(int);
char ungetces(int);

int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);
    short c;//int==long
    printf("getces fun\n");
    while((c=std::cin.get())!=EOF)
        std::cout<<getces(c);

    printf("ungetces fun:\n");
    std::cin.clear();
    while((c=std::cin.get())!=EOF)
        std::cout<<ungetces(c);
    printf("Press \"Ctrl + C\" to exit\n");
    return a.exec();
}

char getces(int c){
    if(isalnum(c)){
        if(isupper(c))
            c=c>L'Z'-N? (L'A'+c-(L'Z'-N)-1):(c+N);
        else if (isdigit(c))c=c>L'9'-N? (L'0'+c-(L'9'-N)-1):(c+N);
        else c=c>(L'z'-N)? (L'a'+c-(L'z'-N)-1):(c+N);
    }
    else if(isrual(c)){
        if(isrupper(c))
            c=c>(ruZ-N)? (ruA+N-ruZ+c-1):(c+N);
        else {
            c=c>(ruz-N)? (rua+N-ruz+c-1):(c+N);
            if(c>rup&&c<=rur)c+=rur-rup-1;
        }
    }
    return c;
}


char ungetces(int c){
    if(isalnum(c)){
        if(isupper(c))
            c=c-N<L'A'? (L'Z'-N+c-L'A'+1):(c-N);
        else if(isdigit(c))
            c=c-N<L'0'? (L'9'-N+c-L'0'+1):(c-N);
        else c=c-N<L'a'? (L'z'+c-L'a'-N+1):(c-N);
    }
    else if(isrual(c)){
        if(isrupper(c))
            c=c-N<ruA? (ruZ-N-ruA+c+1):(c-N);
        else
            c=c-N<rua? (ruz-N-rua+c+1):(c-N);
        if(c>rup&&c<rur)c-=rur-rup-1;
    }
    return c;
}

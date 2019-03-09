#include <stdio.h>
#include <stdlib.h>
#include "dosya.h"
#include<windows.h>
#include "graf_olustur.h"

int main()
{

SetConsoleTitle("SEHIRLERARASI KISA MESAFE CETVELI");

    int eleman;

    node* sehir=dosya_oku(&eleman);

    Sleep(2500);
    system("cls");

    bellekte_graf(eleman,sehir);

    system("color 47");

    int i;

    for(i=0;i<=18;i++)
        printf("\n");

    for(i=0;i<=35;i++)
        printf(" ");

    printf("PROGRAM SONA ERDI");

    for(i=0;i<=15;i++)
        printf("\n");

    for(i=0;i<=65;i++)
        printf(" ");

        printf("Leyla MIZRAK");

        for(i=0;i<=2;i++)
        printf("\n");

    return 0;
}

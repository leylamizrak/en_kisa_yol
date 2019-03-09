#ifndef DOSYA_H_INCLUDED
#define DOSYA_H_INCLUDED
#include<string.h>
#include <ctype.h>
#include<windows.h>

struct liste
{
    char isim[30];
    int kod;

    struct liste *sonraki;
};

typedef struct liste node;

node* dosya_oku(int *eleman)
{
    system("color 5E");

    FILE *dosya=fopen("sehir_kod.txt","r");

    if(dosya==NULL){
        printf("MAALESEF!!\nDosya bulunamadi.");
        exit(0);
    }


    else
    {
        char dizi[30];

        fgets(dizi,30,dosya);

        node *sehir=(node*)malloc(sizeof(node));

        char *ptr;

        fgets(dizi,30,dosya);

        ptr=strtok(dizi,"-");

        strcpy(sehir->isim,ptr);


        ptr=strtok(NULL,"-");

        sehir->kod=atoi(ptr);

        sehir->sonraki=NULL;

        node* baslangic=sehir;


        while(fgets(dizi,30,dosya)!=NULL)
        {
            sehir->sonraki=(node*)malloc(sizeof(node));
            sehir=sehir->sonraki;

            ptr=strtok(dizi,"-");

            strcpy(sehir->isim,ptr);

            ptr=strtok(NULL,"-");

            sehir->kod=atoi(ptr);

            sehir->sonraki=NULL;

        }

        printf("     *********SEHIRLER VE KODLARI*********\n");

        sehir=baslangic;

        int i;

        int en_buyuk=0;

        while(sehir!=NULL)
        {
            for(i=0; sehir->isim[i]!='\0'; i++)
                sehir->isim[i]=tolower(sehir->isim[i]);

            sehir->isim[0]=toupper(sehir->isim[0]);

            printf("    *  %-20s---->  %-3d     *\n",sehir->isim,sehir->kod);

            if(sehir->kod>en_buyuk)
                en_buyuk=sehir->kod;

            sehir=sehir->sonraki;

        }

        (*eleman)=en_buyuk;

        return baslangic;

        fclose(dosya);
    }

}

#endif // DOSYA_H_INCLUDED

#ifndef GRAF_OLUSTUR_H_INCLUDED
#define GRAF_OLUSTUR_H_INCLUDED
#include<string.h>
#include<ctype.h>
#define SINIR 1000000
#include<stdlib.h>
#include<windows.h>

int glb_dgskn;

struct djk
{
    int maliyet;
    int visited;

    int indis;

    int *kod_tut;
};

void iki_sehir_sor(int graf[][glb_dgskn],node *sehir)
{
    system("color 6B");

    int isaret=2;///Dijkstra fonksiyonunun hangi ciktiyi vermesi icin onemli

    int nokta1,nokta2;

    sehir_sor(sehir,&nokta1);

    sehir_sor(sehir,&nokta2);

    dijkstra(graf,nokta1,nokta2,isaret,sehir);
}

void baslangic_sor(int graf[][glb_dgskn],node *sehir)
{
    system("color 74");

    int isaret=1;

    int nokta;

    sehir_sor(sehir,&nokta);

    dijkstra(graf,nokta,nokta,isaret,sehir);


}

void sehir_sor(node *sehir,int *nokta)
{
    node *birinci=sehir;

    char bas_sehir[30];

    printf("Sehir ismi giriniz:");
    scanf("%s",bas_sehir);
    fflush(stdin);

    int i;

    *nokta=-1;

    while(1)
    {

        for(i=0; bas_sehir[i]!='\0'; i++)
            bas_sehir[i]=tolower(bas_sehir[i]);

        bas_sehir[0]=toupper(bas_sehir[0]);

        while(sehir!=NULL)
        {
            if(strcmp(sehir,bas_sehir)==0)
            {
                *nokta=sehir->kod;
                break;
            }
            sehir=sehir->sonraki;
        }

        sehir=birinci;

        if(*nokta==-1)
        {
            system("cls");

            printf("YANLIS!!!\n");

            printf("Sehir ismini tekrar giriniz:");
            scanf("%s",bas_sehir);
            fflush(stdin);
        }

        else break;

    }
}

void dijkstra(int graf[][glb_dgskn],int nokta,int nokta2,int isaret,node *sehir)
{
    struct djk dizi[glb_dgskn];

    int i;

    for(i=0; i<glb_dgskn; i++)
    {
        dizi[i].maliyet=SINIR;
        dizi[i].visited=0;

        dizi[i].indis=-1;

        //dizi[i].kod_tut=(int*)malloc(sizeof(int)*glb_dgskn);
        dizi[i].kod_tut=(int*)malloc(sizeof(int));
    }
    int bas=nokta-1;
    dizi[bas].maliyet=0;

    dizi[bas].indis++;
    dizi[bas].kod_tut[dizi[bas].indis]=-1;

    dizi[nokta-1].visited=1;

    int durak;
    int en_kucuk=SINIR;


    for(i=0; i<glb_dgskn; i++)
    {
        if(i!=bas && graf[nokta-1][i]!=-1)
        {
            dizi[i].maliyet=graf[nokta-1][i];

            if(dizi[i].maliyet<en_kucuk)
            {
                en_kucuk=dizi[i].maliyet;

                durak=i;

            }

        }

        if(i!=bas && dizi[i].maliyet!=SINIR)
        {

            dizi[i].indis++;

            dizi[i].kod_tut[dizi[i].indis]=bas;

        }
    }

    nokta=durak;

    int sayac=2;

    int j;

    while(1)
    {
        en_kucuk=SINIR;

        for(i=0; i<glb_dgskn; i++)
        {
            if(dizi[i].visited!=1 && i!=nokta && graf[nokta][i]!=-1)
            {
                if(dizi[i].maliyet==SINIR)
                {
                    dizi[i].maliyet=dizi[nokta].maliyet+graf[nokta][i];

                }
                else if(dizi[i].maliyet>(dizi[nokta].maliyet+graf[nokta][i]))
                {
                    dizi[i].maliyet=dizi[nokta].maliyet+graf[nokta][i];
                }

                if(dizi[i].maliyet==(dizi[nokta].maliyet+graf[nokta][i]))
                {

                    int alan=dizi[nokta].indis+2;
                    dizi[i].kod_tut=(int*)realloc(dizi[i].kod_tut,alan*sizeof(int));
                    for(j=0; j<=dizi[nokta].indis; j++)
                    {
                        dizi[i].kod_tut[j]=dizi[nokta].kod_tut[j];
                    }
                    dizi[i].indis=dizi[nokta].indis+1;
                    dizi[i].kod_tut[dizi[i].indis]=nokta;
                }

            }

             if(dizi[i].maliyet<=en_kucuk && i!=nokta && dizi[i].visited!=1)
                {
                    en_kucuk=dizi[i].maliyet;
                    durak=i;
                }

        }
        dizi[nokta].visited=1;
        nokta=durak;
        sayac++;

        if(sayac==glb_dgskn)
            break;
    }


    if(isaret==1)
    {
        printf("\n");

        printf("   Diger Sehirlere En Kisa Yollar:\n\n");


        node *ilk_sehir=sehir;

        int deger;

        for(i=0; i<glb_dgskn; i++)
        {
            if(dizi[i].maliyet!=SINIR){
            printf(" * ");
            for(j=0; j<=dizi[i].indis; j++)
            {
                while(sehir!=NULL)
                {
                    if(sehir->kod==dizi[i].kod_tut[j]+1)
                    {
                        printf("%s -> ",sehir->isim);
                    }
                    sehir=sehir->sonraki;
                }

                sehir=ilk_sehir;
            }

            while(sehir!=NULL)
            {
                if((i+1)==sehir->kod)
                {
                    printf("%s -> ",sehir->isim);
                }
                sehir=sehir->sonraki;
            }

            printf("%d",dizi[i].maliyet);
            printf("\n");
            }

            sehir=ilk_sehir;
        }

        Sleep(2500);
        system("cls");

    }

    else if(isaret==2)
    {
        printf("\n\n");

        nokta2--;

        system("cls");

        node *ilk_sehir=sehir;

        printf("Iki Sehir Arasi Uzaklik:\n");

        for(i=0; i<=dizi[nokta2].indis; i++)
        {
            sehir=ilk_sehir;

            while(sehir!=NULL)
            {
                if((dizi[nokta2].kod_tut[i]+1)==sehir->kod)
                {
                    printf("%s -> ",sehir->isim);
                }

                sehir=sehir->sonraki;
            }
        }

        sehir=ilk_sehir;

        while(sehir!=NULL)
        {
            if((nokta2+1)==sehir->kod)
                printf("%s -> ",sehir->isim);

            sehir=sehir->sonraki;
        }

        printf("%d\n",dizi[nokta2].maliyet);

        Sleep(2500);
        system("cls");

    }
}

void bellekte_graf(int eleman,node *sehir)
{
    system("color 3F");

    FILE *dosya=fopen("sehir_mesafe.txt","r");

    if(dosya==NULL){
        printf("MAALESEF!!\nDosya bulunamadi.");
        exit(0);
    }

    else
    {

        int dizi[40];

        int *eslestir;

        fgets(dizi,30,dosya);

        int graf[eleman][eleman];

        int satir,sutun;

        for(satir=0; satir<eleman; satir++)
        {
            for(sutun=0; sutun<eleman; sutun++)
            {
                graf[satir][sutun]=-1;

            }

        }

        node *baslangic=sehir;

        int i;

        while(fgets(dizi,40,dosya)!=NULL)
        {

            eslestir=strtok(dizi,"-");

            for(i=0; eslestir[i]!='\0'; i++)
                eslestir[i]=tolower(eslestir[i]);

            eslestir[0]=toupper(eslestir[0]);

            while(strcmp(eslestir,sehir)!=0)
                sehir=sehir->sonraki;

            satir=sehir->kod-1;

            sehir=baslangic;

            eslestir=strtok(NULL,"-");

            for(i=0; eslestir[i]!='\0'; i++)
                eslestir[i]=tolower(eslestir[i]);

            eslestir[0]=toupper(eslestir[0]);

            while(strcmp(eslestir,sehir)!=0)
                sehir=sehir->sonraki;

            sutun=sehir->kod-1;

            eslestir=strtok(NULL,"-");

            graf[satir][sutun]=atoi(eslestir);
            graf[sutun][satir]=graf[satir][sutun];

            sehir=baslangic;

        }


        printf("   *****SEHIRLER VE ARALARINDAKI MESAFE*****\n\n");

        printf("   KOD|");

        glb_dgskn=eleman;

        for(satir=0; satir<eleman; satir++)
            printf("%-3d|",satir+1);

        printf("\n");

        for(satir=0; satir<eleman; satir++)
        {
            printf("   %-3d|",satir+1);

            for(sutun=0; sutun<eleman; sutun++)
            {

                if(graf[satir][sutun]!=-1)
                    printf("%-3d|",graf[satir][sutun]);

                else
                    printf(" - |");

            }
            printf("\n");
        }

        Sleep(2500);
        system("cls");

        sehir=baslangic;

        baslangic_sor(graf,sehir);

        iki_sehir_sor(graf,sehir);

        fclose(dosya);
    }

}

#endif // GRAF_OLUSTUR_H_INCLUDED

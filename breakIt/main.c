#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include <time.h>
#define caramida_latime 10
#define latime 54
#define inaltime 10
int a[23][80]={0},i,j,k,direction,minge_x,minge_y,bara_x,score;
char c;

void init()
{
    //******************IMPORTANT********************
    //de aici se seteaza directia la inceput in care merge mingea
    direction=45;
    //***********************************************
    score=0;
    //generare perete pe margine
    for(i=1;i<23;i++) a[i][1]=6;
    for(i=1;i<23;i++) a[i][79]=6;
    for(j=1;j<80;j++) a[1][j]=7;
    for(j=1;j<80;j++) a[22][j]=7;
    //generarea caramizilor(random)
    srand(time(NULL));
    for(i=2;i<=inaltime;i++)
    {
        for(j=10;j<=latime;j++)
        {
           if(j%caramida_latime==0)
           {
               //caramizile sunt intre 0-9, intre 10-19, intre 20-29, intre 30-39
               a[i][j]=rand()%3+1;
               //0-nimic
               //1-caramida gri
               //2-caramida orange
               //3-caramida maro
               //4 minge
               //5 bara
               //6 perete
               //7-perete sub-jos
                  for(k=j+1;k<j+caramida_latime;k++) a[i][k]=a[i][j];
           }
        }
    }
    //
    //mingea incepe de pe pozitita 18,30
    a[18][19]=4;
    minge_x=18;
    minge_y=19;
    //bara sa aiba lungimea 10
    for(j=25;j<35;j++) a[19][j]=5;
    bara_x=25;
}
//
//
void gameplay()
{

    while(TRUE)
    {

            //system("cls");-nu folosim stergerea screen-ului pentru ca apare un efect blink
            //redesenam totul
             COORD Coord;
            Coord.X = 0;
            Coord.Y = 0;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Coord);
            //Desenarea scorului pe ecran
            SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),160 );
            printf("       Score: %d\n",score);
            //printf("\n");
           // printf("\n");
            //
                for(i=1;i<23;i++)
                    {
                        for(j=1;j<80;j++)
                        {
                          if(a[i][j]==0)  SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),120 );
                         else if(a[i][j]==1)  SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),135 );
                         else if(a[i][j]==2)  SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),79 );
                          else if(a[i][j]==3)  SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),103 );
                            else if(a[i][j]==4)  {SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),30 ); }
                            else if(a[i][j]==5)  {SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),170 );}
                            else if(a[i][j]==6)  {SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),250 );}
                            else if(a[i][j]==7)  {SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),250 );}
                        if(a[i][j]!=4)    printf(" ");
                        else printf("0");
                            //printf("%c",'*');
                        }
                        printf("\n");
                    }
                //printf("****%d****",direction);-numai pentru debug(sa vedem directia)
                for(i=1;i<=3;i++)
                {

                    Sleep(1);

                    if (kbhit()) //apasare orice tasta
                        {
                             c = getch();
                             if(c==' ')//apasare space
                             {
                                 //pauza pana la urmatorul space
                                    for(;;)
                                    {
                                        Sleep(100);
                                        if (kbhit())
                                        {
                                                c = getch();
                                                if(c==' ')
                                                {
                                                goto totul;//sari peste totul
                                                }
                                        }
                                    }
                             }
                             else //alta tasta apasata - pentru bara
                             {
                             if(c=='a') //stanga
                             {

                            for(k=bara_x;k<bara_x+10;k++) a[19][k]=0; //stergerea locului unde se afla bara
                                bara_x-=2;
                                //noua pozitie
                            for(k=bara_x;k<bara_x+10;k++) a[19][k]=5;
                             }
                             if(c=='d') //stanga
                             {

                            for(k=bara_x;k<bara_x+10;k++) a[19][k]=0; //stergerea locului unde se afla bara
                                bara_x+=2;
                                //noua pozitie
                            for(k=bara_x;k<bara_x+10;k++) a[19][k]=5;
                             }
                             }
                        }
                }
                totul:;
                //deplasare minge
                //sunt 8 directii: sud=270, est=0, vest=180, nord=90, sud-est=315, nord-est=45, sud-vest=225, nord-vest=135
                //********IMPORTANT********
                //jocul este facut in asa fel incat daca la inceput mingea are directia 0,90,180 sau 270 - nu o sa apar directiile 45,135,225,315
                //si inversul este adevarat
                //jocul este facut cu principiile fizicii
                //************************
          if(direction==0)
            {
                if(a[minge_x][minge_y+1]==0)//nu este nimic in cale
                {
                    a[minge_x][minge_y+1]=4;a[minge_x][minge_y]=0;minge_y++;
                }
                else //directia devine opusa=180
                {
                    direction=180;

                        //in fucntie de ce intalneste
                       if(a[minge_x][minge_y+1]==1); // tigla gri-
                       else if(a[minge_x][minge_y+1]==2)//orange
                       {
                           score++;
                           //se distruge

                           for(k=(minge_y+1)/caramida_latime *10;k<(minge_y+1)/caramida_latime *10+caramida_latime;k++)
                            a[minge_x][k]=0;
                       }
                        else if(a[minge_x][minge_y+1]==3)
                        {
                            score++;
                        //devine orange
                        for(k=(minge_y+1)/caramida_latime *10;k<(minge_y+1)/caramida_latime *10+caramida_latime;k++)
                            a[minge_x][k]=2;
                        }
                }

            }
            if(direction==180)
            {
                if(a[minge_x][minge_y-1]==0)//nu este nimic in cale
                {
                    a[minge_x][minge_y-1]=4;a[minge_x][minge_y]=0;minge_y--;
                }
                else //directia devine opusa=0
                {
                    direction=0;

                        //in fucntie de ce intalneste
                       if(a[minge_x][minge_y-1]==1); // tigla gri-
                       else if(a[minge_x][minge_y-1]==2)//orange
                       {
                           score++;
                           //se distruge

                           for(k=(minge_y-1)/caramida_latime *10;k<(minge_y-1)/caramida_latime *10+caramida_latime;k++)
                            a[minge_x][k]=0;
                       }
                        else if(a[minge_x][minge_y-1]==3)
                        {
                            score++;
                        //devine orange
                        for(k=(minge_y-1)/caramida_latime *10;k<(minge_y-1)/caramida_latime *10+caramida_latime;k++)
                            a[minge_x][k]=2;
                        }
                }

            }
          if(direction==90)
            {
                if(a[minge_x-1][minge_y]==0)//nu este nimic in cale
                {
                    a[minge_x-1][minge_y]=4;a[minge_x][minge_y]=0;minge_x--;
                }
                else //directia devine opusa=270
                {
                    direction=270;

                        //in fucntie de ce intalneste
                       if(a[minge_x-1][minge_y]==1); // tigla gri-
                       else if(a[minge_x-1][minge_y]==2)//orange
                       {
                           score++;
                           //se distruge

                           for(k=(minge_y)/caramida_latime *10;k<(minge_y)/caramida_latime *10+caramida_latime;k++)
                            a[minge_x-1][k]=0;
                       }
                        else if(a[minge_x-1][minge_y]==3)
                        {
                            score++;
                        //devine orange
                        for(k=(minge_y)/caramida_latime *10;k<(minge_y)/caramida_latime *10+caramida_latime;k++)
                            a[minge_x-1][k]=2;
                        }
                }

            }
             if(direction==270)
            {
                if(a[minge_x+1][minge_y]==0)//nu este nimic in cale
                {
                    a[minge_x+1][minge_y]=4;a[minge_x][minge_y]=0;minge_x++;
                }
                else //directia devine opusa=90
                {
                    direction=90;

                        //in fucntie de ce intalneste
                       if(a[minge_x+1][minge_y]==1); // tigla gri-
                       else if(a[minge_x+1][minge_y]==2)//orange
                       {
                           score++;
                           //se distruge

                           for(k=(minge_y)/caramida_latime *10;k<(minge_y)/caramida_latime *10+caramida_latime;k++)
                            a[minge_x+1][k]=0;
                       }
                        else if(a[minge_x+1][minge_y]==3)
                        {
                            score++;
                        //devine orange
                        for(k=(minge_y)/caramida_latime *10;k<(minge_y)/caramida_latime *10+caramida_latime;k++)
                            a[minge_x+1][k]=2;
                        }
                }

            }
            if(direction==45)
            {
                if(a[minge_x-1][minge_y+1]==0)//nu este nimic in cale
                {
                    a[minge_x-1][minge_y+1]=4;a[minge_x][minge_y]=0;minge_x--;minge_y++;
                }
                else
                {
                    //*********IMPORTANT
                 //trebuie sa ne uitam ca directia urmatoare va fi 135 sau 315 grade
                 //in functie de ce intalneste mingea-zid vertical sau orizontal
                 //*********IMPORTANT
                 if((minge_y+1)%caramida_latime==0 || a[minge_x-1][minge_y+1]==6) direction=135;//suntem la margine
                    else direction=315;

                        //in fucntie de ce intalneste
                       if(a[minge_x-1][minge_y+1]==1); // tigla gri-
                       else if(a[minge_x-1][minge_y+1]==2)//orange
                       {
                           score++;
                           //se distruge

                           for(k=(minge_y+1)/caramida_latime *10;k<(minge_y+1)/caramida_latime *10+caramida_latime;k++)
                            a[minge_x-1][k]=0;
                       }
                        else if(a[minge_x-1][minge_y+1]==3)
                        {
                            score++;
                        //devine orange
                        for(k=(minge_y+1)/caramida_latime *10;k<(minge_y+1)/caramida_latime *10+caramida_latime;k++)
                            a[minge_x-1][k]=2;
                        }
                }

            }
            if(direction==135)
            {
                if(a[minge_x-1][minge_y-1]==0)//nu este nimic in cale
                {
                    a[minge_x-1][minge_y-1]=4;a[minge_x][minge_y]=0;minge_x--;minge_y--;
                }
                else
                {
                    //*********IMPORTANT
                 //trebuie sa ne uitam ca directia urmatoare va fi 45 sau 225 grade
                 //in functie de ce intalneste mingea-zid vertical sau orizontal
                 //*********IMPORTANT
                    if((minge_y-1)%caramida_latime==0 || a[minge_x-1][minge_y-1]==6) direction=45;//suntem la margine
                    else direction=225;

                        //in fucntie de ce intalneste
                       if(a[minge_x-1][minge_y-1]==1); // tigla gri-
                       else if(a[minge_x-1][minge_y-1]==2)//orange
                       {
                           score++;
                           //se distruge

                           for(k=(minge_y-1)/caramida_latime *10;k<(minge_y-1)/caramida_latime *10+caramida_latime;k++)
                            a[minge_x-1][k]=0;
                       }
                        else if(a[minge_x-1][minge_y-1]==3)
                        {
                            score++;
                        //devine orange
                        for(k=(minge_y-1)/caramida_latime *10;k<(minge_y-1)/caramida_latime *10+caramida_latime;k++)
                            a[minge_x-1][k]=2;
                        }
                }

            }
            if(direction==315)
            {
                if(a[minge_x+1][minge_y+1]==0)//nu este nimic in cale
                {
                    a[minge_x+1][minge_y+1]=4;a[minge_x][minge_y]=0;minge_x++;minge_y++;
                }
                else
                {
                    //*********IMPORTANT
                 //trebuie sa ne uitam ca directia urmatoare va fi 225 sau 45 grade
                 //in functie de ce intalneste mingea-zid vertical sau orizontal
                 //*********IMPORTANT

                 if((minge_y+1)%caramida_latime==0 || a[minge_x+1][minge_y+1]==6) direction=225;//suntem la margine
                    else direction=45;

                        //in fucntie de ce intalneste
                       if(a[minge_x+1][minge_y+1]==1); // tigla gri-
                       else if(a[minge_x+1][minge_y+1]==2)//orange
                       {
                           score++;
                           //se distruge

                           for(k=(minge_y+1)/caramida_latime *10;k<(minge_y+1)/caramida_latime *10+caramida_latime;k++)
                            a[minge_x+1][k]=0;
                       }
                        else if(a[minge_x+1][minge_y+1]==3)
                        {
                            score++;
                        //devine orange
                        for(k=(minge_y+1)/caramida_latime *10;k<(minge_y+1)/caramida_latime *10+caramida_latime;k++)
                            a[minge_x+1][k]=2;
                        }
                }

            }
            if(direction==225)
            {
                if(a[minge_x+1][minge_y-1]==0)//nu este nimic in cale
                {
                    a[minge_x+1][minge_y-1]=4;a[minge_x][minge_y]=0;minge_x++;minge_y--;
                }
                else
                {
                    //*********IMPORTANT
                 //trebuie sa ne uitam ca directia urmatoare va fi 315 sau 135 grade
                 //in functie de ce intalneste mingea-zid vertical sau orizontal
                 //*********IMPORTANT

                 if((minge_y-1)%caramida_latime==0 || a[minge_x+1][minge_y-1]==6) direction=315;//suntem la margine
                    else direction=135;

                        //in fucntie de ce intalneste
                       if(a[minge_x+1][minge_y-1]==1); // tigla gri-
                       else if(a[minge_x+1][minge_y-1]==2)//orange
                       {
                           score++;
                           //se distruge

                           for(k=(minge_y-1)/caramida_latime *10;k<(minge_y-1)/caramida_latime *10+caramida_latime;k++)
                            a[minge_x+1][k]=0;
                       }
                        else if(a[minge_x+1][minge_y-1]==3)
                        {
                            score++;
                        //devine orange
                        for(k=(minge_y-1)/caramida_latime *10;k<(minge_y-1)/caramida_latime *10+caramida_latime;k++)
                            a[minge_x+1][k]=2;
                        }
                }

            }

    //daca mingea cade sub bara
    if(minge_x>20) {gameover();return;}




    }
}
//
void gameover()
{
    system("CLS");
printf("JOCUL S-A TERMINAT!\n APASA ORICE TASTA PENTRU A INCHIDE JOCUL!");
while (TRUE)
{
    if(kbhit())
    {
    return;
    }
    Sleep(1);
}

}
int main()
{
init();
gameplay();
//DACA vrem sa reincepem jocul, modificam aici
//
    return 0;
}

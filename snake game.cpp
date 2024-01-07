#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#define MAX_TAIL_LENGTH 100
int height=20,width=20;
int tailx[MAX_TAIL_LENGTH],taily[MAX_TAIL_LENGTH];
int counttail=0;
int sx,sy,foodx,foody,score,gameover,direction;

void setup()
{
    gameover=0;
    sx=width/2;
    sy=height/2;
    foodx=rand()%(width-2)+1;
    foody=rand()%(height-2)+1;
    score=0;
}
void boundary()
{
    system("cls");
    for (int i=0;i<width;i++)
	{
        for(int j=0;j<height;j++)
		{
            if(i==0 || i==height-1 || j==0 || j==width-1)
			{
                printf("*");
            } 
			else
			{
                if(i==sx && j==sy)
				{
                    printf("O");
                }
				else if(i==foodx && j==foody)
				{
                    printf("F");
                }
				else
				{
                    int ch=0;
                    for(int k=0; k<counttail;k++)
					{
                        if(i==tailx[k] && j==taily[k])
						{
                            printf("o");
                            ch=1;
                        }
                    }
                    if(ch == 0)
					{
                        printf(" ");
                    }
                }
            }
        }
        printf("\n");
    }
    printf("SCORE=%d",score);
}

void input()
{
    if(_kbhit())
	{
        switch(_getch())
		{
            case 'a':
                direction=1;
                break;
            case 's':
                direction=2;
                break;
            case 'w':
                direction=3;
                break;
            case 'z':
                direction=4;
                break;
            case 'x':
                gameover=1;
                break;
        }
    }
}

void move()
{
    int prevx=tailx[0];
    int prevy=taily[0];
    int prev2x,prev2y;
    tailx[0]=sx;
    taily[0]=sy;

    for(int i=0;i<counttail;i++)
	{
        prev2x=tailx[i];
        prev2y=taily[i];
        tailx[i]=prevx;
        taily[i]=prevy;
        prevx=prev2x;
        prevy=prev2y;
    }

    switch(direction)
	{
        case 1:
            sy--;
            break;
        case 2:
            sy++;
            break;
        case 3:
            sx--;
            break;
        case 4:
            sx++;
            break;
        default:
            break;
    }

    if(sx<=0 || sx>=width-1 || sy<=0 || sy>=height-1)
	{
		gameover=1;
	}
        

    if(sx==foodx && sy==foody)
	{
        foodx=rand()%(width-2)+1;
        foody=rand()%(height-2)+1;
        score+=10;
        counttail++;
    }
}

void intro()
{
    char a;
    printf("\n\n \t\t\t\t\t||  WELCOME TO SNAKE GAME   ||\n\n\n");
    printf("\n1) USE ASWZ TO MOVE THE SNAKE.\n\n2) YOU WILL BE PROVIDED FOODS AT THE SEVERAL COORDINATES OF THE SCREEN WHICH YOU HAVE TO EAT.\n\n3)EVERYTIME YOU EAT A FOOD THE LENGTH OF THE SNAKE WILL BE INCREASED BY ' 1 ' ELEMENT AND THUS THE SCORE.\n\n4) HERE YOU ARE PROVIDED WITH THREE LIVES.\n\n5) YOUR LIFE WILL DECREASE AS YOU HIT THE WALL OR SANAKE'S BODY.\n\n6) YOU CAN PAUSE THE GAME IN ITS MIDDLE BY PRESSING ANY KEY.\n\n7) TO CONTINUE THE PAUSED GAME PRESS OTHER KEY ONCE AGAIN\n\n8) IF YOU WANT TO EXIT PRESS ESC. \n\n");
    printf("\n\nPRESS 'ENTER KEY' TO START THE GAME!...\n\n");
    scanf("%c",&a);
}

void saveGameScore()
{
    FILE *file=fopen("scores.txt","a");
    if(file==NULL)
	{
        printf("Error opening file.");
        return;
    }
    fprintf(file,"SCORE: %d\n",score);
    fclose(file);
}

int main()
{
    char choice;
    do {
        char a;
        intro();
        setup();

        while(!gameover)
		{
            boundary();
            input();
            move();
            Sleep(100);
        }
        saveGameScore();
        printf("\nDo you want to play again?\nIF YES THEN PRESS 'Y' : ");
        scanf("%c",&choice); 
    }while(choice == 'y' || choice == 'Y');
    return 0;
}


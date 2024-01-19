#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
int x,y,fruitx,fruity,flag;
int i,j,height=20,width=20,gameover,score;
int tailX[100],tailY[100],ntail;
int k,brojac=0,pr=0;
int prevX,prevY,prev2X,prev2Y,prevflag;
char niz[]={'A','L','E','K','S','A'};
char linije[6]={'_','_','_','_','_','_'};
int indexlinije=0;
int preprekax[100],preprekay[100];
time_t lastupdatetime = 0;


//void updatespikes()
//{
//	int i;
//	for(i=0;i<10;i++)
//	{
//		do
//		{
//			preprekax[i]=rand() % 20;
//			preprekay[i]=rand() % 20;
//		}while(preprekax[i] == 0 || preprekay[i] == 0 || (preprekax[i] == x && preprekay[i] == y));
//	}
//}

void setup()
{

	ntail=0;
	gameover=0;
	x=height/2;
	y=width/2;

	tailX[0]=x;
	tailY[0]=y;
	
label1:
	fruitx=rand() % 20;
	if(fruitx==0)
		goto label1;
	
label2:
	fruity=rand() % 20;
	if(fruity==0)
		goto label2;
score=0;
//updatespikes();
for(pr=0;pr<10;pr++)
{
				do
				{
					preprekax[pr]= rand() % 20;
					preprekay[pr]=rand() % 20;
				}while(preprekax[pr]==0 || preprekay[pr] == 0 || (preprekax[pr]==x && preprekay[pr]==y) || (preprekax[pr]==fruitx && preprekay[pr]==fruity) );
}

}

void draw()
{
	system("cls");
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{

			int isPrinted=0;

			for(pr=0;pr<10;pr++)
			{
				if(i==preprekax[pr] && j==preprekay[pr])
					{
						printf("X");
						isPrinted=1;
					}
			}

			if (i==0 || i == width-1 || j==0 || j == height-1)
			{
				printf("#");
				isPrinted=1;
			}
			else 
			{
				if (!isPrinted)
				{
					for ( k = 0; k < ntail; k++) {
                if (i == tailX[k] && j == tailY[k]) {
                    printf("o");
                    isPrinted=1;
                }
            }
				}
				
				if (!isPrinted)
				{
					if (i==x && j==y)
			
				printf("O");

					
			
			else if(i==fruitx && j==fruity)
			
			{
				if(brojac < sizeof(niz))
				{
					printf("%c",niz[brojac]);
				}
				
					
			else
			{
				gameover=1;
			}
					}
			else
				printf(" ");
				}
				
			}
		}
		printf("\n");
	}
	printf(" Score = %d",score);
	printf("\n Press X to quit.\n");
	for(i=0;i<sizeof(linije);i++)
	{
		printf(" %c ",linije[i]);
	}
	printf("\n");
}

void input()
{
	if(kbhit())
	{
		switch(getch())
		{
		case 'a':
			if(prevflag!=2)
			flag=1;
			break;
		case 'd':
			if(prevflag!=1)
			flag=2;
			break;
		case 'w':
			if(prevflag!=4)
			flag=3;
			break;
		case 's':
			if(prevflag!=3)
			flag=4;
			break;
		case 'x':
			gameover=1;
			break;
		}
	}
	prevflag=flag;
}

void logic()
{
	prevX=tailX[0];
	prevY=tailY[0];

	tailX[0]=x;
	tailY[0]=y;

	for (i=1;i<ntail;i++)
	{
		prev2X=tailX[i];
		prev2Y=tailY[i];
		tailX[i]=prevX;
		tailY[i]=prevY;
		prevX=prev2X;
		prevY=prev2Y;
		if(x==tailX[i] && y==tailY[i])
		{
			gameover=1;
		}
	}

	

	switch(flag)
	{
	case 1:
		y--;
		break;
	case 2:
		y++;
		break;
	case 3:
		x--;
		break;
	case 4:
		x++;
		break;
	default:
		break;
	}



	if (x<0 || x > height-1 || y<0 || y > width-1)
	{
		if(ntail>0)
		{
			ntail--;
			x=height/2;
			y=width/2;
			score-=10;
			Sleep(1000);
		}
		else
		{
			gameover=1;
		}
	}

	for(pr=0;pr<10;pr++)
	{
		if(x==preprekax[pr] && y==preprekay[pr])
	{
		if(ntail>0)
		{
			ntail--;
			x=height/2;
			y=width/2;
			score-=10;
			Sleep(1000);
		}
		else
		{
			gameover=1;
		}
	}
	}

	if(x==fruitx && y==fruity)
	{
		 indexlinije++;
	
		for(i=0;i<indexlinije;i++)
		{
			linije[i]=niz[i];
		}
		
		do
		{
			fruitx=rand()%20;
		}
		while(fruitx==0);
		do
		{
			fruity=rand()%20;
		}while(fruity==0);
		score+=10;
		ntail++;
		brojac++;
	   



}
}

int main()
{
	/*time_t currenttime = time(NULL);
	lastupdatetime=currenttime;*/
	setup();
	while(!gameover)
	{

//		if((currenttime - lastupdatetime)>=10)
//{
//	updatespikes();
//	lastupdatetime=currenttime;
//}

		draw();
		input();
		logic();
		Sleep(100);
	}
	return 0;
		
}
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include<time.h>
#include<ctype.h>
#include <time.h>
#include <windows.h>
#include <process.h>
#include <MMsystem.h>

#define UP 72        //for arrow keys//
#define DOWN 80
#define LEFT 75
#define RIGHT 77

#define SIZE 4
#define BORDER 219
#define ESC 57
#define PR 2

char choose;
int optm;
int Matrix[SIZE+1][SIZE+1]={0};//for 2048//
int score=2048,last=0;

int length;         //for snake game//
int bend_no;
int len;
char key;
void record();
void load();
int life;
void Delay(long double);
void Move();
void Food();
int Score();
void Print();
void gotoxy(int x, int y);
void GotoXY(int x,int y);
void Bend();
void Boarder();
void Down();
void Left();
void Up();
void Right();
void ExitGame();
int Scoreonly();
struct coordinate
{
    int x;
    int y;
    int direction;
};

typedef struct coordinate coordinate;

coordinate head, bend[500],food,body[30];



char square[10] = {'o','1','2','3','4','5','6','7','8','9'};//for tic-tac-toe//
int checkWin();
void drawBoard();



void color_window();    //for 2048//
void display_2048();
void print_2048_box();
void moving_key(int);
void random_movement_create();
void start_random_movement();
int temporary_count();
void end_of_2048();
void record_database();
void down_key_arrow();
void up_key_arrow();
void left_key_arrow();
void right_key_arrow();
void start_windows1();


void snake();//for main//
void t3();
void a2048();
void start_windows();
void wait();
void waitL();

void start_windows()      //the starting screen//
{
    int i;
    system("color 5F");
    char s1[]=" WELCOME TO THE MAIN GAME MENU !!! ";
    char s2[]="PRESS ANY KEY TO CONTINUE";
    char s3[]="Choose the game you want to play.";

    char s5[]="THERE ARE SOME GAMES THAT ARE AVAILABLE.";



    waitL();
    waitL();

    printf("\n\n\n\n\n\n\n\t\t\t\t");
    printer(s1);
    waitL();
    waitL();
    printf("\n\n\n\n\t\t\t\t");
    printer(s2);
    while(!kbhit());
    printf("\n\n\n\n\t\t\t");
    printer(s5);
    waitL();
    printf("\n\n\n\n\t\t\t\t");
    waitL();
    printer(s3);
    waitL();
    waitL();
    waitL();
    waitL();
    waitL();
    waitL();
    system("cls");

    printf("\n\n\t\t\t\t\t");

    for(i=0;i<10;i++)
    {
        waitL();
    }
    system("cls");
    printf("\n\n\n\t\t\tLIST OF THE AVAILABLE GAMES\n\n\n");
    printf(" (1) Snake\n\n");
    printf(" (2) 2048\n\n");
    printf(" (3) Tic-Tac-Toe\n\n\n\n");
    printf("Press any key to proceed and then enter the serial number of game you want to play.\n");
    while(!kbhit());
}

void wait()
{
    int i;
    for(i=0;i<4500000;i++);
}
void waitL()
{
    int i;
    for(i=0;i<25;i++)
    {
        wait();
    }
}

printer(char s[])
{
    int i=0;
    while(s[i]!='\0')
    {
        printf("%c",s[i]);
        wait();
        wait();
        i++;
    }
}

void snake()//main of snake
{
    char key;

    Print();

    system("cls");

    load();

    length=5;

    head.x=25;

    head.y=20;

    head.direction=RIGHT;

    Boarder();

    Food(); //to generate food coordinates initially

    life=3; //number of extra lives

    bend[0]=head;

    Move();   //initialing initial bend coordinate

}
void Move()
{
    int a,i;

    do
    {

        Food();
        fflush(stdin);

        len=0;

        for(i=0; i<30; i++)

        {

            body[i].x=0;

            body[i].y=0;

            if(i==length)

                break;

        }

        Delay(length);

        Boarder();

        if(head.direction==RIGHT)

            Right();

        else if(head.direction==LEFT)

            Left();

        else if(head.direction==DOWN)

            Down();

        else if(head.direction==UP)

            Up();

        ExitGame();

    }
    while(!kbhit());

    a=getch();

    if(a==27)

    {

        system("cls");

        exit(0);

    }
    key=getch();

    if((key==RIGHT&&head.direction!=LEFT&&head.direction!=RIGHT)||(key==LEFT&&head.direction!=RIGHT&&head.direction!=LEFT)||(key==UP&&head.direction!=DOWN&&head.direction!=UP)||(key==DOWN&&head.direction!=UP&&head.direction!=DOWN))

    {

        bend_no++;

        bend[bend_no]=head;

        head.direction=key;

        if(key==UP)

            head.y--;

        if(key==DOWN)

            head.y++;

        if(key==RIGHT)

            head.x++;

        if(key==LEFT)

            head.x--;

        Move();

    }

    else if(key==27)

    {

        system("cls");

        exit(0);

    }

    else

    {

        printf("\a");

        Move();

    }
}

void gotoxy(int x, int y)
{

    COORD coord;

    coord.X = x;

    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}
void GotoXY(int x, int y)
{
    HANDLE a;
    COORD b;
    fflush(stdout);
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a,b);
}
void load()
{
    int row,col,r,c,q;
    gotoxy(36,14);
    printf("loading...");
    gotoxy(30,15);
    for(r=1; r<=20; r++)
    {
        for(q=0; q<=100000000; q++); //to display the character slowly
        printf("%c",177);
    }
    getch();
}
void Down()
{
    int i;
    for(i=0; i<=(head.y-bend[bend_no].y)&&len<length; i++)
    {
        GotoXY(head.x,head.y-i);
        {
            if(len==0)
                printf("v");
            else
                printf("*");
        }
        body[len].x=head.x;
        body[len].y=head.y-i;
        len++;
    }
    Bend();
    if(!kbhit())
        head.y++;
}
void Delay(long double k)
{
    Score();
    long double i;
    for(i=0; i<=(10000000); i++);
}
void ExitGame()
{
    int i,check=0;
    for(i=4; i<length; i++) //starts with 4 because it needs minimum 4 element to touch its own body
    {
        if(body[0].x==body[i].x&&body[0].y==body[i].y)
        {
            check++;    //check's value increases as the coordinates of head is equal to any other body coordinate
        }
        if(i==length||check!=0)
            break;
    }
    if(head.x<=10||head.x>=70||head.y<=10||head.y>=30||check!=0)
    {
        PlaySound(TEXT("hurt.wav"),NULL,SND_SYNC);
        life--;
        if(life>=0)
        {
            head.x=25;
            head.y=20;
            bend_no=0;
            head.direction=RIGHT;
            Move();
        }
        else
        {
            system("cls");
            PlaySound(TEXT("over2.wav"),NULL,SND_SYNC);
            printf("All lives completed\nBetter Luck Next Time!!!\nPress any key to quit the game\n");
            record();
            
                exit(0);

            
        }
    }
}
void Food()
{
    if(head.x==food.x&&head.y==food.y)
    {
        PlaySound(TEXT("point.wav"),NULL,SND_SYNC);
        length++;
        time_t a;
        a=time(0);
        srand(a);
        food.x=rand()%70;
        if(food.x<=10)
            food.x+=11;
        food.y=rand()%30;
        if(food.y<=10)

            food.y+=11;
    }
    else if(food.x==0)/*to create food for the first time coz global variable are initialized with 0*/
    {
        food.x=rand()%70;
        if(food.x<=10)
            food.x+=11;
        food.y=rand()%30;
        if(food.y<=10)
            food.y+=11;
    }
}
void Left()
{
    int i;
    for(i=0; i<=(bend[bend_no].x-head.x)&&len<length; i++)
    {
        GotoXY((head.x+i),head.y);
        {
            if(len==0)
                printf("<");
            else
                printf("*");
        }
        body[len].x=head.x+i;
        body[len].y=head.y;
        len++;
    }
    Bend();
    if(!kbhit())
        head.x--;

}
void Right()
{
    int i;
    for(i=0; i<=(head.x-bend[bend_no].x)&&len<length; i++)
    {
        //GotoXY((head.x-i),head.y);
        body[len].x=head.x-i;
        body[len].y=head.y;
        GotoXY(body[len].x,body[len].y);
        {
            if(len==0)
                printf(">");
            else
                printf("*");
        }
        /*body[len].x=head.x-i;
        body[len].y=head.y;*/
        len++;
    }
    Bend();
    if(!kbhit())
        head.x++;
}
void Bend()
{
    int i,j,diff;
    for(i=bend_no; i>=0&&len<length; i--)
    {
        if(bend[i].x==bend[i-1].x)
        {
            diff=bend[i].y-bend[i-1].y;
            if(diff<0)
                for(j=1; j<=(-diff); j++)
                {
                    body[len].x=bend[i].x;
                    body[len].y=bend[i].y+j;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
            else if(diff>0)
                for(j=1; j<=diff; j++)
                {
                    /*GotoXY(bend[i].x,(bend[i].y-j));
                    printf("*");*/
                    body[len].x=bend[i].x;
                    body[len].y=bend[i].y-j;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
        }
        else if(bend[i].y==bend[i-1].y)
        {
            diff=bend[i].x-bend[i-1].x;
            if(diff<0)
                for(j=1; j<=(-diff)&&len<length; j++)
                {
                    /*GotoXY((bend[i].x+j),bend[i].y);
                    printf("*");*/
                    body[len].x=bend[i].x+j;
                    body[len].y=bend[i].y;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
            else if(diff>0)
                for(j=1; j<=diff&&len<length; j++)
                {
                    /*GotoXY((bend[i].x-j),bend[i].y);
                    printf("*");*/
                    body[len].x=bend[i].x-j;
                    body[len].y=bend[i].y;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
        }
    }
}
void Boarder()
{
    system("cls");
    int i;
    GotoXY(food.x,food.y);   /*displaying food*/
    printf("F");
    for(i=10; i<71; i++)
    {
        GotoXY(i,10);
        printf("!");
        GotoXY(i,30);
        printf("!");
    }
    for(i=10; i<31; i++)
    {
        GotoXY(10,i);
        printf("!");
        GotoXY(70,i);
        printf("!");
    }
}
void Print()
{
    //GotoXY(10,12);
    printf("\tWelcome to the mini Snake game.(press any key to continue)\n");
    getch();
    system("cls");
    printf("\tGame instructions:\n");
    printf("\n-> Use arrow keys to move the snake.\n\n-> You will be provided foods at the several coordinates of the screen which you have to eat. Everytime you eat a food the length of the snake will be increased by 1 element and thus the score.\n\n-> Here you are provided with three lives. Your life will decrease as you hit the wall or snake's body.\n\n-> YOu can pause the game in its middle by pressing any key. To continue the paused game press any other key once again\n\n-> If you want to exit press esc. \n");
    printf("\n\nPress any key to play game...");
    if(getch()==27)
        exit(0);
}
void record()
{
    char plname[20],nplname[20],cha,c;
    int i,j,px;
    FILE *info;
    info=fopen("record.txt","a+");
    getch();
    system("cls");
    printf("Enter your name\n");
    scanf("%[^\n]",plname);
    //************************
    for(j=0; plname[j]!='\0'; j++) //to convert the first letter after space to capital
    {
        nplname[0]=toupper(plname[0]);
        if(plname[j-1]==' ')
        {
            nplname[j]=toupper(plname[j]);
            nplname[j-1]=plname[j-1];
        }
        else nplname[j]=plname[j];
    }
    nplname[j]='\0';
    //*****************************
    //sdfprintf(info,"\t\t\tPlayers List\n");
    fprintf(info,"Player Name :%s\n",nplname);
    //for date and time

    time_t mytime;
    mytime = time(NULL);
    fprintf(info,"Played Date:%s",ctime(&mytime));
    //**************************
    fprintf(info,"Score:%d\n",px=Scoreonly());//call score to display score
    //fprintf(info,"\nLevel:%d\n",10);//call level to display level
    for(i=0; i<=50; i++)
        fprintf(info,"%c",'_');
    fprintf(info,"\n");
    fclose(info);
    printf("Wanna see past records press 'y'\n");
    cha=getch();
    system("cls");
    if(cha=='y')
    {
        info=fopen("record.txt","r");
        do
        {
            putchar(c=getc(info));
        }
        while(c!=EOF);
    }
    fclose(info);
}
int Score()
{
    int score;
    GotoXY(20,8);
    score=length-5;
    printf("SCORE : %d",(length-5));
    score=length-5;
    GotoXY(50,8);
    printf("Life : %d",life);
    return score;
}
int Scoreonly()
{
    int score=Score();
    system("cls");
    return score;
}
void Up()
{
    int i;
    for(i=0; i<=(bend[bend_no].y-head.y)&&len<length; i++)
    {
        GotoXY(head.x,head.y+i);
        {
            if(len==0)
                printf("^");
            else
                printf("*");
        }
        body[len].x=head.x;
        body[len].y=head.y+i;
        len++;
    }
    Bend();
    if(!kbhit())
        head.y--;
}
//end of snake//

//start of 2048//
void start_windows1()
{
    int i;
    system("color 5F");
    char s1[]=" WELCOME TO THE MOST EXCITING GAME THATS CAN BLOW YOUR MIND ";
    char s2[]="PRESS ANY KEY TO CONTINUE";
    char s3[]="Single-player sliding block puzzle game";

    char s5[]="HERE ARE SOME INSTRUCTION BEFORE TO PROCEED IN THE GAME";



    waitL();
    waitL();

    printf("\n\n\n\n\n\n\n\t\t\t\t");
    printer(s1);
    waitL();
    waitL();
    printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t");
    printer(s2);
    while(!kbhit());

    color_window();

    printf("\n\n\n\n\t");
    printer(s5);
    waitL();
    printf("\n\n\n\n\t\t");
    waitL();
    printer(s3);
    waitL();
    waitL();
    waitL();
    waitL();
    waitL();
    waitL();
    system("cls");

    printf("\n\n\t\t\t\t\t");

    for(i=0;i<10;i++)
    {
        waitL();
    }
    system("cls");
    printf("\n\n\n\t\t\tINSTRUCTIONS OF THE GAME 2048\n\n\n");
    printf(" (1) Enter arrow key to move\n\n");
    printf(" (2) For winning this game any one box have value 2048\n\n");
    printf(" (3) You have maximum 2048 try to win the game\n\n\n\n");
    printf("\t\t\t\t\t\tPRESS ANY KEY TO PLAY\n");
    while(!kbhit());
}

void color_window()
{
    int i=1;
    system("cls");
    system("color 5F");
    getch();
    waitL();
    printf("\n\t\t\t\t\t\tWELCOME TO 2048 GAME  ");
    while(i<2)
    {
        system("color  30");
        waitL();

        i++;
    }
}


void moving_key(int Arrow)
{

    switch(Arrow)
    {
        case UP:
            {
                up_key_arrow();
                break;
            }
        case DOWN:
            {

                down_key_arrow();
                break;
            }
        case LEFT:
            {
                left_key_arrow();
                break;
            }
        case RIGHT:
            {
                right_key_arrow();
                break;
            }
        default:
            {

                return;
            }
    }
    score--;
    Random_creater();
    display_2048();
}

void Random_creater()
{
    int temp1,temp2,add,i,j;
    srand(time(NULL));
    temp1=rand()%SIZE;

    srand(time(NULL));
    temp2=rand()%SIZE;

    if((temp1+temp2)%2==0)
        add=2;
    else
        add=4;

    for(i=0;i<temp1;i++)
    {
        for(j=temp2;j<SIZE;j++)
        {
            if(Matrix[i][j]==0)
            {
                Matrix[i][j]=add;
                return;
            }
        }
    }
}

void display_2048()
{
    int i,j;
    system("cls");

    print_2048_box();
    for(i=0;i<SIZE;i++)
    {
        printf("\t\t\t *",BORDER);
        for(j=0;j<SIZE;j++)
        {
            if(Matrix[i][j]==0)
            {
                printf("      ");
            }
            else
                printf(" %4d ",Matrix[i][j]);
        }
        printf("*\n\t\t\t *                        *\n",BORDER,BORDER,BORDER);
    }

    printf("\t\t\t **************************\n\n",BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER);

}
void print_2048_box()
{
    printf("\n\n\n\t\t\tTWO-ZERO-FOUR-EIGHT\n");
    printf("\t\t\t\t\t\t\t\t SCORE  : %d\n\n\n\n",score);
    printf("\t\t\t **************************\n",BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER);

}

void end_of_2048()
{
    printf("\n\n\t\t\t\tYOUR SCORE is  : %d",score);
    record_database();
}
void record_database(){
   char plname[20],nplname[20],cha,c;
   int i,j;
   FILE *info;
   info=fopen("record.txt","a+");
   getch();
   system("cls");
   printf("Enter your name\n");
   scanf("%[^\n]",plname);

   for(j=0;plname[j]!='\0';j++){
   nplname[0]=toupper(plname[0]);
   if(plname[j-1]==' '){
   nplname[j]=toupper(plname[j]);
   nplname[j-1]=plname[j-1];}
   else nplname[j]=plname[j];
   }
   nplname[j]='\0';

   fprintf(info,"Player Name :%s\n",nplname);


   time_t mytime;
  mytime = time(NULL);
  fprintf(info,"Played Date:%s",ctime(&mytime));

     fprintf(info,"Score:%d\n",score);

   for(i=0;i<=50;i++)
   fprintf(info,"%c",'_');
   fprintf(info,"\n");
   fclose(info);
   printf("wanna see past records press 'y'\n");
   cha=getch();
   system("cls");
   if(cha=='y'){
   info=fopen("record.txt","r");
   do{
       putchar(c=getc(info));
       }while(c!=EOF);}
     fclose(info);
     printf("\n\n\n\t\t\t\tPRESS ANY KEY TO EXIT\n");
     while(!kbhit());
    system("attrib +h +s record.txt");
}

void start_random_movement()
{
    Matrix[3][1]=8;
    Matrix[3][2]=32;
    Matrix[3][3]=16;
    Matrix[2][2]=8;
    Matrix[2][3]=8;
    Matrix[1][2]=8;

    display_2048();
}

int temporary_count()
{

    int temp=0,i,j;

    for(i=0;i<SIZE;i++)
    {
        for(j=0;j<SIZE;j++)
        {
            if(Matrix[i][j]==2048)
                return(1);
            if(Matrix[i][j]==0)
                temp=1;
        }
    }
    if(temp==1)
    {
        last=0;
        return(-99);
    }
    else
    {
        if(last==1)
        {
            return(0);
        }
        last=1;
        return(-99);
    }
}

void down_key_arrow()
{
    int i,j;
    for(j=0;j<SIZE;j++)
    {
        i=2;
        while(1)
        {
            while(Matrix[i][j]==0)
            {
                if(i==-1)
                    break;
                i--;
            }
            if(i==-1)
                break;
            while(i<SIZE-1 && (Matrix[i+1][j]==0 || Matrix[i][j]==Matrix[i+1][j]))
            {
                Matrix[i+1][j]+=Matrix[i][j];
                Matrix[i][j]=0;
                i++;
            }
            i--;
        }
    }
}
void up_key_arrow()
{
    int i,j;
    for(j=0;j<SIZE;j++)
    {
        i=1;
        while(1)
        {
            while(Matrix[i][j]==0)
            {
                if(i==SIZE)
                    break;
                i++;
            }
            if(i==SIZE)
                break;
            while(i>0 && (Matrix[i-1][j]==0 || Matrix[i][j]==Matrix[i-1][j]))
            {
                Matrix[i-1][j]+=Matrix[i][j];
                Matrix[i][j]=0;
                i--;
            }
            i++;
        }
    }
}
void right_key_arrow()
{
    int i,j;
    for(i=0;i<SIZE;i++)
    {
        j=2;
        while(1)
        {
            while(Matrix[i][j]==0)
            {
                if(j==-1)
                    break;
                j--;
            }
            if(j==-1)
                break;
            while(j<SIZE-1 && (Matrix[i][j+1]==0 || Matrix[i][j]==Matrix[i][j+1]))
            {
                Matrix[i][j+1]+=Matrix[i][j];
                Matrix[i][j]=0;
                j++;
            }
            j--;
        }
    }
}
void left_key_arrow()
{
    int i,j;
    for(i=0;i<SIZE;i++)
    {
        j=1;
        while(1)
        {
            while(Matrix[i][j]==0)
            {
                if(j==SIZE)
                    break;
                j++;
            }
            if(j==SIZE)
                break;
            while(j>0 && (Matrix[i][j-1]==0 || Matrix[i][j]==Matrix[i][j-1]))
            {
                Matrix[i][j-1]+=Matrix[i][j];
                Matrix[i][j]=0;
                j--;
            }
            j++;
        }
    }
}


a2048() //main of 2048//
{
    int aro;
    char Arrow;
    char s[]="THANKS FOR PLAYING, GOOD LUCK FOR NEXT TIME ";
    int temp;
    start_windows1();
    start_random_movement();
    Arrow=DOWN;
    while(Arrow!=ESC)
    {
        Arrow=getch();
        aro=Arrow;
        moving_key(Arrow);
        temp=temporary_count();
        if(temp==1)
        {
            PlaySound(TEXT("win2.wav"),NULL,SND_SYNC);
            printf("\n\t\t\tYOU WON");
           
            end_of_2048();
            break;
        }
        if(temp==0 || score<0)
        {
            printf("\n\t\t\tSORRY !  GAME OVER\n");
            PlaySound(TEXT("over.wav"),NULL,SND_SYNC);
            break;
        }
    }

    system("cls");
    printf("\n\n\n\t");
    printer(s);
    waitL();
    waitL();
    waitL();
    waitL();
}

void t3()//main of tic-tac-toe//
{
    system("color 4a");
    int player = 1, i ,choice;
    char mark; // X,O
    do {
        drawBoard();
        player = (player % 2) ? 1 : 2;
        printf("Player %d, enter the choice : ",player);
        scanf("%d",&choice);
        mark = (player == 1) ? 'X' : 'O';
        if(choice == 1 && square[1] == '1')
            square[1] = mark;
        else if(choice == 2 && square[2] == '2')
            square[2] = mark;
            else if(choice == 3 && square[3] == '3')
            square[3] = mark;
            else if(choice == 4 && square[4] == '4')
            square[4] = mark;
            else if(choice == 5 && square[5] == '5')
            square[5] = mark;
            else if(choice == 6 && square[6] == '6')
            square[6] = mark;
            else if(choice == 7 && square[7] == '7')
            square[7] = mark;
            else if(choice == 8 && square[8] == '8')
            square[8] = mark;
            else if(choice == 9 && square[9] == '9')
            square[9] = mark;

            else {
                printf("Invalid option !");
                player--;
                getch();
            }
            i = checkWin();
            player++;

    }while(i == -1);

    drawBoard();
    if(i==1){
        printf("==>Player %d won",--player);
        PlaySound(TEXT("win.wav"),NULL,SND_SYNC);

    }
    else {
        PlaySound(TEXT("over3.wav"),NULL,SND_SYNC);
        printf("==>Game draw");

    }
   
        getch();
        return 0;
}
int checkWin(){
    if(square[1] == square[2] && square[2] == square[3])
        return 1;
    else if (square[4] == square[5] && square[5] == square[6])
        return 1;
    else if(square[7] == square[8] && square[8] == square[9])
        return 1;
    else if(square[1] == square[4] && square[4] == square[7])
        return 1;
    else if(square[2] == square[5] && square[5] == square[8])
        return 1;
    else if(square[3] == square[6] && square[6] == square[9])
        return 1;
    else if(square[1] == square[5] && square[5] == square[9])
        return 1;
    else if(square[3] == square[5] && square[5] == square[7])
        return 1;
    else if(square[1] != '1' && square[2] != '2' && square[3] != '3' && square[4] !='4' && square[5] != '5' && square[6] != '6' && square[7] != '7' && square[8] != '8' && square[9] != '9')
        return 0;
    else
        return -1;
}

void drawBoard(){
    system("cls");
    printf("\n\n\t Tic Tac Toe \n\n");
    printf("Player1 (X) - Player2 (O) \n\n\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c  \n",square[1],square[2],square[3]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c  \n",square[4],square[5],square[6]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c  \n",square[7],square[8],square[9]);
    printf("     |     |     \n");
}
int main()
{
    int opt;
    start_windows();
    scanf("%d",&opt);
    switch(opt)
{
    case 1:
    snake();
    break;

    case 2:
    system("cls");
     a2048();
     break;

     case 3:
     system("cls");
     t3();
     break;

    default:
        printf("\n\n \t\t Invalid serial number");
        break;




}

}

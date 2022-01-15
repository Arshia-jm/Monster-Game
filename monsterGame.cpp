// programmer: Arshia Jannat Makan
// Game name: Monster

// How the game works : Run the program --> Enter your name --> Enter the height and width of the ground --> Enter the number of coins
// How to play game: play with  (W-D-S-A)to go Top down left right |Collect coins without hitting monsters

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <conio.h>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <fstream>
using namespace std;
////////////////////
const char wall='#';
const char empt='.';
const char coin='$';
int tcoin=10;


////////////////////
struct Position {
    int i;
    int j;
};
class Player{
    public:
        char skin='P';
        int score=0;
        struct Position pos;
        string name;
        bool is_alive=true;
    private:
        int myRandom(int s,int e){
            int tmp=e-s+1;
            return (rand()%tmp)+s;
        }
    public:
        void playerInit(char **g,int w,int h){
            while(true){
                int i=myRandom(0,h-1);
                int j=myRandom(0,w-1);
                if(g[i][j]!=wall){
                    pos.i=i;
                    pos.j=j;
                    break;
                }
            }
    }
};

class Monster{
    public:
        Monster(char **g,int ww,int hh){//Constructor
            ground=g;
            w=ww;
            h=hh;
        }
    public:
        char skin='M';
        struct Position pos;

    private:
        char **ground;
        int w,h;

    public://function

    private://function
        int myRandom(int s,int e){
            int tmp=e-s+1;
            return (rand()%tmp)+s;
        }
        bool is_available(int i,int j){
        //bool out=true;
        if(!(i>=0 && i<h && j>=0 && j<w)){
            return false;
            //out=false;
        }

        if(ground[i][j]==wall){
            return false;
            //out=false;
        }
        if(ground[i][j]=='M')
        {
            return false;
        }
        if(ground[i][j]=='$')
        {
            return false;
        }
        return true;
    }
    public:
        void monsterInit(){
            while(true){
                int i=myRandom(0,h-1);
                int j=myRandom(0,w-1);
                if(ground[i][j]==empt){
                    pos.i=i;
                    pos.j=j;
                    break;
                }
            }
        }
        struct Position randomMove(){
            struct Position p=pos;
            unsigned int timeout=1000;
            while(timeout>0){
                int r=myRandom(0,3);
                if(r==0){//R
                    if(is_available(pos.i,pos.j+1)){
                        p.i=pos.i;
                        p.j=pos.j+1;
                        break;
                    }
                }
                else  if(r==1){//L
                    if(is_available(pos.i,pos.j-1)){
                        p.i=pos.i;
                        p.j=pos.j-1;
                        break;
                    }
                }
                else if(r==2){//U
                    if(is_available(pos.i-1,pos.j)){
                        p.i=pos.i-1;
                        p.j=pos.j;
                        break;
                    }
                }
                else if(r==3){//D
                    if(is_available(pos.i+1,pos.j)){
                        p.i=pos.i+1;
                        p.j=pos.j;
                        break;
                    }
                }
                timeout--;
            }
            return p;
        }
};
////////Global variables
Player pl;
vector<Monster>monsters;
char **ground;
int w,h;
////////////////////////
int myRandom(int s,int e){

    int tmp=e-s+1;
    return (rand()%tmp)+s;
}
void groundInit(){
    ground=new char*[h];
    for(int i=0;i<h;i++){
        ground[i]=new char[w];
    }
}
void groundFull(){
    for(int i=0;i<h;i++){
        for(int j=0; j<w;j++){
            ground[i][j]=empt;
        }
    }
}
void wallInit(int n){
    int k=0;
    while(k<n){
        int i=myRandom(0,h-1);
        int j=myRandom(0,w-1);
        if(ground[i][j]==empt){
            ground[i][j]=wall;
            k++;
        }
    }
}
void showGround(){
    /////////////////
    system("cls");//clear cmd in windows
    cout<<pl.score<<" | remaining_coin: "<<tcoin-pl.score<<endl;
    for(int i=0;i<h;i++){
        for(int j=0; j<w;j++){
            if(ground[i][j]==wall){
                cout<<char(254);
            }
            else cout<<ground[i][j];
        }
    cout<<endl;
    }
}
void showGrave(){

    cout<<"Game Over"<<endl;
}
bool is_available(int i,int j){
    //bool out=true;
    if(!(i>=0 && i<h && j>=0 && j<w)){
        return false;
        //out=false;
    }

    if(ground[i][j]==wall){
        return false;
        //out=false;
    }
    return true;
}
void movePlayer(int i,int j){
    if(ground[i][j]=='M'){
        pl.is_alive=false;
        //ground[pl.pos.i][pl.pos.j]=empt;
    }

    else{
         if(ground[i][j]=='$')
    {

      pl.score++;

    }
        ground[pl.pos.i][pl.pos.j]=empt;
        pl.pos.i=i;
        pl.pos.j=j;
        ground[pl.pos.i][pl.pos.j]=pl.skin;
    }

}
void moveMonsters(){
    for(int i=0;i<monsters.size();i++){
        ground[monsters.at(i).pos.i][monsters.at(i).pos.j]=empt;
        monsters.at(i).pos=monsters.at(i).randomMove();
        ground[monsters.at(i).pos.i][monsters.at(i).pos.j]=monsters.at(i).skin;
        if(pl.pos.i==monsters.at(i).pos.i && pl.pos.j==monsters.at(i).pos.j)
        {
            pl.is_alive=false;
        }
    }
}
void coininit(int c){
    int k=0;
    while(k<c){
        int i=myRandom(0,h-1);
        int j=myRandom(0,w-1);
        if(ground[i][j]==empt){
            ground[i][j]=coin;

            k++;
        }
    }
}
void show_win()
{
      system("cls");
        cout<<"you win"<<endl;

}
void menu_page(){
    char key;
system("color 2");
cout<<"                                                         get the coins"<<endl;
cout<<endl;
cout<<endl;
cout<<endl;
cout<<endl;
cout<<"                                ---------------------"<<endl;
cout<<"                               |   1.start           |"<<endl;
cout<<"                               |   2.how to play     |"<<endl;
cout<<"                               |   3.about us        |"<<endl;
cout<<"                                ---------------------"<<endl;
key=getch();
switch(key){
case '2':
    system("cls");
    system("color D");
    cout<<"How to play game: play with  (W-D-S-A)to go Top down left right \nCollect coins without hitting monsters"<<endl;
    break;
case '3':
    system("cls");
    system("color 9");
    cout<<"Hi, I'm Arshia Jannat Makan \nI'm 15 and live in Iran"<<endl;
    cout<<"I have been working in the field of programming and robotics for three years"<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"My Id On Social Media"<<endl;
    cout<<"instagram => arshiajannatmakan.ajm"<<endl;
    cout<<"gmail => arshia.j.m1386@gmail.com"<<endl;
    cout<<"+989387375351"<<endl;
    break;
case '1':
    system("cls");
    system("color 7");
    cout<<"Height: ";
    cin>>w;
    cout<<"Width: ";
    cin>>h;
    cout<<"how many coins?";
    cin>>tcoin;
    system("color E");
    groundInit();//declareing 2d array
    groundFull();
    wallInit(w*h*0.09);
    coininit(tcoin);
    pl.playerInit(ground,w,h);
    ground[pl.pos.i][pl.pos.j]=pl.skin;
    int monster_n=pow((w*h),double(0.33))*2;
    for(int i =0;i<monster_n;i++){
        monsters.push_back(Monster(ground,w,h));
        monsters.at(i).monsterInit();
        ground[monsters.at(i).pos.i][monsters.at(i).pos.j]=monsters.at(i).skin;
    }
    while(pl.is_alive && tcoin>pl.score){

        showGround();
        char key;
        key=getch();// new
        switch(key){
            case 'w':
            case 'W':
                if(is_available(pl.pos.i-1,pl.pos.j)) movePlayer(pl.pos.i-1,pl.pos.j);
                break;
            case 's':
            case 'S':
                if(is_available(pl.pos.i+1,pl.pos.j)) movePlayer(pl.pos.i+1,pl.pos.j);
                break;
            case 'a':
            case 'A':
                if(is_available(pl.pos.i,pl.pos.j-1)) movePlayer(pl.pos.i,pl.pos.j-1);
                break;
            case 'd':
            case 'D':
                if(is_available(pl.pos.i,pl.pos.j+1)) movePlayer(pl.pos.i,pl.pos.j+1);;
                break;
            default:

                break;

        }
        moveMonsters();
    }
    system("color 2");
    if(pl.is_alive)
    {
    show_win();
    }
    else{
        system("color 4");
        showGrave();
    }
    break;
}
}

int main(){
    srand(time(NULL));
    cout<<"name: ";
    cin>>pl.name;
    menu_page();
    system("pause");
    return 0;
}

#include <iostream>
#include <conio.h>
#include <atomic>
#include <thread>
#include <chrono>
#include "windows.h"
#include <time.h>
#include <mutex>
#include <condition_variable>
using namespace std;
std::atomic<bool> bitti(false);
std::mutex yazmamutex;
std::mutex bildirimmutex;
std::condition_variable tetik;
std::mutex hareketmutex;
std::mutex mermimutex;
bool dusmansayisidegisti = false;
bool candegisti = false;
class Node{
    public:
    bool yasiyor=true;
    int x;
    int y;
    Node* next=nullptr;
};

void gotoxy(int x, int y) 
{   yazmamutex.lock();
    COORD coord;
    coord.X = x; 
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    yazmamutex.unlock();
}
void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}
//fonksiyonlar
void karakterbas(int x,int y){
gotoxy(x,y);
std::cout<<"+";
}
void dusmanbas(int x,int y,char c){
gotoxy(x,y);
std::cout<<c;
}

void sagagit(int x,int y,char c){
hareketmutex.lock();
    gotoxy(x,y);
std::cout<<" ";
gotoxy(x+1,y);
std::cout<<c;    
hareketmutex.unlock();
}
void solagit(int x,int y,char c){
hareketmutex.lock();
        gotoxy(x,y);
std::cout<<" ";
    gotoxy(x-1,y);
std::cout<<c;    
hareketmutex.unlock();
}
void yukarigit(int x,int y,char c){
hareketmutex.lock();
        gotoxy(x,y);
std::cout<<" ";
    gotoxy(x,y-1);
std::cout<<c;    
hareketmutex.unlock();
}
void altagit(int x,int y,char c){
hareketmutex.lock();
        gotoxy(x,y);
std::cout<<" ";
    gotoxy(x,y+1);
std::cout<<c;    
hareketmutex.unlock();
}

    //default veriler
    std::atomic<int> karakterx(60);
    std::atomic<int> karaktery(26);
    std::atomic<int> dusmanx(30);
    std::atomic<int> dusmany(30);
    const int cercevesagkenar=119;
    const int cercevesolkenar=0;
    const int cerceveust=0;
    const int cercevealt=28;
    int can=3;
    int dusmansayisi=10;
void dusmanhareket(Node* node,int adim){
int randomhareket=std::rand();
int randomsayi=0+randomhareket%4;
switch(randomsayi){
case 0:if(node->x-adim>cercevesolkenar){for(int i=0;i<adim;i++){solagit(node->x,node->y,'x');node->x--;}}
break;
case 1:if(node->x+adim<cercevesagkenar){for(int i=0;i<adim;i++){sagagit(node->x,node->y,'x');node->x++;}}
break;
case 2:if(node->y-adim>cerceveust){for(int i=0;i<adim;i++){yukarigit(node->x,node->y,'x');node->y--;}}
break;
case 3:if(node->y+adim<18){for(int i=0;i<adim;i++){altagit(node->x,node->y,'x');node->y++;}}
break;
default:dusmanhareket(node,1);
break;
}
}    
void mermihareket(Node* node){
    mermimutex.lock();
      gotoxy(node->x,node->y);
std::cout<<" ";
gotoxy(node->x,--node->y);
std::cout<<'|';   
mermimutex.unlock();

}
void dusmanmermihareket(Node* node){
    mermimutex.lock();
      gotoxy(node->x,node->y);
std::cout<<" ";
gotoxy(node->x,++node->y);
std::cout<<'|';   
    mermimutex.unlock();
}


class Llist{
    public:
Node* head=nullptr;
Node* mermihead=nullptr;
Node* dusmanmermihead=nullptr;
void dusmanekle(){
Node* newnode=new Node;
int randomx=std::rand();
int randomy=std::rand();
newnode->x=1+randomx%128;
newnode->y=1+randomy%19;
newnode->yasiyor=true;
if(head==nullptr){
head=newnode;

}
else{
Node* temp=head;
while(temp->next!=nullptr){
    temp=temp->next;
}
temp->next=newnode;
}
dusmanbas(newnode->x,newnode->y,'x');
}


void ateset(int x,int y){
Node* newnode=new Node;
newnode->x=x;
newnode->y=y-1;
newnode->yasiyor=true;
if(mermihead==nullptr){
mermihead=newnode;
}
else{
    Node* temp=mermihead;
while(temp->next!=nullptr){
    temp=temp->next;
}
temp->next=newnode;
}
}
void olumermisil(){
if(dusmanmermihead!=nullptr){
    Node* temp=dusmanmermihead;
    while(temp!=nullptr){
        if(!temp->yasiyor){gotoxy(temp->x,temp->y);cout<<" ";}
        temp=temp->next;
    }
}
}
void olusil(){
if(mermihead!=nullptr){
    Node* temp=mermihead;
    while(temp!=nullptr){
        if(!temp->yasiyor){gotoxy(temp->x,temp->y);cout<<" ";}
        temp=temp->next;
    }
}
}
void dusmanateset(int x,int y){
Node* newnode=new Node;
newnode->x=x;
newnode->y=y+1;
newnode->yasiyor=true;
if(dusmanmermihead==nullptr){
dusmanmermihead=newnode;
}
else{
    Node* temp=dusmanmermihead;
while(temp->next!=nullptr){
    temp=temp->next;
}
temp->next=newnode;
}}
};
Llist dusmanmermiliste;
Llist mermiliste;
Llist dusmanliste;
void hareketet(){
    hideCursor();
        //girdi al
char girdi=getch();
switch(girdi){
case 'a':if(karakterx-1!=cercevesolkenar){solagit(karakterx,karaktery,'+');karakterx--;}
break;
case 'd':if(karakterx+1!=cercevesagkenar){sagagit(karakterx,karaktery,'+');karakterx++;}
break;
case 'w':if(karaktery-1!=cerceveust){if(karaktery>20){yukarigit(karakterx,karaktery,'+');karaktery--;}}
break;
case 's': if(karaktery+1!=cercevealt){altagit(karakterx,karaktery,'+');karaktery++;}
break;
case ' ':mermiliste.ateset(karakterx,karaktery);
default: break;
}

}
void bitisekrani(){
    for(int i=0;i<28;i++){
    for(int i=0;i<120;i++){
        cout<<" ";
    }
    cout<<endl;
    }
    gotoxy(60,14);
    cout<<"oyun bitti";
}
void girdithread(){

    while(!bitti){
hareketet();
std::this_thread::sleep_for(std::chrono::milliseconds(10));
}
bitisekrani();
}

void dusman(){
for(int i=0;i<10;i++)dusmanliste.dusmanekle();
    while(!bitti){
Node* currnode=dusmanliste.head;
Node* mermi=mermiliste.head;
for(currnode;currnode!=nullptr;currnode=currnode->next){
if(currnode->yasiyor){
    int randomhareket=std::rand();
int randomsayi=0+randomhareket%10;
if(randomsayi==0){
    dusmanhareket(currnode,4);}
    else{dusmanhareket(currnode,1);}
int randoms=std::rand();
int ihtimal=0+randoms%100;
    if(ihtimal>90)dusmanmermiliste.dusmanateset(currnode->x,currnode->y);
    
}

}
mermiliste.olusil();
std::this_thread::sleep_for(std::chrono::milliseconds(750));
}
}
void mermi(){

    while(!bitti){
    if(mermiliste.mermihead!=nullptr){
         Node* currnode=mermiliste.mermihead;
         Node* dusman=dusmanliste.head;
for(currnode;currnode!=nullptr;currnode=currnode->next){
if(currnode->yasiyor){mermihareket(currnode);for(dusman;dusman!=nullptr;dusman=dusman->next)if(dusman->yasiyor&&currnode->y==dusman->y&&dusman->x==currnode->x){currnode->yasiyor=false;dusman->yasiyor=false; std::unique_lock<std::mutex> lock(bildirimmutex);dusmansayisi--;dusmansayisidegisti=true;tetik.notify_one();dusmanmermiliste.olumermisil();if(dusmansayisi==0)bitti=true;}if(currnode->y==1)currnode->yasiyor=false;}

    
}
    }
  std::this_thread::sleep_for(std::chrono::milliseconds(20));  

    }



}
void dusmanmermi(){

    while(!bitti){
    if(dusmanmermiliste.dusmanmermihead!=nullptr){
      
         Node* currnode=dusmanmermiliste.dusmanmermihead;
for(currnode;currnode!=nullptr;currnode=currnode->next){
if(currnode->yasiyor){dusmanmermihareket(currnode);if(currnode->y==karaktery&&karakterx==currnode->x){currnode->yasiyor=false; std::unique_lock<std::mutex> lock(bildirimmutex);can--;candegisti=true;tetik.notify_one();dusmanliste.olusil();if(can==0)bitti=true;}if(currnode->y==27)currnode->yasiyor=false;dusmanliste.olusil();}


}
    }
  std::this_thread::sleep_for(std::chrono::milliseconds(20));  

    }



}
void bildirim() {
    while (!bitti) {
            std::unique_lock<std::mutex> lock(bildirimmutex);
            tetik.wait(lock, [] { return dusmansayisidegisti || candegisti; });
        gotoxy(0, 0);
        cout << "dusman sayisi = " << dusmansayisi << "/10";
        gotoxy(30, 0);
        cout << "can = " << can;
        bildirimmutex.unlock();
        dusmansayisidegisti=false;
        candegisti=false;
    }
}
int main(){
   
    //cerceve ciz
for(int y=0;y<29;y++){
    for(int x=0;x<120;x++){
if(y!=0&&y!=28)if(x==0){std::cout<<"|";}
else if(x!=119)std::cout<<" ";
else std::cout<<"|";
if(y==0||y==28)std::cout<<"-";

    }
cout<<endl;
}
//baslamadan once
karakterbas(karakterx,karaktery);
std::thread girdithreadi(girdithread);
std::thread mermithreadi(mermi);
std::thread dusmanthreadi(dusman);
std::thread dusmanmermisi(dusmanmermi);
std::thread bildirimthreadi(bildirim);
//donguyu baslat
girdithreadi.join();
mermithreadi.join();
dusmanthreadi.join();
dusmanmermisi.join();
bildirimthreadi.join();
return 0;
}
#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include<dos.h>
#include<stdlib.h>
using namespace std;
#define HD bird.Hd.c
void gotoxy(int x, int y)
{
    static HANDLE h = NULL;  
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };  
    SetConsoleCursorPosition(h,c);
}
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
void setcursor(bool visible, DWORD size)// an con tro
{
	if(size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}
struct ToaDo{
	int x, y;
};
struct HinhDangBird{
	char c[2][6] = {{'/','-','-','o','\\',' '},{'|','_','_','_',' ','>'}};
};
struct Bird{
	HinhDangBird Hd;
	ToaDo td;
};
struct Vat_Can{
	ToaDo Tru[2];// 2 vat can	
};
struct Ten_Lua{
	ToaDo TL[2];// 2 ten lua
};
void Ve_Tuong();
void Khoi_Tao(Bird &bird,Vat_Can &VC,Ten_Lua &tenlua,int &score);
void Hien_Thi_Bird(Bird bird,int score);
void Xoa_Bird(Bird bird, int td);
void Hien_Thi_VC(Vat_Can VC, int idx);
void Xoa_VC(Vat_Can VC, int idx);
void Hien_Thi_TL(Ten_Lua tenlua, int idx);
void Xoa_Ten_Lua(Ten_Lua tenlua, int idx);
void Dieu_Khien(Bird &bird);
void Update_Score(Bird bird, Vat_Can VC, int &score);
int Game_Over(Vat_Can VC, Bird bird, Ten_Lua tenlua);
void VE();
void PlayEasy();
void PlayHard();
int main(){
	srand((unsigned)time(NULL));
	setcursor(0,0);
	while(1){
		system("cls");
		VE();
		gotoxy(48,22); cout << "1. EASY";
		gotoxy(48,23); cout << "2. HARD";
		gotoxy(48,24); cout << "3. QUIT\n";
		char key = getche();//doc 1 ki tu ban phim
		if(key == '1'){
			system("cls");
			PlayEasy();
		}
		else if(key == '2'){
			system("cls");
			PlayHard();
		}
		else if(key == '3') break;
	}
}
void Ve_Tuong(){// doc 2 -> 25, ngang 5 - > 115
	for(int i=5;i<=115;i++){
		gotoxy(i,2);
		cout << char(219);
	}
	for(int i=5;i<=115;i++){
		gotoxy(i,25);
		cout << char(219);
	}
	for(int i=3;i<=24;i++){
		gotoxy(5,i);
		cout << char(219);
	}
	for(int i=3;i<=24;i++){
		gotoxy(115,i);
		cout << char(219);
	}
	for(int i=3;i<=24;i++){
		gotoxy(90,i);
		cout << char(219);
	}
}
void Khoi_Tao(Bird &bird, Vat_Can &VC,Ten_Lua &tenlua,int &score){
	bird.td.x = 10;
	bird.td.y = 5;
	VC.Tru[0].x = 80;
	VC.Tru[0].y = 15 + rand()% 6;//15 -> 20 max - min +1
	VC.Tru[1].x = 80;
	VC.Tru[1].y = 15 + rand()% 6;
	tenlua.TL[0].x = 80;
	tenlua.TL[0].y = 5 + rand()% 16;// 5 -> 20
	tenlua.TL[1].x = 80;
	tenlua.TL[1].y = 5 + rand()% 16;
	score = 0;
}
void Hien_Thi_Bird(Bird bird, int score){
	for(int i=0;i<2;i++){
		for(int j=0;j<6;j++){                                            
			gotoxy(j+bird.td.x,i+bird.td.y);
			cout << HD[i][j];
		}
		cout << endl;
	}
	gotoxy(96,6); cout << " FLAPPY BIRD";
	gotoxy(96,8); cout << "-------------";
	gotoxy(98,9); cout << "SCORE: " << score;
	gotoxy(96,10); cout << "-------------";
	
}
void Hien_Thi_VC(Vat_Can VC, int idx){
	for(int i=VC.Tru[idx].y;i<=24;i++){
		gotoxy(VC.Tru[idx].x,i);
		cout << char(219) << char(219) << char(219) << char(219);
	}
	for(int i=3;i<=VC.Tru[idx].y-10;i++){//10 la khoang cach giua 2 vat can
		gotoxy(VC.Tru[idx].x,i);
		cout << char(219) << char(219) << char(219) << char(219);
	}
	if(VC.Tru[idx].x == 6) return;
}
void Xoa_Bird(Bird bird, int td){
	if(td < bird.td.y){
//	xoa tren
		gotoxy(bird.td.x,bird.td.y);
		cout << "      ";
		gotoxy(bird.td.x,bird.td.y-1);
		cout << "      ";
	}
	if(td > bird.td.y){
//	xoa duoi
		gotoxy(bird.td.x,bird.td.y+2);
		cout << "      ";
		gotoxy(bird.td.x,bird.td.y+3);
		cout << "      ";
	}
}	 
void Dieu_Khien(Bird &bird){
	if(_kbhit()){
		char key = _getch();
		if(key == 32){
			if(bird.td.y > 3)
				bird.td.y-=3;
		}
	}
	bird.td.y++;
}
void Xoa_VC(Vat_Can VC,int idx){
	for(int i=VC.Tru[idx].y;i<=24;i++){
		gotoxy(VC.Tru[idx].x+4,i);
		cout << " ";
	}
	for(int i=3;i<=VC.Tru[idx].y-10;i++){
		gotoxy(VC.Tru[idx].x+4,i);
		cout << " ";
	}
	if(VC.Tru[idx].x == 6){
		for(int i=VC.Tru[idx].y;i<=24;i++){
			gotoxy(VC.Tru[idx].x,i);
			cout << "    ";
		}
		for(int i=3;i<=VC.Tru[idx].y-10;i++){//8 la khoang cach giua 2 vat can
			gotoxy(VC.Tru[idx].x,i);
			cout << "    ";
		}
	}
}
void Hien_Thi_TL(Ten_Lua tenlua, int idx){
	gotoxy(tenlua.TL[idx].x + 3,tenlua.TL[idx].y-1);
	cout << char(174) << endl;
	gotoxy(tenlua.TL[idx].x,tenlua.TL[idx].y);
	cout << char(17);
	for(int i=1;i<6;i++){
		gotoxy(tenlua.TL[idx].x + i, tenlua.TL[idx].y);
		cout << char(254);
	}
	cout << endl;
	gotoxy(tenlua.TL[idx].x + 3,tenlua.TL[idx].y+1);
	cout << char(174);
	if(tenlua.TL[idx].x == 4){
		return;
	}
}
void Xoa_Ten_Lua(Ten_Lua tenlua, int idx){
	gotoxy(tenlua.TL[idx].x+5,tenlua.TL[idx].y-1);
	cout << " ";
	gotoxy(tenlua.TL[idx].x+5,tenlua.TL[idx].y+1);
	cout << " ";
	gotoxy(tenlua.TL[idx].x+6,tenlua.TL[idx].y);
	cout << "  ";
	if(tenlua.TL[idx].x == 6){
		gotoxy(tenlua.TL[idx].x,tenlua.TL[idx].y);
		cout << "      ";
		gotoxy(tenlua.TL[idx].x+3,tenlua.TL[idx].y-1);
		cout << " ";
		gotoxy(tenlua.TL[idx].x+3,tenlua.TL[idx].y+1);
		cout << " ";
	} 
}
void Update_Score(Bird bird, Vat_Can VC, int &score){
	if(bird.td.x == VC.Tru[0].x + 1) score++;
	if(bird.td.x == VC.Tru[1].x + 1) score++;
}
int Game_Over(Vat_Can VC, Bird bird, Ten_Lua tenlua){
	//-----------cham tuong---------//
	if(bird.td.y == 3 || bird.td.y == 23) return -1;//23 toa do tinh tu cai dau
	//-----------cham tru-----------//
	for(int i=0;i<2;i++){
		if(abs(bird.td.x - VC.Tru[i].x) <= 3 && bird.td.y == VC.Tru[i].y-2 || abs(bird.td.x - VC.Tru[i].x) <= 3 && bird.td.y == VC.Tru[i].y - 10)
			return -1;//cham vao giua 2 dau cot
		if(bird.td.x + 5 == VC.Tru[i].x && bird.td.y <= VC.Tru[i].y - 10)
			return -1;//cham vao tru tren
		if(bird.td.x + 5 == VC.Tru[i].x && bird.td.y >= VC.Tru[i].y-1)
			return -1;//cham vao tru duoi
		if(bird.td.x + 4 == tenlua.TL[i].x && bird.td.y == tenlua.TL[i].y || bird.td.x + 4 == tenlua.TL[i].x && bird.td.y == tenlua.TL[i].y -1 )
			return -1;//cham truc tiep dau` ten lua
		if(abs(bird.td.x - tenlua.TL[i].x) <= 5 && bird.td.y == tenlua.TL[i].y - 3 || abs(bird.td.x - tenlua.TL[i].x) <= 5 && bird.td.y == tenlua.TL[i].y +2 )
			return -1; //cham tren va cham duoi
	}
}
void VE(){
	//----------ve bird---------//
	for(int i=0;i<10;i++){
		gotoxy(51+i,10);
		cout << char('#');
	}
	cout << endl;
	for(int i=0;i<2;i++){
		gotoxy(49+i,11);
		cout << char('#');
	}
	gotoxy(58,11); cout << char('#');
	gotoxy(61,11); cout << char('#');
	cout << endl;
	gotoxy(48,12); cout << char('#');
	gotoxy(57,12); cout << char('#');
	gotoxy(62,12); cout << char('#');
	cout << endl;
	gotoxy(47,13); cout << char('#');
	gotoxy(57,13); cout << char('#');
	gotoxy(61,13); cout << char('#');
	gotoxy(63,13); cout << char('#');
	cout << endl;
	gotoxy(46,14); cout << char('#');
	gotoxy(57,14); cout << char('#');
	gotoxy(61,14); cout << char('#');
	gotoxy(63,14); cout << char('#');
	cout << endl;
	for(int i=0;i<5;i++){
		gotoxy(46+i,15);
		cout << char('#');
	}
	gotoxy(58,15); cout << char('#');
	gotoxy(63,15); cout << char('#');
	cout << endl;
	gotoxy(45,16); cout << char('#');
	gotoxy(51,16);	cout << char('#');
	for(int i=0;i<6;i++){
		gotoxy(59+i,16);
		cout << char('#');
	}
	cout << endl;
	gotoxy(45,17); cout << char('#');
	gotoxy(51,17);	cout << char('#');
	for(int i=0;i<8;i++){
		gotoxy(58+i,17);
		cout << char('#');
	}
	cout << endl;
	for(int i=0;i<5;i++){
		gotoxy(46+i,18);
		cout << char('#');
	}
	for(int i=0;i<8;i++){
		gotoxy(57+i,18);
		cout << char('#');
	}
	cout << endl;
	gotoxy(47,19); cout << char('#');
	for(int i=0;i<7;i++){
		gotoxy(58+i,19);
		cout << char('#');
	}
	cout << endl;
	for(int i=0;i<2;i++){
		gotoxy(48+i,20);
		cout << char('#');
	}
	for(int i=0;i<5;i++){
		gotoxy(59+i,20);
		cout << char('#');
	}
	for(int i=0;i<9;i++){
		gotoxy(50+i,21); cout << char('#');
	}
	//----------ve chu---------//
	gotoxy(32,1); cout << "______ _                          ______ _         _    ";
	gotoxy(32,2); cout << "|  ___| |                         | ___ (_)       | |   ";
	gotoxy(32,3); cout << "| |_  | | __ _ _ __  _ __  _   _  | |_/ /_ _ __ __| |   ";
	gotoxy(32,4); cout << "|  _| | |/ _` | '_ \\| '_ \\| | | | | ___ \\ | '__/ _` |   ";
	gotoxy(32,5); cout << "| |   | | (_| | |_) | |_) | |_| | | |_/ / | | | (_| |   ";
	gotoxy(32,6); cout << "\\_|   |_|\\__,_| .__/| .__/ \\__, | \\____/|_|_|  \\__,_|   ";
	gotoxy(32,7); cout << "              | |   | |     __/ |                       ";
	gotoxy(32,8); cout << "              |_|   |_|    |___/                        ";
	//-----------ve tuong----------//
	for(int i=5;i<=110;i++){
		gotoxy(i,0); cout << char(219);
	}
	for(int i=5;i<=110;i++){
		gotoxy(i,27); cout << char(219);
	}
	for(int i=1;i<=26;i++){
		gotoxy(5,i); cout << char(219);
	}
	for(int i=1;i<=26;i++){
		gotoxy(110,i); cout << char(219);
	}
	//------------ve tru va ten lua-------//
	for(int i=23;i<=26;i++){
		gotoxy(32,i); cout << char(219) << char(219) << char(219) << char(219);
	}
	gotoxy(31,22); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219);
	for(int i=23;i<=26;i++){
		gotoxy(74,i); cout << char(219) << char(219) << char(219) << char(219);
	}
	gotoxy(73,22); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219);
	//ten lua
	for(int i=16;i<=20;i++){
		gotoxy(i,4); cout << char(254);
	}
	gotoxy(21,4); cout << char(16);
	gotoxy(18,3); cout << char(175);
	gotoxy(18,5); cout << char(175);
	for(int i=96;i<=100;i++){
		gotoxy(i,4); cout << char(254);
	}
	gotoxy(95,4); cout << char(17);
	gotoxy(98,3); cout << char(174);
	gotoxy(98,5); cout << char(174);
	
	gotoxy(32,20); cout << char(254);
	gotoxy(35,19); cout << char(254);
	gotoxy(32,18); cout << char(254);
	gotoxy(35,17); cout << char(254);
	gotoxy(32,16); cout << char(254);
	gotoxy(35,15); cout << char(254);
	gotoxy(32,14); cout << char(254);
	gotoxy(35,13); cout << char(254);
	
	gotoxy(74,20); cout << char(254);
	gotoxy(77,19); cout << char(254);
	gotoxy(74,18); cout << char(254);
	gotoxy(77,17); cout << char(254);
	gotoxy(74,16); cout << char(254);
	gotoxy(77,15); cout << char(254);
	gotoxy(74,14); cout << char(254);
	gotoxy(77,13); cout << char(254);
}
void PlayEasy(){
	int score;
	Bird bird;
	Vat_Can VC;
	Ten_Lua tenlua;
	Ve_Tuong();
	Khoi_Tao(bird,VC,tenlua,score);
	int check  = 0;
	while(1){
		Hien_Thi_Bird(bird,score);
		int td = bird.td.y;
		Dieu_Khien(bird);
		Xoa_Bird(bird,td);
		Hien_Thi_Bird(bird,score);
		//-------Vat can------//
		Hien_Thi_VC(VC,0);
		Xoa_VC(VC,0);
		VC.Tru[0].x--;
		if(abs(VC.Tru[0].x - VC.Tru[1].x) == 40 || abs(VC.Tru[0].x - VC.Tru[1].x) == 35){//khoang cach 5 40 80
			Hien_Thi_VC(VC,1);
			Xoa_VC(VC,1);
			VC.Tru[1].x--;
		}
		if(VC.Tru[0].x == 5){
			VC.Tru[0].x = 80;
			VC.Tru[0].y = 15 + rand()% 6;
		}
		if(VC.Tru[1].x == 5){
			VC.Tru[1].x = 80;
			VC.Tru[1].y = 15 + rand()% 6;
		}
		Update_Score(bird,VC,score);
		int over = Game_Over(VC,bird,tenlua);
		if(over == -1){
			system("cls");
			gotoxy(45,9); cout << "-----------------------";
			gotoxy(45,10); cout << "-------Game over-------";
			gotoxy(45,11); cout << "-----------------------";
			gotoxy(42,13); cout << "Press enter to go back to menu";
			while(getch() != 13);//getch() dung chuong trinh khi bam 1 phep nao do
			break;
		}
		Sleep(100);
	}
}
void PlayHard(){
	int score;
	Bird bird;
	Vat_Can VC;
	Ten_Lua tenlua;
	Ve_Tuong();
	Khoi_Tao(bird,VC,tenlua,score);
	int check  = 0;
	while(1){
		Hien_Thi_Bird(bird,score);
		int td = bird.td.y;
		Dieu_Khien(bird);
		Xoa_Bird(bird,td);
		Hien_Thi_Bird(bird,score);
		//-------Vat can------//
		Hien_Thi_VC(VC,0);
		Xoa_VC(VC,0);
		VC.Tru[0].x--;
		if(abs(VC.Tru[0].x - VC.Tru[1].x) == 40 || abs(VC.Tru[0].x - VC.Tru[1].x) == 35){//khoang cach 5 40 80
			Hien_Thi_VC(VC,1);
			Xoa_VC(VC,1);
			VC.Tru[1].x--;
		}
		if(VC.Tru[0].x == 5){
			VC.Tru[0].x = 80;
			VC.Tru[0].y = 15 + rand()% 6;
		}
		if(VC.Tru[1].x == 5){
			VC.Tru[1].x = 80;
			VC.Tru[1].y = 15 + rand()% 6;
		}
//		-------Ten lua------
		Hien_Thi_TL(tenlua,0);
		Xoa_Ten_Lua(tenlua,0);
		tenlua.TL[0].x-=2;
		if(abs(tenlua.TL[0].x - tenlua.TL[1].x) == 40 || abs(tenlua.TL[0].x - tenlua.TL[1].x) == 36){// 4 40 80
			Hien_Thi_TL(tenlua,1);
			Xoa_Ten_Lua(tenlua,1);
			tenlua.TL[1].x-=2;
		}
		if(tenlua.TL[0].x == 4){
			tenlua.TL[0].x = 80;
			tenlua.TL[0].y = 5 + rand()% 16;
		}
		if(tenlua.TL[1].x == 4){
			tenlua.TL[1].x = 80;
			tenlua.TL[1].y = 5 + rand()% 16;
		}
		Update_Score(bird,VC,score);
		int over = Game_Over(VC,bird,tenlua);
		if(over == -1){
			system("cls");
			gotoxy(45,9); cout << "-----------------------";
			gotoxy(45,10); cout << "-------Game over-------";
			gotoxy(45,11); cout << "-----------------------";
			gotoxy(42,13); cout << "Press enter to go back to menu";
			while(getch() != 13);//getch() dung chuong trinh khi bam 1 phep nao do
			break;
		}
		Sleep(100);
	}
}

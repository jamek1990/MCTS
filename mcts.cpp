#include<iostream>
#include<vector>
#include<algorithm>
#include <cstdio>
#include <sstream>
#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>

#include <gsl/gsl_math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include "generator.h"
using namespace std;

generator g;

using namespace std;

const int SIZE = 40;

int rekord[]={-4, 3, -4, 3, -4, -1, 0, -1, -4, -1, 0, -1, -2, -2, -4, 0, 0, -4, 3, -4, -1, -4, 3, -4, 2, 6, 2, 6, 2, 2, -2, 5, -2, 5, 2, 5, -1, 6, -1, 6, -1, 2, 0, 2, -4, 2, 0, 2, -2, 3, 0, 5, -4, 1, 1, -1, 0, -1, 4, -1, 0, 4, 2, 6, -2, 2, 1, 4, -1, 6, 3, 2, 1, 2, 0, 2, 4, 2, -2, 4, -2, 4, 2, 4, -2, 1, -2, 5, -2, 1, -1, 0, -4, 3, 0, -1, -1, 1, -1, 2, -1, -2, 0, 0, -2, 2, 2, -2, 1, 1, 2, 2, -2, -2, 2, 0, -2, 4, 2, 0, 2, 1, 2, 2, 2, -2, 0, 3, -2, 5, 2, 1, -3, 3, -4, 3, 0, 3, 0, 1, 0, 3, 0, -1, 3, 6, 3, 6, -1, 2, 0, 6, 0, 6, -4, 2, -3, 1, -4, 1, 0, 1, 1, 6, -1, 6, 3, 6, 0, 7, 0, 7, 0, 3, 3, 3, 0, 6, 4, 2, 1, 3, 1, 6, 1, 2, -3, 4, 0, 7, -4, 3, 4, 3, 0, 3, 4, 3, 3, 1, -1, 5, 3, 1, -3, 0, -3, 4, -3, 0, 1, 0, -3, 4, 1, 0, 3, 4, 0, 7, 4, 3, 4, 1, 0, 1, 4, 1, 0, -3, -4, 1, 0, -3, -5, -2, -1, 2, -5, -2, 1, -2, 1, 2, 1, -2, 5, 4, 5, 4, 1, 0, 3, 5, 3, 6, 3, 2, 4, 5, 4, 5, 0, 1, 4, -5, 0, -1, 4, -5, 3, 0, 3, 0, -1, -4, 4, 6, 4, 6, 0, 2, 4, 0, 0, 0, 4, 0, 3, -2, 3, 2, 3, -2, 4, 4, 4, 6, 4, 2, 4, -2, 4, 2, 4, -2, 0, -2, -1, -2, 3, -2, 0, -5, 4, -1, 0, -5, 6, 4, 2, 4, 6, 4, -2, 0, -4, 2, 0, -2, -2, -4, 2, 0, -2, -4, 0, -6, 0, -2, 0, -6, 5, 3, 6, 4, 2, 0, -5, 0, -5, 0, -1, 0, -2, -3, -2, 1, -2, -3, 5, 5, 5, 5, 5, 1, 6, 2, 2, 6, 6, 2, -3, -2, -5, 0, -1, -4, -3, -4, 1, 0, -3, -4, 6, 5, 2, 5, 6, 5, 6, 6, 6, 6, 2, 2, 7, 3, 7, 3, 3, -1, -4, -2, -5, -2, -1, -2, -3, -3, -3, 0, -3, -4, 6, 3, 6, 6, 6, 2, 8, 2, 4, 6, 8, 2, -5, -3, -1, 1, -5, -3, 8, 3, 4, 3, 8, 3, 7, 4, 7, 4, 3, 0, 7, 2, 4, 2, 8, 2, -4, -3, -5, -3, -1, -3, 8, 1, 4, 5, 8, 1, 6, 1, 8, 3, 4, -1, -5, -4, -1, 0, -5, -4, 7, 1, 4, 1, 8, 1, -4, -4, -5, -4, -1, -4, 7, 0, 7, 4, 7, 0, 6, 0, 8, 2, 4, -2, -4, -5, -4, -1, -4, -5, 8, -1, 4, 3, 8, -1, 8, 0, 4, 0, 8, 0, 8, -2, 8, 2, 8, -2, 7, -1, 4, 2, 8, -2, 6, -1, 4, -1, 8, -1, 6, -2, 6, 2, 6, -2, 7, -2, 3, 2, 7, -2, 7, -3, 3, 1, 7, -3, 5, -2, 3, -2, 7, -2, 7, -4, 7, 0, 7, -4, 5, -3, 5, 1, 5, -3, 6, -3, 2, 1, 6, -3, 4, -3, 8, 1, 4, -3, 6, -4, 2, 0, 6, -4, 4, -4, 8, 0, 4, -4, 3, -3, 3, -3, 7, -3, 5, -4, 3, -4, 7, -4, 1, -3, -1, -3, 3, -3, 1, -5, 4, -2, 0, -6, 6, -5, 2, -1, 6, -5, -1, -5, 3, -1, -1, -5, 1, -6, 1, -2, 1, -6, 6, -6, 6, -2, 6, -6, -1, -6, -1, -2, -1, -6, -5, -1, -5, -1, -1, -5, 5, -5, 2, -2, 6, -6, -2, -5, -5, -2, -1, -6, -6, -2, -2, 2, -6, -2, 4, -6, 8, -2, 4, -6, 3, -5, 0, -2, 4, -6, 2, -5, -1, -5, 3, -5, 7, -5, 3, -5, 7, -5, 3, -6, 3, -2, 3, -6, 2, -6, 2, -2, 2, -6, 0, -7, 4, -3, 0, -7, 4, -7, 0, -3, 4, -7, 2, -7, 6, -3, 2, -7, -2, -6, -2, -6, 2, -6, 5, -6, 2, -6, 6, -6, 4, -8, 4, -4, 4, -8, 3, -8, -1, -4, 3, -8, -2, -7, -2, -3, -2, -7, -3, -5, -6, -2, -2, -6, 5, -7, 5, -3, 5, -7, 3, -7, 0, -4, 4, -8, -5, -5, -5, -5, -1, -5, 3, -9, 7, -5, 3, -9, 1, -7, 1, -7, 5, -7, -5, -6, -5, -2, -5, -6, -6, -6, -2, -2, -6, -6, 3, -10, 3, -6, 3, -10, 2, -8, -1, -5, 3, -9, 0, -8, 4, -4, 0, -8, 1, -8, 0, -8, 4, -8, 2, -9, -1, -6, 3, -10, 2, -10, 2, -6, 2, -10, 1, -10, 5, -6, 1, -10, 1, -9, 1, -6, 1, -10, -1, -7, -2, -6, 2, -10, 0, -10, 4, -6, 0, -10, -3, -7, -3, -7, 1, -7, -1, -10, -1, -10, 3, -10, 0, -9, 0, -6, 0, -10, -1, -9, -1, -9, 3, -9, -2, -11, 2, -7, -2, -11, -1, -8, -1, -6, -1, -10, -3, -6, -5, -4, -1, -8, -4, -6, -6, -6, -2, -6, -3, -8, -3, -4, -3, -8, -2, -8, -5, -5, -1, -9, -4, -9, 0, -5, -4, -9, -4, -8, -4, -8, 0, -8, -4, -7, -4, -5, -4, -9, -5, -9, -1, -5, -5, -9, -2, -9, -5, -6, -1, -10, -5, -8, -1, -4, -5, -8, -3, -9, -5, -9, -1, -9, -2, -10, -2, -7, -2, -11, -4, -10, 0, -6, -4, -10, -5, -7, -6, -6, -2, -10, -5, -10, -5, -6, -5, -10, -6, -8, -2, -4, -6, -8, -3, -10, -5, -10, -1, -10, -6, -7, -6, -7, -2, -11, -4, -11, 0, -7, -4, -11, -7, -7, -7, -7, -3, -7, -3, -11, -7, -7, -3, -11, -3, -12, -3, -8, -3, -12, -4, -12, 0, -8, -4, -12, -4, -13, -4, -9, -4, -13, -7, -8, -3, -4, -7, -8, -6, -9, -7, -8, -3, -12, -6, -5, -6, -5, -6, -9, -8, -8, -8, -8, -4, -8};

struct point{
  int x;
	int y;
};

inline int hash_point(point p){
	return SIZE*p.y+p.x;
}

struct move{
	point bgn;
	short int dir; //0-SW 1-S 2-SE 3-E
	point pnt;
};
bool operator==(const move& m1, const move& m2){
    	if(m1.bgn.x!=m2.bgn.x)return false;
    	if(m1.bgn.y!=m2.bgn.y)return false;
    	if(m1.pnt.x!=m2.pnt.x)return false;
    	if(m1.pnt.y!=m2.pnt.y)return false;
    	if(m1.dir!=m2.dir)return false;
    	return true;
	}
inline int hash_move(move m){
	return hash_point(m.bgn)*10+m.dir;
}

move available_moves[100000];
int available_moves_size = 0;

bool points[SIZE][SIZE];
point points_clear[1000];
short int points_clear_size=0;

bool connections[SIZE*SIZE][SIZE*SIZE];
point connections_clear[1000];
short int connections_clear_size = 0;

move save_moves[1000];
short int save_moves_size=0;

int dir_x[4]={-1,0,1,1};
int dir_y[4]={1,1,1,0};

move pop[1000];
short int pop_size =0;

point p[36];

void cross(){
	p[0].x=0; p[0].y=0;p[1].x=0; p[1].y=1;
	p[2].x=0; p[2].y=2;p[3].x=0; p[3].y=3;
	p[4].x=1; p[4].y=3;p[5].x=2; p[5].y=3;
	p[6].x=3; p[6].y=3;p[7].x=3; p[7].y=4;
	p[8].x=3; p[8].y=5;p[9].x=3; p[9].y=6;
	p[10].x=4; p[10].y=6;p[11].x=5; p[11].y=6;
	p[12].x=6; p[12].y=6;p[13].x=6; p[13].y=5;
	p[14].x=6; p[14].y=4;p[15].x=6; p[15].y=3;
	p[16].x=7; p[16].y=3;p[17].x=8; p[17].y=3;
	p[18].x=9; p[18].y=3;p[19].x=9; p[19].y=2;
	p[20].x=9; p[20].y=1;p[21].x=9; p[21].y=0;
	p[22].x=8; p[22].y=0;p[23].x=7; p[23].y=0;
	p[24].x=6; p[24].y=0;p[25].x=6; p[25].y=-1;
	p[26].x=6; p[26].y=-2;p[27].x=6; p[27].y=-3;
	p[28].x=5; p[28].y=-3;p[29].x=4; p[29].y=-3;
	p[30].x=3; p[30].y=-3;p[31].x=3; p[31].y=-2;
	p[32].x=3; p[32].y=-1;p[33].x=3; p[33].y=0;
	p[34].x=2; p[34].y=0;p[35].x=1; p[35].y=0;
}

/*#######################################################################
	Funkcja: EXTEND
	Argumenty: move m
	Zwraca: bool czy ruch jest polaczony
  #######################################################################*/

inline bool extend(move m){
	if(connections[SIZE*m.bgn.y+m.bgn.x][SIZE*(m.bgn.y-dir_y[m.dir])+m.bgn.x-dir_x[m.dir]])
		return true;
	if(connections[SIZE*(m.bgn.y+4*dir_y[m.dir])+m.bgn.x+4*dir_x[m.dir]][SIZE*(m.bgn.y+5*dir_y[m.dir])+m.bgn.x+5*dir_x[m.dir]])
	  	return true;
	return false;
}

/*#######################################################################
	Funkcja: ADD_NEW_MOVE
	Argumenty: point pt
	Zwraca: int liczba ruchĂłw dodanych
	Cel: dodaje nowe moves po dodaniu punktu, aktualizuje wektor moves i moves2.
	jest odporna na bezsensowne moves bez polaczen.
  #######################################################################*/
  
int add_new_move(point pt){
	int wynik =0;
	int ill	 =0;
	int pon	 =0;
	int ok	 =0;
	move rucht;
	point ptg;
	
	//poziomo
	for(int i=0;i<9;i++){
		if(points[pt.x-4+i][pt.y]){
			if(ok > 0){
				if(!connections[SIZE*pt.y+pt.x-4+i-1][SIZE*pt.y+pt.x-4+i])
					ok += 1;
				else{
					pon = 0;
					ok = 1;
				}
			}else{
				ok = 1;
			}
		}else{
			if(pon == 1){
				ok = pt.x-4+i-ptg.x;
				ptg.x = pt.x-4+i;
				ptg.y = pt.y;
			}
			else{
				pon = 1;
				ptg.x = pt.x-4+i;
				ptg.y = pt.y;
				ok += 1;
			}
		}
		if(ok > 4 && (pon == 1 && (pt.x-4+i-ptg.x)<5)){
			rucht.pnt=ptg;
			rucht.bgn.x=pt.x-4+i-4;
			rucht.bgn.y=pt.y;
			rucht.dir=3;
			if(extend(rucht)){
				while(ill--){
					available_moves_size--;
					wynik--;
				}
				available_moves[available_moves_size]=rucht;
				available_moves_size++;
				wynik++;
				break;
			}
			available_moves[available_moves_size]=rucht;
			available_moves_size++;
			ill++;
			wynik++;
		}
	}
	//pionowo
	ok = 0;
	pon = 0;
	ill=0;
	for(int i = 0;i<9;i++){
		if(points[pt.x][pt.y-4+i]){
			if(ok > 0){
				if(!connections[SIZE*(pt.y-4+i-1) + pt.x][SIZE*(pt.y-4+i) + pt.x]){
					ok += 1;
				}
				else{
					pon =0;
					ok =1;
				}
			}
			else{
				ok = 1;
			}
		}else{
			if(pon == 1){
				ok = pt.y-4+i-ptg.y;
				ptg.x = pt.x;
				ptg.y = pt.y-4+i;
			}
			else{
				pon = 1;
				ptg.x = pt.x;
				ptg.y = pt.y-4+i;
				ok += 1;
			}
		}
		if(ok > 4 && (pon == 1 && (pt.y-4+i-ptg.y)<5)){
			rucht.pnt=ptg;
			rucht.bgn.x=pt.x;
			rucht.bgn.y=pt.y-4+i-4;
			rucht.dir=1;
			if(extend(rucht)){
				while(ill--){
					available_moves_size--;
					wynik--;
				}
				available_moves[available_moves_size]=rucht;
				available_moves_size++;
				wynik++;
				break;
			}
			available_moves[available_moves_size]=rucht;
			available_moves_size++;
			ill++;
			wynik++;
		}
	}
	//ukosL
	ok = 0;
	pon = 0;
	ill=0;
	for(int i=0;i<9;i++){
		if(points[pt.x-4+i][pt.y-4+i]){
			if(ok > 0){
				if(!connections[SIZE*(pt.y-4+i-1)+pt.x-4+i-1][SIZE*(pt.y-4+i)+pt.x-4+i]){
					ok +=1;
				}else{
					pon = 0;
					ok = 1;
				}
			}
			else{
				ok = 1;
			}
		}else{
			if(pon == 1){
				ok = pt.x-4+i-ptg.x;
				ptg.x = pt.x-4+i;
				ptg.y = pt.y-4+i;
			}else{
				pon = 1;
				ptg.x = pt.x-4+i;
				ptg.y = pt.y-4+i;
				ok += 1;
			}
  		}
		if(ok > 4 && (pon == 1 && (pt.x-4+i-ptg.x)<5)){
			rucht.pnt=ptg;
			rucht.bgn.x=pt.x-4+i-4;
			rucht.bgn.y=pt.y-4+i-4;
			rucht.dir=2;
			if(extend(rucht)){
				while(ill--){
					available_moves_size--;
					wynik--;
				}
				available_moves[available_moves_size]=rucht;
				available_moves_size++;
				wynik++;
				break;
			}
			available_moves[available_moves_size]=rucht;
			available_moves_size++;
			ill++;
			wynik++;
		}
	}
	//ukos_P
	ok = 0;
	pon = 0;
	ill=0;
	for(int i=0;i<9;i++){
		if(points[pt.x+4-i][pt.y-4+i]){
			if(ok > 0){
            if(!connections[SIZE*(pt.y-4+i-1)+pt.x+4-i+1][SIZE*(pt.y-4+i)+pt.x+4-i]){
					ok += 1;
				}else{
					ok = 1;
					pon = 0;
				}
			}
			else{
				ok = 1;
			}
		}
		else{
         if(pon == 1){
				ok = pt.y-4+i-ptg.y;
				ptg.x = pt.x+4-i;
				ptg.y = pt.y-4+i;
			}
			else{
				pon = 1;
				ptg.x = pt.x+4-i;
				ptg.y = pt.y-4+i;
				ok += 1;
			}
		}
		if(ok > 4 && (pon == 1 && (pt.y-4+i-ptg.y)<5)){
			rucht.pnt=ptg;
			rucht.bgn.x=pt.x+4-i+4;
			rucht.bgn.y=pt.y-4+i-4;
			rucht.dir=0;
			if(extend(rucht)){
				while(ill--){
					available_moves_size--;
					wynik--;
				}
				available_moves[available_moves_size]=rucht;
				available_moves_size++;
				wynik++;
				break;
			}
			available_moves[available_moves_size]=rucht;
			available_moves_size++;
			ill++;
			wynik++;
		}
	}
	return wynik;
}

/*#######################################################################
	Funckja: ADD_POINT
	Argumenty: point pt
	Zwraca: void
	Cel: aktualizuje tablice table po dodaniu nowego punktu, wywoluje funkcej
	ADD_NEW_MOVE.
  #######################################################################*/
void add_point(point pnt){
	points[pnt.x][pnt.y] = true;
	add_new_move(pnt);
}

/*#######################################################################
	Funckja: add_connection
	Argumenty: move m
	Zwraca: void
	Cel: dodaje polaczenie, uaktualnie tablice connections[][] oraz wektor
	do czyszczenia connections_clear
  #######################################################################*/
point con;
void add_connection(move m){
	for(int i=0;i<4;i++){
		con.x=SIZE*(m.bgn.y+i*dir_y[m.dir])+m.bgn.x+i*dir_x[m.dir];
		con.y=SIZE*(m.bgn.y+(i+1)*dir_y[m.dir])+m.bgn.x+(i+1)*dir_x[m.dir];
		connections[con.x][con.y]=true;
		connections[con.y][con.x]=true;
		connections_clear_size++;
		connections_clear[connections_clear_size]=con;
	}
}

/*#######################################################################
	Funckja: clear_all
	Argumenty: void
	Zwraca: void
	Cel: usuwa wszytskie punkty z planszy i polaczenia
  #######################################################################*/
void clear_all(){
	while(connections_clear_size!=0){
   		connections[connections_clear[connections_clear_size].x][connections_clear[connections_clear_size].y]=false;
   		connections[connections_clear[connections_clear_size].y][connections_clear[connections_clear_size].x]=false;
   		connections_clear_size--;
	}
	while(points_clear_size!=0){
		points[points_clear[points_clear_size].x][points_clear[points_clear_size].y]=false;
		points_clear_size--;
	}
}

/*#######################################################################
	Funckja: clear_ile
	Argumenty: ile
	Zwraca: void
	Cel: usuwa  punkty z planszy i polaczenia do pozycji z ile
  #######################################################################*/
void clear_ile(int ile){
	while(connections_clear_size!=4*ile){
   		connections[connections_clear[connections_clear_size].x][connections_clear[connections_clear_size].y]=false;
   		connections[connections_clear[connections_clear_size].y][connections_clear[connections_clear_size].x]=false;
   		connections_clear_size--;
	}
	while(points_clear_size!=ile){
		points[points_clear[points_clear_size].x][points_clear[points_clear_size].y]=false;
		points_clear_size--;
	}
}
void set_cross(){
	cross();
	point temp;
	for(int i=0;i<36;i++){
		temp.x = p[i].x+16;
		temp.y = p[i].y+18;
		add_point(temp);
	}
}

void show_points(){
	for(int i=0;i<SIZE;i++){
      for(int j=0;j<SIZE;j++){
			if(points[i][j])
			   cout<<"x";
			else
			   cout<<" ";
		}
		cout<<"\n";
	}
	cout<<"\n";
}

/*#######################################################################
	Funkcja: remove
	Argumenty: brak
	Zwraca: void
	Cel: usuwa bledne ruchy z wektora avaliable_moves
  #######################################################################*/
void remove(){
	pop_size=0;
	move m;
	int ok;
	for(int ii=0;ii<available_moves_size;ii++){
      m=available_moves[ii];
		if(points[m.pnt.x][m.pnt.y])
			continue;
		ok=1;
		for(int i=0;i<4;i++)
			if(connections[SIZE*(m.bgn.y+i*dir_y[m.dir])+m.bgn.x+i*dir_x[m.dir]][SIZE*(m.bgn.y+(i+1)*dir_y[m.dir])+m.bgn.x+(i+1)*dir_x[m.dir]]){
				ok=0;
				break;
			}
		if(ok){
			pop[pop_size]=available_moves[ii];
			pop_size++;
		}
	}
	for(int i =0;i<pop_size;i++)
		available_moves[i]=pop[i];
	available_moves_size=pop_size;
}

char name[10];
void save(int score){
	move m;
	 cout<<"\a";
	ostringstream os;
	os << score;
	string str = os.str();
	str = str+".txt";
   	for(int i=0; i<str.size(); i++)
		name[i]=str[i];
	std::ofstream o(name);
	for(int i=0;i<score;i++){
		m=save_moves[i];
		o<<m.pnt.x-20<<" "<<m.pnt.y-19<<" "<<m.bgn.x-20<<" "<<m.bgn.y-19<<" "<<m.bgn.x+4*dir_x[m.dir]-20<<" "<<m.bgn.y+4*dir_y[m.dir]-19<<"\n";
	}
}

inline bool check_move(move m){
	if(points[m.pnt.x][m.pnt.y])
			return false;
	if(connections[SIZE*m.bgn.y+m.bgn.x][SIZE*(m.bgn.y+dir_y[m.dir])+m.bgn.x+dir_x[m.dir]])
		return false;
	if(connections[SIZE*(m.bgn.y+3*dir_y[m.dir])+m.bgn.x+3*dir_x[m.dir]][SIZE*(m.bgn.y+4*dir_y[m.dir])+m.bgn.x+4*dir_x[m.dir]])
		return false;
	return true;
}
void check_con(){
	for(int i=0;i<SIZE*SIZE;i++)
		for(int j=0;j<SIZE*SIZE;j++)
			if(connections[i][j])
				cout<<"dupa";
}

void dodaj(move move_exe){
	add_connection(move_exe);
	add_point(move_exe.pnt);
	points_clear_size++;
	points_clear[points_clear_size]=move_exe.pnt;
	save_moves[save_moves_size]=move_exe;
	save_moves_size++;
}

struct node{
	move m;
	int visit;
	int ile;
	float x;
	
	int parent;
};
node tree[10000000];
vector<int> tree2[1000000];
void mcts(){
	//przygotuj drzewko:)
	node no;
	int root =0;
	int g=0;
	int w;
	int k;
	int liczba_wierz=1;
	move move_exe;
	int ile=0;
	int max_ile=0;
	tree[0].visit=0;
	while(1){
	//	qq++;
		//cout<<qq<<"\n";
		//wybieramy liscia
		clear_all();
		save_moves_size=ile=0;
		set_cross();
		g=root;
		while(tree[g].visit!=0){
			//wybierz najlepszy na razie losowo;]
			remove();
			g=tree2[g][rand()%tree2[g].size()];
			dodaj(tree[g].m);
			ile++;
		}
		//dodaj nowe
		remove();//to usuwanie wplywa na zlozonosc
		for(int i=0;i<available_moves_size;i++){
				no.m=available_moves[i];
				no.visit=0;
				no.x=0;
				no.parent=g;
				tree[liczba_wierz]=no;
				tree2[g].push_back(liczba_wierz);
				liczba_wierz++;
		}
		//wybierz nowy
		w=rand()%available_moves_size;
		dodaj(available_moves[w]);
		ile++;
		//graj losowo
		while(!available_moves_size==0){
			k=rand()%available_moves_size;
			if(check_move(available_moves[k])){
				dodaj(available_moves[k]);
				ile++;
			}
			else{
				available_moves[k]=available_moves[available_moves_size-1];
				available_moves_size--;
			}
		}
		//cout<<liczba_wierz<<"\n";
		//zapisze maks
		if(max_ile<ile){
			max_ile=ile;
			save(ile);
			cout<<"score: "<<max_ile<<"\n";
		}
		//odswiez ruchy
		while(w!=0){
			tree[w].visit++;
			tree[w].ile=max(tree[w].ile,ile);
			w=tree[w].parent;
		}
	}
}




int ocena[100000];
int times[100000];
int kol[10000];
void random_layer_price_game(int iq){
	//ruchy jako kolejka:)
	move move_exe;
	int ile=iq;
	int max_ile=0;
	bool layer[10000];
	short int layer_size = 0;
	
	move layer_m[100];
	short int layer_m_size = 0;
	move layer_t[100000];
	short int layer_t_size = 0;
	int qtime=0;
	int qt=100;
	for(int i=0;i<100000;i++)ocena[i]=times[i]=0;
	move start[1000];
	int nowe_ruchy[10000];
	int nowe_ruchy_size=0;
	int start_size=0;
	//set_cross();
	for(int i=0;i<available_moves_size;i++)
		start[i]=available_moves[i];
	start_size=available_moves_size;
	int k=0;
	int dupa;
	int dupa2;
	int maks_dupa2;
	int hm;
	int nowy=0;
	while(1){
		qtime++;
		clear_ile(iq);
		save_moves_size=ile=iq;
		available_moves_size=0;
		
		for(int i=0;i<start_size;i++)
			available_moves[i]=start[i];
		available_moves_size=start_size;
		dupa=0;
		layer_t_size=0;
		
		while(available_moves_size!=dupa){
			dupa2=available_moves_size;
			for(int i=dupa;i<dupa2;i++){
				hm=hash_move(available_moves[i]);
				if(ocena[hm]>=max_ile || times[hm]<qtime){
					if(rand()%100<85)
					layer[i]=true;
					else
					layer[i]=false;
				}else
					if(rand()%100<95)
						layer[i]=false;
					else
						layer[i]=true;;
			}
			/*for(int i=dupa;i<dupa2;i++){
				kol[i]=i;
			}
			for(int i=dupa;i<dupa2/2;i++){
				int w=rand()%(dupa2-dupa);
				swap(kol[i],kol[dupa+w]);
			}*/
			
			layer[dupa+rand()%dupa2]=false;
			layer[dupa+rand()%dupa2]=true;
			for(int i=dupa;i<dupa2;i++){
				if(layer[i]){
					if(check_move(available_moves[i])){
						move_exe = available_moves[i];
						add_connection(move_exe);
					   	add_point(move_exe.pnt);
					   	points_clear_size++;
					   	points_clear[points_clear_size]=move_exe.pnt;
					   	save_moves[save_moves_size]=move_exe;
						save_moves_size++;
					   	ile++;
					}
				}
			}
			for(int i=dupa;i<dupa2;i++){
				if(!layer[i]){
					layer_t[layer_t_size]=available_moves[i];
					layer_t_size++;
				}
			}
			dupa=dupa2;
			if(dupa==available_moves_size){
				for(int i=0;i<layer_t_size;i++)
					available_moves[i]=layer_t[i];
				available_moves_size=layer_t_size;
				layer_t_size=0;
				dupa=0;
			}
		}
		for(int i=0;i<ile;i++){
			hm=hash_move(save_moves[i]);
			if(ocena[hm]==0 ){
				nowy++;
				nowe_ruchy[nowe_ruchy_size++]=hm;
				cout<<"nowy: "<<nowy<<"\n";
			}
			ocena[hm]=max(ocena[hm],ile);
			times[hm]=qtime+qt+rand()%qt;
		}
		available_moves_size=0;
		if(max_ile<ile){
			cout<<"score: "<<max_ile<<" "<<ile<<"\n";
			max_ile=ile;
			save(ile);
		}
	}
}
int random_price_time_game(int iq){
	move move_exe;
	int ile=iq;
	int max_ile=0;
	int max_ile2=0;
	int k;
	int ocena[100000];
	int ile_razy[100000];
	int frozen_ocena[100000];
	int nowe_ruchy[10000];
	int nowe_ruchy_size=0;
	int time_frozen=10000;
	
	
	int times[100000];
	
	int qtime=0;
	int qt=50;
	int nowy=0;
	for(int i=0;i<100000;i++)ile_razy[i]=frozen_ocena[i]=ocena[i]=times[i]=0;
	move start[1000];
	int start_size=0;
	//set_cross();
	for(int i=0;i<available_moves_size;i++)
		start[i]=available_moves[i];
	start_size=available_moves_size;
	int hm;
	int go=0;
	int FR=0;
	int t_inf=100000000;
	int iq2=iq;
	while(1){
		qtime++;
		if(qtime%time_frozen==0){
			//qtime=0;
			//cout<<"|";
			if(FR==0){
				for(int i=0;i<nowe_ruchy_size;i++){
					frozen_ocena[nowe_ruchy[i]]=max(frozen_ocena[nowe_ruchy[i]],ocena[nowe_ruchy[i]]);
					//if(ile_razy[nowe_ruchy[i]]>2000 && frozen_ocena[nowe_ruchy[i]]<max_ile-30)
					//	times[nowe_ruchy[i]]=t_inf;
						
					if(rand()%15==0)
					ocena[nowe_ruchy[i]]=0;
					else
					ocena[nowe_ruchy[i]]=frozen_ocena[nowe_ruchy[i]];
					
					//max_ile2=0;
				}
			}else{
				for(int i=0;i<nowe_ruchy_size;i++){
					frozen_ocena[nowe_ruchy[i]]=max(frozen_ocena[nowe_ruchy[i]],ocena[nowe_ruchy[i]]);
					ocena[nowe_ruchy[i]]=frozen_ocena[nowe_ruchy[i]];
					max_ile2=max_ile;
				}
			}
			FR=(FR+1)%2;
		}
		clear_ile(iq);
		save_moves_size=ile=iq;
		available_moves_size=0;
		for(int i=0;i<start_size;i++)
			available_moves[i]=start[i];
		available_moves_size=start_size;
		int qwer =iq+rand()%(max_ile-iq+1);
		while(!available_moves_size==0){
			k=g.int_rand(available_moves_size);
			if(qwer<ile || qwer>ile+7){
				go=0;
				hm=hash_move(available_moves[k]);
				while(ocena[hm]<max_ile2 && qtime<times[hm]){
					k=rand()%available_moves_size;
					hm=hash_move(available_moves[k]);
					go++;
					if(go>7)break;
				}
			}
			if(check_move(available_moves[k])){
				move_exe = available_moves[k];
				add_connection(move_exe);
			   	add_point(move_exe.pnt);
			   	points_clear_size++;
			   	points_clear[points_clear_size]=move_exe.pnt;
			   	save_moves[save_moves_size]=move_exe;
				save_moves_size++;
			   	ile++;
			}
			else{
				available_moves[k]=available_moves[available_moves_size-1];
				available_moves_size--;
			}
		}
		for(int i=iq;i<ile;i++){
			hm=hash_move(save_moves[i]);
			ile_razy[hm]++;
			if(frozen_ocena[hm]==0 && ocena[hm]==0 ){
				nowy++;
				nowe_ruchy[nowe_ruchy_size++]=hm;
				cout<<"nowy: "<<nowy<<"\n";
			}
			ocena[hm]=max(ocena[hm],ile);
			times[hm]=qtime+qt+rand()%qt;
		}
		if(max_ile2<ile){
			max_ile2=ile;
		}
		if(max_ile<ile){
			max_ile=ile;
			max_ile2=max_ile;
			save(ile);
			cout<<"score: "<<max_ile<<"\n";
		}
	//	iq=iq2+rand()%(ile-iq2+1);
	}
}


int random_price_game(){
	move move_exe;
	int ile=0;
	int max_ile=0;
	int k;
	int ocena[100000];
	move start[1000];
	int start_size=0;
	set_cross();
	for(int i=0;i<available_moves_size;i++)
		start[i]=available_moves[i];
	start_size=available_moves_size;
	int hm;
	int go=0;
	int nowy=0;
	while(1){
		clear_all();
		save_moves_size=ile=0;
		available_moves_size=0;
		for(int i=0;i<start_size;i++)
			available_moves[i]=start[i];
		available_moves_size=start_size;
		while(!available_moves_size==0){
			k=rand()%available_moves_size;
			go=0;
			hm=hash_move(available_moves[k]);
			while(ocena[hm]!=0 && ocena[hm]<max_ile-3){
				k=rand()%available_moves_size;
				hm=hash_move(available_moves[k]);
				go++;
				if(go>2)break;
			}
			if(check_move(available_moves[k])){
				move_exe = available_moves[k];
				add_connection(move_exe);
			   	add_point(move_exe.pnt);
			   	points_clear_size++;
			   	points_clear[points_clear_size]=move_exe.pnt;
			   	save_moves[save_moves_size]=move_exe;
				save_moves_size++;
			   	ile++;
			}
			else{
				available_moves[k]=available_moves[available_moves_size-1];
				available_moves_size--;
			}
		}
		//ocena
			for(int i=0;i<ile;i++){
				hm=hash_move(save_moves[i]);
				if(ocena[hm]==0){
					nowy++;
					cout<<"nowy: "<<nowy<<"\n";
				}
				ocena[hm]=max(ocena[hm],ile);
			}

		if(max_ile<ile){
			max_ile=ile;
			save(ile);
			cout<<"score: "<<max_ile<<"\n";
		}
	}
}


int random_game(){
	move move_exe;
	int ile=0;
	int max_ile=0;
	int k;
	while(1){
		clear_all();
		save_moves_size=ile=0;
		set_cross();
		while(!available_moves_size==0){
			k=rand()%available_moves_size;
			if(check_move(available_moves[k])){
				move_exe = available_moves[k];
				add_connection(move_exe);
			   	add_point(move_exe.pnt);
			   	points_clear_size++;
			   	points_clear[points_clear_size]=move_exe.pnt;
			   	save_moves[save_moves_size]=move_exe;
				save_moves_size++;
			   	ile++;
			}
			else{
				available_moves[k]=available_moves[available_moves_size-1];
				available_moves_size--;
			}
		}
		if(max_ile<ile){
			max_ile=ile;
			save(ile);
			cout<<"score: "<<max_ile<<"\n";
		}
	}
}
void read_word_rekord(int ile){
	move m;
	int ilee=0;
	for(int i=0;i<ile;i++){
		int dx=(rekord[i*6+4]-rekord[i*6+2])/4;
		int dy=(rekord[i*6+3]-rekord[i*6+5])/4;
		if(dx==0 && dy==1)
			swap(rekord[i*6+3],rekord[i*6+5]);
		if(dx==1 && dy==1){
			swap(rekord[i*6+3],rekord[i*6+5]);	
			swap(rekord[i*6+2],rekord[i*6+4]);
		}
		if(dx==-1 && dy==1){
			swap(rekord[i*6+3],rekord[i*6+5]);	
			swap(rekord[i*6+2],rekord[i*6+4]);
		}
		m.pnt.x=rekord[i*6]+20;
		m.pnt.y=rekord[i*6+1]+19;
		m.bgn.x=rekord[i*6+2]+20;
		m.bgn.y=rekord[i*6+3]+19;
		if(rekord[i*6+2]==rekord[i*6+4])
			m.dir=1;
		else if(rekord[i*6+3]==rekord[i*6+5])
			m.dir=3;
		else if(rekord[i*6+2]>rekord[i*6+4])
			m.dir=0;
		else
			m.dir=2;
		//znajdz i wstaw:)
		for(int j=0;j<available_moves_size;j++){
			if(m==available_moves[j]){
				add_connection(m);
			   	add_point(m.pnt);
			   	points_clear_size++;
			   	points_clear[points_clear_size]=m.pnt;
			   	save_moves[save_moves_size]=m;
				save_moves_size++;
			   	ilee++;
			   	break;
			}
		}
	}
	cout<<ilee<<"\n";
}
int main(){
	srand ( unsigned ( time (NULL) ) );
	mcts();
	//set_cross();
	//read_word_rekord(0);
	//remove();
	//random_layer_price_game(0);
	//random_layer_game();
	//random_price_game();
//	random_price_time_game(0);
	//random_game();
	//MCTS();
	//MCTS_P();
	return 0;
}

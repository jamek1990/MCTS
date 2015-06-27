#include "stdafx.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string>


#define max(X,Y) (((Y)<(X))?(X):(Y))
#define swap(a,b,type){type t = a;a=b;b=t;}

using namespace std;

const int SIZE = 40;

int rekord[]={-4, 3, -4, 3, -4, -1, 0, -1, -4, -1, 0, -1, -2, -2, -4, 0, 0, -4, 3, -4, -1, -4, 3, -4, 2, 6, 2, 6, 2, 2, -2, 5, -2, 5, 2, 5, -1, 6, -1, 6, -1, 2, 0, 2, -4, 2, 0, 2, -2, 3, 0, 5, -4, 1, 1, -1, 0, -1, 4, -1, 0, 4, 2, 6, -2, 2, 1, 4, -1, 6, 3, 2, 1, 2, 0, 2, 4, 2, -2, 4, -2, 4, 2, 4, -2, 1, -2, 5, -2, 1, -1, 0, -4, 3, 0, -1, -1, 1, -1, 2, -1, -2, 0, 0, -2, 2, 2, -2, 1, 1, 2, 2, -2, -2, 2, 0, -2, 4, 2, 0, 2, 1, 2, 2, 2, -2, 0, 3, -2, 5, 2, 1, -3, 3, -4, 3, 0, 3, 0, 1, 0, 3, 0, -1, 3, 6, 3, 6, -1, 2, 0, 6, 0, 6, -4, 2, -3, 1, -4, 1, 0, 1, 1, 6, -1, 6, 3, 6, 0, 7, 0, 7, 0, 3, 3, 3, 0, 6, 4, 2, 1, 3, 1, 6, 1, 2, -3, 4, 0, 7, -4, 3, 4, 3, 0, 3, 4, 3, 3, 1, -1, 5, 3, 1, -3, 0, -3, 4, -3, 0, 1, 0, -3, 4, 1, 0, 3, 4, 0, 7, 4, 3, 4, 1, 0, 1, 4, 1, 0, -3, -4, 1, 0, -3, -5, -2, -1, 2, -5, -2, 1, -2, 1, 2, 1, -2, 5, 4, 5, 4, 1, 0, 3, 5, 3, 6, 3, 2, 4, 5, 4, 5, 0, 1, 4, -5, 0, -1, 4, -5, 3, 0, 3, 0, -1, -4, 4, 6, 4, 6, 0, 2, 4, 0, 0, 0, 4, 0, 3, -2, 3, 2, 3, -2, 4, 4, 4, 6, 4, 2, 4, -2, 4, 2, 4, -2, 0, -2, -1, -2, 3, -2, 0, -5, 4, -1, 0, -5, 6, 4, 2, 4, 6, 4, -2, 0, -4, 2, 0, -2, -2, -4, 2, 0, -2, -4, 0, -6, 0, -2, 0, -6, 5, 3, 6, 4, 2, 0, -5, 0, -5, 0, -1, 0, -2, -3, -2, 1, -2, -3, 5, 5, 5, 5, 5, 1, 6, 2, 2, 6, 6, 2, -3, -2, -5, 0, -1, -4, -3, -4, 1, 0, -3, -4, 6, 5, 2, 5, 6, 5, 6, 6, 6, 6, 2, 2, 7, 3, 7, 3, 3, -1, -4, -2, -5, -2, -1, -2, -3, -3, -3, 0, -3, -4, 6, 3, 6, 6, 6, 2, 8, 2, 4, 6, 8, 2, -5, -3, -1, 1, -5, -3, 8, 3, 4, 3, 8, 3, 7, 4, 7, 4, 3, 0, 7, 2, 4, 2, 8, 2, -4, -3, -5, -3, -1, -3, 8, 1, 4, 5, 8, 1, 6, 1, 8, 3, 4, -1, -5, -4, -1, 0, -5, -4, 7, 1, 4, 1, 8, 1, -4, -4, -5, -4, -1, -4, 7, 0, 7, 4, 7, 0, 6, 0, 8, 2, 4, -2, -4, -5, -4, -1, -4, -5, 8, -1, 4, 3, 8, -1, 8, 0, 4, 0, 8, 0, 8, -2, 8, 2, 8, -2, 7, -1, 4, 2, 8, -2, 6, -1, 4, -1, 8, -1, 6, -2, 6, 2, 6, -2, 7, -2, 3, 2, 7, -2, 7, -3, 3, 1, 7, -3, 5, -2, 3, -2, 7, -2, 7, -4, 7, 0, 7, -4, 5, -3, 5, 1, 5, -3, 6, -3, 2, 1, 6, -3, 4, -3, 8, 1, 4, -3, 6, -4, 2, 0, 6, -4, 4, -4, 8, 0, 4, -4, 3, -3, 3, -3, 7, -3, 5, -4, 3, -4, 7, -4, 1, -3, -1, -3, 3, -3, 1, -5, 4, -2, 0, -6, 6, -5, 2, -1, 6, -5, -1, -5, 3, -1, -1, -5, 1, -6, 1, -2, 1, -6, 6, -6, 6, -2, 6, -6, -1, -6, -1, -2, -1, -6, -5, -1, -5, -1, -1, -5, 5, -5, 2, -2, 6, -6, -2, -5, -5, -2, -1, -6, -6, -2, -2, 2, -6, -2, 4, -6, 8, -2, 4, -6, 3, -5, 0, -2, 4, -6, 2, -5, -1, -5, 3, -5, 7, -5, 3, -5, 7, -5, 3, -6, 3, -2, 3, -6, 2, -6, 2, -2, 2, -6, 0, -7, 4, -3, 0, -7, 4, -7, 0, -3, 4, -7, 2, -7, 6, -3, 2, -7, -2, -6, -2, -6, 2, -6, 5, -6, 2, -6, 6, -6, 4, -8, 4, -4, 4, -8, 3, -8, -1, -4, 3, -8, -2, -7, -2, -3, -2, -7, -3, -5, -6, -2, -2, -6, 5, -7, 5, -3, 5, -7, 3, -7, 0, -4, 4, -8, -5, -5, -5, -5, -1, -5, 3, -9, 7, -5, 3, -9, 1, -7, 1, -7, 5, -7, -5, -6, -5, -2, -5, -6, -6, -6, -2, -2, -6, -6, 3, -10, 3, -6, 3, -10, 2, -8, -1, -5, 3, -9, 0, -8, 4, -4, 0, -8, 1, -8, 0, -8, 4, -8, 2, -9, -1, -6, 3, -10, 2, -10, 2, -6, 2, -10, 1, -10, 5, -6, 1, -10, 1, -9, 1, -6, 1, -10, -1, -7, -2, -6, 2, -10, 0, -10, 4, -6, 0, -10, -3, -7, -3, -7, 1, -7, -1, -10, -1, -10, 3, -10, 0, -9, 0, -6, 0, -10, -1, -9, -1, -9, 3, -9, -2, -11, 2, -7, -2, -11, -1, -8, -1, -6, -1, -10, -3, -6, -5, -4, -1, -8, -4, -6, -6, -6, -2, -6, -3, -8, -3, -4, -3, -8, -2, -8, -5, -5, -1, -9, -4, -9, 0, -5, -4, -9, -4, -8, -4, -8, 0, -8, -4, -7, -4, -5, -4, -9, -5, -9, -1, -5, -5, -9, -2, -9, -5, -6, -1, -10, -5, -8, -1, -4, -5, -8, -3, -9, -5, -9, -1, -9, -2, -10, -2, -7, -2, -11, -4, -10, 0, -6, -4, -10, -5, -7, -6, -6, -2, -10, -5, -10, -5, -6, -5, -10, -6, -8, -2, -4, -6, -8, -3, -10, -5, -10, -1, -10, -6, -7, -6, -7, -2, -11, -4, -11, 0, -7, -4, -11, -7, -7, -7, -7, -3, -7, -3, -11, -7, -7, -3, -11, -3, -12, -3, -8, -3, -12, -4, -12, 0, -8, -4, -12, -4, -13, -4, -9, -4, -13, -7, -8, -3, -4, -7, -8, -6, -9, -7, -8, -3, -12, -6, -5, -6, -5, -6, -9, -8, -8, -8, -8, -4, -8};

struct point{
	int x;
	int y;
};

struct move2{
	point bgn;
	short int dir; //0-SW 1-S 2-SE 3-E
	point pnt;


};

bool operator==(const move2& m1, const move2& m2){
    if(m1.bgn.x!=m2.bgn.x)return false;
    if(m1.bgn.y!=m2.bgn.y)return false;
    if(m1.pnt.x!=m2.pnt.x)return false;
    if(m1.pnt.y!=m2.pnt.y)return false;
    if(m1.dir!=m2.dir)return false;
    return true;
}


class Position{
	private:
	
	

	inline int hash_point(point p){
		return SIZE*p.y+p.x;
	}

	
	
	public: inline int hash_move2(move2 m){
		return hash_point(m.bgn)*4+m.dir;
	}
	
	public: move2 available_move2s[100000];
	public: int available_move2s_size;

	bool points[SIZE][SIZE];
	point points_clear[100000];
	int points_clear_size;
	

	bool connections[SIZE*SIZE][SIZE*SIZE];
	point connections_clear[100000];
	int connections_clear_size;

	move2 save_move2s[100000];
	int save_move2s_size;

	int dir_x[4];
	int dir_y[4];
	
	move2 pop[10000];
	int pop_size;
	
	point p[36];
	

	private: void cross(){
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
	
	private: void set_cross(){
		cross();
		point temp;
		for(int i=0;i<36;i++){
			temp.x = p[i].x+16;
			temp.y = p[i].y+18;
			add_point(temp);
		}
	}

	public: Position(){
		available_move2s_size = 0;
		points_clear_size=0;
		connections_clear_size = 0;
		save_move2s_size=0;
		pop_size =0;	
		dir_x[0]=-1;dir_x[1]=0;dir_x[2]=1;dir_x[3]=1;
		dir_y[0]= 1;dir_y[1]=1;dir_y[2]=1;dir_y[3]=0;

		set_cross();
		remove2();
	};
	
	public: int wynik(){
		return save_move2s_size;
	}
	
	public: void cofnij(int ile){
		while(connections_clear_size!=4*ile){
			connections[connections_clear[connections_clear_size].x][connections_clear[connections_clear_size].y]=false;
			connections[connections_clear[connections_clear_size].y][connections_clear[connections_clear_size].x]=false;
			connections_clear_size--;
		}
		while(points_clear_size!=ile){
			points[points_clear[points_clear_size].x][points_clear[points_clear_size].y]=false;
			points_clear_size--;
		}
		save_move2s_size = ile;
	}
	
	public: inline bool legal(move2 m){
		if(points[m.pnt.x][m.pnt.y])
			return false;
		if(connections[SIZE*m.bgn.y+m.bgn.x][SIZE*(m.bgn.y+dir_y[m.dir])+m.bgn.x+dir_x[m.dir]])
			return false;
		if(connections[SIZE*(m.bgn.y+3*dir_y[m.dir])+m.bgn.x+3*dir_x[m.dir]][SIZE*(m.bgn.y+4*dir_y[m.dir])+m.bgn.x+4*dir_x[m.dir]])
			return false;
		return true;
	}
	
	public: inline  bool not_end(){
		if(available_move2s_size>0)
			return true;
		return false;
	}
	
	public: inline void play(move2 m){
		add_connection(m);
		add_point(m.pnt);
		points_clear_size++;
		points_clear[points_clear_size]=m.pnt;
		save_move2s[save_move2s_size]=m;
		save_move2s_size++;
	}
	
	/*#######################################################################
		Funckja: add_connection
		Argumenty: move2 m
		Zwraca: void
		Cel: dodaje polaczenie, uaktualnie tablice connections[][] oraz wektor
		do czyszczenia connections_clear
	#######################################################################*/
	private: point con;
	private: void add_connection(move2 m){
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
		Funckja: ADD_POINT
		Argumenty: point pt
		Zwraca: void
		Cel: aktualizuje tablice table po dodaniu nowego punktu, wywoluje funkcej
		ADD_NEW_move2.
    #######################################################################*/
	private: void add_point(point pnt){
		points[pnt.x][pnt.y] = true;
		add_new_move2(pnt);
	}
	
	/*#######################################################################
		Funkcja: ADD_NEW_move2
		Argumenty: point pt
		Zwraca: int liczba ruchów dodanych
		Cel: dodaje nowe move2s po dodaniu punktu, aktualizuje wektor move2s i move2s2.
		jest odporna na bezsensowne move2s bez polaczen.
	 #######################################################################*/
  
	private: int add_new_move2(point pt){
		int wynik =0;
		int ill	 =0;
		int pon	 =0;
		int ok	 =0;
		move2 rucht;
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
						available_move2s_size--;
						wynik--;
					}
					available_move2s[available_move2s_size]=rucht;
					available_move2s_size++;
					wynik++;
					break;
				}
				available_move2s[available_move2s_size]=rucht;
				available_move2s_size++;
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
						available_move2s_size--;
						wynik--;
					}
					available_move2s[available_move2s_size]=rucht;
					available_move2s_size++;
					wynik++;
					break;
				}
				available_move2s[available_move2s_size]=rucht;
				available_move2s_size++;
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
						available_move2s_size--;
						wynik--;
					}
					available_move2s[available_move2s_size]=rucht;
					available_move2s_size++;
					wynik++;
					break;
				}
				available_move2s[available_move2s_size]=rucht;
				available_move2s_size++;
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
						available_move2s_size--;
						wynik--;
					}
					available_move2s[available_move2s_size]=rucht;
					available_move2s_size++;
					wynik++;
					break;
				}
				available_move2s[available_move2s_size]=rucht;
				available_move2s_size++;
				ill++;
				wynik++;
			}
		}
		return wynik;
	}
	
	/*#######################################################################
		Funkcja: remove2
		Argumenty: brak
		Zwraca: void
		Cel: usuwa bledne ruchy z wektora avaliable_move2s
	 #######################################################################*/
	public: void remove2(){
		pop_size=0;
		move2 m;
		int ok;
		for(int ii=0;ii<available_move2s_size;ii++){
		  m=available_move2s[ii];
			if(points[m.pnt.x][m.pnt.y])
				continue;
			ok=1;
			for(int i=0;i<4;i++)
				if(connections[SIZE*(m.bgn.y+i*dir_y[m.dir])+m.bgn.x+i*dir_x[m.dir]][SIZE*(m.bgn.y+(i+1)*dir_y[m.dir])+m.bgn.x+(i+1)*dir_x[m.dir]]){
					ok=0;
					break;
				}
			if(ok){
				pop[pop_size]=available_move2s[ii];
				pop_size++;
			}
		}
		for(int i =0;i<pop_size;i++)
			available_move2s[i]=pop[i];
		available_move2s_size=pop_size;
	}
	
	/*#######################################################################
		Funkcja: EXTEND
		Argumenty: move2 m
		Zwraca: bool czy ruch jest polaczony
	 #######################################################################*/

	private: inline bool extend(move2 m){
		if(connections[SIZE*m.bgn.y+m.bgn.x][SIZE*(m.bgn.y-dir_y[m.dir])+m.bgn.x-dir_x[m.dir]])
			return true;
		if(connections[SIZE*(m.bgn.y+4*dir_y[m.dir])+m.bgn.x+4*dir_x[m.dir]][SIZE*(m.bgn.y+5*dir_y[m.dir])+m.bgn.x+5*dir_x[m.dir]])
			return true;
		return false;
	}
	
	char name[10];
	public: void save(int score){
		move2 m;
		printf("ab");
		ostringstream os;
		os << score;
		string str = os.str();
		str = str+".txt";
		
		for(int i=0;i<(int)str.size();i++)
			name[i]=str[i];
			
		std::ofstream o(name);
		
		for(int i=0;i<score;i++){
			m=save_move2s[i];
			o<<m.pnt.x-20<<" "<<m.pnt.y-19<<" "<<m.bgn.x-20<<" "<<m.bgn.y-19<<" "<<m.bgn.x+4*dir_x[m.dir]-20<<" "<<m.bgn.y+4*dir_y[m.dir]-19<<"\n";
		}
	}
	public: void show_points(){
		for(int i=0;i<SIZE;i++){
		  for(int j=0;j<SIZE;j++){
				if(points[i][j])
				   printf("x");
				else
				   printf(" ");
			}
			printf("\n");
		}
		printf("\n");
	}
	public: void read_word_rekord(int ile){
        move2 m;
        int ilee=0;
        for(int i=0;i<ile;i++){
            int dx=(rekord[i*6+4]-rekord[i*6+2])/4;
            int dy=(rekord[i*6+3]-rekord[i*6+5])/4;
            if(dx==0 && dy==1)
                swap(rekord[i*6+3],rekord[i*6+5],int);
            if(dx==1 && dy==1){
                swap(rekord[i*6+3],rekord[i*6+5],int);	
                swap(rekord[i*6+2],rekord[i*6+4],int);
            }
            if(dx==-1 && dy==1){
                swap(rekord[i*6+3],rekord[i*6+5],int);	
                swap(rekord[i*6+2],rekord[i*6+4],int);
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
            for(int j=0;j<available_move2s_size;j++){
                if(m==available_move2s[j]){
                    play(m);
                    ilee++;
                    break;
                }
            }
        }
        printf("%d\n",ilee);
    }
};
int maks =0;
int ocena[6400];

int odw[6400];
int b_ocena[6400];
int hm;
bool layer[100000];
int layer_size = 0;
move2 layer_m[10000];
 int layer_m_size = 0;
int layer_t[100000];
 int layer_t_size = 0;

int play_random(Position & p){
	//p.remove2();
	layer_t_size=0;
	while(p.available_move2s_size!=0){
		for(int t=0;t<p.available_move2s_size;t++){
			hm=p.hash_move2(p.available_move2s[t]);
			
			if(ocena[hm]>=maks || ocena[hm]==0){
				if(rand()%100<90)
					layer[t]=true;
				else
					layer[t]=false;
            }else{
                /*++odw[hm];
                if(odw[hm]>100000){
                    odw[hm]=0;
                    ocena[hm]=0;
                }*/
                if(rand()%1000<990)
                    layer[t]=false;
                else
                    layer[t]=true;
            }
			if(layer[t]){
				if(p.legal(p.available_move2s[t]))
					p.play(p.available_move2s[t]);
			}else{
				layer_t[layer_t_size]=t;
				layer_t_size++;
			}		
		}
		p.available_move2s_size=0;
		for(int t=layer_t_size-1;t>=0;t--)
			if(p.legal(p.available_move2s[layer_t[t]]))
				p.available_move2s[p.available_move2s_size++]=p.available_move2s[layer_t[t]];
		layer_t_size=0;
	}
	for(int i =0;i<p.wynik();i++){
		hm=p.hash_move2(p.save_move2s[i]);
		ocena[hm]=max(ocena[hm],p.wynik());
	}
	return p.wynik();
}

int play_random2(Position & p){
	//p.remove2();
	int w;
	while(p.not_end()){
		w = rand()%p.available_move2s_size;
		if(p.legal(p.available_move2s[w]))
			p.play(p.available_move2s[w]);
		p.available_move2s[w]=p.available_move2s[--p.available_move2s_size];
	}
	return p.wynik();
}



/*
int nmcs_iter(Position & position, int level, int ile){
	//int g;cin>>g;
	STOS[0].LEVEL = level;
	
	for(int i=0;i<=level;i++)
		 AVAILABLE_move2_SIZE[i] =BEST_SEQ_SIZE[i] =0;
		
	STOS[0].NODE = ile;
	
	for(int i=0;i<B;i++)
		STOS[0].CHILD[i] = 0;
	
	for(int i = 0; i < position.available_move2s_size; i++)
		AVAILABLE_move2[0][i] = position.available_move2s[i];	
	AVAILABLE_move2_SIZE[0] = position.available_move2s_size;
	
	STOS_SIZE = 1;
	
	//INFO info;
	
	while(1){
		
		if(STOS[STOS_SIZE-1].LEVEL == 0){
			
			play_random2(position);
			
			if(position.wynik() > BEST_SEQ_SIZE[1]){
				
				if (maks <position.wynik()){
					maks = position.wynik();
					cout<<"W: "<<maks<<"\n";
					
				}
				BEST_SEQ_SIZE[1] = position.wynik();
				
				for(int i = 0; i < position.wynik(); i++)
					BEST_SEQ[1][i] = position.save_move2s[i];
					
			}
			
			STOS_SIZE--;
			
			position.cofnij(STOS[STOS_SIZE-1].NODE);
			
			// jakie mamy mozliwe ruchy ?
			for(int i = 0; i < AVAILABLE_move2_SIZE[STOS_SIZE-1];i++)
				position.available_move2s[i]=AVAILABLE_move2[0][i];
			position.available_move2s_size =  AVAILABLE_move2_SIZE[STOS_SIZE-1];	
			
			
		}else{
			
			// jesli jeszcze zostalo jakies dziecko na poziomie
			if(STOS[STOS_SIZE-1].CHILD[b]< AVAILABLE_move2_SIZE[STOS_SIZE-1]){
				
				// musimy nalozyc tu wektor z ruchami oczywiscie sprawdzamy poprawnosc - eliminujemy podejscie funkcji redukcji ruchow
				if(position.legal(AVAILABLE_move2[0][STOS[STOS_SIZE-1].CHILD])){
					
					
					position.play(AVAILABLE_move2[0][STOS[STOS_SIZE-1].CHILD]);
					if(STOS[STOS_SIZE-1].LEVEL <2)
                        
                        STOS[STOS_SIZE-1].CHILD+=(1+rand()%2);
					else
                        STOS[STOS_SIZE-1].CHILD++;
					STOS[STOS_SIZE].LEVEL = STOS[STOS_SIZE-1].LEVEL - 1;
					BEST_SEQ_SIZE[STOS[STOS_SIZE].LEVEL] = 0;
					//jako ze dodajemy na koniec nowe ruchy oraz nie usuwamy blednych ruchow to dziecko w nowym lewelu jest takie jak w poprzednim
					STOS[STOS_SIZE].CHILD = STOS[STOS_SIZE-1].CHILD;
					STOS[STOS_SIZE].NODE = STOS[STOS_SIZE-1].NODE + 1;
					
					for(int i = AVAILABLE_move2_SIZE[STOS_SIZE-1]; i<position.available_move2s_size;i++)
						AVAILABLE_move2[0][i]=position.available_move2s[i];
					AVAILABLE_move2_SIZE[STOS_SIZE]=position.available_move2s_size;
					
					STOS_SIZE++;
						
					
				}else{
					if(STOS[STOS_SIZE-1].LEVEL <2)
                        STOS[STOS_SIZE-1].CHILD+=(1+rand()%2);
					else
                        STOS[STOS_SIZE-1].CHILD++;
					
				}
				
			}else{
				
				// w przypadku kiedy przeszlismy wszystkie dzieci i nie jestesmy na samym dole
				
				if(BEST_SEQ_SIZE[STOS[STOS_SIZE-1].LEVEL]>STOS[STOS_SIZE-1].NODE){
					
					if(position.legal(BEST_SEQ[STOS[STOS_SIZE-1].LEVEL][STOS[STOS_SIZE-1].NODE])){
					
						position.play(BEST_SEQ[STOS[STOS_SIZE-1].LEVEL][STOS[STOS_SIZE-1].NODE]);
						
						STOS[STOS_SIZE-1].NODE++;
						
						//STOS[STOS_SIZE-1].CHILD=0;
					
						for(int i = 0; i<position.available_move2s_size;i++)
							AVAILABLE_move2[0][i]=position.available_move2s[i];
						
						AVAILABLE_move2_SIZE[STOS_SIZE-1] = position.available_move2s_size;
						
						//BEST_SEQ_SIZE[STOS[STOS_SIZE-1].LEVEL] = 0;
				
					}else{cout<<"dupa\n";}
					

					
				}else{
					
					if(STOS[STOS_SIZE-1].LEVEL==level){
						
						//koniec gry przeszlismy cale drzewo
						return STOS[STOS_SIZE-1].NODE;
	
					}else if(BEST_SEQ_SIZE[STOS[STOS_SIZE-1].LEVEL]>BEST_SEQ_SIZE[STOS[STOS_SIZE-2].LEVEL]){
						
						BEST_SEQ_SIZE[STOS[STOS_SIZE-2].LEVEL] = BEST_SEQ_SIZE[STOS[STOS_SIZE-1].LEVEL];
						for(int i = 0; i < BEST_SEQ_SIZE[STOS[STOS_SIZE-1].LEVEL];i++)
							BEST_SEQ[STOS[STOS_SIZE-2].LEVEL][i] = BEST_SEQ[STOS[STOS_SIZE-1].LEVEL][i];
							
					}
					//BEST_SEQ_SIZE[STOS[STOS_SIZE-1].LEVEL-1] = 0;
					STOS_SIZE--;				
					
					position.cofnij(STOS[STOS_SIZE-1].NODE);
					
					//odswiezamy ruchy
					for(int i = 0; i < AVAILABLE_move2_SIZE[STOS_SIZE-1];i++)
						position.available_move2s[i]=AVAILABLE_move2[0][i];
						
					position.available_move2s_size =  AVAILABLE_move2_SIZE[STOS_SIZE-1];	

					//position.remove2();
					
				}
			}
		}
	}
	return 0;
}
*/


	/*const int N = 10;
const int B = 10;

struct INFO{
	int LEVEL;
	int CHILD[B];
	int NODE;
	int BEAM;
};

INFO STOS[N];

int STOS_SIZE=0;
int BEST_SEQ_SIZE[10];

move2 BEST_SEQ[10][250];

move2 AVAILABLE_move2[10][100000];
int AVAILABLE_move2_SIZE[10];
*/

const int B = 2000;
const int L = 5;

int maxBeamSize[L];

int nextBeamSize[L];
int beamSize[L];


move2 bestSeq[L][B][200];
int bestSeqSize[L][B];
int bestSeqNumer[L];

move2 nextBestSeq[L][50000][200];
int nextBestSeqSize[L][50000];
int nextBestSeqNumer[L];

move2 availableMove[L][B][1000];
int availableMoveSize[L][B];


move2 nextAvailableMove[L][B][1000];
int nextAvailableMoveSize[L][B];

move2 startAvailableMove[L][100];
int startAvailableMoveSize[L];

int node[L];


Position position;
void beamMonteCarlo(int level, bool ok , int ile){
	bestSeqNumer[level]=1;
	while(1){
		nextBestSeqNumer[level] = 0;
		for(int b=0;b<bestSeqNumer[level];b++){
			position.cofnij(ile);
			for(int i = 0; i < startAvailableMoveSize[level]; i++)
				position.available_move2s[i] = startAvailableMove[level][i];
			position.available_move2s_size=startAvailableMoveSize[level];
			for(int i = ile; i < node[level]; i++)
				position.play(bestSeq[level][b][i]);
			position.remove2();
			
			for(int i = 0; i < position.available_move2s_size; i++)
				availableMove[level][b][i] = position.available_move2s[i];
			availableMoveSize[level][b] = position.available_move2s_size;

			if(availableMoveSize[level][b]>0  && bestSeqSize[level][b] > 0){
				for(int i = ile; i<  bestSeqSize[level][b]; i++)
					nextBestSeq[level][nextBestSeqNumer[level]][i] = bestSeq[level][b][i];
				nextBestSeqSize[level][nextBestSeqNumer[level]] = bestSeqSize[level][b];
				nextBestSeqNumer[level]++;
			}
					

			for(int i = 0; i < availableMoveSize[level][b]; ++i){
				if(!position.legal(availableMove[level][b][i]))cout<<"no legal\n";
				position.play(availableMove[level][b][i]);
				//position.remove2();
				if(level==0){
					play_random(position);
					if(position.wynik()>maks){
						maks = position.wynik();
						position.save(position.wynik());
						
						cout<<"maks: "<<maks<<"\n";
					}

					for(int j = ile; j< position.save_move2s_size; j++)
						nextBestSeq[level][nextBestSeqNumer[level]][j] = position.save_move2s[j];
					nextBestSeqSize[level][nextBestSeqNumer[level]] = position.save_move2s_size;
					nextBestSeqNumer[level]++;

					position.cofnij(node[level]);
					
					position.available_move2s_size = availableMoveSize[level][b];
					for(int j = 0; j < position.available_move2s_size; j++)
						position.available_move2s[j] = availableMove[level][b][j];

				}else{
				
						for(int j = ile; j < node[level]; j++)
							bestSeq[level-1][0][j]=bestSeq[level][b][j];
						bestSeq[level-1][0][node[level]] = availableMove[level][b][i];	
						bestSeqSize[level-1][0] = 0;//bestSeqSize[level][b];
					
					//bestSeqSize[level-1][0] = 0;//bestSeqSize[level][b];
					//if(ile>0)cout<<"Error\n";
					node[level-1]=node[level]+1;
					if( position.save_move2s_size != node[level-1]) cout<<"Error\n";
					for(int j=0;j< position.available_move2s_size; j++)
						startAvailableMove[level-1][j] = position.available_move2s[j];
					startAvailableMoveSize[level-1]	 = position.available_move2s_size;
					
					beamMonteCarlo( level-1,true,node[level-1]);//node[level-1]);
					//cout<<"P: "<<bestSeqSize[level-1][0]<<"\n";
					for(int j = ile; j< bestSeqSize[level-1][0]; j++)
						nextBestSeq[level][nextBestSeqNumer[level]][j] = bestSeq[level-1][0][j];
					nextBestSeqSize[level][nextBestSeqNumer[level]] = bestSeqSize[level-1][0];
					nextBestSeqNumer[level]++;


					position.cofnij(ile);
					for(int j = 0; j < startAvailableMoveSize[level]; j++)
						position.available_move2s[j] = startAvailableMove[level][j];
					position.available_move2s_size = startAvailableMoveSize[level];
					for(int j = ile; j < node[level]; j++)
						position.play(bestSeq[level][b][j]);
					position.remove2();
					/*for(int j = 0; j < position.available_move2s_size; j++)
						availableMove[level][b][j] = position.available_move2s[j];
					availableMoveSize[level][b] = position.available_move2s_size;*/
					
				}
			}
		}
		if(nextBestSeqNumer[level] == 0)
			break;
	
		bestSeqNumer[level] = 0;
		int maxBeamIle=-1;
		int maxBeamNr=0;
		for(int i = 0; i <min(maxBeamSize[level],nextBestSeqNumer[level]);i++){
			maxBeamIle=-1;
			maxBeamNr=0;
			for(int j =0; j< nextBestSeqNumer[level]; j++)
				if(maxBeamIle<nextBestSeqSize[level][j]){
					maxBeamIle = nextBestSeqSize[level][j];
					maxBeamNr = j;
				}
			if(maxBeamIle>node[level]){
				for(int j = ile; j<maxBeamIle; j++)
					bestSeq[level][bestSeqNumer[level]][j] = nextBestSeq[level][maxBeamNr][j];
				bestSeqSize[level][bestSeqNumer[level]] = maxBeamIle;
				nextBestSeqSize[level][maxBeamNr]=0;
				bestSeqNumer[level]++;
				//cout<<maxBeamIle<<" ";
			}else{
				break;
			}
		}	
		//cout<<"\n";
		//int ff;cin>>ff;
		//if(level>0)
			//printf("%d %d\n",level,nextBestSeqNumer[level]);
		node[level]++;
		if(level>0)
			cout<<"node: "<<node[level]<<"\n";
	}
}

void bMC(int level,int ile){
	node[level]=ile;
	maxBeamSize[0]=50;//sqrt(50000);
	maxBeamSize[1]=5;
	maxBeamSize[2]=1;
	maxBeamSize[3]=2;
	maxBeamSize[4]=1;

	for(int i = 0; i< ile; i++)
		bestSeq[level][0][i]=position.save_move2s[i];
	for(int i = 0; i < position.available_move2s_size; i++)
		startAvailableMove[level][i] = position.available_move2s[i];
	startAvailableMoveSize[level] = position.available_move2s_size;

for(int b = 0; b< B; b++)
for(int i = 0; i<= level; i++)
bestSeqSize[i][b]=0;
for(int b = 0; b< B; b++)
for(int i = 0; i<= level; i++)
nextBestSeqSize[i][b]=0;

	//nextBestSeqNumer[level] = 0;
//cout<<"ILE: "<<ile<<"\n";
	beamMonteCarlo(level,false,ile);
}



int main(){
	srand( time( NULL ) );
	
    
    int R=0;
    position.read_word_rekord(R);
    position.remove2();
	
    move2 start[28];
    int start_size = 0;
    for(int i = 0; i < position.available_move2s_size; i++)
		start[i]= position.available_move2s[i];
    start_size = position.available_move2s_size;
    
	//position.play(position.available_move2s[25]);
	//position.play(position.available_move2s[0]);
//	position.play(position.available_move2s[2]);
	position.show_points();
	cout << position.available_move2s_size;
    
	
  //  int ile = 0;
    //cin>>ile;
    int ile_maks = 0;
    
//    int super_ocena[6400];
    
	 while(1){
	 	//position.show_points();
		//ile = nmcs_iter(position,3,R);
		bMC(1,R);
		//ile = play_random(position)
		cout<<".\n";
	/*	if(ile>ile_maks){
			cout<<"wynik: "<<ile<<"\n";
			ile_maks = ile;
		}*/
		
		position.cofnij(R);
		for(int i = 0; i < start_size; i++)
			position.available_move2s[i]= start[i];
			
		position.available_move2s_size = start_size;
		
		//position.play(position.available_move2s[25]);
		//position.play(position.available_move2s[0]);
		//position.play(position.available_move2s[2]);
		
	}
	
	
	return 0;
}

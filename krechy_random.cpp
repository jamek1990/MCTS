#include<iostream>
#include<vector>
#include<algorithm>
#include <cstdio>
#include <sstream>
#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>

using namespace std;

const int SIZE = 40;

struct point{
	int x;
	int y;
};

inline int hash(point p){
	return SIZE*p.y+p.x;
}

struct move{
	point bgn;
	short int dir; //0-SW 1-S 2-SE 3-E
	point pnt;
};

move available_moves[100];
short int available_moves_size = 0;

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


int random_game(){
	move move_exe;
	int ile=0;
	int max_ile=0;
	while(1){
		clear_all();
		save_moves_size=ile=0;
		set_cross();
		while(!available_moves_size==0){
			move_exe = available_moves[rand()%available_moves_size];
			add_connection(move_exe);
		   	add_point(move_exe.pnt);
		   	points_clear_size++;
		   	points_clear[points_clear_size]=move_exe.pnt;
		   	save_moves[save_moves_size]=move_exe;
			save_moves_size++;
		   	remove();
		   	ile++;
		}
		if(max_ile<ile){
			max_ile=ile;
			save(ile);
			cout<<"score: "<<ile<<"\n";
		}
	}
}

int main(){
   srand ( unsigned ( time (NULL) ) );
   set_cross();
	random_game();
	return 0;
}

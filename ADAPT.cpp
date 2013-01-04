/*
ADAPT(node,i){} DLA NRPA
DLA KAZDEGO LEWELU ODEJMUJEMY ALPHA/w
w - liczba wybranych ruchow w warstwie
*/
#include<iostream>
#include<math.h>
#include<vector>
#include<string>
#include<set>
#include<map>
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
#define VAR(i,n) __typeof(n) i =n
#define REP(i,n) for(int i=0;i<(n);++i)
#define FOREACH(it,c) for(VAR(it,c.begin());it!=c.end();++it)
#define SIZE(x) (int)x.size()
long double t[30];
int N=10;
long double z=0;
int main(){
  int n=100000;
	while(n--){
		z=0;
		for(int i=0;i<N;i++)
			z+=exp(t[i]);
		for(int i=0;i<N;i++)
			t[i]-=exp(t[i])/z;
		t[0]+=1.0/5;
		t[1]+=1.0/5;
		t[2]+=1.0/5;
		t[3]+=1.0/5;
		t[4]+=1.0/5;
		
	}
	printf("%f ",exp(t[1]));
	for(int i=0;i<N;i++)
		cout<<t[i]<<" ";
		cout<<"\n";
	return 0;
}

#include<iostream>
#include<cstdio>
using namespace std;
struct KnightCircuit2
{
int maxSize(int n,int m)
{
	if(n>m) swap(n,m);
	if(n==1) return 1;
	if(n==2) return (m+1)/2;
	if(n==3&&m==3) return 8; 
	return n*m;
}
};
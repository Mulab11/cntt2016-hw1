#line 7 "MagicalHats.cpp"
#include<bits/stdc++.h>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
#define pb push_back
#define ll long long
#define inf 0x3f3f3f3f
#define fill(a,b) memset(a,b,sizeof(a))
#define cpy(a,b) memcpy(a,b,sizeof(b))
template<typename T> inline bool MIN(T &a,const T &b) {return a>b? a=b,1:0;}
template<typename T> inline bool MAX(T &a,const T &b) {return a<b? a=b,1:0;}

#define mp make_pair
#define fi first
#define se second
#define N 
#define mod 1000000007
typedef vector<int> vi;
typedef pair<int,int> pii;
int nG;

struct node {
	int x,y;
};
vector<node> q;


int f[1600000],n,power[15];
//f represents the maximum number of coins you can get 
//use 3-based

int outbit(int p,int v) {
	return v*power[p];
}
int bit(int s,int p) {
	return s/power[p]%3;
}


int A[13],B[13];
int get_f(int s,int use,int coin) {	
	int &res=f[s];
	if (res!=-1) return res;
	if (!coin) {
		fill(A,0),fill(B,0);
		for (int i=0;i<n;++i) if (bit(s,i)!=2) A[q[i].x]^=1,B[q[i].y]^=1;
		for (int i=0;i<13;++i) if (A[i]||B[i]) return res=inf;
		return res=0;
	}
	if (!use) {
	
		for (int i=0;i<n;++i) if (bit(s,i)==0) {
			if (get_f(s+outbit(i,2),0,coin-1)==0) return res=0;
		}
		return res=inf;
	}

	
	for (int i=0;i<n;++i) if (bit(s,i)==0) {
		
		MAX(res,min(get_f(s+outbit(i,1),use-1,coin),get_f(s+outbit(i,2),use-1,coin-1)+1));
		//get_f(s+outbit(i,1),use-1,coin)        if not place a coin here
		//get_f(s+outbit(i,2),use-1,coin-1)+1    if place a coin here
	}
	return res;
}

class MagicalHats
{
        public:
        int findMaximumReward(vector <string> board, vector <int> coins, int numGuesses)
        {
        	nG=numGuesses;
        	power[0]=1; for (int i=1;i<15;++i) power[i]=power[i-1]*3;
        	
        	int r=board.size(),c=board[0].size();
        	fill(f,-1);
        	q.clear();
        	for (int i=0;i<r;++i) {
        		for (int j=0;j<c;++j) {
        			if (board[i][j]=='H') q.pb((node){i,j});
        		}
        	}
        	n=q.size();
        	
        	int t=get_f(0,numGuesses,coins.size());
        	if (t>100) return -1;
        	int ans=0;
        	
        	sort(coins.begin(),coins.end()); 
        	for (int i=0;i<t;++i) ans+=coins[i];
        	return ans;
        }
        

};

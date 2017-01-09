//============================================================================
// Author       : Sun YaoFeng
//============================================================================

#include<set>
#include<map>
#include<cmath>
#include<queue>
#include<bitset>
#include<string>
#include<cstdio>
#include<cctype>
#include<cassert>
#include<cstdlib>
#include<cstring>
#include<sstream>
#include<iostream>
#include<algorithm>

#define For(i,x,y) for (int i=x;i<y;i++)
#define pb push_back
#define mp make_pair
#define fi first
#define se second

#define dprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;

typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
typedef vector<int> Vi;
typedef vector<string> Vs;

const int N=50+19;

Vi V;
string res;
int A[N],S[N],T[N];
int n,L;

bool check0(int x){
	memcpy(T,S,sizeof(S));
	for (int i=max(1,x-L+1);i<=min(x,n-L+1);i++){
		T[A[i+L-1]-A[i-1]]--;
	}
	For(i,0,V.size()) T[V[i]]--;
	For(i,0,N) if (T[i]<0) return 0;
	return 1;
}
bool check1(int x){	//贪心判断
	for (int i=max(1,x-L+1);i<=min(x,n-L+1);i++){
		bool b=0;
		For(j,0,V.size()){
			if (V[j]==A[i+L-1]-A[i-1]) b=1;
		}
		if (b) return 1;
	}
	return 0;
}

class SurveillanceSystem{
public:
	string getContainerInfo(string s,Vi V,int L){
		::V=V;::L=L;
		n=s.length();
		For(i,1,n+1) A[i]=A[i-1]+(s[i-1]=='X');
		for (int i=1;i+L-1<=n;i++) S[A[i+L-1]-A[i-1]]++;	//预处理
		
		
		For(i,1,n+1){	//枚举每一个东西的答案
			bool b=0,c=0;
			if (check0(i)) b=1;
			if (check1(i)) c=1;
			if (!b) res+="+";else
				if (!c) res+="-";else res+="?";
		}
		return res;
	}
} Te;
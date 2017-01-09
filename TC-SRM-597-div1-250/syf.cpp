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

int cnt[128],x,n,res;

class LittleElephantAndString{
public:
	int getNumber(string A,string B){
		n=A.length();
		x=n-1;
		For(i,0,n){
			cnt[A[i]]++;
			cnt[B[i]]--;
		}
		For(i,'A','Z'+1) if (cnt[i]) return -1;
		for (int i=B.length()-1;~i;i--){	//直接判断输出答案
			while (x>=0&&A[x]!=B[i]) x--;
			if (x>=0) res++;else break;
			x--;
		}
		return n-res;
	}
} T;
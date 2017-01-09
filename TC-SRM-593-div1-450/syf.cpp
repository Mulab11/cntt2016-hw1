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

const int S=500000+19;
const int oo=(1<<30)-1;

int f[2][S*2];
int n,c,res=oo;

void Upd(int &x,int y){
	if (y<x) x=y;
}

class MayTheBestPetWin{
public:
	int calc(Vi A,Vi B){
		n=A.size();
		memset(f,64,sizeof(f));
		f[c][S]=0;
		
		//F[i][j]表示前i个物品，一部分和为j，另一部分的最大值
		
		For(i,0,n){
			memset(f[c^1],64,sizeof(f[c^1]));
			For(j,0,S*2)
				if (f[c][j]<oo){
					Upd(f[c^1][j+B[i]],f[c][j]-A[i]);	//枚举这一物品的选择
					Upd(f[c^1][j-A[i]],f[c][j]+B[i]);
				}
			c^=1;
		}
		For(i,0,S*2){
			res=min(res,max(i-S,f[c][i]));
		}
		return res;
	}
} T;
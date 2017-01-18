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

const int N=15;

int aR[1<<N],aG[1<<N],bR[1<<N],bG[1<<N],bW[1<<N],f[1<<N][N*10];
int n,res;

void Upd(int &x,int y){
	if (y>x) x=y;
}

class KeyDungeonDiv1{
public:
	int maxKeys(Vi dR,Vi dG,Vi rR,Vi rG,Vi rW,Vi key){
		n=dR.size();
		For(t,0,1<<n)
			For(i,0,n)
				if (t>>i&1){
					aR[t]+=dR[i];
					aG[t]+=dG[i];
					bR[t]+=rR[i];
					bG[t]+=rG[i];
					bW[t]+=rW[i];
				}
		memset(f,-1,sizeof(f));
		f[0][key[0]]=key[2];
		For(t,0,1<<n) For(s,0,N*10)
			if (~f[t][s]){
				res=max(res,key[0]+key[1]+key[2]-aR[t]-aG[t]+bR[t]+bG[t]+bW[t]);
				For(i,0,n)
					if (!(t>>i&1)){
						int tmp=0;
						tmp+=max(dR[i]-s,0);
						tmp+=max(dG[i]-(key[1]-aG[t]+bG[t]+(key[2]+bW[t]-f[t][s]-(s-(key[0]-aR[t]+bR[t])))),0);
						if (tmp>f[t][s]) continue;
						Upd(f[t|1<<i][max(s-dR[i],0)+rR[i]],f[t][s]+rW[i]-tmp);
					}
			}
		return res;
	}
} T;

int main(){
	printf("%d\n",T.maxKeys(
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
	{10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10}, 
	{10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10}, 
	{10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10}, 
	{10, 10, 10}));
}

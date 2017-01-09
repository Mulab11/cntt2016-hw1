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

const int N=2500+19;
const int oo=(1<<30)-1;

struct Seg{
	int l,r;
	bool operator < (const Seg &B) const {return l<B.l;}
} S[N];
string S1000,S100,S10,S1,T1000,T100,T10,T1;
int n,res,rmn,lmx,chk=1;

int work(int x){	//贪心找合法的序列
	int res=0,c=0,R=rmn;
	while (R<lmx){
		int tmp=R;
		if (S[x].l<=R&&S[x].r>R){
			R=S[x].r;
			continue;
		}
		for (;c<n&&S[c].l<=R;c++) tmp=max(tmp,S[c].r);
		if (tmp==R){
			chk=0;
			return 0;
		}
		R=tmp;
		res++;
	}
	return res;
}

class ShoutterDiv1{
public:
	int count(Vs s1000,Vs s100,Vs s10,Vs s1,Vs t1000,Vs t100,Vs t10,Vs t1){
		For(i,0,s1000.size()){
			S1000+=s1000[i];
			S100+=s100[i];
			S10+=s10[i];
			S1+=s1[i];
			T1000+=t1000[i];
			T100+=t100[i];
			T10+=t10[i];
			T1+=t1[i];
		}
		n=S1000.size();
		rmn=oo;
		lmx=-oo;
		For(i,0,n){
			S[i].l=(S1000[i]-'0')*1000+(S100[i]-'0')*100+(S10[i]-'0')*10+(S1[i]-'0');
			S[i].r=(T1000[i]-'0')*1000+(T100[i]-'0')*100+(T10[i]-'0')*10+(T1[i]-'0');
			rmn=min(rmn,S[i].r);
			lmx=max(lmx,S[i].l);
		}
		
		//预处理
		
		sort(S,S+n);
		For(i,0,n){	//对于每一个点求解答案
			res+=work(i);
		}
		return !chk?-1:res;
	}
} T;
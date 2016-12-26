#include <bits/stdc++.h>

#define rep(x,a,b) for (int x=a;x<=(int)b;x++)
#define drp(x,a,b) for (int x=a;x>=(int)b;x--)
#define cross(x,a) for (int x=hd[a];~x;x=nx[x])
#define ll long long
#define inf (1<<29)
#define PII pair<int,int>
#define PDD pair<double,double>
#define mk(a,b) make_pair(a,b)
#define fs first
#define sc second
#define pb push_back
#define VI vector<int>
using namespace std;
const int maxn=30;
string bat,ans;
int n,st[maxn],nom[maxn];
PII mon[maxn][10];
int big[maxn][maxn],sml[maxn][maxn];
void Min(int &a,int b){if (b<a) a=b;}
void Max(int &a,int b){if (b>a) a=b;}

/*
设一个关于标准纪年的偏移量
转差分约束模型
*/

class History{
public:
	string verifyClaims(vector<string>dyn,vector<string>b,vector<string>qry){
		n=dyn.size();
		rep(i,0,b.size()-1) bat+=b[i];
		rep(i,0,n-1){
			int lst=-1,now=0,l=dyn[i].size();
			rep(j,0,l-1){
				int k=j;now=0;
				while (k<l&&isdigit(dyn[i][k])) now=(now<<1)+(now<<3)+dyn[i][k]-'0',k++;
				if (~lst) mon[i][nom[i]++]=mk(lst,now-1);
				lst=now,j=k;
			}
		}
		int l=bat.size();
		memset(big,40,sizeof big),memset(sml,230,sizeof sml);
		rep(i,0,l-1){
			int l1=bat[i]-'A',l2=bat[i+1]-'0',r1=bat[i+3]-'A',r2=bat[i+4]-'0';
			Min(big[l1][r1],mon[r1][r2].sc-mon[l1][l2].fs),Min(big[r1][l1],mon[l1][l2].sc-mon[r1][r2].fs);
			Max(sml[l1][r1],mon[r1][r2].fs-mon[l1][l2].sc),Max(sml[r1][l1],mon[l1][l2].fs-mon[r1][r2].sc);
			i+=5;
		}
		rep(k,0,n-1) rep(i,0,n-1) rep(j,0,n-1) Min(big[i][j],big[i][k]+big[k][j]),Max(sml[i][j],sml[i][k]+sml[k][j]);
		int q=qry.size();
		rep(i,0,q-1){
			int l1=qry[i][0]-'A',l2=qry[i][1]-'0',r1=qry[i][3]-'A',r2=qry[i][4]-'0';
			int L1=mon[l1][l2].fs,R1=mon[l1][l2].sc,L2=mon[r1][r2].fs,R2=mon[r1][r2].sc;
			if (L1+sml[l1][r1]<=R2&&R1+big[l1][r1]>=L2) ans+='Y';else ans+='N';
		}
		return ans;
	}
};

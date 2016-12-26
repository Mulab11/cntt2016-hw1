#include<bits/stdc++.h>

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
#define VS vector<string>

using namespace std;

/*
折半搜索，26^5枚举前一半，hash状态，然后在后一半查询即可
*/

const int maxn=55;
map<string,string>mp1;
map<string,int>mp2;
string tmp1,tmp2;
VS gus;
VI ex[10][10];
int bul[maxn],chs[10],n,l1,l2,alr[maxn];
void dfs1(int nw,int gl){
	rep(i,0,n-1) if (alr[i]>bul[i]) return;
	if (nw==gl){
		tmp1.clear();
		rep(i,0,n-1) tmp1+=alr[i]+'0';
		mp1[tmp1]=tmp2;mp2[tmp1]++;
		return;
	}
	rep(i,0,9){
		rep(j,0,ex[nw][i].size()-1) alr[ex[nw][i][j]]++; 
		tmp2[nw]=i+'0',dfs1(nw+1,gl);
		rep(j,0,ex[nw][i].size()-1) alr[ex[nw][i][j]]--;
	}
}
int num;
string ans;
void dfs2(int nw,int gl){
	rep(i,0,n-1) if (alr[i]>bul[i]) return;
	if (nw==gl){
		tmp1.clear();
		rep(i,0,n-1) tmp1+=bul[i]-alr[i]+'0';
		if (mp2.find(tmp1)!=mp2.end()){
			num+=mp2[tmp1];
			if (num>1) return;
			ans=mp1[tmp1]+tmp2;
		}
		return;
	}
	rep(i,0,9){
		rep(j,0,ex[nw][i].size()-1) alr[ex[nw][i][j]]++; 
		tmp2[nw-l1]=i+'0',dfs2(nw+1,gl);
		if (num>1) return;
		rep(j,0,ex[nw][i].size()-1) alr[ex[nw][i][j]]--;
	}
}
int ndi,ava[10][10];
bool cmp(const int &a,const int &b){return ex[ndi][a]>ex[ndi][b];}
struct EllysBulls{
	string getNumber(VS gus,VI bul){
		n=gus.size(),l2=gus[0].size();
		::gus=gus,l1=l2/2;
		rep(i,0,n-1) ::bul[i]=bul[i];
		rep(i,0,n-1) rep(j,0,l2-1) ex[j][gus[i][j]-'0'].pb(i);
		tmp2=string("0",l1);dfs1(0,l1);
		tmp2=string("0",l2-l1);dfs2(l1,l2);
		if (!num) return "Liar";
		else if (num>1) return "Ambiguity";
		else return ans;
	}
};

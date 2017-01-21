// BEGIN CUT HERE

// END CUT HERE
#line 5 "CheckerFreeness.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
string st;int stamp;
inline int get_char(){
	if (stamp==st.size()) return -1;
	return st[stamp++];
}
inline int read(){
	int ret=0;char ch=get_char();
	while (ch<'0'||ch>'9') ch=get_char();
	while ('0'<=ch&&ch<='9'){
		ret=ret*10-48+ch;
		ch=get_char();
	}
	return ret;
}
void Input(vector<string> &_s,int *a,int &n){
	st="";
	for (int i=0;i<_s.size();++i) st+=_s[i];
	stamp=0;n=0;
	while (stamp<st.size()) a[n++]=read();
}

const int maxn=233;

class CheckerFreeness{
	ll cross(int x0,int y0,int x1,int y1,int x2,int y2){
		return 1LL*(x1-x0)*(y2-y0)-1ll*(x2-x0)*(y1-y0);
	}
	int wx[maxn],wy[maxn],n;
	int bx[maxn],by[maxn],m;
	bitset<maxn> bn[maxn][maxn],bm[maxn][maxn];
	public:
	string isFree(vector <string> whiteX, vector <string> whiteY, vector <string> blackX, vector <string> blackY){
		Input(whiteX,wx,n);
		Input(whiteY,wy,n);
		Input(blackX,bx,m);
		Input(blackY,by,m);
		for (int i=0;i<n;++i)for (int j=i+1;j<n;++j)for (int k=0;k<m;++k)
			if (cross(wx[i],wy[i],wx[j],wy[j],bx[k],by[k])>0) bn[i][j][k]=1;
			else bn[j][i][k]=1;
		for (int i=0;i<m;++i)for (int j=0;j<n;++j)for (int k=i+1;k<m;++k)
			if (cross(bx[i],by[i],wx[j],wy[j],bx[k],by[k])>0) bm[i][j][k]=1;
			else bm[k][j][i]=1;
//		for (int i=0;i<n;++i,puts(""))for (int j=0;j<n;++j,puts(""))for (int k=0;k<m;++k)
//			printf("%d",(int)bn[i][j][k]);
		for (int i=0;i<n;++i)for (int j=i+1;j<n;++j)for(int k=0;k<m;++k)
			if (((bn[i][j][k]?bn[j][i]:bn[i][j])&(bm[k][i]^bm[k][j])).any())
				return "NO";
		return "YES";
	}
};

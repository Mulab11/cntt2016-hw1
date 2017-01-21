// BEGIN CUT HERE

// END CUT HERE
#line 5 "History.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int maxn=55;
inline void Max(int &x,int y){if (y>x)x=y;}
inline void Min(int &x,int y){if (y<x)x=y;}

void decode(string &st,int &id0,int &x,int &id1,int &y){
//	cout<<st<<endl;
	int k=0;
	id0=st[k++]-'A';x=st[k++]-48;
	if (isdigit(st[k])) (x*=10)+=st[k++]-48;
	id1=st[++k]-'A';y=st[++k]-48;
	if (k+1<st.size()) (y*=10)+=st[++k]-48;
//	printf("%d %d %d %d\n",id0,x,id1,y);
}

class History{
	int l[maxn][maxn],r[maxn][maxn];
	int a[maxn][maxn],n;
	public:
	string verifyClaims(vector <string> dynasties, vector <string> battles, vector <string> queries){
		n=dynasties.size();
		for (int i=0;i<n;++i)for (int j=0;j<n;++j)l[i][j]=-(r[i][j]=3e6);
		for (int i=0;i<n;++i){
			l[i][i]=r[i][i]=0;
			int k=a[i][0]=0;
			for (int j=0;j<dynasties[i].size();++j)
				if (dynasties[i][j]!=' ') (a[i][k]*=10)+=dynasties[i][j]-48;
				else a[i][++k]=0;
//			for (int j=0;j<=k;++j) printf("%d ",a[i][j]);puts("");
		}
		int id0,x,id1,y;
		#define l0 (a[id0][x])
		#define r0 (a[id0][x+1])
		#define l1 (a[id1][y])
		#define r1 (a[id1][y+1])
		string st="",limit;
		for (int i=0;i<battles.size();++i) st+=battles[i];
		st+=' ';
		for (int i=0;i<st.size();++i){
			limit="";
			for (;st[i]!=' ';++i) limit+=st[i];
			decode(limit,id0,x,id1,y);
			for (int k=0;k<2;++k,swap(id0,id1),swap(x,y))
				Max(l[id0][id1],l0-r1+1),Min(r[id0][id1],r0-l1-1);
		}
		for (int k=0;k<n;++k)
			for (int i=0;i<n;++i)for (int j=0;j<n;++j)
				Max(l[i][j],l[i][k]+l[k][j]),Min(r[i][j],r[i][k]+r[k][j]);
		string ret;
		for (int i=0;i<queries.size();++i){
			decode(queries[i],id0,x,id1,y);
			ret.push_back((l0-r1+1>r[id0][id1]||r0-l1-1<l[id0][id1])?'N':'Y');
		}
		return ret;
	}
};

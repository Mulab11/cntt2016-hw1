#include<bits/stdc++.h>
#define sqr(x) (x)*(x)
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define vi vector<int>
#define pb push_back
#define ld long double
#define mp make_pair
#define pii pair<int,int>
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

int ans[10][10];
vi row,col;
void add(int ax,int bx,int ay,int by){
	int lx,ly,rx,ry;
	lx=lower_bound(row.begin(),row.end(),ax)-row.begin();
	rx=upper_bound(row.begin(),row.end(),bx)-row.begin();
	ly=lower_bound(col.begin(),col.end(),ay)-col.begin();
	ry=upper_bound(col.begin(),col.end(),by)-col.begin();
//	printf("%d %d %d %d\n",lx,rx,ly,ry);
	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++)
			if((i>=lx&&i<rx)||(j>=ly&&j<ry)) ans[i][j]++;
}

class HyperKnight{
public:
	long long countCells(int a, int b, int numRows, int numColumns, int k){
		k=8-k;
		int n=numRows,m=numColumns;
		memset(ans,0,sizeof(ans));
		row.clear();row.pb(a+1);row.pb(b+1);row.pb(n-a+1);row.pb(n-b+1);row.pb(1);row.pb(n+1);
		sort(row.begin(),row.end());
		col.clear();col.pb(a+1);col.pb(b+1);col.pb(m-a+1);col.pb(m-b+1);col.pb(1);col.pb(m+1);
		sort(col.begin(),col.end());
//		for(int i=0;i<row.size();i++) printf("%d ",row[i]);puts("");
		add(1,a,1,b);add(1,b,1,a);
		add(1,a,m-b+1,m);add(n-b+1,n,1,a);
		add(n-a+1,n,1,b);add(1,b,m-a+1,m);
		add(n-a+1,n,m-b+1,m);add(n-b+1,n,m-a+1,m);
		ll res=0;
		for(int i=0;i<5;i++)
			for(int j=0;j<5;j++)
				if(ans[i][j]==k) res+=(ll)(row[i+1]-row[i])*(col[j+1]-col[j]);
		for(int i=0;i<5;i++){
			for(int j=0;j<5;j++) printf("%d ",ans[i][j]);
			puts("");
		}
		return res;
	}
};

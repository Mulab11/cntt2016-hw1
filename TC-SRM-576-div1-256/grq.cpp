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

const int N=2505;
struct node{
	int x,y,z;
}p[N];
int n,m,cnt,fa[N];
bool cmp(node a,node b){
	return a.z<b.z;
}
int find(int x){
	if(fa[x]!=x) fa[x]=find(fa[x]);
	return fa[x];
}
void merge(int x,int y){
	x=find(x);y=find(y);
	fa[x]=y;
}
bool check(vector<string> a,int x,int y){
	if(y<0) return 0;
	return a[x][y]=='X';
}
void add(int x,int y,int z){p[++cnt]=(node){x,y,z};}

class ArcadeManao{
public:
	int shortestLadder(vector<string> a, int cr, int cc){
		cr--;cc--;
		n=a.size();m=a[0].size();
		for(int i=0;i<n*m;i++) fa[i]=i;
		cnt=0;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++){
				if(a[i][j]=='.') continue;
				if(check(a,i,j-1)) merge(i*m+j-1,i*m+j);
				int k;
				for(k=i+1;k<n;k++) if(a[k][j]=='X') break;
				if(k<n) add(i*m+j,k*m+j,k-i);
			}
		sort(p+1,p+cnt+1,cmp);
		if(find(cr*m+cc)==find((n-1)*m)) return 0;
		for(int i=1;i<=cnt;i++){
			merge(p[i].x,p[i].y);
			if(find(cr*m+cc)==find((n-1)*m)) return p[i].z;
		}
		return -1;
	}
};

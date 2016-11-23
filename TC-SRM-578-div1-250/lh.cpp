#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class GooseInZooDivOne{
	static const int maxn=100*100,mod=1000000007;
	int fa[maxn],size[maxn],n,m;
	
	int num(int a,int b){
		return a*m+b;
	}
	
	int abs(int a){return (a<0)?-a:a;}
	
	int dis(int a,int b,int c,int d){
		return abs(a-c)+abs(b-d);
	}
	
	int find(int x){
		if (x!=fa[x]) fa[x]=find(fa[x]);
		return fa[x];
	}
	
	void merge(int a,int b){
		a=find(a);
		b=find(b);
		if (a==b) return;
//		printf("merge(%d,%d)\n",a,b);
		if (size[a]<size[b]) swap(a,b);
		fa[b]=a;
		size[a]+=size[b];
		return;
	}
	
	int power(long long a,int b){
		long long ret=1;
		while(b){
			if (b&1) ret=ret*a%mod;
			a=a*a%mod;
			b>>=1;
		}
		return ret;
	}
	
	public:
	int count(vector<string> field, int dist){
		n=field.size();
		m=field[0].length();
//		printf("n=%d,m=%d\n",n,m);
		for (int i=0;i<n*m;++i) fa[i]=i,size[i]=1;
		for (int i=0;i<n;++i)
		for (int j=0;j<m;++j) if (field[i][j]=='v'){
//			printf("i,j = %d,%d:\n",i,j);
			for (int a=0;a<n;++a)
			for (int b=0;b<m;++b){
//				printf("a,b= %d,%d\n",a,b);
				if (field[a][b]=='v'&&dis(i,j,a,b)<=dist)
					merge(num(i,j),num(a,b));
			}
		}
		int a=0,b=1;//,x=0,y=0;
		for (int i=0;i<n;++i)
		for (int j=0;j<m;++j) if (field[i][j]=='v'){
//			printf("%d,%d\n",i,j);
			if (fa[num(i,j)]==num(i,j)){
//				printf("size[%d,%d]=%d\n",i,j,size[num(i,j)]);
				if (size[num(i,j)]&1){
					b=((a+=b)%=mod);
//					++x;
				}
				else{
					(a<<=1)%=mod;
					(b<<=1)%=mod;
//					++y;
				}
			}
		}
//		printf("x=%d,y=%d\n",x,y);
//		printf("  %d\n",power(2,x+y-1));
		return (b-1+mod)%mod;
	}
};

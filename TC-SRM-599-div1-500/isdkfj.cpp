#include <bits/stdc++.h>

using namespace std;

struct orz{
	int x,y,z;
}a[100005];

class FindPolygons {
public:
	double minimumPolygon(int L) {
		if(L<=2||L%2)return -1;
		int n=0;
		for(int i=1;i<=L>>1;++i)
			for(int j=0;j<=i;++j){
				int k=sqrt(i*i-j*j+0.000001);
				if(k*k+j*j==i*i)a[++n]=(orz){j,k,i};
			}//合法的点 
		int ret=998244353;
		for(int i=1,p=n;i<=n;++i){
			while(p&&a[p].z+a[i].z>=L)--p;
			for(int j=p;j>i;--j){
				if(a[i].x*a[j].y-a[j].x*a[i].y==0)continue;//不共线 
				int k=(a[i].x-a[j].x)*(a[i].x-a[j].x)+(a[i].y-a[j].y)*(a[i].y-a[j].y);
				int l=L-a[i].z-a[j].z;
				if(l*l==k)//可以构成三角形 
					ret=min(ret,max(a[j].z,l)-min(a[i].z,l));
			}
		}
		if(ret==998244353)ret=L%4?1:0;//矩形 
		return 1.*ret;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!

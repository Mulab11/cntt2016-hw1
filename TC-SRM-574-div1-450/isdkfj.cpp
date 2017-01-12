#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
LL f[1<<18][18];

bool check(int N,int s,int x,int y){//判断s中点是否有位于x,y两端 
	if(x>y)swap(x,y);
	bool f1=0,f2=0;
	for(int i=0;i<N;++i)
	if(s&(1<<i)){
		if(i<x||i>y)f2=1;
		else f1=1;
	}
	return f1&&f2;
}
bool pd(int N,int x,int y){//判断x,y是否相邻 
	if(x>y)swap(x,y);
	if(y==x+1)return 1;
	if(x==0&&y==N-1)return 1;
	return 0;
}

class PolygonTraversal {
public:
	long long count(int N, vector <int> points) {
		int st=0;
		for(int i=0;i<points.size();++i)st|=1<<(points[i]-1);
		f[st][*(--points.end())-1]=1;//初始化 
		for(int s=0;s<1<<N;++s)
			for(int i=0;i<N;++i)
			if(f[s][i])
				for(int j=0;j<N;++j)//枚举下一个端点 
				if(!(s&(1<<j))&&check(N,s^(1<<i),i,j))
				f[s|(1<<j)][j]+=f[s][i];
		LL ans=0;
		for(int i=0;i<N;++i)if(!pd(N,i,points[0]-1))ans+=f[(1<<N)-1][i];
		return ans;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!

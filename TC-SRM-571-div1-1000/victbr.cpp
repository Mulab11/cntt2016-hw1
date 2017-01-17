#include <bits/stdc++.h>

using namespace std;
typedef double ld;
typedef long long ll;
const int N = 65;
const ld eps = 0;
const ld eps2 = 1e-6;
struct Point{
	ll x,y;
	Point(){}
	Point(ll x,ll y):x(x),y(y){}
};
/*
这题卡精。。。long double也卡。。。只好先整形在浮点运算。
发现上述方法不行。。。只好用一些奇怪的eps技巧。。。 
*/ 
Point operator - (const Point &a,const Point &b){
	return Point(a.x-b.x,a.y-b.y);
}
ll dot(const Point &a,const Point &b){
	return a.x*b.x+a.y*b.y;
}
ld getdis(const Point &a,const Point &b){
	return sqrt(dot(a-b,a-b));
}

class CandyOnDisk{
	public:
		bool b[N];
		int n,e[N];
		ld dis[N][N];
		ld low[N],up[N];
		Point S,T,p[N];
		string ableToAchieve(vector <int> x, vector <int> y, vector <int> r, int sx, int sy, int tx, int ty){
			if (sx == tx && sy == ty) return "YES";
			n = x.size();
			S = Point(sx,sy);
			T = Point(tx,ty);
			for (int i = 0;i < n;i++)
				p[i] = Point(x[i],y[i]);
			int t = 1,w = 0;
			for (int i = 0;i < n;i++){
				if ((ld)r[i]-getdis(p[i],S) > -eps2){//需要判相等 
					up[i] = low[i] = getdis(p[i],S);
					e[++w] = i;b[i] = 1;
				}
				else{up[i] = 0;low[i] = 2e9;}
			}
			
			for (int i = 0;i < n;i++)
				for (int j = 0;j < n;j++)
					dis[i][j] = getdis(p[i],p[j]);
			if (w == 0) return "NO";//可能一开始就无解 
			//第一次知道不能输出换行符。。。。 
			while (1){
				int u = e[t];
				for (int i = 0;i < n;i++){
					if ((ld)r[i]+r[u]-dis[i][u] > -eps && i != u){
						if (dis[i][u] < eps2){//特判同心圆 这个地方需要eps 
							continue;
						}
						if (up[i] < low[i]){
//							cout << i << endl;
							if (up[u]+r[i] > dis[i][u]){
								if (up[u]+dis[u][i] < r[i]){
									up[i] = min((ld)r[i],dis[i][u]+up[u]);
									low[i] = max((ld)0.0,dis[i][u]-up[u]);
								}
								else{
									low[i] = max((ld)0.0,dis[i][u]-r[u]);
									up[i] = min((ld)r[i],dis[i][u]+r[u]);	
								}
								if(low[i] < up[i]){
									(w%=60)++;e[w] = i;b[i] = 1;
								}
							}
							else if (dis[i][u]+r[i] < up[u]){//注意考虑包含的情况 
								low[i] = 0;
								up[i] = r[i];
								if (low[i] < up[i]){
									(w%=60)++;e[w] = i;b[i] = 1;
								}
							}
						}
						else{
							ld x = low[i],y = up[i];
//							printf("%d %d\n",i,u);
//							printf("%d %.10lf %.10lf\n",i,low[i],up[i]);
							if (up[u]+r[i] > dis[i][u]){
								if (up[u]+dis[u][i] < r[i]){
									up[i] = max(up[i],min(dis[i][u]+r[u],(ld)r[i]));
									low[i] = min(low[i],max((ld)0.0,dis[i][u]-r[u]));
								}
								else{
									low[i] = min(low[i],max((ld)0.0,dis[i][u]-r[u]));
									up[i] = max(up[i],min((ld)r[i],dis[i][u]+r[u]));	
								}
							}
							else if (dis[i][u]+r[i] < up[u]){//注意考虑包含的情况 
								low[i] = 0;
								up[i] = r[i];
							}

							if (fabs(x-low[i]) > eps2 || fabs(y-up[i]) > eps2){//有更新就继续 
								if (!b[i]) {
									(w%=60)++;e[w] = i;b[i] = 1;
								}
							}
						}
					}
				}
				b[u] = 0;
				if (t == w) break;
//				printf("%d %d\n",t,w);
				(t%=60)++;
			}
			
//			printf("%.3lf %.3lf\n",(double)T.x,(double)T.y);
//			printf("%lld\n",T.x*T.x);
			
//			printf("%lld %lld\n",dot(S,S),dot(T,T));
//			printf("%.10lf %.10lf\n",(double)getdis(p[0],S),(double)getdis(p[0],T));
//			for (int i = 0;i < n;i++)
//				printf("aa%d %.10lf %.10lf\n",i,(double)low[i],(double)up[i]);
			for (int i = 0;i < n;i++){
				ld u = getdis(T,p[i]);
//				printf("%.20lf\n",(double)u);
//				printf("%.20lf %.20lf\n",(double)low[i],(double)up[i]);
//				printf("%d %d\n",(u-low[i] > -eps),(u-up[i] < eps));
				if (u-low[i] > -eps && u-up[i] < eps) return "YES";
			}
			return "NO";
		}
}A;

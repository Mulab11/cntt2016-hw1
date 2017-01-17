#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 233;

struct Point{
	int x,y;
	Point(){}
	Point(int x,int y):x(x),y(y){}
};
Point operator + (const Point &a,const Point &b){
	return Point(a.x+b.x,a.y+b.y);
}
Point operator - (const Point &a,const Point &b){
	return Point(a.x-b.x,a.y-b.y);
}
ll cross (const Point &a,const Point &b){
	return (ll)a.x*b.y-(ll)a.y*b.x;
}

class CheckerFreeness{
	public:
		Point a[N],b[N]; 
		bitset <N> f[N][N],g[N][N];
		int n,m,tot,len;

		string isFree(vector <string> whiteX, vector <string> whiteY, vector <string> blackX, vector <string> blackY){
			string whitex="",whitey="",blackx="",blacky="";
			for (int i = 0;i < whiteX.size();i++)
				whitex = whitex + whiteX[i];			
			for (int i = 0;i < whiteY.size();i++)
				whitey = whitey + whiteY[i];
			for (int i = 0;i < blackX.size();i++)
				blackx = blackx + blackX[i];			
			for (int i = 0;i < blackY.size();i++)
				blacky = blacky + blackY[i];				

			whitex = whitex + ' ';whitey = whitey + ' ';
			blackx = blackx + ' ';blacky = blacky + ' ';
			

			n = 0;len = whitex.size();tot = 0;
			for (int i = 0;i < len;i++){
				if (whitex[i] == ' ') {
					a[++n].x = tot;	
					tot = 0;
				}
				else{
					if ('0' <= whitex[i] && whitex[i] <= '9')
						tot = tot*10 + whitex[i]-'0';
				}
			}
			n = 0;len = whitey.size();tot = 0;
			for (int i = 0;i < len;i++){
				if (whitey[i] == ' ') {
					a[++n].y = tot;	
					tot = 0;
				}
				else{
					if ('0' <= whitey[i] && whitey[i] <= '9')
						tot = tot*10 + whitey[i]-'0';
				}
			}
			m = 0;len = blackx.size();tot = 0;
			for (int i = 0;i < len;i++){
				if (blackx[i] == ' ') {
					b[++m].x = tot;	
					tot = 0;
				}
				else{
					if ('0' <= blackx[i] && blackx[i] <= '9')
						tot = tot*10 + blackx[i]-'0';
				}
			}
			m = 0;len = blacky.size();tot = 0;
			for (int i = 0;i < len;i++){
				if (blacky[i] == ' ') {
					b[++m].y = tot;	
					tot = 0;
				}
				else{
					if ('0' <= blacky[i] && blacky[i] <= '9')
						tot = tot*10 + blacky[i]-'0';
				}
			}

			for (int i = 1;i <= m;i++)
				for (int j = 1;j <= n;j++)
					for (int k = 1;k <= n;k++)
						f[i][j][k] = check1(i,j,k);
			for (int i = 1;i <= m;i++)
				for (int j = 1;j <= m;j++)
					for (int k = 1;k <= n;k++)
						g[i][j][k] = check2(i,j,k);
			for (int i = 1;i <= m;i++)
				for (int j = 1;j <= m;j++)
					for (int k = 1;k <= n;k++){
						bitset <N> c,d;
						c = f[i][k] ^ f[j][k];
						if (g[i][j][k] == 1){
							d = g[i][j];d.flip();
							c = c & d;
						}
						else c = c & g[i][j];
						if (c.count() > 0) return "NO";
					}
			return "YES";
		}
		bool check1(int i,int j,int k){
			return cross(b[i]-a[j],a[k]-a[j]) > 0;
		}
		bool check2(int i,int j,int k){
			return cross(b[i]-b[j],a[k]-b[j]) > 0;
		}
};

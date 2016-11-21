#include<bitset>
#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<sstream>
#include<iostream>
#include<algorithm>
using namespace std;

struct point{
	double x,y;
	point (double a=0,double b=0):x(a),y(b){};
	point operator + (const point &a)const{
		return point(x+a.x,y+a.y);
	}
	point operator - (const point &a)const{
		return point (x-a.x,y-a.y);
	}
	double operator * (const point &a)const{
		return x*a.y-y*a.x;
	}
};

class CheckerFreeness{
	private:
		static const int maxn=222;
		point nod[maxn<<1];
		int n,m;
		bitset<maxn> ch[maxn][maxn],ct[maxn][maxn];
	
	public:
		string isFree(vector<string> whiteX, vector<string> whiteY, vector<string> blackX, vector<string> blackY){
			stringstream tmp;
			for (auto &x: whiteX) tmp<<x;
			while(tmp>>nod[n].x) ++n;
			tmp.clear();
			for (auto &x: whiteY) tmp<<x;
			for (int i=0;i<n;++i) tmp>>nod[i].y;
			tmp.clear();
			m=n;
			for (auto &x: blackX) tmp<<x;
			while(tmp>>nod[m].x) ++m;
			tmp.clear();
			for (auto &x: blackY) tmp<<x;
			for (int i=n;i<m;++i) tmp>>nod[i].y;
			
			for (int i=n;i<m;++i)
			for (int j=0;j<n;++j)
			for (int k=n;k<m;++k)
			if (i!=k) if((nod[j]-nod[i])*(nod[k]-nod[j])<0) ch[i-n][j][k-n]=1;
			
			for (int i=0;i<n;++i)
			for (int j=0;j<n;++j) if (i!=j)
			for (int k=n;k<m;++k) if ((nod[j]-nod[i])*(nod[k]-nod[i])>0) ct[i][j][k-n]=1;
			
			for (int i=n;i<m;++i)
			for (int j=0;j<n;++j)
			for (int k=0;k<n;++k) if (j!=k) if (ct[j][k][i-n])
			{
				if ((ch[i-n][k]&(~ch[i-n][j])&ct[k][j]).any()) return "NO";
				
			}
			return "YES";
		}
};

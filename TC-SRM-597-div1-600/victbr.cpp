#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 60;
const double eps = 1e-6;

struct Node{
	int x,y,u,v;
	Node(){}
	Node(int _x,int _y,int _u,int _v){
		if (_x > _u) {swap(_x,_u);swap(_y,_v);}
		x = _x;y = _y;
		u = _u;v = _v;
	}
};
struct Point{
	int x,y;
	Point(){};
	Point(int x,int y):x(x),y(y){}
};
Point operator - (const Point &a,const Point &b){
	return Point(a.x-b.x,a.y-b.y);
}
ll cross(const Point &a,const Point &b){
	return (ll)a.x*b.y-(ll)a.y*b.x;
}
bool operator < (const Node &a,const Node &b){
	return a.x == b.x ? a.u < b.u : a.x < b.x;
}


class ConvexPolygonGame{
	public:
		int n,mn,mx,cnt;
		Point pt[200001+10];
		Node nod[N];
		string winner(vector <int> X, vector <int> Y){
			n = X.size();
			mn = X[0];mx = X[0];
			for (int i = 0;i < n;i++){
				nod[i] = Node(X[i],Y[i],X[(i+1)%n],Y[(i+1)%n]);
//				printf("%d %d %d %d\n",nod[i].x,nod[i].y,nod[i].u,nod[i].v);
				mn = min(mn,X[i]);
				mx = max(mx,X[i]);
			}
			sort(nod,nod+n);
			for (int i = 0;i < n;i++)
				if (nod[i].x == nod[i].u){
					
					for (int j = min(nod[i].v,nod[i].y)+1;j < max(nod[i].v,nod[i].y);j++){
						pt[++cnt] = Point(nod[i].x,j);
//						printf("%d %d\n",nod[i].x,j);
						if (cnt > 200001) return "Masha";
					}
				}
			int t = -1,w = -1,last = 0;
//			printf("%d %d\n",mn,mx);
			for (int i = mn;i < mx;i++){
				if (t != -1 && w != -1){
					double x1 = (double)((double)nod[t].y-nod[t].v)/(nod[t].x-nod[t].u);
					double y1 = (double)((double)nod[w].y-nod[w].v)/(nod[w].x-nod[w].u);
					double xx = 0,yy = 0;
					x1 = x1*i+nod[t].y-x1*nod[t].x;
					if (nod[t].u == i) xx = 0.5;
					if (nod[w].u == i) yy = 0.5;
					y1 = y1*i+nod[w].y-y1*nod[w].x;					
					
					for (int j = ceil(min(x1+xx-eps,y1+yy-eps));j <= floor(max(x1-xx+eps,y1-yy+eps));j++){
//						if (i == -1)cout << j << endl;
						pt[++cnt] = Point(i,j);
			//		printf("%d %d\n",i,j);
						if (cnt > 200001) return "Masha";
					}
				}
				if (t == -1) t = last++;
				if (w == -1) w = last++;
				if (nod[t].u == i) t = last++;
				if (nod[w].u == i) w = last++;				
				while (nod[t].x == nod[t].u) t = last++;
				while (nod[w].x == nod[w].u) w = last++;
			}
			for (int j = 3;j <= cnt;j++)
				if (cross(pt[j]-pt[2],pt[j]-pt[1]) != (ll)0) return "Masha";
			return "Petya";
		}
}A;


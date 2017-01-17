#include <bits/stdc++.h>

using namespace std;

class RobotHerb{
	public:
		int n;
		long long x,y,u,v;
		long long getdist(int T, vector <int> a){
			n = a.size();
			x = 0;y = 0;int z = 0,w;
			for (int i = 0;i < n;i++){
				if (z == 0) x += a[i];
				if (z == 1) y += a[i];
				if (z == 2) x -= a[i];
				if (z == 3) y -= a[i];
				(z += a[i]) %= 4;
			}
			u = x;v = y;w = z;
			for (int i = 1;i < 4;i++){
				if (w == 0) u += x,v += y;
				if (w == 1) v += x,u -= y;
				if (w == 2) u -= x,v -= y;
				if (w == 3) v -= x,u += y;					
				(w += z)%=4;
			}
			//cout << u << ' ' << v << endl;
			u *= T/4;v *= T/4;
			for (int i = 1;i <= T%4;i++){
				if (w == 0) u += x,v += y;
				if (w == 1) v += x,u -= y;
				if (w == 2) u -= x,v -= y;
				if (w == 3) v -= x,u += y;					
				(w += z)%=4;
			}			
			return abs(u)+abs(v);//×¢Òâ²»ÊÇu+v 
		}
};

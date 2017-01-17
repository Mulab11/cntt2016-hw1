#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

class HyperKnight{
	public:
		ll ans;
		long long countCells(int a, int b, int numRows, int numColumns, int K) {
			ans = 0;
			int x[6] = {0,numRows,min(a,numRows),min(b,numRows),max(0,numRows-a),max(0,numRows-b)};
			int y[6] = {0,numColumns,min(a,numColumns),min(b,numColumns),max(0,numColumns-a),max(0,numColumns-b)};
			sort(x,x+6);sort(y,y+6);
//			printf("%d %d %d %d\n",x[0],x[1],x[2],x[3]);
//			printf("%d %d %d %d\n",y[0],y[1],y[2],y[3]);
			for (int i = 0;i < 5;i++)
				for (int j = 0;j < 5;j++)
					if (check(x[i],x[i+1],y[j],y[j+1],a,b,numRows,numColumns,K)) {
//						printf("%d %d %d %d\n",x[i],x[i+1],y[j],y[j+1]);
						ans += ((ll)x[i+1]-x[i])*(y[j+1]-y[j]); 				
					}
		
			return ans;
		}
		bool check(int x1,int x2,int y1,int y2,int a,int b,int r,int c,int k){
			int tot = 0;
			if (x2+b <= r && y2 + a <= c) tot++;
			if (x2+b <= r && y1 - a >= 0) tot++;
			if (x2+a <= r && y2 + b <= c) tot++;
			if (x2+a <= r && y1 - b >= 0) tot++;
			if (x1-b >= 0 && y2 + a <= c) tot++;
			if (x1-b >= 0 && y1 - a >= 0) tot++;
			if (x1-a >= 0 && y2 + b <= c) tot++;
			if (x1-a >= 0 && y1 - b >= 0) tot++;
			return tot == k;
		}
};

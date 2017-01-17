#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 310;

struct Node{
	int x,y;
	Node(){}
	Node(int x,int y):x(x),y(y){}
};

class Ear{
	public:
		int a[N],n,m;
		int pre[10100],suf[10100];
		Node b[N];
		string rx="",bx="",by="";		
		long long getCount(vector <string> redX, vector <string> blueX, vector <string> blueY){
			long long ans = 0;
			int len = redX.size();
			n = 0;m = 0;
			for (int i = 0;i < len;i++) rx = rx + redX[i];
			len = blueX.size();
			for (int i = 0;i < len;i++) bx = bx + blueX[i];
			len = blueY.size();
			for (int i = 0;i < len;i++) by = by + blueY[i];			
			rx = rx + ' ';bx = bx + ' ';by = by + ' ';
			
			int num = 0;
			for (int i = 0;i < rx.size();i++){
				if (rx[i] == ' ') {
					if (num) a[++n] = num; 
					num = 0;
				}
				if ('0' <= rx[i] && rx[i] <= '9')
					num = num*10+rx[i]-'0';
			}
			num = 0;
			for (int i = 0;i < bx.size();i++){
				if (bx[i] == ' ') {
					if (num) b[++m].x = num; 
					num = 0;
				}
				if ('0' <= bx[i] && bx[i] <= '9')
					num = num*10+bx[i]-'0';
			}
			num = 0;m = 0;
			for (int i = 0;i < by.size();i++){
				if (by[i] == ' ') {
					if (num) b[++m].y = num; 
					num = 0;
				}
				if ('0' <= by[i] && by[i] <= '9')
					num = num*10+by[i]-'0';
			}					
			for (int i = 1;i <= n;i++) pre[a[i]]++,suf[a[i]]++;
			for (int i = 1;i <= 10000;i++)pre[i] += pre[i-1];
			for (int i = 10000;i >= 1;i--)suf[i] += suf[i+1];
			sort(a+1,a+n+1);
			for (int i = 1;i <= m;i++)
				for (int j = 1;j <= m;j++)
					if (b[i].y > b[j].y){
						int sum1 = 0,sum2 = 0,x3;
						if (b[i].x < b[j].x){
							int u = (b[i].x-b[j].x)*b[j].y,v = b[i].y-b[j].y;
							x3 = b[j].x - u/v + 1;
							if (x3 > 10000) x3 = 10001;
							sum1 = suf[x3]*(suf[b[j].x+1]-suf[x3]+suf[b[j].x+1]-1)/2;
							sum2 = pre[b[i].x-1]*(pre[b[j].x-1]-1+pre[b[j].x-1]-pre[b[i].x-1])/2;
							ans += sum1*sum2;
						}
						if (b[i].x == b[j].x){
							sum1 = pre[b[i].x-1];
							sum1 = sum1*(0+sum1-1)/2;
							sum2 = suf[b[i].x+1];
							sum2 = sum2*(0+sum2-1)/2;
							ans += sum1*sum2;
						}
						if (b[i].x > b[j].x){
							int u = (b[i].x-b[j].x)*b[j].y,v = b[i].y-b[j].y;
							x3 = b[j].x - u/v - 1;
							if (x3 < 1) x3 = 0;
							sum1 = pre[x3]*(pre[b[j].x-1]-pre[x3]+pre[b[j].x-1]-1)/2;
							sum2 = suf[b[i].x+1]*(suf[b[j].x+1]-1+suf[b[j].x+1]-suf[b[i].x+1])/2;
							ans += sum1*sum2;							
						}	
//						printf("--%d %d %d %d\n",i,j,sum1,sum2);				
					}
			return ans;
		}
};



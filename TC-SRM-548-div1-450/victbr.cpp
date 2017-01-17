#include <bits/stdc++.h>

using namespace std;
const int N = 60;

struct Node{
	int x,y;
	Node(){}
	Node(int x,int y):x(x),y(y){}
			
};
bool operator < (const Node &a,const Node &b){return a.x < b.x;}

class KingdomAndDice{
	public:
		int cnt,n,len,num[N*N];
		bool f[N][N*N],bo[N*N];
		Node a[N<<1];
		double newFairness(vector <int> firstDie, vector <int> secondDie, int X){
			memset(f,0,sizeof(f));
			memset(bo,0,sizeof(bo));
			n = firstDie.size();len = 0;cnt = 1;
			int sum = 0,tot = 0,val = 0;
			for (int i = 0;i < n;++i){
				if (firstDie[i] != 0) a[len++] = Node(firstDie[i],i);
				else sum++;
				a[len++] = Node(secondDie[i],i+n);
			}
			sort(a,a+len);
			cnt = sum+1;
			a[len].x = X;
			if (a[0].x < cnt) cnt = a[0].x;
			for (int i = 0;i < len;i++){
				bo[cnt] = 1;
				if (a[i].y >= n) {
					secondDie[a[i].y-n] = cnt;
					tot++;
					num[cnt+1] = 1;
				}
				else {
					firstDie[a[i].y] = cnt;
					val += tot;
				}
				if (a[i+1].x-a[i].x <= sum) cnt += a[i+1].x-a[i].x;
				else cnt += sum+1;
			}
			for (int i = 1;i <= cnt;i++)
				num[i] += num[i-1];
			f[0][val] = 1;
			for (int i = 1;i <= cnt;i++)
				if (!bo[i]){
					for (int j = sum;j >= 1;j--)
						for (int k = 0;k < n*n;k++)
							if (f[j-1][k]) f[j][k+num[i]] |= f[j-1][k];
				}
			int l = n*n/2,r;
			if (n&1) r = l + 1;else r = l;
			while (1){
				bool flag = 0;
				for (int i = 0;i <= sum;i++)
					flag |= f[i][l];
				if (flag) return (double)l/n/n;
				flag = 0;
				for (int i = 0;i <= sum;i++)
					flag |= f[i][r];
				if (flag) return (double)r/n/n;				 
				l--;r++;
			}
			return 0;
		}
};

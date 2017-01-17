#include <bits/stdc++.h>
 
using namespace std;
typedef long long ll;

const int N = 60;

struct Node{
	int x,y;
	Node(){}
	Node(int x,int y):x(x),y(y){}
};
bool operator < (const Node &a,const Node &b){
	return a.x < b.x;
}

class GUMIAndSongsDiv1{
	public:
		Node nod[N];
		int f[N][N][N],n,ans;
		int maxSongs(vector<int> duration,vector<int> tone, int T){
			for (int i = 0;i < tone.size();i++)
				nod[i+1] = Node(tone[i],duration[i]);
			n = tone.size();
			memset(f,0x3f,sizeof(f));
			sort(nod+1,nod+n+1);
			f[0][0][0] = 0;
			for (int i = 0;i < n;i++){
				for (int j = 0;j <= i;j++)
					for (int k = 0;k <= i;k++){
						f[i+1][j+1][i+1] = min(f[i+1][j+1][i+1],f[i][j][k]+nod[i+1].y+(k != 0)*(nod[i+1].x-nod[k].x));//第一个不用减 
						f[i+1][j][k] = min(f[i+1][j][k],f[i][j][k]);
					}
			}
			for (int i = 1;i <= n;i++)
				for (int j = 0;j <= i;j++)
					for (int k = 0;k <= i;k++)
						if (f[i][j][k] <= T) ans = max(ans,j);   
			return ans;
		}
};

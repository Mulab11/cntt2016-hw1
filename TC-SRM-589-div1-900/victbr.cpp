#include <bits/stdc++.h>

using namespace std;

const int N = 310;

class FlippingBitsDiv1{
	public:
		int n,T,ans,m;
		int f[N][2];
		bitset<N> q;
		string s;
		int getmin(vector <string> S, int M){
			n = S.size();m = M;ans = 0x7fffffff;
			for (int i = 0;i < n;i++) s = s + S[i];
			n = s.size();
			for (int i = 0;i < n;i++) q[i] = s[i]-'0';
			T = n/M;
			if (M <= 17) solve1();
			else solve2();
			return ans;
		}
		void solve1(){
			bitset<N> p;
			for (int i = 0;i < (1<<m);i++){
				for (int j = 0;j < n;j++)
					p[j] = (i&(1<<(j%m)));
				p ^= q;
				for (int j = 0;j < n;j++){
					f[j+1][0] = f[j][0] + (p[j] == 1);
					f[j+1][1] = f[j][1] + (p[j] == 0);
					if ((j+1)%m == 0){ 	
						f[j+1][0] = min(f[j+1][0],f[j+1][1]+1);
						f[j+1][1] = min(f[j+1][1],f[j+1][0]+1);
					}
				}
				ans = min(ans,f[n][0]);
			}
		}
		void solve2(){
			bitset<N> p;
			static int a[20];
			for (int i = 0;i < (1<<T);i++){
				p = q;int tot = 0;
				for (int j = 0;j < T;j++)	
					if ((1<<j)&i) {a[j] = 1;tot++;}//覆盖前km要算一次操作 
					else a[j] = 0;//注意覆盖上次的信息 
				for (int j = T-1;j >= 0;j--)
					a[j] ^= a[j+1];//注意是异或后一个而不是前一个 
				for (int j = 0;j < T;j++)
					if (a[j] == 1){
						for (int k = j*m;k < j*m+m;k++)
							p[k] = p[k]^1;
					}
				for (int j = 0;j < m;j++){
					int x = 0,y = 0;
					for (int k = j;k < n;k += m)
						if (p[k] == 0) x++;//是0不是'0' 
						else y++;
					if (x > y) tot += y;
					else tot += x;
				}
				ans = min(ans,tot);
			}
		}
};


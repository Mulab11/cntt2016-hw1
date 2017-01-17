/*
	对于每一个变量，有两种情况：1.最值在顶点 2.最值在端点 
	于是枚举每个变量取最值的情况，判断是否合法即可。
	直接求解是n^3的，注意到：
	如果存在xixj，目标函数中无这一项，则必然有一个(xi或xj)在端点取最值。所以不存在。
	此时原式可看成xixj+bixi+bjxj+c=(xi+bj)(xj+bi)-c'，显然当xi+bj=xj+bi时取最值。
	于是xi-xj=bi-bj，由于对于所有最值在顶点的k，xixk都存在。所以bi-bj只与最值在端点的k有关。
	于是可以On求xi-xj，进而On^2求解。 
*/

#include <bits/stdc++.h>

using namespace std;
const double eps = 1e-6;
const int N = 15;

class BoundedOptimization{
	public:
		double mem[N][N],f[N][N],g[N][N];
		double ans,x[N][N],val[N],ms;
		int n,m,ad,state[N],lower[N],upper[N];
		string s;
		double maxValue(vector <string> expr, vector <int> lowerBound, vector <int> upperBound, int maxSum){
			int len = expr.size(),sum = 0;ms = maxSum;
			for (int i = 0;i < len;i++) s = s + expr[i];
			m = s.size();
			n = lowerBound.size();ad = n;
			for (int i = 0;i < n;i++) lower[i] = lowerBound[i],upper[i] = upperBound[i];
			for (int i = 0;i < n;i++) sum += upperBound[i];
			if (maxSum > sum){//特判最值都在端点，因为此时不满足sigmaxi=max。 
				int val = 1;
				for (int j = 0;j < m;j++){
					if ('a' <= s[j] && s[j] <= 'z')
						val *= upperBound[s[j]-'a'];
					else ans += val,val = 1;
				}
				ans += val;
				return ans;
			}
			int u = 0,v = 0; 
			for (int j = 0;j < m;j++){
				if ('a' <= s[j] && s[j] <= 'z'){
					if (u == 0) u = s[j]-'a';
					else v = s[j]-'a';
				}
				else{
					if (u < v) swap(u,v);
					mem[u][v]+=1;
					u = 0;v = 0;
				}
			}
			if (u < v) swap(u,v);
			mem[u][v]+=1;
			
			dfs(0);
			return ans;
		}
		void dfs(int p){
			if (p >= n){
				double tot = 0,sum = ms;
				memset(val,0,sizeof(val));
				memset(f,0,sizeof(f));
				for (int i = 0;i < n;i++){
					if (state[i] == 0) val[i] = lower[i];
					if (state[i] == 1) val[i] = upper[i];
					sum -= val[i];
				}
				
				for (int i = 0;i < n;i++)//维护函数 
					for (int j = 0;j <= i;j++)
						if (state[i] != 2 && state[j] != 2)
							f[ad][ad] += mem[i][j]*val[i]*val[j];
						else if (state[i] != 2) f[j][ad] += mem[i][j]*val[i];
						else if (state[j] != 2) f[i][ad] += mem[i][j]*val[j];
						else f[i][j] += mem[i][j]; 								
						
				int u = -1;//判断是否所有xixj都存在 
				for (int i = 0;i < n;i++)
					if (state[i] == 2){
						if (u == -1) u = i;
						bool flag = 1;
						for (int j = 0;j < i;j++)
							if (state[j] == 2)
								if (fabs(f[i][j]) < eps) flag = 0;
						if (!flag) return;
					}

				if (u != -1){//注意可能所有答案都在端点。 
					int cnt = 0;
					for (int i = 0;i < n;i++) 
						if (state[i] == 2) sum += f[u][ad]-f[i][ad],cnt++;
					sum /= cnt;

					for (int i = 0;i < n;i++) 
						if (state[i] == 2) val[i] = sum - (f[u][ad]-f[i][ad]);
				}
				sum = 0;//判是否在范围内 
				for (int i = 0;i < n;i++){
					if (val[i]-upper[i] > eps) return;
					if (lower[i]-val[i] > eps) return;
					sum += val[i];
				}

				if (fabs(sum-ms) > eps) return;	
				for (int j = 0;j < n;j++){
					for (int k = 0;k < j;k++){
						tot += mem[j][k]*val[j]*val[k];
					}
					tot += mem[j][ad]*val[j];
				}
				
				tot += mem[ad][ad];
				ans = max(ans,tot);
				return;
			}
			state[p] = 0;dfs(p+1);
			state[p] = 1;dfs(p+1);
			state[p] = 2;dfs(p+1);
		}
};

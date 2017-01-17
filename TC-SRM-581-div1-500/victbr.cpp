#include <bits/stdc++.h>

using namespace std;

const int N = 310;

struct Edge{
	int next,end;
};

class TreeUnion{
	public:
		string s;
		int n,a[N],b[N],cnt[2][5];
		int first1[N],efn1;
		int first2[N],efn2;
		Edge edge1[N<<1],edge2[N<<1];
		double ans;
		double expectedCycles(vector <string> tree1, vector <string> tree2, int K){
			int tot,cntt;
			for (int i = 0;i < tree1.size();i++)
				s = s + tree1[i];
			tot = 0;cntt = 0;
			s = s + ' ';
			for (int i = 0;i < s.size();i++){
				if (s[i] == ' '){
					cntt++;
					addedge1(tot,cntt);
					tot = 0;
				}
				else tot = tot*10+s[i]-'0';
			}
			cntt++;addedge1(tot,cntt);
			n = cntt+1;
			
			for (int i = 0;i < tree2.size();i++)
				s = s + tree2[i];
			tot = 0;cntt = 0;
			s = s + ' ';
			for (int i = 0;i < s.size();i++){
				if (s[i] == ' '){
					cntt++;
					addedge2(tot,cntt);
					tot = 0;
				}
				else tot = tot*10+s[i]-'0';
			}
			cntt++;addedge2(tot,cntt);

			for (int i = 0;i < n;i++){
				dfs1(i,0,0);
				dfs2(i,0,0);
			}
			for (int i = 0;i < 5;i++)
				for (int j = 0;j < 2;j++)
					cnt[j][i] /= 2;
			for (int i = 1;i < K-2;i++)
				ans += 2.0/n/(n-1)*cnt[0][i]*cnt[1][K-2-i];

			return ans;
		}
		void addedge1(int x,int y){
			edge1[++efn1].end = y;
			edge1[  efn1].next = first1[x];
			first1[x] = efn1;
			edge1[++efn1].end = x;
			edge1[  efn1].next = first1[y];
			first1[y] = efn1;
		}
		void addedge2(int x,int y){
			edge2[++efn2].end = y;
			edge2[  efn2].next = first2[x];
			first2[x] = efn2;
			edge2[++efn2].end = x;
			edge2[  efn2].next = first2[y];
			first2[y] = efn2;
		}	
		void dfs1(int x,int y,int z){
			if (z > 4) return;
			cnt[0][z]++;
			for (int h = first1[x];h;h = edge1[h].next){
				int u = edge1[h].end;
				if (u != y) dfs1(u,x,z+1);
			}
		}
		void dfs2(int x,int y,int z){
			if (z > 4) return;
			cnt[1][z]++;
			for (int h = first2[x];h;h = edge2[h].next){
				int u = edge2[h].end;
				if (u != y) dfs2(u,x,z+1);
			}
		}
};

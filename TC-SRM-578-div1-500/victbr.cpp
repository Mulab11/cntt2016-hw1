#include <bits/stdc++.h>
using namespace std;

const int N = 310,mod = 1e9+7;

struct Node{
	int x,y;
	Node(){}
	Node(int x,int y):x(x),y(y){}
};
bool cmp1(const Node &a,const Node &b){
	return a.x < b.x;
}
bool cmp2(const Node &a,const Node &b){
	return a.y < b.y;
}

class WolfInZooDivOne{
	public:
		//f deng deng g xiao xiao h deng xiao
		int f[N][N],g[N][N],h[N][N],tot,n,l[N],r[N],m;
		string s;
		struct Node nod1[N],nod2[N];
		multiset <int> q;
		multiset <int> ::iterator it;
		int count(int N, vector<string> L, vector<string> R){	
			init(N,L,R);				
			
			for (int i = 1;i <= m;i++){
				nod1[i] = Node(l[i],r[i]);
				nod2[i] = Node(l[i],r[i]);
			}
			sort(nod1+1,nod1+m+1,cmp1);
			sort(nod2+1,nod2+m+1,cmp2);
			int u = 1,v = 1;
			for (int i = 0;i <= n;i++) h[0][i] = g[0][i] =1;
			f[0][0] = 1;
			for (int i = 1;i <= n;i++){
				while (u <= m && nod1[u].x <= i) {q.insert(nod1[u].x);u++;}
				while (v <= m && nod2[v].y <  i) {
					it = q.find(nod2[v].x);
					q.erase(it);v++;
				}
				int x = i;
				if (q.size()>0) x = *(q.begin());
				for (int j = x;j < i;j++)
					f[i][j] = h[j][x-1];
				for (int j = 1;j < x;j++)
					f[i][j] = h[j][j-1];
				f[i][0] = 1;
				
				
				h[i][0] = f[i][0];
				for (int j = 1;j <= n;j++)
					h[i][j] = add(h[i][j-1],f[i][j]);
				for (int j = 0;j <= n;j++)
					g[i][j] = add(g[i-1][j],h[i][j]);
			}
			/*
			for (int i = 0;i <= n;i++){
				for (int j = 0;j <= n;j++)
					printf("%d ",f[i][j]);
				printf("\n");	
			}*/
			
			return g[n][n-1];
		}
		int add(int x,int y){
			x += y;while(x >= mod) x -= mod;
			return x;
		}
		void init(int N, vector<string> L, vector<string> R){
			n = N;
			s = "";
			for (int i = 0;i < L.size();i++) s = s + L[i];
			tot = 0;m = 0;
			for (int i = 0;i < s.size();i++){
				if ('0' <= s[i] && s[i] <= '9') tot = tot * 10 + s[i]-'0';
				else {
					l[++m] = tot+1;
					tot = 0;
				}
			}
			l[++m] = tot+1;
			
			s = "";
			for (int i = 0;i < R.size();i++) s = s + R[i];
			tot = 0;m = 0;
			for (int i = 0;i < s.size();i++){
				if ('0' <= s[i] && s[i] <= '9') tot = tot * 10 + s[i]-'0';
				else {
					r[++m] = tot+1;
					tot = 0;
				}
			}
			r[++m] = tot+1;			
		}
};/*A;


int main(){
	vector <string> s1,s2;
//	s1.push_back("0 2 2 2 2 2");
//	s2.push_back("4 3 3 5 5 4");
	s1.push_back("0 2 2 2");
	s2.push_back("4 5 5 4");
	cout << A.count(6,s1,s2);
	return 0;
}*/

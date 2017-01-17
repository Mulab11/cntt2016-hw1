#include <bits/stdc++.h>

using namespace std;
const int N = 60;

struct Node{
	int x;string s;
	Node(){}
	Node(int _x,string _s):x(_x),s(_s){}
};
bool operator < (const Node &a,const Node &b){
	return a.x > b.x;
}

//meet in the middle

class EllysBulls{
	public:
		int cnt,m,n,H;
		Node nod[N];
		map <vector<int>,vector<string> > q;
		vector <int> b;
		string ans;
		string getNumber(vector <string> guesses, vector <int> bulls){
			n = bulls.size();m = guesses[0].size();
			H = m/2;
			for (int i = 0;i < n;i++)
				nod[i] = Node(bulls[i],guesses[i]);	
			for (int i = 0;i < n;i++) b.push_back(0);

			dfs1(0,"");
			for (int i = 0;i < n;i++)
				b[i] = bulls[i];
			dfs2(H,"");
			if (cnt == 0) return "Liar";//daxiaoxie...
			else if (cnt > 1) return "Ambiguity";
			else return ans;
		}
		void dfs1(int p,string val){
			/*
			for (int i = 0;i < n;i++)
				if (b[i] > m-p || b[i] < 0) return;//可行性剪枝
				*/
			if (p == H){
				q[b].push_back(val);
				return;
			} 
			for (int i = 0;i < 10;i++){
					for (int j = 0;j < n;j++)
						if (nod[j].s[p] == (i+'0')) b[j]++; 
					dfs1(p+1,val+(char)(i+'0'));
					if (cnt > 1) return;
					for (int j = 0;j < n;j++)
						if (nod[j].s[p] == (i+'0')) b[j]--; 				
			}
		}
		void dfs2(int p,string val){
			/*
			for (int i = 0;i < n;i++)
				if (b[i] > m-p || b[i] < 0) return;//可行性剪枝
				*/
			if (p == m){
				map <vector<int>,vector<string> > :: iterator it = q.find(b);
				if (it != q.end()){
					cnt += it->second.size();
					ans = it->second[0]+val;
				}
				return;
			} 
			for (int i = 0;i < 10;i++){
					for (int j = 0;j < n;j++)
						if (nod[j].s[p] == (i+'0')) b[j]--; 
					dfs2(p+1,val+(char)(i+'0'));
					if (cnt > 1) return;
					for (int j = 0;j < n;j++)
						if (nod[j].s[p] == (i+'0')) b[j]++; 				
			}
		}
}A;

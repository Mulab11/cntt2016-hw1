// BEGIN CUT HERE

// END CUT HERE
#line 5 "DisjointSemicircles.cpp"
#include<bits/stdc++.h>
using namespace std;

int n,m,ans,flag,col;
int used[110],mat[110],f[110],id[110],L[110],R[110],b[110],a[110],fa[110];
vector<pair<int,int> > w;
vector<int> g[110];

int check(int i,int x)
{int j,k;
 
 used[i]=col;
 f[i]=x;
 for(j=0;j<g[i].size();j++)
 {	k=g[i][j];
 	//cout<<"## "<<i<<" "<<k<<endl;
 	if(used[k]==col)
	{	if(f[k]==f[i])
			return 0;
	}
	else if(!check(k,x^1))
		return 0;
 }
 return 1;
}

namespace task1
{int find(int i)
 {	return fa[i]==i?i:fa[i]=find(fa[i]);
 }

 void dfs(int i)
 {	int j,k,s,fx,fy;
 
 	if(flag) return;
 	if(i==2*n+1)
 	{	//for(j=1;j<=2*n;j++)
 		//	cout<<b[j]<<" ";
 		//cout<<endl;
	 	
		for(j=1;j<=2*n;j++)
	 	{	if(!mat[j] || mat[j]<j) continue;
	 		for(k=j+1;k<mat[j];k++)
	 		{	if(!mat[k] || mat[k]<k) continue;
	 			if(mat[k]>mat[j] && b[j]==b[k]) return;
	 		}
	 	}
	 	//cout<<"##"<<endl;
	 	for(j=0;j<=2*n;j++) g[j].clear();
 		for(j=0;j<=2*n;j++)
 			if(id[j]) fa[id[j]]=id[j];
 		w.clear();
 		//cout<<m<<endl;
 		fx=find(1);
 		fy=find(m);
 		fa[fx]=fy;
		for(j=1;j<=2*n;j++)
		{	if(a[j]==-1 || mat[j]<j) continue;
			fx=find(L[j-1]);
			fy=find(L[mat[j]]);
			//cout<<fx<<" "<<fy<<endl;
			if(b[j]==1 || (b[j]==0 && (L[mat[j]]-L[j-1])%2==0))
			{	//cout<<"^^ "<<fx<<" "<<fy<<" "<<L[mat[j]]<<" "<<L[j]<<endl;
				if(fx!=fy)
					fa[fx]=fy;
			}
			else
				w.push_back(make_pair(fx,fy));
		}
		for(j=0;j<w.size();j++)
		{	fx=find(w[j].first);
			fy=find(w[j].second);
			//cout<<j<<" "<<fx<<" "<<fy<<endl;
			g[fx].push_back(fy);
			g[fy].push_back(fx);
		}
		flag=1;
		col++;
		for(j=0;j<=2*n;j++)
			if(a[j]==-1)
			{	k=find(id[j]);
				//cout<<k<<endl;
				if(used[k]!=col) flag&=check(k,0);
			}
		//cout<<"flag "<<flag<<endl;	
		return;
	}
	//cout<<"ddd "<<endl;
	//for(j=1;j<=6;j++) cout<<b[j]<<" ";
	//cout<<endl<<"--=-=-="<<endl;
 	if(a[i]==-1 || b[i]!=-1)
	{ 	dfs(i+1);
		return;
	}
 	b[i]=b[mat[i]]=0;
 	//cout<<i<<" c0 "<<endl;
	dfs(i+1);
 	b[i]=b[mat[i]]=1;
 	//cout<<i<<" c1 "<<endl;
 	dfs(i+1);
 	b[i]=b[mat[i]]=-1;
 }

 int solve()
 {	int i,j;
 	
	memset(b,-1,sizeof(b));
	flag=0;
 	dfs(1);
 	return flag;
 }
}

namespace task2
{void dfs(int i)
 {	int j,k;
 
 	if(flag) return;
 	if(i==2*n+1)
 	{	//for(j=1;j<=2*n;j++) cout<<mat[j]<<" ";
 		//cout<<endl;
	 	
		for(j=1;j<=2*n;j++) g[j].clear();
 		for(j=1;j<=2*n;j++)
 		{	if(mat[j]<j) continue;
 			for(k=j+1;k<mat[j];k++)
 			{	if(mat[k]<k || mat[k]<mat[j]) continue;
 				g[j].push_back(k);
 				g[k].push_back(j);
 			}
 		}
 		col++;
 		flag=1;
 		for(j=1;j<=2*n;j++)
 			if(used[j]!=col) flag&=check(j,0);
 		return;
  	}
 	if(mat[i])
	{	dfs(i+1);
		return;
	}
 	for(j=i+1;j<=2*n;j++)
 		if(!mat[j])
 		{	mat[i]=j;
 			mat[j]=i;
 			dfs(i+1);
 			mat[i]=0;
 			mat[j]=0;
 		}
 }
 
 int solve()
 {	int i,j;
 	
 	flag=0;
 	dfs(1);
 	return flag;
 }
}

class DisjointSemicircles
{	public:
	string getPossibility(vector <int> labels)
	{	int i,j,s=0;
		
		n=labels.size()/2;
		for(i=1;i<=2*n;i++) a[i]=labels[i-1];
		memset(used,0,sizeof(used));
		memset(mat,0,sizeof(mat));
		for(i=1;i<=2*n;i++)
			if(a[i]!=-1)
			{	if(used[a[i]])
				{	mat[used[a[i]]]=i;
					mat[i]=used[a[i]];
					s++;
				}
				else
					used[a[i]]=i;
			}
		memset(used,0,sizeof(used));	
		memset(id,0,sizeof(id));
		memset(L,0,sizeof(L));
		
		m=1;
		id[0]=1;
		for(i=1;i<=2*n;i++)
			if(a[i]==-1) id[i]=++m;	
		L[0]=1;
		for(i=1;i<=2*n;i++) L[i]=(a[i]==-1?id[i]:L[i-1]);
		col=0;
		
		//for(i=1;i<=2*n;i++)
		//	cout<<mat[i]<<" ";
		//cout<<endl;
		//cout<<"---------------------"<<endl;
		
		if(s<=19)
			ans=(task1::solve());
		else
			ans=(task2::solve());	
		return ans?"POSSIBLE":"IMPOSSIBLE";	
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {2, 1, -1, 2, 1, -1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "IMPOSSIBLE"; verify_case(0, Arg1, getPossibility(Arg0)); }
	void test_case_1() { int Arr0[] = { 1, -1, 2, 1, -1, 2 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "IMPOSSIBLE"; verify_case(1, Arg1, getPossibility(Arg0)); }
	void test_case_2() { int Arr0[] = { 2, -1, -1, 0, -1, -1, 2, 0 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "POSSIBLE"; verify_case(2, Arg1, getPossibility(Arg0)); }
	void test_case_3() { int Arr0[] = { -1, 1, 3, -1, 1, 3, -1, -1 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "IMPOSSIBLE"; verify_case(3, Arg1, getPossibility(Arg0)); }
	void test_case_4() { int Arr0[] = { -1, 5, -1, -1, 3, 6, 8, -1, 10, 7, -1, 7, 8, 0, 11, -1, -1, 11, 0, 10, 4, -1, 6, 5, -1, -1, 9, 9, 4, 3 }
; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "POSSIBLE"; verify_case(4, Arg1, getPossibility(Arg0)); }
	void test_case_5() { int Arr0[] = { 4, -1, 2, 4, -1, 3, 3, 12, 2, 5, -1, 0, 9, 9, 8, -1, 12, 8, -1, 6, 0, -1, -1, -1, 5, 6, 10, -1, -1, 10 }
; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "IMPOSSIBLE"; verify_case(5, Arg1, getPossibility(Arg0)); }
	void test_case_6() { int Arr0[] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "POSSIBLE"; verify_case(6, Arg1, getPossibility(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	DisjointSemicircles ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE

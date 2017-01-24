// BEGIN CUT HERE

// END CUT HERE
#line 5 "InducedSubgraphs.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int mod=1000000009;

struct edge
{int u,v,next;
};
struct edge e[210];

struct unit
{int w,size;
};
struct unit f[110][110];

int n,m,root,mx,ans,num;
int head[110],fac[110],ifac[110],dis[110][110],comb[110][110],g[110][110][110],h[110][110];

void update(int &i,int x)
{i=(i+x)%mod;
}

int fpow(int i,int j)
{int ret=1;
 for(;j;i=(ll)i*i%mod,j/=2)
 	if(j&1) ret=(ll)ret*i%mod;
 return ret;
}

void add(int u,int v)
{e[num].u=u;
 e[num].v=v;
 e[num].next=head[u];
 head[u]=num;
 num++;
 e[num].u=v;
 e[num].v=u;
 e[num].next=head[v];
 head[v]=num;
 num++;
}

void dfs(int i,int fa)
{int j;
 
 if(f[i][fa].size) return;
 f[i][fa].w=0;
 f[i][fa].size=1;
 j=head[i];
 while(j!=-1)
 {	if(e[j].v!=fa)
 	{	dfs(e[j].v,i);
 		f[i][fa].size+=f[e[j].v][i].size;
 	}
 	j=e[j].next;
 } 
 f[i][fa].w=fac[f[i][fa].size-1];
 j=head[i];
 while(j!=-1)
 {	if(e[j].v!=fa)
 		f[i][fa].w=(ll)f[i][fa].w*f[e[j].v][i].w%mod*ifac[f[e[j].v][i].size]%mod;
 	j=e[j].next;
 }
}

int solve1()
{int i,j,si,sj,k1,k2;
 
 //cout<<f[2][3].size<<" "<<f[3][2].size<<" "<<dis[2][3]<<endl;
 
 ans=0;
 for(i=1;i<=n;i++) //枚举两颗子树的根是i,j 
 	for(k1=head[i];k1!=-1;k1=e[k1].next)
 	{	si=e[k1].v;
 		if(f[i][si].size!=m) continue;
 		for(j=1;j<=n;j++)
 			for(k2=head[j];k2!=-1;k2=e[k2].next)
 			{	sj=e[k2].v;
 				if(f[j][sj].size!=m) continue;
 				if(dis[i][j]==n-2*m+1 && (i!=j || (si!=sj && e[head[i]].next==-1)))
 					update(ans,(ll)f[i][si].w*f[j][sj].w%mod);
 			}
 	}
 return ans;
}

void work(int i,int fa)
{int j,k,p,q,r,s;
 
 //cout<<i<<" "<<fa<<endl;
 
 g[i][0][0]=1;
 s=0;
 j=head[i];
 while(j!=-1)
 {	if(e[j].v!=fa)
	{	work(e[j].v,i);
		for(k=0;k<=s+f[e[j].v][i].size;k++)
			for(p=0;k+p<=s+f[e[j].v][i].size;p++)
				h[k][p]=0;		
		for(k=0;k<=s;k++) //背包 
			for(p=0;k+p<=s;p++)
			{	if(!g[i][k][p]) continue;
				for(q=0;q<=f[e[j].v][i].size;q++)
					for(r=0;r+q<=f[e[j].v][i].size;r++)
						update(h[k+q][p+r],(ll)g[i][k][p]*g[e[j].v][q][r]%mod*comb[k+q][k]%mod*comb[p+r][p]%mod);
			}
		s+=f[e[j].v][i].size;
		for(k=0;k<=s;k++)	
			for(p=0;k+p<=s;p++)
				g[i][k][p]=h[k][p];		
	}
	j=e[j].next;
 }
 update(g[i][f[i][fa].size][0],f[i][fa].w);
 update(g[i][0][f[i][fa].size],f[i][fa].w);
}

int solve2()
{int i,j,x;
 
 //cout<<"hH"<<endl;
 
 root=0;
 for(i=1;i<=n;i++) //求重心 
 {	j=head[i];	
 	x=0;
 	while(j!=-1)
 	{	x=max(x,f[e[j].v][i].size);
 		j=e[j].next;
	}
	if(!root || x<mx)
	{	root=i;
		mx=x;
	}
 }
 memset(g,0,sizeof(g));
 work(root,0); //动态规划 
 ans=(ll)g[root][n-m][n-m]*fac[2*m-n]%mod;
 return ans;
}

class InducedSubgraphs
{	public:
	int getCount(vector <int> edge1, vector <int> edge2, int K)
	{	int i,j,k,x,y;
		
		n=edge1.size()+1;
		m=K;
		num=0;
		memset(head,-1,sizeof(head));
		memset(dis,0x3f,sizeof(dis));
		for(i=1;i<n;i++)
		{	x=edge1[i-1]+1;
			y=edge2[i-1]+1;
			add(x,y);
			dis[x][y]=dis[y][x]=1;
		}
		for(i=1;i<=n;i++) dis[i][i]=1;
		for(k=1;k<=n;k++) //求亮点距离 
			for(i=1;i<=n;i++)
				for(j=1;j<=n;j++)
					dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);		
		fac[0]=1;
		for(i=1;i<=n;i++) fac[i]=(ll)fac[i-1]*i%mod; //预处理阶乘，阶乘逆元，组合数 
		ifac[n]=fpow(fac[n],mod-2);
		for(i=n-1;i>=0;i--) ifac[i]=(ll)ifac[i+1]*(i+1)%mod;
		for(i=0;i<=n;i++)
		{	comb[i][0]=1;
			for(j=1;j<=i;j++)
				comb[i][j]=(comb[i-1][j-1]+comb[i-1][j])%mod;
		}
		if(m==1) return fac[n]; //特判m=1的情况 
		memset(f,0,sizeof(f));
		for(i=1;i<=n;i++) dfs(i,i); //预处理每个子树内要求id[父亲]<id[儿子]的方案 
		ans=0;
		if(m*2<=n) //分类讨论 
			return solve1();
		else
			return solve2();
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; int Arg3 = 2; verify_case(0, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {0, 1, 3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 2, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; int Arg3 = 12; verify_case(1, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {5, 0, 1, 2, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 1, 2, 4, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; int Arg3 = 4; verify_case(2, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 11; int Arg3 = 481904640; verify_case(3, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {5, 9, 4, 10, 10, 0, 7, 6, 2, 1, 11, 8}
; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0, 10, 3, 0, 6, 1, 1, 12, 12, 7, 11}
; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 6; int Arg3 = 800; verify_case(4, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arr0[] = {0, 5, 1, 0, 2, 3, 5}
; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4, 7, 0, 6, 7, 5, 0}
; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; int Arg3 = 0; verify_case(5, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_6() { int Arr0[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; int Arg3 = 890964601; verify_case(6, Arg3, getCount(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	InducedSubgraphs ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE

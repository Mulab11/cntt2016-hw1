// BEGIN CUT HERE

// END CUT HERE
#line 5 "Tunnels.cpp"
#include<bits/stdc++.h>
using namespace std;

const int inf=1e9;

struct point
{int x,y;
};
struct point pu,pd,pl,pr,plast;

int n,m,ans,tot,col,su,sd,sl,sr;
int a[110][110],used[110][110],f[110][110][110],g[110][110],L[110],R[110],v[4][2]={0,1,0,-1,1,0,-1,0};
pair<int,int> b[110];

void update(int &i,int x)
{if(i==-1 || x<i) i=x;
}

void dfs(int x,int y)
{int i,nx,ny;
 
 plast=(point){x,y};
 used[x][y]=col;
 for(i=0;i<4;i++)
 {	nx=x+v[i][0];
 	ny=y+v[i][1];
 	if(nx<=0 || nx>n || ny<=0 || ny>m || used[nx][ny] || !a[nx][ny]) continue;
 	dfs(nx,ny);
 	break;
 }
}

void work(int i,int A[],int l,int r,int flag)
{int j,k,p;

 for(j=l;j<=r;j++)
 {	if(A[j]==0) continue;
 	memset(g,-1,sizeof(g));
	for(k=0;k<=n;k++)
		for(p=0;p<=n;p++)
		{	if(f[i][k][p]==-1) continue;
			if(!flag)
			{	if(A[j]==1)
					update(g[k+1][p],f[i][k][p]);
				else if(A[j]==-1)
				{	if(k>0)
						update(g[k-1][p],f[i][k][p]);
					else
						update(g[k][p],f[i][k][p]+1);
				}
			}
			else
			{	if(A[j]==1)
					update(g[k][p+1],f[i][k][p]);
				else if(A[j]==-1)
				{	if(p>0)
						update(g[k][p-1],f[i][k][p]);
					else
						update(g[k][p],f[i][k][p]+1);
				}
			}
		}
	for(k=0;k<=n;k++)
		for(p=0;p<=n;p++)
			f[i][k][p]=g[k][p];	
 }
}

class Tunnels
{	public:
	int minimumTunnels(vector <string> frame)
	{	int i,j,k,p,s,x,y,flag;
		
		//freopen("1.out","w",stdout);
		
		n=frame.size();
		m=frame[0].length();
		flag=0;
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
			{	a[i][j]=(frame[i-1][j-1]=='X'?1:0);
				flag|=a[i][j];
			}
		if(m==1) return flag;	
		memset(used,0,sizeof(used));	
		memset(L,0,sizeof(L));
		memset(R,0,sizeof(R));
		ans=0;	
		tot=0;
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
			{	if(!a[i][j] || used[i][j]) continue;
				s=0;
				for(k=0;k<4;k++)
				{	x=i+v[k][0];
					y=j+v[k][1];
					if(x>0 && x<=n && y>0 && y<=m && a[x][y]) s++;
				}
				if(s>1) continue;
				//cout<<i<<" "<<j<<endl;
				col++;
				dfs(i,j);
				if(j==1 && plast.y==m)
					b[++tot]=make_pair(i,plast.x);
				else if(j==m && plast.y==1)
					b[++tot]=make_pair(plast.x,i);	
				else if(i==1)
				{	if(plast.y==1 || j==1)
						L[plast.x]=1;
					else if(plast.y==m || j==m)
						R[plast.x]=1;
					ans++;
				}
				else if(j==1)
				{	L[i]=-1;
					if(plast.y==1 && plast.x>i+1) L[plast.x]=1;
				}
				else if(j==m)
				{	R[i]=-1;
					if(plast.y==m && plast.x>i+1) R[plast.x]=1;
				}
				else if(plast.y==m)
					R[plast.x]=-1;
			}
		/*
		for(i=1;i<=n;i++)
		{	for(j=1;j<=m;j++)
				cout<<a[i][j]<<" ";
			cout<<endl;
		}	
		*/
		//cout<<"HH"<<endl;	
		/*
		cout<<ans<<endl;
		for(i=1;i<=n;i++) cout<<L[i]<<" ";
		cout<<endl;
		for(i=1;i<=n;i++) cout<<R[i]<<" ";
		cout<<endl;
		
		cout<<tot<<endl;
		*/
		b[++tot]=make_pair(n+1,n+1);
		memset(f,-1,sizeof(f));	
		f[0][0][0]=0;
		for(i=0;i<tot;i++)
		{	work(i,L,b[i].first+1,b[i+1].first-1,0);
			work(i,R,b[i].second+1,b[i+1].second-1,1);
			//cout<<f[i][1][0]<<" "<<f[i][0][1]<<endl;
			//cout<<"## "<<b[i+1].first<<" "<<b[i+1].second<<endl;
			if(i==tot-1) break;
			memset(g,-1,sizeof(g));
			for(k=0;k<=n;k++)
				for(p=0;p<=n;p++)
				{	if(f[i][k][p]==-1) continue;
					if(b[i+1].first<=b[i+1].second)
					{	if(k>0)
							update(g[k-1][p+1],f[i][k][p]);
						else
							update(g[k][p+1],f[i][k][p]+1);
					}
					if(b[i+1].second<=b[i+1].first)
					{	if(p>0)
							update(g[k+1][p-1],f[i][k][p]);
						else
							update(g[k+1][p],f[i][k][p]+1);
					}
				}
			for(k=0;k<=n;k++)
				for(p=0;p<=n;p++)
					f[i+1][k][p]=g[k][p];
		}
		s=inf;
		for(k=0;k<=n;k++)
			for(p=0;p<=n;p++)
				if(f[tot-1][k][p]!=-1) s=min(s,f[tot-1][k][p]);
		ans+=s;		
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); if ((Case == -1) || (Case == 8)) test_case_8(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"............................X.................X.XX", "............................X.....................", "............................XX..........XXXXXXXXXX", "..................................................", ".................................................X", ".................................................X", "..................................................", ".................................................X", ".................................................X", "XXXXX............................................X", "....X.............................................", "X...X.............................................", "....X..........................................XXX", "XXXXX.............................................", "...............................................XXX", ".................................................."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; verify_case(0, Arg1, minimumTunnels(Arg0)); }
	void test_case_1() { string Arr0[] = {"X..X.X", "...XX.", "....XX", "......", ".....X", "X....X", "XXX..X", "..X...", "XXX.XX", "....X.", "X...XX", "X....X", "X.....", "....XX", "XXX.X.", "..X.X.", "...XX.", "..XX.X", ".XX.XX", "X..XX.", "X.XX..", ".XX...", "XX....", "......", "......", "......", "......", "......", "......", "......", "X.....", "XXX...", "..X...", ".XX...", ".X....", ".X....", "XX...."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(1, Arg1, minimumTunnels(Arg0)); }
	void test_case_2() { string Arr0[] = {".............",
 "XXXXXXXXXXXXX",
 ".............",
 "XXX.......XXX",
 "..........X..",
 "..........XXX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, minimumTunnels(Arg0)); }
	void test_case_3() { string Arr0[] = {"XXXX...X..",
 "....XXXX.X",
 "XX.......X",
 "..........",
 "....XXXXXX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(3, Arg1, minimumTunnels(Arg0)); }
	void test_case_4() { string Arr0[] = {"X........X..",
 ".........XXX",
 "............",
 "XXXXXXXXXXXX",
 "............",
 "XXXXXXXXXXXX",
 "............",
 ".........XXX",
 "..XXXXXXXX.."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(4, Arg1, minimumTunnels(Arg0)); }
	void test_case_5() { string Arr0[] = {"...............X.X....X",
 "XXXXX..........X.......",
 "....X..................",
 "XXX.X.........XXXXXXXXX",
 "..X.X.........X........",
 "XXX.X.........XXXXXXXXX",
 "....X..................",
 "XXXXX......XXXXXXXXXXXX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(5, Arg1, minimumTunnels(Arg0)); }
	void test_case_6() { string Arr0[] = {".",
 "X",
 "X",
 ".",
 "X"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(6, Arg1, minimumTunnels(Arg0)); }
	void test_case_7() { string Arr0[] = {"X.XX",
 "X...",
 "...X",
 "X...",
 "X..X"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(7, Arg1, minimumTunnels(Arg0)); }
	void test_case_8() { string Arr0[] = {"...",
 "..."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(8, Arg1, minimumTunnels(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	Tunnels ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE

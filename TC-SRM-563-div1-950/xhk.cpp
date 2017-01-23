// BEGIN CUT HERE

// END CUT HERE
#line 5 "CoinsGame.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int mod=1000000009;

struct unit
{int x,y,x1,y1;
};
struct unit q[3200010];

int n,m,ans,cnt;
int a[50][50],v[4][2]={0,1,1,0,-1,0,0,-1};
bool f[42][42][42][42],used[50][50];

int fpow(int i,int j)
{int ret=1;
 for(;j;i=(ll)i*i%mod,j/=2)
 	if(j&1) ret=(ll)ret*i%mod;
 return ret;
}

int inside(int x,int y)
{return x>=1 && x<=n && y>=1 && y<=m;
}

void bfs()
{int i,j,i1,j1,t,w,x,y,x1,y1,nx,ny,nx1,ny1;
 
 t=1;
 w=0;
 for(i=0;i<=n+1;i++)
 	for(j=0;j<=m+1;j++)
 		for(i1=0;i1<=n+1;i1++)
 			for(j1=0;j1<=m+1;j1++)
 				if(f[i][j][i1][j1])
 					q[++w]=(unit){i,j,i1,j1};
 while(t<=w)
 {	x=q[t].x;
 	y=q[t].y;
 	x1=q[t].x1;
 	y1=q[t].y1;
 	for(i=0;i<4;i++)
 	{	if(a[x+v[3-i][0]][y+v[3-i][1]] && !a[x1+v[i][0]][y1+v[i][1]] && inside(x1+v[i][0],y1+v[i][1]) && inside(x+v[3-i][0],y+v[3-i][1]))
 		{	nx1=x1+v[i][0];
		 	ny1=y1+v[i][1];
		 	if(!f[x][y][nx1][ny1])
		 	{	//if(x==2 && y==2 && nx1==3 && ny1==3) cout<<x<<" "<<y<<" "<<x1<<" "<<y1<<endl;
			 	f[x][y][nx1][ny1]=1;
		 		q[++w]=(unit){x,y,nx1,ny1};
		 	}
		}
		if(a[x1+v[3-i][0]][y1+v[3-i][1]] && !a[x+v[i][0]][y+v[i][1]] && inside(x+v[i][0],y+v[i][1]) && inside(x1+v[3-i][0],y1+v[3-i][1]))
		{	nx=x+v[i][0];
		 	ny=y+v[i][1];
		 	if(!f[nx][ny][x1][y1])
		 	{	//if(nx==2 && ny==2 && x1==3 && y1==3) cout<<x<<" "<<y<<" "<<x1<<" "<<y1<<" && "<<x1+v[3-i][0]<<" "<<y1+v[3-i][1]<<endl;
			 	f[nx][ny][x1][y1]=1;
		 		q[++w]=(unit){nx,ny,x1,y1};
		 	}
		}
		if(!a[x+v[i][0]][y+v[i][1]] && !a[x1+v[i][0]][y1+v[i][1]] && inside(x+v[i][0],y+v[i][1]) && inside(x1+v[i][0],y1+v[i][1]))
		{	nx=x+v[i][0];
		 	ny=y+v[i][1];
		 	nx1=x1+v[i][0];
		 	ny1=y1+v[i][1];
			if(!f[nx][ny][nx1][ny1])
		 	{	//if(nx==2 && ny==2 && nx1==3 && ny1==3) cout<<x<<" "<<y<<" "<<x1<<" "<<y1<<endl;
			 	f[nx][ny][nx1][ny1]=1;
		 		q[++w]=(unit){nx,ny,nx1,ny1};
		 	}
		}
	}
	t++;
 }
 //cout<<w<<endl;
}
			
class CoinsGame
{	public:
	int ways(vector <string> Board)
	{	int i,j,i1,j1,s;
	 
	 	n=Board.size();
	 	m=Board[0].length();
	 	//memset(a,0,sizeof(a));
	 	for(i=1;i<=n;i++)
	 		for(j=1;j<=m;j++)
	 			a[i][j]=(Board[i-1][j-1]=='.'?0:1);
	 			
	 	//n=m=4;
		//for(i=1;i<=4;i++)
		//	for(j=1;j<=4;j++)
		//		a[i][j]=1;
		//a[1][2]=a[1][3]=a[2][2]=a[2][3]=0;		
	 			
	 	memset(f,0,sizeof(f));
	 	for(i=0;i<=n+1;i++)
		 	for(j=0;j<=m+1;j++)
			{	if(inside(i,j) || a[i][j]) continue;
				for(i1=1;i1<=n;i1++)
					for(j1=1;j1<=m;j1++)
						if(inside(i1,j1) && !a[i1][j1])
							f[i][j][i1][j1]=1;
			}
		//cout<<f[2][2][3][3]<<endl;	
		//cout<<f[1][2][1][4]<<endl;	
		bfs();
		//cout<<f[2][2][3][3]<<endl;
		//cout<<f[1][2][1][3]<<endl;
		memset(used,0,sizeof(used));
		cnt=0;
		ans=0;
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
			{	//cout<<i<<" "<<j<<" "<<a[i][j]<<" "<<used[i][j]<<endl;
				if(a[i][j] || used[i][j]) continue;
				used[i][j]=1;
				s=1;
				for(i1=1;i1<=n;i1++)
					for(j1=1;j1<=m;j1++)
						if((i1!=i || j1!=j) && !a[i1][j1] && !f[i][j][i1][j1] && !f[i1][j1][i][j])
						{	used[i1][j1]=1;
							s++;
						}
				//cout<<f[1][2][1][3]<<" "<<f[1][3][1][2]<<endl;		
				//cout<<i<<" "<<j<<" "<<s<<endl;		
				cnt+=s;
				ans=(ans+mod-fpow(2,s)+1)%mod;
			}
		//cout<<cnt<<endl;	
		ans=(ans+fpow(2,cnt)-1)%mod;	
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {".."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, ways(Arg0)); }
	void test_case_1() { string Arr0[] = {"##.#",
 ".###",
 "###.",
 "#.##"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 11; verify_case(1, Arg1, ways(Arg0)); }
	void test_case_2() { string Arr0[] = {"####",
 "#..#",
 "#..#",
 "####"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(2, Arg1, ways(Arg0)); }
	void test_case_3() { string Arr0[] = {"#.#.#"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(3, Arg1, ways(Arg0)); }
	void test_case_4() { string Arr0[] = {"........",
 "........",
 "........",
 "........",
 "........",
 "........",
 "........",
 "........"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 688856388; verify_case(4, Arg1, ways(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	CoinsGame ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE

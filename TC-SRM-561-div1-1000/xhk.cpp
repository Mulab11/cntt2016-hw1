// BEGIN CUT HERE

// END CUT HERE
#line 5 "Orienteering.cpp"
#include<bits/stdc++.h>
using namespace std;

const int inf=0x3f3f3f3f;

struct edge
{int u,v,next;
};
struct edge e[10010];

int n,m,num,tot,cnt,col;
int head[3010],a[110][110],b[310],dis[3010],q[3010],dfn[3010],fa[3010][20],c[310][310],dep[3010],used[310],v[4][2]={0,1,0,-1,1,0,-1,0};
double ans;
double comb[310][310];

void add(int u,int v)
{e[num].u=u;
 e[num].v=v;
 e[num].next=head[u];
 head[u]=num;
 num++;
}

bool cmp(int A,int B)
{return dfn[A]<dfn[B];
}

bool cmp1(int A,int B)
{return dis[A]<dis[B] || (dis[A]==dis[B] && A<B);
}

int lca(int x,int y)
{int i;
 
 if(dep[x]<dep[y]) swap(x,y);
 for(i=12;i>=0;i--)
 	if(dep[x]-(1<<i)>=dep[y]) x=fa[x][i];
 for(i=12;i>=0;i--)
 	if(fa[x][i]!=fa[y][i])
 	{	x=fa[x][i];
 		y=fa[y][i];
 	}
 return x!=y?fa[x][0]:x;
}

void dfs(int i,int pre)
{int j;
 
 dfn[i]=++cnt;
 for(j=1;j<=12;j++)
 	fa[i][j]=fa[fa[i][j-1]][j-1];
 j=head[i];
 while(j!=-1)
 {	if(e[j].v!=pre)
 	{	dep[e[j].v]=dep[i]+1;
		fa[e[j].v][0]=i;
		dfs(e[j].v,i);
	}
 	j=e[j].next;
 }
}

void bfs(int S)
{int i,j,t,w;
 
 t=1;
 w=1;
 q[t]=S;
 memset(dis,0x3f,sizeof(dis));
 dis[S]=0;
 while(t<=w)
 {	i=q[t];
 	j=head[i];
 	while(j!=-1)
 	{	if(dis[e[j].v]==inf)
 		{	dis[e[j].v]=dis[i]+1;
 			q[++w]=e[j].v;
 		}
 		j=e[j].next;
 	}
 	t++;
 }
}

class Orienteering
{	public:
	double expectedLength(vector <string> field, int K)
	{	int i,j,k,p,x,y,s,flag;
		
		n=0;
		m=K;
		tot=0;
		memset(a,0,sizeof(a));
		
		for(i=0;i<field.size();i++)
			for(j=0;j<field[i].length();j++)
				if(field[i][j]=='*') a[i][j]=++tot;
		n=tot;		
		for(i=0;i<field.size();i++)
			for(j=0;j<field[i].length();j++)
				if(field[i][j]=='.') a[i][j]=++n;
		num=0;
		memset(head,-1,sizeof(head));		
		for(i=0;i<field.size();i++)
			for(j=0;j<field[i].length();j++)
			{	if(!a[i][j]) continue;
				for(k=0;k<4;k++)
				{	x=i+v[k][0];
					y=j+v[k][1];
					if(x<0 || x>=field.size() || y<0 || y>=field[i].length() || !a[x][y]) continue;
					//cout<<i<<" "<<j<<" "<<a[i][j]<<" "<<a[x][y]<<endl;
					add(a[i][j],a[x][y]);
				}		
			}	
		cnt=0;	
		//cout<<n<<" "<<num<<" "<<tot<<" "<<m<<endl;	
		dfs(1,0);
		//cout<<"HH"<<endl;
		for(i=1;i<=tot;i++) b[i]=i;
		sort(b+1,b+tot+1,cmp);	
		for(i=0;i<=tot;i++)
		{	comb[i][0]=1;
			for(j=1;j<=i;j++)
				comb[i][j]=comb[i-1][j-1]+comb[i-1][j];
		}
		/*
		for(i=1;i<=tot;i++)
			cout<<b[i]<<" ";
		cout<<endl;
		*/
		ans=0;
		for(i=1;i<=tot;i++)
			for(j=i+1;j<=tot;j++)
			{	ans+=(dep[b[i]]+dep[b[j]]-2*dep[lca(b[i],b[j])])*(comb[i-1+tot-j][m-2]+comb[j-i-1][m-2]);
				//cout<<b[i]<<" "<<b[j]<<" "<<lca(b[i],b[j])<<" "<<dep[b[i]]+dep[b[j]]-2*dep[lca(b[i],b[j])]<<endl;
			}
		//cout<<ans<<endl;	
		if(m==2)
		{	ans/=2;
			ans/=comb[tot][2];
			return ans;
		}
		for(i=1;i<=tot;i++)
		{	bfs(i);
			for(j=1;j<=tot;j++)
				c[i][j]=j;
			sort(c[i]+1,c[i]+tot+1,cmp1);
			//for(j=1;j<=tot;j++)
			//	cout<<c[i][j]<<" ";
			//cout<<endl;
		}
		//cout<<ans<<endl;
		col=0;
		memset(used,0,sizeof(used));
		for(i=1;i<=tot;i++)
		{	col++;
			for(j=tot;j>1;j--)
			{	p=c[i][j];
				if(p<i) continue;
				s=0;
				flag=0;
				for(k=2;k<=tot;k++)	
					if(c[p][k]==i)
					{	flag=1;
						ans-=comb[s][m-2]*(dep[c[p][k]]+dep[p]-2*dep[lca(c[p][k],p)]);
						//cout<<"# "<<i<<" "<<j<<" "<<p<<" "<<s<<" "<<" "<<ans<<endl;
					}
					else if(used[c[p][k]]!=col && c[p][k]>i)
					{	s++;
						if(flag && s)
						{	//cout<<ans<<endl;
							ans-=comb[s-1][m-3]*(dep[c[p][k]]+dep[p]-2*dep[lca(c[p][k],p)]);
							//cout<<i<<" "<<j<<" "<<p<<" "<<s<<" "<<" "<<ans<<endl;
						}
					}
				used[p]=col;
			}
		}
		ans/=comb[tot][m];
		return ans;		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"*#..#",
 ".#*#.",
 "*...*"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; double Arg2 = 3.8333333333333353; verify_case(0, Arg2, expectedLength(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"*#..#",
 ".#*#.",
 "*...*"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; double Arg2 = 8.0; verify_case(1, Arg2, expectedLength(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"#.#**",
 "....#",
 "#*#**",
 "**#*#",
 "#..##",
 "*#..#",
 ".#.#.",
 "....*"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; double Arg2 = 10.825000000000024; verify_case(2, Arg2, expectedLength(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"###################",
 "#*###############*#",
 "#.....#######.....#",
 "#*###*.#.*.#.*###*#",
 "#*####*.*#*.*####*#",
 "#*#####*###*#####*#",
 "###################"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 9; double Arg2 = 30.272233648704244; verify_case(3, Arg2, expectedLength(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"**##*.**#..#.*...*#...*#..#.##..#..#.#*...#.##*##.",
 ".#..###..#..#.#.##..#.#.*#.*..#..#.#*..##.#*...*..",
 "..#.....###.#*.##..#.#.#*..#.#..#....#..#...#*####",
 ".#.##*#.*#..#*#*.#.#...*.#.*#.#.##.#*.##.#.#..*...",
 "..*.*#*.###.#..#.#..##.##.*#..#.....#.....#..#.#.#",
 ".#.##.#..##..*#..#.#...#*##*#*..#.#.#.#.##.##.#.#*",
 "..##....#..#.#*#...*.##...#.#.####...#.#*.....#...",
 ".#.*#.##.*#*.#*.#.#.#..#.#..#.#*#.###..##.##.#.##*",
 ".*.#*..*.#.#...#.*##.#.**.#.*...**..*#..#.#.#*.#..",
 ".#*.#*##....##.#.#*..*.###.#.##.##.#.#.#....#.#*.#",
 "*.#..#*#.#*#*....#.#.#..*#**...##.#.#.**#*##.*.#..",
 ".#*.##..##..##.#.#..#.#.###.###...#...#*#..##*#.#.",
 "#..#*.#..*.###..#.#...#.###.#.#*#.#.#**##.#...*.#*",
 "..#..#.#.##.#..#.**.##*#.#**.**..#.#..#...#.##*#..",
 ".#*#.#.*..#.*#...#.#...#...#.##.#..*#*.##*....###.",
 ".*.#.#.#.#*#..*##.**.##*##..#.*#.#*###..*.#.##.#..",
 ".#......#...#.#.*#.#.#..#..#.#*#....#*.#*#.*#..*.#",
 "#..####..#*#...#*.#..#.###...#.#.#.###*#..##*##.#.",
 ".#.*..#.#...#.#..#.##...#..#.#.#.#.###..##..*.*.*.",
 ".#.#.#.#..##.*..#.*.#.##.#..##*...#.#..#.#.##.#.##",
 ".#..#*.#.#..#.##..##..#.*..#.*#.#...##....#...###.",
 ".#.#.#.#*.#.#..#.#..#..#.#.*#...#.##...#.##.##.*..",
 ".#...#.#.##.#.#..*#.*#..###..#.#.#*###.##...#*.##.",
 ".#.##.*.......*.#.*#.#.#*###..*...*..#.*.##.#.#..#",
 "...###*####*#.#..##*...#..#..##.#.#.#..##*#*.*.*#.",
 "#.#.#....*#..#.#.#.#.##..#*.#...#..#.#*#...#.##.*.",
 "..*.#*##.#.#*#.###...#..##.#.#.#*###*#.*#.#.*###.#",
 "##*##..##...#.....##.#.#.**#..#*.....##.#..#*.#.*.",
 ".....#.*.##..##.##*.*#...#.#.#.##.#*#.**..#..#.#.#",
 "##.#.#*##.#.#.*.*.#.#*#.#.#....*...#*##*##.#....#.",
 "*.**#**....*..##.#*.*.**..##.###.##.....##...##.**",
 "#.####.##*#*##..#.*#*#.##*...#.##..#.##....#*..##.",
 "....#...##.#...#*.#..##.##.#*..*.#....##.#.*##...#",
 "#.#..*##*..#.#..#..#..#*....#.##..##.#*##.##.*##..",
 "..#.#*.*.##.#.#*#.#*##.###.##...#............#*.#.",
 "#.#.##.#....*....*..##..*#.#.#.###.#.#.#.###..#..#",
 ".#**..#*#.#*#*#.#.#...*##....##.#*..#..#*..*#..#..",
 "...#*#.....#..#.#..#*#.*##.#..#.#.##..#.*#*#.#...#",
 ".#*.###.#.#.#.#.*#*##.##..#.#*..#...#.#.#..#*.*#..",
 "#*.#.#.#..#..#..#....*#.*##..##.#.#..#...##.#.#..#",
 "*.#..#..#...#..##.#*#..#.#*#.#.#.###..#.#*...#.#..",
 "#...#.#...#.#.#..#.*.#*.....**.*..#*##.#*.##....##",
 "#*#....#*#..#.*.###*#..#*##.##.#.#...#.*.##.##.##.",
 "..##*##*..#*#.#..#*.*##*.##.#...#.#.#.#.#..*#.##..",
 "#...#*##.#*#**.##.*#.*.##..*.#*#**....#**##...*.*#",
 "*#.##......*#.##.#.#.##**.#.#.#.#.#.##..#...#*#*#*",
 "*....##.#.#..#.....#..##.#....*....#.#.##.#.#.##**",
 "#.##*#...#..#.#.##..#..##.##.##.##........##.#*#.#",
 "..#...#.#*#*..*#..*#.*#.#......##.#.#.#*#..#..****",
 ".###.#..#...#.#..#..#.#...#.#.#...**.#..*#*.*##*#."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 150; double Arg2 = 1309.4951033725558; verify_case(4, Arg2, expectedLength(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	Orienteering ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE

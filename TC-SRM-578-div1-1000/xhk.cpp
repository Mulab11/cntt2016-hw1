// BEGIN CUT HERE

// END CUT HERE
#line 5 "DeerInZooDivOne.cpp"
#include<bits/stdc++.h>
using namespace std;

const int inf=0x3f3f3f3f;

struct edge
{int u,v,next;
};
struct edge e[210];

int n,t,w,N,flag,num,col,ans;
int head[110],group[52],d[52],ga[52][52],f[52][52][52][52],usedx[52],usedy[52],matx[52],maty[52],pre[52],lx[52],ly[52],slack[52],q[10010];

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

int find(int i) //并查集 
{return group[i]==i?i:group[i]=find(group[i]);
}

void change(int i)
{int j,k;
 
 if(i==0) return;
 j=pre[i];
 k=matx[j];
 maty[i]=j;
 matx[j]=i;
 change(k);
}

void bfs()
{int i,j;
 
 while(t<=w)
 {	i=q[t];
 	for(j=1;j<=N;j++)
 	{	if(usedy[j]==col) continue;
 		if(ga[i][j]==lx[i]+ly[j])
 		{	pre[j]=i;
 			if(maty[j]==0)
 			{	change(j);
 				flag=1;
 				return;
 			}
 			else
 			{	usedy[j]=col;
 				usedx[maty[j]]=col;
 				q[++w]=maty[j];
 			}
 		}
 		else if(lx[i]+ly[j]-ga[i][j]<slack[j])
 		{	slack[j]=lx[i]+ly[j]-ga[i][j];
 			pre[j]=i;
 		}
 	}
 	t++;
 }
}

int km() //求二分图最大权匹配
{int i,j,s,ret=0;
 
 for(i=1;i<=N;i++) lx[i]=ly[i]=0;
 for(i=1;i<=N;i++)
 	for(j=1;j<=N;j++)
 		lx[i]=max(lx[i],ga[i][j]);
 memset(matx,0,sizeof(matx));
 memset(maty,0,sizeof(maty));
 for(i=1;i<=N;i++)
 {	col++;
 	memset(pre,0,sizeof(pre));
 	memset(slack,0x3f,sizeof(slack));
 	usedx[i]=col;
 	t=1;
 	w=1;
 	q[t]=i;
 	flag=0;
 	bfs();
 	while(!flag)
 	{	s=inf;
 		for(j=1;j<=N;j++)
 			if(usedy[j]!=col) s=min(s,slack[j]);
 		for(j=1;j<=N;j++)
 			if(usedx[j]==col) lx[j]-=s;
 		for(j=1;j<=N;j++)
 			if(usedy[j]==col)
 				ly[j]+=s;
 			else
 				slack[j]-=s;
 		for(j=1;j<=N;j++)
 		{	if(usedy[j]!=col && slack[j]==0)
			{	if(maty[j]==0)
				{	change(j);
					flag=1;
					break;
				}
				else
				{	usedy[j]=col;
					usedx[maty[j]]=col;
					q[++w]=maty[j];
				}
			}
			if(flag) break;
		}
		if(!flag) bfs();
	}
 }
 for(i=1;i<=N;i++) ret+=lx[i]+ly[i];
 /*
 for(i=1;i<=N;i++)
 {	for(j=1;j<=N;j++)
		cout<<ga[i][j]<<" ";
	cout<<endl;
 }
 cout<<ret<<endl;
 cout<<"----------------"<<endl;
 */
 return ret;
}

int ff;

int work(int x,int fx,int y,int fy)
{static vector<int> A,B;
 int i,j,j1;

 if(f[x][fx][y][fy]!=-1) return f[x][fx][y][fy];
 j=head[x];
 while(j!=-1) //把要用到的f[][][][]值先递归下去计算 
 {	if(e[j].v!=fx)
 	{	j1=head[y];
 		while(j1!=-1)
 		{	//cout<<y<<" "<<j1<<endl;
		 	assert(e[j1].v!=0);
		 	if(e[j1].v!=fy)
 				work(e[j].v,x,e[j1].v,y);
			j1=e[j1].next;
		}
	}
	j=e[j].next;
 }
 A.clear();
 B.clear();
 j=head[x];
 while(j!=-1)
 {	if(e[j].v!=fx) A.push_back(e[j].v);
 	j=e[j].next;
 }
 j=head[y];
 while(j!=-1)
 {	if(e[j].v!=fy) B.push_back(e[j].v);
 	j=e[j].next;
 }
 N=max(A.size(),B.size());
 memset(ga,0,sizeof(ga));
 for(i=1;i<=A.size();i++)
 	for(j=1;j<=B.size();j++)
 		ga[i][j]=f[A[i-1]][x][B[j-1]][y]; //建图 
 return f[x][fx][y][fy]=1+km(); //求f[][][][]的值 
}

int solve()
{int i,j,k1,k2,si,sj,ret=0;
 
 for(i=1;i<=n;i++)
 {	if(group[i]==2) continue;
 	k1=head[i];
 	while(1)
 	{	si=(k1!=-1?e[k1].v:0);
 		for(j=1;j<=n;j++)
 		{	if(group[j]==1) continue;
 			k2=head[j];
 			while(1)
 			{	sj=(k2!=-1?e[k2].v:0);
 				ret=max(ret,work(i,si,j,sj)); //计算f[i][si][j][sj]的答案 
 				if(k2==-1) break;
 				k2=e[k2].next;
 			}
 		}
 		if(k1==-1) break;
 		k1=e[k1].next;
 	}
 }
 return ret;
}

class DeerInZooDivOne
{	public:
	int getmax(vector <int> a, vector <int> b)
	{	int i,j,fx,fy;
		
		ans=0;
		n=a.size()+1;
		for(i=1;i<n;i++) //枚举断掉哪条边  
		{	num=0;
			memset(head,-1,sizeof(head));
			memset(d,0,sizeof(d));
			for(j=1;j<=n;j++) group[j]=j;
			for(j=1;j<n;j++)
			{	if(j==i) continue;
				add(a[j-1]+1,b[j-1]+1); //建图 
				d[a[j-1]+1]++;
				d[b[j-1]+1]++;
				fx=find(a[j-1]+1); //并查集求联通块  
				fy=find(b[j-1]+1);
				if(fx!=fy) group[fx]=fy;
			}
			for(j=1;j<=n;j++) group[j]=find(j);
			for(j=2;j<=n;j++)
				group[j]=group[j]==group[1]?1:2;
			group[1]=1;
			memset(f,-1,sizeof(f));
			ans=max(ans,solve()); //计算答案 
		}
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0, 1, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(0, Arg2, getmax(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1, 8, 1, 7, 4, 2, 5, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {5, 3, 6, 8, 2, 6, 8, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; verify_case(1, Arg2, getmax(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(2, Arg2, getmax(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {0, 11, 10, 10, 19, 17, 6, 17, 19, 10, 10, 11, 9, 9, 14, 2, 13, 11, 6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {7, 5, 2, 12, 8, 9, 16, 8, 4, 18, 8, 13, 15, 13, 17, 16, 3, 1, 7}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 8; verify_case(3, Arg2, getmax(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {14, 13, 28, 15, 20, 4, 9, 6, 1, 23, 19, 25, 25, 8, 14, 16, 2, 8, 15, 25, 22, 22, 28, 10, 10, 14, 24, 27, 8}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {21, 5, 12, 13, 27, 1, 24, 17, 27, 17, 23, 14, 18, 26, 7, 26, 11, 0, 25, 23, 3, 29, 22, 11, 22, 29, 15, 28, 29}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 11; verify_case(4, Arg2, getmax(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	DeerInZooDivOne ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE

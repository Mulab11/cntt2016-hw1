// BEGIN CUT HERE

// END CUT HERE
#line 5 "Incubator.cpp"
#include<bits/stdc++.h>
using namespace std;

struct edge
{int u,v,next;
};
struct edge e[100010];

int n,num,col,ans;
int head[110],mat[110],used[110],ga[110][110];

void add(int u,int v)
{e[num].u=u;
 e[num].v=v;
 e[num].next=head[u];
 head[u]=num;
 num++;
}

int dfs(int i) //二分图匹配 
{int j;
 
 j=head[i];
 while(j!=-1)
 {	if(used[e[j].v]!=col)
 	{	used[e[j].v]=col;
 		//cout<<i<<" "<<e[j].v<<endl;
		if(!mat[e[j].v] || dfs(mat[e[j].v]))
 		{	mat[e[j].v]=i;
 			return 1;
 		}
 	}
 	j=e[j].next;
 }
 return 0;
}

class Incubator
{	public:
	int maxMagicalGirls(vector <string> love)
	{	int i,j,k;
		
		n=love.size();
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
				ga[i][j]=(love[i-1][j-1]=='Y');
		for(k=1;k<=n;k++) //求传递闭包 
			for(i=1;i<=n;i++)
				for(j=1;j<=n;j++)
					ga[i][j]|=(ga[i][k] && ga[k][j]);
		num=0;
		memset(head,-1,sizeof(head));
		for(i=1;i<=n;i++) //连边 
			for(j=1;j<=n;j++)
				if(ga[i][j]) add(i,j);
		//cout<<ga[1][2]<<" "<<head[1]<<endl;		
		memset(mat,0,sizeof(mat));		
		ans=n;
		for(i=1;i<=n;i++) //求最大匹配 
		{	col++;
			ans-=dfs(i);
		}
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"NY","NN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, maxMagicalGirls(Arg0)); }
	void test_case_1() { string Arr0[] = {"NYN", "NNY", "NNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(1, Arg1, maxMagicalGirls(Arg0)); }
	void test_case_2() { string Arr0[] = {"NNYNN","NNYNN","NNNYY","NNNNN","NNNNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, maxMagicalGirls(Arg0)); }
	void test_case_3() { string Arr0[] = {"NNNNN","NYNNN","NYNYN","YNYNN","NNNNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(3, Arg1, maxMagicalGirls(Arg0)); }
	void test_case_4() { string Arr0[] = {"NNNNN","NNNNN","NNNNN","NNNNN","NNNNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(4, Arg1, maxMagicalGirls(Arg0)); }
	void test_case_5() { string Arr0[] = {"NNYNNNNN","NNNYNNNN","NNNNYNNN","NNYNNNNN","NNNNNYYN","NNNYNNNY","NNNNNNNN","NNNNNNNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(5, Arg1, maxMagicalGirls(Arg0)); }
	void test_case_6() { string Arr0[] = {"Y"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(6, Arg1, maxMagicalGirls(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	Incubator ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE

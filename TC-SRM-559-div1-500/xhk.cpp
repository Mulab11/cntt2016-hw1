// BEGIN CUT HERE

// END CUT HERE
#line 5 "HatRack.cpp"
#include<bits/stdc++.h>
using namespace std;

struct edge
{int u,v,next;
};
struct edge e[110];

struct unit
{int h1,h2,dd,size;
 long long s;
};
struct unit f[110];

int n,num;
int head[110],d[110];
long long ans;

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

void dfs(int i,int fa,int dep) //f[i].size表示子树大小,f[i].h1表示最大深度,f[i].h2表示最小深度 
{int j;
 vector<int> w;
 
 f[i].size=1;
 f[i].h1=-1;
 f[i].h2=n+1;
 f[i].dd=0;
 f[i].s=0;
 j=head[i];
 if(e[j].next==-1 && dep!=0) //判断是不是叶子 
 {	f[i].h1=f[i].h2=dep;
 	f[i].dd=0;
 	f[i].s=1;
 	return;
 }
 w.clear();
 while(j!=-1)
 {	if(e[j].v!=fa)
	{	dfs(e[j].v,i,dep+1); //递归 
		w.push_back(e[j].v);
		f[i].size+=f[e[j].v].size; //更新信息 
		f[i].dd+=f[e[j].v].dd;
		f[i].h1=max(f[i].h1,f[e[j].v].h1);
		f[i].h2=min(f[i].h2,f[e[j].v].h2);
	}
	j=e[j].next;
 }
 //cout<<"## "<<i<<" "<<w[0]<<" "<<w.size()<<endl;
 if(f[i].dd>1 || f[i].h1>f[i].h2+1) //判断是否无解 
 {	f[i].s=0;
 	return;
 }
 f[i].dd=(f[i].h1!=f[i].h2);
 if(w.size()>2) //判断是否无解 
 {	f[i].s=0;
 	return;
 } 
 if(w.size()==1) //考虑只有一个儿子的情况 
 {	//cout<<"## "<<i<<" "<<w[0]<<endl;
 	if(f[w[0]].size!=1)
 		return;
 	else
 	{	f[i].h2=f[i].h1-1;
 		f[i].dd=1;
		f[i].s=1;
	}
	return;
 }
 if(f[w[0]].size==f[w[1]].size) //判断两边是否相同，使得话可以交换 
 	f[i].s=2*f[w[0]].s*f[w[1]].s;
 else
 	f[i].s=f[w[0]].s*f[w[1]].s;
}

class HatRack
{	public:
	long long countWays(vector <int> knob1, vector <int> knob2)
	{	int i,j;
		
		n=knob1.size()+1;
		num=0;
		memset(head,-1,sizeof(head));
		memset(d,0,sizeof(d));
		for(i=1;i<n;i++)
		{	add(knob1[i-1],knob2[i-1]);
			d[knob1[i-1]]++;
			d[knob2[i-1]]++;
		}
		ans=0;
		for(i=1;i<=n;i++)
			if(d[i]==1 || d[i]==2) //枚举根 
			{	memset(f,0,sizeof(f));
				dfs(i,0,0);
				ans+=f[i].s;
				//cout<<i<<" "<<f[i].s<<endl;
			}
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 2LL; verify_case(0, Arg2, countWays(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 2LL; verify_case(1, Arg2, countWays(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {1,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,4,5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 0LL; verify_case(2, Arg2, countWays(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {6,6,6,4,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,4,5,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 0LL; verify_case(3, Arg2, countWays(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {1,1,2,2,11,11,8,8,3,3,4,4,5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,11,8,12,13,9,10,4,5,7,6,14}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 16LL; verify_case(4, Arg2, countWays(Arg0, Arg1)); }
	void test_case_5() { int Arr0[] = {1,2,3,4,5,6,7,8,9}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,4,5,6,7,8,9,10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 0LL; verify_case(5, Arg2, countWays(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	HatRack ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE

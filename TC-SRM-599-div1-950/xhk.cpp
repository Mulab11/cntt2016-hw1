// BEGIN CUT HERE

// END CUT HERE
#line 5 "SimilarNames.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int mod=1000000007;

struct edge
{int u,v,next;
};
struct edge e[110];

struct unit
{int x,y;
};
struct unit b[20];

vector<string> a;
int n,m,num,s,ans;
int head[60],pw[20],used[60],f[60][7010],g[7010];

void add(int u,int v)
{e[num].u=u;
 e[num].v=v;
 e[num].next=head[u];
 head[u]=num;
 num++;
}

int check(string &A,string &B)
{int i;
 
 if(A.length()>=B.length()) return 0;
 for(i=0;i<A.length();i++)
 	if(A[i]!=B[i]) return 0;
 return 1;
}

void dfs(int p,int i,int j,int k,int k1,int k2)
{int i1;

 if(p==m)
 {	g[k]=(g[k]+(ll)f[i][k1]*f[j][k2]%mod)%mod;
 	return;
 }
 dfs(p+1,i,j,k,k1,k2);
 dfs(p+1,i,j,k+pw[p],k1,k2+pw[p]);
 dfs(p+1,i,j,k+2*pw[p],k1,k2+2*pw[p]);
 dfs(p+1,i,j,k+pw[p],k1+pw[p],k2);
 dfs(p+1,i,j,k+2*pw[p],k1+2*pw[p],k2);
}

void calc(int j,int i)
{int k;
 //cout<<"## "<<j<<" "<<i<<endl;
 memset(g,0,sizeof(g));
 dfs(0,j,i,0,0,0);
 for(k=0;k<pw[m];k++)
 	f[i][k]=g[k];
}

void work(int i)
{int j,t,p,k,k1,flag;
 
 f[i][0]=1;
 j=head[i];
 while(j!=-1)
 {	work(e[j].v);
 	calc(e[j].v,i);
 	j=e[j].next;
 }
 if(i==1) return;
 //cout<<i<<" "<<f[i][0]<<endl;
 memset(g,0,sizeof(g));
 for(k=0;k<pw[m];k++)
 {	for(p=0;p<n;p++)
 	{	if(!used[p]) continue;
 		t=k;
 		k1=k;
 		flag=1;
 		//cout<<t<<endl;
 		for(j=0;j<m;j++)
 		{	if(t%3==1 && p==b[j].x)
 				k1+=pw[j];
 			else if(t%3==0 && p==b[j].y)
 				k1+=pw[j];
 			else if(t%3==2 && (p==b[j].x || p==b[j].y))
 				flag=0;
 			else if(t%3==0 && p==b[j].x)
			 	flag=0;
			else if(t%3==1 && p==b[j].y)
				flag=0;
			//cout<<t%3<<" "<<p<<" "<<b[j].x<<" "<<b[j].y<<" "<<flag<<endl;	
 			t/=3;
 		}
 		//cout<<i<<" "<<k<<" "<<p<<" "<<flag<<endl;
 		if(flag)
		 	g[k1]=(g[k1]+f[i][k])%mod;
	}
	g[k]=(g[k]+f[i][k])%mod;
 }
 for(k=0;k<pw[m];k++)
 	f[i][k]=g[k];
 //cout<<i<<" ^^ "<<f[i][0]<<" "<<f[i][1]<<" "<<f[i][2]<<endl;	
}

class SimilarNames
{	public:
	int count(vector <string> names, vector <int> info1, vector <int> info2)
	{	int i,j,k;
	
	 	n=names.size();
	 	m=info1.size();
	 	num=0;
	 	memset(head,-1,sizeof(head));
	 	pw[0]=1;
	 	for(i=1;i<=8;i++) pw[i]=pw[i-1]*3;
	 	for(i=0;i<n;i++)
	 	{	k=-1;
	 		for(j=0;j<n;j++)
	 			if(j!=i && check(names[j],names[i]) && (k==-1 || names[j].length()>names[k].length()))
	 				k=j;
	 		if(k!=-1)
			 	add(k+2,i+2);
			else
				add(1,i+2);		
	 	}
	 	memset(used,0,sizeof(used));
	 	for(i=0;i<m;i++)
	 	{	b[i]=(unit){info1[i],info2[i]};
	 		used[info1[i]]=1;
	 		used[info2[i]]=1;
	 	}
	 	s=0;
	 	for(i=0;i<n;i++) s+=1-used[i];
	 	memset(f,0,sizeof(f));
	 	/*
	 	for(i=0;i<num;i++)
	 		cout<<e[i].u<<" "<<e[i].v<<endl;
	 	*/
	 	work(1);
	 	ans=f[1][pw[m]-1];
	 	//cout<<s<<endl;
	 	for(i=2;i<=s;i++) ans=(ll)ans*i%mod;
		return ans;	
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"kenta", "kentaro", "ken"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 3; verify_case(0, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"hideo", "hideto", "hideki", "hide"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 6; verify_case(1, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"aya", "saku", "emi", "ayane", "sakura", "emika", "sakurako"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 1, 3, 5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 2, 4, 6}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; verify_case(2, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"taro", "jiro", "hanako"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 0; verify_case(3, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arr0[] = {"alice", "bob", "charlie"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 6; verify_case(4, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_5() { string Arr0[] = {"ryota", "ryohei", "ryotaro", "ryo", "ryoga", "ryoma", "ryoko", "ryosuke", "ciel", "lun",
 "ryuta", "ryuji", "ryuma", "ryujiro", "ryusuke", "ryutaro", "ryu", "ryuhei", "ryuichi", "evima"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {17, 5, 6, 13, 5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {9, 2, 14, 17, 14}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 994456648; verify_case(5, Arg3, count(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	SimilarNames ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE

// BEGIN CUT HERE

// END CUT HERE
#line 5 "ConversionMachine.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int mod=1000000007,maxn=12,N=2*maxn*maxn;

struct matrix
{int val[N+10][N+10];
};
struct matrix f,g,e;

int n;
long long lim;

int num(int x,int y)
{return x*maxn+y;
}

matrix operator *(const matrix &A,const matrix &B)
{int i,j,k;
 matrix ret;
 
 for(i=0;i<=N;i++)
 	for(j=0;j<=N;j++)
 		ret.val[i][j]=0;
 for(i=0;i<=N;i++)
 	for(j=0;j<=N;j++)
 	{	if(!A.val[i][j]) continue;
 		for(k=0;k<=N;k++)
 			ret.val[i][k]=(ret.val[i][k]+(ll)A.val[i][j]*B.val[j][k]%mod)%mod;
 	}
 return ret;
}

matrix fpow(matrix A,long long j)
{matrix ret=e;
 //cout<<j<<endl;
 for(;j;A=A*A,j/=2)
 	if(j&1) ret=ret*A;
 return ret;
}

class ConversionMachine
{	public:
	int countAll(string word1, string word2, vector <int> costs, int maxCost)
	{	int i,j,s1=0,s2=0,p;
		
		lim=maxCost;
		n=word1.size();
		for(i=1;i<=n;i++)
		{	if(word1[i-1]==word2[i-1]) continue;
			if((word1[i-1]+1-word2[i-1]+3)%3==0)
			{	s1++;
				if(word1[i-1]=='a')
					lim-=costs[0];
				else if(word1[i-1]=='b')
					lim-=costs[1];
				else
					lim-=costs[2];
			}
			else
			{	s2++;
				if(word1[i-1]=='a')
					lim-=costs[0]+costs[1];
				else if(word1[i-1]=='b')
					lim-=costs[1]+costs[2];
				else
					lim-=costs[2]+costs[0];
			}
			if(lim<0) return 0;
		}
		for(i=0;i<=N;i++)
			e.val[i][i]=1;
		memset(g.val,0,sizeof(g.val));
		for(i=0;i<=n;i++)
			for(j=0;j+i<=n;j++)
			{	p=num(i,j);
				g.val[p][num(i,j+1)]+=n-i-j;
				g.val[p][num(i-1,j)]+=i;
				g.val[p][num(i+1,j-1)]+=j;
				g.val[p][maxn*maxn+num(i,j+1)]+=n-i-j;
				g.val[p][maxn*maxn+num(i-1,j)]+=i;
				g.val[p][maxn*maxn+num(i+1,j-1)]+=j;
				g.val[maxn*maxn+p][maxn*maxn+p]=1;
			}
		/*	
		for(i=0;i<=10;i++)
		{	for(j=0;j<=10;j++)
				cout<<g.val[i][j]<<" ";
			cout<<endl;
		}
		*/
		//cout<<s1<<" "<<s2<<endl;
		//cout<<lim<<endl;	
		memset(f.val,0,sizeof(f.val));
		f.val[1][num(s1,s2)]=f.val[1][maxn*maxn+num(s1,s2)]=1;
		f=f*fpow(g,(ll)(lim/(costs[0]+costs[1]+costs[2]))*3+s1+2*s2);
		//cout<<f.val[1][maxn*maxn]<<endl;
		return f.val[1][maxn*maxn];
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "a"; string Arg1 = "b"; int Arr2[] = {100,2,3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 205; int Arg4 = 2; verify_case(0, Arg4, countAll(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { string Arg0 = "abcba"; string Arg1 = "abcba"; int Arr2[] = {67,23,43}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 0; int Arg4 = 1; verify_case(1, Arg4, countAll(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { string Arg0 = "cccccccc"; string Arg1 = "aaaaaaaa"; int Arr2[] = {10000000,1,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 100; int Arg4 = 40320; verify_case(2, Arg4, countAll(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { string Arg0 = "aa"; string Arg1 = "cc"; int Arr2[] = {1,10,100}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1787; int Arg4 = 123611681; verify_case(3, Arg4, countAll(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	ConversionMachine ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE

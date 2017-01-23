// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheBrickTowerHardDivOne.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
typedef vector<int> VI;
const int mod=1234567891;

struct matrix
{long long val[250][250];
};
struct matrix f,g,e;

int col,lim,N,cnt;
int b[20];
long long n,ans;
VI a,w;

map<VI,int> h;

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
 for(;j;A=A*A,j/=2)
 	if(j&1) ret=ret*A;
 return ret;
}

void update(long long &i,long long x)
{i=(i+x)-(i+x>=mod?mod:0);
}

int number(int x,int y,int z)
{return z*(lim+1)*cnt+y*cnt+x;
}

void dfs0(int i,int k)
{int j,s=0;
 
 if(i==5)
 {	//cout<<"^^^^^^^^ "<<cnt<<endl;
 	h[a]=++cnt;
 	return;
 }
 for(j=1;j<=k+1;j++)
 {	a.push_back(j);
 	dfs0(i+1,max(j,k));
 	a.pop_back();
 }
}

void dfs(int i,int k,long long ways)
{int j,s,p,p1,p2,flag,tot;
 
 if(i==9)
 {	s=0;
 	for(j=1;j<=4;j++)
 		s+=(b[j]==b[j+4]);
 	s+=(b[5]==b[6])+(b[5]==b[7])+(b[6]==b[8])+(b[7]==b[8]);
 	tot=0;
 	w.clear();
 	for(j=1;j<=4;j++) w.push_back(b[j]);
 	p1=h[w];
 	w.clear();
 	for(j=5;j<=8;j++)
 	{	flag=0;
 		for(p=5;p<j;p++)
 			if(b[p]==b[j])
 			{	flag=p;
 				break;
 			}
 		if(flag)
		 	w.push_back(w[flag-5]);
 		else
 			w.push_back(++tot);
 	}
 	p2=h[w];
 	for(j=0;j+s<=lim;j++)
 	{	update(g.val[number(p1,j,0)][number(p2,j+s,0)],ways);
 		update(g.val[number(p1,j,0)][number(p2,j+s,1)],ways);
 	}
 	return;
 }
 for(j=1;j<=k;j++)
 {	b[i]=j;
 	dfs(i+1,k,ways);
 }
 b[i]=k+1;
 dfs(i+1,k+1,(ll)ways*(i>4?col-k:1)%mod);
}

class TheBrickTowerHardDivOne
{	public:
	int find(int C, int K, long long H)
	{	int i,j,s,k;
		long long s1;
		map<VI,int>::iterator p;
	
		col=C;
		lim=K;
		n=H;
		cnt=0;
		h.clear();
		a.clear();
		dfs0(1,0);
		memset(g.val,0,sizeof(g.val));
		dfs(1,0,1);
		for(i=1;i<=cnt;i++)
			for(j=0;j<=lim;j++)
				update(g.val[number(i,j,1)][number(i,j,1)],1);
		memset(f.val,0,sizeof(f.val));
		for(p=h.begin();p!=h.end();p++)
		{	a=(*p).first;
			s=(a[0]==a[1])+(a[0]==a[2])+(a[1]==a[3])+(a[2]==a[3]);
			k=0;
			for(i=0;i<4;i++)
			{	k++;
				for(j=0;j<i;j++)
					if(a[i]==a[j])
					{	k--;
						break;
					}
			}
			s1=1;
			for(i=0;i<k;i++)
				s1=s1*(col-i)%mod;
			//for(i=0;i<4;i++) cout<<a[i]<<" ";
			//cout<<endl;
			//cout<<(*p).second<<" "<<s<<" "<<s1<<endl;	
			//cout<<"---------------"<<endl;
			if(s<=lim)
 			{	update(f.val[1][number((*p).second,s,0)],s1);
 				update(f.val[1][number((*p).second,s,1)],s1);
 			}
 		}
 		N=2*cnt*(lim+1);
 		for(i=1;i<=N;i++) e.val[i][i]=1;
 		
 		//cout<<cnt<<endl;
		//for(i=1;i<=N;i++)
		//	cout<<"## "<<i<<" "<<f.val[1][i]<<endl; 
		 
		f=f*fpow(g,n-1);
 		ans=0;
 		for(i=1;i<=cnt;i++)
 			for(j=0;j<=lim;j++)
 				update(ans,f.val[1][number(i,j,1)]);
 		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 0; long long Arg2 = 2LL; int Arg3 = 4; verify_case(0, Arg3, find(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 1; int Arg1 = 7; long long Arg2 = 19LL; int Arg3 = 1; verify_case(1, Arg3, find(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 2; int Arg1 = 3; long long Arg2 = 1LL; int Arg3 = 14; verify_case(2, Arg3, find(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 4; int Arg1 = 7; long long Arg2 = 47LL; int Arg3 = 1008981254; verify_case(3, Arg3, find(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	TheBrickTowerHardDivOne ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE

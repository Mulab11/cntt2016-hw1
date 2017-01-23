// BEGIN CUT HERE

// END CUT HERE
#line 5 "CharacterBoard.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int mod=1000000009;
int n,m,w,tot,ans;
int b[5000010];
char a[110][110];
map<int,int> h,s;
map<long long,int> used;

int fpow(int i,int j)
{int ret=1;
 for(;j;i=(ll)i*i%mod,j/=2)
 	if(j&1) ret=(ll)ret*i%mod;
 return ret;
}

void work(int l) //判断l是否合法 
{int i,j,k,cnt;
 //return;
 cnt=0;
 s.clear();
 for(i=0;i<n;i++)
	for(j=0;j<m;j++)
	{	k=((ll)i*w+j)%l;
		if(s[k])
		{	if(s[k]!=a[i][j])
				return;
		}
		else
		{	s[k]=a[i][j];
			cnt++;
		}
	}
 ans=(ans+fpow(26,l-cnt))%mod;
}		
	
void calc(int l,int r) //等比数列求和 
{int s1,s2;
 if(l>r) return;
 //if(l<=0 || r<=0) cout<<l<<" "<<r<<endl;
 s1=(ll)(fpow(26,r+1)+mod-1)*fpow(25,mod-2)%mod;
 s2=(ll)(fpow(26,l)+mod-1)*fpow(25,mod-2)%mod;
 ans=(ans+(s1+mod-s2)%mod)%mod;
}
	
class CharacterBoard
{	public:
	int countGenerators(vector <string> fragment, int W, int i0, int j0)
	{	int i,j,i1,j1;
		long long t,k;
		
		n=fragment.size();
		m=fragment[0].length();
		w=W;
		for(i=0;i<n;i++)
			for(j=0;j<m;j++)
				a[i][j]=fragment[i][j];
		//cout<<n<<" "<<m<<endl;		
		ans=0;		
		tot=0;
		h.clear();
		used.clear();
		for(i=0;i<n;i++)
			for(j=0;j<m;j++)
				for(i1=0;i1<n;i1++)
					for(j1=0;j1<m;j1++) //找出有两个格子模l相同的l 
					{	if(i1==i && j1==j) continue;
						//cout<<i<<" "<<j<<" "<<i1<<" "<<j1<<endl;
						t=(ll)i1*w+j1-(ll)i*w-j;
						if(t<0) t=-t;
						if(used[t]) continue;
						used[t]=1;
						//cout<<t<<endl;
						//if(t%99==0) cout<<t<<endl;//cout<<i<<" "<<j<<" "<<i1<<" "<<j1<<endl;
						for(k=1;(ll)k*k<=t;k++)
							if(t%k==0)
							{	//continue;
								//if(k==99 || t/k==99) cout<<"$$ "<<endl;
								if(k<=(ll)w && h[k]==0)
								{	h[k]=1;
									b[++tot]=k;
									work(k);
								}
								if((ll)k*k!=t && t/k<=(ll)w && h[t/k]==0)
								{	h[t/k]=1;
									b[++tot]=t/k;
									work(t/k);
								}
							}
					}			
		//cout<<"$$"<<endl;			
		sort(b+1,b+tot+1);
		//cout<<endl;
		//for(i=1;i<=tot;i++) cout<<b[i]<<" ";
		//cout<<endl;
		//cout<<tot<<endl;
		//cout<<n<<" "<<m<<endl;
		calc(1-n*m,b[1]-1-n*m);
		for(i=1;i<tot;i++)
			calc(b[i]+1-n*m,b[i+1]-1-n*m);
		calc(b[tot]+1-n*m,w-n*m);
		return ans;				
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"aaaaaaaaaa", "aaaaaaaaaa", "aaaaaaaaaa", "aaaaaaaaaa", "aaaaaaaaaa", "aaaaaaaaaa", "aaaaaaaaaa", "aaaaaaaaaa", "aaaaaaaaaa", "aaaaaaaaaa"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1000000000; int Arg2 = 1; int Arg3 = 1; int Arg4 = 471477008; verify_case(0, Arg4, countGenerators(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { string Arr0[] = {"xyxxy"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; int Arg2 = 1; int Arg3 = 0; int Arg4 = 28; verify_case(1, Arg4, countGenerators(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { string Arr0[] = {"gogogo",
 "jijiji",
 "rarara"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; int Arg2 = 0; int Arg3 = 0; int Arg4 = 0; verify_case(2, Arg4, countGenerators(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { string Arr0[] = {"abababacac",
 "aaacacacbb",
 "ccabababab"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8827; int Arg2 = 104; int Arg3 = 6022; int Arg4 = 829146844; verify_case(3, Arg4, countGenerators(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	CharacterBoard ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE

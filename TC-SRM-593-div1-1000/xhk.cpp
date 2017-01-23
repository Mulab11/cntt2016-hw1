// BEGIN CUT HERE

// END CUT HERE
#line 5 "WolfDelaymasterHard.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int mod=1000000007;
int n;
int f[2000010],g[2000010],s[2000010],nextw[2000010],nexto[2000010],prew[2000010],preo[2000010];
char a[2000010];

void update(int &i,int x)
{i=(i+x)%mod;
}

class WolfDelaymasterHard
{	public:
	int countWords(int N, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd)
	{	int i,j,k,p,p1,l,r,x;
		
		n=N;
		for(i=1;i<=n;i++) a[i]='?';
		x = w0;
		for(i=0;i<wlen;i++)
		{	a[x+1] = 'w';	
			x = ((ll)x * wmul + wadd) % N;
		}
		x = o0;
		for(i=0;i<olen;i++)
		{	a[x+1] = 'o';
			x = ((ll)x * omul + oadd) % N;
		}
		
		//for(i=1;i<=n;i++) cout<<a[i];
		//cout<<endl;
		
		nextw[n]=nexto[n]=n+1;
		for(i=n-1;i>=0;i--)
		{	nextw[i]=nextw[i+1];
			nexto[i]=nexto[i+1];
			if(a[i+1]=='w')
				nextw[i]=i+1;
			else if(a[i+1]=='o')
				nexto[i]=i+1;
		}
		prew[1]=preo[1]=0;
		for(i=2;i<=n+1;i++)
		{	prew[i]=prew[i-1];
			preo[i]=preo[i-1];
			if(a[i-1]=='w')
				prew[i]=i-1;
			else if(a[i-1]=='o')
				preo[i]=i-1;
		}
		memset(f,0,sizeof(f));
		memset(s,0,sizeof(s));
		memset(g,0,sizeof(g));
		for(i=0;i<=n;i++)
		{	update(s[i],(i>=2)?s[i-2]:0);
			if(i==0)
				f[i]=1;
			else
			{	f[i]=s[i];
				j=prew[i+1];
				k=preo[i+1];
				p=preo[j];
				p1=nexto[j];
				l=max(p,i-(i-j)*2);
				if(k>j && p1!=n+1)
					r=min(j-1,i-(i-p1+1)*2);
				else
					r=j-1;
				if(r>=0)
				{	l=max(l,0);
					if(l%2!=i%2) l++;
					if(r%2!=i%2) r--;
					if(l<=r) update(f[i],(g[r]-(l-2>=0?g[l-2]:0)+mod)%mod);	
				}
			}
			g[i]=(i>=2)?g[i-2]:0;
			update(g[i],f[i]);
			j=nextw[i];
			k=nexto[i];
			if(j<k)
				p=j-1;
			else
				p=min(i+(k-i-1)*2,j-1);
			while(p%2!=i%2) p--;
			if(p>i)
			{	update(s[i+2],f[i]);
				update(s[p+2],mod-f[i]);
			}
		}
		return f[n];		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 8; int Arg1 = 5; int Arg2 = 2; int Arg3 = 3; int Arg4 = 2; int Arg5 = 0; int Arg6 = 6; int Arg7 = 7; int Arg8 = 1; int Arg9 = 6; verify_case(0, Arg9, countWords(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
	void test_case_1() { int Arg0 = 20; int Arg1 = 19; int Arg2 = 12; int Arg3 = 9; int Arg4 = 15; int Arg5 = 1; int Arg6 = 8; int Arg7 = 11; int Arg8 = 1; int Arg9 = 26; verify_case(1, Arg9, countWords(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
	void test_case_2() { int Arg0 = 40; int Arg1 = 24; int Arg2 = 34; int Arg3 = 5; int Arg4 = 11; int Arg5 = 33; int Arg6 = 35; int Arg7 = 23; int Arg8 = 27; int Arg9 = 296; verify_case(2, Arg9, countWords(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
	void test_case_3() { int Arg0 = 60; int Arg1 = 35; int Arg2 = 8; int Arg3 = 55; int Arg4 = 3; int Arg5 = 11; int Arg6 = 20; int Arg7 = 9; int Arg8 = 29; int Arg9 = 10058904; verify_case(3, Arg9, countWords(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
	void test_case_4() { int Arg0 = 2000; int Arg1 = 183; int Arg2 = 994; int Arg3 = 862; int Arg4 = 468; int Arg5 = 148; int Arg6 = 433; int Arg7 = 1247; int Arg8 = 1989; int Arg9 = 532199331; verify_case(4, Arg9, countWords(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
	void test_case_5() { int Arg0 = 2000000; int Arg1 = 419443; int Arg2 = 1305303; int Arg3 = 1761823; int Arg4 = 1007025; int Arg5 = 874640; int Arg6 = 1516339; int Arg7 = 229519; int Arg8 = 1473199; int Arg9 = 861766906; verify_case(5, Arg9, countWords(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
	void test_case_6() { int Arg0 = 8; int Arg1 = 6; int Arg2 = 0; int Arg3 = 1; int Arg4 = 1; int Arg5 = 3; int Arg6 = 3; int Arg7 = 6; int Arg8 = 1; int Arg9 = 0; verify_case(6, Arg9, countWords(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	WolfDelaymasterHard ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE

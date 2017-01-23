// BEGIN CUT HERE

// END CUT HERE
#line 5 "EqualSums.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int inf=1e9,mod=1000000007;

struct unit
{int A,B;
};
struct unit f[110];

int n,m,flag,val,col,ans;
int a[110][110],used[110];

void calc(unit w1,unit w2)
{int x;
 
 //cout<<"## "<<flag<<" "<<w1.A<<" "<<w1.B<<" "<<w2.A<<" "<<w2.B<<endl;
 
 if(w1.A!=w2.A || w1.B!=w2.B)
 {	if(w1.A==w2.A)
 		flag=0;
	else if((w1.B-w2.B)%(w2.A-w1.A)!=0)
		flag=0;
	else
	{	x=(w1.B-w2.B)/(w2.A-w1.A);
		if(val!=-1 && x!=val)
			flag=0;
		else
			val=x;
	}
 }
 //cout<<flag<<endl;
}

void dfs(int p)
{int i,j;
 unit w;
 
 used[p]=col;
 if(p<=n)
 {	for(j=1;j<=n;j++)
 	{	if(a[p][j]==-1) continue;
	 	w=(unit){-f[p].A,a[p][j]-f[p].B};
	 	if(!used[n+j])
 		{	f[n+j]=w;
 			dfs(n+j);
 		}
 		else 
		 	calc(w,f[n+j]);
	}
 }
 else
 {	for(i=1;i<=n;i++)
 	{	if(a[i][p-n]==-1) continue;
 		w=(unit){-f[p].A,a[i][p-n]-f[p].B};
 		if(!used[i])
 		{	f[i]=w;
 			dfs(i);
 		}
 		else
 			calc(w,f[i]);
 	}
 }
}

int solve(int lim)
{int i,j,L,R,s,ret=1;
 
 memset(used,0,sizeof(used));
 memset(f,0,sizeof(f));
 col=0;
 for(i=1;i<=n;i++)
 {	if(used[i]) continue;
 	col++;
 	f[i].A=1;
 	f[i].B=0;
 	flag=1;
 	val=-1;
 	dfs(i);
 	//cout<<i<<" "<<flag<<endl;
 	if(flag==0) return 0;
 	if(val!=-1)
 	{	for(j=1;j<=2*n;j++)
 			if(used[j]==col && f[j].A*val+f[j].B<(j<=n?lim:0))
 			{	flag=0;
 				break;
 			}
 		if(!flag) return 0;
 	}
 	else
 	{	L=0;
 		R=inf;
 		for(j=1;j<=2*n;j++)
 		{	if(used[j]!=col) continue;
 			if(f[j].A==0)
 			{	if(f[j].B<(j<=n?lim:0))
			 		return 0;
 			}
 			else if(f[j].A>0)
 			{	s=(j<=n?lim:0);
 				if(s-f[j].B>0)
 					L=max(L,(s-f[j].B-1)/f[j].A+1);
 			}
 			else
 			{	//cout<<"%%% "<<f[j].A<<" "<<f[j].B<<endl;
			 	s=(j<=n?lim:0);
 				if(s-f[j].B<=0)
 					R=min(R,(f[j].B-s)/(-f[j].A));
 				else
 					return 0;
 			}
 		}
 		if(L>R) return 0;
 		//cout<<i<<" "<<L<<" "<<R<<endl;
 		ret=(ll)ret*(R-L+1)%mod;
 	}
 }
 //cout<<ret<<endl;
 return ret;
}

class EqualSums
{	public:
	int count(vector <string> board)
	{	int i,j;
	
		n=board.size();
		memset(a,0,sizeof(a));
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
				if(board[i-1][j-1]!='-')
					a[i][j]=board[i-1][j-1]-48;
				else
					a[i][j]=-1;
		/*	
		for(i=1;i<=n;i++)
		{	for(j=1;j<=n;j++)
				cout<<a[i][j]<<" ";
			cout<<endl;
		}
		*/			
		ans=(solve(0)+mod-solve(1))%mod;
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"1-",
 "-2"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(0, Arg1, count(Arg0)); }
	void test_case_1() { string Arr0[] = {"123",
 "4--",
 "--9"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(1, Arg1, count(Arg0)); }
	void test_case_2() { string Arr0[] = {"9--",
 "-9-",
 "--9"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 271; verify_case(2, Arg1, count(Arg0)); }
	void test_case_3() { string Arr0[] = {"11",
 "12"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(3, Arg1, count(Arg0)); }
	void test_case_4() { string Arr0[] = {"-4--",
 "-0-2",
 "--1-",
 "4---"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; verify_case(4, Arg1, count(Arg0)); }
	void test_case_5() { string Arr0[] = {"--2",
 "02-",
 "-10"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(5, Arg1, count(Arg0)); }
	void test_case_6() { string Arr0[] = {"----------1---------------0-----7-----------------",
 "-----4--------------------------------------------",
 "--------5-------------5-3---5---------------6-----",
 "-------2----------1-------------------------------",
 "-----4--------------------------------------------",
 "-----3--------------------------------------------",
 "-6----------5-------------------------------------",
 "-------------------------------7---5----------6---",
 "--------6-------------6-4---6---------------7-----",
 "-------------4----------------5-------------------",
 "3------------------------------------------6------",
 "3------------------------------------------6------",
 "-------------4----------------5-------------------",
 "---------------2-------------------------3--------",
 "--2------------------------------------------2----",
 "---8---------------1-------------------3----------",
 "---------------3----------------------------------",
 "----7----------------5---0-----------------------5",
 "----------------5-------------------------3-----1-",
 "----------1---------------0-----7-----------------",
 "-------------5----------------6-------------------",
 "-7----------6-------------------------------------",
 "---8---------------1-------------------3----------",
 "-----------------------3--------------------------",
 "----8----------------6---1-----------------------6",
 "------------------------------------------4-----2-",
 "-----------5---------------5----------------------",
 "-----------------------------6--------------------",
 "----8----------------6---1-----------------------6",
 "----------------5-------------------------3-----1-",
 "-------------------------------6---4--2-------5---",
 "-6----------5-------------------------------------",
 "--------5-------------5-3---5---------------6-----",
 "-------------5----------------6-------------------",
 "-----3--------------------------------------------",
 "---------------2-------------------------3--------",
 "---------4---------------------------6------------",
 "-------------------------------6---4--2-------5---",
 "------2-------------1------------22---------------",
 "--------5-------------5-3---5---------------6-----",
 "-----------5--3------------5----------------------",
 "--2------------------------------------------2----",
 "---------5---------------------------7------------",
 "-------------4----------------5-------------------",
 "-----------------5------------------4---6------2--",
 "-------------------------------6---4--2-------5---",
 "-----------------------2--------------------------",
 "----------------6-------------------------4-----2-", 
 "-------------------------------6---4--2-------5---",
 "--------5-------------5-3---5---------------6-----"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 45094393; verify_case(6, Arg1, count(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	EqualSums ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE

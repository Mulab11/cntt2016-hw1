// BEGIN CUT HERE

// END CUT HERE
#line 5 "TravellingPurchasingMan.cpp"
#include<bits/stdc++.h>
using namespace std;

const int inf=0x3f3f3f3f;

struct unit
{int l,r,x;
};
struct unit a[110];

int n,m,ans;
int ga[110][110],cnt[70010],f[51][70010];
vector<int> w;

void update(int &i,int x)
{i=min(i,x);
}

class TravellingPurchasingMan
{	public:
	int maxStores(int N, vector <string> A, vector <string> roads)
	{	int i,j,k,s,x,y,z;
		
		n=N;
		m=A.size();
		for(i=0;i<A.size();i++) //分离数字			 
		{	w.clear();
			s=0;
			for(j=0;j<A[i].length();j++)
				if(A[i][j]==' ')
				{	w.push_back(s);
					s=0;
				}
				else
					s=s*10+A[i][j]-48;
			a[i+1].l=w[0];
			a[i+1].r=w[1];
			a[i+1].x=s;
		}
		memset(ga,0x3f,sizeof(ga));
		for(i=0;i<roads.size();i++) //分离数字
		{	w.clear();
			s=0;
			for(j=0;j<roads[i].length();j++)
				if(roads[i][j]==' ')
				{	w.push_back(s);
					s=0;
				}
				else
					s=s*10+roads[i][j]-48;		
			x=w[0]+1;
			y=w[1]+1;
			z=s;
			ga[x][y]=min(ga[x][y],z);
			ga[y][x]=min(ga[y][x],z);
			//cout<<x<<" "<<y<<" "<<ga[x][y]<<endl;
		}
		for(i=1;i<=n;i++) ga[i][i]=0;
		for(k=1;k<=n;k++) //floyd求最短路 
			for(i=1;i<=n;i++)
				for(j=1;j<=n;j++)
					ga[i][j]=min(ga[i][j],ga[i][k]+ga[k][j]);
		memset(f,0x3f,sizeof(f));
		for(i=1;i<(1<<m);i++) cnt[i]=cnt[i-(i&(-i))]+1;
		
		ans=0;
		f[n][0]=0;
		for(i=0;i<(1<<m);i++)
			for(j=1;j<=n;j++) //状压dp,f[j][i]表示当前在j已买了i集合的东西 
			{	if(f[j][i]==inf) continue;
				ans=max(ans,cnt[i]);
				for(k=1;k<=m;k++)
				{	if(i&(1<<(k-1))) continue;
					x=max(a[k].l,f[j][i]+ga[j][k]);
					if(x<=a[k].r)
						update(f[k][i|(1<<(k-1))],x+a[k].x); //下一次取k 
				}
			}
		return ans;	
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; string Arr1[] = {"1 10 10" , "1 55 31", "10 50 100" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"1 2 10"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1; verify_case(0, Arg3, maxStores(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 3; string Arr1[] = {"1 10 10" , "1 55 30", "10 50 100" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"1 2 10"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; verify_case(1, Arg3, maxStores(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 5; string Arr1[] = {"0 1000 17"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"2 3 400", "4 1 500", "4 3 300", "1 0 700", "0 2 400"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 0; verify_case(2, Arg3, maxStores(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	TravellingPurchasingMan ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE

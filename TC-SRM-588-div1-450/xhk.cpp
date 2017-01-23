// BEGIN CUT HERE

// END CUT HERE
#line 5 "KeyDungeonDiv1.cpp"
#include<bits/stdc++.h>
using namespace std;

struct unit
{int x,y,z;
};
struct unit a[20],b[20];

int n,ans;
int f[5010][410];

void update(int &i,int x)
{if(x>i) i=x;
}

class KeyDungeonDiv1
{	public:
	int maxKeys(vector <int> doorR, vector <int> doorG, vector <int> roomR, vector <int> roomG, vector <int> roomW, vector <int> keys)
	{	int i,j,k,x,y,z,nx,ny,nz,s;
		
		n=doorR.size();
		for(i=1;i<=n;i++)
		{	a[i].x=doorR[i-1];
			a[i].y=doorG[i-1];
		}
		for(i=1;i<=n;i++)
		{	b[i].x=roomR[i-1];
			b[i].y=roomG[i-1];
			b[i].z=roomW[i-1];
		}
		memset(f,-1,sizeof(f));
		f[0][keys[0]]=keys[2];
		ans=0;
		for(i=0;i<(1<<n);i++)
			for(j=0;j<=3*n*10;j++) //f[i][j]表示开i集合的门之后手上有j把R钥匙是最多有几把W钥匙，因为开的门固定，R,W固定就能算出G来 
			{	if(f[i][j]==-1) continue;
				s=keys[0]+keys[1]+keys[2];
				for(k=1;k<=n;k++)
					if(i&(1<<(k-1))) s+=b[k].x+b[k].y+b[k].z-a[k].x-a[k].y;
				ans=max(ans,s);	
				z=f[i][j]; //x,y,z表示当前R,G,B数量 
				y=s-j-z;
				x=j;
				for(k=1;k<=n;k++) //枚举下一个开哪扇门 
					if(!(i&(1<<(k-1))))
					{	if(z>=max(a[k].x-x,0)+max(a[k].y-y,0))
						{	nx=max(0,x-a[k].x)+b[k].x;
							ny=max(0,y-a[k].y)+b[k].y;
							nz=s+b[k].x+b[k].y+b[k].z-a[k].x-a[k].y-nx-ny;
							update(f[i|(1<<(k-1))][nx],nz);
						}
					}
			}	
		return ans;	
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1, 2, 3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 4, 9}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0, 0, 10}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {0, 8, 9}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {1, 0, 8}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {3, 1, 2}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arg6 = 8; verify_case(0, Arg6, maxKeys(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_1() { int Arr0[] = {1, 1, 1, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 2, 3, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2, 1, 0, 4}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1, 3, 3, 1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {1, 0, 2, 1}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {0, 4, 0}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arg6 = 4; verify_case(1, Arg6, maxKeys(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_2() { int Arr0[] = {2, 0, 4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3, 0, 4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0, 0, 9}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {0, 0, 9}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {8, 5, 9}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {0, 0, 0}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arg6 = 27; verify_case(2, Arg6, maxKeys(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_3() { int Arr0[] = {5, 3, 0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 1, 2, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0, 9, 2, 4}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {2, 9, 2, 0}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {0, 9, 1, 1}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {1, 1, 0}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arg6 = 32; verify_case(3, Arg6, maxKeys(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_4() { int Arr0[] = {9,5,10,8,4,3,0,8,4,1,3,9}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {9,10,0,8,9,4,3,8,1,8,10,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,2,0,2,3,3,5,3,1,3,0,5}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {5,2,5,0,5,2,3,4,0,0,5,2}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {1,5,1,2,0,4,4,0,3,3,1,3}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {5,0,1}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arg6 = 16; verify_case(4, Arg6, maxKeys(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	KeyDungeonDiv1 ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE

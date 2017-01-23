// BEGIN CUT HERE

// END CUT HERE
#line 5 "SemiPerfectPower.cpp"
#include<bits/stdc++.h>
using namespace std;

//首先次数只能为2或3,用x=a*b^2,加上x=b*y^3但不能表示成平方的就是答案 

#define ll long long
const int maxn=500000;
int tot;
int prime[maxn+10],u[maxn+10],miu[maxn+10];
long long ans;
vector<int> a[20010];

void prework() //预处理miu以及a数组a[d]里面是所有1~maxn内为d的倍数x=i*d且 p2(d)=1的前缀和 
{int i,j;
 
 miu[1]=1;
 for(i=2;i<=maxn;i++)
 {	if(!u[i])
 	{	miu[i]=-1;
 		prime[++tot]=i;
 	}
 	for(j=1;j<=tot;j++)
 	{	if(i*prime[j]>maxn) break;
 		u[i*prime[j]]=1;
 		if(i%prime[j]==0)
 		{	miu[i*prime[j]]=0;
 			break;
 		}
 		miu[i*prime[j]]=-miu[i];
 	}
 }
 //int s=0;
 for(i=1;i<=20000;i++)
 {	a[i].push_back(0);
 	for(j=1;j*i<=maxn;j++)
 		a[i].push_back(a[i].back()+(miu[j*i]!=0));
 	//s+=a[i].size();	
 }
 //cout<<s<<endl;
}

long long sqr3(int x){return (ll)x*x*x;}
long long sqr4(int x){return (ll)x*x*x*x;}
int gcd(int x,int y){return !y?x:gcd(y,x%y);}

int check3(int x) //判断有没有三次因子 
{int i;
 
 for(i=2;sqr3(i)<=x;i++)
 	if(x%sqr3(i)==0) return 0;
 return 1;
}

int sqrt3(long long x) //求立方根 
{int l,r,mid,ret;
 
 ret=0;
 l=1;
 r=maxn;
 while(l<=r)
 {	mid=(l+r)/2;
 	if(sqr3(mid)<=x)
 	{	ret=max(ret,mid);
 		l=mid+1;
 	}
 	else
 		r=mid-1;
 }
 return ret;
}

int calc(int l,int r,int d)
{if(l>r) return 0;
 
 //cout<<l<<" "<<r<<" "<<d<<" "<<a[d].size()<<endl;
 //if(d>20000) cout<<d<<endl;
 
 l=(l-1)/d;
 r/=d;
 return a[d][r]-a[d][l];
}

long long solve(long long N)
{int i,j,b,k,l,r,d,b1,k1,m;
 long long ret=0;
 //cout<<N<<endl;
 for(i=1;sqr3(i)<=N;i++) 
 {	if(miu[i]==0) continue;
 	k=floor(sqrt(N/i));
 	while((ll)(k+1)*(k+1)<=N/i) k++;
 	while((ll)k*k>N/i) k--;
 	//if(i<=10) cout<<N/i<<" "<<i<<" "<<k<<endl;
 	if(k>i) ret+=k-i;
 }	
 
 //cout<<ret<<endl;
 
 for(b=1;sqr4(b)<=N;b++) //枚举b 
 {	if(!check3(b)) continue;
 	//cout<<b<<endl;
 	for(k=1;sqr3(k)<=b;k++)
 	{	m=gcd(k*k,b);
 		b1=b/m;
 		k1=k*k/m;
 		if(miu[b1]==0) continue;
 		//cout<<b<<" "<<k<<endl;
 		for(d=1;d*d<=b1;d++)
 		{	if(b1%d!=0) continue;
 			//cout<<k1<<endl;
 			l=b/k1+1;
 			r=sqrt3(N/b)/k1; //把y表示成a*k1，a的范围是[l,r] 
 			
 			//cout<<b<<" "<<k<<" "<<d<<endl;
 			//continue;
 			ret+=miu[d]*calc(l,r,d);
			if(d*d!=b1) ret+=miu[b1/d]*calc(l,r,b1/d);
		}
	}
 }
 return ret;
}

class SemiPerfectPower
{	public:
	long long count(long long L, long long R)
	{	int i,j;
		
		prework();
		
		//cout<<solve(80000000000000000)-solve(80000000000000000-1)<<endl;
		//cout<<solve(10000000000)-solve(10000000000-1)<<endl;
		//return 0;
		
		ans=solve(R)-solve(L-1); //求前缀和 
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 18LL; long long Arg1 = 58LL; long long Arg2 = 9LL; verify_case(0, Arg2, count(Arg0, Arg1)); }
	void test_case_1() { long long Arg0 = 1LL; long long Arg1 = 10LL; long long Arg2 = 3LL; verify_case(1, Arg2, count(Arg0, Arg1)); }
	void test_case_2() { long long Arg0 = 60LL; long long Arg1 = 70LL; long long Arg2 = 1LL; verify_case(2, Arg2, count(Arg0, Arg1)); }
	void test_case_3() { long long Arg0 = 319268319114310LL; long long Arg1 = 35860463407469139LL; long long Arg2 = 95023825161LL; verify_case(3, Arg2, count(Arg0, Arg1)); }
	void test_case_4() { long long Arg0 = 1LL; long long Arg1 = 80000000000000000LL; long long Arg2 = 169502909978LL; verify_case(4, Arg2, count(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	SemiPerfectPower ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE

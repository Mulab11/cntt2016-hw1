#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>
#include<cmath>
#include<string>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 100005
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k;
class TheJediTest{
	public:
		int minimumSupervisors(vector <int> students, int K)
		{
				n=students.size();
					for (i=0;i<n;++i) //本题可以看做将每个学生按楼层标号顺次放在序列上,然后要取若干段,使得每段不超过K，且最大值和最小值不超过2,那么贪心选取即可. 
				{
						k+=(students[i]+K-1)/K;
						int res=(K-students[i]%K)%K;
						if (i+1<n)
						{
								int x=min(students[i+1],res);
								res-=x;
								students[i+1]-=x;
						}
						if (i+2<n)
						students[i+2]-=min(students[i+2],res);
				}
				return k;
		}
};


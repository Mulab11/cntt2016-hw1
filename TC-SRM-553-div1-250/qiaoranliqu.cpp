#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>

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
int i,j,m,n,p,k,top;
struct Node{
		long long x,c;
}stack[N];
inline Node operator +(Node a,Node b)
{
		 return (Node){a.x+b.x,a.c+b.c};
}
int calc(vector<int> x)
{
		int i;
		top=0;
		for (i=0;i<100;++i) stack[++top]=(Node){0,0};
		for (i=0;i<(int)x.size();++i) //模拟过程 
			if (!x[i])
			{
					stack[top-1]=stack[top-1]+stack[top];
					--top;
			}
			else if (x[i]==-1) stack[++top]=(Node){1,0};
			else stack[++top]=(Node){0,x[i]};
		if (stack[top].x==0)
		{
				if (stack[top].c==p) return 1;
				return -1;
		}
		if (stack[top].c>=p) return -1;  
		return p-stack[top].c;
}
class Suminator{
	public:
		int findMissing(vector <int> program, int wantedResult)
		{
				p=wantedResult;
				for (i=0;i<(int)program.size();++i)
					if (program[i]==-1) break;
				program[i]=0; //先试试能不能填合并 
				if (calc(program)==1) return 0;
				program[i]=-1; return calc(program); //设未知的位置值为X,代入去判断一下 
		}
}FFT;

int main()
{
	 FFT.findMissing(vector<int>{1,-1},1);
}


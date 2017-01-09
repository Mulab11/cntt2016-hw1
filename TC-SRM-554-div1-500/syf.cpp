//============================================================================
// Author       : Sun YaoFeng
//============================================================================

//#pragma 	comment(linker, "/STACK:100240000,100240000")
//#include	<cstdio>
//#include	<cstdlib>
//#include	<cstring>
//#include	<algorithm>

#include	<bits/stdc++.h>

using	namespace	std;

#define DB		double
#define	lf		else if
#define I64		long long
#define	Rd()	(rand()<<15|rand())
#define For(i,a,b)	for(int i=a,lim=b;i<=lim;i++)
#define Rep(i,a,b)	for(int i=a,lim=b;i>=lim;i--)

#define	fi	first
#define se	second
#define MK	make_pair
#define PA	pair<int, int>

//#define	min(a,b)	((a)<(b)?(a):(b))
//#define	max(a,b)	((a)<(b)?(b):(a))

#define	CH	(ch=getchar())
int		IN()	{
		int x= 0, f= 0, ch;
		for	(; CH < '0' || ch > '9';)	f= (ch == '-');
		for	(; ch >= '0' && ch <= '9'; CH)	x= x*10 + ch -'0';
		return	f? -x : x;
}

#define n	55

int		N, V[n], A[n], ID[n];

vector<int>	Ans;

bool	Cmp(int a, int b){	//排序
		if	(A[a] != A[b])	return	A[a] < A[b];
		return	a < b;
}

class	TheBrickTowerMediumDivOne{
	public:
		vector <int> find(vector <int> H){
			N= H.size() - 1;
			For(i, 0, N)	A[i]= H[i], ID[i]= i;
			
			sort(ID, ID+N+1, Cmp);
			
			int	Min= 0;
			For(i, 1, N)	if	(H[i] < H[Min])	Min= i;
			
			int	t= 0, last= 100;
			For(i, 0, N)	{
				if	(t == 0)	{
					For(j, 0, N)	if	(! V[j] && H[j] <= last){	//逐位确定
						V[j]= 1;
						Ans.push_back(j);
						last= H[j];
						
						if	(j == Min)	t=1;	//判断
						break;
					}
				}
				
				if	(t == 1)	break;
			}
			
			For(i, 0, N)	if	(! V[ID[i]])	Ans.push_back(ID[i]);	//输出
			
			
			return	Ans;
		}
};
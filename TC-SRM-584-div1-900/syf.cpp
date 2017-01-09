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

#define n	105
#define m	1005
#define INF	(1 << 30)

int		N, M;

int		Rt, X[m], Y[m], W[m];

namespace	Zhu_Liu{	//朱刘算法 用于解最小树形图 板子
	int		C, IN[n], Bel[n], V[n], Min[n];
	
	int		Main(){
		int	ret= 0;
		
		for	( ; ; ){
			For(i, 1, N)	IN[i]= Bel[i]= V[i]= 0, Min[i]= INF;
			
			For(i, 1, M)	if	(X[i] != Y[i] && Y[i] != Rt && W[i] < Min[Y[i]])	//对每一个点处理入度边
				IN[Y[i]]= X[i], Min[Y[i]]= W[i];
			
			For(i, 1, N)	if	(i != Rt && Min[i] == INF)	return	-1;	//终止

			For(i, 1, N)	if	(i != Rt)	{	//处理环
				ret+= Min[i];
				
				int	j= i, k;
				for (; V[j] != i && j != Rt && ! Bel[j]; j= IN[j])	V[j]= i;
				
				if	(j != Rt && ! Bel[j])	{
					for (k= j, C++; IN[k] != j; k= IN[k])	Bel[k]= C;
					Bel[k]= C;
				}
			}
			
			if	(! C)	return	ret;

			For(i, 1, N)	if	(! Bel[i])	Bel[i]= ++C;	//缩环
			
			For(i, 1, M)	{	//处理边
				int v= Y[i];
				
				X[i]= Bel[X[i]];
				Y[i]= Bel[Y[i]];
				
				if	(X[i] != Y[i])	W[i]-= Min[v];
			}
			
			Rt= Bel[Rt];
			N= C;
			C= 0;
		}
		
		return	233;
	}
};

class	FoxTheLinguist{
	public:
		int	ID[n][n];
	
		int minimalHours(int D, vector <string> ss)	{
			For(i, 1, D)	For(j, 0, 9)	ID[i][j]= ++N;
			Rt= ++N;
			
			string	s= "";
			For(i, 1, ss.size())	s+= ss[i-1];
			
		//	cout << s << endl;
			
			For(i, 1, (s.length()+1) / 12)	{
				int	t= (i-1) * 12,
					u= ID[s[t]-'A'+1][s[t+1]-'0'],
					v= ID[s[t+4]-'A'+1][s[t+5]-'0'],
					w= (s[t+7]-'0')*1000 + (s[t+8]-'0')*100 + (s[t+9]-'0')*10 + (s[t+10]-'0');
				
				M++;
				X[M]= u;
				Y[M]= v;
				W[M]= w;
			}	//预处理
		
			For(i, 1, D)	M++, X[M]= Rt, Y[M]= ID[i][0], W[M]= 0;
			For(i, 1, D)	For(j, 1, 9)	M++, X[M]= ID[i][j], Y[M]= ID[i][j-1], W[M]= 0;	//构图
			
		//	For(i, 1, M)	printf("%d %d %d\n", X[i], Y[i], W[i]);
			
			return	Zhu_Liu::Main();
		}
}GTW;
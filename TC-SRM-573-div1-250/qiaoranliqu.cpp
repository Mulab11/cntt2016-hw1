#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>

using namespace std;

const int inf=(int)1e9;

int i,j,m,n,p,k,Q[100005];

class TeamContest{
	 public:
	 	int worstRank(vector<int> v)
		{
			    for (i=3;i<(int)v.size();++i) Q[++Q[0]]=v[i];
			    int now=1,sum=max(v[0],max(v[1],v[2]))+min(v[0],min(v[1],v[2]));
			    sort(Q+1,Q+Q[0]+1);
			     
			    while (Q[0]>=3)
			    {
			    	    int rel=Q[Q[0]]; Q[Q[0]]=inf;  int noww=0; //由于要求组数最多,所以先把当前最大值拿出来,然后找两个满足条件的最小的值 
			    	    for (i=1;i<=Q[0];++i) if (Q[i]!=inf&&rel+Q[i]>sum&&(!noww||Q[noww]>Q[i])) noww=i;
						if (!noww) return now;  
						Q[noww]=inf;
						noww=0;
			    	    for (i=1;i<=Q[0];++i) if (Q[i]!=inf&&rel+Q[i]>sum&&(!noww||Q[noww]>Q[i])) noww=i;
						if (!noww) return now;  
						Q[noww]=inf;
						sort(Q+1,Q+Q[0]+1); Q[0]-=3; //删掉选取的三个点 
						++now;
			    }
			    return now;
		}
}FFT;

int main()
{
	  int A[]={5, 7, 3,-1};vector<int> v;
	  for (i=0;A[i]!=-1;++i) v.push_back(A[i]);
	  FFT.worstRank(v);
}
 

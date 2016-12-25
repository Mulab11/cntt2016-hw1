#include<vector>
#include<algorithm>
#include<cstdio>
using namespace std;
long long f[11111]={};int size,n;
long long g[1111]={},top;int cnt=0;
class Suminator  
{  
        public:  
        int findMissing(vector <int> program, int wantedResult)  
        {  
			n=program.size();
			for(int i=0;i<n;i++)
				f[i]=program[i];
			top=1000;
			for(int i=0;i<n;i++)
				if(f[i]==-1||f[i]==0)
					g[top-1]=g[top]+g[top-1],top--;
				else
					g[++top]=f[i];
			if(g[top]==wantedResult)
			return 0;
			top=1000;
			for(int i=0;i<=1100;i++)
				g[i]=0;
			int pos=0,flag=0;
			for(int i=0;i<n;i++)
				switch(f[i])
				{
				case 0:
					if(top==pos||top-1==pos)
						flag=1;
					g[top-1]=g[top]+g[top-1],top--;
					break;
				case -1:
					g[++top]=1;
					pos=top;
					break;
				default:
					g[++top]=f[i];
					break;
				}
			if(pos==top)
				flag=1;
			if(!flag)
				if(wantedResult==g[top])
					return 1;
				else
					return -1;
			else
				if(wantedResult>=g[top])
					return wantedResult-g[top]+1;
				else
					return -1;
		}
};

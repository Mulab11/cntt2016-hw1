#include<cstdio>
#include<string>
#include<vector>
using namespace std;
char f[222][222]={};
char fg[55][55]={};
int r,g,b,rr,gg,bb;int n,m;
vector<long long>ans;
class PastingPaintingDivOne
{
    public:
        vector<long long> countColors(vector<string> clipboard, int T)
        {
            n=clipboard.size();m=clipboard[0].size();
			for(int i=0;i<n;i++)
				for(int j=0;j<m;j++)
					fg[i][j]=clipboard[i][j];
			if(T<=100)
			{
				for(int k=0;k<T;k++)
					for(int i=0;i<n;i++)
						for(int j=0;j<m;j++)
							f[i+k][j+k]=fg[i][j];
				for(int i=0;i<=200;i++)
					for(int j=0;j<=200;j++)
						if(f[i][j]=='R')r++;
						else if(f[i][j]=='G')g++;
						else if(f[i][j]=='B')b++;
				goto gggg;
			}
			for(int k=0;k<100;k++)
				for(int i=0;i<n;i++)
					for(int j=0;j<m;j++)
						f[i+k][j+k]=fg[i][j];
			for(int i=0;i<=200;i++)
				for(int j=0;j<=200;j++)
					if(f[i][j]=='R')r++;
					else if(f[i][j]=='G')g++;
					else if(f[i][j]=='B')b++;
			for(int i=0;i<n;i++)
				for(int j=0;j<m;j++)
					f[i+100][j+100]=fg[i][j];
			for(int i=0;i<=200;i++)
				for(int j=0;j<=200;j++)
					if(f[i][j]=='R')rr++;
					else if(f[i][j]=='G')gg++;
					else if(f[i][j]=='B')bb++;
			r=r+1LL*(rr-r)*(T-100);
			b=b+1LL*(gg-g)*(T-100);
			b=b+1LL*(bb-b)*(T-100);
			gggg:
			ans.push_back(r);
			ans.push_back(g);
			ans.push_back(b);
			return ans;
        }
};

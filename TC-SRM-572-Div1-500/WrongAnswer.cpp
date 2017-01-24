#include <vector>
#include <string>
#include <algorithm>
#define ull unsigned long long
using namespace std;
class EllysBulls{
public:
	struct item{
		int a;ull x[4];
		item(){a=*x=x[1]=x[2]=x[3]=0;}
		item operator+(const item&it)const{
			item z;for(int i=0;i<4;i++)z.x[i]=x[i]+it.x[i];
			return z;
		}
		bool operator<(const item&it)const{
			for(int i=0;i<4;i++)if(x[i]!=it.x[i])return x[i]<it.x[i];
			return 0;
		}
	}L[10010],R[100010],G;
	string getNumber(vector <string> guesses, vector <int> bulls){
		int l=guesses[0].length(),r=l-l/2,lmax=1,rmax=1;l/=2;
		item*ltot=L,*rtot=R;
		for(int i=0;i<l;i++)lmax*=10;
		for(int i=0;i<r;i++)rmax*=10;
		for(int a=0;a<lmax;ltot->a=a++,ltot++)
			for(int i=0;i<bulls.size();i++)
				for(int x=a,j=0;j<l;x/=10,j++)if(guesses[i][j]-'0'==x%10)ltot->x[i>>4]+=1ull<<i%16*4;
		for(int a=0;a<rmax;rtot->a=a++,rtot++)
			for(int i=0;i<bulls.size();i++)
				for(int x=a,j=0;j<r;x/=10,j++)if(guesses[i][j+l]-'0'==x%10)rtot->x[i>>4]+=1ull<<i%16*4;
		sort(L,ltot);
		sort(R,rtot);
		for(int i=0;i<bulls.size();i++)G.x[i>>4]|=(1ull*bulls[i])<<i%16*4;
		item*ans1=0,*ans2=0;
		for(item*lp=ltot-1,*rp=R;lp>=L;lp--){
			while(rp<rtot&&*lp+*rp<G)rp++;
			for(item*p=rp;p<rtot&&!(G<*lp+*p);p++){
				if(!ans1)ans1=lp,ans2=p;
				else return"Ambiguity";
			}
		}
		if(ans1){
			string ans;
			for(int i=0;i<l;i++)ans.push_back(ans1->a%10+'0'),ans1->a/=10;
			for(int i=0;i<r;i++)ans.push_back(ans2->a%10+'0'),ans2->a/=10;
			return ans;
		}
		else return"Liar";
	}
};

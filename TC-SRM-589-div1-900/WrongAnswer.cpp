#include <vector>
#include <string>
using namespace std;
class FlippingBitsDiv1{
public:
	int min(int a,int b){return a<b?a:b;}
	int getmin(vector <string> S, int M){
		string s;
		for(int i=0;i<S.size();i++)s+=S[i];
		int n=s.length()/M,ans=1<<30;
		if(M<=17)for(int K=0;K<(1<<M);K++){
			int a0=0,a1=0,b,p;
			for(int i=0;i<n;i++){
				for(int j=p=0;j<M;j++)p+=(s[i*M+j]-'0'!=(K>>j&1));
				b=p+min(a0,a1+1);a1=M-p+min(a0+1,a1);a0=b;
			}
			for(int j=p=0;n*M+j<s.length();j++)p+=(s[n*M+j]-'0'!=(K>>j&1));
			ans=min(ans,min(a0,a1+1)+p);
		}
		else for(int K=0;K<(1<<n);K++){
			int a=0;
			for(int i=0;i<n;i++)a+=K>>i&1;
			for(int i=0;i<M;i++){
				int a0=0,a1=0,t=0;
				for(int j=n;j>=0;j--)
					if(j*M+i<s.length())(t=K>>j&1?!t:t)==s[j*M+i]-'0'?++a0:++a1;
				a+=min(a0,a1);
			}
			ans=min(ans,a);
		}
		return ans;
	}
};

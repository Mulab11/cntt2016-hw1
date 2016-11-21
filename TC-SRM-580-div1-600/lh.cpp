#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class ShoutterDiv1{
	private:
		static const int maxn=2600;
		int n;
		int pre[maxn],nxt[maxn],L[maxn],R[maxn],cnt[maxn];
		bool in(int a,int b){
			return ((L[a]>=L[b]&&L[a]<=R[b])||(R[a]>=L[b]&&R[a]<=R[b])||(L[a]<=L[b]&&R[a]>=R[b]));
		}
		bool in2(int a,int ll,int rr){
			return ((L[a]>=ll&&L[a]<=rr)||(R[a]>=ll&&R[a]<=rr)||(L[a]<=ll&&R[a]>=rr));
		}

	public:
		int count(vector<string> s1000, vector<string> s100, vector<string> s10, vector<string> s1, vector<string> t1000, vector<string> t100, vector<string> t10, vector<string> t1){
			memset(L,0,sizeof(L));
			memset(R,0,sizeof(R));
			memset(cnt,0,sizeof(cnt));
			int tmp=0;
			for (int i=0;i<s1000.size();++i)
			for (int j=0;j<s1000[i].length();++j) L[tmp++]+=1000*(s1000[i][j]-'0');
			n=tmp;
			if (n==1) return 0;
			tmp=0;
			for (int i=0;i<s100.size();++i)
			for (int j=0;j<s100[i].length();++j) L[tmp++]+=100*(s100[i][j]-'0');
			tmp=0;
			for (int i=0;i<s10.size();++i)
			for (int j=0;j<s10[i].length();++j) L[tmp++]+=10*(s10[i][j]-'0');
			tmp=0;
			for (int i=0;i<s1.size();++i)
			for (int j=0;j<s1[i].length();++j) L[tmp++]+=(s1[i][j]-'0');
			
			tmp=0;
			for (int i=0;i<t1000.size();++i)
			for (int j=0;j<t1000[i].length();++j) R[tmp++]+=1000*(t1000[i][j]-'0');
			tmp=0;
			for (int i=0;i<t100.size();++i)
			for (int j=0;j<t100[i].length();++j) R[tmp++]+=100*(t100[i][j]-'0');
			tmp=0;
			for (int i=0;i<t10.size();++i)
			for (int j=0;j<t10[i].length();++j) R[tmp++]+=10*(t10[i][j]-'0');
			tmp=0;
			for (int i=0;i<t1.size();++i)
			for (int j=0;j<t1[i].length();++j) R[tmp++]+=(t1[i][j]-'0');
			
			for (int i=0;i<n;++i){
				nxt[i]=pre[i]=i;
				for (int j=0;j<n;++j){
					if (in(i,j)){
						if (L[pre[i]]>L[j]) pre[i]=j;
						else if (L[pre[i]]==L[j]&&R[pre[i]]<R[j]) pre[i]=j;
						if (R[nxt[i]]<R[j]) nxt[i]=j;
						else if (R[nxt[i]]==R[j]&&L[nxt[i]]>L[j]) nxt[i]=j;
					}
				}
			}
			
			int ans=0;
			for (int i=0;i<n;++i){
				int ll=i,rr=i;
//				printf("i=%d\n",i);
				for (int j=0;j<n;++j){
//					if (i==13) printf("j=%d\n",j);
					while(R[j]<L[ll]){
//						printf("ll=%d,pre=%d\n",ll,pre[ll]);
						if (pre[ll]==ll) return -1;
						ll=pre[ll];
						if (R[ll]>R[rr]) rr=ll;
						++cnt[i];
					}
//					if (i==13) printf("j=%d\n",j);
					while(L[j]>R[rr]){
						if (nxt[rr]==rr) return -1;
						rr=nxt[rr];
						if (L[rr]<L[ll]){
//							printf("ll:%d [%d,%d]\n",ll,L[ll],R[ll]);
//							printf("rr:%d [%d,%d]\n",rr,L[rr],R[rr]);
							ll=rr;
//							puts("xxxxxxxx");
						}
						++cnt[i];
					}
				}
			}
			for (int i=0;i<n;++i)
			for (int j=0;j<n;++j) if (in(i,j)) cnt[i]=min(cnt[i],cnt[j]+1);
			for (int i=0;i<n;++i)
			for (int j=0;j<n;++j) if (in(i,j)) cnt[i]=min(cnt[i],cnt[j]+1);
			for (int i=0;i<n;++i)
			for (int j=0;j<n;++j) if (in(i,j)) cnt[i]=min(cnt[i],cnt[j]+1);
			for (int i=0;i<n;++i) ans+=cnt[i];
			return ans;
		}
};

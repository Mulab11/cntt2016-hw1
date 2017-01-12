#include <bits/stdc++.h>

using namespace std;


class ICPCBalloons {
public:
	int minRepaintings(vector <int> balloonCount, string balloonSize, vector <int> maxAccepted) {
		int da[55],xi[55],n1=0,n2=0,n=balloonCount.size(),m=maxAccepted.size(),sd=0,sx=0;
		for(int i=0;i<n;++i)if(balloonSize[i]=='M')sx+=(xi[++n2]=balloonCount[i]);
		else sd+=(da[++n1]=balloonCount[i]);
		sort(maxAccepted.begin(),maxAccepted.end(),greater<int>() );//排序 
		sort(da+1,da+n1+1,greater<int>() );//排序 
		sort(xi+1,xi+n2+1,greater<int>() );//排序 
		int ans=99999;
		for(int s=0;s<(1<<m);++s){//枚举哪些取大的 
			int tmp=0,flag=1,rd=0,rx=0,jd=0,jx=0;
			for(int i=0,j=0,k=0;i<m;++i){//从大到小塞 
				int x=maxAccepted[i];
				if((s>>i)&1){
					if(j==n1){
						if(jd<x){flag=0;break;}
						jd-=x;tmp+=x;
					}else {
						++j;
						if(da[j]<x)tmp+=x-da[j];
						else jd+=da[j]-x;
					}rd+=x;//和 
				}else {
					if(k==n2){
						if(jx<x){flag=0;break;}
						jx-=x;tmp+=x;
					}else {
						++k;
						if(xi[k]<x)tmp+=x-xi[k];
						else jx+=xi[k]-x;
					}rx+=x;//和 
				}
			}
			if(rd>sd||rx>sx)flag=0;
			if(flag)ans=min(ans,tmp);
		}
		return ans==99999?-1:ans;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!

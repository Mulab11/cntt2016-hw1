#include <bits/stdc++.h>

using namespace std;



class EllysRoomAssignmentsDiv1 {
public:
	double getAverage(vector <string> ratings) {
		vector<int>rat;
		string sb;
		for(int i=0;i<ratings.size();++i)sb+=ratings[i];
		stringstream ss(sb);
		int t;
		while(ss>>t)rat.push_back(t);//转成数组 
		int re=rat[0];
		sort(rat.begin(),rat.end(),greater<int>() );//排序 
		int ri=-1;
		double sum=0;
		for(int i=0;i<rat.size();++i)if(rat[i]==re)ri=i;
		int ro=(rat.size()+19)/20;
		for(int i=0;i<rat.size()/ro;++i){
			if(i==ri/ro)continue;
			for(int j=0;j<ro;++j)if(ro*i+j<rat.size())sum+=rat[ro*i+j];
		}//除了Elly在的那轮全加起来 
		sum/=ro;
		if(rat.size()%ro){//有剩下 
			double sum2=0;
			int R=rat.size()/ro*ro;
			if(ri>=R)return (sum+re)/(rat.size()/ro+1);//Elly在最后面 
			for(int i=R;i<rat.size();++i)sum2+=rat[i];
			sum2/=(rat.size()-R);			
			return (sum+sum2+re)/(rat.size()/ro+1)/ro*(rat.size()-R)+(sum+re)/(rat.size()/ro)/ro*(ro-rat.size()+R);
			//两种情况：有跟没有，乘上对应的概率 
		}
		return (sum+re)/(rat.size()/ro);
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!

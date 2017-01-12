#include <bits/stdc++.h>

using namespace std;


class TheJediTest {
public:
	int minimumSupervisors(vector <int> students, int K) {
		students.push_back(0);
		int sum=students[0],ans=0,k=K;
		for(int i=1;i<students.size();++i){
			int tmp=(sum+k-1)/k*k;//上取整到k的倍数 
			if(tmp-sum<=students[i])//当前够用 
				sum=students[i]-(tmp-sum);
			else {
				if(i+1<students.size()&&tmp-sum<=students[i]+students[i+1])//下一个够用 
					students[i+1]-=tmp-sum-students[i];
				else if(i+1<students.size())students[i+1]=0;//不够用也要拿来用 
				sum=0;
			}
			ans+=tmp/k;
		}
		return ans;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!

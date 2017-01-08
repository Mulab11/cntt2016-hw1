#include<bits/stdc++.h>
using namespace std;
int n,i,j,ans;
class TheJediTest
{
    public:
        int minimumSupervisors(vector <int> students, int K)
        {
            n=students.size();
            for(i=0;i<n;i++)//贪心求解 
            {
                ans+=students[i]/K;//学生在同一层 
                students[i]%=K;
                if(students[i])//有剩余的学生 
                {
                    ans++;
                    if(i+1<n)//学生在相邻两层 
                    {
                        j=min(students[i+1],K-students[i]);
                        students[i]+=j;
                        students[i+1]-=j;
                        if(students[i]!=K&&i+2<n)//学生在相邻三层 
                        {
                            j=min(students[i+2],K-students[i]);
                            students[i]+=j;
                            students[i+2]-=j;
                        }
                    }
                    students[i]=0;
                }
            }
            return ans;
        }
};
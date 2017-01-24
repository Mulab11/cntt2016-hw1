class BigFatInteger{
public:
	int minOperations(int A, int B){
		int a=0,b=0;
		for(int i=2;i*i<=A;i++)if(A%i==0){
			int t=0;a++;
			while(A%i==0)A/=i,t++;
			if(t>b)b=t;
		}
		if(A>1)a++,b<1?b=1:1;
		b*=B;
		for(int i=0;;i++)if(b<=(1<<i))return a+i;
	}
};

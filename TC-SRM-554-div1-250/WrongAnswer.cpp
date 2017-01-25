class TheBrickTowerEasyDivOne{
public:
	int find(int A,int a,int B,int b){
		int C=A<B?A:B;
		if(a==b)return A==B?C*2:C*2+1; // 两种颜色高度相同
		return A==B?3*C:3*C+1; // 两种颜色高度不同
	}
};

# include <iostream>
# include <cstring>
# include <chrono>

using namespace std;
using namespace std::chrono;

string randstring(int l){
	char arr[4] = {'A','T','C','G'};
	string res = "";
	for(int i=0;i<l;i++) res += arr[rand() % 4];
	return res;
}
void print(int *arr, string s1, string s2){
    int i, j,m = s1.length()+1,n = s2.length()+1;
    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++) cout << *((arr+i*n) + j) << "  ";
        cout << endl;
    }cout << endl;
}
int maxr=0,maxc=0;
void fillarray(int *arr, string s1, string s2, int i=1, int j=1){
    int m = s1.length()+1,n = s2.length()+1;

    if(s1[i-1] == s2[j-1]) *((arr+i*n) + j) = *((arr+(i-1)*n) + j-1) + 2;
    else *((arr+i*n) + j) = max(max(*((arr+(i-1)*n) + j-1) ,*((arr+i*n) + j-1)),*((arr+(i-1)*n) + j)) - 1;
	
	if (*((arr+i*n) + j) > *((arr+maxr*n) + maxc)){
		maxr = i;
		maxc = j;
	}
    if(j<n-1) fillarray(arr,s1,s2,i,j+1);
    if(j==1 && i<m-1) fillarray(arr,s1,s2,i+1,j);
}
void backtrack(int *arr, string s1, string s2,string ans1="",string ans2=""){
	int n = s2.length()+1;
	if (maxr==0 && maxc==0){
		cout << ans1 << endl << ans2 << endl;
		return;
	}
	else if(*((arr+(maxr-1)*n) + maxc-1)+2 == *((arr+maxr*n) + maxc) && s2[maxc-1]==s1[maxr-1]){
		ans2 = s2[maxc-1] + ans2;
		ans1 = s1[maxr-1] + ans1;
		maxr -= 1;
		maxc -= 1;
	}
	else if(*((arr+maxr*n) + maxc-1)-1 == *((arr+maxr*n) + maxc)){
		ans2 = s2[maxc-1] + ans2;
		ans1 = "_" + ans1;
		maxc -= 1;
	}
	else if(*((arr+(maxr-1)*n) + maxc)-1 == *((arr+maxr*n) + maxc)){
		ans2 = "_" + ans2;
		ans1 = s1[maxr-1] + ans1;
		maxr -= 1;
	}
	else{
		ans2 = "*" + s2[maxc-1] + ans2;
		ans1 = "*" + s1[maxr-1] + ans1;
		maxr -= 1;
		maxc -= 1;
	}
	backtrack(arr,s1,s2,ans1,ans2);
}
int main(){
    string s1="AGCACACA",s2="ACACACTA";
	cout << s1 << endl << s2 << endl;
    int mat[s1.length()+1][s2.length()+1];
    memset(mat, 0, sizeof(mat));

	auto start = high_resolution_clock::now();
    fillarray((int *)mat, s1, s2);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	
    print((int *)mat, s1, s2);
	cout << "time taken:" << duration.count() << endl;
	backtrack((int *)mat, s1 ,s2);
    return 0;
}

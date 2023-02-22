#include <iostream>
#include <thread>
#include <cstring>
#include <chrono>
#include <mutex>
#include <queue>
#include <condition_variable>

using namespace std;
using namespace std::chrono;

std::mutex mu;
std::condition_variable cond;
int STEP = 0;
int SOLVED = 0;
string s1="AGCACACA",s2="ACACACTA";
int mat[9][9];

void fillarray(int *arr, string s1, string s2, int i, int j){
    int m = s1.length()+1,n = s2.length()+1;

    if(s1[i-1] == s2[j-1]) *((arr+i*n) + j) = *((arr+(i-1)*n) + j-1) + 2;
    else *((arr+i*n) + j) = max(max(*((arr+(i-1)*n) + j-1) ,*((arr+i*n) + j-1)),*((arr+(i-1)*n) + j)) - 1;
}
void print(int *arr, string s1, string s2){
    int i, j,m = s1.length()+1,n = s2.length()+1;
    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++) cout << *((arr+i*n) + j) << "  ";
        cout << endl;
    }cout << endl;
}

int tobesolved(int r,int c){
	if(r+c<8) return r + c + 1;
	return 8*2 - r - c - 1;
}

void status(int a,int b,int c,int d){
	cout << "solved: " << a << " row col: " << b << c <<" step:" << d << endl;
}
void func(int col){
	int row = 0;
	while(row<8){
		std::unique_lock<mutex> locker(mu);
		
		cond.wait(locker,[row,col](){return (STEP == (row+col));});
		fillarray((int *)mat,s1,s2,row+1,col+1);
		SOLVED += 1;
		
		if(SOLVED == tobesolved(row,col)){
			cond.notify_all();
			STEP+=1;
			SOLVED = 0;
		}
		
		row++;
		locker.unlock();
	}
}
	
int main(){
	cout << s1 << endl << s2 << endl;
    memset(mat, 0, sizeof(mat));
	
	auto start = high_resolution_clock::now();
    thread th[8];
	for(int i=0;i<8;i++){
		th[i] = thread(func,i);
	}
	for(int i=0;i<8;i++){
		th[i].join();
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	
    print((int *)mat, s1, s2);
	cout << "time taken:" << duration.count() << endl;
}
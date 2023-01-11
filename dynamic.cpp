# include <iostream>
# include <cstring>

using namespace std;

int main(){
    string s1,s2;
    cout << "enter first string:";
    cin >> s1;
    cout << "enter second string:";
    cin >> s2;
    int mat[s1.length()+1][s2.length()+1];
    memset(mat, 0, sizeof(mat));
    int maxEle=-1,maxR,maxC;
    for(int i=1;i<=s1.length();i++){
        for(int j=1;j<=s2.length();j++){
            if(s1[i-1] == s2[j-1]){
                mat[i][j] = mat[i-1][j-1]+2;
            }
            else{
                mat[i][j] = max(max(mat[i-1][j-1],mat[i][j-1]),mat[i-1][j])-1;
            }
            if(maxEle<mat[i][j]){
                maxEle = mat[i][j];
                maxR = i;
                maxC = j;
            }
            cout << mat[i][j] << "  ";
        }
        cout << endl;
    }

    string ans1="",ans2="";
    while(maxR && maxC){
        if(mat[maxR-1][maxC-1]+2 == maxEle && s2[maxC-1]==s1[maxR-1]){
            ans2 = s2[maxC-1] + ans2;
            ans1 = s1[maxR-1] + ans1;
            maxEle = mat[maxR-1][maxC-1];
            maxR -= 1;
            maxC -= 1;
        }
        else if(mat[maxR][maxC-1]-1 == maxEle){
            ans2 = s2[maxC-1] + ans2;
            ans1 = "_" + ans1;
            maxEle = mat[maxR][maxC-1];
            maxC -= 1;
        }
        else if(mat[maxR-1][maxC]-1 == maxEle){
            ans2 = "_" + ans2;
            ans1 = s1[maxR-1] + ans1;
            maxEle = mat[maxR-1][maxC];
            maxR -= 1;
        }
    }
    cout << "String1:" << ans1 << endl << "String2:" << ans2;
}

/* 
 * File:   main.cpp
 * Author: cueva.r
 *
 * Created on 17 de septiembre de 2024, 02:06 PM
 */

#include <iostream>

using namespace std;

int buscasuma(int *arr,int n,int peso){
    int sum=0;
    for(int i=0;i<n;i++)
        sum+=arr[i];
    int dp[n+1][sum+1];
    for(int i=0;i<=n;i++)
        dp[i][0]=1;
    for(int i=1;i<=sum;i++)
        dp[0][i]=0;
    
    for(int i=1;i<=n;i++){
        for(int j=1;j<=sum;j++){
            dp[i][j]=dp[i-1][j];
            if(arr[i-1]<=j and dp[i][j]==0)
                dp[i][j]=dp[i-1][j-arr[i-1]]; //aqui esta lo dificil
        }
    }
    
    for(int i=0;i<=n;i++){
        for(int j=0;j<=sum;j++)
            cout << dp[i][j] <<" ";
        cout << endl;
    }
    return dp[n][peso];
}
        
        
int main(int argc, char** argv) {
    int arr[]={3,5,7};
    int peso=10,n=sizeof(arr)/sizeof(arr[0]);
    cout << buscasuma(arr,n,peso);
    
    return 0;
}


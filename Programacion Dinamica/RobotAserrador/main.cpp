
/* 
 * File:   main.cpp
 * Author: cueva
 *
 * Created on 19 de septiembre de 2024, 10:21 AM
 */

#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

int conflictos(int ini[],int fin[], int i)
{
	for (int j = i - 1; j >= 0; j--) 
		if (fin[j] <= ini[i])	return j;

	return -1;
}

int maxbeneficio(int ini[],int fin[],int ben[], int n){   
    int temp;
    //imprimiendo para ver
//    for (int i=0; i < n; i++) 
//        cout << setw(3) << ini[i] << " ";
//    cout << endl;
//    for (int i=0; i < n; i++) 
//        cout << setw(3) <<fin[i] << " ";
//    cout << endl;
//    for (int i=0; i < n; i++) 
//        cout << setw(3) <<ben[i] << " ";
//    cout << endl;
    /////////////////////////////7
    for (int i=0; i < n; i++) 
        for(int j=i+1;j<n;j++)
           if (fin[i]>fin[j])
           {
               temp=fin[i];
               fin[i]=fin[j];
               fin[j]=temp;
               temp=ini[i];
               ini[i]=ini[j];
               ini[j]=temp;               
               temp=ben[i];
               ben[i]=ben[j];
               ben[j]=temp;              
           } 
    /////////////////////////////77
//    cout << endl;
//    for (int i=0; i < n; i++) 
//        cout << setw(3) << ini[i] << " ";
//    cout << endl;
//    for (int i=0; i < n; i++) 
//        cout << setw(3) <<fin[i] << " ";
//    cout << endl;
//    for (int i=0; i < n; i++) 
//        cout << setw(3) <<ben[i] << " ";
//    cout << endl;
    //////////////////////////////////77
    
    
    
    
    
    
    int dp[n];
    dp[0] = ben[0];

    for (int i = 1; i < n; i++) {
        int inclProf = ben[i];
        int l = conflictos(ini,fin, i);
        if (l != -1) inclProf = inclProf + dp[l];
        dp[i] = max(inclProf, dp[i - 1]);

        for(int j=0;j<i;j++)
            cout << dp[j] <<" ";
        cout << endl;    
    }
    int result = dp[n - 1];

    for(int i=0;i<n;i++)
        cout << dp[i] <<" ";

    return result;
}

int main()
{
    int ini[]={4,5,2,6};
    int fin[]={15,10,4,12};
    int ben[]={100,30,40,80};

    int n = sizeof(ini) / sizeof(ini[0]);
    cout << endl<<"El beneficio es: "	<< maxbeneficio(ini,fin,ben, 4);
	return 0;
}


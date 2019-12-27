#include<bits/stdc++.h>
#include<iostream>

using namespace std;



void final_result(double** a, double** b,double** pi,int a_n, int a_m, int b_n,int b_m, int c_n,int c_m ){
    
    double** output1 = new double*[100];
    
    
    for(int i=0;i<c_n;i++){
    	output1[i] = new double[a_m];
    	for(int j=0;j<a_m;j++){
    	// Initialize the element to zero.
    		output1[i][j] = 0;
     		for (int k = 0; k < c_m; k++) {
        // Accumulate the result
        output1[i][j] += pi[i][k] * a[k][j];
     }
   }
}
    
    double** output2 = new double*[100];



    for(int i=0;i<c_n;i++){
    	output2[i] = new double[b_m];
    	for(int j=0;j<b_m;j++){
    	// Initialize the element to zero.
    		output2[i][j] = 0;
     		for (int k = 0; k < b_n; k++) {
        // Accumulate the result
        output2[i][j] += output1[i][k] * b[k][j];
     }
   }
}    
    
 cout<<c_n<<" "<<b_m<<" ";
	for(int i=0;i<c_n;i++){
		for(int j=0;j<b_m;j++){
            cout<<output2[i][j]<<" ";
	
	 	}
		
	}


// delete memory


for(int i = 0; i < c_n; i++) {
        delete[] output2[i];   
 }
delete[] output2;


for(int i = 0; i < a_m; i++) {
        delete[] output1[i];   
 }
delete[] output1;



int main(){
	
	int a_n,a_m,b_n,b_m,c_n,c_m;

// a matrix
 // b matrix
// pi initial matrix


	double** a = new double* [100];

	double** b = new double* [100];

	double** pi = new double* [100];



	cin>>a_n;
	cin>>a_m;


	for(int i=0;i<a_n;i++){
	    a[i]= new double[a_m];
		for(int j=0;j<a_m;j++){
            cin>>a[i][j];
		
	}
}

	cin>>b_n;
	cin>>b_m;


	for(int i=0;i<b_n;i++){
	    b[i]= new double[b_m];
		for(int j=0;j<b_m;j++){
            cin>>b[i][j];
		
	}
}




	cin>>c_n;
	cin>>c_m;


	for(int i=0;i<c_n;i++){
	    pi[i]= new double[c_m];
		for(int j=0;j<c_m;j++){
            cin>>pi[i][j];
		
	}
}


	

final_result(a, b, pi, a_n, a_m, b_n,b_m, c_n,c_m );




}
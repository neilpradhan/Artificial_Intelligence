#include<bits/stdc++.h>
#include<iostream>

using namespace std;


 int a_n,a_m,b_n,b_m,c_n,c_m,d_n;// size of aij , bij , pi, o


void alpha(double**a,double** b,double** pi, double** o, double** output1,double* local){
    
    



    for (int i=0;i<a_m;<i++){
        output1[i] = pi[0][i]*b[o[0]];
    }


	local[0] = 0;
	for(int i = 0; i < a_m; i++)
	{
		local[0] += output1[0][i];
	}
	local[0] = 1/local[0];// normalizing term

	for(int i = 0; i < a_n; ++i)
	{
		output1[0][i] *= local[0];// normalizing here
	}


	for(int t = 1; t < d_n; t++) // T is length of O or input
	{
		local[t] = 0;// initializing
		for(int i = 0; i < a_n; i++)// length of hidden states A,B,H,S = 4
		{
			output1[t][i] = 0;// initialize for every input t we have a result

			// result will have the same number of rows as the output and columns as hidden states
			for(int j = 0; j <a_n ; j++)
			{
				output1[t][i] += output1[t-1][j]*a[j][i];// for every hidden state A,B..  we add previous result
			}
			output1[t][i] *= b[i][O[t]];
			local[t] += output1[t][i];
		}
		local[t] = 1/local[t];
		for(int i = 0; i < N; ++i)
		{
			output1[t][i] *= local[t];
		}
	}





	

    
}










void Transpose_mat(double**arr,int r_a, int c_a,double** output1){
    
    
     for (int i=0;i<c_a;i++){
         output1[i] = new double[r_a];
     }
    
    
    
    
    for (int i=0;i<r_a;i++){
        for( int j=0;j<c_a;j++){
            output1[j][i] = arr[i][j];
        }
    }
    
    
    // visualize output
	for(int i=0;i<c_a;i++){
		for(int j=0;j<r_a;j++){
            cout<<output1[i][j]<<" ";
	
	 	}
		cout<<endl;
	}    
    
    
    
}

void Multiply_two_matrix(double** arr1,double** arr2, int r_a, int c_a , int r_b, int c_b,double** output1){


    for(int i=0;i<r_a;i++){
    	output1[i] = new double[c_b];
    	for(int j=0;j<c_b;j++){
    	// intialize for sum
    		output1[i][j] = 0;
     		for (int k = 0; k < c_a; k++) {
        // Accumulate the result
        output1[i][j] += arr1[i][k] * arr2[k][j];
     }
   }
}

// visualize output
	for(int i=0;i<r_a;i++){
		for(int j=0;j<c_b;j++){
            cout<<output1[i][j]<<" ";
	
	 	}
		cout<<endl;
	}







}













void emission_prob(double** a, double** b,double** pi,int a_n, int a_m, int b_n,int b_m, int c_n,int c_m ){
    
    double** output1 = new double*[100];// multiply pi and aij
    
    
    for(int i=0;i<c_n;i++){
    	output1[i] = new double[a_m];
    	for(int j=0;j<a_m;j++){
    	// intialize for sum
    		output1[i][j] = 0;
     		for (int k = 0; k < c_m; k++) {
        // Accumulate the result
        output1[i][j] += pi[i][k] * a[k][j];
     }
   }
}
    
    double** output2 = new double*[100];// multiply output1 and bij



    for(int i=0;i<c_n;i++){
    	output2[i] = new double[b_m];
    	for(int j=0;j<b_m;j++){
    	// Initialize for sum
    		output2[i][j] = 0;
     		for (int k = 0; k < b_n; k++) {
        // Accumulate the result
        output2[i][j] += output1[i][k] * b[k][j];
     }
   }
}    
    
// cout<<c_n<<" "<<b_m<<" ";

//displaying output
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

}

int main(){
	
	int a_n,a_m,b_n,b_m,c_n,c_m, d_n;

// a matrix
 // b matrix
// pi initial matrix


	double** a = new double* [100];

	double** b = new double* [100];

	double** pi = new double* [100];



// taking input

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


    // taking input from user
	cin>>d_n;
	double* o = new double[d_n];
	
	
	for(int i=0;i<d_n;i++){
	    cin>>o[i];

}	




	
// next emission distribution hmm0
//emission_prob(a, b, pi, a_n, a_m, b_n,b_m, c_n,c_m );


double** output1 = new double*[100];

//Multiply_two_matrix(a,b,a_n,a_m,b_n,b_m,output1);

Transpose_mat(pi,c_n,c_m,output1);




// for hmm1 alpha calcualtion
// matrix of size input X number of hidden states 
    double** output2 = new double*[d_n];

    for (int i =0;i<d_n;i++){
    	output2[i] = new double[a_m];
    }





}
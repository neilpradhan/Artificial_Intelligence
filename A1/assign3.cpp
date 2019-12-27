




#include<bits/stdc++.h>
#include<iostream>
#include<algorithm>
using namespace std;



short unsigned T, M, N, pi_l;
// transpose of a vector or vector 
template <typename T>
vector < vector <T> > transpose(vector < vector <T> > a)
{
	vector < vector <T> > output;
	output.resize(a[0].size());
	for(int i = 0; i < output.size(); ++i)
	{
		output[i].resize(a.size());
	}
	for(int i = 0; i < a.size(); ++i)
	{
		for(int j = 0; j < a[i].size(); ++j)
		{
			output[j][i] =  a[i][j];
		}
	}
	return output;
}


// multiply vectors
template < typename T>
vector < vector <T> > mutiply_2d_arrays(vector < vector <T> >a, vector < vector <T> > b)
{
    vector < vector <T> > output;
    // size is the 
    output.resize(a.size()); // rows of 1 st vector
    for(int i = 0; i < output.size(); ++i)
    {

        // fill a vector with zeros with size as columns of 2nd vector
        // fill complete 2d vector by zeros

        output[i] = vector<T> (b[0].size(), 0);
    }

    for(int i = 0; i < a.size(); ++i)
    {
        for(int j = 0; j < b[0].size(); ++j)
        {
            for(int k = 0; k < b.size(); ++k)
            {
                output[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return output;
}


// multiplying 1d arrays
template <typename T>
vector<T> multiply_1d_arrays(vector<T> a, vector<T> b)
{
    vector<T> output;
    output.resize(a.size());// size of rows 
    for(unsigned i = 0; i < output.size(); ++i)
    {
        output[i] = a[i]*b[i];
    }

    return output;
}







template <typename T>
// returns an 1 d array
vector <T> multiply_1d_with_2d_arrays(vector <T> a, vector < vector <T> > b)
{
    vector <T> output(b[0].size(), 0); //fill zeros with rows

    for(int i = 0; i < b[0].size(); ++i)
    {
        for(int  j = 0; j < b.size(); ++j)// columns
        {
            output[i] += a[j] * b[j][i];
        }
    }

    return output;
}




//hmm1
vector< vector<double> > final_probability(vector<vector <double> > a, vector < vector <double> > b, vector < vector <double> > pi, vector<double> o)
{

	

 
	vector < vector<double> > output;
	output.resize(o.size()); // N


	output[0] =   multiply_1d_arrays(pi[0], b[o[0]]);

	for(int i = 1; i < o.size(); ++i)
	{
		output[i] = multiply_1d_arrays(multiply_1d_with_2d_arrays(output[i-1],a), b[o[i]]);// return vector<double>
	}
	double sum = 0;
	for(int i = 0; i < output[0].size(); ++i)
	{
		sum += output[output.size()-1][i];
	}
	cout << sum << endl;
	return output;
}







//hmm2
void most_probable_states(vector < vector <long double> > a, vector < vector <long double> > b, vector < vector <long double> > pi, vector<int> o)
{
	
	



	vector<unsigned> most_probable_sequency;




	vector< vector<long double> > delta;

	vector< vector<unsigned> > deltaState;

	delta.resize(o.size());// size of input but in matrix
	deltaState.resize(o.size());// size of input also in matrix
	
	for(int i = 0; i < delta.size(); ++i)
	{
		delta[i].resize(a.size());// every row is vector of size input b,p,l,e
		deltaState[i].resize(a.size());
	}


	vector < vector <long double> > b_trans = transpose(b);
	delta[0] = multiply_1d_arrays(pi[0], b_trans[o[0]]);// 1st element is delta1 which is simply . of 1st probable state with previous



	unsigned max = distance(delta[0].begin(), max_element(delta[0].begin(), delta[0].end()));// finding max of these and the index of it in the 
//	vector using distance
//looping through all inputs o
	for(int t = 1; t < delta.size(); ++t)
	{
		// for every input state 
		// looping througn N 
		for(int i = 0; i < a.size(); ++i)
		{
			vector<long double> v = vector<long double>(a.size());// temperary matrix
			for(int j = 0; j < a.size(); ++j)
			{
				v[j] = delta[t-1][j] * a[j][i] * b[i][o[t]];// every row is equal to previous observed delta
			}

			delta[t][i] =  *max_element(v.begin(), v.end());
			deltaState[t][i] = distance(v.begin(), max_element(v.begin(), v.end()));
		}
		//showVect(delta[t]);
	}

	max = distance(delta[delta.size()-1].begin(), max_element(delta[delta.size()-1].begin(), delta[delta.size()-1].end()));
	most_probable_sequency.resize(delta.size());
	most_probable_sequency[delta.size()-1] = max;


	vector < vector <long double> > a_trans = transpose(a);

	for(int  i = delta.size()-1; i > 0; --i)
	{
		vector<long double> v;
		v = multiply_1d_arrays(delta[i-1],a_trans[most_probable_sequency[i]]);
		most_probable_sequency[i-1] = distance(v.begin(), max_element(v.begin(), v.end()));
	}

	for(int i = 0; i < most_probable_sequency.size(); ++i)
	{
		cout << most_probable_sequency[i] << " ";
	}
	cout << endl;

}


//extra methods for hmm3


void display_mat(double **mat, short unsigned m, short unsigned n)
{
	cout<<m<<" "<<n<<" ";
	for(short unsigned i = 0; i < m; ++i)
	{
		for(short unsigned j = 0; j < n; ++j)
		{
			cout<<mat[i][j]<<" ";
		}
	}
	cout<<endl;
}



// alpha pass stamp 2
void alpha(double **output, double **a, double **b, double **pi, short unsigned*o, double*C)
{


	C[0] = 0; // c0 =0;
	for(short unsigned i = 0; i < N; ++i)
	{
		output[0][i] = pi[0][i]*b[i][o[0]];// stamp 2 alpha  pass
		C[0] += output[0][i];// c0+= alpha 0(i)
	}



	// scaling the  alpha 0 of i
	C[0] = 1/C[0];

	for(short unsigned i = 0; i < N; ++i)
	{
		output[0][i] *= C[0];
	}


	for(short unsigned t = 1; t < T; ++t)
	{
		C[t] = 0;
		for(short unsigned i = 0; i < N; ++i)
		{
			output[t][i] = 0;
			for(short unsigned j = 0; j < N; ++j)
			{
				output[t][i] += output[t-1][j]*a[j][i];
			}
			output[t][i] *= b[i][o[t]];
			C[t] += output[t][i];
		}
		C[t] = 1/C[t];
		for(short unsigned i = 0; i < N; ++i)
		{
			output[t][i] *= C[t];
		}
	}

}



//beta pass // output is Beta stamp 3
void beta(double **output, double **a, double **b, double **pi, short unsigned* o, double*C)
{	// let beta t-1 (i) be scaled by  c(t-1)
	for(short unsigned i = 0; i < N; ++i)
	{
		output[T-1][i] = C[T-1];
	}

	//beta pass
	for(int t = T-2; t >= 0; --t)
	{
		for(short unsigned i = 0; i < N; ++i)
		{
			output[t][i] = 0;
			for(short unsigned j = 0; j < N; ++j)
			{
				output[t][i] += output[t+1][j]*b[j][o[t+1]]*a[i][j];
			}
			output[t][i] *= C[t];
		}
	}
}






void hmm_3(double ** a, double ** b, double ** pi, short unsigned* o)
{
	short unsigned i, j, t;

	double *** tGamma;// 3d array  for each t it stores N X N matrix 


	//local  mAlpha
	double **Alpha = new double*[T];
	for(t = 0; t < T; ++t)
	{
		Alpha[t] = new double[N];
	}





// local  mBeta

	double **Beta = new double*[T];
	for(t = 0; t < T; ++t)
	{
		Beta[t] = new double[N];
	}




// local mGamma , mc  and mdigamma

	double **iGamma;// 2d array
	double *mC = new double[T]; // vector

	tGamma = new double**[T];// T rows and 1 column and N X N for each t 
	for(t = 0; t < T; ++t)
	{
		tGamma[t] = new double*[N];
		for(j = 0; j < N; ++j)
		{
			tGamma[t][j] = new double[N];
		} 
	}

	iGamma = new double* [T];
	for(t = 0; t < T; ++t)
	{
		iGamma[t] = new double[N];
		for(i = 0; i < N; ++i)
		{
			iGamma[t][i] = 0;
		}
	}

// stamp 4



	double logProb =0;
	double oldLogProg = -1000000;

	short unsigned idx = 0;
	for(;;)
	{
		alpha(Alpha, a, b, pi, o, mC);

		beta(Beta, a, b, pi, o, mC);

		double denom;
		for(t = 0; t < T-1; ++t)
		{
			denom = 0;
			for(i = 0; i < N; ++i)
			{
				for(j = 0; j < N; ++j)	
				{
					denom += Alpha[t][i] * a[i][j] * b[j][o[t+1]] * Beta[t+1][j];
				}
			}
			for(i = 0; i < N; ++i)
			{
				iGamma[t][i] = 0;
				for(j = 0; j < N; ++j)
				{
					tGamma[t][i][j] = Alpha[t][i]*a[i][j]*b[j][o[t+1]]*Beta[t+1][j]/denom;
					iGamma[t][i] += tGamma[t][i][j];
				}
			}
		}

// special cases for gamma t-1
		denom = 0;
		for(i = 0; i < N; ++i)
		{
			denom += Alpha[N-1][i];
		}
		for(i = 0; i < N; ++i)
		{
			iGamma[T-1][i] = Alpha[T-1][i]/denom;
		}

// stamp 5 re estimating 
		//Re-estimate Pi
		pi[0] = iGamma[0];

		double sumDiGamma = 0;
		double sumGamma = 0;
		//Re-estimate A
		for(i = 0; i < N; ++i)
		{
			for(j = 0; j < N; ++j)
			{
				sumDiGamma = 0;
				sumGamma = 0;
				for(t = 0; t < T-1; ++t)
				{
					sumDiGamma += tGamma[t][i][j];
					sumGamma += iGamma[t][i];
				}
				a[i][j] = sumDiGamma/sumGamma;
			} 
		}


		double sum1;
		double sum2;
		//Re-estimate B
		for(i = 0; i < N; ++i)
		{
			for(j = 0; j < M; ++j)
			{
				sum1 = 0;
				sum2 = 0;
				for(t = 0; t < T; ++t)
				{
					if(o[t] == j)
						sum1 += iGamma[t][i];
					sum2 += iGamma[t][i];
				}
				b[i][j] = sum1/sum2;
			}
		}
		
		// stamp 6 Compute log[P(O|y)]
		logProb = 0;
		for(i = 0; i < T; ++i)
		{
			logProb += log(mC[i]);
		}
		logProb = -logProb;

		++idx;

		if(idx >= 30 || logProb <= oldLogProg)
			break;

		oldLogProg = logProb;
	}

	display_mat(a, N, N);
	display_mat(b, N, M);
    display_mat(pi,1,pi_l);

}

int main(){




// 	int a_n,a_m,b_n,b_m,c_n,c_m, d_n;
// 	double value;

// // a matrix
// // b matrix
// // pi initial matrix
// // o matrix




// // taking input

// 	cin>>a_n;
// 	cin>>a_m;


// vector< vector<long double > > a(a_n) ;
// for( int i =0 ; i < a_n ; i++ ) {
// for ( int j=0 ; j < a_m ; j++ ) {
// cin >> value ;
// a[i].push_back ( value ) ;
// } 
// }

// 	cin>>b_n;
// 	cin>>b_m;




// vector< vector<long double > > b(b_n) ;
// for( int i =0 ; i < b_n ; i++ ) {
// for ( int j=0 ; j < b_m ; j++ ) {
// cin >> value ;
// b[i].push_back ( value ) ;
// } 
// }




// 	cin>>c_n;
// 	cin>>c_m;

// vector< vector<long double > > pi(c_n) ;
// for( int i =0 ; i < c_n ; i++ ) {
// for ( int j=0 ; j < c_m ; j++ ) {
// cin >> value ;
// pi[i].push_back ( value ) ;
// } 
// }





//     // taking input from user
// cin>>d_n;

// //cout <<d_n;

// vector<int>o;
// for( int i =0 ; i <d_n ; ++i ) {
// 	cin>>value;
// 	o.push_back(value);
// }



// visualize output
// for (int i = 0; i < a.size(); i++) { 
//     for (int j = 0; j < a[i].size(); j++){
//         cout << a[i][j] << " ";     	
//     } 
//     cout << endl; 
//  } 


// cout<<o.size();
// showVect(o);

//hmm1
	//vector< vector<double> > tmp = final_probability(a, transpose(b), pi, o);

	


//visualize output
// for (int i = 0; i < a.size(); i++) { 
//     for (int j = 0; j < a[i].size(); j++){
//         cout << a[i][j] << " ";     	
//     } 
//     cout << endl; 
//  } 


// hmm2

//most_probable_states(a,b,pi,o);

// hmm 3 extra work
	short unsigned a_n,a_m,b_n,b_m,c_n,c_m, d_n;

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

// cout<<"done";
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
	short unsigned* o = new short unsigned[d_n];
	
	
	for(int i=0;i<d_n;i++){
	    cin>>o[i];

}

T = d_n;
N = a_n;
M = b_m;
pi_l = c_m;
hmm_3(a, b, pi, o);


}
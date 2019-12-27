




#include<bits/stdc++.h>
#include<iostream>
#include<algorithm>
using namespace std;





// transpose
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

	// o.size() N

 
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
void most_probable_states(vector<vector<double>> a,vector<vector<double>> b,vector<vector<double>> pi,vector<double> o ){

	
	vector<vector<double>> a_trans = transpose(a);

	vector<vector<double>> b_trans = transpose(b);


	vector<int> most_probable_states;

	vector<vector<double>> delta;
	
	vector<vector<double>> deltastate;

	delta.resize(o.size()); // A,B, H, S

	most_probable_states.resize(o.size());// same size as Hidden states

	for(int i=0;i<delta.size();i++){
		delta[i].resize(a.size());// rows of a is the rowsof delta
		deltastate[i].resize(a.size());
	}


	delta[0] = multiply_1d_arrays(pi[0],b_trans[o[0]]);// 0.05 0 0 0.05


	long double max_index = distance(delta[0].begin(),max_element(delta[0].begin(), delta[0].end()));// for 1 from zero


// finding delta for all inputs 
	for (int k=0;k<delta.size(); k++){


		for (int i=0;i<a.size();i++){

			vector<long double> v = vector<long double>(a.size());
		
			for (int j=0;j<a.size();j++){

				v[j] = delta[k-1][j] * a[j][i] * b[i][o[k]]; // as solved in the hmm1 
			}


			// we find the index of maximum element
			delta[k][i] = (*max_element(v.begin(), v.end()));
			deltastate[k][i] = distance(v.begin(),max_element(v.begin(),v.end()));


		}

	}




	max_index  = distance(delta[delta.size()-1].begin(),max_element(delta[delta.size()-1].begin(),delta[delta.size()-1].end()));

	most_probable_states.resize(delta.size());

	most_probable_states[delta.size()-1] = max_index;

	for (int i = delta.size()-1;i>0;i--){
		vector<double> v;
		v = multiply_1d_arrays(delta[i-1],a_trans[most_probable_states[i]]);
		most_probable_states[i-1]= distance(v.begin(),max_element(v.begin(),v.end()));
		
	
	}




	for (int i=0;i<most_probable_states.size();i++){
				cout<< most_probable_states[i]<<" ";
			}
	cout<<endl;




}








int main(){




	int a_n,a_m,b_n,b_m,c_n,c_m, d_n;
	double value;

// a matrix
// b matrix
// pi initial matrix
// o matrix




// taking input

	cin>>a_n;
	cin>>a_m;


vector< vector< double > > a(a_n) ;
for( int i =0 ; i < a_n ; i++ ) {
for ( int j=0 ; j < a_m ; j++ ) {
cin >> value ;
a[i].push_back ( value ) ;
} 
}

	cin>>b_n;
	cin>>b_m;




vector< vector< double > > b(b_n) ;
for( int i =0 ; i < b_n ; i++ ) {
for ( int j=0 ; j < b_m ; j++ ) {
cin >> value ;
b[i].push_back ( value ) ;
} 
}




	cin>>c_n;
	cin>>c_m;

vector< vector< double > > pi(c_n) ;
for( int i =0 ; i < c_n ; i++ ) {
for ( int j=0 ; j < c_m ; j++ ) {
cin >> value ;
pi[i].push_back ( value ) ;
} 
}





    // taking input from user
cin>>d_n;

//cout <<d_n;

vector<double>o;
for( int i =0 ; i <d_n ; ++i ) {
	cin>>value;
	o.push_back(value);
}



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


// hmm1

most_probable_states(a,b,pi,o);





}
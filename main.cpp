/**
    Weighted Index
    Copyright (C) 2016 Carl Barton, Tomasz Kociumak, Chang Liu, Solon P. Pissis and Jakub Radoszewski.
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/

#include <iostream>
#include <string>
#include <chrono>
#include <list>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "node.h"
#include "defs.h"

#include <divsufsort.h>
#include <sdsl/rmq_support.hpp>

using namespace std;
using get_time = chrono::steady_clock;
	double ** text;

int main (int argc, char ** argv )
{
	TSwitch sw;
	int mod;
	string text_file;
	string pattern_file;
	string output_file;
	double z;
	
	int n;

	ofstream result;

	unsigned int k;

	/* Decodes the arguments */

	k = decode_switches ( argc, argv, &sw );

	/* Check the arguments */
	if ( k < 5 )
	{
		usage();
		return 1;
	}
	else
	{
		if ( sw.text_file_name.empty() )
		{
			cout << "Error: No Text input!\n";
			return 0;
		}
		else
	{
			text_file = sw.text_file_name;
		}
		

/*
		if ( sw.pattern_file_name.empty() )
		{
			cout << "Error: No pattern input!\n";
			return 0;
		}
		else
		{
			pattern_file = sw.pattern_file_name;
		}
*/
		if ( sw.output_file_name.empty() )
		{
			cout << "Error: No Output file\n";
			return 0;
		}
		else
		{
			output_file = sw.output_file_name;
		}

		if ( sw.z > 0 )
		{
			z = sw.z;
		}
		else
		{
			cout << "Error: z must be a positive number!\n";
		}
	}

	/* read input */
	if ( !read ( text_file, &text, &n ) )
	{
		cout << "Error: Failed to read input!\n";
		return 0;
	}
	cout << "text length:" << n << endl;
	cout << "Finish reading input" << endl;

	cout << "index begin" << endl;

	auto begin = get_time::now();
	//build special sequence
	string sq;
	weighted_index_building ( text, n, z, &sq );

	cout << "After building, sq length is " << sq.size() << endl;

	cout << sq << endl;

	//Index using Suffix array
	int N = sq.size();

	int * SA	= new int [2*N];
	int * iSA	= new int [2*N];
	int * LCP	= new int [2*N];
	int * ME	= new int [2*N];
	int * MP	= new int [2*n];
	unsigned char * psq	= new unsigned char [2*N];
	for ( int i = 0, j = 0; i < N, j < N; i++, j++ )
	{
		psq[i] = sq[j];
	}
	for ( int i = N, j = N; i < 2*N, j > 0; i++, j-- )
	{
		psq[i] = sq[j-1];
	}

	maximal_check ( sq, text, z, n, ME );
	SA_LCP_index ( text, psq, 2*N, n, z, SA, iSA, LCP );

	cout << "after index" << endl;
#if 1
	for ( int i = 0; i < z; i++ )
	{
		for ( int j = 0; j < 2 * n; j ++ )
		{
			cout << ME[i*2*n +j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
#endif
	
	vector < int > v ( 2*N, 0 );
	for ( int i = 0; i < 2*N; i++ )
		v[i] = LCP[i];
	rmq_succinct_sct<> rmq(&v);


	maximal_palindrome ( N, n, z, SA, iSA, LCP, rmq, ME, MP );

	cout << "after maximal palindrome" << endl;

#if 0
	for ( int i = 0; i < 2*N; i++ )
		cout << ME[i] << endl;
#endif

	deque<int> decomposition;
	FunctionWMPD ( MP, 2*n-1, decomposition );
	for ( int i : decomposition )		cout << i << ' ';	cout << endl;
	auto end = get_time::now();
	auto diff = end - begin;
	cout<<"Time is:  "<< chrono::duration_cast<chrono::milliseconds>(diff).count()<<" ms "<<endl;

	delete[] SA;
	delete[] iSA;
	delete[] LCP;
	delete[] ME;
	delete[] MP;
	delete[] psq;
	for ( int i = 0; i < n; i++ )
		delete[] text[i];
	delete[] text;

	return 0;
}


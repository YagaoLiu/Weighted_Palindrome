#include <iostream>
#include <cmath>
#include <list>

#include <sdsl/rmq_support.hpp>

using namespace std;
using namespace sdsl;

int longest_common_extension( int a, int b, int n, double z, int * SA, int *iSA, int * LCP, int * ME, rmq_succinct_sct<> &rmq )
{
	list <int> SA_a;
	list <int> SA_b;
	int lce = 0;
	for ( int i = 0; i < z; i++ )
	{
		SA_a.push_back ( SA[a+n*z] );
		SA_b.push_back ( SA[b+n*z] );
	}
	SA_a.sort();
	SA_b.sort();
	int i = j = 0;
	while ( i < SA_a.size() && j < SA_b.size() )
	{
		if ( SA_a[i] < SA_b[j] )
		{
			if ( SA_a[i+1] < SA_b[j] )
			{
				i = i + 1;
			}
			else
			{
				lce = max ( lce, LCP[rmq(SA_a[i]+1,SA_b[j])] );
			}
		}
		else
		{
			if ( SA_a[i] )
		}
	}
	return lce;
}


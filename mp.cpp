#include <cmath>
#include <sdsl/rmq_support.hpp>
#include "defs.h"

using namespace std;
using namespace sdsl;

void maximal_palindrome ( int N, int n, double z, int * SA, int * iSA, int * LCP, rmq_succinct_sct<> &rmq, int * ME, int * MP )
{
	//compute previous MPZ
	int * MPZ = new int [2 * N];
	int l, r;
	MPZ[2*N-1] = 0;
	for ( int i = 0; i < N; i++ )
	{
		l = min ( iSA[i], iSA[2*N-i-1] );
		r = max ( iSA[i], iSA[2*N-i-1] );
		MPZ[2*i] = 2*LCP[ rmq(l+1,r) ]-1;
		if ( i > 0 )
		{
			l = min ( iSA[i], iSA[2*N-i] );
			r = max ( iSA[i], iSA[2*N-i] );
			MPZ[2*i-1] = 2*LCP[ rmq(l+1,r) ];
		}
	}

	//fix MPZ with ME: take the min value
	for ( int i = 0; i < 2*N; i++ )
	{
		MPZ[i] = min( MPZ[i], ME[i] );
	}

	//Compute MP: take the maximal value for each position in text
	for ( int i = 0; i < 2*n; i++ )
	{
		MP[i] = 0;
		for ( int j = 0; j < z; j++ )
		{
			MP[i] = max ( MP[i], MPZ[i+j*2*n] );
		}
	}

	delete[] MPZ;

}



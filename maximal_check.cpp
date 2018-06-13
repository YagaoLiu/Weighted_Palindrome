#include <string>

#include "defs.h"

using namespace std;

double pos_prob ( char x, int pos, double **text )
{
	double prob = 0;
	switch ( x )
	{
		case 'A':
			prob = text[pos][0];
			break;
		case 'C':
			prob = text[pos][1];
			break;
		case 'G':
			prob = text[pos][2];
			break;
		case 'T':
			prob = text[pos][3];
			break;
		default:
			break;
	}
	return prob;
}

void maximal_check( string & sq, double ** text, double z, int n, int * ME )
{
	int begin = 0;
	int center = 0;
	double prob = 1;
	for ( int i = 0; i < z; i++ )
	{
		prob = 1;
		begin = 0;
		for ( int j = 0; j < n; j++ )
		{
			int end_pos = j + i * n;
			int begin_pos = begin + i * n;
			double end_prob = pos_prob ( sq[end_pos], j, text );
			double begin_prob = pos_prob ( sq[begin_pos], begin, text );
			double temp_prob = prob * end_prob;
			if ( temp_prob >= 1/z )
			{
				if ( j == 0 )
				{
					ME[center] = 1;
				}
				else
				{
					ME[center] = ME[center-1] + 1;
				}
				prob = temp_prob;
			}
			else
			{
				if ( j == 0 || ME[center-1] == 0)
				{
					ME[center] = 0;
					ME[center+1] = 0;
					center ++;
					begin ++;
				}
				else
				{
					ME[center] = ME[center-1] - 1;
					prob /= begin_prob;
					begin ++;
					j--;
				}
			}
			center ++;
			if ( j == n -1 )
			{
				for ( begin = begin; begin < j; begin++ )
				{
					ME[center] = ME[center-1]-1;
					center ++;
				}
			}
		}
		ME[center] = 0;
		center ++;
	}
}



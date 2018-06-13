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
#include <cmath>
#include <list>

#include <sdsl/rmq_support.hpp>

using namespace std;
using namespace sdsl;

int lcp ( string & x, int M, string & y, int l )
{
	int i = 0;
	for ( i = 0; i < min ( x.size(), y.size()); i++ )
	{
		if ( x[M+i] != y[i+l] )	break;
	}
	return i;
}

int match ( string & pattern, string & text, int n, int * SA, int * LCP, int * ME, list<int> & Occ, rmq_succinct_sct<> &rmq )
{
	int P = pattern.size();
	int N = text.size();
	int L, R, M;
	int l, r, m;
	int num_Occ = 0;
	int found_flag = 0;;
	
	// LCP Match
	l = lcp ( text, SA[0], pattern, 0 );
	r = lcp ( text, SA[N-1], pattern, 0 );

#if	1 
	if ( l == P )
	{
		if ( ME[SA[0]] >= P )
		{
			Occ.push_back( SA[0] );
		}
		return Occ.size();
	}
	else
	{
		L = 0;
		R = N-1;
		while ( R-L > 1 )
		{
			M = (L+R) / 2 ;
			if ( l >= r )
			{
				if ( LCP[rmq( L+1, M )] >= l )
					m = l + lcp ( text, SA[M]+l, pattern, l );
				else
					m = LCP[rmq( L+1, M )];
			}
			else
			{
				if ( LCP[rmq( M+1, R )] >= r )
					m = r + lcp ( text, SA[M] + r, pattern, r );
				else
					m = LCP[rmq( M+1, R )];
			}
			if ( m == P )
			{
				found_flag = 1;
				int E = M;
				while ( L+1 < E )
				{
					int J = (L+E)/2;
					if ( LCP[rmq( J+1, E )] < P )
						L = J;
					else
						E = J;
				}
				if ( LCP[rmq( L+1, E )] >= P )
					L = max ( L, 0 );
				else
					L = L+1;
				E = M;
				while( E + 1 < R )
				{
					int J = (E+R)/2;
					if ( LCP[rmq (E+1, J)] < P )
						R = J;
					else
						E = J;
				}
				if ( LCP[rmq (E+1,R)] >= P )
					R = min ( R, N-1 );
				else
					R = R-1;
				break;
			}				
			else if	( pattern[m] <= text[SA[M]+m] ) 
			{
				R = M;
				r = m;
			}
			else
			{
				L = M;
				l = m;
			}
		}
	}
	if ( found_flag )
	{
		for ( int i = L; i <= R; i++ )
		{
			if ( ME[SA[i]] >= P )
			{
				Occ.push_back ( SA[i]%(n+1) );
			}
		}
		Occ.sort();
		Occ.unique();
	}
#endif
	return Occ.size();
}




	

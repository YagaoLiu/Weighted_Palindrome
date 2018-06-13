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

#include <string>
#include <list>

#include <sdsl/rmq_support.hpp>

using namespace std;
using namespace sdsl;

#ifndef TSWITCH_H
#define TSWITCH_H

struct TSwitch
{
	double z;
	string text_file_name;
	string pattern_file_name;
	string output_file_name;
};

#endif


int decode_switches ( int argc, char * argv[], TSwitch * sw );
void usage ( void );
int read ( string filename, double *** text, int * n );
int read_pattern ( string filename, string * pattern, int * m );
int * LCParray ( unsigned char * text, int n, int * SA, int * ISA );
void maximal_check ( string & sq, double ** text, double z, int n, int * ME );
void SA_LCP_index ( double ** text, unsigned char * sq, int N, int n, double z, int * SA, int * iSA, int * LCP);
void maximal_palindrome ( int N, int n, double z, int * SA, int * iSA, int * LCP, rmq_succinct_sct<> & rmq, int * ME, int *MP );	
void FunctionWMPD(int * MP, int n, deque<int>& decomposition);
void FunctionWMPA(int * MP, int n);

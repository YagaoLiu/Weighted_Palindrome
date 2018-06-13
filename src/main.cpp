/**
 *    Weighted Index
 *    Copyright (C) 2017 Carl Barton, Tomasz Kociumaka, Chang Liu, Solon P. Pissis and Jakub Radoszewski.
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#include <iostream>
#include <fstream>
#include <string>
#include <set>

#include "input.h"
#include "weighted_sequence.h"

using namespace std;

int main (int argc, char ** argv ) {
    Settings st = decode_switches(argc, argv);
#if 0
    istream& text = st.text.is_open()?st.text:cin;
    istream& patterns = st.patterns.is_open()?st.patterns:cin;
    ostream& output = st.output.is_open()?st.output:cout;
#endif
	ifstream text ( st.text );
	ifstream patterns ( st.patterns );
	ofstream output ( st.output, ios::app );
    
    WeightedSequence W;
    text >> W;
    
    W.build_index(st.z, st.quiet, output);
        
    while ( true )  {
        string pattern;
        if (!(patterns >> pattern)) break;
        output << pattern << ": ";
        if (!W.contains(pattern)) {
            output << "Not found\n";
        } else {
            for (auto p : W.occurrences(pattern)) {
                output << p << " ";
            }
            output << endl;
        }
    }
    return 0;
}


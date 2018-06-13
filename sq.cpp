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
#include <fstream>
#include <cmath>
#include <string>
#include <iomanip>
#include <map>
#include <queue>
#include "node.h"

using namespace std;

char alphabet[4] = {'A', 'C', 'G', 'T'};
map < int, Node* > token_map;
vector < string > sq;
vector <int> heavy_string;

void heavy_position ( double ** text, vector<int> &heavy_string, int pos )
{
	int heavy_letter = 0;
	double max = text[pos][0];
	for ( int i = 1; i < 4; i++ )
	{
		if ( max < text[pos][i] )
		{
			max = text[pos][i];
			heavy_letter = i;
		}
	}
	heavy_string[pos] = heavy_letter;
}

void token_track ( Node * token_node, Node * ancestor_node, string& token_sq )
{
	Node * track = token_node;
	while ( track != ancestor_node && track != NULL )
	{
		token_sq[track->parent->pos] = alphabet[track->edge];
		for ( int i = track->parent->pos+1; i < track->pos; i++ )
			token_sq[i] = alphabet[heavy_string[i]];
		track = track->parent;
	}
}

void breadth_first_track ( Node * root, vector < Node * > *bft_nodes )
{
	queue < Node * > q;
	if ( !root ) { return; }
	for ( q.push( root ); !q.empty(); q.pop() )
	{
		Node * temp_node = q.front();
		if ( temp_node->token.size() )
			bft_nodes->push_back ( temp_node );
		for ( unsigned int i = 0; i < temp_node->child.size(); i++ )
			q.push( temp_node->child[i] );
	}
}

void token_request ( Node * root )
{	
	vector < Node * > bft_nodes;
	breadth_first_track ( root, &bft_nodes );
	for ( bft_nodes.back(); !bft_nodes.empty(); bft_nodes.pop_back() )
	{
		Node * T = bft_nodes.back();
		for ( unsigned int i = 0; i < T->token.size(); i++ )
		{
			if ( T->coreNode )
			{
				if ( T->coreNode->token.size() )
				{
					T->token[i] = T->coreNode->token[0];
					T->coreNode->token.erase ( T->coreNode->token.begin() );
				}
				else
				{
					T->token[i] = T->coreNode->subToken();
				}
			   	token_track ( token_map[T->token[i]], T->coreNode, sq[T->token[i]]);
				token_map[T->token[i]] = T;
			}
		}

	}
}

void root_token ( double z, Node * new_root, Node * root ) 
{	
	int parent_token = floor ( new_root->odds * z );
	int child_token = 0;
	for ( unsigned int i = 0; i < new_root->child.size(); i++ )
		child_token += floor ( new_root->child[i]->odds * z );
	int num_token = parent_token - child_token;
	if ( num_token )
	{
		new_root->token.resize( num_token );
		for ( int i = 0; i < num_token; i++ )
		{
			if ( root->token.size() )
			{
				new_root->token[i] = root->token[0];
				root->token.erase ( root->token.begin() );
			}
			else
			{
				new_root->token[i] = root->subToken();
			}
			token_track ( token_map[new_root->token[i]], root, sq[new_root->token[i]] );
			token_map[new_root->token[i]] = new_root;
		}
	}
}

void print_out ( Node * x )
{
	cout << x << ":\tpos:" << x->pos << " || edge:" << x->edge << " || parent:" << x->parent<< " || probablity:" << x->odds;
	if ( x->token.size() )
	{
		cout << "\ttoken: ";
		for ( unsigned int i = 0; i < x->token.size(); i++ )
			cout << x->token[i] << " ";
	}
	else
		cout << "\tno token.";
	cout << endl;
	if ( x->child.size() )
	{
		for ( unsigned int i = 0; i < x->child.size(); i++ )
			print_out ( x->child[i] );
	}
}

void weighted_index_building( double ** text, int n, double z, string * sq_return )
{
	heavy_string.resize(n);
	for ( int i = 0; i < n; i++ )
	{
		heavy_position ( text, heavy_string, i );
	}		

	Node ** tree;
	tree = new Node * [2];
	tree[0] = new Node;
	tree[0]->parent = NULL;
	tree[0]->odds = 1;
	tree[0]->pos = n;
	tree[0]->token.resize ( floor(z) );
	sq.resize ( floor(z) );
	for ( int i = 0; i < z; i++ )
	{
		sq[i].resize(n, 'N');
	}

	for ( int t = 0; t < floor(z); t++ )
	{
		tree[0]->token[t] = t;
		token_map[t] = tree[0];
	}

	int i = n - 1;
	while ( i>= 0 )
	{
		tree[1] = new Node;
		tree[1]->parent = NULL;
		tree[1]->odds = 1;
		tree[1]->pos = i;
		for ( int j = 0; j < 4; j++ )
		{
			if ( text[i][j] >= 1/z )
			{
				Node * branch = new Node;
				branch->Copy ( tree[0] );
				branch->parent = tree[1];
				branch->odds = text[i][j];
				branch->edge = j ;
				tree[1]->child.push_back( branch );
				tree[1]->child.back()->Update( text[i][j], z );
			}
		}
		tree[1]->Compact( 0 );
#if 1
		token_request ( tree[1] );
		root_token( z, tree[1], tree[0] );
//		for ( unsigned int t = 0; t < tree[1]->token.size(); t++ )
//		{
//			int l = ( n- i ) - sq[tree[1]->token[t]].size();
//			if ( l > 0 )
//				sq[tree[1]->token[t]].insert ( sq[tree[1]->token[t]].begin(), l, 'N' );
//		}
#endif
		swap ( tree[0], tree[1] );	
		tree[1]->deleteNode();
		i--;
	//	print_out(tree[0]);
	//	cout << "=====================================================" << endl;
	}

#if 1 
	for ( int j = 0; j < z; j++ )
	{
	    token_track(token_map[j], tree[0], sq[j] );
//		sq[j].insert ( 0, temp );
	}
	for ( int j = 0; j < z; j++ )
	{
			if ( sq[j].size() != 0 )
			{
				sq_return->append( sq[j] );
//				sq_return->push_back ( '#' );
			}
	}
//	sq_return->back() = '$';
#endif
	tree[0]->deleteNode();
	delete[] tree;
	heavy_string.clear();
	vector<int>().swap ( heavy_string );
}


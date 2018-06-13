#include <iostream>
#include <math.h>
#include <deque>
#include <forward_list>
#include <vector>
#include <stack>

using namespace std;

struct node{
	int pos;
	vector <node*> pathes;
	bool visited = false;
	node * pred = NULL;
	void print()
	{
		cout << pos << ':';
		for ( auto i : pathes )
		{
			cout << i->pos << ' ';
		}
		cout << endl;
	}
};

ostream& operator << (ostream& out, deque<deque<int>> const& X )
{
	for ( auto i : X ){
		for ( auto j : i )
			out << j << ' ';
		out << endl;
	}
	return out;
}

void FunctionWMPD(int * MP, int MP_size, deque<int>& decomposition){
	int n = int(MP_size/2) + 1;
	vector<vector<int>> F(n);
	vector<vector<int>> U(n);
	for ( int i = 0; i < MP_size; i++ )
	{
		int end = int((i+MP[i])/2);
		F[end].push_back ( MP[i] );
		U[end].push_back ( end-MP[i] );
	}
//	cout << F << endl;
//	cout << U << endl;
#if 1
	vector<node*> V(n+1);
	V[n] = new node;
	V[n]->pos = -1;
	for ( int i = 0; i < n; i++ )
	{
		V[i] = new node;
		V[i]->pos = i;
		for ( int j : U[i] )
		{
			if ( j == -1 )
				V[i]->pathes.push_back( V[n] );
			else
				V[i]->pathes.push_back( V[j] );
		}
	}

	deque<node*> s;
	s.push_back( V[n-1] );

//	cout << "Traveral:" << endl;
	while ( !s.empty() )
	{
		node * cur = s[0];
		if ( cur->pos == -1 )
			break;
		s.pop_front();
		for ( auto it : cur->pathes )
		{
			if ( !it->visited )
			{
				it->visited = true;
				it->pred = cur;
				s.push_back(it);
			}
		}
	}
	
	node * cur = V[n];
	while ( cur )
	{
		decomposition.push_back ( cur->pos );
		cur = cur->pred;
	}
	decomposition.pop_front();
#endif
}


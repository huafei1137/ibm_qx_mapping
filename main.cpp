#include <iostream>
#include <algorithm>
#include <string.h>
#include <set>
#include <climits>
#include <fstream>
#include "QASMparser.h"
#include "unique_priority_queue.h"
#include<tr1/unordered_map>
#include <list>
#include <map>
#include <ctime> 
#define LOOK_AHEAD 1
#define HEURISTIC_ADMISSIBLE 0
#define USE_INITIAL_MAPPING 0
#define MINIMAL_OUTPUT 0
#define DUMP_MAPPED_CIRCUIT 1

#define ARCH_LINEAR_N 0
#define ARCH_IBM_QX5 1

#ifndef ARCH
// assume default architecture
#define ARCH ARCH_LINEAR_N
#endif


int** dist;
int positions;
unsigned long ngates = 0;
unsigned int nqubits = 0;
int maxx = INT_MIN;
int minx = INT_MAX;
int maxy= INT_MIN;
int miny = INT_MAX;


const int qubitdistance = 1;
const char Mygatenum[5][128] = { "U(1.570796, 0.000000, 3.141593)",
"U(0.000000, 0.000000, 3.141593)",
"U(0.000000, 0.000000, 0.785398)",
"U(3.141593, 0.000000, 3.141593)",
"U(0.000000, 0.000000, 1.570796)",
};
const int Mygatetime[7] = { 9+qubitdistance ,1,1,1,1,2 * qubitdistance + 3,1};
std::vector<int> MyTimelookup;
std::vector<int> MyTimelookup2;
std::vector<int> MyTimelookup3;
std::vector<int> MyTimelookupf;
std::vector<int> MyTimelookupl;
std::vector<int> MyTimelookupini;
std::vector<int> MapMetis;
struct Point
{
	int x;
	int y;
	int Pindex;
	bool operator < (const Point& p) const
	{
		if(x == p.y && y == p.x) {
			return 0;
		}
		else if (x == p.x) {
			return y < p.y;
		}
		else {
			return x < p.x;
		}
	}
};
struct queuenode
{
	Point pt;  // The cordinates of a cell 
	int dist;  // cell's distance of from the source 
};
int rowNum[] = { -1, 0, 0, 1 };
int colNum[] = { 0, -1, 1, 0 };
int rowN[] = { 0,0,1,1 };
int colN[] = { 0,1,0,1 };
std::tr1::unordered_map<int, int> m2; 
  
// Used for sorting by frequency. And if frequency is same, 
// then by appearance 
bool sortByVal(const std::pair<int, int>& a, const std::pair<int, int>& b) 
{ 
    // If frequency is same then sort by index 
    if (a.second == b.second)  
        return m2[a.first] < m2[b.first]; 
      
    return a.second > b.second; 
} 
  
// function to sort elements by frequency 
 std::vector<std::pair<int, int> > sortByFreq(int a[], int n) 
{ 
    std::tr1::unordered_map<int, int> m; 
    std::vector<std::pair<int, int> > v; 
    
    for (int i = 0; i < n; ++i) { 
  
        // Map m is used to keep track of count  
        // of elements in array 
        m[a[i]]++; 
  
        // Update the value of map m2 only once 
        if (m2[a[i]] == 0)  
            m2[a[i]] = i + 1;         
    } 
  
    // Copy map to vector 
    copy(m.begin(), m.end(), back_inserter(v)); 
  	
    // Sort the element of array by frequency 
    sort(v.begin(), v.end(), sortByVal); 
  
   // for (int i = 0; i < v.size(); ++i){  
     //    std::cout << v[i].first << " and it appears "<<v[i].second<<"times"<<std::endl;  
         
   //  }
     return v;
} 
bool isValid(int row, int col,int Mysize, int Mycolum)
{
	// return true if row number and column number 
	// is in range 
	return (row >= 0) && (row < Mysize) &&
		(col >= 0) && (col < Mycolum);
}
void myreset(int** p,int Mysize, int Mycolum) {
	for (int i = 0; i < Mysize; i++) {
		for (int j = 0; j < Mycolum; j++) {
			p[i][j] = 0;

		}

	}

}
int** reset( int Mysize, int Mycolum) {
	int **p = new int* [Mysize];

	for (int i = 0; i<Mysize; i++)
	{
		p[i] = new int[Mycolum];
	}


	for (int i = 0; i < Mysize; i++) {
		for (int j = 0; j < Mycolum; j++) {
			p[i][j] = 0;

		}

	}

	return p;
}

void showres(int** p,int Mysize,int Mycolum) {
	for (int i = 0; i < Mysize; i++) {
		for (int j = 0; j < Mycolum; j++) {
			std::cout << p[i][j] << '\t';
		}
		//std::cout << std::endl;
	}
}

int BFS(int** mat, Point src, Point dest,int Mysize,int Mycolum) //arbitrary find the start point top-right
{
	// check source and destination cell 
	// of the matrix have value 1 
	if (mat[src.x][src.y] == -1 || mat[dest.x][dest.y] == -1) { return -1; }
	bool visited[Mysize][Mycolum];
	memset(visited, false, sizeof visited);

	// mark the source cell as visited 
	visited[src.x][src.y] = true;

	// create a queue for bfs 
	std::queue<queuenode> q;

	// distance of source cell is 0 
	queuenode s = { src, 0 };
	q.push(s);  // enqueue source cell 
	std::vector<Point> Gpt;
	int Msize = 0;
	// do a bfs starting from source cell 
	while (!q.empty())
	{

		queuenode curr = q.front();
		Point pt = curr.pt;
		Gpt.push_back(pt);//earse this and make sure it no longer needed

		Point Myp = pt;
		// if we have reached the destination cell, 
		// we are done 
		if (pt.x == dest.x && pt.y == dest.y) {
			return curr.dist;
		}


		// otherwise dequeue the front cell in the queue 
		// and enqueue its adjacent cells 
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int row = pt.x + rowNum[i];
			int col = pt.y + colNum[i];
			// if adjacent cell is valid, has path and 
			// not visited yet, enqueue it. 
			if (isValid(row, col,Mysize,Mycolum) && ((mat[row][col] == 0) || (row == dest.x && col == dest.y)) &&
				!visited[row][col])
			{
				// mark cell as visited and enqueue it 
				visited[row][col] = true;

				queuenode adjcell = { { row, col,Msize },
					curr.dist + 1 };

				q.push(adjcell);
			}
		}
		Msize++;
	}

	//return -1 if destination cannot be reached 
	return -1;
}
int BFSroute(int** mat, Point src, Point dest,int Mysize,int Mycolum)
{
	// check source and destination cell 
	// of the matrix have value 1 
	if (mat[src.x][src.y] == -1 || mat[dest.x][dest.y] == -1) { return -1; }
	bool visited[Mysize][Mycolum];
	memset(visited, false, sizeof visited);

	// mark the source cell as visited 
	visited[src.x][src.y] = true;

	// create a queue for bfs 
	std::queue<queuenode> q;

	// distance of source cell is 0 
	queuenode s = { src, 0 };
	q.push(s);  // enqueue source cell 
	std::vector<Point> Gpt;
	int Msize = 0;
	// do a bfs starting from source cell 
	while (!q.empty())
	{
		queuenode curr = q.front();
		Point pt = curr.pt;
		Gpt.push_back(pt);

		Point Myp = pt;
		// if we have reached the destination cell, 
		// we are done 
		if (pt.x == dest.x && pt.y == dest.y) {
			mat[pt.x][pt.y] = -1;
			int temp = pt.Pindex;
			while (temp > -1) {
				if (mat[Gpt[temp].x][Gpt[temp].y] == 0) {
					mat[Gpt[temp].x][Gpt[temp].y] = -1;
				}
				temp = Gpt[temp].Pindex;
			}
			return curr.dist;
		}


		// otherwise dequeue the front cell in the queue 
		// and enqueue its adjacent cells 
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int row = pt.x + rowNum[i];
			int col = pt.y + colNum[i];
			// if adjacent cell is valid, has path and 
			// not visited yet, enqueue it. 
			if (isValid(row, col,Mysize,Mycolum) && ((mat[row][col] == 0) || (row == dest.x && col == dest.y)) &&
				!visited[row][col])
			{
				// mark cell as visited and enqueue it 
				visited[row][col] = true;

				queuenode adjcell = { { row, col,Msize },
					curr.dist + 1 };

				q.push(adjcell);
			}
		}
		Msize++;
	}

	//return -1 if destination cannot be reached 
	return -1;
}


struct edge {
	int v1;
	int v2;
};
struct Mynode{
	int indegree;
	std::vector<int> nei;
	int index;
	int Myc;
	int Myt;
	int MycI;
	int MytI;
	int Mygatetype;
	int Mygatetime;
	int distance;
	int layers;
    int nodes;
    bool border;
	bool operator <(const Mynode& d)
	{
		if (nodes > d.nodes)
		{
			return true;
		}else if(nodes == d.nodes) {
			if(nodes == 2 ) {
 				if(d.border == false && border == true) {
 					return false;
 				}
 				if(border == false && d.border == true) {
 					return true;
 				}

			}
			if(distance > d.distance) {
				return true;
			}
			return false;
		}else{
		
		return false;
	    }
	}
};
struct LessThanByDistance
{
	bool operator()(const Mynode& lhs, const Mynode& rhs) const
	{
		return lhs.distance > rhs.distance;
	}
};
int modifiedBFS(int** mat, Point src, Point dest, int Mysize, int Mycolum)
{
	// check source and destination cell 
	// of the matrix have value 1 
	if ((mat[src.x][src.y] == -1 && mat[src.x + 1][src.y] == -1 && mat[src.x][src.y + 1] == -1 && mat[src.x + 1][src.y + 1] == -1) || (mat[dest.x][dest.y] == -1 && mat[dest.x + 1][dest.y] == -1 && mat[dest.x][dest.y + 1] == -1 && mat[dest.x + 1][dest.y + 1] == -1)) { return -1; }
	bool visited[Mysize][Mycolum];
	memset(visited, false, sizeof visited);
	// mark the source cell as visited 
	visited[src.x][src.y] = true;

	// create a queue for bfs 
	std::queue<queuenode> q;

	// distance of source cell is 0 
	queuenode s = { src, 0 };
	queuenode s2 = { { src.x + 1,src.y,src.Pindex }, 0 };
	queuenode s3 = { { src.x ,src.y + 1,src.Pindex }, 0 };
	queuenode s4 = { { src.x + 1,src.y + 1,src.Pindex }, 0 };
	if (mat[src.x][src.y] != -1) q.push(s);  // enqueue source cell 
	if (mat[src.x + 1][src.y] != -1)q.push(s2);
	if (mat[src.x][src.y + 1] != -1)q.push(s3);
	if (mat[src.x + 1][src.y + 1] != -1)q.push(s4);
	std::vector<Point> Gpt;
	int Msize = 0;
	// do a bfs starting from source cell 
	while (!q.empty())
	{
		queuenode curr = q.front();
		Point pt = curr.pt;
		Gpt.push_back(pt);

		Point Myp = pt;
		// if we have reached the destination cell, 
		// we are done 
		if ((pt.x == dest.x && pt.y == dest.y && mat[dest.x][dest.y] != -1) || (pt.x == dest.x + 1 && pt.y == dest.y && mat[dest.x + 1][dest.y] != -1) || (pt.x == dest.x && pt.y == dest.y + 1 && mat[dest.x][dest.y + 1] != -1) || (pt.x == dest.x + 1 && pt.y == dest.y + 1 && mat[dest.x + 1][dest.y + 1] != -1)) {
			mat[pt.x][pt.y] = -1;
			int temp = pt.Pindex;
			while (temp > -1) {
				if (mat[Gpt[temp].x][Gpt[temp].y] >= 0) {
					mat[Gpt[temp].x][Gpt[temp].y] = -1;
				}
				temp = Gpt[temp].Pindex;
			}
			return curr.dist;
		}


		// otherwise dequeue the front cell in the queue 
		// and enqueue its adjacent cells 
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int row = pt.x + rowNum[i];
			int col = pt.y + colNum[i];
			// if adjacent cell is valid, has path and 
			// not visited yet, enqueue it. 
			if (isValid(row, col, Mysize, Mycolum) && (mat[row][col] >= 0) &&
				!visited[row][col])
			{
				// mark cell as visited and enqueue it 
				visited[row][col] = true;

				queuenode adjcell = { { row, col,Msize },
					curr.dist + 1 };

				q.push(adjcell);
			}
		}
		Msize++;
	}

	//return -1 if destination cannot be reached 
	return -1;
}

bool modifiedschedule(Mynode cur, int** p,int xqubit, int yqubit) {
	int res;
	//std::cout << s << "    " << e << std::endl;
	if (cur.Myc == -1) return true;
	int s = cur.Myc;
	int e = cur.Myt;
	int yindex = (s % xqubit);
	int xindex = (s / xqubit);

	int eyindex = (e % xqubit);
	int exindex = (e / xqubit);

	Point ss = { xindex,yindex,-1 };
	Point ee = { exindex,eyindex };

	res = modifiedBFS(p, ss, ee,xqubit+1,yqubit+1);
	if (res != -1) {
		//std::cout << "the shortest path length is  " << res<< std::endl;
		return true;
	}
	else {
		//std::cout << "can not find the path" << std::endl;
		return false;
	}


}
bool modifiedschedulewithinitial(Mynode cur, int** p,int xqubit, int yqubit) {
	int res;
	//std::cout << s << "    " << e << std::endl;
	if (cur.Myc == -1) return true;
	int s = cur.MycI;
	int e = cur.MytI;
	int yindex = (s % xqubit);
	int xindex = (s / xqubit);

	int eyindex = (e % xqubit);
	int exindex = (e / xqubit);

	Point ss = { xindex,yindex,-1 };
	Point ee = { exindex,eyindex };

	res = modifiedBFS(p, ss, ee,xqubit+1,yqubit+1);
	if (res != -1) {
		//std::cout << "the shortest path length is  " << res<< std::endl;
		return true;
	}
	else {
		//std::cout << "can not find the path" << std::endl;
		return false;
	}


}
bool checkparrallel(Mynode cur, int** p,int xqubit, int yqubit) {
	int res = -1;
	Point startpoint;
	Point endpoint;
	if (cur.Myc == -1) return true;
	int ss = cur.Myc; int ee = cur.Myt;
	//std::cout << "start point is  " << ss<<"end point is "<<ee << std::endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int yindex = (ss % xqubit) + colN[i];
			int xindex = (ss / xqubit) + rowN[i];		
			int eyindex = (ee % xqubit) + colN[j];
			int exindex = (ee / xqubit) + rowN[j];
			Point s = { xindex,yindex,-1 };
			Point e = { exindex,eyindex };
			int BFSres = BFS(p, s, e,xqubit+1,yqubit+1);
			if (BFSres != -1) {
				if (res == -1) {
					res = BFSres;
					startpoint = s;
					endpoint = e;
				}
				else if (BFSres < res) {
					res = std::min(res, BFSres);
					startpoint = s;
					endpoint = e;
				}
			}


		}
	}
	if (res != -1) {
		//std::cout << "the shortest path length is  " << BFSroute(p, startpoint, endpoint,xqubit+1,yqubit+1) << std::endl;
		BFSroute(p, startpoint, endpoint,xqubit+1,yqubit+1);
		return true;
	}
	else {
		//std::cout << "can not find the path" << std::endl;
		return false;
	}
	
}
bool checkparrallelwithmetis(Mynode cur, int** p,int xqubit, int yqubit) {
	int res = -1;
	Point startpoint;
	Point endpoint;
	if (cur.Myc == -1) return true;
	int ss = MapMetis[cur.Myc]; int ee = MapMetis[cur.Myt];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int yindex = (ss % xqubit) + colN[i];
			int xindex = (ss / xqubit) + rowN[i];		
			int eyindex = (ee % xqubit) + colN[j];
			int exindex = (ee / xqubit) + rowN[j];
			Point s = { xindex,yindex,-1 };
			Point e = { exindex,eyindex };
			int BFSres = BFS(p, s, e,xqubit+1,yqubit+1);
			if (BFSres != -1) {
				if (res == -1) {
					res = BFSres;
					startpoint = s;
					endpoint = e;
				}
				else if (BFSres < res) {
					res = std::min(res, BFSres);
					startpoint = s;
					endpoint = e;
				}
			}


		}
	}
	if (res != -1) {
		//std::cout << "the shortest path length is  " << BFSroute(p, startpoint, endpoint,xqubit+1,yqubit+1) << std::endl;
		return true;
	}
	else {
		//std::cout << "can not find the path" << std::endl;
		return false;
	}
	
}
bool checkwithanothermodel(Mynode cur, int** p,int xqubit, int yqubit) {
	int res = -1;
	Point startpoint;
	Point endpoint;
	if (cur.Myc == -1) return true;
	int ss = cur.Myc; int ee = cur.Myt;
	
	int yindex = (ss % xqubit) ;
	int xindex = (ss / xqubit) ;		
	int eyindex = (ee % xqubit) ;
	int exindex = (ee / xqubit) ;
	Point s = { xindex,yindex,-1 };
	Point e = { exindex,eyindex };
	int BFSres = BFS(p, s, e,xqubit+1,yqubit+1);
	if (BFSres != -1) {
		if (res == -1) {
			res = BFSres;
			startpoint = s;
			endpoint = e;
		}
		else if (BFSres < res) {
			res = std::min(res, BFSres);
			startpoint = s;
			endpoint = e;
		}
	}
	if (res != -1) {
		//std::cout << "the shortest path length is  " << BFSroute(p, startpoint, endpoint,xqubit+1,yqubit+1) << std::endl;
		return true;
	}
	else {
		//std::cout << "can not find the path" << std::endl;
		return false;
	}
	
}
bool checklinear(Mynode cur, int** p,int xqubit, int yqubit) {
	int res = -1;
	Point startpoint;
	Point endpoint;
	if (cur.Myc == -1) return true;
	int ss = cur.Myc; int ee = cur.Myt;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int yindex = (ss % xqubit) + colN[i];
			int xindex = (ss / xqubit) + rowN[i];
			if(xindex % 2 != 0) {
				yindex = std::abs(yqubit - 1 - xindex);
			}
			int eyindex = (ee % xqubit) ;
			int exindex = (ee / xqubit) ;
			if(exindex % 2 != 0) {
				eyindex = std::abs(yqubit - 1 - eyindex);
			}		
			Point s = { xindex,yindex,-1 };
			Point e = { exindex,eyindex };
			int BFSres = BFS(p, s, e,xqubit+1, yqubit+1);
			if (BFSres != -1) {
				if (res == -1) {
					res = BFSres;
					startpoint = s;
					endpoint = e;
				}
				else if (BFSres < res) {
					res = std::min(res, BFSres);
					startpoint = s;
					endpoint = e;
				}
			}


		}
	}
	if (res != -1) {
		//std::cout << "the shortest path length is  " << BFSroute(p, startpoint, endpoint,xqubit+1,yqubit+1) << std::endl;
		return true;
	}
	else {
		//std::cout << "can not find the path" << std::endl;
		return false;
	}
	
}


	


inline bool operator<(const edge& lhs, const edge& rhs) {
	if (lhs.v1 != rhs.v1) {
		return lhs.v1 < rhs.v1;  //here is we inline(which is faster) overload the operator < for edge
	}                                       
	return lhs.v2 < rhs.v2;
}

struct node {
	int cost_fixed;
	int cost_heur;
	int cost_heur2;
	int depth;
	int* qubits; // get qubit of location -> -1 indicates that there is "no" qubit at a certain location
	int* locations; // get location of qubits -> -1 indicates that a qubit does not have a location -> shall only occur for i > nqubits
	int nswaps;
	int done;
	std::vector<std::vector<edge>> swaps;
};

struct node_func_less {
	// true iff x < y
	bool operator()(const node& x, const node& y) const {
		for(int i=0; i < positions; i++) {
			if (x.qubits[i] != y.qubits[i]) {
				return x.qubits[i] < y.qubits[i];
			}
		}
		return false;
	}
};

struct node_cost_greater {
	// true iff x > y
	bool operator()(const node& x, const node& y) const {
		if ((x.cost_fixed + x.cost_heur + x.cost_heur2) != (y.cost_fixed + y.cost_heur + y.cost_heur2)) {
			return (x.cost_fixed + x.cost_heur + x.cost_heur2) > (y.cost_fixed + y.cost_heur + y.cost_heur2);
		}

		if(x.done == 1) {
			return false;
		}
		if(y.done == 1) {
			return true;
		}

		if (x.cost_heur + x.cost_heur2 != y.cost_heur + y.cost_heur2) {
			return x.cost_heur + x.cost_heur2 > y.cost_heur + y.cost_heur2;
		} else {
			return node_func_less{}(x, y);
		}

	}
};

struct cleanup_node {
	void operator()(const node& x) {
		delete[] x.qubits;
		delete[] x.locations;
	}
};

std::set<edge> graph;
std::vector<std::vector<QASMparser::gate> > layers;
unique_priority_queue<node, cleanup_node, node_cost_greater, node_func_less> nodes;


void build_graph_NN(int nqubits) {
	graph.clear();
	positions = 16;

    edge e;
    for(int i = 0; i < nqubits-1; i++) {
        e.v1 = i;
        e.v2 = i+1;
        graph.insert(e);
        e.v1 = i+1;
        e.v2 = i;
        graph.insert(e);
    }
}


//build a graph representing the coupling map of IBM QX5
void build_graph_QX5() {
	graph.clear();
	positions = 16;
	edge e;
	e.v1 = 1;
	e.v2 = 0;
	graph.insert(e);
	e.v1 = 1;
	e.v2 = 2;
	graph.insert(e);
	e.v1 = 2;
	e.v2 = 3;
	graph.insert(e);
	e.v1 = 3;
	e.v2 = 14;
	graph.insert(e);
	e.v1 = 3;
	e.v2 = 4;
	graph.insert(e);
	e.v1 = 5;
	e.v2 = 4;
	graph.insert(e);
	e.v1 = 6;
	e.v2 = 5;
	graph.insert(e);
	e.v1 = 6;
	e.v2 = 11;
	graph.insert(e);
	e.v1 = 6;
	e.v2 = 7;
	graph.insert(e);
	e.v1 = 7;
	e.v2 = 10;
	graph.insert(e);
	e.v1 = 8;
	e.v2 = 7;
	graph.insert(e);
	e.v1 = 9;
	e.v2 = 8;
	graph.insert(e);
	e.v1 = 9;
	e.v2 = 10;
	graph.insert(e);
	e.v1 = 11;
	e.v2 = 10;
	graph.insert(e);
	e.v1 = 12;
	e.v2 = 5;
	graph.insert(e);
	e.v1 = 12;
	e.v2 = 11;
	graph.insert(e);
	e.v1 = 12;
	e.v2 = 13;
	graph.insert(e);
	e.v1 = 13;
	e.v2 = 4;
	graph.insert(e);
	e.v1 = 13;
	e.v2 = 14;
	graph.insert(e);
	e.v1 = 15;
	e.v2 = 0;
	graph.insert(e);
	e.v1 = 15;
	e.v2 = 14;
	graph.insert(e);
	e.v1 = 15;
	e.v2 = 2;
	graph.insert(e);
}

void build_graph_linear(int qubits) {
    graph.clear();
    positions = qubits;

    for(int i = 0; i < qubits-1; i++) {
        graph.insert(edge{i, i+1});
        graph.insert(edge{i+1, i});
    }
}

bool contains(const std::vector<int>& v, const int e) {
    return std::find(v.begin(), v.end(), e) != v.end();
}

//Breadth first search algorithm to determine the shortest paths between two physical qubits
int bfs(const int start, const int goal, const std::set<edge>& graph) {
    std::queue<std::vector<int>> queue;
    std::vector<int> v;
	v.push_back(start);
	queue.push(v);
    std::vector<std::vector<int>> solutions;

	unsigned long length = 0;
	std::set<int> successors;
	while (!queue.empty()) {
		v = queue.front();
		queue.pop();
		int current = v[v.size() - 1];
		if (current == goal) {
			length = v.size();
			solutions.push_back(v);
			break;
		} else {
			successors.clear();
			for (const auto edge : graph) {
                if (edge.v1 == current && !contains(v, edge.v2)) {
					successors.insert(edge.v2);
				}
				if (edge.v2 == current && !contains(v, edge.v1)) {
					successors.insert(edge.v1);
				}
			}
			for (int successor : successors) {
                std::vector<int> v2 = v;
				v2.push_back(successor);
				queue.push(v2);
			}
		}
	}
	while (!queue.empty() && queue.front().size() == length) {
		if (queue.front()[queue.front().size() - 1] == goal) {
			solutions.push_back(queue.front());
		}
		queue.pop();
	}

	for (auto v : solutions) {
        for (int j = 0; j < v.size() - 1; j++) {
			edge e{v[j], v[j + 1]};
			if (graph.find(e) != graph.end()) {
				return (length-2)*7;
			}
		}
	}

	return (length - 2)*7 + 4;
}

void build_dist_table(const std::set<edge>& graph) {
	dist = new int*[positions];

	for (int i = 0; i < positions; i++) {
		dist[i] = new int[positions];
	}

	for (int i = 0; i < positions; i++) {
		for (int j = 0; j < positions; j++) {
			if (i != j) {
				dist[i][j] = bfs(i,j,graph);
			} else {
				dist[i][i] = 0;
			}
		}
	}
}

void expand_node(const std::vector<int>& qubits, unsigned int qubit, edge *swaps, int nswaps,
				 int* used, node base_node, const std::vector<QASMparser::gate>& gates, int** dist, int next_layer) {

	if (qubit == qubits.size()) {
		//base case: insert node into queue
		if (nswaps == 0) {
			return;
		}
		node new_node;

		new_node.qubits = new int[positions];
		new_node.locations = new int[nqubits];

		memcpy(new_node.qubits, base_node.qubits, sizeof(int) * positions);
		memcpy(new_node.locations, base_node.locations, sizeof(int) * nqubits);

		new_node.swaps = std::vector<std::vector<edge> >();
		new_node.nswaps = base_node.nswaps + nswaps;
		for (std::vector<std::vector<edge> >::iterator it2 = base_node.swaps.begin();
			 it2 != base_node.swaps.end(); it2++) {
            std::vector<edge> new_v(*it2);
			new_node.swaps.push_back(new_v);
		}

		new_node.depth = base_node.depth + 5;
		new_node.cost_fixed = base_node.cost_fixed + 7 * nswaps;
		new_node.cost_heur = 0;

        std::vector<edge> new_swaps;
		for (int i = 0; i < nswaps; i++) {
			new_swaps.push_back(swaps[i]);
			int tmp_qubit1 = new_node.qubits[swaps[i].v1];
			int tmp_qubit2 = new_node.qubits[swaps[i].v2];

			new_node.qubits[swaps[i].v1] = tmp_qubit2;
			new_node.qubits[swaps[i].v2] = tmp_qubit1;

			if (tmp_qubit1 != -1) {
				new_node.locations[tmp_qubit1] = swaps[i].v2;
			}
			if (tmp_qubit2 != -1) {
				new_node.locations[tmp_qubit2] = swaps[i].v1;
			}
		}
		new_node.swaps.push_back(new_swaps);
		new_node.done = 1;

		for (std::vector<QASMparser::gate>::const_iterator it = gates.begin(); it != gates.end();
			 it++) {
			QASMparser::gate g = *it;
			if (g.control != -1) {
#if HEUR_ADMISSIBLE
				new_node.cost_heur = max(new_node.cost_heur, dist[new_node.locations[g.control]][new_node.locations[g.target]]);
#else
				new_node.cost_heur = new_node.cost_heur + dist[new_node.locations[g.control]][new_node.locations[g.target]];
#endif
				if(dist[new_node.locations[g.control]][new_node.locations[g.target]] > 4) {
					new_node.done = 0;
				}
			}
		}

		//Calculate heuristics for the cost of the following layer
		new_node.cost_heur2 = 0;
#if LOOK_AHEAD
		if(next_layer != -1) {
			for (std::vector<QASMparser::gate>::const_iterator it = layers[next_layer].begin(); it != layers[next_layer].end();
							it++) {
                QASMparser::gate g = *it;
				if (g.control != -1) {
					if(new_node.locations[g.control] == -1 && new_node.locations[g.target] == -1) {
						//No additional penalty in heuristics
					} else if(new_node.locations[g.control] == -1) {
						int min = 1000;
						for(int i=0; i< positions; i++) {
							if(new_node.qubits[i] == -1 && dist[i][new_node.locations[g.target]] < min) {
								min = dist[i][new_node.locations[g.target]];
							}
						}
						new_node.cost_heur2 = new_node.cost_heur2 + min;
					} else if(new_node.locations[g.target] == -1) {
						int min = 1000;
						for(int i=0; i< positions; i++) {
							if(new_node.qubits[i] == -1 && dist[new_node.locations[g.control]][i] < min) {
								min = dist[new_node.locations[g.control]][i];
							}
						}
						new_node.cost_heur2 = new_node.cost_heur2 + min;
					} else {
#if HEURISTIC_ADMISSIBLE
						new_node.cost_heur2 = max(new_node.cost_heur2, dist[new_node.locations[g.control]][new_node.locations[g.target]]);
#else
						new_node.cost_heur2 = new_node.cost_heur2 + dist[new_node.locations[g.control]][new_node.locations[g.target]];
#endif
					}
				}
			}
		}
#endif

		nodes.push(new_node);
	} else {
		expand_node(qubits, qubit + 1, swaps, nswaps, used, base_node, gates,
					dist, next_layer);

		for (std::set<edge>::iterator it = graph.begin(); it != graph.end(); it++) {
			edge e = *it;
			if (e.v1 == base_node.locations[qubits[qubit]]
				|| e.v2 == base_node.locations[qubits[qubit]]) {
				if (!used[e.v1] && !used[e.v2]) {
					used[e.v1] = 1;
					used[e.v2] = 1;
					swaps[nswaps].v1 = e.v1;
					swaps[nswaps].v2 = e.v2;
					expand_node(qubits, qubit + 1, swaps, nswaps + 1, used,
								base_node, gates, dist, next_layer);
					used[e.v1] = 0;
					used[e.v2] = 0;
				}
			}
		}
	}
}

unsigned int getNextLayer(unsigned int layer) {
	unsigned int next_layer = layer+1;
	while(next_layer < layers.size()) {
		for(std::vector<QASMparser::gate>::iterator it = layers[next_layer].begin(); it != layers[next_layer].end(); it++) {
			if(it->control != -1) {
				return next_layer;
			}
		}
		next_layer++;
	}
	return -1;
}

node a_star_fixlayer(int layer, int* map, int* loc, int** dist) {

	int next_layer = getNextLayer(layer);

	node n;
	n.cost_fixed = 0;
	n.cost_heur = n.cost_heur2 = 0;
	n.qubits = new int[positions];
	n.locations = new int[nqubits];
	n.swaps = std::vector<std::vector<edge> >();
	n.done = 1;

    std::vector<QASMparser::gate> v = std::vector<QASMparser::gate>(layers[layer]);
    std::vector<int> considered_qubits;

	//Find a mapping for all logical qubits in the CNOTs of the layer that are not yet mapped
	for (std::vector<QASMparser::gate>::iterator it = v.begin(); it != v.end(); it++) {
		QASMparser::gate g = *it;
		if (g.control != -1) {
			considered_qubits.push_back(g.control);
			considered_qubits.push_back(g.target);
			if(loc[g.control] == -1 && loc[g.target] == -1) {
                std::set<edge> possible_edges;
				for(std::set<edge>::iterator it = graph.begin(); it != graph.end(); it++) {
					if(map[it->v1] == -1 && map[it->v2] == -1) {
						possible_edges.insert(*it);
					}
				}
				if(!possible_edges.empty()) {
					edge e = *possible_edges.begin();
					loc[g.control] = e.v1;
					map[e.v1] = g.control;
					loc[g.target] = e.v2;
					map[e.v2] = g.target;
				} else {
                    std::cerr << "no edge available!";
                    std::exit(1);
				}
			} else if(loc[g.control] == -1) {
				int min = 1000;
				int min_pos = -1;
				for(int i=0; i< positions; i++) {
					if(map[i] == -1 && dist[i][loc[g.target]] < min) {
						min = dist[i][loc[g.target]];
						min_pos = i;
					}
				}
				map[min_pos] = g.control;
				loc[g.control] = min_pos;
			} else if(loc[g.target] == -1) {
				int min = 1000;
				int min_pos = -1;
				for(int i=0; i< positions; i++) {
					if(map[i] == -1 && dist[loc[g.control]][i] < min) {
						min = dist[loc[g.control]][i];
						min_pos = i;
					}
				}
				map[min_pos] = g.target;
				loc[g.target] = min_pos;
			}
			n.cost_heur = std::max(n.cost_heur, dist[loc[g.control]][loc[g.target]]);
		} else {
			//Nothing to do here
		}
	}

	if(n.cost_heur > 4) {
		n.done = 0;
	}

    memcpy(n.qubits, map, sizeof(int) * positions);
    memcpy(n.locations, loc, sizeof(int) * nqubits);

	nodes.push(n);

	int *used = new int[positions];
	for (int i = 0; i < positions; i++) {
		used[i] = 0;
	}
	edge *edges = new edge[considered_qubits.size()];

	//Perform an A* search to find the cheapest permutation
	while (!nodes.top().done) {
		node n = nodes.top();
		nodes.pop();

		expand_node(considered_qubits, 0, edges, 0, used, n, v, dist, next_layer);

		delete[] n.locations;
		delete[] n.qubits;
	}

	node result = nodes.top();
	nodes.pop();

	//clean up
	delete[] used;
	delete[] edges;
	while (!nodes.empty()) {
		node n = nodes.top();
		nodes.pop();
		delete[] n.locations;
		delete[] n.qubits;
	}
	return result;
}
void getboundary(std::vector<Mynode> res, int xqubit, int yqubit) {

    for(int i = 0 ; i < res.size(); i++){
    	int x = res[i].Myc /yqubit ;
    	int y = res[i].Myc %yqubit;
    	int ex = res[i].Myt /yqubit;
    	int ey= res[i].Myt % yqubit;
    	minx = std::min(ex,std::min(minx, x));
    	maxx = std::max(ex,std::max(maxx, x));
    	miny = std::min(ey,std::min(miny, y));
    	maxy = std::max(ey,std::max(maxy, y));
    }
}
int getoverlap(Mynode cur, int xqubit) {
	if(cur.Myc == -1) {
		return -1;
	}
	int res = 0;
	int a1x = cur.Myc / xqubit;
	int a1y = cur.Myc % xqubit;
	int a2x = cur.Myt / xqubit;
	int a2y = cur.Myt % xqubit;
	if(a1x == minx || a2x == minx) {res++;}
	if(a1y == miny || a2y == miny) {res++;}
	if(a1x == maxx || a2x == maxx) {res++;}
	if(a1y == maxy || a2y == maxy) {res++;}
	//if (a1x == minx || a1x == maxx) { res++; }
	//if (a1y == miny || a1y == maxy) { res++; }
	//if (a2x == minx || a2x == maxx) { res++; }
	//if (a2y == miny || a2y == maxy) { res++; }
	

	return res;


}
int Mycal(int x, int y, int size) {
	return x * size + y;

}
int getLT(int x, int size) {
	return x - size - 1;

}
int getRT(int x, int size) {
	return x - size + 1;

}
int getLB(int x, int size) {
	return x + size - 1;

}
int getRB(int x, int size) {
	return x + size + 1;

}
bool checkoverlap(int c1,int t1, int c2, int t2,int xqubit,int yqubit) {
        int x = c1 /yqubit ;
    	int y = c1 %yqubit;
    	int ex = t1 /yqubit;
    	int ey= t1 % yqubit;
    	int minx = std::min(ex, x);
    	int maxx = std::max(ex, x);
    	int miny = std::min(ey, y);
    	int maxy = std::max(ey,y);
    	 int x2 = c2 /yqubit ;
    	int y2 = c2 %yqubit;
    	int ex2 = t2 /yqubit;
    	int ey2= t2 % yqubit;
    	int minx2 = std::min(ex2, x2);
    	int maxx2 = std::max(ex2, x2);
    	int miny2 = std::min(ey2,y2);
    	int maxy2 = std::max(ey2,y2);
    	if(minx2 > maxx || maxx2 < minx || miny2 > maxy || maxy2 < miny) {
    		return false;
    	}else{
    		return true;
    	}
}

bool judgeborder(Mynode cur, int xqubit) {
	//if(cur.Myc == -1) {
	//	return -1;
	//}
	
	int a1x = cur.Myc / xqubit;
	int a1y = cur.Myc % xqubit;
	int a2x = cur.Myt / xqubit;
	int a2y = cur.Myt % xqubit;
	if((a1x == minx && a1y == miny) || (a1x == maxx && a1y == miny)||(a1x == minx && a1y == maxy) ||(a1x == maxx && a1y == maxy)) {return true;}
	
	//if (a1x == minx || a1x == maxx) { res++; }
	//if (a1y == miny || a1y == maxy) { res++; }
	//if (a2x == minx || a2x == maxx) { res++; }
	//if (a2y == miny || a2y == maxy) { res++; }
	

	return false;


}
bool comp(Mynode i, Mynode j) {
	return i.distance < j.distance;
}

int main(int argc, char** argv) {
	


#if DUMP_MAPPED_CIRCUIT
	if(argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        std::exit(1);
	}
#else
	if(argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        std::exit(1);
	}
#endif

	QASMparser* parser = new QASMparser(argv[1]);
	parser->Parse();

	layers = parser->getLayers();
	nqubits = parser->getNqubits();
	ngates = parser->getNgates();


	delete parser;






	std::vector<int> myfreq;
	std::set<int> mysetq; //calculate all cnot qubits
	int neiqubit[nqubits][nqubits];
	int initialmappingqubit[nqubits];
	//int testinitialmapping[16] = {9,11,6,12,2,7,13,3,5,1,8,14,0,4,15,10};
	for(int i = 0; i < nqubits; i++) {
		initialmappingqubit[i] = -1;
	}
	for(int i = 0; i < nqubits; i++) {
		for(int j = 0; j < nqubits; j++) {
			neiqubit[i][j] = -1;
		}

	}
	int countcnot[layers.size()];

           for(int i = 0; i < layers.size(); i++ ){
           	int tempcount=0;
		//std::cout<<"the layer is: "<<i<<std::endl;
		for(int j = 0; j <layers[i].size();j++){
			if(layers[i][j].target >= 0 && layers[i][j].control >=0 ) {
			tempcount++;
			neiqubit[layers[i][j].target][layers[i][j].control] = 1;
			neiqubit[layers[i][j].control][layers[i][j].target] = 1;
			//std::cout<<"current layer is:"<<i<<" the cnot number is"<<tempcount<<std::endl;
		}
		countcnot[i] = tempcount;
	}
}

           for(int i = 0; i < layers.size(); i++ ){

		//std::cout<<"the layer is: "<<i<<std::endl;
		for(int j = 0; j <layers[i].size();j++){
			if(layers[i][j].target >= 0 && layers[i][j].control >=0 && countcnot[i] > 3) {
				myfreq.push_back(layers[i][j].target);
				myfreq.push_back(layers[i][j].control);	
			}
			if(layers[i][j].target > 0) {
				mysetq.insert(layers[i][j].target);
				
			}
			//std::cout<<"the control qubit is:"<<layers[i][j].control<<"the target qubit is:"<<layers[i][j].target<<std::endl;
			if(layers[i][j].control > 0) {
				mysetq.insert(layers[i][j].control);
				
			}
		
			
			
		}
	}
	int arsize = myfreq.size();
	int mya[arsize]; 
	for(int i = 0; i < arsize; i++) {
		mya[i] = myfreq[i];
	}
	
	std::vector<std::pair<int, int> > arrfreq;
	arrfreq = sortByFreq(mya, arsize);
	
	int Mynumqubit = nqubits;
	int xqubit = 1;
	int yqubit = 1;
	for(int i = 2; i < Mynumqubit/2; i++) {
		if ((i*i) >= Mynumqubit){
			xqubit = i;
			yqubit = i;
			break;
		}
	}// square root.
	//std::cout << "the qubit size x is " <<xqubit<<" y is "<<yqubit<< std::endl;
	bool maprelation[nqubits];
	for(int i = 0; i < nqubits; i++) {
		maprelation[i] = true;
	}
for(int i = 0; i < arrfreq.size(); i++) {
	//	std::cout<<"the "<<i<<"th frequency number is: "<< arrfreq[i].first<<"   ";
		int curtemp =  arrfreq[i].first;
		if(i == 0) {
			initialmappingqubit[arrfreq[i].first] = Mycal(xqubit/2,xqubit/2,xqubit);
			//std::cout<<arrfreq[i].first<<"maps to "<<Mycal(xqubit/2,xqubit/2,xqubit);
			maprelation[Mycal(xqubit/2,xqubit/2,xqubit)] = false;
		}else{
			for(int j = 0; j < i; j++) {
				if(neiqubit[i][j] == 1) {
					int indextemp = initialmappingqubit[arrfreq[j].first];
					int LTindex = getLT(indextemp,xqubit);
					int RTindex = getRT(indextemp,xqubit);
					int LBindex = getLB(indextemp,xqubit);
					int RBindex = getRB(indextemp,xqubit);
					if(LTindex >=0 && LTindex < nqubits && maprelation[LTindex] == true) {
						initialmappingqubit[curtemp] = LTindex;
						//std::cout<<curtemp<<"maps to "<<initialmappingqubit[curtemp]<<"based on"<<indextemp<<"LT"<<std::endl;
						maprelation[LTindex] = false;
						break;
					}
					else if(RTindex >=0 && RTindex < nqubits &&maprelation[RTindex] == true) {
						initialmappingqubit[curtemp] = RTindex;
						//std::cout<<curtemp<<"maps to "<<initialmappingqubit[curtemp]<<"based on"<<indextemp<<"RT"<<std::endl;
						maprelation[RTindex] = false;
						break;
					}
					else if(LBindex >=0 && LBindex < nqubits &&maprelation[LBindex] == true) {
						initialmappingqubit[curtemp] = LBindex;
						//std::cout<<curtemp<<"maps to "<<initialmappingqubit[curtemp]<<"based on"<<indextemp<<"LB"<<std::endl;
						maprelation[LBindex] = false;
						break;
					}
					else if(RBindex >=0 && RBindex < nqubits &&maprelation[RBindex] == true) {
						initialmappingqubit[curtemp] = RBindex;
						//std::cout<<curtemp<<"maps to "<<initialmappingqubit[curtemp]<<"based on"<<indextemp<<"RB"<<std::endl;
						maprelation[RBindex] = false;
						break;
					}
				}

			}
			//std::cout<<arrfreq[i].first<<"maps to "<<initialmappingqubit[curtemp];

		}
		std::cout<<std::endl;
	} 
	//for(int i = 0; i < nqubits; i ++) {
	//	std::cout<<"the "<<i<<"th qubits map to" << initialmappingqubit[i]<<std::endl;
	//}





	const int Mysize = xqubit + 1;// size to row
	const int Mycolum = yqubit + 1;
	//std::cout << "\nInitial mapping of the logical qubits (q) to the physical qubits (Q) of the IBM QX5 architecture: " << std::endl;
	std::vector<std::vector<int>> Mygraph(mysetq.size() + 1); //neighor relationship +1 for?
	int Mycount = 0;
	int readtemp;
	char * arrayres = new char[40];
	int count = -1;
	for (int i = 0; argv[1][i] != '\0'; i++) {
		if (argv[1][i] == '.') break;
		if (count >= 0) {
			arrayres[count] = argv[1][i];
			count++;
		}
		if (argv[1][i] == '/') {
			count = 0;
		}
	}
	arrayres[count] = '\0';
//	std::cout << arrayres << std::endl;
	FILE* Myfp = fopen("result4.txt","r");
	while(!feof(Myfp))  
	{  
		int a,b;
		fscanf(Myfp,"(%d,%d)\n",&a,&b);
		int Myrealindex = a* xqubit + b;
		MapMetis.push_back(Myrealindex);
	}  
	std::vector<Mynode> Mystore, Mystoreinreal, Mystoreinrealbrad, Mystoreinmetis,Mystoreh,Mystorell,Mystoreini;
	
	std::cout<<"xqubit:"<<xqubit<<"yqubit:"<<yqubit<<std::endl;
	std::cout<<"total gates number:"<<ngates<<std::endl;
	if(checkoverlap(8,3,9,2,xqubit,yqubit) == true){
		std::cout<<"*************"<<std::endl;
		std::cout<<"test overlap correct"<<std::endl;
		std::cout<<"*************"<<std::endl;
	}
  std::srand ( unsigned ( std::time(0) ) );
  std::vector<int> myvector;

  // set some values:
  for (int i=0; i<xqubit*yqubit; i++) myvector.push_back(i); // 1 2 3 4 5 6 7 8 9

  // using built-in random generator:
  std::random_shuffle ( myvector.begin(), myvector.end() );

  

  // print out content:
std::cout<<"*************"<<std::endl;
  std::cout << "myvector contains:";
  for (std::vector<int>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
    std::cout << ' ' << *it;


  std::cout << '\n';
  std::cout<<"*************"<<std::endl;
  int round = 1000;
  int minimalresult=INT_MAX;
  while(round > 0){
  	int maxparallelcnots = 0;
    std::random_shuffle ( myvector.begin(), myvector.end() );

  

  // print out content:
//std::cout<<"*************"<<std::endl;
 // std::cout << "myvector contains:";
  //for (std::vector<int>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
  //  std::cout << ' ' << *it;


//  std::cout << '\n';
//  std::cout<<"*************"<<std::endl;


	for(int i = 0; i < layers.size(); i++) {
		//std::cout<<"the"<<i<<"th layer:"<<std::endl;
		int parallelcnots = 0;
		int tempnum = layers[i].size();
		for(int j = 0; j < layers[i].size(); j++) {
			int overlapcount = 0;
			//std::cout<<Mycount<<"th gate type is: "<<layers[i][j].type;
			//std::cout<<"control qubit: "<<layers[i][j].control<<"  target qubit:"<<layers[i][j].target<<std::endl;
			if(layers[i][j].control != -1) {
				for(int k = 0; k < layers[i].size(); k++) {
					if(k != j && layers[i][k].control != -1) {
						if(checkoverlap(myvector[layers[i][j].control],myvector[layers[i][j].target],myvector[layers[i][k].control],myvector[layers[i][k].target],xqubit,yqubit)) {
							overlapcount++;
						}
					}
				}
					
				
			}
			if(overlapcount > 0) overlapcount++;
			parallelcnots = std::max(parallelcnots,overlapcount);
		}
		
		maxparallelcnots = std::max(maxparallelcnots,parallelcnots);
	}
	//std::cout<<"in current round overlap number is"<<maxparallelcnots<<std::endl;
	minimalresult=std::min(minimalresult,maxparallelcnots);
	round--;
}
	
	std::cout<<"*************"<<std::endl;
	std::cout<<"maximum overlap number is"<<minimalresult<<std::endl;
	std::cout<<"*************"<<std::endl;
	int maxnumcnot = 0;
	for(int i = 0; i < layers.size(); i++) {
		//std::cout<<"the"<<i<<"th layer:"<<std::endl;
		int tempnum = layers[i].size();
		for(int j = 0; j < layers[i].size(); j++) {
		//	std::cout<<Mycount<<"th gate type is: "<<layers[i][j].type<<std::endl;
			if(layers[i][j].control < 0 || layers[i][j].target < 0 ) {
					tempnum--;
			}

			if(i == 0){
				Mynode temp;
				temp.index = Mycount;
				temp.indegree = 0;
				temp.layers = i;
				int Mc = layers[i][j].control;
				int Mt = layers[i][j].target;
				int yindex = (Mc % xqubit);
				int xindex = (Mc / xqubit);
				int yindex2 = (Mt % xqubit);
				int xindex2 = (Mt / xqubit);
				temp.distance = std::abs(yindex - yindex2) + std::abs(xindex - xindex2);
				temp.Mygatetype = 6; //for gatetype use enumurate
				if (Mc >= 0 && Mt >= 0) {
					temp.Mygatetype = 5;
				}
				else {
					for (int k = 0; k < 5; k++) {
						if (strcmp(Mygatenum[k], layers[i][j].type) == 0) {
							
							temp.Mygatetype = k;
						}
					}
				}
				
				temp.Myc = Mc;
				temp.Myt = Mt;
				temp.MycI =initialmappingqubit[Mc];
				temp.MytI = initialmappingqubit[Mt];
				temp.Mygatetime = Mygatetime[temp.Mygatetype];
				if(Mc >= 0 ){
					Mygraph[Mc].push_back(Mycount);	
				}
				if(Mt >= 0) {
					Mygraph[Mt].push_back(Mycount);
				
				}
               //f(temp.Mygatetype == 0 || temp.Mygatetype == 5){
				Mystore.push_back(temp);
				Mycount++;			
              //}
	
		}else{
				int degreetemp = 0;				
				Mynode temp;
				temp.layers = i;
				temp.index = Mycount;
				temp.Mygatetype = 6;
				int Mc = layers[i][j].control;
				int Mt = layers[i][j].target;
				int yindex = (Mc % xqubit);
				int xindex = (Mc / xqubit);
				int yindex2 = (Mt % xqubit);
				int xindex2 = (Mt / xqubit);
				temp.distance = std::abs(yindex - yindex2) + std::abs(xindex - xindex2);
				if (Mc >= 0 && Mt >= 0) {
					temp.Mygatetype = 5;
				}
				else {
					for (int k = 0; k < 5; k++) {
						if (strcmp(Mygatenum[k], layers[i][j].type) == 0) {
							
							temp.Mygatetype = k;
						}
					}
				}
				temp.Myc = Mc;
				temp.Myt = Mt;
				temp.MycI =initialmappingqubit[Mc];
				temp.MytI = initialmappingqubit[Mt];
				temp.Mygatetime = Mygatetime[temp.Mygatetype];
				//std::cout<<"the Mc are "<< Mc<<" Mt "<< Mt<<std::endl;
				if(Mc >= 0 && Mygraph[Mc].size() > 0) {
					degreetemp++;
					Mystore[Mygraph[Mc][Mygraph[Mc].size() - 1]].nei.push_back(Mycount);
				
				}
				if(Mt >= 0 && Mygraph[Mt].size() > 0) {
					Mystore[Mygraph[Mt][Mygraph[Mt].size() - 1]].nei.push_back(Mycount);
					degreetemp++;
					
				}
				temp.indegree = degreetemp;
				if(Mc >= 0) {
					Mygraph[Mc].push_back(Mycount);
				}
				if(Mt >= 0) {
					Mygraph[Mt].push_back(Mycount);	
				}
            //  if(temp.Mygatetype == 0 || temp.Mygatetype == 5){
				Mycount++;
				Mystore.push_back(temp);
             // }
			}
		}
		maxnumcnot = std::max(maxnumcnot,tempnum);
		
	}

	for(auto x : Mystore) {
		std::vector<int> nei = x.nei;
		int min;
		for(int i : nei) {
			//std::cout << "the neighor is target is:" << Mystore[i].Myt << "control is : " <<Mystore[i].Myc<< "gate type is:" <<Mystore[i].Mygatetype<<"layers"<<Mystore[i].layers<< std::endl;
			min = std::min(min,Mystore[i].layers);
		}
		//std::cout << "the number of the node is: "<<x.index<<"target is:" << x.Myt << "control is : " <<x.Myc<< "gate type is:" <<x.Mygatetype<<"layers"<<x.layers<< std::endl;
		
		//std::cout << "after initial mapping the target is:" << x.MytI << "control is : " <<x.MycI << std::endl;
		MyTimelookup.push_back(x.Mygatetime);
	
	}
	MyTimelookupf = MyTimelookup;
	MyTimelookupini = MyTimelookup;
	MyTimelookupl = MyTimelookup;
	Mystoreinreal = Mystore;
	Mystorell = Mystore;
	Mystoreini = Mystore;
	Mystoreinrealbrad = Mystore;
	Mystoreinmetis = Mystore;
	Mystoreh = Mystore;
	MyTimelookup2 = MyTimelookup;
	MyTimelookup3 = MyTimelookup;
	//std::cout<<"the size of node is " <<Mystore.size()<<std::endl;
	std::vector<std::vector<Mynode>> Olayers(Mystore.size());
	std::queue<Mynode> frontier,cfrontier,ccfrontier,mclfrontier,hfrontier,lfrontier,inifrontier;
	int cl = 0;
	int ccl = 0;
	int cccl = 0;
	int mcl = 0;
	int ccccl = 0;

	
	int **p = reset(Mysize,Mycolum);
	//showres(p,Mysize,Mycolum);

	for(auto x : Mystore){
		//std::cout << "control:" << x.Myc << "target is:" << x.Myt << "distance is :" << x.distance << std::endl;
		if(x.indegree == 0 ) {
			frontier.push(x);
			cfrontier.push(x);
			ccfrontier.push(x);
			mclfrontier.push(x);
			hfrontier.push(x);
			lfrontier.push(x);
			inifrontier.push(x);
		}
	}
	
	while (cfrontier.size() > 0) {
		int cap = cfrontier.size();
			for (int i = 0; i < cap; i++) {
			Mynode cur = cfrontier.front();
			cfrontier.pop();
			if (MyTimelookup[cur.index] == 1) {
				//std::cout << cur.index << " th node pop out" <<"current time is :"<<ccl<< std::endl;
				for (auto y : cur.nei) {
					Mystoreinreal[y].indegree--;
					if (Mystoreinreal[y].indegree == 0) {
						cfrontier.push(Mystoreinreal[y]);
					}
				}
			}
			else {

				MyTimelookup[cur.index]--;
				cfrontier.push(cur);
			}

		}
		
		ccl++;
        
	
	}
	//std::cout  << " finish the cycles calculate"<< std::endl;

	while (mclfrontier.size() > 0) {
		int cap = mclfrontier.size();
		int temp = cap;
		myreset(p,Mysize,Mycolum);
		for (int i = 0; i < cap; i++) {																																										
			Mynode cur = mclfrontier.front();
			if((cur.Myc == -1)||(cur.Myt == -1)) {
				temp--;
			}
			bool checkres = checkparrallel(cur, p,xqubit,yqubit);
			if (checkres) {
				mclfrontier.pop();
				for (auto y : cur.nei) {
					Mystoreinmetis[y].indegree--;
					if (Mystoreinmetis[y].indegree == 0) {
						mclfrontier.push(Mystoreinmetis[y]);
					}
				}
			}
			
		}
		//std::cout<<"find number of operations are"<<temp<<std::endl;
		
		mcl++;
	}
	std::cout<<"maximum number of CNOT are"<<maxnumcnot<<std::endl;
	while (ccfrontier.size() > 0) {
		int cap = ccfrontier.size();
		myreset(p, Mysize, Mycolum);
		//std::cout<<"the heap now has:";
		for (int i = 0; i < cap; i++) {
			Mynode cur = ccfrontier.front();
			//std::cout<<cur.index<<" ";
			ccfrontier.pop();
			bool checkres = modifiedschedule(cur, p,xqubit,yqubit);
            if(cap <= 2) checkres = true;
			if (checkres) {
				if (MyTimelookup2[cur.index] == 1) {
					//std::cout << cur.index << " th node pop out" << "current time is :" << cccl << std::endl;
					for (auto y : cur.nei) {
						Mystoreinrealbrad[y].indegree--;
						if (Mystoreinrealbrad[y].indegree == 0) {
							ccfrontier.push(Mystoreinrealbrad[y]);
						}
					}
				}

				else {
					MyTimelookup2[cur.index]--;
					ccfrontier.push(cur);
				}
			}
			else {
				ccfrontier.push(cur);
			}
		}
		//std::cout<<std::endl;
		cccl++;

	}
	std::cout << "  CriticalCycles : " << ccl << ", Parallelcycles : " << cccl<<std::endl;
	Mystoreinrealbrad = Mystore;
	MyTimelookup2 = MyTimelookup;
		for(auto x : Mystore){
		//std::cout << "control:" << x.Myc << "target is:" << x.Myt << "distance is :" << x.distance << std::endl;
		if(x.indegree == 0 ) {
			
			ccfrontier.push(x);
		}
	}
	
while (inifrontier.size() > 0) {
		int cap = inifrontier.size();
		myreset(p, Mysize, Mycolum);
		//std::cout<<"the heap now has:";
		for (int i = 0; i < cap; i++) {
			Mynode cur = inifrontier.front();
			//std::cout<<cur.index<<" ";
			inifrontier.pop();
			bool checkres = modifiedschedule(cur, p,xqubit,yqubit);
            if(cap <= 2) checkres = true;
			if (checkres) {
				if (MyTimelookupini[cur.index] == 1) {
					//std::cout << cur.index << " th node pop out" << "current time is :" << cccl << std::endl;
					for (auto y : cur.nei) {
						Mystoreini[y].indegree--;
						if (Mystoreini[y].indegree == 0) {
							inifrontier.push(Mystoreini[y]);
						}
					}
				}

				else {
					MyTimelookupini[cur.index]--;
					inifrontier.push(cur);
				}
			}
			else {
				inifrontier.push(cur);
			}
		}
		//std::cout<<std::endl;
		ccccl++;

	}
	std::cout <<"the new initialmapping method Parallelcycles : " << ccccl<<std::endl;
    int hcl = 0;
	//Mystoreh
		//hfrontier
	//MyTimelookup2 = MyTimelookupf;
    std::vector<Mynode> curcap;
	while (lfrontier.size() > 0) {
		//std::cout<<std::endl;
		int cap = lfrontier.size();
		myreset(p, Mysize, Mycolum);
		curcap.clear();
		for (int i = 0; i < cap; i++) {
			Mynode cur = lfrontier.front();
			lfrontier.pop();
			curcap.push_back(cur);
		}

       // getboundary(curcap,xqubit,yqubit);
       // for (int i = 0; i < cap; i++) {
		//	curcap[i].nodes = getoverlap(curcap[i],yqubit);
		//	std::cout<<"overlap number is" << curcap[i].nodes<<std::endl;
	//	}

    //    for (int i = 0; i < cap; i++) {
      //      int index = i;
        //    for(int j = i + 1; j < cap; j++) {
          //      if(curcap[i] < curcap[index]) {
           //         index = i;
            //    }
           // }
           //
      std::sort(curcap.begin(),curcap.end(),comp);
           // Mynode temp = curcap[i];
           // curcap[i] = curcap[index];
           // curcap[index] = temp;
     
  //  	for (int i = 0; i < cap; i++) {
	//		std::cout<<"the control qubit is: "<<ccurcap[i].Myc<<" target is : "<<ccurcap[i].Myt<<"overlap number is" << ccurcap[i].nodes<<std::endl;
	//	}
	//	std::cout<<"the heap now has:";
		for (int i = 0; i < cap; i++) {
			Mynode cur = curcap[i];
		//	std::cout<<cur.index<<" ";
			//ccfrontier.pop();
			bool checkres = modifiedschedule(cur, p, xqubit, yqubit);//add initial
		//	if (cap <= 2) checkres = true;
			if (checkres) {
				if (MyTimelookupl[cur.index] == 1) {
				//	std::cout << cur.index << " th node pop out" << "current time is :" << cccl << std::endl;
					for (auto y : cur.nei) {
						Mystorell[y].indegree--;
						if (Mystorell[y].indegree == 0) {
							lfrontier.push(Mystorell[y]);
						}
					}
				}

				else {
					MyTimelookupl[cur.index]--;
					lfrontier.push(cur);
				}
			}
			else {
				lfrontier.push(cur);
			}
		}
		//std::cout<<std::endl;
		hcl++;

	}
	//hcl = std::min(hcl, cccl);
	std::cout << " Heuristic-cycles with initial: " << hcl << std::endl;
	


	hcl = 0;
	//Mystoreh
		//hfrontier
	//MyTimelookup2 = MyTimelookupf;
    curcap.clear();
	while (hfrontier.size() > 0) {
		//std::cout<<std::endl;
		int cap = hfrontier.size();
		myreset(p, Mysize, Mycolum);
		curcap.clear();
		for (int i = 0; i < cap; i++) {
			Mynode cur = hfrontier.front();
			hfrontier.pop();
			curcap.push_back(cur);
		}
       // getboundary(curcap,xqubit,yqubit);
       // for (int i = 0; i < cap; i++) {
		//	curcap[i].nodes = getoverlap(curcap[i],yqubit);
		//	std::cout<<"overlap number is" << curcap[i].nodes<<std::endl;
	//	}

    //    for (int i = 0; i < cap; i++) {
      //      int index = i;
        //    for(int j = i + 1; j < cap; j++) {
          //      if(curcap[i] < curcap[index]) {
           //         index = i;
            //    }
           // }
           //
     //   std::sort(curcap.begin(),curcap.end());
           // Mynode temp = curcap[i];
           // curcap[i] = curcap[index];
           // curcap[index] = temp;
        std::vector<Mynode> ccurcap;
        ccurcap.clear();
        while(curcap.size() != 0) {
    	
    		
    		getboundary(curcap,xqubit,yqubit);

        	for (int i = 0; i < curcap.size(); i++) {
				curcap[i].nodes = getoverlap(curcap[i],yqubit);
				curcap[i].border= judgeborder(curcap[i],yqubit);
				//	std::cout<<"overlap number is" << curcap[i].nodes<<std::endl;
			}
			std::sort(curcap.begin(), curcap.end());
    		ccurcap.push_back(curcap[0]);
    		curcap.erase (curcap.begin(),curcap.begin()+1);
    	}
    //	for (int i = 0; i < cap; i++) {
	//		std::cout<<"the control qubit is: "<<ccurcap[i].Myc<<" target is : "<<ccurcap[i].Myt<<"overlap number is" << ccurcap[i].nodes<<std::endl;
	//	}
		//std::cout<<std::endl;
	//	std::cout<<"the heap now has:";
		for (int i = cap-1; i >= 0; i--) {
			Mynode cur = ccurcap[i];
		//	std::cout<<cur.index<<" ";
			//ccfrontier.pop();
			bool checkres = modifiedschedulewithinitial(cur, p, xqubit, yqubit);//add initial
		//	if (cap <= 2) checkres = true;
			if (checkres) {
				if (MyTimelookupf[cur.index] == 1) {
				//	std::cout << cur.index << " th node pop out" << "current time is :" << hcl <<"the control qubit is: "<<cur.Myc<<" target is : "<<cur.Myt<<"overlap number is" << cur.nodes<< std::endl;
					for (auto y : cur.nei) {
						Mystoreh[y].indegree--;
						if (Mystoreh[y].indegree == 0) {
							hfrontier.push(Mystoreh[y]);
						}
					}
				}

				else {
					MyTimelookupf[cur.index]--;
					hfrontier.push(cur);
				}
			}
			else {
				hfrontier.push(cur);
			}
		}
		//std::cout<<std::endl;
		hcl++;

	}
	//hcl = std::min(hcl, cccl);
	std::cout << " overlap-cycles with initial: " << hcl << std::endl;
	
	while(frontier.size() > 0) {
		int cap = frontier.size();
		myreset(p, Mysize, Mycolum);
		for(int i = 0; i < cap; i++) {
			Mynode cur = frontier.front();
			bool checkres = modifiedschedule(cur, p,xqubit,yqubit);
			if (checkres) {
				frontier.pop();
				//std::cout << cur.index << " th node" << std::endl;
				Olayers[cl].push_back(cur);
				for (auto y : cur.nei) {
					Mystore[y].indegree--;
					if (Mystore[y].indegree == 0) {
						frontier.push(Mystore[y]);
					}
				}
			}
								
		}
		cl++;
	
	}
	
	
	
	//for(int i = 0; i < cl;i++) {
		//std::cout<<"the current layer is"<<i <<std::endl;
	//	for(int j = 0; j < Olayers[i].size(); j++) {
		//	std::cout<<"the index" <<Olayers[i][j].index<<std::endl;
	//	}
	//	std::cout<<"end of layer"<<std::endl;
//	}
	//int size_grid = 3;
	//bool dmatrix[size_grid][size_grid] = {0};
	//for(int i = 0; i < size_grid; i++) {
	//	for(int j = 0; j < size_grid;j++) {
	//		if(j>0){dmatrix[i*size_grid+j-1][i*size_grid+j] = true; dmatrix[i*size_grid + j][i*size_grid + j - 1]=true;}
	//		if(i>0){dmatrix[i*size_grid+j][i*size_grid+j-size_grid]=true;dmatrix[i*size_grid+j-size_grid][i*size_grid+j]=true;}
	//	}
	//}
//	std::cout << "the critical path is" << layers.size() << "  our braiding schedule cycle is" << cl<<std::endl;
	
	//std::cout << "  considering metis intial mapping cycle is " << mcl<<std::endl;

	return 0;
}

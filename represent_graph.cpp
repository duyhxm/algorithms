#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<set>

struct mEdge
{
	int u;
	int v;
	float w;
};

struct lEdge
{
	int v;
	float w;
};

using lE = lEdge;
using mE = mEdge;
using mGraph = std::vector<std::vector<float>>;
using lGraph = std::vector<std::vector<lE>>;

mGraph build_mGraph(int vertices)
{
	mGraph g(vertices, std::vector<float>(vertices, 0.0));
	return g;
}

lGraph build_lGraph(int vertices)
{
	lGraph g(vertices);
	return g;
}

void add_edge(mGraph& g, mE e)
{
	if (e.u < 0 || e.u >= g.size() || e.v < 0 || e.v >= g.size())
		return;
	g[e.u][e.v] = e.w;
	g[e.v][e.u] = e.w;
}

void add_edge(lGraph& g, int u, lE e)
{
	if (u < 0 || u >= g.size() || e.v < 0 || e.v >= g.size())
		return;
	g[u].push_back(e);
	lE t{ u,e.w };
	g[e.v].push_back(t);
}

void print_mgraph(mGraph g)
{
	for (int i = 0; i < g.size(); i++)
	{
		for (int j = 0; j < g[i].size(); j++)
		{
			std::cout << g[i][j] << "  ";
		}
		std::cout << std::endl;
	}
}
void print_lgraph(lGraph g)
{
	for (int i = 0; i < g.size(); i++)
	{
		std::cout << i << ": ";
		for (int j = 0; j < g[i].size(); j++)
		{
			std::cout << g[i][j].v << "  ";
		}
		std::cout << std::endl;
	}
}

int main()
{
	std::vector<std::string> line;
	std::fstream file("E:\\exercise.txt");

	//read file
	if (file.is_open())
	{
		std::string l;
		while (std::getline(file, l)) //n+1 times
		{
			std::stringstream ss(l); 
			std::string data; 
			std::string word;
			while (ss >> word)
			{
				data += word; 
			}
			line.push_back(data);
		}
		file.close();
	}

	//create graph
	int size = line[0].size();
	lGraph lG(size);
	mGraph mG(size, std::vector<float>(size, 0));

	//add edge
	std::pair<int, int> p;
	for (int i = 1; i < line.size(); i++) //O(n) n is the number of lines
	{
		p.first = line[0].find(line[i][0]); //O(k) k is the length of the string
		p.second = line[0].find(line[i][1]); //O(k) k is the length of the string
		add_edge(mG, { p.first,p.second,1 }); //O(1)
		add_edge(lG, p.first, { p.second,1 }); //O(1)
	} //O(nk)
	
	//print graph
	print_mgraph(mG);
	std::cout << std::endl;
	print_lgraph(lG);

	system("pause>0");
}
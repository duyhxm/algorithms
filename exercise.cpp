#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>

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
	mGraph g(vertices, std::vector<float>(vertices,0.0));
	return g;
}

lGraph build_lGraph(int vertices)
{
	lGraph g(vertices);
	return g;
}

void add_edge(mGraph&g, mE e)
{
	if (e.u < 0 || e.u >= g.size() || e.v < 0 || e.v >= g.size())
		return;
	g[e.u][e.v] = e.w;
	g[e.v][e.u] = e.w;
}

void add_edge(lGraph&g, int u, lE e)
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
			std::cout << g[i][j] << " ";
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
			std::cout << g[i][j].v << " ";
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
		while (std::getline(file,l))
			line.push_back(l);
		line.erase(line.begin()+line.size()-1);
		file.close();
	}

	//create graph
	std::stringstream ss(line[0]);
	std::vector<std::string> origin;
	std::string word;
	short cnt = 0;
	while (ss >> word)
	{
		cnt++;
		origin.push_back(word);
	}
	lGraph lG(cnt);
	mGraph mG(cnt, std::vector<float>(cnt,0));

	//add edge
	for (int i = 1; i < line.size(); i++)
	{
		std::stringstream ss(line[i]);
		std::string vertex;
		short u = 0;
		short v = 0;
		std::pair<std::string, std::string> edge;
		ss >> vertex;
		edge.first = vertex;
		ss >> vertex;
		edge.second = vertex;
		for (int i = 0; i < origin.size(); i++)
		{
			if (origin[i] == edge.first)
				u = i;
			if (origin[i] == edge.second)
				v = i;
		}
		mG[u][v] = 1;
		mG[v][u] = 1;
		lG[u].push_back({ v,0 });
		lG[v].push_back({ u,0 });
	}

	//print graph
	print_mgraph(mG);
	std::cout << std::endl;
	print_lgraph(lG);

	system("pause>0");
}
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<queue>
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

int main()
{
	std::priority_queue<int> a;
	std::vector<std::string> line;
	std::fstream file("E:\\exercise.txt");

	if (file.is_open())
	{
		std::string l;
		while (std::getline(file,l))
			line.push_back(l);
		file.close();
	}

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
	system("pause>0");
}
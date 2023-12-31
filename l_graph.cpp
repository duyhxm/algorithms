#include<iostream>
#include<vector>
#include<queue>
#include<stack>

struct edge {
	float w;
	int v;
};

using graph = std::vector<std::vector<edge>>;

graph buid_graph(int vertices)
{
	graph g(vertices);
	return g;
}

void add_edge(graph& g, int u, edge e)
{
	if (u < 0 || e.v < 0 || u >= g.size() || e.v >= g.size())
		return;
	g[u].push_back(e);
	edge t{ e.w,u };
	g[e.v].push_back(t);
}

void delete_edge(graph &g, int u, edge e)
{
	if (u < 0 || e.v < 0 || u >= g.size() || e.v >= g.size())
		return;
	for (int i = 0; i < g[u].size(); i++)
	{
		if(g[u][i].v==e.v)
			g[u].erase(g[u].begin() + i);
	}
	for (int i = 0; i < g[e.v].size(); i++)
	{
		if(g[e.v][i].v==u)
			g[e.v].erase(g[e.v].begin() + i);
	}
}

void print_graph(graph g)
{
	for (int i = 0; i < g.size(); i++)
	{
		for (int j = 0; j < g[i].size(); j++)
			std::cout << "(" << g[i][j].v << "," << g[i][j].w << ")" << "  ";
		std::cout << std::endl;
	}
}

std::vector<int>  bfs(graph l, int u)
{
	std::queue<int> q;
	std::vector<int> r;
	std::vector<bool> status(l.size(), false);
	q.push(u);
	status[u] = true;
	while (!q.empty())
	{
		int v = q.front();
		q.pop();
		r.push_back(v);

		for (int i = 0; i < l[u].size(); i++)
			if (!status[l[u][i].v])
			{
				status[l[u][i].v] = true;
				q.push(l[u][i].v);
			}	
	}
	return r;
}

std::vector<int> dfs(graph g, int u)
{
	static std::vector<int> r;
    static std::vector<bool> status(g.size(), false);

	if (r.size() == g.size())
		return r;
	r.push_back(u);
	status[u] = true;
	for (int i = 0; i < g[u].size(); i++)
	{
		int w = g[u][i].v;
		if (!status[w])
			dfs(g, w);
	}
	return r;
}

int main()
{
	int n;
	std::cout << "Enter the number of vertices: ";
	std::cin >> n;
	graph g(n);
	std::cout << std::endl;
	while (true)
	{
		std::cout << "--------------------" << std::endl;
		std::cout << "Enter your choice: \n";
		std::cout << "1. Adding an edge\n";
		std::cout << "2. Removing an edge\n";
		std::cout << "3. Printing\n";
		std::cout << "4. Tranversal BFS\n";
		std::cout << "5. Tranversal DFS\n";
		std::cout << "6. Exit\n";
		std::cout << "Enter a number to choose: ";
		short choice = 0; std::cin >> choice;
		std::cout << "--------------------" << std::endl;

		edge e{ 0,0 };
		int u = 0;
		if (choice == 1)
		{
			std::cout << "Enter sequentially original point, destination point and weight that you want to add: ";
			std::cin >> u >> e.v >> e.w;
			add_edge(g, u, e);
		}
		else
			if (choice == 2)
			{
				std::cout << "Enter sequentially original point, destination point and weight that you want to remove: ";
				std::cin >> u >> e.v >> e.w;
				delete_edge(g, u, e);
			}
			else
				if (choice == 3)
					print_graph(g);
				else
					if (choice == 4)
					{
						std::cout << "enter a point: ";
						std::cin >> u;
						std::vector<int> r = bfs(g, u);
						for (int i = 0; i < r.size(); i++)
						{
							std::cout << r[i] << "  ";
							std::cout << std::endl;
						}
					}
					else
						if (choice == 5)
						{
							std::cout << "enter a point: ";
							std::cin >> u;
							std::vector<int> r = dfs(g, u);
							for (int i = 0; i < r.size(); i++)
							{
								std::cout << r[i] << "  ";
								std::cout << std::endl;
							}
						}
						else
							exit(0);
	}

	system("pause>0");
	return 0;
}
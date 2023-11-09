#include<iostream>
#include<vector>

struct Edge {
	float w;
	int u;
	int v;
};

using edge = Edge;
using graph = std::vector<std::vector<float>>;

graph build_graph(int vertices)
{
	graph a(vertices, std::vector<float>(vertices,0.0));
}

void add_edge(graph &g, edge e)
{
	g[e.u][e.v] = e.w;
}

void delete_edge(graph& g, edge e)
{
	g[e.u][e.v] = 0.0;
}

void print_graph(graph g)
{
	for (int i = 0; i < g.size(); i++)
	{
		for (int j = 0; j < g.size(); j++)
			std::cout << g[i][j] << "  ";
		std::cout << std::endl;
	}
}

int main()
{
	graph g;
	int vertices=0;

	std::cout << "Enter the number of vertices: ";
	std::cin >> vertices;

	g = build_graph(vertices);

	std::cout << "Enter your choice: " << std::endl;
	while (true)
	{
		std::cout << "-----------------------------" << std::endl;
		std::cout << "1. Adding an edge\n";
		std::cout << "2. Removing an edge\n";
		std::cout << "3. Printing\n";
		std::cout << "4. Exit\n";
		std::cout << "Typing a number to choose: ";
		short choice = 0;	std::cin>>choice;
		std::cout << "-----------------------------" << std::endl;
		edge e{ 0,0,0 };
		if (choice == 1)
		{
			std::cout << "Enter sequentially original point, destination point and weight that you need to add: ";
			std::cin >> e.u >> e.v >> e.w;
			add_edge(g, e);
		}
		else
			if (choice == 2)
			{
				std::cout << "Enter sequentially original point, destination point that you need to remove:  ";
				std::cin >> e.u >> e.v;
				delete_edge(g, e);
			}
			else
				if (choice == 3)
					print_graph(g);
				else
					break;
	}

	system("pause>0");
	return 0;
}
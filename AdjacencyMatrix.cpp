#include <iostream>
#include <fstream>
#include <string>
#include <queue> 

using namespace std;
double graph[10][10];
char store[10];
bool weight, direction;
int vertices, edges;

int getIndex(char a)
{
	int b = 0;
	for (int i = 0; i < 10; i++)
	{
		if (store[i] == a)
			b = i;
	}
	return b;
}
string hasEdge(char from, char to)
{
	int a = 0, b = 0;
	a = getIndex(from);
	b = getIndex(to);
	if ((graph[a][b] == 0) || (graph[a][b] == -1))
		return "false";
	else
		return "true";
}
void addEdge(char from, char to, double c)
{
	int a = 0, b = 0;
	a = getIndex(from);
	b = getIndex(to);
	graph[a][b] = c;
	if (direction == false)
		graph[b][a] = c;
}
void deleteEdge(char from, char to)
{
	int a, b;
	a = getIndex(from);
	b = getIndex(to);
	graph[a][b] = 0;
	graph[b][a] = 0;
}
void addVertex(char a)
{
	store[vertices - 1] = a;
	for (int i = 0; i < vertices; i++)
	{
		for (int j = 0; j < vertices; j++)
		{
			graph[i][j] = 0;
		}
	}

}
void deleteVertex(char a)
{
	vertices--;
	int x;
	x = getIndex(a);
	for (int i = x; i < 10; i++)
		store[i] = store[i + 1];
	for (int i = 0; i <= vertices; i++)
	{
		for (int j = x; j <= vertices; j++)
		{
			graph[i][j] = graph[i][j + 1];
		}
		for (int i = vertices - 1; i >= 0; i--)
		{
			graph[x][i] = graph[x + 1][1];
		}
	}
	for (int i = x; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			graph[i][j] = graph[i + 1][j];
			if (i == 9)
				graph[i][j] = -1;
		}
	}
}
string isSparce()
{
	int vertex = vertices - 1;
	int temp = (vertex * (vertex + 1)) / 2;
	if (edges <= (temp * 15) / 100)
		return "true";
	else
		return "false";

}
string isDense()
{
	int vertex = vertices - 1;
	int temp = vertex * (vertex + 1) / 2;
	if (edges >= (temp * 85) / 100)
		return "true";
	else
		return "false";
}
int countVertices()
{
	return vertices;
}
int countEdges()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (graph[i][j] != 0 && graph[i][j] != -1)
				edges++;
		}
	}
	if (direction == 0)
		edges = edges / 2;
	return edges;
}

bool checkForVisited(char a, char visited[])
{
	int m = 0;
	for (int i = 0; i < 10; i++)
	{
		if (a == visited[i])
			m = 1;
	}
	if (m == 1)
		return 1;
	else
		return 0;
}

void shiftArray(char m[])
{
	for (int i = 0; i < 10; i++)
	{
		m[i] = m[i + 1];
		if (i == 9)
			m[i] = ' ';
	}
}

string isConnected()
{
	char visited[10] = { ' ' };
	char todo[10] = { ' ' };
	string temp;
	int  b = 1, visitedCount = 0;
	visited[0] = store[0];
	for (int i = 1; i < vertices; i++)
	{
		temp = hasEdge(store[0], store[i]);
		if (temp == "true")
		{
			todo[b - 1] = store[i];
			visited[b] = store[i];
			b++;
		}
	}
	while (todo[0] != ' ')
	{
		char a = todo[0];
		shiftArray(todo);
		int c = getIndex(a);
		for (int i = 0; i < vertices; i++)
		{
			temp = hasEdge(store[c], store[i]);
			if (temp == "true" && checkForVisited(store[i], visited) == 0)
			{
				visited[b] = store[i];
				todo[b - 2] = store[i];
				b++;
			}
		}

	}
	for (int i = 0; i < 10; i++)
	{
		if (visited[i] >= 'A' + 0 && visited[i] <= 'Z' + 0)
			visitedCount++;
	}
	int x = countVertices();
	if (x == visitedCount)
		return "true";
	else
		return "false";
}
string isFullyConnected()
{
	int vertex = vertices - 1;
	if (edges == (vertex*(vertex + 1)) / 2)
		return "true";
	else
		return "false";
}
string readGraph()
{
	string buffer; //character buffer
	ifstream infile("Example.txt"); //create file for input
	while (!infile.eof()) //until end-of-file
	{
		getline(infile, buffer);
		if (buffer.substr(0, 1) == "*")
			continue;
		if (buffer == "weighted")
			weight = true;
		if (buffer == "unweighted")
			weight = false;
		if (buffer == "directed")
			direction = true;
		if (buffer == "undirected")
			direction = false;

		if (buffer == "begin")
		{
			getline(infile, buffer);
			for (size_t i = 0; i < buffer.length(); i++)
			{
				if (buffer[i] != ' ')
				{
					vertices++;
					addVertex(buffer[i]);
				}
			}
			while (buffer != "end")
			{
				char buff[5];
				for (size_t i = 4; i < buffer.length(); i++)
					buff[i - 4] = buffer[i];
				double c = atof(buff);
				for (size_t i = 0; i < buffer.length(); i++)
				{
					char from = buffer[0];
					char to = buffer[2];
					addEdge(from, to, c);
				}
				getline(infile, buffer);
			}
		}

	}
	return "read";
}
void printGraph()
{
	cout << "\t";
	for (int i = 0; i < 10; i++)
		cout << store[i] << "\t";
	cout << endl;
	for (int i = 0; i < vertices; i++)
	{
		cout << store[i] << "\t";
		for (int j = 0; j < vertices; j++)
		{
			cout << graph[i][j] << "\t";
		}
		cout << "\n";
	}
}

void testGraph()
{
	int failed = 0;
	string buffer;
	ifstream infile("Example.txt");
	while (!infile.eof())
	{
		getline(infile, buffer);
		string s1 = "hasEdge";
		string s2 = "addEdge";
		string s3 = "deleteEdge";
		string s4 = "addVertex";
		string s5 = "deleteVertex";
		string s6 = "isSparce";
		string s7 = "isDense";
		string s8 = "countVertices";
		string s9 = "countEdges";
		string s10 = "isConnected";
		string s11 = "isFullyConnected";
		string s12 = "readGraph";
		string s13 = "printGraph";
		if (buffer.compare(0, s1.length(), s1) == 0)
		{
			string s = hasEdge(buffer[8], buffer[10]);
			getline(infile, buffer);
			if (s == buffer)
				cout << "Test passed: " << s1 << endl;
			else
			{
				cout << "Test failed: " << s1 << endl;
				failed++;
			}
		}
		if (buffer.compare(0, s2.length(), s2) == 0)
		{
			char buff[15];
			int a, b;
			for (size_t i = 12; i < buffer.length(); i++)
				buff[i - 1] = buffer[i];
			double c = atof(buff);
			for (size_t i = 0; i < buffer.length(); i++)
			{
				char from = buffer[8];
				char to = buffer[10];
				addEdge(from, to, c);
			}
			for (int i = 0; i < 10; i++)
			{
				if (store[i] == buffer[8])
					a = i;
				if (store[i] == buffer[10])
					b = i;
			}
			addEdge(buffer[8], buffer[10], c);

			getline(infile, buffer);
			if (graph[a][b] == c)
				cout << "Test passed: " << s2 << endl;
			else
			{
				cout << "Test failed: " << s2 << endl;
				failed++;
			}
		}
		if (buffer.compare(0, s3.length(), s3) == 0)
		{
			deleteEdge(buffer[11], buffer[13]);
			int a, b;
			for (int i = 0; i < 10; i++)
			{
				if (store[i] == buffer[11])
					a = i;
				if (store[i] == buffer[13])
					b = i;
			}
			getline(infile, buffer);
			if (graph[a][b] == 0)
				cout << "Test passed: " << s3 << endl;
			else
			{
				cout << "Test failed: " << s3 << endl;
				failed++;
			}
		}
		if (buffer.compare(0, s4.length(), s4) == 0)
		{
			addVertex(buffer[10]);
			if (store[vertices - 1] == buffer[10])
				cout << "Test passed: " << s4 << endl;
			else
			{
				cout << "Test failed: " << s4 << endl;
				failed++;
			}
			getline(infile, buffer);
		}
		if (buffer.compare(0, s5.length(), s5) == 0)
		{
			int tot = 0;
			deleteVertex(buffer[13]);
			for (int i = 0; i < vertices; i++)
			{
				if (store[i] == buffer[13])
					tot++;
			}
			if (tot == 0)
				cout << "Test passed: " << s5 << endl;
			else
			{
				cout << "Test failed: " << s5 << endl;
				failed++;
			}
			getline(infile, buffer);
		}
		if (buffer.compare(0, s6.length(), s6) == 0)
		{
			string i = isSparce();
			getline(infile, buffer);
			if (i == buffer)
				cout << "Test passed: " << s6 << endl;
			else
			{
				cout << "Test failed: " << s6 << endl;
				failed++;
			}
		}
		if (buffer.compare(0, s7.length(), s7) == 0)
		{
			string i = isDense();
			getline(infile, buffer);
			if (i == buffer)
				cout << "Test passed: " << s7 << endl;
			else
			{
				cout << "Test failed: " << s7 << endl;
				failed++;
			}
		}
		if (buffer.compare(0, s8.length(), s8) == 0)
		{
			int i = countVertices();
			getline(infile, buffer);
			if (i == atoi(buffer.c_str()))
				cout << "Test passed: " << s8 << endl;
			else
			{
				cout << "Test failed: " << s8 << endl;
				failed++;
			}
		}
		if (buffer.compare(0, s9.length(), s9) == 0)
		{
			int i = countEdges();
			getline(infile, buffer);
			if (i == atoi(buffer.c_str()))
				cout << "Test passed: " << s9 << endl;
			else
			{
				cout << "Test failed: " << s9 << endl;
				failed++;
			}

		}
		if (buffer.compare(0, s10.length(), s10) == 0)
		{
			string s = isConnected();
			getline(infile, buffer);
			if (s == buffer)
				cout << "Test passed: " << s10 << endl;
			else
			{
				cout << "Test failed: " << s10 << endl;
				failed++;
			}
		}
		if (buffer.compare(0, s11.length(), s11) == 0)
		{
			string i = isFullyConnected();
			getline(infile, buffer);
			if (i == buffer)
				cout << "Test passed: " << s11 << endl;
			else
			{
				cout << "Test failed: " << s11 << endl;
				failed++;
			}
		}
		if (buffer.compare(0, s12.length(), s12) == 0)
		{
			string i = readGraph();
			getline(infile, buffer);
			if (i == buffer)
				cout << "Test passed: " << s12 << endl;
			else
			{
				cout << "Test failed: " << s12 << endl;
				failed++;
			}
		}
		if (buffer.compare(0, s13.length(), s13) == 0)
		{
			printGraph();
			getline(infile, buffer);
			if (true == 1)
				cout << "Test passed: " << s13 << endl;
			else
			{
				cout << "Test failed: " << s13 << endl;
				failed++;
			}
		}

	}
	cout << "The number of failed tests: " << failed << endl;
	cout << "The number of passing tests: " << (13 - failed) << endl;
}
void printPrims(char from, char to)
{
	int a, b;
	a = getIndex(from);
	b = getIndex(to);
	cout << "Edge from " << from << " to " << to << " with weight " << graph[a][b] << endl;
}
void shortestDist(char visited[], char visit[])
{
	int i = 0;
	int saveIndex = 0;
	double smallestDist = 100;
	string temp1 = "";
	char addToVisited = ' ', temp2 = ' ';
	while (visited[i] != ' ')
	{
		for (int j = 0; j < vertices; j++)
		{
			temp1 = hasEdge(visited[i], visit[j]);
			if (temp1 == "true")
			{
				if (graph[i][j] < smallestDist)
				{
					smallestDist = graph[i][j];
					addToVisited = visit[j];
					temp2 = visited[i];
					saveIndex = j;
				}
			}

		}
		i++;
	}

	if (!(temp2 == ' ' || addToVisited == ' '))
		printPrims(temp2, addToVisited);

	for (i = saveIndex; i < vertices; i++)
		visit[i] = visit[i + 1];
	for (i = vertices; i >= 0; i--)
		visited[i] = visited[i - 1];
	visited[0] = addToVisited;

}

void Prims()
{
	char visit[10] = { ' ' };
	char visited[10] = { ' ' };
	int k = 0, i = 0;
	int saveIndex = 0;
	while (k < vertices)
	{
		visit[k] = store[k];
		k++;
	}
	visited[0] = visit[0];
	shiftArray(visit);
	for (i = 0; i < vertices; i++)
	{
		if (visit[0] != ' ')
		{
			shortestDist(visited, visit);
		}
	}
}


int main()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			graph[i][j] = -1;
		}
	}
	readGraph();
	printGraph();
	Prims();
	system("Pause");
	return 0;
}


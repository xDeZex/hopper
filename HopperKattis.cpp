// A try to solve the Kattis problem Hooper,
// this is a simple solution and is probably too slow, though it got the wrong answer on a task and I can't find why and there's nothing online to help

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;


class Node {
public:

	int number;
	int index;

	Node() {

	}

	Node(int Tnumber, vector<int> Tneighbours) {
		number = Tnumber;
		neighbours = Tneighbours;
	}
	Node(int Tnumber, int Tindex) {
		number = Tnumber;
		index = Tindex;
	}

	bool addNeigbours(vector<int> Tneighbours) {
		neighbours = Tneighbours;
		return true;
	}

	bool hasVisited(string thread) {
		if (visited.find(thread) == visited.end()) {
			visited[thread] = true;
			return false;
		}
		else {
			return true;
		}
	}

	vector<int> getNeighbours() {
		return neighbours;
	}
private:

	unordered_map<string, bool> visited;
	vector<int> neighbours;
};





class Hopper {
public:
	unordered_map<int, Node> nodeList;
	Hopper() {

	}

	int dfsHelper(Node node, int depth, vector<int> visited) {
		if (find(visited.begin(), visited.end(), node.index) != visited.end()) {
			/*cout << "visited ";
			for (int i : visited) {
				cout << i << " ";
			}
			cout << endl;*/
			return depth;
		}
		depth++;
		visited.push_back(node.index);
		/*cout << " test " << node.index << " " << node.number << endl;*/
		vector<int> n = node.getNeighbours();
		int longest = depth;
		while (!n.empty()) {
			int i = n.back();
			n.pop_back();
			/*cout << " index " << i << endl;*/
			int foundDepth = dfsHelper(nodeList[i], depth, visited);
			if (foundDepth > longest)
				longest = foundDepth;
		}
		return longest;
	}

	int dfs(Node start) {

		return dfsHelper(start, 0, {});

	}

	int hopperLength(vector<int> list, int jumpLength, int jumpSize) {
		//jumpLength++;
		int index = 0;
		for (int i : list) {
			nodeList[index] = Node(i, index);
			index++;

		}

		for (int i = 0; i < list.size(); i++) {
			int value = list[i];
			int lower = 0;
			if (i - jumpLength > 0)
				lower = i - jumpLength;
			int higher = list.size();
			if (i + jumpLength + 1 < list.size())
				higher = i + jumpLength + 1;
			vector<int> neighbours;
			for (int j = lower; j < higher; j++) {
				int neighbourV = list[j];
				int neighbour = j;
				if (neighbourV == value)
					continue;
				if (abs(neighbourV - value) <= jumpSize)
					neighbours.push_back(neighbour);
			}
			/*for (int q : neighbours) {
				cout << q << " ";
			}
			cout << endl;*/
			nodeList[i].addNeigbours(neighbours);
		}
		int longest = 0;
		for (int i = 0; i < list.size(); i++) {
			//cout << i << " start at index" << endl;
			int depth = dfs(nodeList[i]);
			if (depth > longest)
				longest = depth;
		}
		return longest;
	}
};

int main()
{
	while (true) {

		vector<int> temp;
		string line;
		getline(std::cin, line);
		stringstream sstr(line);
		int n;
		while (sstr >> n)
			temp.push_back(n);
		vector<int> list;
		getline(std::cin, line);
		stringstream sstr2(line);
		while (sstr2 >> n)
			list.push_back(n);

		//vector<int> list = { 1, 7, 8, 2, 6, 4, 3, 5 };
		//list = {2, 3, 1, 4, 6, 5, 7, 9, 8};
		//list = {1, 100000, 2, 10000, 10000, 3, 4, 6, 5, 7, 9, 8};
		cout << Hopper().hopperLength(list, temp[1], temp[2]) << endl;
	}
}

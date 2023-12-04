#include <iostream>
#include <vector>
using namespace std;
const int MAX_E = 8;
const int MAX_V = 6;

struct Edge { int from, to, weight; };

Edge e[MAX_E]; // 边
int dist[MAX_V]; // 最短距离
int E, V; // E：边数	V：顶点数

// 注意：该算法针对的是有向图
// 如果是有向无环图（DAG）则一定没有负权环可以不用判断
// 时间复杂度：O(V * E)
// 求解从S点出发到所有点的最短距离
bool shortest_path(int s) 
{
	for (int i = 0; i < V; i++) dist[i] = INT_MAX;
	dist[s] = 0; // 起点距离为0
	// 每一次更新至少会更新一个点，比如 初度为1的起点
	// 每次更新的点都是和上次更新过的边相关
	// 就这样一次次更新下去，最多到V - 1（除开起始点）次就可以更新完
	// 缺点是当前已经更新的点不一定是距离最近的点，可能还会受到后面更新的影响
	for(int i = 0; i < V - 1; i++)
	{
		bool isUpdate = false;
		for (int i = 0; i < E; i++)
		{
			Edge edge = e[i];
			// 更新最短距离
			if (dist[edge.from] != INT_MAX && dist[edge.to] > dist[edge.from] + edge.weight)
				dist[edge.to] = dist[edge.from] + edge.weight;
			isUpdate = true;
		}
		if (!isUpdate) break; // 没有更新就没必要继续执行下去
	}

	// 检测是否存在负权环路 (环路上的权值和为负)
	bool hasCycle = false;
	for (int i = 0; i < E; i++)
	{
		Edge eg = e[i];
		// 有更新则有负权环存在，负权环会一直更新下去
		if (dist[eg.from] != INT_MAX && dist[eg.to] > dist[eg.from] + eg.weight)
		{
			hasCycle = true;
			break;
		}
	}
	return hasCycle;
}

// 检测是否存在负权环路 (环路上的权值和为负)
// 负权环路的危害：因为负权环路跑一圈的距离代价为负，这就使得能够到达其他点的距离不准确，可能会为负无穷且负权环路会导致距离会一直无穷更新
bool hasNegativeCycle()
{
	memset(dist, 0, sizeof(dist));
	for (int i = 0; i < V; i++) // 如果退出条件为 i < V - 1则和上面shortest_path()函数功能相同
	{
		for (int j = 0; j < E; j++)
		{
			Edge eg = e[j];
			// 负权环路会导致距离会一直无穷更新
			if (dist[eg.from] != INT_MAX && dist[eg.to] > dist[eg.from] + eg.weight)
			{
				dist[eg.to] = dist[eg.from] + eg.weight;
				// 如果第V次仍然更新，则存在负权环
				if (i == V - 1) return true;
			}
		}
	}
	return false;
}


int main()
{
	e[0] = { 0,1,2 };
	e[1] = { 0,5,5 };
	e[2] = { 1,2,1 };
	e[3] = { 2,3,-2 };
	e[4] = { 3,4,3 };
	e[5] = { 4,5,4 };
	e[6] = { 0,3,2 };
	e[7] = { 1,5,2 };
	//e[8] = { 3,1,0 };
	E = MAX_E, V = MAX_V; // E：边数	V：顶点数
	bool rs0 = hasNegativeCycle();
	cout << rs0 << endl;
	bool rs = shortest_path(0);
	for (int i = 0; i < 6; i++)
	{
		cout <<"0 to "<<i<<" = "<< dist[i] << endl;
	}
	cout << rs;
	return 0;
}

/******执行结果********/
/*
0
0 to 0 = 0
0 to 1 = 2
0 to 2 = 3
0 to 3 = 1
0 to 4 = 4
0 to 5 = 4
0
*/

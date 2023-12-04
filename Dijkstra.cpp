#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
* Dijkstra算法
* 对象：无向图
* 每次选取能够确定最短距离的顶点进行更新
*/

typedef pair<int, int> P; // first:距离  second:顶点编号
const int MAX_V = 6;

struct Edge { int cost, to; };
vector<Edge> Grap[MAX_V];

int dist[MAX_V];

void Dijkstra(int s)
{
	priority_queue<P, vector<P>, greater<P>> que;
	// 初始化
	for (int i = 0; i < MAX_V; i++) dist[i] = INT_MAX;
	dist[s] = 0;
	que.push(P(0, s));

	while (!que.empty())
	{
		P p = que.top(); que.pop();
		int v = p.second;
		if (dist[v] < p.first) continue; // 当前节点就是最短距离 无需更新
		for (int i = 0; i < Grap[v].size(); i++)
		{
			Edge e = Grap[v][i];
			// 这里能够过滤掉已经更新过的点
			// 把没有遍历过的相邻点入队列
			// 但队列里顶点的cost不一定是最短路
			if (dist[e.to] > dist[v] + e.cost) 
			{
				dist[e.to] = dist[v] + e.cost;
				que.push(P(dist[e.to], e.to));
			}
		}
	}
}
int main()
{
	Grap[0].push_back({ 4,1 });
	Grap[0].push_back({ 2,2 });

	Grap[1].push_back({ 3,3 });
	Grap[1].push_back({ 1,2 });
	Grap[1].push_back({ 4,0 });


	Grap[2].push_back({ 2,0 });
	Grap[2].push_back({ 1,1 });
	Grap[2].push_back({ 5,3 });
	Grap[2].push_back({ 1,4 });

	Grap[3].push_back({ 3,1 });
	Grap[3].push_back({ 5,2 });
	Grap[3].push_back({ 2,4 });
	Grap[3].push_back({ 1,5 });

	Grap[4].push_back({ 1,2 });
	Grap[4].push_back({ 2,3 });
	Grap[4].push_back({ 1,5 });


	Grap[5].push_back({ 1,3 });
	Grap[5].push_back({ 1,4 });


	Dijkstra(0);

	for (int i = 0; i < MAX_V; i++)
		cout << "0 to " << i << " = " << dist[i] << endl;

	return 0;
}

/******运行结果********/
/*
0 to 0 = 0
0 to 1 = 3
0 to 2 = 2
0 to 3 = 5
0 to 4 = 3
0 to 5 = 4
*/

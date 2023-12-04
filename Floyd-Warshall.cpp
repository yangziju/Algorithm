#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/*
求解所有两点间的最短路的问题叫做任意两点间的最短路问题。让我们试着用DP来求解任意

两点间的最短路问题。只使用顶点0~ k和ij的情况下，记到j的最短路长度为a[k+1][i][j]。

k=-1时，
认为只使用i和j，所以d[O][i][i]=cost[i][j]。 接下来让我们把只使用顶点0~k的问题归约

到只使用0~ k-1的问题上。
只使用0~ k时，我们分到j的最短路正好经过顶点k一次 和完全不经过顶点k两种情况来讨论。
不经过顶点k的情况下，d[k][i][j]=d[k-1][i][j]。 通过顶点k的情况下，d[k][i][j]=d[k-

1][i][k]+d[k-1][k][j]。合起来，就得到了d[k][i][i]=min(d[k-1][i][i], d[k-1][i]

[k]+d[k-1][k][j])。这个DP也可以使用同-个数组，不断进行d[i][j]=min(d[i][j], d[i]

[k]+d[k][i])的更新来实现。
这个算法叫做Floyd-Warshall算法，可以在O(V3)时间里求得所有两点间的最短路长度。
Floyd-Warshall算法和Bellman-Ford算法一样， 可以处理边是负数的情况。而判断图中是否

有负圈，只需检查是否存在d[i][i]是负数的顶点就可以了。

*/

const int MAX_V = 6;
int dist[MAX_V][MAX_V]; // dist[i][j]:init is cost from i to j

void initGraph()
{
	dist[0][1] = 4;
	dist[0][2] = 2;
	dist[1][2] = 1;
	dist[1][3] = 3;
	dist[2][3] = 5;
	dist[2][4] = 1;
	dist[3][4] = 2;
	dist[3][5] = 1;

	dist[1][0] = 4;
	dist[2][0] = 2;
	dist[2][1] = 1;
	dist[3][1] = 3;
	dist[3][2] = 5;
	dist[4][2] = 1;
	dist[4][3] = 2;
	dist[5][3] = 1;

	// 增加负权环
	//dist[4][5] = -4;
	//dist[5][4] = -4;

}

void warshall_floyd()
{
	for (int i = 0; i < MAX_V; i++)
		for (int j = 0; j < MAX_V; j++)
		{
			if (i == j) dist[i][j] = 0;
			else dist[i][j] = 10000; // edge does no exist
		}
	initGraph();
	for (int k = 0; k < MAX_V; k++) // 加入第k个节点
		for (int i = 0; i < MAX_V; i++) // 松弛i行
			for (int j = 0; j < MAX_V; j++) // 松弛j列
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]); // 经过当前节点和不经过当前节点
}

// 判断是否有负权环
//判断图中是否有负圈，只需检查是否存在d[i][i]是负数的顶点就可以了。
bool has_negative_cycle()
{
	for (int i = 0; i < MAX_V; i++)
		if (dist[i][i] < 0) return true;
	return false;
}

int main()
{
	

	warshall_floyd();

	for (int i = 0; i < MAX_V; i++)
	{
		cout << "节点" << i << "的最短路：";
		for (int j = 0; j < MAX_V; j++)
		{
			cout << dist[i][j] << " ";
		}
		cout << endl;
	}

	bool rs = has_negative_cycle();
	cout << rs << endl;
	return 0;
}

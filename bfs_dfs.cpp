#include <iostream>
#include <stack>
#include <queue>
using namespace std;

struct Node {
    int data;
    struct Node* lChild;
    struct Node* rChild;
    Node(int data):data(data) {}
};

void dfs(Node* root) {
    if (!root) return;

    stack<Node*> s;
    s.push(root);

    while(!s.empty()) {
        Node* node = s.top();
        cout << node->data << " ";
        s.pop();
        if (node->rChild) s.push(node->rChild);
        if (node->lChild) s.push(node->lChild);
    }
}

void bfs(Node* root) {
    if (!root) return;

    queue<Node*> que;
    que.push(root);

    while(!que.empty()) {
        Node* node = que.front();
        cout << node->data << " ";
        que.pop();
        if (node->lChild) que.push(node->lChild);
        if (node->rChild) que.push(node->rChild);
    }
}

int main()
{
    Node root(20);
    root.lChild = new Node(10);
    root.rChild = new Node(30);
    cout << "dfs:" << endl;
    dfs(&root);
    cout << endl << "bfs:" << endl;
    bfs(&root);
    cout << endl;
    return 0;
}
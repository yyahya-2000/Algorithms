#include "ReadWriter.h"
#include <stack>

using namespace std;


class Node {
public:
    int number;
    int component;
};

int getComponents(vector<Edge> &result, vector<Node> &nodes) {
    stack<Node> nodesStack;
    vector<bool> used;
    int size = nodes.size();
    int component = 0;
    nodesStack.push(nodes[0]);

    for (int i = 0; i < size; ++i)
        used.push_back(false);
    used[0] = true;


    while (size > 0) {
        while (!nodesStack.empty()) {
            Node node = nodesStack.top();
            nodesStack.pop();
            node.component = component;
            nodes[node.number].component = component;
            size--;

            for (auto &i : result) {
                if (i.A == node.number && !used[i.B]) {
                    nodesStack.push(nodes[i.B]);
                    used[i.B] = true;
                }
                if (i.B == node.number && !used[i.A]) {
                    nodesStack.push(nodes[i.A]);
                    used[i.A] = true;
                }
            }
        }
        for (int j = 0; j < nodes.size(); ++j) {
            if (!used[j]) {
                nodesStack.push(nodes[j]);
                used[j] = true;
                break;
            }
        }
        component++;
    }
    return component;
}

vector<Node> getNodes(int N) {
    vector<Node> nodes;
    for (int i = 0; i < N; ++i) {
        Node node{};
        node.number = i;
        node.component = i;
        nodes.push_back(node);
    }
    return nodes;
}


void pushEdge(vector<Edge> &result, Edge spanningTreeEdge) {
    if (!any_of(result.begin(), result.end(),
                [&spanningTreeEdge](Edge &i) { return i.number == spanningTreeEdge.number; })) {
        result.push_back(spanningTreeEdge);
    }
}

void fillEdges(int N, vector<Edge> &spanningTreeEdges) {
    for (int i = 0; i < N; ++i) {
        Edge tempEdge{};
        tempEdge.W = 30000;
        spanningTreeEdges.push_back(tempEdge);
    }
}

void solve(int N, int M, vector<Edge> &edges, vector<Edge> &result) {
    vector<Node> nodes = getNodes(N);

    vector<Edge> spanningTreeEdges;
    fillEdges(N, spanningTreeEdges);


    while (result.size() < N - 1) {
        for (int j = 0; j < M; ++j) {
            if (nodes[edges[j].A].component != nodes[edges[j].B].component) {
                if (spanningTreeEdges[nodes[edges[j].A].component].W > edges[j].W)
                    spanningTreeEdges[nodes[edges[j].A].component] = edges[j];
                if (spanningTreeEdges[nodes[edges[j].B].component].W > edges[j].W)
                    spanningTreeEdges[nodes[edges[j].B].component] = edges[j];
            }
        }

        for (auto &spanningTreeEdge : spanningTreeEdges) {
            pushEdge(result, spanningTreeEdge);
        }

        if (result.size() == N - 1)
            break;

        spanningTreeEdges.clear();
        int compsNum = getComponents(result, nodes);

        fillEdges(compsNum, spanningTreeEdges);
    }

}

int main() {
    ReadWriter rw;

    int N, M;
    rw.read2Ints(N, M);

    vector<Edge> edges;
    rw.readEgdes(M, edges);

    vector<Edge> result;

    solve(N, M, edges, result);

    rw.writeInt(result.size());
    rw.writeEdges(result);

    return 0;
}
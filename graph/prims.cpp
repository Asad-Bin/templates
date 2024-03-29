vi taken;               // global boolean flag to avoid cycle
priority_queue<ii> pq;  // priority queue to help choose shorter edges
// note: default setting for C++ STL priority_queue is a max heap
void process(int vtx) {  // so, we use -ve sign to reverse the sort order
    taken[vtx] = 1;
    for (int j = 0; j < (int)AdjList[vtx].size(); j++) {
        ii v = AdjList[vtx][j];
        if (!taken[v.first]) pq.push(ii(-v.second, -v.first));
    }
}  // sort by (inc) weight then by (inc) id
// inside int main()---assume the graph is stored in AdjList, pq is empty
taken.assign(V, 0);  // no vertex is taken at the beginning
process(0);          // take vertex 0 and process all edges incident to vertex 0
mst_cost = 0;
while (!pq.empty()) {  // repeat until V vertices (E=V-1 edges) are taken
    ii front = pq.top();
    pq.pop();
    u = -front.second, w = -front.first;  // negate the id and weight again
    if (!taken[u])                        // we have not connected this vertex yet
        mst_cost += w, process(u);        // take u, process all edges incident to u
}  // each edge is in pq only once!
printf("MST cost = %d (Prim's)\n", mst_cost

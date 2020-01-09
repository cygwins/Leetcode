class Solution {
public:
    vector<vector<int>> colorBorder(vector<vector<int>>& G, int r0, int c0, int bc) {
        if(G.empty()) return G; // Grid not exist
        int cc = G[r0][c0];
        if(cc == bc) return G; // Component Color == Border Color
        vector<vector<int>> D{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // Direction
        auto og = [G](int r, int c) { // Outside Grid
            return r < 0 || c < 0 || r >= G.size() || c >= G[0].size();
        };
        auto ib = [G, D, og](int r, int c) { // Position Is a Border square
            for(int d = 0; d < D.size(); ++d) {
                int rt = r + D[d][0], ct = c + D[d][1]; // R/C Temp
                if(og(rt, ct) || G[rt][ct] != G[r][c]) return true;
            }
            return false;
        };
        auto mv = [](vector<int> p, vector<int> d) { // MoVe p to dirction d
            return vector<int>{p[0] + d[0], p[1] + d[1]};
        };
        set<vector<int>> B; // Border
        queue<vector<int>> Q; // queue for BFS
        map<vector<int>, bool> inQ;
        Q.push({r0, c0});
        inQ[{r0, c0}] = true;
        while(!Q.empty()) {
            int rh = Q.front()[0], ch = Q.front()[1]; // R/C head
            for(int d = 0; d < D.size(); ++d) {
                int rt = rh + D[d][0], ct = ch + D[d][1]; // R/C temp
                if(!og(rt, ct) && G[rt][ct] == cc && !inQ[{rt, ct}]) {
                    Q.push({rt, ct});
                    inQ[{rt, ct}] = true;
                }
            }
            if(ib(rh, ch)) B.insert({rh, ch});
            Q.pop();
        }
        for(auto &v : B) {
            G[v[0]][v[1]] = bc;
        }
        return G;
    }
};

/*
 * 1DFS: 0 -> f farthest
 * 2DFS: f -> g farthest
 * answer: mid-point(s) on path f---g 
 */
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Solution {
    List<Integer>[] E; // neighbors
    int[] prev; // previous node on path
    int f, g, d, maxL;
    public List<Integer> findMinHeightTrees(int n, int[][] edges) {
        if(n <= 0) { return new ArrayList<>(); }
        // if(n == 1) { return Arrays.asList<>(0); }
        E = new List[n];
        for (int i = 0; i < n; i++) { E[i] = new ArrayList<>(); }
        for (int[] pair : edges) {
            int u = pair[0];
            int v = pair[1];
            E[u].add(v);
            E[v].add(u);
        }
        prev = new int[n];
        d = 0; maxL = 0; DFS(0, -1);
        g = f;
        d = 0; maxL = 0; DFS(f, -1);
        int u = f;
        for(int i = 0; i < maxL / 2; i++) {
            u = prev[u];
        }
        ArrayList<Integer> answer = new ArrayList<>(); 
        answer.add(u);
        if(maxL % 2 == 1) { answer.add(prev[u]); }
        return answer;
    }

    private void DFS(int u, int parent) { // java pass all arguments by reference
        for(int v : E[u]) {
            if(v != parent) {
                d++;
                prev[v] = u;
                if(d > maxL) {
                    maxL = d;
                    f = v;
                }
                DFS(v, u);
                d--;
            }
        }
    }

    public static void main(String[] args) {
        Solution s = new Solution();
        int[][] g = new int[][] {{1,0},{1,2},{1,3}};
        int[][] h = new int[][] {{0,3},{1,3},{2,3},{4,3},{5,4}};
        System.out.print(s.findMinHeightTrees(4, g));
        System.out.print(s.findMinHeightTrees(6, h));
    }
}

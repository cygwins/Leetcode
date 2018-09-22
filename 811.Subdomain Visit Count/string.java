import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.lang.Integer;

class Solution {
    public List<String> subdomainVisits(String[] cpdomains) {
        Map<String,Integer> counts = new HashMap<String,Integer>();
        List<String> answer = new ArrayList<String>();
        for(String cpd : cpdomains) {
            String[] cpds = cpd.split(" ");
            int c = Integer.parseInt(cpds[0]);
            inc(counts, cpds[1], c);
            String[] subs = cpds[1].split("\\.");
            inc(counts, subs[subs.length - 1], c);
            if(subs.length > 2) inc(counts, subs[1] + "." + subs[2], c);
        }
        for(Map.Entry m : counts.entrySet()){
            answer.add(m.getValue() + " " + m.getKey());
        }
        return answer;
    }
    private void inc(Map<String,Integer> m, String s, int c) {
        if(!m.containsKey(s)) m.put(s, c);
        else m.put(s, m.get(s) + c);
    }
    public static void main(String[] args) {
        Solution S = new Solution();
        String[] c = {"900 google.mail.com", "50 yahoo.com", "1 intel.mail.com", "5 wiki.org"};
        List<String> answer = S.subdomainVisits(c);
        for(String s : answer) System.out.println(s);
    }
}

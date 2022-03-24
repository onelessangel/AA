import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;

public abstract class Task {

    public static class Edge {
        protected final int u;
        protected final int v;

        protected Edge(int u, int v) {
            this.u = u;
            this.v = v;
        }
    }

    public abstract void solve() throws IOException, InterruptedException;

    public abstract void readProblemData() throws IOException;

    public abstract void formulateOracleQuestion() throws IOException, InterruptedException;

    public abstract void decipherOracleAnswer() throws IOException;

    public abstract void writeAnswer() throws IOException;

    public void askOracle() throws IOException, InterruptedException {
        ProcessBuilder builder = new ProcessBuilder();
        builder.redirectErrorStream(true);
        builder.command("python3", "sat_oracle.py", "sat.cnf", "sat.sol");
        Process process = builder.start();
        BufferedReader in = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String buffer;
        StringBuilder output = new StringBuilder();

        while ((buffer = in.readLine()) != null) {
            output.append(buffer).append("\n");
        }

        int exitCode = process.waitFor();
        if (exitCode != 0) {
            System.err.println("Error encountered while running oracle");
            System.err.println(output.toString());
            System.exit(-1);
        }
    }

    /**
     * Stores variables in a hashtable, each node having assigned a list with its variables.
     * @param n nodes
     * @param k variables for each node
     * @return the hashtable for given graph
     */
    public HashMap<Integer, ArrayList<Integer>> storeVariables(int n, int k) {
        HashMap<Integer, ArrayList<Integer>> variables= new HashMap<>();
        int counter = 1;

        for (int node = 1; node <= n; node++) {
            variables.put(node, new ArrayList<>());
            for (int i = 0; i < k; i++) {
                variables.get(node).add(counter);
                counter++;
            }
        }

        return variables;
    }

    /**
     * Creates list of non edges.
     * @param n nodes
     * @param edgesList of current graph
     * @return list of non edges of current graph
     */
    public ArrayList<Edge> createNonEdgesList(int n, ArrayList<Edge> edgesList) {
        ArrayList<Edge> nonEdgesList = new ArrayList<>();

        for (int u = 1; u <= n; u ++) {
            for (int v = u + 1; v <= n; v++) {
                boolean nonEdge = true;

                for (Edge edge : edgesList) {
                    if (edge.u != u || edge.v != v) {
                        continue;
                    }

                    nonEdge = false;
                    break;
                }

                if (!nonEdge) {
                    continue;
                }

                nonEdgesList.add(new Edge(u, v));
            }
        }

        return nonEdgesList;
    }
}
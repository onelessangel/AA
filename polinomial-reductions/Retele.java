import java.io.*;
import java.util.*;

class Retele extends Task {
    private int n;
    private int m;
    private int k;
    private final ArrayList<Edge> edgesList;
    private HashMap<Integer, ArrayList<Integer>> variables;
    private String result;
    private int[] coverage;

    public Retele(int n, int m, int k, ArrayList<Edge> edgesList) {
        this.n = n;
        this.m = m;
        this.k = k;
        this.edgesList = edgesList;
        variables = new HashMap<>();
        coverage = null;
    }

    public Retele() {
        this(0, 0, 0, new ArrayList<>());
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        Retele retea = new Retele();
        retea.readProblemData();
        retea.solve();
        retea.writeAnswer();
    }

    @Override
    public void readProblemData() {
        Scanner in = new Scanner(System.in);

        n = in.nextInt();
        m = in.nextInt();
        k = in.nextInt();

        for (int i = 0; i < m; i++) {
            edgesList.add(new Edge(in.nextInt(), in.nextInt()));
        }
    }

    @Override
    public void solve() throws IOException, InterruptedException {
        formulateOracleQuestion();
        askOracle();
        decipherOracleAnswer();
    }

    @Override
    public void formulateOracleQuestion() throws IOException {
        BufferedWriter writer = new BufferedWriter(new FileWriter("sat.cnf"));
        StringBuilder satOutput = new StringBuilder("p cnf ");

        variables = storeVariables(n, k);

        int numberOfVariables = n * k;
        int numberOfClauses = k + (k - 1) * k / 2 * n + (n * (n - 1) / 2 - m) * k * (k - 1);

        satOutput.append(numberOfVariables).append(" ");
        satOutput.append(numberOfClauses).append("\n");

        writeFirstClauses(satOutput);
        writeSecondClauses(satOutput);
        writeThirdClauses(satOutput);

        writer.write(String.valueOf(satOutput));
        writer.close();
    }

    /**
     *  (y1,r V y2,r V ... V yn,r), for each r, 1 ≤ r ≤ k
     */
    private void writeFirstClauses(StringBuilder satOutput) {
        for (int index = 0; index < k; index++) {
            for (int node = 1; node <= n; node++) {
                satOutput.append(variables.get(node).get(index)).append(" ");
            }
            satOutput.append(0).append("\n");
        }
    }

    /**
     *  (¬yi,r V ¬yi,s), for each 1 ≤ i ≤ n, 1 ≤ r, s ≤ k and r ≠ s
     */
    private void writeSecondClauses(StringBuilder satOutput) {
        for (int node = 1; node <= n; node++) {
            for (int i = 0; i < k; i++) {
                for (int j = i + 1; j < k; j++) {
                    satOutput.append(-variables.get(node).get(i)).append(" ");
                    satOutput.append(-variables.get(node).get(j)).append(" ");
                    satOutput.append(0).append("\n");
                }
            }
        }
    }

    /**
     *  (¬yu,r V ¬yv,s), for each (u, v) non-edge of graph G, r ≠ s
     */
    private void writeThirdClauses(StringBuilder satOutput) {
        ArrayList<Edge> nonEdgesList = createNonEdgesList(n, edgesList);

        for (Edge edge : nonEdgesList) {
            for (int i = 0; i < k; i++) {
                for (int j = 0; j < k; j++ ) {
                    if (i == j) {
                        continue;
                    }

                    satOutput.append(-variables.get(edge.u).get(i)).append(" ");
                    satOutput.append(-variables.get(edge.v).get(j)).append(" ");
                    satOutput.append(0).append("\n");
                }
            }
        }
    }

    @Override
    public void decipherOracleAnswer() throws IOException {
        BufferedReader solutionReader= new BufferedReader(new FileReader("sat.sol"));
        result = solutionReader.readLine();
//
        if (result.equals("False")) {
            return;
        }

        // reads the number of variables
        solutionReader.readLine();

        // reads variables
        StringTokenizer variables = new StringTokenizer(solutionReader.readLine());

        coverage = new int[k];

        // stores each node at the correct index in the clique coverage
        for (int node = 1; node <= n; node++) {
            for (int index = 0; index < k; index++) {
                int currentVariable = Integer.parseInt(variables.nextToken());

                if (currentVariable < 0) {
                    continue;
                }

                coverage[index] = node;
            }
        }
    }

    @Override
    public void writeAnswer() {
        System.out.println(result);

        if (coverage == null) {
            return;
        }

        for (int node : coverage) {
            System.out.print(node + " ");
        }
    }

    public String getResult() {
        return result;
    }

    public int[] getCoverage() {
        return coverage;
    }
}
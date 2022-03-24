import java.io.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;
import java.util.StringTokenizer;

class Registre extends Task {
    private int n;
    private int m;
    private int k;
    private final ArrayList<Edge> edgesList;
    private HashMap<Integer, ArrayList<Integer>> variables;
    private String result;
    private final ArrayList<Integer> registers;

    public Registre(int n, int m, int k) {
        this.n = n;
        this.m = m;
        this.k = k;
        edgesList = new ArrayList<>();
        variables = new HashMap<>();
        registers = new ArrayList<>();
    }

    public Registre() {
        this(0, 0, 0);
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        Registre registre = new Registre();
        registre.readProblemData();
        registre.solve();
        registre.writeAnswer();
    }

    @Override
    public void solve() throws IOException, InterruptedException {
        formulateOracleQuestion();
        askOracle();
        decipherOracleAnswer();
    }

    @Override
    public void readProblemData() {
        Scanner in = new Scanner(System.in);

        n = in.nextInt();
        m = in.nextInt();
        k = in.nextInt();

        for (int i = 0; i < m; i ++) {
            edgesList.add(new Edge(in.nextInt(), in.nextInt()));
        }
    }

    @Override
    public void formulateOracleQuestion() throws IOException {
        BufferedWriter writer = new BufferedWriter((new FileWriter("sat.cnf")));
        StringBuilder satOutput = new StringBuilder("p cnf ");

        variables = storeVariables(n, k);

        int numberOfVariables = n * k;
        int numberOfClauses = n + (k - 1) * k / 2 * n + k * m;

        satOutput.append(numberOfVariables).append(" ");
        satOutput.append(numberOfClauses).append("\n");

        writeFirstClauses(satOutput);
        writeSecondClauses(satOutput);
        writeThirdClauses(satOutput);

        writer.write(String.valueOf(satOutput));
        writer.close();
    }

    /**
     *  (yi,1 V yi,2 V ... V yi,k), for each i, 1 ≤ i ≤ n
     */
    private void writeFirstClauses(StringBuilder satOutput) {
        for (int node = 1; node <= n; node++) {
            for (int index = 0; index < k; index++) {
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
     *  (¬yu,r V ¬yv,r), for each (u, v) edge of graph G, 1 ≤ r ≤ k
     */
    private void writeThirdClauses(StringBuilder satOutput) {
        for (Edge edge : edgesList) {
            for (int i = 0; i < k; i++) {
                satOutput.append(-variables.get(edge.u).get(i)).append(" ");
                satOutput.append(-variables.get(edge.v).get(i)).append(" ");
                satOutput.append(0).append("\n");
            }
        }
    }

    @Override
    public void decipherOracleAnswer() throws IOException {
        BufferedReader solutionReader= new BufferedReader(new FileReader("sat.sol"));
        result = solutionReader.readLine();

        if (result.equals("False")) {
            return;
        }

        // reads the number of variables
        solutionReader.readLine();

        // reads variables
        StringTokenizer variables = new StringTokenizer(solutionReader.readLine());

        // stores register used for each node
        for (int node = 1; node <= n; node++) {
            for (int index = 0; index < k; index++) {
                int currentVariable = Integer.parseInt(variables.nextToken());

                if (currentVariable < 0) {
                    continue;
                }

                registers.add(index + 1);
            }
        }
    }

    @Override
    public void writeAnswer() {
        System.out.println(result);

        if (registers.isEmpty()) {
            return;
        }

        for (int register : registers) {
            System.out.print(register + " ");
        }
    }
}
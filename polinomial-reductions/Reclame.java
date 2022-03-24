import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

class Reclame extends Task {
    private int n;
    private int m;
    private int k;
    private final ArrayList<Edge> edgesList;
    private ArrayList<Edge> nonEdgesList;
    private final ArrayList<Integer> coverage;
    private int[] coverageClique;

    public Reclame(int n, int m, int k) {
        this.n = n;
        this.m = m;
        this.k = k;
        edgesList = new ArrayList<>();
        nonEdgesList = new ArrayList<>();
        coverage = new ArrayList<>();
    }

    public Reclame() {
        this(0, 0, 0);
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        Reclame reclama = new Reclame();
        reclama.readProblemData();
        reclama.solve();
        reclama.writeAnswer();
    }

    @Override
    public void readProblemData() {
        Scanner in = new Scanner(System.in);

        n = in.nextInt();
        m = in.nextInt();

        for (int i = 0; i < m; i++) {
            edgesList.add(new Edge(in.nextInt(), in.nextInt()));
        }

        nonEdgesList = createNonEdgesList(n, edgesList);

        for (int node = 1; node <= n; node++) {
            coverage.add(node);
        }
    }

    @Override
    public void solve() throws IOException, InterruptedException {
        formulateOracleQuestion();
        decipherOracleAnswer();
    }

    @Override
    public void formulateOracleQuestion() throws IOException, InterruptedException {
        while (true) {
            k++;
            Retele retea = new Retele(n, m, k, nonEdgesList);
            retea.solve();

            // if there is a clique for the current complementary graph, the coverage is saved
            if (retea.getResult().equals("True")) {
                coverageClique = retea.getCoverage();
                continue;
            }

            // if there is no clique for the current complementary graph, exits from loop
            break;
        }
    }

    @Override
    public void decipherOracleAnswer() {
        // the nodes that are in the clique coverage are not in the vertex cover
        for (int element : coverageClique) {
            coverage.remove(Integer.valueOf(element));
        }
    }

    @Override
    public void writeAnswer() {
        for (int node : coverage) {
            System.out.print(node + " ");
        }
    }
}
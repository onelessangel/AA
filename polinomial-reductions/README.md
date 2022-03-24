Copyright Teodora Stroe 321CA 2022

# Repository folder structure
```
.
├── check
├── check_utils
├── install.sh
├── Makefile
├── README.md
├── Reclame.java
├── Registre.java
├── Retele.java
├── run_example.sh
├── sat_oracle.py
├── Task.java
└── tasks

```

# Implementation

For each task, the variables are retained in a **hashtable**, each node having assigned a list of variables 
for each index.

## Retele ━ Clique Problem

Let the graph be G = (V, E).

Variables: **yi,r**, for 1 ≤ i ≤ n and 1 ≤ r ≤ k -- true if node i is the rth in the clique.

### Clauses

1. There is at least one node for each element of the clique:
> **(y1,r V y2,r V ... V yn,r)**, for each r, 1 ≤ r ≤ k

2. No node is both the rth and sth element of the clique:
> **(¬yi,r V ¬yi,s)**, for each 1 ≤ i ≤ n, 1 ≤ r, s ≤ k and r ≠ s

3. If there is no edge between 2 nodes, they cannot both be in the clique:
> **(¬yu,r V ¬yv,s)**, for each (u, v) ∉ E, r ≠ s

### Oracle answer interpretation

Reading groups of n variables, the index of the *true* variable is the index of the current node in the
clique.

### Complexity

This solution has Θ(n<sup>2</sup>k<sup>2</sup>) complexity.

## Reclame ━ Vertex Cover Problem

Let the graph be G = (V, E).

Let the complementary graph be G' = (V, E'), E' = { (u, v) | (u, v) ∉ E }.

The essential group of a graph is its vertex cover.

The Vertex Cover Problem can be reduced to the Clique Problem. If G' has a clique of size **k**, then
G has a vertex cover of size **V - k**. Therefore, the nodes that are **not** in the clique of graph G' 
are in the vertex cover of the G graph.

In order to find the minimum vertex cover of graph G, the oracle is called several times to find the maximum size 
clique of the G' graph.

### Complexity

This solution has Θ(n<sup>2</sup>k<sup>2</sup>) complexity.

## Registre ━ k-coloring Problem

Let the graph be G = (V, E).

Variables: **yi,r**, for 1 ≤ i ≤ n and 1 ≤ r ≤ k -- true if node i has r register.

### Clauses

1. There is at least one register assigned to each node:
> **(yi,1 V yi,2 V ... V yi,k)**, for each i, 1 ≤ i ≤ n

2. No node has multiple registers assigned:
> **(¬yi,r V ¬yi,s)**, for each 1 ≤ i ≤ n, 1 ≤ r, s ≤ k and r ≠ s

3. If there is an edge between 2 nodes, they cannot both be assigned the same register:
> **(¬yu,r V ¬yv,r)**, for each (u, v) ∈ E, 1 ≤ r ≤ k

### Oracle answer interpretation

Reading groups of n variables, the index of the *true* variable determines the register assigned to the 
current node.

### Complexity

This solution has Θ(nk<sup>2</sup>) complexity.
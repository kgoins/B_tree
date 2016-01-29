# B_tree

Overview:
A bTree is a self­balancing tree structure comprised of nodes. It is the general form of a binary tree and is classified by its degree. The degree denotes the total number of children that each node of the tree can have, with degree ­1 being the total number of elements held in a given node. For example, a binary tree is a degree 2 bTree.

Performance:
● Time complexity: Search,Insert,Delete are all O(lg(n))
● Space complexity: O(n)

Known Bugs:
1. Can’t handle non­unique strings
2. Doesn’t overload any operators
3. Can only handle even degrees. This implementation uses the top­down approach for
the sake of efficiency and therefore pre­emptively splits/merges nodes to optimize results. The bTree constructor increments all odd values by one to compensate for this.

global INF 
INF = float('inf')

class myTree:
    def __init__(self):
        self.tree = {}

    def addInfo(self, parent, children):
        self.tree[parent] = children
  
    def postorder(self, root):
        if root == '.': return
        self.postorder(self.tree[root][0])
        self.postorder(self.tree[root][1])
        if "postorder_answer" not in self.tree:
            self.tree["postorder_answer"] = [root]
        else:
            self.tree["postorder_answer"].append(root)
        return self.tree["postorder_answer"]

class myGraph:
    def __init__(self, vertex, matrix):
        self.vertex = vertex
        self.matrix = matrix

    def find_parent(self, parent, x):
        if parent[x] != x:
            parent[x] = self.find_parent(parent, parent[x])
        return parent[x] 
    def union_parent(self, parent, a, b):
        a = self.find_parent(parent, a)
        b = self.find_parent(parent, b)
        if a < b:
            parent[b] = a
        else:
            parent[a] = b

    def MST(self):
        node_number = len(self.matrix)
        edges_info = []
        temp_tuple = ()
        parent = []
        for i in range(node_number):
            parent.append(i)

        sum = 0
        for i in range(node_number):
            for j in range(i):
                if self.matrix[i][j] == INF:
                    continue
                temp_tuple = self.matrix[i][j], i, j
                edges_info.append(temp_tuple)
        edges_info.sort()

        for edge in edges_info:
            cost, i, j = edge
            if self.find_parent(parent, i) != self.find_parent(parent, j):
                self.union_parent(parent, i, j)
                sum += cost
        return sum
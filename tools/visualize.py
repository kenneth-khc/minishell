import json
import graphviz

class Node:
	def __init__(self, data):
		self.data = data
		self.left: Node | None = None
		self.right:Node | None = None
	
	def print_node(self):
		print(self.data)
		if self.left:
			self.left.print_node()
		if self.right:
			self.right.print_node()
	
def	deserialize(data) -> Node | None:
	if data is None:
		return None
	node = Node(data["string"])
	node.left = deserialize(data.get("left"))
	node.right = deserialize(data.get("right"))
	return node

def	add_edges(graph, node, parent=None):
	if node is None:
		return
	node_id = str(id(node))
	graph.node(node_id, node.data)
	if parent is not None:
		graph.edge(parent, node_id)
	add_edges(graph, node.left, node_id)
	add_edges(graph, node.right, node_id)

def main():
	with open("tree.json", "r") as file:
		data = json.load(file)
	tree: Node | None = deserialize(data)
	if tree:
		tree.print_node()


	dot = graphviz.Digraph()
	dot = graphviz.Graph()
	add_edges(dot, tree)
	dot.render("binary_tree", format="png", view=True)

if __name__ == "__main__":
	main()

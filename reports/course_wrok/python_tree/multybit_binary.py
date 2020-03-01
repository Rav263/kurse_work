from anytree import Node, RenderTree
node      = Node("*")
node_0    = Node("P3: 0*",    parent = node)
node_001  = Node("P1: 001*",  parent = node_0)
node_11   = Node("P4: 11*",   parent = node)
node_1100 = Node("P2: 1100*", parent = node_11)
node_101  = Node("P5: 101*",  parent = node)
node_1011 = Node("P6: 1011*", parent = node_101)

from anytree.exporter import DotExporter
DotExporter(node).to_picture("multybit_compressed.png")


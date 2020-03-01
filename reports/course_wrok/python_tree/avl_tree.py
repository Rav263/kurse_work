from anytree import Node, RenderTree
node_101  = Node("P5: 101* => 5") #5
node_001  = Node("P1: 001* => 1",  parent = node_101) #1
node_0    = Node("P3: 0* => 0",    parent = node_001)  #0
node_11   = Node("P4: 11* => 3",   parent = node_001) #3
node_1100 = Node("P2: 1100* => 12", parent = node_101) #12
node_1011 = Node("P6: 1011* => 13", parent = node_1100) #13

from anytree.exporter import DotExporter
DotExporter(node_101).to_picture("avl_tree.png")


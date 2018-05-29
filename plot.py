# -*- coding: utf-8 -*-

import pickle
import networkx as nx
import matplotlib.pyplot as plt


G = pickle.load(open("GG.pickle", "rb"))
print(G.number_of_nodes())
print(G.number_of_edges())

pos = {}
for n, data in G.nodes(data=True):
  pos[n] = (float(data["y"]), float(data["x"]))

fig = plt.figure(figsize=(8, 7))
ax = plt.gca()
node = nx.draw_networkx_nodes(G, pos, node_size=10)
node.set_edgecolor('k')
nx.draw_networkx_edges(G, pos, lw=1, alpha=0.9, arrows=False)
ax.axis("off")
ax.margins(0)
ax.set_position([0, 0, 1, 1])
plt.savefig("output.png", dpi=150)
plt.close()


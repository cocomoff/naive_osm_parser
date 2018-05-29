# -*- coding: utf-8 -*-
import networkx as nx
import pickle
from copy import deepcopy

G = pickle.load(open("G.pickle", "rb"))
GG = deepcopy(G)

targets = set({
  'motorway',
  'trunk',
  'primary',
  'secondary',
  'tertiary'
  })

# remove unimportant edges
for u, v, data in G.edges(data=True):
  if 'highway' not in data or data['highway'] not in targets:
    GG.remove_edge(u, v)

# remove isolated nodes
for n in G.nodes():
  if GG.degree(n) == 0:
    GG.remove_node(n)

# save cleaned file
pickle.dump(GG, open("GG.pickle", "wb"))

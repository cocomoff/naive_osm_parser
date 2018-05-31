# -*- coding: utf-8 -*-

import pickle
import networkx as nx
from lxml import etree
from copy import deepcopy

# filename = 'hiroshima.osm'
filename = "small_toyota.osm"
tree = etree.parse(filename)
G = nx.DiGraph()

# parse nodes
nodes = tree.xpath("//node")
print("nodes={}".format(len(nodes)))
for idx, n in enumerate(nodes):
  nid = n.attrib['id']
  nx = n.attrib['lat']
  ny = n.attrib['lon']
  G.add_node(nid, x=nx, y=ny)

# parse edges
ways = tree.xpath("//way")
print("ways={}".format(len(ways)))
for idx, e in enumerate(ways):
  eid = e.attrib['id']
  ndrefs = e.xpath("nd")
  ndlist = [ndref.attrib['ref'] for ndref in ndrefs]
  ndhighs = e.xpath("tag")
  ndhighs = [n for n in ndhighs if n.attrib['k'] == 'highway']
  ndoway = [n for n in ndhighs if n.attrib['k'] == 'oneway']
  for i in range(len(ndlist) - 1):
    j = i + 1
    ni = ndlist[i]
    nj = ndlist[j]
    is_oneway = False if not ndoway else (True if ndoway[0].attrib['v'] == 'yes' else False)
    if ndhighs:
      G.add_edge(ni, nj, highway=ndhighs[0].attrib['v'])
      if not is_oneway:
        G.add_edge(nj, ni, highway=ndhighs[0].attrib['v'])
    else:
      G.add_edge(ni, nj)
      if not is_oneway:
        G.add_edge(nj, ni)


# save graph by removing degree 0 vertices
GG = deepcopy(G)
for v in G.nodes():
  if G.degree(v) == 0:
    GG.remove_node(v)

# output
pickle.dump(GG, open("G.pickle", "wb"))


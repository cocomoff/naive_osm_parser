# -*- coding: utf-8 -*-

import pickle
import networkx as nx
from collections import defaultdict
import mpu

from math import sin, cos, sqrt, atan2, radians
R = 6373.0

def latlon2dist(latlon1, latlon2):
  lat1, lon1 = latlon1
  lat2, lon2 = latlon2
  dlon = lon2 - lon1
  dlat = lat2 - lat1
  a = sin(dlat / 2)**2 + cos(lat1) * cos(lat2) * sin(dlon / 2)**2
  c = 2 * atan2(sqrt(a), sqrt(1 - a))
  distance = R * c
  return distance

if __name__ == '__main__':
  G = pickle.load(open("GG.pickle", "rb"))
  print(G.number_of_nodes())
  print(G.number_of_edges())

  # V -> {0, |V|}
  vdict = {}
  vtoxy = {}
  for v, data in G.nodes(data=True):
    vdict[v] = len(vdict)
    vtoxy[v] = (float(data["x"]), float(data["y"]))

  with open("nodes.csv", "w") as f:
    for n in vdict:
      f.write("{}\t{}\n".format(n, vdict[n]))

  # E -> file
  with open('edges.csv', 'w') as f:
    for idx, (u, v, data) in enumerate(G.edges(data=True)):
      d = mpu.haversine_distance(vtoxy[u], vtoxy[v]) * 1000
      f.write("{}\t{}\t{}\n".format(vdict[u], vdict[v], d))

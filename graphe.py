import networkx as nx
from networkx.algorithms import tournament
import numpy as np
import matplotlib.pyplot as plt
import pylab

G = nx.DiGraph()

# ajouter les arcs ici
G.add_edges_from([(4,3)],weight=31)
G.add_edges_from([(2,4)],weight=24)
G.add_edges_from([(4,1)],weight=27)
G.add_edges_from([(4,0)],weight=23)
G.add_edges_from([(3,2)],weight=28)
G.add_edges_from([(1,3)],weight=33)
G.add_edges_from([(0,3)],weight=30)
G.add_edges_from([(2,1)],weight=29)
G.add_edges_from([(0,2)],weight=26)
G.add_edges_from([(1,0)],weight=25)
G.add_edges_from([(0,0)],weight=0)

print(tournament.is_tournament(G))

edge_labels=dict([((u,v,),d['weight'])
                 for u,v,d in G.edges(data=True)])

pos=nx.circular_layout(G)

nx.draw_networkx_edge_labels(G,pos,edge_labels=edge_labels)
nx.draw_networkx(G,pos, node_size=200)
pylab.show()
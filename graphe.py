import networkx as nx
from networkx.algorithms import tournament
import numpy as np
import matplotlib.pyplot as plt
import pylab

G = nx.DiGraph()

# ajouter les arcs ici
G.add_edges_from([(6,2)],weight=55)
G.add_edges_from([(6,5)],weight=51)
G.add_edges_from([(6,7)],weight=50)
G.add_edges_from([(1,5)],weight=50)
G.add_edges_from([(3,2)],weight=50)
G.add_edges_from([(3,7)],weight=49)
G.add_edges_from([(3,4)],weight=49)
G.add_edges_from([(4,2)],weight=49)
G.add_edges_from([(5,2)],weight=48)
G.add_edges_from([(1,0)],weight=48)
G.add_edges_from([(6,4)],weight=47)
G.add_edges_from([(0,5)],weight=47)
G.add_edges_from([(3,1)],weight=47)
G.add_edges_from([(0,7)],weight=46)
G.add_edges_from([(6,3)],weight=46)
G.add_edges_from([(3,5)],weight=46)
G.add_edges_from([(5,7)],weight=45)
G.add_edges_from([(7,2)],weight=45)
G.add_edges_from([(3,0)],weight=45)
G.add_edges_from([(1,7)],weight=44)
G.add_edges_from([(1,2)],weight=44)
G.add_edges_from([(4,7)],weight=43)
G.add_edges_from([(6,0)],weight=42)
G.add_edges_from([(4,1)],weight=42)
G.add_edges_from([(4,0)],weight=42)
G.add_edges_from([(0,2)],weight=42)
G.add_edges_from([(0,0)],weight=0)

print(tournament.is_tournament(G))

edge_labels=dict([((u,v,),d['weight'])
                 for u,v,d in G.edges(data=True)])

pos=nx.circular_layout(G)

nx.draw_networkx_edge_labels(G,pos,edge_labels=edge_labels)
nx.draw_networkx(G,pos, node_size=200)
pylab.show()
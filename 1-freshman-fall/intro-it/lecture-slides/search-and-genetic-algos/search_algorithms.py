# -*- coding: utf-8 -*-
"""
Created on Tue Dec 20 05:24:34 2022

@author: sarva
"""
from heapq import heappop, heappush

def dfs(graph, start, target):
    visited, stack = set(), [start]
    while stack:
        vertex = stack.pop()
        if vertex not in visited:
            visited.add(vertex)
            print("visited %d" % vertex)
            stack.extend(graph[vertex] - visited)
        if vertex == target:
            break
    # return visited


def bfs(graph, start, target):
    visited, queue = set(), [start]
    while queue:
        vertex = queue.pop(0)
        if vertex not in visited:
            visited.add(vertex)
            print("visited %d" % vertex)
            queue.extend(graph[vertex] - visited)
        if vertex == target:
            break
    # return visited

def heuristic(graph, start, target, h):
    start_tuple=(h(target,start), start)
    visited, pqueue = set(), [start_tuple]
    while pqueue:
        vertex_tuple = heappop(pqueue)
        vertex = vertex_tuple[1]
        if vertex not in visited:
            visited.add(vertex)
            print("visited %d, heuristic %d" % (vertex, vertex_tuple[0]))
            for v in graph[vertex] - visited:
                v_tuple = (h(target, v), v)
                heappush(pqueue, v_tuple)
        if vertex == target:
            break
    # return visited

# heuristic function
h = lambda x,y: abs(x-y)

graph = {
    1: {2,5},
    2: {1,3,5},
    3: {2,7,4},
    4: {3,5,6,8},
    5: {1,2,4,6},
    6: {4,5},
    7: {3},
    8: {4}
}


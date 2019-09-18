import os, sys
import random

"""
Can we search in a sorted linked list in better than O(n) time?
The worst case search time for a sorted linked list is O(n) as we can only linearly traverse the list and cannot skip nodes while searching.
For a Balanced Binary Search Tree, we skip almost half of the nodes after one comparison with root.
For a sorted array, we have random access and we can apply Binary Search on arrays.

Can we augment sorted linked lists to make the search faster?
The answer is Skip List.
The idea is simple, we create multiple layers so that we can skip some nodes.
Example:
|*|--------->|6|*|----------------------------------------------------------------->|NIL|
|*|--------->|6|*|-------------------------------------------------------->|25|*|-->|NIL|
|*|--------->|6|*|----------->|9|*|------------>|17|*|-------------------->|25|*|-->|NIL|
|*|-->|3|*-->|6|*|-->|7|*|--->|9|*|-->|12|*|-->|17|*|-->|19|*|-->|21|*|-->|25|*|-->|NIL|
"""
class Node(object):
    """
    class to implement node
    """
    def __init__(self, key, level):
        self.key = key
        self.forward = [None]*(level+1)

class SkipList(object):
    """
    class for skip list
    """
    def __init__(self, max_lvl, P):
        self.MAXLVL = max_lvl
        self.P = P

        self.header = self.createNode(self.MAXLVL, -1)
        self.level = 0

    def createNode(self, lvl, key):
        n = Node(key, lvl)
        return n

    def randomLevel(self):
        lvl = 0
        r = random.random()
        while r < self.P and lvl < self.MAXLVL:
            lvl += 1
            r = random.random()
        return lvl

    def insert(self, key):
        update = [None]*(self.MAXLVL+1)
        current = self.header

        for i in range(self.level, -1, -1):
            while current.forward[i] and \
                current.forward[i].key < key:
                current = current.forward[i]
            update[i] = current
        #we should reach to the bottom level
        current = current.forward[0]
        if current == None or current.key != key:
            rlevel = self.randomLevel()
            if rlevel > self.level:
                for i in range(self.level+1, rlevel+1):
                    update[i] = self.header
                self.level = rlevel
            n = self.createNode(rlevel, key)
            for i in range(rlevel+1):
                n.forward[i] = update[i].forward[i]
                update[i].forward[i] = n
            print 'successfully inserted key {}'.format(key)

    def delete(self, key):
        update = [None]*(self.MAXLVL+1)
        current = self.header

        for i in range(self.level, -1, -1):
            while current.forward[i] and current.forward[i].key < key:
                current = current.forward[i]
            update[i] = current

        current = current.forward[0]

        if current!=None and current.key == key:
            for i in range(self.level+1):
                if update[i].forward[i] != current:
                    break
                update[i].forward[i] = current.forward[i]
            while self.level > 0 and self.header.forward[self.level] == None:
                self.level -= 1
            print 'successfully deleted one key {}'.format(key)

    def search(self, key):
        current = self.header

        for i in range(self.level, -1, -1):
            while current.forward[i] and current.forward[i].key < key:
                current = current.forward[i]

        current = current.forward[0]
        if current != None and current.key == key:
            print 'key found {}'.format(key)
        else:
            print 'key {} not found'.format(key)

    def __str__(self):
        s = '\n***Skip List***\n'
        head = self.header
        for lvl in range(self.level, -1, -1):
            s += 'Level {}:'.format(lvl)
            lvlkeys = []
            node = head.forward[lvl]
            while node!=None:
                lvlkeys.append(node.key)
                node = node.forward[lvl]
            s += str(lvlkeys) + '\n'
        return s

if __name__ == '__main__':
    lst = SkipList(3, 0.5)
    lst.insert(3)
    lst.insert(6)
    lst.insert(7)
    lst.insert(9)
    lst.insert(12)
    lst.insert(19)
    lst.insert(17)
    lst.insert(26)
    lst.insert(21)
    lst.insert(25)
    print lst
    lst.search(19)
    lst.search(30)
    lst.search(12)
    lst.search(21)
    lst.delete(21)
    print lst
    lst.search(21)

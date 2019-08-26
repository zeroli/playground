import os, sys
import random

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
    
    def insertElement(self, key):
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
    
    def deleteElement(self, key):
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

    def searchElement(self, key):
        current = self.header
        
        for i in range(self.level, -1, -1):
            while current.forward[i] and current.forward[i].key < key:
                current = current.forward[i]
        
        current = current.forward[0]
        if current != None and current.key == key:
            print 'key found {}'.format(key)
        else:
            print 'key {} not found'.format(key)
    
    def displayList(self):
        print '\n***Skip List***'
        head = self.header
        for lvl in range(self.level+1):
            print 'Level {}:'.format(lvl),
            node = head.forward[lvl]
            while node!=None:
                print node.key, 
                node = node.forward[lvl]
            print

def main():
    lst = SkipList(3, 0.5)
    lst.insertElement(3) 
    lst.insertElement(6) 
    lst.insertElement(7) 
    lst.insertElement(9) 
    lst.insertElement(12) 
    lst.insertElement(19) 
    lst.insertElement(17) 
    lst.insertElement(26) 
    lst.insertElement(21) 
    lst.insertElement(25)
    lst.displayList()
    lst.searchElement(19)
    lst.searchElement(30)
    lst.searchElement(12)
    lst.searchElement(21)
    lst.deleteElement(21)
    lst.displayList()
    lst.searchElement(21)

main()

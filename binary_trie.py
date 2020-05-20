import random
import os

"""binary trie
reference:  $13.1: Binary Trie @ http://opendatastructures.org/
"""

left_ = 0
right_ = 1
prev_ = 0
next_ = 1
w = 32

class TrieNode(object):
    def __init__(self):
        self._x = None
        self._child = [None, None]
        self._parent = None
        self._jump = None

class BinaryTrie(object):
    def __init__(self):
        self._root = TrieNode()
        # keep track of all leaves on level w
        self._dummy = TrieNode()
        # form one circular doubly-linked list
        self._dummy._child[prev_] = self._dummy
        self._dummy._child[next_] = self._dummy
        # count how many elements in the tree
        self._n = 0

    def add(self, x):
        print 'add {}: {:032b}'.format(x, x)
        ix = x
        c = 0
        u = self._root
        #1: follow the search path until falling out of tree
        for i in xrange(0, w):
            c = (ix >> (w - i - 1)) & 1
            if u._child[c] is None: break
            u = u._child[c]
        else: # already there
            return True

        if u == self._root:
            pred = self._dummy
        else:
            pred = u._jump if c == right_ else u._jump._child[prev_]

        u._jump = None
        #2: create the remaining nodes of x
        for j in xrange(i, w):
            c = (ix >> (w - j - 1)) & 1
            u._child[c] = TrieNode()
            u._child[c]._parent = u
            u = u._child[c]
        u._x = x
        #3: insert node of x in the doubly-linked list for leaves

        u._child[prev_] = pred
        u._child[next_] = pred._child[next_]
        u._child[prev_]._child[next_] = u
        u._child[next_]._child[prev_] = u
        #4: traverse back up to update parent's jump pointers
        v = u._parent
        while v:
            if (v._child[left_] is None and (v._jump is None or v._jump._x > x)) or \
                (v._child[right_] is None and (v._jump is None or v._jump._x < x)):
                v._jump = u
            v = v._parent

        self._n += 1
        return True

    def remove(self, x):
        print 'remove {}: {:032b}'.format(x, x)

        ix = x
        c = 0
        u = self._root
        #1: follow the search path until found it
        for i in xrange(0, w):
            c = (ix >> (w - i - 1)) & 1
            if u._child[c] is None: return False  # not found it, fail
            u = u._child[c]
        else: # found it
            print 'found, and then remove it later'

        #2: unlink it from doubly linked list for leaves
        u._child[prev_]._child[next_] = u._child[next_]
        u._child[next_]._child[prev_] = u._child[prev_]

        v = u
        #3: traverse back up to delete parent nodes
        for i in xrange(w-1, -1, -1):
            c = (ix >> (w - i - 1)) & 1
            v = v._parent
            v._child[c] = None
            if v._child[1-c] is not None: # the other subtree is there
                break

        #4: adjust those ancestor's jump pointer, which was pointing to this u
        c = (ix >> (w - i - 1)) & 1
        #if c=0(left), deleting left subtree, right tree is there
        #assign jump to smallest node in right subtree (1-c), which is exactly next of u in doubly linked list
        #if c=1(right), deleting right subtree, left tree is there
        #assign jump to largest node in left subtree (1-c), which is exactly prev of u in doubly linked list
        v._jump = u._child[1-c] # before, v._jump might be None
        v = v._parent
        i -= 1
        for j in xrange(i, -1, -1):
            c = (ix >> (w - j - 1)) & 1
            #if c=0, left is there, jump points to larget one in left-subtree
            #if c=1, right is there, jump points to smallest one in right-subtree
            #so c=0, jump should still point to the largest one, after u removed
            #that's u's precedence
            #the code in book is wrong here, it was 'u._child[1-c]'
            if v._jump == u:
                v._jump = u._child[c]
            v = v._parent

        self._n -= 1

        return True

    def find(self, x):
        print 'find {}: {:032b}'.format(x, x)
        ix = x
        c = 0
        u = self._root
        for i in xrange(0, w):
            c = (ix >> (w - i - 1)) & 1
            if u._child[c] == None: return False
            u = u._child[c]
        else:  # found it
            return True

    def __str__(self):
        arr = []
        u = self._dummy._child[next_]
        while u != self._dummy:
            arr.append(str(u._x))
            u = u._child[next_]
        return ','.join(arr)

    def size(self):
        return self._n

if __name__ == '__main__':
    arr = [random.randint(1, 100) for i in xrange(1, 20)]
    print 'input: {}'.format(arr)

    btrie = BinaryTrie()
    map(btrie.add, arr)
    assert btrie.size() == len(set(arr))
    print 'btrie list: {}'.format(btrie)

    arr.sort()
    for x in arr:
        print 'find {}: {}'.format(x, btrie.find(x))

    find_arr = [random.randint(1, 100) for i in xrange(1, 20)]
    print 'find list: {}'.format(find_arr)
    for x in find_arr:
        ret = btrie.find(x)
        print 'find {}: {}'.format(x, ret)
        assert ret == (x in arr)

    for x in arr:
        print 'remove {}: {}'.format(x, btrie.remove(x))
    assert btrie.size() == 0

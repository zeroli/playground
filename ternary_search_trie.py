import random

"""implementation of ternary search trie data structure
to address issue of excessive space in regular trie structure
"""

R = 3
LEFT = 0
MIDDLE = 1
RIGHT = 2

class TSTNode(object):
    def __init__(self):
        self.val = None
        self.key = None
        """links contains
        1) link to substrings whose first char is smaller than current 'key'
        2) link to substrings that continue with current 'key'
        3) link to substrings whose first char is greater than current 'key'
        """
        self.links = [None] * R

class TSTrie(object):
    def __init__(self):
        self.root = TSTNode()

    def put(self, key, val):
        """key is specifically a string, val is assigned specific value for that string key"""
        def _put(node, key, val, d):
            if node == None:
                prev = None
                for k in xrange(d, len(key)):
                    prev = nn = TSTNode()
                    nn.key = key[k]
                    if not node: node = nn
                    if prev:
                        prev.links[MIDDLE] = nn
                    if k == len(key) - 1:
                        nn.val = val
                    prev = nn
                return node

            if d == len(key):
                node.val = val # update the value
            else:
                if key[d] == node.key: # put it in middle link, and increase d
                    node.links[MIDDLE] = _put(node.links[MIDDLE], key, val, d+1)
                elif key[d] < node.key: # put it in left link
                    node.links[LEFT] = _put(node.links[LEFT], key, val, d)
                else:
                    node.links[RIGHT] = _put(node.links[RIGHT], key, val, d)
            return node

        print '>>put key={}, val={}'.format(key, val)
        _put(self.root, key, val, 0)
        print '>>tstrie: {}'.format(self)

    def get(self, key):
        def _get(node, key, d):
            if node == None: return None
            if d == len(key): return node
            if key[d] == node.key: # follow middle link, we will increase d
                return _get(node.links[MIDDLE], key, d+1)
            elif key[d] < node.key: # follow left link
                return _get(node.links[LEFT], key, d)
            else: # follow right link
                return _get(node.links[RIGHT], key, d)
        print '>>get key={} => '.format(key),
        node = _get(self.root, key, 0)
        val = node.val if node else None
        print val
        return val

    def size(self):
        """lazy implementation of size"""
        def _size(node):
            if node == None: return 0
            size = 1 if node.val != None else 0
            for n in node.links:
                size += _size(n)
            return size
        return _size(self.root)

    def _collect(self, node, coll, keys):
        if node.val != None:
            keys.append(''.join(coll))
        left = node.links[LEFT]
        if left:
            self._collect(left, coll, keys)

        middle = node.links[MIDDLE]
        if middle:
            coll.append(node.key)
            self._collect(middle, coll, keys)
            coll.pop()

        right = node.links[RIGHT]
        if right:
            self._collect(right, coll, keys)

    def keys(self):
        keys = []
        coll = []
        self._collect(self.root, coll, keys)
        return keys

    def __str__(self):
        s = ''
        node = self.root
        if node == None or not any(node.links): return '<EMPTY>'
        s = ' '.join(self.keys())
        return s

if __name__ == '__main__':
    data = [
        'she',
        'sells',
        'sea',
        'shells',
        'by',
        'the',
        'sea',
        'shore',
    ]
    tstrie = TSTrie()
    for i in xrange(len(data)):
        tstrie.put(data[i], i)
    print '>>tstrie: size={}, {}'.format(tstrie.size(), tstrie)

    print '>>test get'
    for i in xrange(len(data)):
        tstrie.get(data[i])

import random
import copy

"""
some problems about linked list
"""

class Node(object):
    def __init__(self, val=None, next=None):
        self.val = val
        self.next = next

class SingleLinkedList(object):
    def __init__(self, data=None):
        self.head = None
        if data:
            self.build(data)

    def build(self, data):
        for x in reversed(data):
            p = Node()
            p.val = x
            p.next = self.head
            self.head = p

    def reverse(self, iterative=False):
        """in-place reverse single linked list
        """
        if iterative:
            pp, cp, np = None, None, None
            cp = self.head
            while cp:
                np = cp.next
                cp.next = pp
                pp = cp
                cp = np
            self.head = pp
        else:
            def _reverse(node):
                if node.next:
                    head = _reverse(node.next)
                    node.next.next = node
                    node.next = None
                    return head
                return node
            if self.head:
                self.head = _reverse(self.head)

    def toList(self):
        s = []
        p = self.head
        while p:
            s.append(p.val)
            p = p.next
        return s

    def hasCyclic(self):
        slow, fast = self.head, self.head
        while fast:
            # fast pointer, advance 2 steps one time
            fast = fast.next
            if fast:
                fast = fast.next
            # slow pointer, advance 1 step one time
            if slow:
                slow = slow.next
            if fast == slow:
                #the found node doesn't have to be the connection node
                return True
        return False

    def __str__(self):
        s = []
        p = self.head
        while p:
            s.append(str(p.val))
            p = p.next
        return ','.join(s)

if __name__ == '__main__':
    lst = [random.randint(0, 19) for _ in xrange(20)]
    print '>>random list:\n{}'.format(lst)

    sl = SingleLinkedList(lst)
    print '>>single linked list: {}'.format(sl)
    sl.reverse()
    print '>>reversed linked list: {}'.format(sl)
    sl.reverse(iterative=True)
    print '>>reversed linked list: {}'.format(sl)
    assert sl.toList() == lst

    p0 = Node(100)
    p = Node(-1,
            Node(-2,
                Node(-3,
                    Node(-4,
                        Node(-5, p0))))
        )
    sl = SingleLinkedList()
    sl.head = Node(1,
        Node(2,
            Node(3,
                Node(4,
                    Node(5, p))))
    )

    print '>>built-up single linked list: {}'.format(sl)
    print '>>has cyclic' if sl.hasCyclic() else '>>has no cyclic'
    #make one circular in this single linked list
    p0.next = p
    print '>>has cyclic' if sl.hasCyclic() else '>>has no cyclic'
import random

"""
sort one stack using 2 stacks
"""

class Stack(object):
    def __init__(self, data = None):
        self._data = data if data else []

    def push(self, d):
        self._data.append(d)

    def pop(self):
        return self._data.pop()

    def top(self):
        return self._data[-1]

    def empty(self):
        return len(self._data) == 0

    def __str__(self):
        return str(self._data)

    def sort(self):
        aux = Stack()

        while not self.empty():
            d = self.pop()

            n = 0
            # insertion sort variation
            # invariant fact: in aux, always store reversed sorted elements
            while not aux.empty() and aux.top() < d:
                self.push(aux.pop())
                n += 1
            aux.push(d)
            while n:
                aux.push(self.pop())
                n -= 1
        while not aux.empty():
            self.push(aux.pop())

if __name__ == '__main__':
    data = [random.randrange(-100, 100) for i in xrange(1, 20)]
    s = Stack(data)
    print 'stack: {}'.format(s)
    s.sort()
    print 'after sorted stack: {}'.format(s)

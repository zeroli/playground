import random

"""implementation of largest contenuous histogram area problem
"""

"""solution#1:
naive solution, loop all possible contenous histograms, and compute their area, and then return maximum one
"""
def find_largest_area1(lst):
    maxarea = 0
    maxrange = (-1, -1)
    for i in xrange(len(lst)):
        ileft = i
        while ileft >= 0 and lst[ileft] >= lst[i]:
            ileft -= 1
        iright = i
        while iright < len(lst) and lst[iright] >= lst[i]:
            iright += 1
        area = ((iright - i - 1) + (i - ileft - 1)  + 1) * lst[i]
        if maxarea < area:
            maxarea = area
            maxrange = (ileft+1, iright-1)
    print '>>1) largest area: {}, range: {}'.format(maxarea, maxrange)

"""solution#2:
use divide-and-concur algo
1) find minimum bar from input
2) divide 2 parts of bars, left part is bars that before the found minimum bar,
    right part is bars that after the found minimum bar
3) separately compute these 2 parts using divide-and-concur algo, and then finally we could get
the maximum area from the following 3 candidates:
<1> maximum area from left part
<2> maximum area from right part
<3> number of bars total multiply with this current minimum bar
The runtime complixity is optimized to O(nlg(n)), if we could find the minimum bar using O(n) time
"""

"""solution#3:
runtime complexity is O(n)
"""

def find_largest_area3(lst):
    s = []
    maxarea = 0
    maxrange = (-1, -1)
    i = 0
    while i < len(lst):
        if not s or lst[s[-1]] < lst[i]:
            s.append(i)
            i += 1
        else:
            top_on_stack = s.pop()
            """calculate the area with iprev bar as smallest bar
            left bars in stack are smaller than this iprev (may have some empty slots),
            right bars in stack are bigger, so here, we use s[-1]
            """
            area = lst[top_on_stack] * ((i - s[-1] - 1) if s else i)
            if maxarea < area:
                maxarea = area
                maxrange = (s[-1]+1, i-1) if s else (0, i-1)
    while s:
        top_on_stack = s.pop()
        area = lst[top_on_stack] * ((i - s[-1] - 1) if s else i)
        if maxarea < area:
            maxarea = area
            maxrange = (s[-1]+1, i-1) if s else (0, i-1)

    print '>>3) largest area: {}, range: {}'.format(maxarea, maxrange)

if __name__ == '__main__':
    lst = [random.randint(1, 100) for _ in xrange(20)]
    #lst = [6, 2, 5, 4, 5, 1, 6]
    print '>>random list:\n{}'.format(lst)
    find_largest_area1(lst)
    find_largest_area3(lst)

import random

"""implementions for maximal rectangle problem
"""

def _area(ll, ur):
    if ll[0] > ur[0] or ll[1] > ur[1]:
        return 0
    else:
        return (ur[0] - ll[0] + 1) * (ur[1] - ll[1] + 1)

def _all(data, ll, ur):
    for ix in xrange(ll[0], ur[0]+1):
        for iy in xrange(ll[1], ur[1]+1):
            if data[N * iy + ix] == 0: return False
    return True

"""solution 0:
brute-force solution
runtime complexity: O(M^3 * N^3)
"""
def max_rect0(data, M, N):
    """input 2d array using one list, with M rows, N columns
    """
    maxarea = 0
    ll = (0, 0)
    ur = (-1, -1)
    for ll_ix in xrange(N):
        for ll_iy in xrange(M):
            for ur_ix in xrange(N):
                for ur_iy in xrange(M):
                    ll_t = (ll_ix, ll_iy)
                    ur_t = (ur_ix, ur_iy)
                    area = _area(ll_t, ur_t)
                    if area > maxarea and _all(data, ll_t, ur_t):
                        maxarea = area
                        ll = ll_t
                        ur = ur_t
    print '>>0)found maximal rect: {}, at bbox: {}, {}'.format(maxarea, ll, ur)

"""solution 1:
improved brute-force solution
runtime complexity: O(M^3 * N^3)
"""
def max_rect1(data, M, N):
    """input 2d array using one list, with M rows, N columns
    """
    maxarea = 0
    ll = (0, 0)
    ur = (-1, -1)
    for ll_ix in xrange(0, N):
        for ll_iy in xrange(0, M):
            for ur_ix in xrange(ll_ix, N):
                for ur_iy in xrange(ll_iy, M):
                    ll_t = (ll_ix, ll_iy)
                    ur_t = (ur_ix, ur_iy)
                    area = _area(ll_t, ur_t)
                    if area > maxarea and _all(data, ll_t, ur_t):
                        maxarea = area
                        ll = ll_t
                        ur = ur_t
    print '>>1)found maximal rect: {}, at bbox: {}, {}'.format(maxarea, ll, ur)

"""solution 2:
improved brute-force solution by using grow_ones
runtime complexity: O(M^2 * N^2)
"""
def max_rect2(data, M, N):
    """input 2d array using one list, with M rows, N columns
    """
    def _grow_ones(ll):
        """with this 'll' as lower-left corner, to grow ones, to form one max rect
        """
        ur = (ll[0] - 1, ll[1] - 1)
        maxarea = _area(ll, ur)
        xmax = N
        for iy in xrange(ll[1], M):
            if data[N * iy + ll[0]] == 0:
                break
            #we'd like to improve this, see below max_rect3
            for ix in xrange(ll[0], xmax):
                if data[N * iy + ix] == 0:
                    xmax = ix
                    ix -= 1
                    break

            ur_t = (ix, iy)
            area = _area(ll, ur_t)
            if area > maxarea:
                area = maxarea
                ur = ur_t
        return ur

    maxarea = 0
    ll = (0, 0)
    ur = (-1, -1)
    for ll_ix in xrange(0, N):
        for ll_iy in xrange(0, M):
            ll_t = (ll_ix, ll_iy)
            ur_t = _grow_ones(ll_t)
            area = _area(ll_t, ur_t)
            if area > maxarea:
                maxarea = area
                ll = ll_t
                ur = ur_t
    print '>>2)found maximal rect: {}, at bbox: {}, {}'.format(maxarea, ll, ur)

"""solution 3:
improved brute-force solution by using grow_ones and cache
runtime complexity: O(M^2 * N)
"""
def max_rect3(data, M, N):
    """input 2d array using one list, with M rows, N columns
    """
    """cache for all rows, which handling each column"""
    cache = [0] * M
    def _update_cache(ix):
        for iy in xrange(M):
            if data[iy * N + ix] != 0:
                cache[iy] += 1
            else:
                cache[iy] = 0

    def _grow_ones(ll):
        """with this 'll' as lower-left corner, to grow ones, to form one max rect
        """
        ur = (ll[0] - 1, ll[1] - 1)
        maxarea = _area(ll, ur)
        xmax = N
        for iy in xrange(ll[1], M):
            if data[N * iy + ll[0]] == 0:
                break
            #we use cache directly
            #for each iy, we already know continuous '1' at this row
            xmax = min(cache[iy] + ll[0], xmax)
            ix = xmax - 1

            ur_t = (ix, iy)
            area = _area(ll, ur_t)
            if area > maxarea:
                area = maxarea
                ur = ur_t
        return ur

    maxarea = 0
    ll = (0, 0)
    ur = (-1, -1)
    #in reversed order, so that we could build up cache
    for ll_ix in xrange(N-1, -1, -1): # handle column one by one
        _update_cache(ll_ix)
        for ll_iy in xrange(M-1, -1, -1):
            ll_t = (ll_ix, ll_iy)
            ur_t = _grow_ones(ll_t)
            area = _area(ll_t, ur_t)
            if area > maxarea:
                maxarea = area
                ll = ll_t
                ur = ur_t
    print '>>3)found maximal rect: {}, at bbox: {}, {}'.format(maxarea, ll, ur)

"""solution 4:
improved brute-force solution by using grow_ones and cache
runtime complexity: O(M^2 * N)
"""
def max_rect4(data, M, N):
    """input 2d array using one list, with M rows, N columns
    """
    print '>>max_rect4 using 1d largest histogram area algo'
    """cache for all rows, which handling each column"""
    cache = [0] * M
    def _update_cache(ix):
        for iy in xrange(M):
            if data[iy * N + ix] != 0:
                cache[iy] += 1
            else:
                cache[iy] = 0

    import largest_hist_area

    maxarea = 0
    ll = (0, 0)
    ur = (-1, -1)
    #in reversed order, so that we could build up cache
    for ll_ix in xrange(N-1, -1, -1): # handle column one by one
        _update_cache(ll_ix)

        (area, yrange) = largest_hist_area.find_largest_area3(cache)
        ll_t = (ll_ix, yrange[0])
        ur_t = (area/(yrange[1]-yrange[0]+1)+ll_ix-1, yrange[1])
        if area > maxarea:
            maxarea = area
            ll = ll_t
            ur = ur_t
    print '>>4)found maximal rect: {}, at bbox: {}, {}'.format(maxarea, ll, ur)

if __name__ == '__main__':
    M = 16
    N = 12
    data = [ # row 16, column 12
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, # row1
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, # row2
        1,  1, 0, 0, 0, 0, 0, 1,  1, 0, 0, 0,
        0, 1,  1, 1, 0, 0, 0, 0,  1, 1, 0, 0,
        0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0,
        0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0,
        0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 1, 1 ,1, 1, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1,
        0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1,
        0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1,
        0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
        0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, # row 16
    ]
    data = [random.choice([0, 1]) for _ in xrange(M*N)]
    max_rect0(data, M, N)
    max_rect1(data, M, N)
    max_rect2(data, M, N)
    max_rect3(data, M, N)
    max_rect4(data, M, N)

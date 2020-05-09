import random
import copy

"""
Given an unsorted array, you need to find the second largest element in the array in o(n) time complexity.
"""

# wrong algorithm
def find_second_largest_number(arr):
    highest = -1
    secondHighest = -1

    for num in arr:
        if num > highest:
            secondHighest = highest
            highest = num
        elif num > secondHighest and num != highest:
            secondHighest = num

    return secondHighest


if __name__ == '__main__':
    #arr = [7,5,6,1,4,2]
    arr = {random.randint(1, 100) for i in xrange(1, 20)}
    arr = list(arr)
    print 'second largest number in array {} is {}'.format(find_second_largest_number(arr), arr)
    print 'baseline: {}'.format(sorted(arr)[-2])

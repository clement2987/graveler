import random
import time
from itertools import repeat

start_time = time.time()

items = [1,2,3,4]
numbers = [0,0,0,0]
rolls = 0
maxOnes = 0

while numbers[0] < 177 and rolls < 1_000_000:
    numbers = [0,0,0,0]
    for i in repeat(None, 231):
        roll = random.choice(items)
        numbers[roll-1] = numbers[roll-1] + 1
    rolls = rolls + 1
    if numbers[0] > maxOnes:
        maxOnes = numbers[0]

end_time = time.time()
elapsed_time = end_time - start_time

print("Highest Ones Roll:",maxOnes)
print("Number of Roll Sessions: ",rolls)
print("time taken:", elapsed_time)

"""
TIME TAKEN FOR 1,000,000 62.957 seconds
"""
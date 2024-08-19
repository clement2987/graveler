from random import random
import time



#total number of attempts the (try to get one billion down to a reasonable time)
attempts = 1_000_000
rolls = attempts
maxOnes = 0
start_time = time.time()
# Using a for loop because it is faster than a while loop
for i in range(attempts):
    # takes 0.3 seconds per million attempts
    if maxOnes >= 177:
        rolls = i
        break
    score = 0
    for j in range(231):
       # takes 7 seconds per 1,000,000 attempts
        if random()<=0.25:
            score += 1
        
    #takes about 0.1 seconds per million attempts
    maxOnes += (score * (score > maxOnes)) - (maxOnes * (score > maxOnes))
    

end_time = time.time()
elapsed_time = end_time - start_time

print("Highest Ones Roll:",maxOnes)
print("Number of Roll Sessions:",rolls)
print("time taken:", elapsed_time)

"""
TIME TAKEN FOR 1,000,000 10.267 seconds
"""

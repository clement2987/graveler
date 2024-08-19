import random
import time

start_time = time.time()

#total number of attempts the (try to get one billion down to a reasonable time)
attempts = 1_000_000
rolls = attempts
maxOnes = 0

# Using a for loop because it is faster than a while loop
for i in range(attempts):
    # takes 0.3 seconds per million attempts
    if maxOnes >= 177:
        rolls = i
        break
    score = 0
    for __ in range(231):
        #takes 10 seconds per million attempts
        # number = random.random()
        #check if the number is below 25%. true is 1 and false is 0. this is quicker than an if statement
        # counting the score takes about 10 seconds per million attempts
        score += (random.random()<=0.25)
    #takes about 0.1 seconds per million attempts
    maxOnes += (score * (score > maxOnes)) - (maxOnes * (score > maxOnes))
    

end_time = time.time()
elapsed_time = end_time - start_time

print("Highest Ones Roll:",maxOnes)
print("Number of Roll Sessions:",rolls)
print("time taken:", elapsed_time)

"""
TIME TAKEN FOR 1,000,000 16.467 seconds
"""
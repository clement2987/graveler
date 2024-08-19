# Graveler
My humble attempt to optimize Austin's code

# Original File
## aistin_graveler.py
besides adding logic to time the execution I kept this the same as a benchmark

on my machein it look roughly a minute to run 1,000,000 iterations


# The First Attempt
## me_graveler.py
for all attempts I wanted to stay as close to the original as I could, manually checking all 231 rolls for each attempt
first  majer change I made was to replace the while loop with a for loop as for loops in python tend to be 4x faster than while loops
I tested different functions in random and found random.random() was the fastest
I added the boolian value (1 for true, 0 for false) to score when the value returned by random was under 0.25 which should be 1/4 times

the best time I could get from python was 16 seconds for 1,000,000 attempts


# The Second Attempt:
## me_graveler.c
Like I am sure many people will have done I turned to C because it is famous for its speed (if I was more comfortable with ASM I'm sure that would be an even better choice)
The first attempt in C started off very similar to the oridinal python. I noticed one of my biggest bottlenecks was generating a random number, taking most of the time
I made the change to generating a very large number and just going through 2 bits at a time, I was finally inder a second for a million iterations
I further cut my time by a 3rd by adding a check to see if it was possible to set a new record for the best score in the current attempt, and if not then just move on early

for 1,000,000 attempts it took 0.702 seconds
for 1,000,000,000 attempts we are at 656 seconds or 11 minutes

# The Third Attempt
## me2__graveler.c
This is it, we are going for the fastest time and using all the recorses of my machein and turning to multi-threading
I took the logic from second attemps and put in in a function called work, spent several hours reading and learning how to thread in c (time well spent getting the basics)
added some extra safety checks then let loose with 10 cpu corees weoking together to complete the task
unfortunatly this code will only work on a windows machein but I am happy with the times

for 1,000,000 attempts it took 0.134 seconds
for 1,000,000,000 attempts we are at 120 seconds or 2 minutes

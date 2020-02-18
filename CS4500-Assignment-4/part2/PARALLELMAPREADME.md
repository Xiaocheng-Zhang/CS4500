# Readme
pmap:
1. generate num of rows' threads.
2. create an array of Rowers.
3. parallel run each thread with helper method(passed in a Compressed class whcih package Rower and Row).
4. thread.join() to end threads.

- no threads mutex because rows are different.
# 365-problems
## About
This is a repository comprising of multiple programming solutions to problems I found interesting and wanted to approach them in the most creative fashion I can.
They will be written in C, compiled with GCC. The use of extensions will be used to their fullest extent. 

The goal of this repository is for anyone coming to check it out will learn something new.

## Solutions
### Solution 1 - AZPath.c
Given a 10x10 grid, starting from x and y, 
randomly move to adjacent cells. If every cell adjacent to the current cell 
are all occupied, exit. If not, leave 'A' in the cell that was left and move
to an unoccupied cell repeat until 'Z'. An unoccupied cell will be signified by
a '.', an occupied cell will have an alphabet. 

### Solution 2 - SeqMap.c
For a sequence of single digits, a mapping exists for 1->'a', 2->'b', ...,
26->'z'. Map such a sequence into its string counterparts. In a case that two
possible interpretations exist, for example, 12 can both be 'ab' and 'l',
present both as an answer. If, however, it cannot be represented, such as 39, 42,
86, that interpreted mapping shall not exist and be given as an answer.

### Solution 3 - CompSort.c
Given a list of numbers, arrange them such that the greatest possible combination can be achieved.

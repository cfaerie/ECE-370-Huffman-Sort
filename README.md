# ECE 370 Huffman Sort
Original code was created by me for ECE 370 course. I plan to make adjustments/improvements to the original code.
Assignment details are shown below:
-----------------------
This assignment is a structured program to implement Huffman algorithm using binary tree.
 
In your program, assume that the sample space consists of no more than 52 samples. Each sample is an English letter and its probability is represented by the frequency that letter appears, that is an integer. You need to build up a binary Huffman tree using Huffman algorithm, and to assign a codeword for each letter. Your program should be capable translating a string of binary digits {1,0} into a sequence of letters from the sample space. There are two input files. The first file a3-1.txt consists of:
an integer at the first line indicating the number of samples within sample space.
starting from 2nd line, each line contains an English letter and its frequency (i.e. its associated probability).
 
It is a general algorithm so your program can handle all possible cases as long as the sample space consists of English letters (no matter how many are there in a3-1.txt).
The second input file a3-2.txt consists of a string of binary digits {1,0} (no more than one line).
 
Note:
When a codeword is assigned to a letter, always assign a 0 to the leftchild (that is the node with the least frequency in the queue), and a 1 to the rightchild, if you choose to use a binary tree structure. If two (left and right) have the same number, assign the first read-in 0, and the second read-in 1.
 
Your program should put codewords associated with a letter on the screen alphabetically.
 
Your program should output a sequence of letters on the screen after the program translates the string of {1,0} in a3-2.txt into a sequence of letters.
 
This is a single program. You may have many functions.
Here is an example of input file a3-1.txt:  (note that there is NO empty line in between lines, see sample input file)
9
a 15
b 7
c 8
d 9
e 20
f 6
g 3
h 12
k 4
 
An example of input string in a3-2.txt
01000111000100010010100100010000……

/**
Shiva khatri
Programming Assignment 6
*/

/**
In this C program with embedded assembly code, the objective is
 to identify the element that occurs most frequently in a predefined array
  and determine the count of its occurrences. The array, denoted as "array," 
  is manually populated with 30 elements. This program leverages inline assembly 
  within the Visual Studio C environment to execute low-level assembly instructions
   alongside high-level C code. The core algorithm involves employing two nested loops. 
   The outer loop iterates over each element in the array, while the inner loop tallies
   the occurrences of the current number. After completing the inner loop for each number,
    the program compares the count with the maximum count observed so far. If the count surpasses
     the existing maximum count, the program updates the maximum count and its corresponding number.
      The final output, generated through printf, showcases the number that occurs most frequently and
       the count of its occurrences. For instance, when applied to Array 2, it correctly identifies that
        the number 3 repeats 17 times, leading to the output: "3 occurs 17 times."
*/

#include <stdio.h> 

int main() {
    int n = 30;  // Number of elements in the array
    int array[] = { 25,26,27,28,29,30,25,26,27,29,30,25,28,30,27,30,26,27,28,25,24,26,27,26,27,26,28,26,30,25};
    int number, count, maxNumber, maxCount; // Declare variables to store the number, count, maxNumber, and maxCount

    __asm { // Begining of assembly code
        
        mov maxCount, 0 // Initialize maxCount to 0

        // Outer loop (i)
        mov ecx, 0  // Initialize i to 0
        outer_loop: // top of the outer loop
            cmp ecx, n  // Compare i with n
            jge done  // If i >= n, leave the loop

            // Initialize currentNumber and count
            mov eax, array[ecx * 4] // eax = array[i]
            mov number, eax // number = eax
            mov count, 0 // count = 0

            // Inner loop (j)
            mov ebx, 0  // Initialize j to 0
            inner_loop: // top of the inner loop
                cmp ebx, n  // Compare j with n
                jge inner_done  // If j >= n, leave the inner loop

                // Preserve the original value of eax
                mov edx, eax // edx = eax

                // Check if current element matches inner loop element
                mov eax, edx // eax = edx
                cmp eax, array[ebx*4] // Compare eax with array[j]
                jne inner_continue  // If not a match, continue to the next iteration

                // Increment count if a match
                inc count // count = count + 1 if a match

                inner_continue : // bottom of the inner loop
                inc ebx  // Increment j
                jmp inner_loop  // Repeat the inner loop

                inner_done : // bottom of the inner loop

        // Check if count > maxCount
             mov eax, count // eax = count
            cmp eax, maxCount // Compare eax with maxCount
            jle outer_continue  // If not, continue to the next iteration

            // Update maxCount and maxNumber using registers
            mov eax, count // eax = count
            mov maxCount, eax // maxCount = eax

            mov eax, number // eax = number
            mov maxNumber, eax // maxNumber = eax

            outer_continue : // bottom of the outer loop
             inc ecx  // Increment i
             
            jmp outer_loop  // Repeat the outer loop

            done : nop // End of the program
    } // End of assembly code

    // Output the result
    printf("%d occurs %d times.\n", maxNumber, maxCount); // Print the number that occurs most frequently and the count of its occurrences

    return 0; // End of the program
}

/**
Output

50 occurs 4 times.



3 occurs 10 times.


26 occurs 7 times.





**/

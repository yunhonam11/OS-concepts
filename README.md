# OS-concepts
Important OS concepts

These files work separately. They illustrate OS concepts I learned from class in the simplest ways possible, so that anyone with
rudimentary understanding of those concepts can follow them.

multipipe.c : illustrates how to use multiprogramming using multiple processes with multiple pipes connected to child processes. A child process does not create more child processes and all operations are done concurrently with children (no grandchildren) of the main/parent process.
              
wc_thread.c - illustrates how to use the work crew model of multithreading.

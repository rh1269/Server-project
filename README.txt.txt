INCLUDED FILES IN SUBMISSION:

1. README.txt
2. DesignDoc.doc
3. server.c
4.  logFile.txt

-To execute the server.c file properly the following command is needed

./[executable][the current machines ip][the desired port][the size of the backlog queue]
 ./a.out 147.26.100.201 54324 15

this format was chosen initially to mirror the client.c command input, hopefully this will suffice.


-The program compiles and executes successfully, there are no known errors and no unexpected behavior has been observed during runtime of server.c

-This program has been tested on both my home windows computer using cygwin and on txstate machine zeus.cs.txstate.edu.  

-The file size transferred and the file size recieved by the client has been identical during testing on multiple machines,  with reasonable transfer rates and times.

-The output file is logFile.txt, information is stored here during runtime as described in the design, the file sent was created prior to submission.  

!please direct any questions to me at rh1269@txstate.edu
 *  1. In the program (L93), modify [dbname], [username], [password] to
 *     yours ([dbname] is the same as your [username] by default).
 *     Open cmd, go to the directory where this program is.  
 *  2. Preprocessor - $ ecpg -c sdap.pgc
 *  3. Compile      - $ gcc -c -I "D:\Program Files\PostgreSQL\9.5\include" sdap.c
 *  4. Link         - $ gcc -L "D:\Program Files\PostgreSQL\9.5\lib" -lecpg sdap.o -o sdap.exe
 *  5. Execute      - $ sdap.exe

 *  "D:\Program Files\PostgreSQL\9.5\include" and "D:\Program Files\PostgreSQL\9.5\lib" are two     directory where postgreSQL store its "include" folder and "lib" folder. change them to your 
    own directory.
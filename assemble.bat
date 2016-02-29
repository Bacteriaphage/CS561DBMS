ecpg -c sdap.pgc
gcc -c -I "D:\Program Files\PostgreSQL\9.5\include" sdap.c
gcc -L "D:\Program Files\PostgreSQL\9.5\lib" -lecpg sdap.o -o sdap.exe
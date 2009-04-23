gcc -c lexer.c
gcc -c driver.c
gcc -o out lexer.c driver.c
./out input2

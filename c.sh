gcc -DSMTP_OPENSSL smtp.c -c -o smtp.o 
gcc -DSMTP_OPENSSL main.c -c -o main.o
gcc smtp.o main.o  -o wsmtp -lssl -lcrypto
 

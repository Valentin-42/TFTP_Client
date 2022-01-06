puttftp : puttftp.o
	gcc -o puttftp puttftp.o 

puttftp.o : puttftp.c puttftp.h
	gcc -o puttftp.o -c puttftp.c -W -Wall


gettftp : gettftp.o
	gcc -o gettftp gettftp.o 

gettftp.o: gettftp.c gettftp.h
	gcc -o gettftp.o -c gettftp.c -W -Wall

clean:
	rm -rf *.o

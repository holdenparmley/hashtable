ht: main.o hashtable.o
        g++ -o ht main.o hashtable.o

main.o: main.cpp
        g++ -c main.cpp

hashtable.o: hashtable.cpp hashtable.h
        g++ -c hashtable.cpp

clean:
        rm -f ht *.o *-

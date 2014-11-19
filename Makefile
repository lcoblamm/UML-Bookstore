Lab8: main.o Good.o Retailer.o Customer.o Supplier.o
	g++ -g -std=c++11 main.o Good.o Retailer.o Customer.o Supplier.o -o Lab8

main.o: main.cpp Good.h Retailer.h Customer.h Supplier.h Enums.h
	g++ -g -std=c++11 main.cpp -c

Supplier.o: Supplier.h Supplier.cpp Enums.h
	g++ -g -std=c++11 Supplier.cpp -c

Retailer.o: Retailer.h Retailer.cpp Good.h Supplier.h Enums.h
	g++ -g -std=c++11 Retailer.cpp -c

Customer.o: Customer.h Customer.cpp Retailer.h Enums.h
	g++ -g -std=c++11 Customer.cpp -c

Good.o: Good.h Good.cpp 
	g++ -g -std=c++11 Good.cpp -c

clean:
	rm *.o *~ Lab8

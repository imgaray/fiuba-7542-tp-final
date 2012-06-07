for i in *.cpp; do
	if "$i" != "main.cpp"; then
		g++ -Wall -Werror -g -O3 -std=c++98 -lpthread -pthread "$i" -c
	fi
done	
g++ -Wall -Werror -g -O3 -std=c++98 -lpthread -pthread *.o main.cpp -o main


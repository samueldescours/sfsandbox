CXX=g++
CXXFLAGS=-fsanitize=address -O3 -Werror -Wall -Wextra -Iinclude

SRC=$(wildcard *.cpp)
OBJ=$(addprefix obj/, $(SRC:.cpp=.o))

INCLUDE=-lsfml-graphics -lsfml-window -lsfml-system 

all: obj/ $(OBJ)
	$(CXX) $(OBJ) -o sfsandbox $(CXXFLAGS) $(INCLUDE)

obj/:
	mkdir -p obj

obj/%.o: %.cpp
	g++ -c $^ -o $@ $(CXXFLAGS)

clean:
	rm -rf obj

fclean: clean
	rm -f app

re: fclean all

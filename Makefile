BOOST = /usr/local/Cellar/boost/1.72.0_1/lib

all:
	g++ -std=c++11 src/*.cpp -o main -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network -lsfml-system
test:
	g++ -std=c++11 tests/test.cpp -o test -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network -lsfml-system -L$(BOOST) -lboost_unit_test_framework -lboost_test_exec_monitor

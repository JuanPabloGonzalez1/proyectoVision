adalib_path=../adalib

all: ada

ada: ejemplo1.o adaboost.o
	g++ ejemplo1.o adaboost.o -o ada

ejemplo1.o: ejemplo1.cpp
	g++ -c ejemplo1.cpp

adaboost.o: $(adalib_path)/adaboost.cpp
	g++ -c $(adalib_path)/adaboost.cpp

clean:
	rm -rf *o ada

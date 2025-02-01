all:
	python3 src/genTestAll.py
	g++ -DTEST -I./src src/*.cpp src/test/*.cpp -o ./link-pd-code.out

clean:
	rm -rf *.out

.PHONY: all clean
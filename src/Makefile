all:
	python3 genTestAll.py
	g++ -DTEST *.cpp -o ./link-pd-code.out

clean:
	rm -rf *.out

.PHONY: all clean
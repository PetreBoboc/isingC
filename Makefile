co:
	rm -rf ising
	gcc -o ising main.c neighbors.c
clean:
	rm -rf latice1.txt latice2.txt x.txt y.txt
all: static shared

static:
	gcc -c bstrutils.c -o bstrutils.o
	ar rcs libbstrutils.a bstrutils.o
	gcc main.c libbstrutils.a -o main_static

shared:
	gcc -fPIC -c bstrutils.c -o bstrutils_pic.o
	gcc -shared -o libbstrutils.so bstrutils_pic.o
	gcc main.c -L. -lbstrutils -o main_shared

run_static:
	./main_static

run_shared:
	LD_LIBRARY_PATH=. ./main_shared

clean:
	rm -f *.o *.a *.so main_static main_shared

.PHONY: all static shared run run_shared clean
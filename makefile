all: gadget.c
	mkdir bin -p
	gcc gadget.c -m32 -o bin/g
clean:
	rm bin -rf

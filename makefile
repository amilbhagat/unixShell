all:
	gcc mkdir.c -o mkdir
	gcc rm.c -o rm
	gcc ls.c -o ls
	gcc cat.c -o cat
	gcc date.c -o date 
	gcc main.c
	./a.out
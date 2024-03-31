main: main.c mat_sparsa_lista.o ran_mat
	./ran_mat 10 10
	g++ main.c -o main mat_sparsa_lista.o -g
	rm ran_mat

mat_sparsa_lista.o: mat_sparsa_lista.c mat_sparsa_lista.h
	g++ mat_sparsa_lista.c -c -g

ran_mat: ran_mat.c
	g++ ran_mat.c -o ran_mat

main_arr_arr: main_arr_arr.c mat_sparsa_arr.o ran_mat
	./ran_mat 10 10
	g++ main_arr_arr -o main_arr_arr mat_sparsa_arr.o -g
	rm ran_mat

mat_sparsa_arr.o: mat_sparsa_arr.c mat_sparsa_arr.h
	g++ mat_sparsa_arr.c -c -g

.PHONY: clean
clean:
	rm *.o mat.dat main

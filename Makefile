SRC=main.C image.C sink.C source.C PNMreader.C PNMwriter.C filters.C filter.C logging.C
OBJ=$(SRC:.C=.o)

prog: $(OBJ)
	g++ $(OBJ) -o proj

.C.o: $<
	g++  -g -I. -c $<

clean:
	rm *.o proj

run:
	./proj 3D_input.pnm my_output.pnm
	pnmtopng <my_output.pnm> my_output.png

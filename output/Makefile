# Starts attempting to create main.o and app.o, sequentially until all of the .o files are existent
output: main.o app.o filemanager.o
	g++ main.o app.o filemanager.o -o output -lurlmon

# Creates main.o in output directory
main.o: ../main.cpp
	g++ -c ../main.cpp -lurlmon

# Creates app.o in output directory
app.o: ../app.cpp ../app.h
	g++ -c ../app.cpp -lurlmon

filemanager.o: ../modules/filemanager.cpp ../modules/filemanager.h
	g++ -c ../modules/filemanager.cpp -lurlmon

# Cleans all output files in directory
clean:
	rm *.o output
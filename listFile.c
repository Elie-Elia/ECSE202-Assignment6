/*
 ============================================================================
 Name        : listFile.c
 Author      : F. Ferrie
 Version     :
 Copyright   : Your copyright notice
 Description : A "C" version of the fileReader program originally
             : written Java for Assignment 2.  This one uses the command
             : line interface to obtain the file name.  Like its predecessor,
             : this program reads a text file line by line, displaying the
             : output on the standard output.  Use this program as a basis
             : for Assignment 6.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define MAXBUF 100

int main(int argc, char *argv[]) {
// Internal declarations
	FILE * FileD;			// File descriptor (an object)!
	char *line;				// Pointer to buffer used by getline function
	int bufsize = MAXBUF;	// Size of buffer to allocate
	int linelen;				// Length of string returned (getline)

// Argument check
	if (argc != 2) {
		printf("Usage: fileReader [text file name]\n");
		return -1;
	}

// Attempt to open the user-specified file.  If no file with
// the supplied name is found, exit the program with an error
// message.

	if ((FileD=fopen(argv[1],"r"))==NULL) {
		printf("Can't read from file %s\n",argv[1]);
		return -2;
	}

// Allocate a buffer for the getline function to return data to.

	line=(char *)malloc(bufsize+1);
	if (line==NULL) {
		printf("Unable to allocate a buffer for reading.\n");
		return -3;
	}

// If the file exists and a buffer was successfully allocated,
// use the getline function to read the file libe by line.  This
// is directly analogous to the readLine method in Java.
//
// Notice that the first argument to getline is a pointer to
// a pointer.  This type of argument passing is used when
// the function modifies that actual value of the pointer itself
// as well as the data that the pointer references.  This detail
// is beyond the scope of this course.

// Another detail about the behavior of the getline function -
// it returns the \n (newline) delimiter at the end of the
// current line, so you need to remember to strip this off
// depending on how you use the string.  Since this function
// simply prints the file, the newline is left in and does not
// have to be added in the printf call.

	printf("Listing of file %s:\n",argv[1]);

	while ((linelen=getline(&line,(size_t *)&bufsize,FileD))>0)
		printf("%s",line);
	printf("End of file\n");

	return EXIT_SUCCESS;
}

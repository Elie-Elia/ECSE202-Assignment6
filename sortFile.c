/*
======================================================================
Name : listFile.c
Author : E. Elia
Version :
Copyright : Your copyright notice
Description : A "C" version of the fileReader program originally
: written Java for Assignment 2. This one uses the
command
: line interface to obtain the file name. Like its
predecessor,
: this program reads a text file line by line, displaying
the
: output on the standard output. Use this program as a
basis
: for Assignment 6.
======================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define STRLEN 80
#define MAXBUF 100

ssize_t getline(char **lineptr, size_t *n, FILE *stream) {
    char *bufptr = NULL;
    char *p = bufptr;
    size_t size;
    int c;

    if (lineptr == NULL) {
        return -1;
    }
    if (stream == NULL) {
        return -1;
    }
    if (n == NULL) {
        return -1;
    }
    bufptr = *lineptr;
    size = *n;

    c = fgetc(stream);
    if (c == EOF) {
        return -1;
    }
    if (bufptr == NULL) {
        bufptr = malloc(128);
        if (bufptr == NULL) {
            return -1;
        }
        size = 128;
    }
    p = bufptr;
    while(c != EOF) {
        if ((p - bufptr) > (size - 1)) {
            size = size + 128;
            bufptr = realloc(bufptr, size);
            if (bufptr == NULL) {
                return -1;
            }
        }
        *p++ = c;
        if (c == '\n') {
            break;
        }
        c = fgetc(stream);
    }

    *p++ = '\0';
    *lineptr = bufptr;
    *n = size;

    return p - bufptr - 1;
}


//Structure for the binary tree
struct BinaryTree{
    //Payload value to be stored as an array of characters
    char payload [STRLEN];
    //Pointer to the left node
    struct BinaryTree* left;
    //Pointer to the right node
    struct BinaryTree* right;
};

//Method to traverse and print the binary tree in left-root-right order
void traversebTree(struct BinaryTree* btree)
{
    //If the left of the binary tree is not null
    if(btree->left != NULL)
        //Traverse the left tree
        traversebTree(btree->left);
    //Print the value of the payload
    printf("%s",btree->payload);
    //If the right of the binary tree is not null
    if(btree->right !=NULL)
        //Traverse the right of the tree
        traversebTree(btree->right);
}

//Method to create the binary tree
struct BinaryTree* create_binaryTree(char* new_payload)
{
    //Allocating space in memory to store the Binary Tree
    struct BinaryTree* tree_add = (struct BinaryTree*)malloc(sizeof(struct BinaryTree));
    //Copy the payload to the data of the bnode
    strcpy(tree_add->payload, new_payload);
    //Pointer to the left of the node
    tree_add->left = NULL;
    //Pointer to the right of the node
    tree_add->right = NULL;
    return tree_add;
}

//Method to add a node to the Binary Tree
void addNode(char* new_payload,struct BinaryTree* btree)
{
    //If the new payload being added is smaller than the root value
    if(strcmp(new_payload,(btree->payload)) <0)
    {
        //As long as the the left branch of tree is not empty
        if(btree->left != NULL)
        {
            //A new node is added to the left with a new value as payload
            addNode(new_payload,btree->left);
        }
        else
        {
            //Otherwise, a new binary tree is created to the left
            btree->left = create_binaryTree(new_payload);
        }


    }else{

        //As long as the right branch of the tree is not empty
        if(btree->right != NULL){
            //A new node is added to the right with a new value as payload
            addNode(new_payload,btree->right);
        }
        else
        {
            //Otherwise, a new binary tree is created to the right
            btree->right = create_binaryTree(new_payload);
        }

    }

}


int main(int argc, char *argv[]) {

    FILE * FileD; // File descriptor (an object)!
    char *line; // Pointer to buffer used by getline
    int bufsize = MAXBUF; // Size of buffer to allocate
    int linelen; // Length of string returned (getline)
    if (argc != 2) {
        printf("Usage: fileReader [text file name]\n");
        return -1;
    }

    if ((FileD=fopen(argv[1],"r"))==NULL) {
        printf("Can't read from file %s\n",argv[1]);
        return -2;
    }
    line=(char *)malloc(bufsize+1);
    if (line==NULL) {
        printf("Unable to allocate a buffer for reading.\n");
        return -3;
    }
    printf("Listing of file %s:\n",argv[1]);

    int i = 0; //i is a counter
    struct binarytree* root;
    while ((linelen=getline(&line,(size_t *)&bufsize,FileD))>0){
        if (i<1){
            root = create_binaryTree(line);// creates node and adds name to it
            i++;
        } else {
            addNode(line, root); //adds the node with the name in the correct position in binary tree
        }

    }

    printf("File in sort order:\n\n");
    //Call the function to traverse the Binary Tree
    traversebTree(root);
    printf("\nprogram terminated\n\n");
    return EXIT_SUCCESS;
}
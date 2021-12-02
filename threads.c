#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include "lab10.h"

#define NODE struct contact
#define SIZE 26

/*
*****************************************************************
*
*       functions implementation
*
*****************************************************************
*/

void *auto_saver() //Auto Saver thread function
{
    FILE *fp; //File pointer
    NODE *p; //temporary node to hold each node from file

    if ((p = (NODE *)malloc(sizeof(NODE))) == NULL)
    {
        printf("Malloc error...\n"); //Error given if pointers not allocated successfully
        exit(1);
    }

    

    while (1)
    {
        sleep(5);
        
        fp = fopen("temp", "wb"); //Writing to the file (overwriting)

        if (fp == NULL) //If file does not exist
        {
            printf("The file cannot be saved.\n");
            exit(1); 
        }

        int letterIndex;
        for (letterIndex = 0; letterIndex < SIZE; ++letterIndex)
        {
            p = lists[letterIndex];
            
            while (p != NULL) //While node is not null
            {
                pthread_mutex_lock(&mutex);
                fwrite(p, sizeof(NODE), 1, fp); //Writes one node to the file
                pthread_mutex_unlock(&mutex);
                p = p->next; //Contiues to the next node
            }
        }

        fclose(fp); //Closes file pointer
    }

    return NULL;
}
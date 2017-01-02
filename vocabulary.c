//
//  vocabulary.c
//  test
//
//  Created by bb107110 on 11/10/14.
//  Copyright (c) 2014 bb107110. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_LINE 1024
#define MAX_FIELD 128
#define NUM_FIELD 4

int main ( int argc, char *argv[] )
{
    char buf[MAX_LINE];
    const char* token = ",";
    int linenum=0;
    
    if ( argc != 2 ) /* argc should be 2 for correct execution */
    {
        /* We print argv[0] assuming it is the program name */
        printf( "usage: %s filename", argv[0] );
    }
    else
    {
        // We assume argv[1] is a filename to open
        FILE *file = fopen( argv[1], "r" );
        
        /* fopen returns 0, the NULL pointer, on failure */
        if ( file == NULL )
        {
            printf( "Could not open file %s\n", argv[1] );
        }
        else
        {
            while  ( fgets(buf, MAX_LINE, file ) != NULL )
            {
                linenum++;
            }
            rewind(file);
            char voc[linenum][NUM_FIELD][MAX_FIELD];
            linenum=0;
            while  ( fgets(buf, MAX_LINE, file ) != NULL )
            {
                char *k, *kn;
                int knum=0;
                k = strtok(buf,token);
                while (k != NULL) {
                    kn=strchr(k,'\n');
                    if (kn != NULL) {
                        *kn='\0';
                    }
                    strcpy(voc[linenum][knum],k);
                    knum++;
                    k = strtok(NULL,token);
                }
                linenum++;
            }
            fclose( file );
            srand ( time(NULL) );
            linenum--;
            for (int i = linenum; i > 0; i--)
            {
                int j = rand() % (i);
                j++;
                char temp[MAX_FIELD];
                for (int l=0; l<NUM_FIELD ; l++) {
                    strcpy(temp,voc[i][l]);
                    strcpy(voc[i][l],voc[j][l]);
                    strcpy(voc[j][l],temp);
                    }
            }
            for (int i=1; i<=linenum; i++) {
                char resp[MAX_FIELD], *n;
                //printf ("%s %s %s %s \n",voc[i][0],voc[i][1],voc[i][2],voc[i][3]);
                int j = rand() % (NUM_FIELD);
                sleep(1);
                system("TERM=vt100; export TERM; clear");
                printf ("%s : %s\n", voc[0][j], voc[i][j]);
                for (int k=0; k<NUM_FIELD; k++) {
                    if (k != j) {
                        printf("%s ?", voc[0][k]);
                        fgets(resp,MAX_FIELD,stdin);
                        n=strchr(resp, '\n');
                        if (n != NULL) {
                            *n = '\0';
                        }
                        if ( strcmp(resp, voc[i][k]) != 0) {
                            printf ("\nwrong !\n");
                        }
                    }
                }
                
            }
            
        }
        
    }
}

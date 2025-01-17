/******************************************************************************
 *
 * Project:  Shapelib
 * Purpose:  Sample application for adding a shape to a shapefile.
 * Author:   Frank Warmerdam, warmerdam@pobox.com
 *
 ******************************************************************************
 * Copyright (c) 1999, Frank Warmerdam
 *
 * This software is available under the following "MIT Style" license,
 * or at the option of the licensee under the LGPL (see COPYING).  This
 * option is discussed in more detail in shapelib.html.
 *
 * --
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ******************************************************************************
 *
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shapefil.h"

int main(int argc, char **argv)
{
    /* -------------------------------------------------------------------- */
    /*      Display a usage message.                                        */
    /* -------------------------------------------------------------------- */
    if (argc < 2)
    {
        printf("shpadd shp_file [[x y] [+]]*\n");
        printf("  or\n");
        printf("shpadd shp_file -m [[x y m] [+]]*\n");
        printf("  or\n");
        printf("shpadd shp_file -z [[x y z] [+]]*\n");
        printf("  or\n");
        printf("shpadd shp_file -zm [[x y z m] [+]]*\n");
        exit(1);
    }

    const char *filename = argv[1];
    argv++;
    argc--;

    /* -------------------------------------------------------------------- */
    /*      Check for tuple description options.                            */
    /* -------------------------------------------------------------------- */
    const char *tuple = "";

    if (argc > 1 && (strcmp(argv[1], "-z") == 0 || strcmp(argv[1], "-m") == 0 ||
                     strcmp(argv[1], "-zm") == 0))
    {
        tuple = argv[1] + 1;
        argv++;
        argc--;
    }

    /* -------------------------------------------------------------------- */
    /*      Open the passed shapefile.                                      */
    /* -------------------------------------------------------------------- */
    SHPHandle hSHP = SHPOpen(filename, "r+b");

    if (hSHP == NULL)
    {
        printf("Unable to open:%s\n", filename);
        exit(1);
    }

    int nShapeType;
    SHPGetInfo(hSHP, NULL, &nShapeType, NULL, NULL);

    if (argc == 1)
        nShapeType = SHPT_NULL;

    /* -------------------------------------------------------------------- */
    /*	Build a vertex/part list from the command line arguments.	*/
    /* -------------------------------------------------------------------- */
    int nVMax = 1000;
    double *padfX = (double *)malloc(sizeof(double) * nVMax);
    double *padfY = (double *)malloc(sizeof(double) * nVMax);

    double *padfZ = NULL;
    if (strchr(tuple, 'z'))
        padfZ = (double *)malloc(sizeof(double) * nVMax);
    double *padfM = NULL;
    if (strchr(tuple, 'm'))
        padfM = (double *)malloc(sizeof(double) * nVMax);

    int *panParts;
    if ((panParts = (int *)malloc(sizeof(int) * 1000)) == NULL)
    {
        printf("Out of memory\n");
        exit(1);
    }

    int nParts = 1;
    panParts[0] = 0;
    int nVertices = 0;

    for (int i = 1; i < argc;)
    {
        if (argv[i][0] == '+')
        {
            panParts[nParts++] = nVertices;
            i++;
        }
        else if (i < argc - 1 - (int)strlen(tuple))
        {
            if (nVertices == nVMax)
            {
                nVMax = nVMax * 2;
                padfX = (double *)realloc(padfX, sizeof(double) * nVMax);
                padfY = (double *)realloc(padfY, sizeof(double) * nVMax);
                if (padfZ)
                    padfZ = (double *)realloc(padfZ, sizeof(double) * nVMax);
                if (padfM)
                    padfM = (double *)realloc(padfM, sizeof(double) * nVMax);
            }

            sscanf(argv[i++], "%lg", padfX + nVertices);
            sscanf(argv[i++], "%lg", padfY + nVertices);
            if (padfZ)
                sscanf(argv[i++], "%lg", padfZ + nVertices);
            if (padfM)
                sscanf(argv[i++], "%lg", padfM + nVertices);

            nVertices += 1;
        }
    }

    /* -------------------------------------------------------------------- */
    /*      Write the new entity to the shape file.                         */
    /* -------------------------------------------------------------------- */
    SHPObject *psObject =
        SHPCreateObject(nShapeType, -1, nParts, panParts, NULL, nVertices,
                        padfX, padfY, padfZ, padfM);
    SHPWriteObject(hSHP, -1, psObject);
    SHPDestroyObject(psObject);

    SHPClose(hSHP);

    free(panParts);
    free(padfX);
    free(padfY);
    free(padfZ);
    free(padfM);

    return 0;
}

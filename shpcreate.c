/******************************************************************************
 *
 * Project:  Shapelib
 * Purpose:  Sample application for creating a new shapefile.
 * Author:   Frank Warmerdam, warmerdm@pobox.com
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shapefil.h"

int main(int argc, char **argv)
{
    /* -------------------------------------------------------------------- */
    /*      Display a usage message.                                        */
    /* -------------------------------------------------------------------- */
    if (argc != 3)
    {
        printf("shpcreate shp_file [point/arc/polygon/multipoint][/m/z]\n");
        exit(1);
    }

    /* -------------------------------------------------------------------- */
    /*	Figure out the shape type.					*/
    /* -------------------------------------------------------------------- */
    int nShapeType;
    if (strcmp(argv[2], "POINT") == 0 || strcmp(argv[2], "point") == 0)
        nShapeType = SHPT_POINT;
    else if (strcmp(argv[2], "ARC") == 0 || strcmp(argv[2], "arc") == 0)
        nShapeType = SHPT_ARC;
    else if (strcmp(argv[2], "POLYGON") == 0 || strcmp(argv[2], "polygon") == 0)
        nShapeType = SHPT_POLYGON;
    else if (strcmp(argv[2], "MULTIPOINT") == 0 ||
             strcmp(argv[2], "multipoint") == 0)
        nShapeType = SHPT_MULTIPOINT;
    else if (strcmp(argv[2], "POINTZ") == 0 || strcmp(argv[2], "pointz") == 0)
        nShapeType = SHPT_POINTZ;
    else if (strcmp(argv[2], "ARCZ") == 0 || strcmp(argv[2], "arcz") == 0)
        nShapeType = SHPT_ARCZ;
    else if (strcmp(argv[2], "POLYGONZ") == 0 ||
             strcmp(argv[2], "polygonz") == 0)
        nShapeType = SHPT_POLYGONZ;
    else if (strcmp(argv[2], "MULTIPOINTZ") == 0 ||
             strcmp(argv[2], "multipointz") == 0)
        nShapeType = SHPT_MULTIPOINTZ;
    else if (strcmp(argv[2], "POINTM") == 0 || strcmp(argv[2], "pointm") == 0)
        nShapeType = SHPT_POINTM;
    else if (strcmp(argv[2], "ARCM") == 0 || strcmp(argv[2], "arcm") == 0)
        nShapeType = SHPT_ARCM;
    else if (strcmp(argv[2], "POLYGONM") == 0 ||
             strcmp(argv[2], "polygonm") == 0)
        nShapeType = SHPT_POLYGONM;
    else if (strcmp(argv[2], "MULTIPOINTM") == 0 ||
             strcmp(argv[2], "multipointm") == 0)
        nShapeType = SHPT_MULTIPOINTM;
    else
    {
        printf("Shape Type `%s' not recognised.\n", argv[2]);
        exit(2);
    }

    /* -------------------------------------------------------------------- */
    /*	Create the requested layer.					*/
    /* -------------------------------------------------------------------- */
    SHPHandle hSHP = SHPCreate(argv[1], nShapeType);

    if (hSHP == NULL)
    {
        printf("Unable to create:%s\n", argv[1]);
        exit(3);
    }

    SHPClose(hSHP);

    return 0;
}

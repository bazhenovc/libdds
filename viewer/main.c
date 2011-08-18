/*
 * libdds
 * Copyright (c) 2010 Cyril Bazhenov bazhenovc@gmail.com
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <libdds.h>
#include <libdds_opengl.h>

#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>

/* Our texture */
static DDS_GL_TextureInfo texture;

/* Cleanup */
static void cleanup () {
    ddsGL_free (&texture);
}

/* Draw our texture */
static void display () {
    glClear (GL_COLOR_BUFFER_BIT);

    glEnable (GL_TEXTURE_2D);
    glBindTexture (GL_TEXTURE_2D, texture.id);
    glBegin (GL_QUADS);
    glTexCoord2f (0.0f, 0.0f);
    glVertex3f (-0.5f, -0.5f, 0.0f);

    glTexCoord2f (1.0f, 0.0f);
    glVertex3f (0.5f, -0.5f, 0.0f);

    glTexCoord2f (1.0f, 1.0f);
    glVertex3f (0.5f, 0.5f, 0.0f);

    glTexCoord2f (0.0f, 1.0f);
    glVertex3f (-0.5f, 0.5f, 0.0f);
    glEnd ();
    glutSwapBuffers ();
}

static void key (unsigned char key, int x, int y) {
    if (key == 27) {
        exit (0);
    }
}

int main (int argc, char** argv) {
    const char* imagename = argc < 2 ? "images/fungus.dds" : argv[1];

    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize (800, 600);

    glutCreateWindow (imagename);

    glutDisplayFunc (display);
    glutKeyboardFunc (key);

    /* Load texture */
    int err = ddsGL_load (imagename, &texture);
    if (err != DDS_OK) {
        printf ("DDS load error: %s\n", dds_error_string (err));
        return (1);
    }
    atexit (cleanup);

    glutMainLoop ();

    return (0);
}

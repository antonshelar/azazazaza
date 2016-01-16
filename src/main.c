#include <GL/glut.h>
#include <stdio.h>
#include "main.h"
#include "pixmap.h"
#include "image.h"

void displayFunc();
void start();

int wnd_id = 0;

int main(int argc, char **argv){

	struct image img;
	read_image("/home/os/workspace/azazazaza/Debug/Untitled.png", &img);

	bufer_init(img.width, img.height);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(img.width, img.height);
	glutInitWindowPosition(100, 100);

	wnd_id = glutCreateWindow("Image");

	glClearColor (1.0, 1.0, 1.0, 0.0);

	glutDisplayFunc(displayFunc);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)img.width, 0.0, (GLdouble)img.height);

	/* draw image */
	//set_pixels(img.pixels, img.width * img.height);

	struct b8_image *grayscale = binarize_image(&img);

	glBegin(GL_POINTS);
	for(unsigned int pix = 0; pix < grayscale->width * grayscale->height; pix++){



		set_pixel_(grayscale->pixels[pix].color, grayscale->pixels[pix].color,
				grayscale->pixels[pix].color, grayscale->pixels[pix].x, grayscale->pixels[pix].y
				);

	}
	glEnd();
	glFlush();

	printf("OK\n");

	glutMainLoop();



	return 0;

}

void displayFunc(){

	flush_bufer();

}

void start(){


}

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <math.h>
#include <stdbool.h>
// #define TEXTURE_PATH "/home/vinitha/fractalblack.jpg"
#define WIDTH 256
#define HEIGHT 256
#define MAX 7
#define interval 30
#define line 4
const float PI = 3.141592654f;
typedef GLfloat point2[2];


int xval[4], yval[4];
GLuint texture;
void init();
void display();
void keys(unsigned char key,int x,int y);
int val=-1;
int win, win1;
GLfloat oldx=-0.7,oldy=0.5;
float x=400;
float y=250;
float theta=0;
bool draw=true;
int iter=0;

void Forward(float dist)
{
    float thetaRadians = (theta/180.0f)*PI;

    float lx = dist*cos(thetaRadians);
    float ly = dist*sin(thetaRadians);

    float x1 = x + lx;
    float y1 = y + ly;

    float x0 = x;
    float y0 = y;

    if(draw){
        glBegin(GL_LINE_STRIP);
        glVertex2f(x0, y0);
        glVertex2f(x1, y1);
        glEnd();
    }

    x = x1;
    y = y1;

    glFlush();
}

void Right(float _theta)
{
    theta = theta - _theta;
    if(theta < 0){
        theta = 360 + theta;
    }
}

void Left(float _theta)
{
    theta = theta + _theta;
    if(theta > 360){
        theta = theta - 360;
    }
}

void dragon(int n)
{
 glDisable(GL_TEXTURE_2D);
    if(n==0)
        Forward(line);
    else
    {
        dragon(n-1);
        Left(90.0);
        nogard(n-1);
    }
}

void nogard(int n)
{
    if(n==0)
        Forward(line);
    else
    {
        dragon(n-1);
        Right(90.0);
        nogard(n-1);
    }
}

void keys(unsigned char key,int x,int y)
{
   switch(key)
    {
        case 27:
        exit(0);
    }
}

void sierpinski()
{
    glDisable(GL_TEXTURE_2D);
   GLfloat vertices[3][3] = {{100.0,100.0,0.0}, {225,350,0.0} , {350.0,100.0,0.0}};
   GLfloat p[3]={7.5,5.0,0.0};
   int j,k;

   glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1, 1, 1, 1);
    glFlush();
   glColor3f(1.0, 0.0, 0.0);
   glBegin(GL_POINTS);
   for(k=0;k<50000;k++)
   {
        glBegin(GL_POINTS);
          j=rand()%3;
          p[0]=(p[0]+vertices[j][0])/2;
          p[1]=(p[1]+vertices[j][1])/2;
          /*display new points*/
          glVertex2fv(p);
           glFlush();
           glEnd();
          glFlush();
}

//glFlush();
}

void drawkoch(GLfloat dir,GLfloat len,GLint iter) {

	GLdouble dirRad = 0.0174533 * dir;
	GLfloat x1, x2, y1, y2;
    glDisable(GL_TEXTURE_2D);
	GLfloat newX = oldx + len * cos(dirRad);
	GLfloat newY = oldy + len * sin(dirRad);
	if (iter==0) {
		if(oldx<0)
            x1=(1+oldx)*250;
        else
             x1=(oldx*250)+250;
        if(oldy<0)
            y1=(1+oldy)*250;
        else
             y1=(oldy*250)+250;
        if(newX<0)
            x2=(1+newX)*250;
        else
             x2=(newX*250)+250;
        if(newY<0)
            y2=(1+newY)*250;
        else
             y2=(newY*250)+250;
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		oldx = newX;
		oldy = newY;
		}
	else {
		iter--;
		//draw the four parts of the side _/\_
		drawkoch(dir, len, iter);
		dir += 60.0;
		drawkoch(dir, len, iter);
		dir -= 120.0;
		drawkoch(dir, len, iter);
		dir += 60.0;
		drawkoch(dir, len, iter);
	}
}

void cantor(int loop, int x0, int x1, int x[4], int y[4])
{
    int x2[4], y2[4];
    y[3]=y[2]= loop*interval*2;
    y[0]=y[1]=y[3]-interval;

    glDisable(GL_TEXTURE_2D);
    if(loop==MAX)
    {
        x[0]=x[3]=x0;
        x[1]=x[2]=x1;

        glBegin(GL_POLYGON);
        glVertex2i(x[0], y[0]);
        glVertex2i(x[1], y[1]);
        glVertex2i(x[2], y[2]);
        glVertex2i(x[3], y[3]);
        glEnd();

        cantor(loop-1, x[0], x[1], x2, y2);
    }

    else if(loop>1)
    {
        x[0]=x[3]=x0;
        x[2]=x[1]=x0+((x1-x0)/3);

        glBegin(GL_QUADS);
        glVertex2i(x[0], y[0]);
        glVertex2i(x[1], y[1]);
        glVertex2i(x[2], y[2]);
        glVertex2i(x[3], y[3]);
        glEnd();

        cantor(loop-1, x[0], x[1], x2, y2);

        x[2]=x[1]=x1;
        x[0]=x[3]= x0+ (2*(x1-x0))/3;

        glBegin(GL_QUADS);
        glVertex2i(x[0], y[0]);
        glVertex2i(x[1], y[1]);
        glVertex2i(x[2], y[2]);
        glVertex2i(x[3], y[3]);
        glEnd();

        cantor(loop-1, x[0], x[1], x2, y2);
    }

    else
    {

        x[0]=x[3]=x0;
        x[2]=x[1]=x0+((x1-x0)/3);

        glBegin(GL_QUADS);
        glVertex2i(x[0], y[0]);
        glVertex2i(x[1], y[1]);
        glVertex2i(x[2], y[2]);
        glVertex2i(x[3], y[3]);
        glEnd();

        x[2]=x[1]=x1;
        x[0]=x[3]= x0+ (2*(x1-x0))/3;

        glBegin(GL_QUADS);
        glVertex2i(x[0], y[0]);
        glVertex2i(x[1], y[1]);
        glVertex2i(x[2], y[2]);
        glVertex2i(x[3], y[3]);
        glEnd();
    }
}


void barnsley()
{
    glDisable(GL_TEXTURE_2D);
    int i;
    point2 p;
    int point_num = 100000;
    double prob[4] = { 0.85, 0.92, 0.99, 1.00 };
    double r;
    double x;
    double y;

    glClear( GL_COLOR_BUFFER_BIT );

    p[0] = drand48();
    p[1] = drand48();

    for( i = 0; i < point_num; i++ )
    {
        r = drand48();

        if( r < prob[0] )
        {
            x =   0.85 * p[0] + 0.04 * p[1] + 0.0;
            y = - 0.04 * p[0] + 0.85 * p[1] + 1.6;
        }
        else if( r < prob[1] )
        {
            x =   0.20 * p[0] - 0.26 * p[1] + 0.0;
            y =   0.23 * p[0] + 0.22 * p[1] + 1.6;
        }
        else if( r < prob[2] )
        {
            x = - 0.15 * p[0] + 0.28 * p[1] + 0.0;
            y =   0.26 * p[0] + 0.24 * p[1] + 0.44;
        }
        else
        {
            x =   0.00 * p[0] + 0.00 * p[1] + 0.0;
            y =   0.00 * p[0] + 0.16 * p[1] + 0.0;
        }

        p[0] = x;
        p[1] = y;
        y=41.66*y;
        if(x<0)
            x=(6+x)*41.66;
        else
            x=250+(x*41.66);

        glBegin( GL_POINTS );
        glVertex2d(x,y);
        glEnd();

        glFlush();
    }
    return;
}


void menu(int value)
{
	if(value == 6){
		glutDestroyWindow(win);
		exit(0);
	}else{
		val=value;
	}
}

void createMenu(void)
{
	glutCreateMenu(menu);
	glutAddMenuEntry("SIERPINSKI GASKET", 1);
	glutAddMenuEntry("KOCH SNOWFLAKE", 2);
	glutAddMenuEntry("BARNSLEY FERN", 3);
	glutAddMenuEntry("CANTOR SET", 4);
	glutAddMenuEntry("DRAGON CURVE", 5);
    glutAddMenuEntry("QUIT",6);

	// Let the menu respond on the right mouse button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void drawstring(int x, int y, char *string)
{
    glRasterPos2f(x, y);
    int len, i;
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
    }
}

GLuint LoadTextureRAW(const char * filename, int wrap);


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    win=glutCreateWindow("Fractal geometry");
    init();
    createMenu();
    glutDisplayFunc(display);
    //glutReshapeFunc(reshape);
    glutKeyboardFunc(keys);
    glutMainLoop();
    return 0;
}

void init()
{
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(0,499,0,499);
    glEnable(GL_TEXTURE_2D);
    texture = SOIL_load_OGL_texture
    (
        TEXTURE_PATH,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
// check for an error during the load process
    if(texture == 0)
    printf("SOIL loading error: '%s'\n", SOIL_last_result());

}


void display()
{
    switch(val)
    {
        case -1:
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(1, 1, 1, 1);
            glBegin( GL_QUADS );
            glTexCoord2f(0.0,0.0);
            glVertex2d(0.0, 0.0);
            glTexCoord2d(1.0,0.0);
            glVertex2d(499.0,0.0);
            glTexCoord2d(1.0,1.0);
            glVertex2d(499.0,499.0);
            glTexCoord2d(0.0,1.0);
            glVertex2d(0.0,499.0);
            glEnd();
            glFlush();
            glColor3f(0,0,1);
            drawstring(150, 400,"A MINI PROJECT ON");
            glColor3f(1,0,0);
            drawstring(200,350,"3D MAZE");
            glColor3f(1,0.5,0);
            drawstring(20,250,"BY:");
            glColor3f(0.5,0,0.5);
            drawstring(10,200,"ANKITA KUMARI 1PE12CS018");
            drawstring(10,160,"BHOOMIKA AGARWAL 1PE12CS033");
            glColor3f(1,0.5,0);
            drawstring(20,120,"GUIDE:");
            glColor3f(0.5,0.2,0.2);
            drawstring(10,80,"SHEELA D.");
            glColor3f(1,0.1,1);
            drawstring(125,20,"RIGHT CLICK TO SEE THE MENU");
            glFlush();
            break;

        case 1:
            sierpinski();
            glFlush();
            break;

        case 2:
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.0,0.0,1.0,1.0);
            glLineWidth(3.0);
            glColor3f(1.0, 1.0, 1.0);
            glBegin(GL_LINES);
            drawkoch(0.0,0.05,3);
            drawkoch(-120.0, 0.05,3);
            drawkoch(120.0,0.05,3);
            glEnd();
            glFlush();
            break;

        case 3:
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor( 1.0, 1.0, 1.0, 1.0 );
            glColor3f( 0.133, 0.545, 0.133 );
            barnsley();
            glFlush();
            break;

        case 4:
            gluOrtho2D(-1,1,-1,1);
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(1.0, 1.0, 1.0, 1.0);
            glColor3f(0.0,0.0,1.0);
            glFlush();
            cantor(MAX, 100, 400, xval, yval);
            glFlush();
            break;

        case 5:
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(1.0, 1.0, 1.0, 1.0);
            glColor3f(1.0, 0.0, 0.0);
            glLineWidth(2.0);
            x=400;
            y=250;
            theta=0;
            dragon(12);
            glFlush();
            break;
    }
}



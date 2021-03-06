/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */
#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <bits/stdc++.h>
/* GLUT callback Handlers */
using namespace std;
float polyg[20][2];
float bp[20][2];
int n=0,np=0;


void init()
{   glClearColor(0,0,0,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);

}
static void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);
}

vector<float> fn(float t)
{   vector<float>a;
    float temp[20][2];
    if(np==1)
    {   cout<<"inner call"<<endl;
        a.push_back(bp[0][0]);
        a.push_back(bp[0][1]);
        return a;
    }
    else
    {
        for(int i=0;i<np-1;i++)
        {   temp[i][0]=t*bp[i][0]+(1-t)*bp[i+1][0];
            temp[i][1]=t*bp[i][1]+(1-t)*bp[i+1][1];

        }
        for(int i=0;i<np-1;i++)
        {   bp[i][0]=temp[i][0];
            bp[i][1]=temp[i][1];
        }
        np=np-1;
        a=fn(t);
        return a;
    }
}
void drawbezier()
{
    glColor3d(1,0,0);
    glBegin(GL_LINES);
        for(int i=0;i<n-1;i++)
        {
            glVertex2f(polyg[i][0],polyg[i][1]);
            glVertex2f(polyg[i+1][0],polyg[i+1][1]);
        }
    glEnd();
    glFlush();

    np=n;
    cout <<"n,np is"<<n<<","<<np<<endl;
    glColor3d(0,1,0);
    glBegin(GL_POINTS);
    cout << "2";
    for(float t=0.0;t<=1;t+=0.01)
    {     for(int i=0;i<n;i++)
        {
            bp[i][0]=polyg[i][0];
            bp[i][1]=polyg[i][1];
        }
        np=n;
        cout <<"t values is"<<t<<endl;
        vector <float> a1=fn(t);
        cout<<"the curve point is"<<a1[0]<<" ,"<<a1[1]<<endl;
        glVertex2f(a1[0],a1[1]);
    }
    glEnd();
    glFlush();

}
void mousehandler(int button,int state,int x ,int y)
{   if(button==GLUT_LEFT_BUTTON &&state==GLUT_DOWN)
    {   cout<<"point is"<<x<<" "<<480-y<<endl;
        polyg[n][0]=x;
        polyg[n][1]=480-y;
        glColor3d(1,1,1);
        glPointSize(3.0);
        glBegin(GL_POINTS);
            glVertex2f(x,480-y);
        glEnd();
        glFlush();
        n+=1;
    }
    else if(button==GLUT_RIGHT_BUTTON &&state==GLUT_DOWN)
    {
        drawbezier();
        n=0;



    }

}

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutCreateWindow("GLUT Shapes");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mousehandler);
    glutMainLoop();

    return EXIT_SUCCESS;
}
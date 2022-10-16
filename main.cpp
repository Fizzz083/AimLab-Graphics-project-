#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include<bits/stdc++.h>
#include "include/BmpLoader.h"

#define gt(x, y, z) glTranslatef(x,y,z)
#define gs(x, y, z) glScalef(x, y, z)
#define gr(a,x,y,z) glRotatef(a, x, y, z)
#define gpu glPushMatrix()
#define gpo glPopMatrix()




using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

double Txval=0,Tyval=0,Tzval=0, arodure=60;
double radius = 80;
double eyex = 80;
double eyey = 60;
double eyez = radius;
double centerx = eyex;
double centery = eyey;
double centerz = 0;
double upx = 0;
double upy = 1;
double upz = 0;
double myval = 0;


double windowHeight=960, windowWidth=540;
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0;
GLboolean bRotate = false, uRotate = false;
double far_id =1000.0;
double near_id = 4.0;
unsigned int ID[100], ID1;
 /// 1920x1080
 int ini_x, ini_y ;

static void resize(int width, int height)
{
    const float ar = (float) height / (float) width;
    ini_x = width/2;
    ini_y = height/2;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -ar, ar, near_id, far_id);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;

}

static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}



GLfloat cube_coordinate[8][3] =
{
    {0.0,0.0,0.0},
    {0.0,2.0,0.0},
    {2.0,2.0,0.0},
    {2.0,0.0,0.0},

    {0.0,0.0,-2.0},
    {0.0,2.0,-2.0},
    {2.0,2.0,-2.0},
    {2.0,0.0,-2.0}

};
static GLubyte cube_indices[6][4] =
{
    {0,3,2,1},
    {3,7,6,2},
    {7,4,5,6},
    {4,0,1,5},

    {1,2,6,5},
    {7,4,0,3}


};

static GLubyte pyramid_indices[6][4] =
{
    {0,3,2,1},
    {3,7,2,2},
    {7,4,1,2},
    {4,0,1,1},

    //{1,2,6,5},
    {7,4,0,3}


};

void draw_angular_cube()
{
    GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glBegin(GL_QUADS);
    for (GLint i = 0; i <5; i++)
    {
        //glColor3f(0.1f, 0.1f, 0.1f);
        //glColor3f(0.2f, 0.2f, 0.2f);
        getNormal3p(cube_coordinate[pyramid_indices[i][0]][0], cube_coordinate[pyramid_indices[i][0]][1], cube_coordinate[pyramid_indices[i][0]][2],
                    cube_coordinate[pyramid_indices[i][1]][0], cube_coordinate[pyramid_indices[i][1]][1], cube_coordinate[pyramid_indices[i][1]][2],
                    cube_coordinate[pyramid_indices[i][2]][0], cube_coordinate[pyramid_indices[i][2]][1], cube_coordinate[pyramid_indices[i][2]][2]);

        glVertex3fv(&cube_coordinate[pyramid_indices[i][0]][0]);glTexCoord2f(1,0);
        glVertex3fv(&cube_coordinate[pyramid_indices[i][1]][0]);glTexCoord2f(1,1);
        glVertex3fv(&cube_coordinate[pyramid_indices[i][2]][0]);glTexCoord2f(0,0);
        glVertex3fv(&cube_coordinate[pyramid_indices[i][3]][0]);glTexCoord2f(0,1);
    }
    glEnd();


}
void draw_cube()
{
    GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3f(0.1f, 0.1f, 0.1f);
        //glColor3f(0.2f, 0.2f, 0.2f);
        getNormal3p(cube_coordinate[cube_indices[i][0]][0], cube_coordinate[cube_indices[i][0]][1], cube_coordinate[cube_indices[i][0]][2],
                    cube_coordinate[cube_indices[i][1]][0], cube_coordinate[cube_indices[i][1]][1], cube_coordinate[cube_indices[i][1]][2],
                    cube_coordinate[cube_indices[i][2]][0], cube_coordinate[cube_indices[i][2]][1], cube_coordinate[cube_indices[i][2]][2]);


        glVertex3fv(&cube_coordinate[cube_indices[i][0]][0]);glTexCoord2f(1,0);
        glVertex3fv(&cube_coordinate[cube_indices[i][1]][0]);glTexCoord2f(1,1);
        glVertex3fv(&cube_coordinate[cube_indices[i][2]][0]);glTexCoord2f(0,0);
        glVertex3fv(&cube_coordinate[cube_indices[i][3]][0]);glTexCoord2f(0,1);
    }
    glEnd();


}

void draw_color_cube(GLfloat c1,GLfloat c2,GLfloat c3 )
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.6*c1, 0.6*c2, 0.6*c3, 1.0 };
    GLfloat mat_diffuse[] = { c1, c2, c3, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {40};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3f(0.1f, 0.1f, 0.1f);
        //glColor3f(0.2f, 0.2f, 0.2f);
        glVertex3fv(&cube_coordinate[cube_indices[i][0]][0]);
        glVertex3fv(&cube_coordinate[cube_indices[i][1]][0]);
        glVertex3fv(&cube_coordinate[cube_indices[i][2]][0]);
        glVertex3fv(&cube_coordinate[cube_indices[i][3]][0]);
    }
    glEnd();

}

void draw_floor(GLint id)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0, 0, 0, 1.0 };
    GLfloat mat_diffuse[] = { 0.0039, .1961, 0.12,1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {40};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glEnable(GL_TEXTURE_2D);
    //gt(-75,-5,50);
    //gs(80,1,80);
    glBindTexture(GL_TEXTURE_2D, id);
    draw_cube();
    glDisable(GL_TEXTURE_2D);

}

double anglex = 0;

void draw_pointer()
{

   // cout<<anglex<<endl;
   // gt(anglex, 0,0);

    gt(0,0,0.5);
    //gs(300,300,300);
    gpu;

    gt(centerx, centery, centerz);

    glScalef(1,0.4,0.1);
    draw_color_cube(1,0,0);
    gpo;

    gpu;

    //gr(90,0,0,1);
     gt(0.75,-1.5,0);
    //gt(eyex, eyey, eyez);
     gt(centerx, centery, centerz);
    glScalef(0.2,2,0.1);

    draw_color_cube(1,0,0);
    gpo;


}

void draw_room()
{

    //gr(anglex, 0,1,0);


    gpu;
    gs(80,1,80);
    draw_color_cube(1,1,1);
    //draw_floor(1);
    gpo;

    gpu;
    gr(90,0,0,1);
    gs(80,1,80);
    draw_color_cube(1,0,1);
    //draw_floor(1);
    gpo;


    gpu;
    gt(0,0,-160);
    gr(90,1,0,0);
    gs(80,1,80);
    draw_color_cube(0,0,1);
    //draw_floor(2);
    gpo;

    gpu;
    gt(160,0,0);
    gr(90,0,0,1);
    gs(80,1,80);
    draw_color_cube(1,0,1);
    //draw_floor(2);
    gpo;

}

double ball_radius = 5;

void draw_ball()
{
    gpu;
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.6, 0, 0, 1.0 };
    GLfloat mat_diffuse[] = { 0.3, 0.3, 1,1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {40};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glutSolidSphere(ball_radius,50,50);
    gpo;
}

const double pi = acos(-1);
const double eps = 1e-6;
inline int dcmp (double x) { if (fabs(x) < eps) return 0; else return x < 0 ? -1 : 1; }
inline double torad(double deg) { return deg / 180 * pi; }

struct Point3D{
    double x, y, z;
    Point3D() {}
    void read () {cin>>x>>y>>z;}
    void write () {cout<<x<<" --- "<<y<<" --- "<<z<<"\n";}

    Point3D(double x, double y, double z) : x(x), y(y), z(z) {}
    Point3D(const Point3D &p) : x(p.x), y(p.y), z(p.z) {}
    Point3D operator +(Point3D b)  {return Point3D(x+b.x,y+b.y, z+b.z);}
    Point3D operator -(Point3D b)  {return Point3D(x-b.x,y-b.y, z-b.z);}
    Point3D operator *(double b) {return Point3D(x*b,y*b, z*b);}
    Point3D operator /(double b) {return Point3D(x/b,y/b, z/b);}
    bool operator  <(Point3D b)  {return make_pair(make_pair(x,y),z) < make_pair(make_pair(b.x,b.y),b.z);}
    bool operator ==(Point3D b)  {return dcmp(x-b.x)==0 && dcmp(y-b.y) == 0 && dcmp(z-b.z) == 0;}
};
vector<Point3D>Ball;
typedef Point3D Vector3D;

namespace Vectorial{
    double getDot (Vector3D a, Vector3D b)  {return a.x*b.x+a.y*b.y+a.z*b.z;}
    Vector3D getCross(Vector3D a, Vector3D b) {return Point3D(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x);}
    double getLength (Vector3D a)         {return sqrt(getDot(a, a)); }
    double getPLength (Vector3D a)        {return getDot(a, a); }
    Vector3D unitVector(Vector3D v)         {return v/getLength(v);}

    double getUnsignedAngle(Vector3D u,Vector3D v){
        double cosTheta = getDot(u,v)/getLength(u)/getLength(v);
        cosTheta = max(-1.0,min(1.0,cosTheta));
        return acos(cosTheta);
    }

    Vector3D rotate(Vector3D a,Vector3D v,double deg){ // rotate a around v with degree of deg
       // a = unitVector(a);
        double rad = torad(deg);
        return v * cos(rad) + getCross(a, v)*sin(rad)+a*getDot(a, v)*(1-cos(rad)) ;
    }
}


using namespace Vectorial;

void draw_many_balls()
{
//    gpu;
//    gt(80,80,-60);
//    draw_ball();
//    gpo;



//    gpu;
////    gt(dx,dy,dz);
//    draw_ball();
//    draw_ball();
//    gpo;

    while(Ball.size()<5)
    {
        int dx = 40+rng()%80;
        int dy = 20+rng()%80;
        int dz = -60;
        Point3D b;
        b.x = dx;
        b.y = dy;
        b.z = dz;
        Ball.push_back(b);
    }

    for(int i=0;i<Ball.size();i++)
    {

        gpu;
        gt(Ball[i].x, Ball[i].y, Ball[i].z);
        draw_ball();
        gpo;
    }




}


void draw_every()
{
    draw_room();
    draw_pointer();
    draw_many_balls();

}

bool light_switch0 = 1, light_switch1 = 1, light_switch2 = 1;

void light0()
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.5, 0.5, 0.5, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   // GLfloat light_position[] = { 10, 0.0, 50.0, 1.0 };
    GLfloat light_position[] = { 200, 200, 100, 0.0 };


    if(light_switch0)
    glEnable( GL_LIGHT0);
    else
    glDisable(GL_LIGHT0);
    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);

    /*  GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
      glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
      glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 10.0); */
}






void mouse( int button, int state, int xpos, int ypos)
{
//    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
//    {

    Vector3D s,c,b;
    s.x = eyex;
    s.y = eyey;
    s.z = eyez;

    c.x = centerx;
    c.y = centery;
    c.z = centerz;

    for(int i=0;i<Ball.size();i++)
    {
        b = Ball[i];
        double p,q,r;

        p = getLength(s-c);
        q = getLength(s-b);
        r = getLength(b-c);
        double s1 = (p+q+r)/2;
        double h = (2*sqrt(s1*(s1-p)*(s1-q)*(s1-r)))/p;

        if(fabs(ball_radius-h)<=ball_radius)
        {
            Ball.erase(Ball.begin()+i);
            break;
        }
        cout<<(ball_radius-h)<<" ";
    }
    cout<<endl;







      //  cout<<ini_x<<" "<<ini_y<<" "<endl;

       cout << "Cursor Position at (" << xpos << " : " << ypos <<" "<< centerx<<" "<<centery<<endl;
   // }
}

/*

arccos((P122 + P132 - P232) / (2 * P12 * P13))

where P12 is the length of the segment from P1 to P2, calculated by

sqrt((P1x - P2x)2 + (P1y - P2y)2)

*/

double sq(double x1, double y1, double x2, double y2)
{
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

double angle_cal(double x1, double y1, double x2, double y2, double x3, double y3 )
{
    double p12 = sq(x1,y1,x2,y2);
    double p13 = sq(x1,y1,x3,y3);
    double p23 = sq(x2,y2,x3,y3);

    double ap = p12*p12 - p13*p13 - p23*p23;
    double bp = 2*p12*p13;

    if(bp==0) return 0;

    return acos(ap/bp);



    double result = atan2(y3 - y1, x3 - x1) -
                atan2(y2 - y1, x2 - x1);

    return result;

}

int last_x = ini_x, last_y=ini_y;
double sign = 1;



void mouseMove(int mx, int my) {

    //cout<<mx<<" "<<my<<endl;
    POINT Point;
    long x;
    long y;

    GetCursorPos(&Point);

    x = Point.x;
    y = Point.y;

    double dx = ((float) (((float)ini_x) - Point.x)); // how far moved x
    double dy = ((float) (((float)ini_y) - Point.y)); // how fa moved y

    int px = dx;// mx - last_x;
    int py = dy; //my - last_y;


    double old_centerx = centerx;
    double old_centerz = centerz;



    //cout<<angle_cal(0,5)<<endl;

    //cout<<px<<" : "<<py<<endl;


    centerx-=(double)px/40;
    centery+=(double)py/40;

//    if(centerx<=80 || centerx>=175 ){
//        sign*=(-1);
//    }
    //if(centerx==)
    //double ang = angle_cal(centerx, centerz,eyex, eyez, old_centerx, old_centerz);
    //anglex = ang;
    anglex = (double)px/10;
    glutPostRedisplay();
//    cout<<" ang "<<ang<<endl;
    //cout<<centerx<<" cen "<<endl;

    //centery-= (double)py/400;
    SetCursorPos(ini_x, ini_y);

}

//void glutWarpPointer(int x, int y)
//{
//    XWarpPointer(__glutDisplay, None, __glutCurrentWindow->win,
//                 0, 0, 0, 0, x, y);
//    XFlush(__glutDisplay);
//}


int f = 1;

void check()
{
    if(f==1)
    {
        SetCursorPos(ini_x, ini_y);
        f=0;

    }


}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum(-5,5, -5, 5, near_id, far_id);

    //gluPerspective(60,1,5,100);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eyex,eyey,eyez, centerx,centery,centerz, upx,upy,upz); // camera , ,
    glutSetCursor(GLUT_CURSOR_NONE);
    //glutWarpPointer();
    //glutWarpPointer(ini_x, ini_y);
   // GetMouseInput();

    light0();

    glRotatef( alpha,axis_x, axis_y, 0.0 );
    glRotatef( theta, axis_x, axis_y, 0.0 );

    glutMouseFunc(mouse);
    glutPassiveMotionFunc(mouseMove);

    gpu;
    //gs(2,5,5);
    //gt(-80,0,0);
    draw_every();
    gpo;

    glFlush();
    glutSwapBuffers();


}

int bv = 0;

void b_swap()
{
    if(bv==1)
    {
        int tmp = eyey;
        eyey = eyez;
        eyez = tmp;

        tmp = upy;
        upy = upz;
        upz = tmp;

    }
}

void bird_view()
{
//     init(6);
//     f=6;
    bv = 1-bv;
    b_swap();

}


void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 'q':
    case 'Q':
        bRotate = !bRotate;
        // uRotate = false;
        axis_x=0.0;
        axis_y=1.0;

        break;

    case 'E':
    case 'e':
        uRotate = !uRotate;/**<  */
        //bRotate = false;
        axis_x=1.0;
        axis_y=0.0;

        break;
    case 'a':
        eyex-=2;
        centerx-=2;
        break;
    case 'd':
        eyex+=2;
        centerx+=2;
        break;
    case 'w':
        eyey+=2;
        centery+=2;
        break;
    case 's':
        eyey-=2;
        centery-=2;
        break;
    case 'f':
        eyez+=2;
        centerz+=2;
        //glutPostRedisplay();
        break;
    case 'g':
        eyez-=2;
        centerz-=2;
        //glutPostRedisplay();
        break;
    case 'b':
        bird_view();
        break;

    case 27:	// Escape key
        exit(1);
    }
}



void animate()
{
    if (bRotate == true)
    {
        theta += 1;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }

    if (uRotate == true)
    {
        alpha += 1;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }
    glutPostRedisplay();

}

static void idle(void)
{
    glutPostRedisplay();
}
int id= 1;
void LoadTexture(const char*filename)
{
    glGenTextures(1, &ID[id++]);
    glBindTexture(GL_TEXTURE_2D, ID[id-1]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID[id-1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}


int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    // glutInitWindowSize(900,900);
    //glutInitWindowPosition(10,10);
    glutInitWindowPosition(200,200);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Traingle-Demo");

    //LoadTexture("E:\\Code\\glut\\project_v1\\wall.bmp"); /// 1
    //LoadTexture("E:\\Code\\glut\\project_v1\\wall_2.bmp"); /// 2
//    LoadTexture("E:\\Code\\glut\\lab4\\lab4_asn_v3\\car_side_3.bmp"); /// 2
//    LoadTexture("E:\\Code\\glut\\lab4\\lab4_asn_v3\\car_side_2.bmp"); /// 3
//    LoadTexture("E:\\Code\\glut\\lab4\\lab4_asn_v3\\tree_wood.bmp"); /// 4
//    LoadTexture("E:\\Code\\glut\\lab4\\lab4_asn_v3\\glass.bmp"); /// 5
//    LoadTexture("E:\\Code\\glut\\lab4\\lab4_asn_v3\\car_side_4.bmp"); /// 6
//    LoadTexture("E:\\Code\\glut\\lab4\\lab4_asn_v3\\car_side_5.bmp"); /// 7


    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    //light0();
    //light1();
    glEnable( GL_DEPTH_TEST );
    glutKeyboardFunc(myKeyboardFunc);
    glutReshapeFunc(resize);
    glutDisplayFunc(display);

    glutIdleFunc(idle);
    glutIdleFunc(animate);
    glutMainLoop();

    return EXIT_SUCCESS;
}


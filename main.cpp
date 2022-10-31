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
double radius = 120;
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
bool st = 0;


double windowHeight=960, windowWidth=540;
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0;
GLboolean bRotate = false, uRotate = false;
double far_id =1000.0;
double near_id = 4.0;
GLuint ID[100], ID1;
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

        glVertex3fv(&cube_coordinate[pyramid_indices[i][0]][0]);
        glTexCoord2f(1,0);
        glVertex3fv(&cube_coordinate[pyramid_indices[i][1]][0]);
        glTexCoord2f(1,1);
        glVertex3fv(&cube_coordinate[pyramid_indices[i][2]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&cube_coordinate[pyramid_indices[i][3]][0]);
        glTexCoord2f(0,1);
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


        glVertex3fv(&cube_coordinate[cube_indices[i][0]][0]);
        glTexCoord2f(1,0);
        glVertex3fv(&cube_coordinate[cube_indices[i][1]][0]);
        glTexCoord2f(1,1);
        glVertex3fv(&cube_coordinate[cube_indices[i][2]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&cube_coordinate[cube_indices[i][3]][0]);
        glTexCoord2f(0,1);
    }
    glEnd();


}

static GLubyte c_pyramid_indices[6][4] =
{
    {0,3,2,1},
    {3,7,2,2},
    {7,4,1,2},
    {4,0,1,1},

    //{1,2,6,5},
    {7,4,0,3}


};

void draw_color_pyramid()
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
        getNormal3p(cube_coordinate[c_pyramid_indices[i][0]][0], cube_coordinate[c_pyramid_indices[i][0]][1], cube_coordinate[c_pyramid_indices[i][0]][2],
                    cube_coordinate[c_pyramid_indices[i][1]][0], cube_coordinate[c_pyramid_indices[i][1]][1], cube_coordinate[c_pyramid_indices[i][1]][2],
                    cube_coordinate[c_pyramid_indices[i][2]][0], cube_coordinate[c_pyramid_indices[i][2]][1], cube_coordinate[c_pyramid_indices[i][2]][2]);

        glVertex3fv(&cube_coordinate[c_pyramid_indices[i][0]][0]);
        glTexCoord2f(1,0);
        glVertex3fv(&cube_coordinate[c_pyramid_indices[i][1]][0]);
        glTexCoord2f(1,1);
        glVertex3fv(&cube_coordinate[c_pyramid_indices[i][2]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&cube_coordinate[c_pyramid_indices[i][3]][0]);
        glTexCoord2f(0,1);
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

#define gleT glEnable(GL_TEXTURE_2D);
#define glT(id) glBindTexture(GL_TEXTURE_2D, id);
#define gldT glDisable(GL_TEXTURE_2D);

void draw_floor(GLint id)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 0.5, .5, 0.5,1.0 };
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
    gt(-8000,0,8000);
    gs(8000,1,8000);
//    gleT;
//    glT(1);
//    draw_color_cube(1,1,1);
//    gldT;
    draw_floor(3);
    gpo;

    gpu;
    gt(0,0,-60);
    gr(90,0,0,1);
    gs(80,1,60);
    //draw_color_cube(1,0,1);
    draw_floor(6);
    gpo;


    gpu;
    gt(0,0,-160);
    gr(90,1,0,0);
    gs(80,1,80);
    //draw_color_cube(0,0,1);
    draw_floor(5);
    gpo;

    gpu;
    gt(160,0,-60);
    gr(90,0,0,1);
    gs(80,1,60);
    //draw_color_cube(1,0,1);
    draw_floor(6);
    gpo;

}

double ball_radius = 5;

void draw_ball(GLuint c1 = 3,GLuint c2 = 3,GLuint c3 = 1,double ball_radius = 5)
{
    gpu;
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { c1*0.2, c2*0.2, c3*0.2, 1.0 };
    GLfloat mat_diffuse[] = { c1*0.5, c2*0.5, c3*0.5,1.0 };
    GLfloat mat_specular[] = { c1, c2, c3, 1.0 };
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
inline int dcmp (double x)
{
    if (fabs(x) < eps)
        return 0;
    else
        return x < 0 ? -1 : 1;
}
inline double torad(double deg)
{
    return deg / 180 * pi;
}

struct Point3D
{
    double x, y, z;
    Point3D() {}
    void read ()
    {
        cin>>x>>y>>z;
    }
    void write ()
    {
        cout<<x<<" --- "<<y<<" --- "<<z<<"\n";
    }

    Point3D(double x, double y, double z) : x(x), y(y), z(z) {}
    Point3D(const Point3D &p) : x(p.x), y(p.y), z(p.z) {}
    Point3D operator +(Point3D b)
    {
        return Point3D(x+b.x,y+b.y, z+b.z);
    }
    Point3D operator -(Point3D b)
    {
        return Point3D(x-b.x,y-b.y, z-b.z);
    }
    Point3D operator *(double b)
    {
        return Point3D(x*b,y*b, z*b);
    }
    Point3D operator /(double b)
    {
        return Point3D(x/b,y/b, z/b);
    }
    bool operator  <(Point3D b)
    {
        return make_pair(make_pair(x,y),z) < make_pair(make_pair(b.x,b.y),b.z);
    }
    bool operator ==(Point3D b)
    {
        return dcmp(x-b.x)==0 && dcmp(y-b.y) == 0 && dcmp(z-b.z) == 0;
    }
};
vector<Point3D>Ball;
typedef Point3D Vector3D;

namespace Vectorial
{
    double getDot (Vector3D a, Vector3D b)
    {
        return a.x*b.x+a.y*b.y+a.z*b.z;
    }
    Vector3D getCross(Vector3D a, Vector3D b)
    {
        return Point3D(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x);
    }
    double getLength (Vector3D a)
    {
        return sqrt(getDot(a, a));
    }
    double getPLength (Vector3D a)
    {
        return getDot(a, a);
    }
    Vector3D unitVector(Vector3D v)
    {
        return v/getLength(v);
    }

    double getUnsignedAngle(Vector3D u,Vector3D v)
    {
        double cosTheta = getDot(u,v)/getLength(u)/getLength(v);
        cosTheta = max(-1.0,min(1.0,cosTheta));
        return acos(cosTheta);
    }

    Vector3D rotate(Vector3D a,Vector3D v,double deg)  // rotate a around v with degree of deg
    {
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

    Vector3D s,c,b;
    s.x = eyex;
    s.y = eyey;
    s.z = eyez;

    c.x = centerx;
    c.y = centery;
    c.z = centerz;

    while(Ball.size()<5)
    {
        int dx = 40+rng()%80;
        int dy= 20+rng()%80;
        int dz = -40+rng()%40;
        Point3D b;
        b.x = dx;
        b.y = dy;
        b.z = dz;
        bool f=0;

        for(int i=0; i<Ball.size(); i++)
        {
            dx= 40+rng()%80;
            dy = 20+rng()%80;
            dz = -40+rng()%20;
            b.x = dx;
            b.y = dy;
            b.z = dz;


            double d  = getLength(b-Ball[i]);
            double p = getLength(s-c);
            double q = getLength(s-b);
            double r = getLength(b-c);
            double s1 = (p+q+r)/2;
            double h1 = (2*sqrt(s1*(s1-p)*(s1-q)*(s1-r)))/p;

            ///p = getLength(s-c);
            q = getLength(s-Ball[i]);
            r = getLength(Ball[i]-c);
            double s2 = (p+q+r)/2;
            double h2 = (2*sqrt(s2*(s2-p)*(s2-q)*(s2-r)))/p;


            cout<<h1<<" "<<h2<<endl;
            if(d>20 )
            {
                f=1;
                break;
            }
        }
        //if(f)
        Ball.push_back(b);
    }

    for(int i=0; i<Ball.size(); i++)
    {

        gpu;
        gt(Ball[i].x, Ball[i].y, Ball[i].z);
        draw_ball();
        gpo;
    }




}


int points = 0;

void Sprint( int posx, int posy,int posz,int space_char, string st)
{
    int l,i, j=0;

    GLvoid *font_style1 = GLUT_BITMAP_TIMES_ROMAN_24;

    for(int i=0;i<st.size();i++)
    {
        glRasterPos3f ((posx+(j*space_char)),posy, posz);
        glutBitmapCharacter(font_style1,st[i]);
        j++;
    }
}


void draw_score_text()
{
    string s=to_string(points);


    int len = s.size();
    for (int i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, s[i]);
    }
}


void scoredisplay (int posx, int posy, int posz, int space_char, int scorevar, string s)
{
    int j=0,p,k;
    GLvoid *font_style1 = GLUT_BITMAP_TIMES_ROMAN_24;

    string sc = to_string(scorevar);

    p = scorevar;
    j = 0;
    k = 0;



//    glRasterPos3f ((posx-(j*space_char)), posy, posz);
//    glutBitmapCharacter(font_style1,48+p);

    for(int i=0;i<s.size();i++)
    {
        glRasterPos3f ((posx+(j*space_char)),posy, posz);
        glutBitmapCharacter(font_style1,s[i]);
        j++;
    }

     for(int i=0;i<sc.size();i++)
    {
        //k = p % 10;
        glRasterPos3f ((posx+(j*space_char)),posy, posz);
        glutBitmapCharacter(font_style1,sc[i]);
        j++;
       // p /= 10;
    }
//    glRasterPos3f ((posx-(j*space_char)), posy, posz);
//    glutBitmapCharacter(font_style1,48+p);



}

bool show_score = 1;

void draw_score()
{
    gpu;
    gt(10,148,-90);
    gs(70,12,2);
    draw_color_cube(0.55,0.47,0.33);
    gpo;

    if(show_score==0)
    {
        return;
    }

    gpu;
    //gt(20,150,-50);
    //gs(50,10,2);
    //glColor3f(1,1,1);
    gt(0.5,-0.5,0);
    draw_color_cube(0.5,1,0);
    gt(-0.5,.5,0);
    string p = " Score: ";
    // Sprint(40,110,p);
    scoredisplay(20,152,-85,5,points, p);
    //draw_score_text();
    //draw_color_cube(1,1,1);
    gpo;

}

void draw_gun()
{

    gpu;

    gs(1,1,0.5);

    // gt(10,10,0);
    gpu;
    gs(0.5,4,30);
    gleT;
    glT(10);
    draw_cube();
    //draw_color_cube(0,0,1);
    gldT;
    gpo;

    gpu;
    gt(-0.25,-5,5);
    gs(0.75,4,20);
    gleT;
    glT(10);
    draw_cube();
    //draw_color_cube(0,1,1);
    gldT;
    gpo;

    gpu;
    gt(-.5,-7,2.5);
    gs(0.95,5,15);
    gleT;
    glT(11);
    draw_cube();
    //draw_color_cube(0.4,0.4,0.4);
    gldT;
    gpo;

    gpu;
    gt(-.75,-14,3);
    gs(1,10,2);
    gleT;
    glT(11);
    draw_cube();
    //draw_color_cube(1,1,0.2);
    gldT;
    gpo;

    gpo;
}

double sq(double x1, double y1, double x2, double y2)
{
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

double Pi = acos(-1);

double angle_cal(double x1, double y1, double x2, double y2, double x3, double y3 )
{
//    double p12 = sq(x1,y1,x2,y2);
//    double p13 = sq(x1,y1,x3,y3);
//    double p23 = sq(x2,y2,x3,y3);
//
//    double ap = p12*p12 - p13*p13 + p23*p23;
//    double bp = 2*p12*p23;
//
//    if(bp==0) return 0;
//
//    return acos(ap/bp);



    double result = atan2(y3 - y1, x3 - x1) -
                    atan2(y2 - y1, x2 - x1);

    return result*180/Pi;

}

double gun_point_x = eyex;
double gun_point_y = eyey-20;
double gun_point_z = centerz;

void change()
{
    gun_point_x = eyex;
    gun_point_y = eyey-20;
    gun_point_z = centerz;

}
bool gun_show = 1;
double gun_angle = 0;

int bv = 0;
void draw_gun_at_eye()
{
    double new_gun_point_x = centerx;
    double new_gun_point_y = centery;
    double new_gun_point_z = centerz;

    double mid_x = eyex+15;
    double mid_y = eyey-15;
    double mid_z = eyez-2;

    //double ang = angle_cal(gun_point_x, gun_point_y,mid_x,mid_y,new_gun_point_x,new_gun_point_y);

    double angx = angle_cal(gun_point_x,gun_point_z,mid_x, mid_z,new_gun_point_x,new_gun_point_z);
    double angy = angle_cal(gun_point_y,gun_point_z,mid_y, mid_z,new_gun_point_y,new_gun_point_z);

    double dx = ((float) (((float)gun_point_x) - new_gun_point_x)); // how far moved x
    double dy = ((float) (((float)gun_point_y) - new_gun_point_y)); // how fa moved y

    angx = atan2(dx,mid_z)*180/Pi;
    angy = atan2(dy,mid_z)*180/Pi;

    // cout<<angx<<" "<<angy<<endl;
//
//    //gun_point_x = centerx;
//    //gun_point_y = centery;
//


    //angx/=10;
    //angy/=10;

    if(bv!=0&& !gun_show)
    {
        gt(80,60,80);
    }
    else
        gt(mid_x,mid_y,mid_z);

    gr(gun_angle,1,0,0);
    gr(angx, 0,1,0);
    gr(-angy, 1,0,0);
    //gr(15,0,1,0);
    draw_gun();

}


void draw_sky()
{


    glPushMatrix();

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.0039, .1961, 0.12, 1.0 };
    GLfloat mat_diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {40};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

//    glEnable(GL_TEXTURE_2D);
//    glEnable(GL_TEXTURE_GEN_S);
//    glEnable(GL_TEXTURE_GEN_T);
//    glBindTexture(GL_TEXTURE_2D, 2);



    //glutSolidSphere(1000,1000,1000);
    draw_ball(0.4,0.4,1,700);



//     glDisable(GL_TEXTURE_GEN_S);
//    glDisable(GL_TEXTURE_GEN_T);
//
//    glDisable(GL_TEXTURE_2D);


    glPopMatrix();


}


void draw_sp()
{
    glTranslatef(150,-30,-10);
    glScalef(0.5,0.5,0.5);

    // cout<<" kn "<<endl;



    glPushMatrix();

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.1, .1, 0.1, 1.0 };
    GLfloat mat_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {40};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glBindTexture(GL_TEXTURE_2D, 1);

    glPushMatrix();
    glTranslatef(0, 0.0, 0.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(15, 3.0, 0.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(30, 0.0, 0.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(30, 1.0, 5.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(25, 10.0, 0.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(25, 10.0, 5.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(20, 10.0, 0.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(20, 11.0, 5.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5, 10.0, 0.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5, 10.0, 5.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(20, 20.0, 0.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();

    glPushMatrix();

    glTranslatef(0,5,10);

    glPushMatrix();
    glTranslatef(0, 0.0, 0.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(15, 0.0, 0.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(30, 0.0, 0.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(30, 0.0, 5.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(25, 10.0, 0.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(25, 10.0, 5.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(20, 10.0, 0.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(20, 10.0, 5.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5, 10.0, 0.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5, 10.0, 5.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(20, 20.0, 0.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();

    glPopMatrix();


//    for(double i=60; i>=0; i-=2)
//    {
//        for(double j = 0; j<i; j+=5)
//        {
//
//            for(double k=0; k<j; k+=7)
//            {
//
//                glPushMatrix();
//                glTranslatef(i, -j, k);
//                glutSolidSphere(10.0, 50, 50);
//                glPopMatrix();
//            }
//        }
//    }

    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);

    glDisable(GL_TEXTURE_2D);


    glPopMatrix();

}

void draw_tree()
{

    glTranslatef(10,-20,-80);
    glScalef(1.5,1.5,1.5);
    glScalef(2.5,3.5,2.5);

    glPushMatrix();
    glTranslatef(-100,50,0);
    draw_sp();
    glPopMatrix();

    glPushMatrix();

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { .5, .5, 0.5, 1.0 };
    GLfloat mat_specular[] = { 1, 1, 1, 1.0 };
    GLfloat mat_shininess[] = {30};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glTranslatef(56,4,-4);
    glScalef(2, 10, 2);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 12);
    draw_cube();
    //draw_color_cube(0,1,1);
    glDisable(GL_TEXTURE_2D );
    glPopMatrix();
}



void draw_wheel (GLfloat c1,GLfloat c2,GLfloat c3, GLfloat radi )
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.3*c1, 0.3*c2, 0.3*c3, 1.0 };
    GLfloat mat_diffuse[] = { c1, c2, c3, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {40};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    double circle_radius = radi;

    glBegin(GL_LINES);
//    glColor3f(1,0,0);
    for(int i=0; i<1000; ++i)
    {
        glVertex2f(0,0);
        glVertex2f(circle_radius*cos(2*3.14159*i/1000.0),circle_radius*sin(2*3.14159*i/1000.0));
    }
    glEnd();

    glBegin(GL_LINES);
//    glColor3f(1,0,0);
    for(int i=0; i<1000; ++i)
    {
        //glVertex2f(0,0);
        glVertex3f(circle_radius*cos(2*3.14159*i/1000.0),circle_radius*sin(2*3.14159*i/1000.0), 0);
        glVertex3f(circle_radius*cos(2*3.14159*i/1000.0),circle_radius*sin(2*3.14159*i/1000.0), 3);
    }
    glEnd();

    glTranslatef(0,0,radi);

    glBegin(GL_LINES);
//    glColor3f(1,0,0);
    for(int i=0; i<1000; ++i)
    {
        glVertex2f(0,0);
        glVertex2f(circle_radius*cos(2*3.14159*i/1000.0),circle_radius*sin(2*3.14159*i/1000.0));
    }
    glEnd();

}

double car_x = 0;

void draw_car()
{
    gpu;
    // glTranslatef(car_x, 0, 0);
    glTranslatef(-20,0,10);
    gs(1,2.5,1);
    // glTranslatef(-70,0,0);

    ///body
    glPushMatrix();
    glScalef(1.2,1.4,2);
    glTranslatef(0,0,-40);


    glPushMatrix();
    glTranslatef(11.5,1,60);
    //glRotatef(90,0,0,1);
    glScalef(15.5, 1.7, 4);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 7);
    draw_cube();
    glDisable(GL_TEXTURE_2D);
    //draw_color_cube(1,0,0);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(16,4,60);
    //glRotatef(90,0,0,1);
    glScalef(6, 2, 4);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 8);
    draw_cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(28,4,52.5);
    glRotatef(-90,0,1,0);
    //glRotatef(90,0,1,0);
    glScalef(3.5, 2, 4);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 9);
    draw_color_pyramid();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(28,4,52);
    glRotatef(-90,0,1,0);
    //glRotatef(90,0,1,0);
    glScalef(4, 1.5, 7.3);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 7);
    draw_color_pyramid();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(16,4,60);
    glRotatef(-270,0,1,0);
    //glRotatef(90,0,1,0);
    glScalef(4, 2, 2);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 8);
    draw_color_pyramid();
    glDisable(GL_TEXTURE_2D);
    //draw_color_pyramid();
    glPopMatrix();
    glPopMatrix();



    ///wheel
    glPushMatrix();
    glTranslatef(20,0,38.5);
    draw_wheel(0.1,0.1,0.1, 2.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(44,0,38.5);
    draw_wheel(0.1,0.1,0.1, 2.5);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0,0,-16.5);
    glTranslatef(20,0,38.5);
    draw_wheel(0.1,0.1,0.1, 2.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,-16.5);
    glTranslatef(44,0,38.5);
    draw_wheel(0.1,0.1,0.1, 2.5);
    glPopMatrix();
    gpo;
}

void draw_cloud()
{
    gpu;
    gt(0,400,-200);
    glColor3f(1,1,1);
    draw_sp();
    gpo;


}


void draw_fan_stand()
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat mat_diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {40};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);


    glTranslatef(-2,-5,0);
    glScalef(2, 25, 2);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 12);
    draw_cube();
    //draw_color_cube(0,1,1);
    glDisable(GL_TEXTURE_2D );


}

void draw_triangle()
{
    glBegin(GL_TRIANGLES);
    glVertex2f(0,0);
    glVertex2f(5,-8);
    glVertex2f(5,8);
    glEnd();

}


void draw_fan()
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { .53, 0.53, 0.53, 1.0 };
    GLfloat mat_specular[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat mat_shininess[] = {40};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);



    glPushMatrix();
    glTranslatef(0,0,0);
    glScalef(5, 0.8, 2);
    draw_triangle();
    glPopMatrix();

    glPushMatrix();
    //glTranslatef(0,0,0);
    glRotatef(-90,0,0,1);
    glScalef(5, 0.8, 2);
    draw_triangle();
    glPopMatrix();
//
    glPushMatrix();
    // glTranslatef(24,44,0);
    glRotatef(180,0,0,1);
    glScalef(5, 0.8, 2);
    draw_triangle();
    glPopMatrix();
//
//
    glPushMatrix();

    // glTranslatef(6,18,0);
    glRotatef(90,0,0,1);
    glScalef(5, 0.8, 2);
    draw_triangle();
    glPopMatrix();

    glPushMatrix();

    glTranslatef(-2,-2,0);
    //glRotatef(90,0,0,1);
    glScalef(2, 2, 1);
    draw_cube();
    glPopMatrix();


}


double ftheta = 0;
bool frotate=1;

void draw_windmill()
{


    //glutSolidSphere (10.0, 20, 26);

    gpu;

    gt(-100,0,-100);

    gs(1,2,1);
    gr(40,0,1,0);

    glPushMatrix();
    gt(0,8,0);
    gs(1,1.5,1);
    draw_fan_stand();
    glPopMatrix();

    glPushMatrix();
//    glTranslatef();
    glTranslatef(0,60,0);
    glRotatef(ftheta, 0, 0, 1);
    glTranslatef(0,-60,0);
    glPushMatrix();
    glTranslatef(0,60,2);
    draw_fan();
    glPopMatrix();
    glPopMatrix();

    gpo;


}

void draw_garbage()
{
    gpu;
    gt(10,2,60);
    gs(8,4,8);
    gr(20,0,1,0);

    //draw_cube();
    draw_floor(13);
    //draw_color_cube(1,0,0);
    gpo;
    gpu;
    gt(18,10,65);
    gs(8,4,8);
    gr(50,0,1,0);
    draw_floor(14);
    //draw_color_cube(1,1,0);
    gpo;

}


void draw_many_garbage()
{
    gpu;
    gt(-80,0,-200);
    gs(2,2,2);
    draw_garbage();
    gpo;
    gpu;
    gt(-180,0,-170);
    gs(1.5,1.5,1.5);
    draw_garbage();
    gpo;

    gpu;
    gt(40,0,-220);
    gs(1.5,1.5,1.5);
    draw_garbage();
    gpo;
    gpu;
    gt(10,0,-220);
    gs(1,1,1);
    draw_garbage();
    gpo;
    gpu;
    gt(140,0,-100);
    gs(1.5,1.5,1.5);
    draw_garbage();
    gpo;



    gpu;
    gt(200,0,-160);
    draw_garbage();
    gpo;
    gpu;
    gt(220,0,-180);
    gs(2,2,2);
    draw_garbage();
    gpo;

}




void draw_every()
{
    draw_room();
    draw_pointer();
    draw_many_balls();
    gpu;
//    if(gun_show)
//        gt(eyex-20,-20,eyez-5);
//    else{
//        gt(80-20,60+5,80-5);
//    }
    draw_score();
    gpo;

    //gt(20,20,20);
    //if(gun_show)
    glPushMatrix();
    draw_gun_at_eye();
    glPopMatrix();

    glPushMatrix();
    // glTranslatef(100,0,0);
    draw_tree();

    glPopMatrix();

    draw_sky();

    gpu;
    gt(-80,10,-200);
    gr(-100,0,1,0);
    gs(2,2.5,2);
    draw_car();
    gpo;

//    gpu;
//    draw_garbage();
//    gpo;



    gpu;
    draw_many_garbage();
    gpo;

     gpu;
    draw_windmill();
    gpo;

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

void light1()
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.5, 0.5, 0.5, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat light_position[] = { 50.0, 0.0, 0.0, 1.0 };
    GLfloat light_position[] = { 8, -4, -55.0, 1.0 };

    if(light_switch1)
        glEnable( GL_LIGHT1);
    else
        glDisable(GL_LIGHT1);
    glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT1, GL_POSITION, light_position);

    /*  GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
      glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
      glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 10.0); */
}

void light2()
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_spot[] = {-1.0,-1.0,0};
    GLfloat light_position[] = { -1.0,300.0,10.0, 1.0 };
//    GLfloat light_position[] = { 8, -4, -55.0, 1.0 };


    if(light_switch2)
        glEnable( GL_LIGHT2);
    else
        glDisable(GL_LIGHT2);
    glLightf( GL_LIGHT2, GL_SPOT_CUTOFF, 45.0);
    glLightf( GL_LIGHT2, GL_SPOT_EXPONENT, 2.0);
    glLightfv( GL_LIGHT2, GL_SPOT_DIRECTION, light_spot);
    glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT2, GL_POSITION, light_position);




    /*  GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
      glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
      glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 10.0); */
}



#include <chrono>
#include <ctime>
auto start = std::chrono::system_clock::now();



void mouse( int button, int state, int xpos, int ypos)
{
//    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
//    {
    if(st==0) return;

    Vector3D s,c,b;
    s.x = eyex;
    s.y = eyey;
    s.z = eyez;

    c.x = centerx;
    c.y = centery;
    c.z = centerz;

    for(int i=0; i<Ball.size(); i++)
    {
        b = Ball[i];
        double p,q,r;

        p = getLength(s-c);
        q = getLength(s-b);
        r = getLength(b-c);
        double s1 = (p+q+r)/2;
        double h = (2*sqrt(s1*(s1-p)*(s1-q)*(s1-r)))/p;

        if(fabs(ball_radius-h)<=(ball_radius))
        {
            Ball.erase(Ball.begin()+i);
            points++;
            break;
        }
        // cout<<(ball_radius-h)<<" ";
    }
    //cout<<endl;

    start = std::chrono::system_clock::now();
    gun_angle = 15;







    //  cout<<ini_x<<" "<<ini_y<<" "<endl;

    //  cout << "Cursor Position at :" << xpos << " : " << ypos <<" "<< centerx<<" "<<centery<<endl;
    // }
}

/*

arccos((P122 + P132 - P232) / (2 * P12 * P13))

where P12 is the length of the segment from P1 to P2, calculated by

sqrt((P1x - P2x)2 + (P1y - P2y)2)

*/




int last_x = ini_x, last_y=ini_y;
double sign = 1;



void mouseMove(int mx, int my)
{
    if(st==0) return;

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

double limit = 360;
double roll_value = 5;
GLfloat angleYaw = 90.0, anglePitch = 90.0, angleRoll = 90.0;
GLfloat angleYawLimit1 = 180.0, anglePitchLimit1 = 180.0, angleRollLimit1 = 270.0;
GLfloat angleYawLimit2 = 0.0, anglePitchLimit2 = 0.0, angleRollLimit2 = -90.0;

int ff = 0;
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
        bv=2;
        glutPostRedisplay();

    }
    else
    {


    }
}

void init(int d)
{
    if(d!=ff)
    {
        angleYaw = 90.0;
        anglePitch = 270.0;
        angleRoll = 90.0;
       // radius = 120;
        eyex = 80;
        eyey = 60;
        eyez = radius;
        centerx = 80;
        centery = 60;
        centerz = 0;
        upx = 0;
        upy = 1;
        upz = 0;
        ff=d;
        theta = 0;
        alpha = 0;
        bv=0;
        //scale_x=1.5;
        //scale_y=1.5;
        //scale_z=1.5;

    }
    b_swap();
}

int mode = 0;

auto game_start = std::chrono::system_clock::now();



void choose_board()
{
//    gpu;
//    gt(eyex-2,eyey-2,eyez-5);
//    gs(2,2,1);
//
//    draw_color_cube(0.5,0.5,0.5);
//    gpo;


    gt(-1000,0,0);
    draw_color_cube(1,1,1);
    gt(1000,0,0);

    gpu;

    //gt(eyex-2,eyey-2,eyez-4);

    glColor3f(1,0,0);
    init(5);
    Sprint(40, 65,4,5,"Play Game : 'S' ");
    Sprint(40, 50,4,5,"Exit : 'Esc' ");
//
    //display_text(0.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "PLay Game: 'S' ", RGB(1.0f, 0.0f, 0.0f));
    //display_text("Play Game:> 'S'");
    gpo;



}


int hs = 0;
void game_over_board()
{

    gpu;

    //gt(eyex-2,eyey-2,eyez-4);

    gt(-1000,0,0);
    draw_color_cube(1,0,0);
    gt(1000,0,0);

    int p = points;

    string q = to_string(p);

    double x = windowHeight / 2;
    double y = windowWidth / 2;

    //init(5);



    Sprint(40, 100,4,5,"Game Over");
    gt(-1000,0,0);
    draw_color_cube(1,1,1);
    gt(1000,0,0);
    Sprint(40, 60,4,5,"Score: "+q);
    q = to_string(hs);
    Sprint(40, 45,4,5,"Highest Score: "+hs);
    Sprint(40, 30,4,5,"Play Game : 'S' ");
    Sprint(40, 15,4,5,"Exit : 'Esc' ");
//
    //display_text(0.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "PLay Game: 'S' ", RGB(1.0f, 0.0f, 0.0f));
    //display_text("Play Game:> 'S'");
    gpo;



}

int count_time = 100;

void show_time(double t)
{
    t = 20 - floor(t/1000);
    int p  = t;
    count_time = t;
    cout<<p<<endl;

    gpu;

    gt(0.5,-0.5,0);
    draw_color_cube(0.5,1,0);
    gt(-0.5,.5,0);
    //Sprint(50, 150,"Score:");
    //Sprint(80,110,"Time :");
    scoredisplay(80,152,-85,6,p, " Seconds:");

    gpo;

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
    light1();
    light2();



    glRotatef( alpha,axis_x, axis_y, 0.0 );
    glRotatef( theta, axis_x, axis_y, 0.0 );

    glutMouseFunc(mouse);
    glutPassiveMotionFunc(mouseMove);


    //cout<<"mode "<<mode<<endl;

//    gpu;
//    //gs(2,5,5);
//    //gt(-80,0,0);
//    draw_every();
//    gpo;

    if(mode==0)
    {
        gpu;
        //game_over_board();
        choose_board();
        gpo;
    }
    else if(mode==1)
    {
        if(st==0)
        {

            st=1;
            game_start = std::chrono::system_clock::now();
            points = 0;

        }


        gpu;
        //gs(2,5,5);
        //gt(-80,0,0);
        draw_every();
        gpo;
        //points = 1234;
       // mode = 3;
    }
    else if(mode==3){
        st=0;
        init(6);

        gpu;
        game_over_board();
        gpo;
    }




    auto end_ = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end_-start;
    //std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    double t= elapsed_seconds.count()*1000;
    // cout<<"timee  "<<t<<endl;
    if(t>=50.0)
    {
        gun_angle = 0;
    }

    std::chrono::duration<double> elapsed_seconds_ = end_-game_start;
    //std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    double tg= elapsed_seconds_.count()*1000;

    if(st==1 && mode==1)
    show_time(tg);

    // cout<<"timee  "<<tg<<endl;
    if(tg>=20000.0 && mode==1)
    {
        init(6);

        //    cout<<"done  "<<tg<<endl;
        mode= 3;
        //   glutPostRedisplay();

    }


    glFlush();
    glutSwapBuffers();


}






void setCameraEye_Yaw() /// y axis , y u
{
    init(1);
    ff=1;
    centerx = eyex+radius*(cos(angleYaw*3.1416/180.0));
    centerz = eyez+radius*(sin(angleYaw*3.1416/180.0));
}

void setCameraEye_Roll() // z axis ,i o
{
    //init(2);
    //f=2;
    centery = 20;
    eyey=  20;;

    upx = (cos(angleRoll*3.1416/180.0));
    upy = (sin(angleRoll*3.1416/180.0));

}

void setCameraEye_Pitch() // x axis , r t
{
    init(3);
    ff=3;

    centery = eyey+radius*(cos(anglePitch*3.1416/180.0));
    centerz = eyez+radius*(sin(anglePitch*3.1416/180.0));
}

void normal_view()
{

    bv = 0;
    cout<<" normal view "<<endl;
    gun_show = 1;
    init(5);

}

void bird_view()
{
//     init(6);
//     f=6;
    bv = 1;
    cout<<" bird view "<<endl;
    gun_show = 0;
    b_swap();

}


void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 'r':
//        if(anglePitch>=anglePitchLimit1)
//                break;
        anglePitch += roll_value;

        //printf("%lf  p\n ", anglePitch);
        //if(anglePitch > limit)
        //    anglePitch -= limit;
        setCameraEye_Pitch();
        glutPostRedisplay();

        // eyex = eyex;

        break;
    case 't':
//        if(anglePitch<=anglePitchLimit2)
//                break;
        anglePitch -= roll_value;
        //if(anglePitch < 0)
        //   anglePitch += limit;
        setCameraEye_Pitch();
        glutPostRedisplay();
        break;
    case 'y':
//        if(angleYaw==angleYawLimit1)
//            break;
        angleYaw += roll_value;
        //if(angleYaw > limit)
        //    angleYaw -= limit;
        setCameraEye_Yaw();
        //setCameraEye_Yaw();
        glutPostRedisplay();

        // eyex = eyex;
        break;
    case 'u':
//        if(angleYaw==angleYawLimit2)
//            break;
        angleYaw -= roll_value;
        //if(angleYaw < 0)
        //   angleYaw += limit;
        setCameraEye_Yaw();
        //setCameraEye_Yaw();
        glutPostRedisplay();
        break;
    case 'i':
        //if(angleRoll>=angleRollLimit1)
        //   break;
        angleRoll += roll_value;
        //if(angleRoll >= limit)
        //    angleRoll -= limit;
        printf("%lf\n", angleRoll);
        setCameraEye_Roll();
        //setCameraEye_Yaw();
        glutPostRedisplay();

        // eyex = eyex;
        break;
    case 'o':
        //if(angleRoll<=angleRollLimit2)
        //   break;
        angleRoll -= roll_value;
        //if(angleRoll < 0)
        //    angleRoll += limit;
        setCameraEye_Roll();
        //setCameraEye_Yaw();
        glutPostRedisplay();
        break;
    case 'S':
        //if(mode==0){
        mode=1;
        game_start = std::chrono::system_clock::now();
        //}
        break;
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
        change();
        break;
//    case 'j':
//        light_switch0^=1;
////        eyex-=2;
////        centerx-=2;
//        break;

    case 'd':
        eyex+=5;
        centerx+=5;
        change();
        break;
    case 'w':
        eyey+=5;
        centery+=5;
        change();
        break;
    case 's':
        eyey-=5;
        centery-=5;
        change();
        break;
    case 'f':
        eyez+=5;
        centerz+=5;
        change();
        //glutPostRedisplay();
        break;
    case 'g':
        eyez-=5;
        centerz-=5;
        change();
        //glutPostRedisplay();
        break;
    case 'b':
        show_score=!show_score;

        bird_view();
        break;
    case 'n':
        normal_view();
        break;
    case 'l':
        light_switch0=!light_switch0;
        //light0();
        glutPostRedisplay();
        break;
    case 'k':
        light_switch1=!light_switch1;
        //light1();
        glutPostRedisplay();
        break;
    case ';':
        light_switch2=!light_switch2;
        //light1();
        glutPostRedisplay();
        break;
    case 'j':
        frotate = !frotate;
        // uRotate = false;
        //axis_x=0.0;
        //axis_y=1.0;

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

    if (frotate == true)
    {
        ftheta += 1;
        // if(ftheta > 360.0)
        //   ftheta -= 360.0*floor(ftheta/360.0);
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
    glGenTextures(1, &ID[id]);
    glBindTexture(GL_TEXTURE_2D, ID[id]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID[id]);
    id++;
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
    glutCreateWindow("AimLab");

    LoadTexture("E:\\Code\\glut\\project_v1\\tree_leaf.bmp");       /// 1
    LoadTexture("E:\\Code\\glut\\project_v1\\wood2.bmp");       /// 2

    LoadTexture("E:\\Code\\glut\\project_v1\\floor3.bmp");      /// 3
    LoadTexture("E:\\Code\\glut\\project_v1\\floor1.bmp");     /// 4


    LoadTexture("E:\\Code\\glut\\project_v1\\wall2.bmp"); /// 5
    LoadTexture("E:\\Code\\glut\\project_v1\\wall3.bmp"); /// 6

    LoadTexture("E:\\Code\\glut\\project_v1\\car2.bmp");  /// 7
    LoadTexture("E:\\Code\\glut\\project_v1\\car_side_2.bmp");  /// 8
    //LoadTexture("E:\\Code\\glut\\project_v1\\car_side_4.bmp"); /// 9
    //LoadTexture("E:\\Code\\glut\\project_v1\\car_side_5.bmp"); /// 10
    LoadTexture("E:\\Code\\glut\\project_v1\\glass.bmp");   ///9


    LoadTexture("E:\\Code\\glut\\project_v1\\gun.bmp");  /// 10
    LoadTexture("E:\\Code\\glut\\project_v1\\gun_barrel.bmp"); /// 11
    LoadTexture("E:\\Code\\glut\\project_v1\\tree_wood.bmp"); ///12

    LoadTexture("E:\\Code\\glut\\project_v1\\box1.bmp"); /// 13
    LoadTexture("E:\\Code\\glut\\project_v1\\box2.bmp"); ///14

    //LoadTexture("E:\\Code\\glut\\project_v1\\gun2.bmp"); /// 12
    //LoadTexture("E:\\Code\\glut\\project_v1\\tree_wood.bmp");      cout<<"tree_wood"<<endl; /// 4


    // LoadTexture("E:\\Code\\glut\\project_v1\\wood2.bmp");     /// 5
    //LoadTexture("E:\\Code\\glut\\project_v1\\sky.bmp");     cout<<"sky"<<endl; /// 2

    //LoadTexture("E:\\Code\\glut\\project_v1\\floor3.bmp");     cout<<"floor3"<<endl; /// 7
    //LoadTexture("E:\\Code\\glut\\project_v1\\floor1.bmp");     cout<<"floor1"<<endl; /// 8


    //LoadTexture("E:\\Code\\glut\\project_v1\\tree_wood.bmp");      cout<<"tree_wood"<<endl; /// 4
    //LoadTexture("E:\\Code\\glut\\project_v1\\glass.bmp");      cout<<"glass"<<endl; /// 5
    //LoadTexture("E:\\Code\\glut\\project_v1\\car_side_4.bmp");     cout<<"car_side_4"<<endl; /// 6
    //LoadTexture("E:\\Code\\glut\\project_v1\\car_side_5.bmp");     cout<<"car_side_5"<<endl; /// 7
    //LoadTexture("E:\\Code\\glut\\project_v1\\leaf.bmp");      cout<<"leaf"<<endl; /// 8
    //LoadTexture("E:\\Code\\glut\\project_v1\\floor3.bmp");     cout<<"floor3"<<endl; /// 9
    //LoadTexture("E:\\Code\\glut\\project_v1\\floor2.bmp");     cout<<"floor2"<<endl; /// 10
    //LoadTexture("E:\\Code\\glut\\project_v1\\sky.bmp");     cout<<"sky"<<endl; /// 8
    // LoadTexture("E:\\Code\\glut\\project_v1\\wall2.bmp");     cout<<"wall2"<<endl; /// 9
    // LoadTexture("E:\\Code\\glut\\project_v1\\wall3.bmp");     cout<<"wall3"<<endl; /// 10


    //LoadTexture("E:\\Code\\glut\\project_v1\\wall.bmp"); /// 12
    // LoadTexture("E:\\Code\\glut\\project_v1\\wall_2.bmp"); /// 13


    //LoadTexture("E:\\Code\\glut\\project_v1\\gun.bmp"); /// 9
    //LoadTexture("E:\\Code\\glut\\project_v1\\gun2.bmp"); /// 10
    //LoadTexture("E:\\Code\\glut\\project_v1\\gun_barrel.bmp"); /// 11
//
    // LoadTexture("E:\\Code\\glut\\project_v1\\wall.bmp"); /// 12
    // LoadTexture("E:\\Code\\glut\\project_v1\\wall_2.bmp"); /// 13
//    LoadTexture("E:\\Code\\glut\\project_v1\\gun.bmp"); /// 3
//    LoadTexture("E:\\Code\\glut\\project_v1\\gun2.bmp"); /// 4
//    LoadTexture("E:\\Code\\glut\\project_v1\\gun_barrel.bmp"); /// 5
//    LoadTexture("E:\\Code\\glut\\lab4\\lab4_asn_v3\\car_side_3.bmp"); /// 2
//    LoadTexture("E:\\Code\\glut\\lab4\\lab4_asn_v3\\car_side_2.bmp"); /// 3
//    LoadTexture("E:\\Code\\glut\\lab4\\lab4_asn_v3\\tree_wood.bmp"); /// 4
//     LoadTexture("E:\\Code\\glut\\project_v1\\grass.bmp"); /// 5
//     LoadTexture("E:\\Code\\glut\\project_v1\\sky.bmp"); /// 5
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


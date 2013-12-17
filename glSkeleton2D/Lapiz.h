//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef LapizH
#define LapizH

#include <gl\gl.h>
#include <gl\glu.h>
#include<math.h>
#define PI 3.14159265
#include "PV2D.h"

//--------------------------------------------------------------------------

class Lapiz
{
   private:

        PV2D* pos;     //PV2D
        GLdouble dir;   //angulo en radianes
   public:

        Lapiz(){ pos = new PV2D (0,0);dir = 0; };
        Lapiz(PV2D* p, GLdouble d){ pos = new PV2D(0,0);pos->setCoor(p->getX(), p->getY()); dir = d; }
        ~Lapiz(){ delete pos; };

        void moveTo(PV2D* p){ pos->setCoor(p->getX(), p->getY());}
        void turnTo (GLdouble d){ dir = d;}
        void turn (GLdouble ang) {dir += ang;}

        GLfloat getPosX(){ return pos->getX(); }
        GLfloat getPosY(){ return pos->getY(); }
        GLdouble getDir(){ return dir;}

    /*** FORWARD ***/
        void foward (GLdouble dist, boolean draw ){
            GLdouble newX = pos->getX() + dist * cos(dir);
            GLdouble newY = pos->getY() + dist * sin(dir);

            if (draw){

                glColor3f(0, 0, 1.0);

                glBegin(GL_LINES);
                        glVertex2f(pos->getX(), pos->getY());
                        glVertex2f(newX, newY);
                glEnd();
            }
            pos->setCoor(newX, newY);
        }
      
    /*** LOOKAT ***/
        void lookAt(PV2D* p){  
      
            GLdouble x = p->getX() - pos->getX();
            GLdouble y =  p->getY() - pos->getY();
            dir = atan2 (  y   , x );
            GLdouble degrees = dir * 180 / PI;
        }
};
    

#endif

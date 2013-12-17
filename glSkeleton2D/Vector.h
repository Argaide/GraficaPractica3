//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef VectorH
#define VectorH

#include <gl\gl.h>
#include <gl\glu.h>

#include "PV2D.h"
#include <math.h>
#define PI 3.14159265

//---------------------------------------------------------------------------

class Vector
{
   private:

        PV2D* vector;

   public:
        Vector();
        Vector(PV2D* p){ vector = p; }
        Vector(PV2D* p1, PV2D* p2){ vector = new PV2D(p2->getX() - p1->getX(), p2->getY() - p1->getY() ); }

        ~Vector(){ delete vector;};

        GLdouble getX(){ return vector->getX(); }
        GLdouble getY(){ return vector->getY(); }
        PV2D* getPunto(){ return vector; }
        void setX(GLdouble x){ vector->setX(x); }
        void setY(GLdouble y){ vector->setY(y); }

        GLdouble getModulo(){ return sqrt (pow (getX(),2) +  pow(getY(), 2) ); }

        void  getNormalVector(){
             GLdouble aux = getX();
             GLdouble componenteX = -getY();
             GLdouble componenteY = aux;
             setX(componenteX); setY(componenteY);
        }
        
        void getVectorNormalizado(){

                GLdouble modulo = sqrt (pow (getX(),2) +  pow(getY(), 2) );
                GLdouble componenteX = getX() / modulo;
                GLdouble componenteY = getY() / modulo;
                setX(componenteX); setY(componenteY);
        }

        GLdouble productoEscalar(Vector* w){
                return (getX() * w->getX() + getY() * w->getY());
        }

        void productoVectorPorConstante(GLdouble k){
            setX(getX()*k); setY(getY()*k);
        }



};


#endif

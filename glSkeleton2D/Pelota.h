//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef PelotaH
#define PelotaH

#include <gl\gl.h>
#include <gl\glu.h>

#include "PV2D.h"
#include "Poligono.h"
#include "Vector.h"
#include "Triangulo.h"
#include "Obstaculo.h"

#include <math.h>
#define PI 3.14159265

//---------------------------------------------------------------------------
class Pelota
{
   private:

        Vector* vectorMovimiento; // vector que expresa el movimiento (Velocidad)
        Poligono* poligono;

   public:
        Pelota();
        Pelota(GLdouble r, PV2D* c, Vector* v){
            vectorMovimiento =  v;
            poligono = new Poligono(r, c);
        }
        ~Pelota(){ delete vectorMovimiento; delete poligono;};

/*** GET ***/ 
        PV2D* getCentro(){ return poligono->getCentro(); }
        GLdouble getX(){ return poligono->getCentro()->getX(); }
        GLdouble getY(){ return poligono->getCentro()->getY(); }
        Vector* getVector() {return vectorMovimiento;}
        double getRadio(){ return poligono->getRadio(); }

/*** SET ***/ 
        void setCentro(GLdouble x, GLdouble y){ poligono->setCentro(x,y); }
        void cambiaSentidoRotacion() {poligono->cambiaSentidoRotacion();}

/*** DIBUJA PELOTA ***/
        void dibujaPelota(){
            poligono->pintaPoligonoCentrado();

            // Pintamos el centro de la pelota
            glMatrixMode(GL_MODELVIEW);
            glTranslated(getX(),getY(),0);
            glColor3f(1,0,0);
            glBegin(GL_POINTS);
                glVertex2d(1,1);
            glEnd();
            glLoadIdentity();
        }

         void muevePelota(){ // TODO -> USAR LA CLASE TTIMER... (por el momento no la uso)

            GLdouble nuevaX = getX() + vectorMovimiento->getX();
            GLdouble nuevaY = getY() + vectorMovimiento->getY();
            setCentro(nuevaX, nuevaY);
        }

        void muevePelotaHasta(GLdouble tImpacto){ // TODO -> USAR LA CLASE TTIMER... (por el momento no la uso)
             tImpacto = tImpacto/10;
             Vector* aux = new Vector(new PV2D (vectorMovimiento->getX(), vectorMovimiento->getY()));
             aux->productoVectorPorConstante(tImpacto);

             GLdouble nuevaX = getX() + aux->getX();
             GLdouble nuevaY = getY() + aux->getY();
             setCentro(nuevaX, nuevaY);

             delete aux;
        }

};

#endif

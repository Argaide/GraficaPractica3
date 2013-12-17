//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef PoligonoH
#define PoligonoH

#include <gl\gl.h>
#include <gl\glu.h>
#include "PV2D.h"
#include "Obstaculo.h"
#include "Lapiz.h"
#include "Lista.h"

#include <math.h>
#define PI 3.14159265

//---------------------------------------------------------------------------

class Poligono
{
   private:
        double radio;
        PV2D* centro;                    
        Lista<PV2D*>* listaVertices;
        
   public:
        Poligono();
        Poligono(double r, PV2D* c){
            radio = r;
            centro = c;
            listaVertices = new Lista<PV2D*>();
        }
        ~Poligono(){ radio = 0; delete centro; delete listaVertices;};

/*** GETTERS ***/    
        double getRadio(){ return radio; }
        PV2D* getCentro(){ return centro; }

/*** SETTERS ***/
        void setRadio(double r){ radio = r; }
        void setCentro(GLdouble x, GLdouble y){ centro->setCoor(x,y); }

/*** PINTAR ***/
        void pintaPoligono(){

            listaVertices->vaciaLista();

            int numeroLados = 30;  // numero de lados que tiene el Poligono, le ponemos por ejemplo 120

            //Calculamos el angulo con el el que tiene que mover el lapiz
            GLdouble anguloDesigual = 360 / numeroLados * PI / 180;                                 
            GLdouble angulo = ((2*PI) - anguloDesigual) / 2;

            Lapiz* lapiz = new Lapiz();

            // Movemos el lapiz al principio del Poligono
            GLdouble centroX = centro->getX();
            GLdouble centroY = centro->getY();
            PV2D* vertice0 = new PV2D(centroX + radio, centroY);
            lapiz->moveTo(vertice0);

            // Calculamos el punto en el que el lapiz tiene que mirar
            GLdouble mitadAngulo = anguloDesigual / 2;
            GLfloat dist =  radio * sin(mitadAngulo) * 2;
            GLdouble anguloAux = PI - angulo;
            GLfloat base = dist * sin(anguloAux);
            GLfloat nuevaY = dist * cos(anguloAux);
            GLdouble nuevoX = radio - base;

            PV2D* vertice1 = new PV2D(centroX+nuevoX, centroY+nuevaY);
            lapiz->lookAt(vertice1);

            //Movemos el lapiz para adelante y formar el primer lado del Poligono
            lapiz->foward(dist, true);

            // anadimos a la lista de vertices los dos primeros vertices
            listaVertices->ponElem(vertice0);
            listaVertices->ponElem(vertice1);

            GLdouble anguloAuxiliar = (2*PI)-(2*angulo);
            for(int i = 0; i < (numeroLados-1); i++){
                // primero movemos el lapiz, lo avanzamos y metemos el nuevo vertice en la lista
                lapiz->turn(anguloAuxiliar);
                lapiz->foward(dist, true);
                PV2D* verticeI = new PV2D(lapiz->getPosX(), lapiz->getPosY());
                listaVertices->ponElem(verticeI);
            }

            pintaVertices();

            delete lapiz;
        }

/*** PINTA VERTICES ***/
        void pintaVertices(){

            int numElem = listaVertices->numElem();
            PV2D* verticeActual;

            glColor3f(0,1,0);
            glBegin(GL_LINE_STRIP);

                for(int i=0; i<numElem; i++)
                {
                    verticeActual = listaVertices->iesimo(i);
                    GLdouble x = verticeActual->getX();
                    GLdouble y = verticeActual->getY();
                    glVertex2d(x, y);
                }
            glEnd();
        }
};

#endif




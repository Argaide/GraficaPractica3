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
        double rotacionAcumulada;
        bool sentidoRotacion; // true para horario false para antihorario
        
   public:
        Poligono();
        Poligono(double r, PV2D* c){
            radio = r;
            centro = c;
            listaVertices = new Lista<PV2D*>();  
            rotacionAcumulada=0;
            sentidoRotacion=false;
        }
        ~Poligono(){ radio = 0; delete centro; delete listaVertices; rotacionAcumulada=0;};

/*** GETTERS ***/    
        double getRadio(){ return radio; }
        PV2D* getCentro(){ return centro; }

/*** SETTERS ***/
        void setRadio(double r){ radio = r; }
        void setCentro(GLdouble x, GLdouble y){ centro->setCoor(x,y); }
        void cambiaSentidoRotacion(){ if(sentidoRotacion) sentidoRotacion = false; else sentidoRotacion=true;}

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

/*** PINTA POLIGONO EN EL CENTRO ***/
//Pinta un poligono de radio 1 y centrado en el origen
void pintaPoligonoCentrado(){

            listaVertices->vaciaLista();

            int numeroLados = 30;  // numero de lados que tiene el Poligono, le ponemos por ejemplo 120

            //Calculamos el angulo con el el que tiene que mover el lapiz
            GLdouble anguloDesigual = 360 / numeroLados * PI / 180;                                 
            GLdouble angulo = ((2*PI) - anguloDesigual) / 2;

            Lapiz* lapiz = new Lapiz();

            // Movemos el lapiz al principio del Poligono
            GLdouble centroX = 0;
            GLdouble centroY = 0;
            GLdouble radio = 1;
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
            //pintaRadios();

            delete lapiz;
        }

/*** PINTA VERTICES ***/
        void pintaVertices(){

            int numElem = listaVertices->numElem();
            PV2D* verticeActual;
            glMatrixMode(GL_MODELVIEW);
            //glRotated(90,0,0,0);
            glTranslated(centro->getX(),centro->getY(),0);
            glScaled(radio,radio,1);
            glRotated(rotacionAcumulada,0,0,1);
            glColor3f(0,1,0);
            glBegin(GL_LINE_STRIP);

                for(int i=0; i<numElem; i++)
                {
                    verticeActual = listaVertices->iesimo(i);
                    GLdouble x = verticeActual->getX();
                    GLdouble y = verticeActual->getY();
                    glVertex2d(x, y);
                }
                glVertex2d(0, 0);
                //glVertex2d(0, 1);
            glEnd();
            glLoadIdentity();

            if(sentidoRotacion) rotacionAcumulada++; else rotacionAcumulada--;

        }

/*** PINTA RADIOS ***/
void pintaRadios(){

            glMatrixMode(GL_MODELVIEW);
            glScaled(radio,radio,1);
            glTranslated(centro->getX(),centro->getY(),0);
            //glRotated(90,radio,radio,0);
                glColor3f(0,1,0);
                //Pintamos el radio a piñon en el origen
             glBegin(GL_LINE_STRIP);
                    glVertex2d(0, 0);
                    glVertex2d(0, 1);
            glEnd();
            glLoadIdentity();

        }

};

#endif




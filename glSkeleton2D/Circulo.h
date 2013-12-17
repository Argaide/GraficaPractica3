//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef CirculoH
#define CirculoH

#include <gl\gl.h>
#include <gl\glu.h>
#include "PV2D.h"
#include "Obstaculo.h"
#include "Lapiz.h"
#include "Lista.h"
#include "Poligono.h"
#include "Pelota.h"

#include <math.h>
#define PI 3.14159265

//---------------------------------------------------------------------------

class Circulo : public Obstaculo
{
   private:
        Poligono* poligono;
        Vector* normalCirculo;

   public:
        Circulo();
        Circulo(double r, PV2D* c){
            poligono = new Poligono(r,c);
        }
        ~Circulo(){ delete poligono; };

/*** GETTERS ***/    
        double getRadio(){ return poligono->getRadio(); }
        PV2D* getCentro(){ return poligono->getCentro(); }

/*** SETTERS ***/
        void setRadio(double r){ poligono->setRadio(r); }
        void setCentro(GLdouble x, GLdouble y){ poligono->setCentro(x,y); }

/*** HAY COLISION (Metodo de Obstaculo) ***/
 bool  resuelveColision(Vector* normal, PV2D* centro, Vector* vectorMovimiento){
          //ShowMessage("Resolviendo colision con el circulo");

           GLdouble modulo = vectorMovimiento->getModulo();

           Vector* centroAlPuntoDeImpacto = new Vector(getCentro(), centro );
           centroAlPuntoDeImpacto->getVectorNormalizado();
           centroAlPuntoDeImpacto->productoVectorPorConstante(modulo);

           vectorMovimiento->setX(centroAlPuntoDeImpacto->getX());
           vectorMovimiento->setY(centroAlPuntoDeImpacto->getY());

           delete centroAlPuntoDeImpacto;

      return false;
}

/*** RESUELVE COLISION (Metodo de Obstaculo) ***/
        bool hayColision(PV2D* centro, Vector* vector , GLdouble& tImpacto, Vector*& normalImpacto){
            //ShowMessage("Comprobando si hay colision con un circulo");
            tImpacto = 9999;

            //Calculo de datos
            GLdouble A = vector->productoEscalar(vector);

            Vector* vectorAuxCP = new Vector( getCentro(), centro);
            GLdouble B = 2* vectorAuxCP->productoEscalar(vector);

            GLdouble C = vectorAuxCP->productoEscalar(vectorAuxCP) - pow(getRadio(), 2);

            GLdouble delta = pow(B, 2) - 4* A * C;

            delete vectorAuxCP;
           // Miramos si hay colision con el circulo
           if(delta < 0){
                //ShowMessage("No hay interseccion con el circulo");

                return false;
           }

           //Calculamos los tImpactos y miramos cual es menor
           tImpacto = (-B - pow(delta,0.5)) / (2*A);

           normalImpacto  = 0;

           GLdouble tImpactoAux = (-B + sqrt(delta)) / (2*A);

           if(tImpactoAux < tImpacto){
                tImpacto = tImpactoAux;
                normalImpacto= 0;
           }

           //ShowMessage("Hay interseccion con el circulo");
            return true;
        }

/*** PINTAR EL CIRCULO ***/
        void pintaObstaculo(){
            poligono->pintaPoligono();
        }
};



#endif

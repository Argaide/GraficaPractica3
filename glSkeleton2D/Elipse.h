//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef ElipseH
#define ElipseH

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

class Elipse : public Obstaculo
{
   private:
        Poligono* poligono;
        Vector* normalElipse;

   public:
        Elipse();
        Elipse(double ancho, double alto, PV2D* c){
            poligono = new Poligono(ancho, alto,c, false);             
        }
        ~Elipse(){ delete poligono; };

/*** GETTERS ***/
        double getAnchura(){ return poligono->getAnchura(); }
        double getAltura(){ return poligono->getAltura(); }
        PV2D* getCentro(){ return poligono->getCentro(); }

/*** SETTERS ***/
        void setAnchura(double a){ poligono->setAnchura(a); }
        void setAltura(double a){ poligono->setAltura(a); }
        void setCentro(GLdouble x, GLdouble y){ poligono->setCentro(x,y); }

/*** HAY COLISION (Metodo de Obstaculo) ***/
        bool resuelveColision(Vector* normal, PV2D* centro, Vector* vectorMovimiento){
            //ShowMessage("Resolviendo colision con la elipse");

            GLdouble modulo = vectorMovimiento->getModulo();

            Vector* centroAlPuntoDeImpacto = new Vector(getCentro(), centro);

            // Lo multiplicamos por la normal
            GLdouble xVector = (1/poligono->getAnchura()) * centroAlPuntoDeImpacto->getX() ;
            GLdouble yVector = (1/poligono->getAltura()) * centroAlPuntoDeImpacto->getY() ;
            Vector* centroAlPuntoDeImpactoNuevo = new Vector( new PV2D(xVector,yVector));

            centroAlPuntoDeImpactoNuevo->getVectorNormalizado();
            centroAlPuntoDeImpactoNuevo->productoVectorPorConstante(modulo);

            vectorMovimiento->setX(centroAlPuntoDeImpactoNuevo->getX());
            vectorMovimiento->setY(centroAlPuntoDeImpactoNuevo->getY());

            delete centroAlPuntoDeImpactoNuevo;
            delete centroAlPuntoDeImpacto;

            return false;
        }

/*** RESUELVE COLISION (Metodo de Obstaculo) ***/
        bool hayColision(PV2D* centro, Vector* vector , GLdouble& tImpacto, Vector*& normalImpacto){
            //ShowMessage("Comprobando si hay colision con la elipse");
            tImpacto = 9999;

            //Calculo el nuevo centro de la pelota transformado
            GLdouble xCentro = (1/poligono->getAnchura()) * centro->getX() - (poligono->getCentro()->getX() / poligono->getAnchura() ) ;
            GLdouble yCentro = (1/poligono->getAltura()) * centro->getY() - (poligono->getCentro()->getY() / poligono->getAltura());
            PV2D* centroPelotaTransformado = new PV2D(xCentro,yCentro);

            //Calculo el nuevo vector de la pelota transformado
            GLdouble xVector = (1/poligono->getAnchura()) * vector->getX() ;
            GLdouble yVector = (1/poligono->getAltura()) * vector->getY() ;
            Vector* vectorPelotaTransformado = new Vector( new PV2D(xVector,yVector));

            //LLevo una variable con el centro de la elipse transformada
            PV2D* centroElipseTransformado = new PV2D(0,0);

            //Ahora calculo la interseccion como si fuese un circulo de radio 1 y centrado en el origen
            GLdouble A = vectorPelotaTransformado->productoEscalar(vectorPelotaTransformado);

            Vector* vectorAuxCP = new Vector( centroElipseTransformado, centroPelotaTransformado);
            GLdouble B = 2* vectorAuxCP->productoEscalar(vectorPelotaTransformado);

            GLdouble C = vectorAuxCP->productoEscalar(vectorAuxCP) - pow(1, 2);

            GLdouble delta = pow(B, 2) - 4* A * C;

            delete centroPelotaTransformado;
            delete vectorPelotaTransformado;
            delete centroElipseTransformado;
            delete vectorAuxCP;


            if(delta < 0){
                //ShowMessage("No hay interseccion con la elipse");
                return false;
           }
           //ShowMessage("Hay interseccion con la elipse");

            //Calculamos los tImpactos y miramos cual es menor
           tImpacto = (-B - pow(delta,0.5)) / (2*A);

           normalImpacto  = 0;

           GLdouble tImpactoAux = (-B + sqrt(delta)) / (2*A);

           if(tImpactoAux < tImpacto){
                tImpacto = tImpactoAux;
                normalImpacto= 0;
           }


            return true;
        }

/*** PINTAR EL CIRCULO ***/
        void pintaObstaculo(){
            poligono->pintaPoligonoCentrado();
        }
};



#endif

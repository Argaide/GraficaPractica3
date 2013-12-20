//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef RecbElipseH
#define RecbElipseH

#include <gl\gl.h>
#include <gl\glu.h>
#include "PV2D.h"
#include "Obstaculo.h"
#include "Elipse.h"
#include "Lapiz.h"
#include "Lista.h"

#include <math.h>
#define PI 3.14159265

//---------------------------------------------------------------------------

class RecbElipse : public Obstaculo
{
  private:
        Elipse* elipse;
        Elipse* recubrimiento;
        double radioPelota;

  public:
        RecbElipse();                                               
        RecbElipse(double r, Elipse* e){     
            radioPelota = r;
            elipse = e;
            recubrimiento = new Elipse(e->getAnchura() + radioPelota, e->getAltura() + radioPelota, new PV2D(e->getCentro()->getX(),e->getCentro()->getY()));
        }

        ~RecbElipse(){ radioPelota = 0; delete recubrimiento; delete elipse;};

/*** HAY COLISION ***/
        bool hayColision(PV2D* centro, Vector* vector, GLdouble& tImpacto , Vector*& normalImpacto){
            return recubrimiento->hayColision(centro, vector , tImpacto, normalImpacto);
        }

/*** RESUELVE COLISION ***/
        bool resuelveColision(Vector* normal, PV2D* centro, Vector* vectorMovimiento){
            return elipse->resuelveColision(normal, centro, vectorMovimiento);
        }

/*** PINTA OBSTACULO ***/
        void pintaObstaculo(){
            elipse->pintaObstaculo();
            //recubrimiento->pintaObstaculo();
        }
};

#endif




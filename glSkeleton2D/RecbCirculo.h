//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef RecbCirculoH
#define RecbCirculoH

#include <gl\gl.h>
#include <gl\glu.h>
#include "PV2D.h"
#include "Obstaculo.h"
#include "Circulo.h"
#include "Lapiz.h"
#include "Lista.h"

#include <math.h>
#define PI 3.14159265

//---------------------------------------------------------------------------

class RecbCirculo : public Obstaculo
{
  private:
      Circulo* circulo;
      Circulo* recubrimiento;
      double radioPelota;

  public:
        RecbCirculo();                                               
        RecbCirculo(double r, Circulo* c){     
            radioPelota = r;
            circulo = c;
            recubrimiento = new Circulo(c->getRadio() + radioPelota, new PV2D(c->getCentro()->getX(),c->getCentro()->getY()));
        }

        ~RecbCirculo(){ radioPelota = 0; delete recubrimiento; delete circulo;};

/*** HAY COLISION ***/
        bool hayColision(PV2D* centro, Vector* vector, GLdouble& tImpacto , Vector*& normalImpacto){
            return recubrimiento->hayColision(centro, vector , tImpacto, normalImpacto);
        }

/*** RESUELVE COLISION ***/
        bool resuelveColision(Vector* normal, PV2D* centro, Vector* vectorMovimiento){
            return circulo->resuelveColision(normal, centro, vectorMovimiento);
        }

/*** PINTA OBSTACULO ***/
        void pintaObstaculo(){
            circulo->pintaObstaculo();
            //recubrimiento->pintaObstaculo();
        }
};

#endif




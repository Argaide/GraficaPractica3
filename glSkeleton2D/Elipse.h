//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef ElipseH
#define ElipseCirculoH

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
        Elipse(double r, PV2D* c){
            poligono = new Poligono(r,c);             
        }
        ~Elipse(){ delete poligono; };

/*** GETTERS ***/    
        double getRadio(){ return poligono->getRadio(); }
        PV2D* getCentro(){ return poligono->getCentro(); }

/*** SETTERS ***/
        void setRadio(double r){ poligono->setRadio(r); }
        void setCentro(GLdouble x, GLdouble y){ poligono->setCentro(x,y); }

/*** HAY COLISION (Metodo de Obstaculo) ***/
 bool  resuelveColision(Vector* normal, PV2D* centro, Vector* vectorMovimiento){
          //ShowMessage("Resolviendo colision con el circulo");


      return false;
}

/*** RESUELVE COLISION (Metodo de Obstaculo) ***/
        bool hayColision(PV2D* centro, Vector* vector , GLdouble& tImpacto, Vector*& normalImpacto){
            //ShowMessage("Comprobando si hay colision con un circulo");
            tImpacto = 9999;


            return true;
        }

/*** PINTAR EL CIRCULO ***/
        void pintaObstaculo(){
            poligono->pintaPoligono();
        }
};



#endif

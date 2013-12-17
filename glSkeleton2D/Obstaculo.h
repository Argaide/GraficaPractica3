//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef ObstaculoH
#define ObstaculoH

#include <gl\gl.h>
#include <gl\glu.h>

#include "PV2D.h"
#include "Vector.h"

//---------------------------------------------------------------------------

class Obstaculo
{        
    public:
    	Obstaculo(){}
        virtual ~Obstaculo(){}
        virtual bool hayColision(PV2D* centro, Vector* vector, GLdouble& tImpacto , Vector*& normalImpacto) = 0;
        virtual bool resuelveColision(Vector* normal, PV2D* centro,  Vector* vectorMovimiento) = 0;
        virtual void pintaObstaculo() = 0;
};

#endif

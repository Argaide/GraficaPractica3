//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef PV2DH
#define PV2DH

#include <gl\gl.h>
#include <gl\glu.h>
//---------------------------------------------------------------------------
class PV2D
{
   private:
        // Coordenadas de un Punto o Vector en dos dimensiones
        GLdouble x;
        GLdouble y;

   public:
        PV2D();
        PV2D(GLdouble newX, GLdouble newY){x=newX; y=newY;};
        ~PV2D(){ x=0 ; y=0;};
        GLdouble getX(){return x;};
        GLdouble getY(){return y;};
        void setCoor(GLdouble newX, GLdouble newY){x=newX; y=newY;};
        void setX(GLdouble newX){x=newX;};
        void setY(GLdouble newY){y=newY;};
};

#endif

//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef TrianguloH
#define TrianguloH

#include <gl\gl.h>
#include <gl\glu.h>
#include "PV2D.h"
#include "Obstaculo.h"
#include "Pelota.h"

//---------------------------------------------------------------------------

class Triangulo : public Obstaculo
{
   private:
        //Nota, los triangulos han de declararse de manera horaria
        PV2D* vertices[3];
        Vector* normales[3]; //normales[0] lleva la normal entre los puntos getP1() y getP2() normales[1] entre getP2() y getP3() y normales[2] entre getP3() y getP1()
        //Para que el vector de normales funcione bien es muy importante que los vertices del triangulo se numeren en sentido horario
        Vector* alturas[3];

   public:
        Triangulo();
        Triangulo(PV2D* v1, PV2D* v2, PV2D* v3){
            vertices[0] = v1;
            vertices[1] = v2;
            vertices[2] = v3;
            calculaNormalesDeAristas();
            calculaAlturasVertices();
        }
        ~Triangulo(){  
            delete vertices[0]; 
            delete vertices[1]; 
            delete vertices[2]; 

            delete normales[0]; 
            delete normales[1]; 
            delete normales[2];

            delete alturas[0]; 
            delete alturas[1]; 
            delete alturas[2];
        }

/*** GETTERS ***/
        PV2D* getP1(){ return vertices[0];}
        PV2D* getP2(){ return vertices[1];}
        PV2D* getP3(){ return vertices[2];}

        Vector* getNormal1(){ return normales[0];}
        Vector* getNormal2(){ return normales[1];}
        Vector* getNormal3(){ return normales[2];}

/*** CALCULA NORMALES ***/
        void calculaNormalesDeAristas(){

                normales[0] = new Vector(getP1(), getP2());
                normales[0]->getNormalVector();
                normales[0]->getVectorNormalizado();

                normales[1] = new Vector(getP2(), getP3());
                normales[1]->getNormalVector();
                normales[1]->getVectorNormalizado();

                normales[2] = new Vector(getP3(), getP1());
                normales[2]->getNormalVector();
                normales[2]->getVectorNormalizado();
        }


 /*** HAY COLISION (Metodo de Obstaculo) ***/
 bool hayColision(PV2D* centro, Vector* vector , GLdouble& tImpacto, Vector*& normalImpacto){
            //ShowMessage("Comprobando si hay colision con un triangulo");
            tImpacto = 999;


              //Calculo de las distancias
              GLdouble dist[3];
              GLdouble proy[3];
              int signo[3]; signo[0]= signo[1] = signo[2] = 0;
              PV2D* vertices[3]; vertices[0] = getP1(); vertices[1] = getP2(); vertices[2] = getP3();
              
              Vector* vectorAux = new Vector(new PV2D (vector->getX(), vector->getY()));
              Vector* vectorAux2 = new Vector(new PV2D (vector->getX(), vector->getY()));
              
              vectorAux->getVectorNormalizado();
              vectorAux2->getVectorNormalizado(); vectorAux2->getNormalVector();

              for(int i = 0; i<3; i++){
                Vector* vectorAuxPPi = new Vector(centro, vertices[i] );
                dist[i] = vectorAux2->productoEscalar(vectorAuxPPi);
                proy[i] = vectorAux->productoEscalar(vectorAuxPPi);
                delete vectorAuxPPi;

                if(dist[i] > 0){
                        signo[i] = 1;
                } else if(dist[i] < 0){
                        signo[i]=-1;
                }
              }

              delete vectorAux;
              delete vectorAux2;

              int suma =  signo[0] + signo[1] + signo[2];
              if(abs(suma) == 3){
                //ShowMessage("La pelota no ha colisionado con un triangulo. Trivial failure");
                return false;
              }else{
                //ShowMessage("La pelota esta la la linea de colision de un triangulo");

                // 1) Impactos en Aristas
                int numImpactos=0; GLdouble impacto[3]; Vector* normalDelImpacto[3];
                impacto[0] = impacto[1] = impacto[2] = 9999;
                // i Vertice actual
                // j Vertice siguiente
                int j;
                for(int i=0; i < 3 ; i++){
                   j = (i+1) %3;
                   //Miramos si en la artista del vertice i al vertice j esta en la linea de colision
                   if( signo[i]*signo[j] <0 ){
                       GLdouble numerador =  (proy[i] * dist[j]) - (dist[i] * proy[j]);
                       GLdouble denominador = dist[j] - dist[i];

                       impacto[numImpactos] = numerador/denominador;
                       normalDelImpacto [numImpactos] = normales[i];
                       numImpactos++;
                   }
                }

                // 2) Impactos en Vertices
                if(numImpactos < 2){       // numImpactos == 1
                    for(int i=0; i < 3; i++){
                        if(signo[i] == 0){
                            impacto[numImpactos] = proy[i];    
                            normalDelImpacto[numImpactos] = alturas[i];
                            numImpactos++;
                        }
                    }
                }

                
                //Resultados
                GLdouble minImpacto = impacto[0];
                int indiceMinImpacto = 0;
                for(int k = 1; k<3; k++){
                    if(minImpacto > impacto[k]){
                        minImpacto = impacto[k];
                        indiceMinImpacto = k;
                    }
                }

                tImpacto = impacto[indiceMinImpacto];
                normalImpacto = normalDelImpacto[indiceMinImpacto];

                return true;
              }
}

/*** RESUELVE COLISION (Metodo de Obstaculo) ***/
        bool resuelveColision(Vector* normal, PV2D* centro, Vector* vectorMovimiento){
                //Calculo a con el vectorMovimiento de la pelota y la normal de la normal del lado del triangulo con el que se choca
                Vector* auxNormal = new Vector(new PV2D (normal->getX(), normal->getY()));

                GLdouble aNumerador = auxNormal->productoEscalar(vectorMovimiento);
                GLdouble aDenominador = auxNormal->productoEscalar(auxNormal);

                GLdouble a = aNumerador / aDenominador;

                GLdouble componenteX = vectorMovimiento->getX() - 2 * a * normal->getX();
                GLdouble componenteY = vectorMovimiento->getY() - 2 * a * normal->getY();

                vectorMovimiento->setX(componenteX);
                vectorMovimiento->setY(componenteY);

                //Calculo las dos componentes de r y las devulto.
                //E intercambio la r nueva por el vector movimiento
                 delete auxNormal;

            return true;
        }

/*** PINTAR ***/
        void pintaObstaculo(){
            glColor3f(0,0,0);
            glBegin(GL_TRIANGLES);
                glVertex2d(getP1()->getX(),getP1()->getY());
                glVertex2d(getP2()->getX(),getP2()->getY());
                glVertex2d(getP3()->getX(),getP3()->getY());
            glEnd();
        }

/*** DISTANCIA DEL CENTRO AL VERTICE ***/
        void transformaVector(PV2D* vertice, Vector* vector){
            vector->getNormalVector();
            GLdouble nuevaX = (-1) * vector->getX();
            GLdouble nuevaY = (-1) * vector->getY();
            vector->setX(nuevaX);
            vector->setY(nuevaY);
        }

/*** CALCULA ALTURAS ***/
        void calculaAlturasVertices(){
            for(int i = 0; i < 3; i++){
                int indiceT1 = (i+1)%3;
                int indiceT2 = (i+2)%3;
                Vector* vectorResultante = new Vector(vertices[indiceT1], vertices[indiceT2]);
                transformaVector(vertices[i], vectorResultante);    // vector del centro del triangulo al punto Pi
                alturas[i] = vectorResultante;
            }
        }

};

#endif

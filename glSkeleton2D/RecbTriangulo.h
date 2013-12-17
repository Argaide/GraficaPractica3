//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef RecbTrianguloH
#define RecbTrianguloH

#include <gl\gl.h>
#include <gl\glu.h>
#include "PV2D.h"
#include "Obstaculo.h"
#include "Triangulo.h"
#include "Lapiz.h"
#include "Lista.h"
#include "Vector.h"

#include <math.h>
#define PI 3.14159265

//---------------------------------------------------------------------------

class RecbTriangulo : public Obstaculo
{
    private:

        Lista<PV2D*>* listaVertices;
        Lista<Vector*>* listaNormales;

        Triangulo* triangulo;
        double radioPelota;

    public:

        RecbTriangulo();
        RecbTriangulo(double r, Triangulo* t){

            radioPelota = r;
            triangulo = t;
            listaVertices = new Lista<PV2D*>();
            calulaRecubrimiento();
            listaNormales = new Lista<Vector*>();
            calculaNormalesDeAristas();
        }

        ~RecbTriangulo(){
            radioPelota = 0;            
            delete triangulo;
            delete listaVertices;
            delete listaNormales;
        };

/*** HAY COLISION ***/
        bool hayColision(PV2D* centro, Vector* vector, GLdouble& tImpacto , Vector*& normalImpacto){
            //ShowMessage("Calculando colision con un triangulo recubierto");

            GLdouble tIn = 0; GLdouble tOut = radioPelota;
            int i = 0; bool encontrado = false; tImpacto = 9999;
            while(!encontrado && i<listaVertices->numElem()){

                Vector* PiP = new Vector(listaVertices->iesimo(i), centro);
                GLdouble numerador =  PiP->productoEscalar(listaNormales->iesimo(i));
                GLdouble denominador = vector->productoEscalar(listaNormales->iesimo(i));

                //if(denominador == 0 && numerador >= 0 ) //paralelismo por fuera y coincidencia
                //        encontrado = true;
                 if(denominador != 0 ){ // interseccion normal
                     tImpacto = (-numerador) / denominador;
                     if( denominador < 0){
                        if (tImpacto > tIn ) {tIn = tImpacto; normalImpacto = listaNormales->iesimo(i);}
                     }
                     else if(denominador > 0 ){
                         tOut = min(tOut, tImpacto);
                     }
                    if ( tIn > tOut) {delete PiP; tImpacto = 999;return false ;}
                }
                delete PiP;
                i++;
            }

            tImpacto = vector->getModulo()*tIn;
            return true;
        }

/*** RESUELVE COLISION ***/
        bool resuelveColision(Vector* normal, PV2D* centro,  Vector* vectorMovimiento){
            //ShowMessage("Resolviendo colision con un triangulo recubierto");
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


/*** PINTA OBSTACULO ***/
        void pintaObstaculo(){
            glColor3f(0.4,0,0.4);
            glBegin(GL_TRIANGLES);
                glVertex2d(triangulo->getP1()->getX(),triangulo->getP1()->getY());
                glVertex2d(triangulo->getP2()->getX(),triangulo->getP2()->getY());
                glVertex2d(triangulo->getP3()->getX(),triangulo->getP3()->getY());
            glEnd();

            /*int numElem = listaVertices->numElem();
            PV2D* verticeActual;

            glColor3f(1,0,0);
            glBegin(GL_LINE_STRIP);

                for(int i=0; i<numElem; i++)
                {
                    verticeActual = listaVertices->iesimo(i);
                    GLdouble x = verticeActual->getX();
                    GLdouble y = verticeActual->getY();
                    glVertex2d(x, y);
                }

                verticeActual = listaVertices->iesimo(0);
                GLdouble x = verticeActual->getX();
                GLdouble y = verticeActual->getY();
                glVertex2d(x, y);
                
            glEnd();*/  
        }

/*** CALCULA RECUBRIMIENTO ***/

        void calulaRecubrimiento(){

            PV2D* vertices[3];
            vertices[0] = triangulo->getP1(); vertices[1] = triangulo->getP2(); vertices[2] = triangulo->getP3();

            Vector* normales[3];
            normales[0] = triangulo->getNormal1(); normales[1] = triangulo->getNormal2(); normales[2] = triangulo->getNormal3();

            for(int i = 0; i < 3; i++){
                int j = (i + 1) % 3;

            //Calculamos el lado
                PV2D* verticeAux1 = new PV2D (vertices[i]->getX(), vertices[i]->getY());
                PV2D* verticeAux2 = new PV2D (vertices[j]->getX(), vertices[j]->getY());
                Vector* normal1 = new Vector(new PV2D (normales[i]->getX(), normales[i]->getY()));
                normal1->getVectorNormalizado();
                normal1->productoVectorPorConstante(radioPelota);

                verticeAux1->setX(verticeAux1->getX() + normal1->getX() );
                verticeAux1->setY(verticeAux1->getY() + normal1->getY() );

                verticeAux2->setX(verticeAux2->getX() + normal1->getX() );
                verticeAux2->setY(verticeAux2->getY() + normal1->getY() );

                // Metemos el lado en la lista
                listaVertices->ponElem(verticeAux2);

                delete normal1;

            // Calculamos el tercer vertice para calcular el arco
                PV2D* verticeAux3 = new PV2D (vertices[j]->getX(), vertices[j]->getY());
                Vector* normal2 = new Vector(new PV2D (normales[j]->getX(), normales[j]->getY()));
                normal2->getVectorNormalizado();
                normal2->productoVectorPorConstante(radioPelota);

                verticeAux3->setX(verticeAux3->getX() + normal2->getX() );
                verticeAux3->setY(verticeAux3->getY() + normal2->getY() );

            //Calulamos el arco
                Lapiz* lapiz1 = new Lapiz();
                lapiz1->moveTo(vertices[j]);
                lapiz1->lookAt(verticeAux2);
                GLdouble anguloInicial = lapiz1->getDir();
                GLdouble anguloInicialGrados = (anguloInicial * 180) / PI;
                lapiz1->lookAt(verticeAux3);
                GLdouble anguloFinal = lapiz1->getDir();
                GLdouble anguloFinalGrados = (anguloFinal * 180) / PI;

                GLdouble recorridoAngulo = anguloInicial - anguloFinal;
                if(recorridoAngulo < 0) {recorridoAngulo = (2*PI) + recorridoAngulo;}
                GLdouble grados = (recorridoAngulo * 180) / PI;

                GLdouble anguloInterior = recorridoAngulo / 3; // Hacemos un arco de 3 lados
                GLdouble beta = (PI-anguloInterior) /2;
                GLdouble ganmma =  PI - beta;
                GLdouble lado = 2 * radioPelota * cos(beta);

                lapiz1->lookAt(verticeAux2);
                lapiz1->foward(radioPelota, false);
                lapiz1->turn(-ganmma);
                lapiz1->foward(lado,false);

                for(int k = 0; k < 3; k++){

                    PV2D* nuevoPunto = new PV2D(lapiz1->getPosX(), lapiz1->getPosY());
                    listaVertices->ponElem(nuevoPunto);

                    lapiz1->turn(-anguloInterior);
                    lapiz1->foward(lado,false);

                }

                delete lapiz1;
                delete normal2;
                delete verticeAux1;
                delete verticeAux3;
            }

        } 


        void calculaNormalesDeAristas(){

                PV2D* puntoActual;
                PV2D* puntoSiguiente;

                for(int i=0; i<listaVertices->numElem()-1; i++){
                        puntoActual = listaVertices->iesimo(i);
                        puntoSiguiente = listaVertices->iesimo(i+1);

                        Vector* normal = new Vector(puntoActual, puntoSiguiente);
                        normal->getNormalVector();
                        normal->getVectorNormalizado();
                        listaNormales->ponElem(normal);
                }

                //Ultima normal

                puntoActual = listaVertices->iesimo(listaVertices->numElem()-1);
                puntoSiguiente = listaVertices->iesimo(0);

                Vector* normal = new Vector(puntoActual, puntoSiguiente);
                normal->getNormalVector();
                normal->getVectorNormalizado();
                listaNormales->ponElem(normal);
        }
};

#endif




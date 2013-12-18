//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//


#include <vcl.h>
#pragma hdrstop

using namespace std;

#include "UFP.h"
#include "PV2D.h"
#include "Obstaculo.h"
#include "Pelota.h"
#include "Lista.h"
#include "Circulo.h"
#include "RecbTriangulo.h"
#include "RecbCirculo.h"
#include "Elipse.h"

#include <math.h>
#include "stdlib.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"

using namespace std;

TGLForm2D *GLForm2D;


/*** ATRIBUTOS GLOBALES ***/
Lista<Obstaculo*>* listaObstaculos;
Pelota* pelota;

//---------------------------------------------------------------------------

__fastcall TGLForm2D::TGLForm2D(TComponent* Owner)
        : TForm(Owner)
{
}

//---------------------------------------------------------------------------
//---------------------- FORM CREATE ----------------------------------------
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::FormCreate(TObject *Sender)
{
    hdc = GetDC(Handle);
    SetPixelFormatDescriptor();
    hrc = wglCreateContext(hdc);
    if(hrc == NULL)
            ShowMessage(":-)~ hrc == NULL");
    if(wglMakeCurrent(hdc, hrc) == false)
            ShowMessage("Could not MakeCurrent");
    //Cor de fondo de la ventana
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    //inicialización del volumen de vista
    xRight=200.0; xLeft=-xRight;
    yTop=250; yBot=-yTop;
    //Radio del volumen de vista == 1

    //inicialización del puerto de vista
    //ClientWidth=400;
    //ClientHeight=400;
    RatioViewPort=1.0;


    srand(time(NULL));
    int x = (rand() % 6) - 3;
    int y = (rand() % 6) - 3;

    while(y == 0)
        y = (rand() % 6) - 3;     // Evitamos que se mueva de forma horizontal al inicio

    pelota = new Pelota(25, new PV2D(0,0), new Vector(new PV2D(1, 1)));

    // inicialización de las variables del programa

    //Obstaculo* triangulo1 = new Triangulo(new PV2D(-570,570), new PV2D(570,170), new PV2D(-570,170));
    Obstaculo* recb01 = new RecbTriangulo(25, new Triangulo(new PV2D(-570,570), new PV2D(570,170), new PV2D(-570,170)));
    //Obstaculo* triangulo2 = new Triangulo(new PV2D(170,570), new PV2D(570,-170), new PV2D(170,-570));
    Obstaculo* recb02 = new RecbTriangulo(25, new Triangulo(new PV2D(170,570), new PV2D(570,-170), new PV2D(170,-570)));
    //Obstaculo* triangulo3 = new Triangulo(new PV2D(-570,-170), new PV2D(570,-170), new PV2D(-570,-570));
    Obstaculo* recb03 = new RecbTriangulo(25, new Triangulo(new PV2D(-570,-170), new PV2D(570,-170), new PV2D(-570,-570)));
    //Obstaculo* triangulo4 = new Triangulo(new PV2D(-570,170), new PV2D(-170,170), new PV2D(-170,-570));
    Obstaculo* recb04 = new RecbTriangulo(25, new Triangulo(new PV2D(-570,170), new PV2D(-170,170), new PV2D(-170,-570)));
    //Obstaculo* circulo1 = new Circulo (30, new PV2D(10,-100));
    //Obstaculo* triangulo5 = new Triangulo(new PV2D(-50,10), new PV2D(50,10), new PV2D(-10,-40));
    //Obstaculo* triangulo6 = new Triangulo(new PV2D(20,60), new PV2D(70,120), new PV2D(70,50));
    //Obstaculo* triangulo7 = new Triangulo(new PV2D(-70,-60), new PV2D(-10,-130), new PV2D(-90,-120) );
    //Obstaculo* circulo2 = new Circulo (30, new PV2D(-100,100));
    //Obstaculo* circulo3 = new Circulo (30, new PV2D(0,100));
    //Obstaculo* triangulo8 = new Triangulo(new PV2D(-30,0), new PV2D(0,30), new PV2D(30,0));

    //Obstaculo* recb1 = new RecbTriangulo(25, new Triangulo(new PV2D(-30,30), new PV2D(30,30), new PV2D(0,0)));
    //Obstaculo* recb2 = new RecbTriangulo(25, new Triangulo(new PV2D(-70,-60), new PV2D(-10,-130), new PV2D(-90,-120)));
    //Obstaculo* recb3 = new RecbTriangulo(25, new Triangulo(new PV2D(20,60), new PV2D(70,120), new PV2D(70,50)));

    //Obstaculo* circulo1R = new RecbCirculo(pelota->getRadio(), new Circulo(30, new PV2D(10,-100)));
    //Obstaculo* circulo2R = new RecbCirculo(pelota->getRadio(), new Circulo(30, new PV2D(-50,100)));

    Obstaculo* elipse1 = new Elipse(20, 30, new PV2D(0,100));

    //Obstaculo* elipse2 = new Elipse(30, 15, new PV2D(-100,100));

   //Obstaculo* elipse3 = new Elipse(30, 22, new PV2D(100,-100));


    listaObstaculos = new Lista<Obstaculo*>();
     //metemos las cuatro paredes en la lista de objetos
    //listaObstaculos->ponElem(triangulo1);
    //listaObstaculos->ponElem(triangulo2);
    //listaObstaculos->ponElem(triangulo3);
    //listaObstaculos->ponElem(triangulo4);
    //listaObstaculos->ponElem(circulo1);
    //listaObstaculos->ponElem(triangulo5);
    //listaObstaculos->ponElem(triangulo6);
    //listaObstaculos->ponElem(triangulo7);
    //listaObstaculos->ponElem(triangulo8);
    //listaObstaculos->ponElem(circulo2);


    //listaObstaculos->ponElem(recb1);
    //listaObstaculos->ponElem(recb2);
    //listaObstaculos->ponElem(recb3);


    //listaObstaculos->ponElem(circulo1R);
    //listaObstaculos->ponElem(circulo2R);

    //Paredes con recubrimiento
    listaObstaculos->ponElem(recb01);
    listaObstaculos->ponElem(recb02);
    listaObstaculos->ponElem(recb03);
    listaObstaculos->ponElem(recb04);
    listaObstaculos->ponElem(elipse1);
    //listaObstaculos->ponElem(elipse2);
    //listaObstaculos->ponElem(elipse3);
    //listaObstaculos->ponElem(circulo3);

}

//---------------------------------------------------------------------------

void __fastcall TGLForm2D::SetPixelFormatDescriptor()
{
    PIXELFORMATDESCRIPTOR pfd = {
            sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        32,
        0,0,0,0,0,0,
        0,0,
        0,0,0,0,0,
        32,
        0,
        0,
        PFD_MAIN_PLANE,
        0,
        0,0,0
    };
    int PixelFormat = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, PixelFormat, &pfd);
}

//---------------------------------------------------------------------------
//---------------------- FORM RESIZE ----------------------------------------
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::FormResize(TObject *Sender)
{

 //se actualiza puerto de vista y su radio
  if ((ClientWidth<=1)||(ClientHeight<=1)){
     ClientWidth=400;
     ClientHeight=400;
     RatioViewPort=1.0;
  }
  else RatioViewPort= (float)ClientWidth/(float)ClientHeight;
  
  glViewport(0,0,ClientWidth,ClientHeight);

  // se actualiza el volumen de vista
  // para que su radio coincida con ratioViewPort
  GLfloat RatioVolVista=xRight/yTop;

  if (RatioVolVista>=RatioViewPort){
     //Aumentamos yTop-yBot
     yTop= xRight/RatioViewPort;
     yBot=-yTop;
     }
  else{
     //Aumentamos xRight-xLeft
     xRight=RatioViewPort*yTop;
     xLeft=-xRight;
     }

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(xLeft,xRight, yBot,yTop);


  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  GLScene();

}

//---------------------------------------------------------------------------
//---------------------- DIBUJA OBJETOS -------------------------------------
//---------------------------------------------------------------------------

void dibulaObstaculo(){

    int numElem = listaObstaculos->numElem();
    Obstaculo* obstaculo;

    for(int i=0; i<numElem; i++){
        obstaculo = listaObstaculos->iesimo(i);
        obstaculo->pintaObstaculo();
    }
}

//---------------------------------------------------------------------------
//---------------------- GLScene --------------------------------------------
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::GLScene()
{
    glClear(GL_COLOR_BUFFER_BIT);

    dibulaObstaculo();
    
    pelota->dibujaPelota();

    glFlush();
    SwapBuffers(hdc);
}

//---------------------------------------------------------------------------
//---------------------- FORM PAINT -----------------------------------------
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::FormPaint(TObject *Sender)
{
    GLScene();
}

//---------------------------------------------------------------------------
//---------------------- FORM DESTROY ----------------------------------------
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::FormDestroy(TObject *Sender)
{
    ReleaseDC(Handle,hdc);
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hrc);  
    
    // eliminar objetos creados
    delete pelota;
    delete listaObstaculos;
}

//---------------------------------------------------------------------------
//-------------------------- FORM CLICK -------------------------------------
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::FormClick(TObject *Sender)
{
    //Timer1->Enabled = ! Timer1->Enabled;
    GLdouble tImpacto;
    Vector* normalImpacto;
    GLdouble mintImpacto=9999;
    Vector* minNormalImpacto;
    bool colision = false;
    Obstaculo* obstaculo;
    Obstaculo* minObstaculo;
    GLdouble modulo = pelota->getVector()->getModulo() + 0.01;

    //Para cada obstaculo
    for(int j=0; j< listaObstaculos->numElem(); j++){
        obstaculo = listaObstaculos->iesimo(j);

        //Miro si hay una colision
        colision |= obstaculo->hayColision(pelota->getCentro(), pelota->getVector(), tImpacto ,normalImpacto);

        //Nos quedamos con el mínimo impacto
        if(tImpacto > 0  && tImpacto<=modulo  && tImpacto < mintImpacto){
            mintImpacto = tImpacto;
            minNormalImpacto = normalImpacto;
            minObstaculo = obstaculo;
        }
    }

    //Descarto falsos positivos
    if(colision && mintImpacto > 0 && mintImpacto <=modulo ){
        //Mueve la pelota hasta tImpacto
        //ShowMessage("Positivo valido detectado");
        pelota->muevePelotaHasta(mintImpacto);
        pelota->cambiaSentidoRotacion();
        //Timer1->Enabled = false;
        minObstaculo->resuelveColision(minNormalImpacto, pelota->getCentro(), pelota->getVector());
    }
    else
        pelota->muevePelota();

    GLScene();
}

//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Timer1Timer(TObject *Sender)
{                          
    GLdouble tImpacto;
    Vector* normalImpacto;
    GLdouble mintImpacto=9999;
    Vector* minNormalImpacto;
    bool colision = false;
    Obstaculo* obstaculo;
    Obstaculo* minObstaculo;
    GLdouble modulo = pelota->getVector()->getModulo() + 0.01;

    //Para cada obstaculo
    for(int j=0; j< listaObstaculos->numElem(); j++){
        obstaculo = listaObstaculos->iesimo(j);

        //Miro si hay una colision
        colision |= obstaculo->hayColision(pelota->getCentro(), pelota->getVector(), tImpacto ,normalImpacto);

        //Nos quedamos con el mínimo impacto
        if(tImpacto > 0  && tImpacto<=modulo  && tImpacto < mintImpacto){
            mintImpacto = tImpacto;
            minNormalImpacto = normalImpacto;
            minObstaculo = obstaculo;
        }
    }

    //Descarto falsos positivos
    if(colision && mintImpacto > 0 && mintImpacto <=modulo ){
        //Mueve la pelota hasta tImpacto
        //ShowMessage("Positivo valido detectado");
        pelota->muevePelotaHasta(mintImpacto);
        pelota->cambiaSentidoRotacion();
        //Timer1->Enabled = false;
        minObstaculo->resuelveColision(minNormalImpacto, pelota->getCentro(), pelota->getVector());
    }
    else
        pelota->muevePelota();

    GLScene();

}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

#ifndef UFPH
#define UFPH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

#include <gl\gl.h>
#include <gl\glu.h>

//---------------------------------------------------------------------------
class TGLForm2D : public TForm
{
__published:	// IDE-managed Components
        TTimer *Timer1;
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall FormResize(TObject *Sender);
  void __fastcall FormPaint(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
        void __fastcall FormClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);

private:	// User declarations
 HDC hdc;
 HGLRC hrc;
 //definen el tamaño del volumen de vista
 GLfloat xLeft,xRight,yTop,yBot;
 //guarda el radio del puerto de vista
 GLfloat RatioViewPort;
 // métodos privados
 void __fastcall SetPixelFormatDescriptor();
 void __fastcall GLScene();

 public:		// User declarations
   __fastcall TGLForm2D(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGLForm2D *GLForm2D;
//---------------------------------------------------------------------------
#endif

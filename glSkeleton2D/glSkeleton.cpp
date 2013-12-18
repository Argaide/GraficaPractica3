//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("glSkeleton.res");
USEFORM("UFP.cpp", GLForm2D);
USEUNIT("Lapiz.cpp");
USEUNIT("Triangulo.cpp");
USEUNIT("Circulo.cpp");
USEUNIT("Obstaculo.cpp");
USEUNIT("Pelota.cpp");
USEUNIT("PV2D.cpp");
USEUNIT("Vector.cpp");
USEUNIT("Lista.cpp");
USEUNIT("RecbTriangulo.cpp");
USEUNIT("Elipse.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TGLForm2D), &GLForm2D);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------

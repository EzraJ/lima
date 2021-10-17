#include <iostream>
/*#include "args.hxx"
#include "core/terminal/terminal.hpp"
#include "core/engine/block.hpp"
#include "core/engine/scene.hpp"
#include "core/engine/layer.hpp"*/
#include "angelscript.h"
#include <scriptstdstring/scriptstdstring.h>
#include <scriptbuilder/scriptbuilder.h>
#include <cassert>


void print(const std::string& in){
    std::cout << in;
}

// Implement a simple message callback function
void MessageCallback(const asSMessageInfo *msg)
{
  const char *type = "ERR ";
  if( msg->type == asMSGTYPE_WARNING ) 
    type = "WARN";
  else if( msg->type == asMSGTYPE_INFORMATION ) 
    type = "INFO";
  printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
}

class myClass{
    public:
        myClass(int x){
            refCount = 1;
            std::cout << x << std::endl;
            std::cout << "myClass created\n";
        }
        ~myClass(){
            std::cout << "myClass destroyed\n";
        }

        void Addref(){
            refCount++;
        }

        void Release(){
            if(--refCount == 0){
                delete this;
            }
        }

        int refCount;
    private:


};

myClass* myClass_factory(int x){
    return new myClass(x);
}
myClass* myClass_factory(){
    return new myClass(0);
}

myClass* myClass_factory(int x, int y, int c){
    y = c;
    c = y;
    return new myClass(x);
}

int main(){



    // Create the script engine
    asIScriptEngine *engine = asCreateScriptEngine();
    
    int r = engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL); assert( r >= 0 );
    RegisterStdString(engine);
    


    engine->RegisterObjectType("myClass", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("myClass", asBEHAVE_FACTORY, "myClass@ f(int)", asFUNCTIONPR(myClass_factory, (int), myClass*), asCALL_CDECL);
    engine->RegisterObjectBehaviour("myClass", asBEHAVE_FACTORY, "myClass@ f()", asFUNCTIONPR(myClass_factory, (void), myClass*), asCALL_CDECL);
    engine->RegisterObjectBehaviour("myClass", asBEHAVE_FACTORY, "myClass@ f(int,int,int)", asFUNCTIONPR(myClass_factory, (int,int,int), myClass*), asCALL_CDECL);

    engine->RegisterObjectBehaviour("myClass", asBEHAVE_ADDREF, "void f()", asMETHOD(myClass,Addref), asCALL_THISCALL);
    engine->RegisterObjectBehaviour("myClass", asBEHAVE_RELEASE, "void f()", asMETHOD(myClass,Release), asCALL_THISCALL);

    //engine->RegisterObjectBehaviour("myClass", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Constructor), asCALL_CDECL_OBJLAST);
    //engine->RegisterObjectBehaviour("myClass", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Dtor), asCALL_CDECL_OBJLAST);

    engine->RegisterGlobalFunction("void print(const string& in)", asFunctionPtr(print), asCALL_CDECL);


    CScriptBuilder builder;
    r = builder.StartNewModule(engine, "MyModule"); 
    if( r < 0 ) 
    {
        // If the code fails here it is usually because there
        // is no more memory to allocate the module
        printf("Unrecoverable error while starting a new module.\n");
        return 0;
    }
    r = builder.AddSectionFromFile("main.as");
    //builder.AddSectionFromFile("main2.as");
    if( r < 0 )
    {
        // The builder wasn't able to load the file. Maybe the file
        // has been removed, or the wrong name was given, or some
        // preprocessing commands are incorrectly written.
        printf("Please correct the errors in the script and try again.\n");
        return 0;
    }
    r = builder.BuildModule();
    if( r < 0 )
    {
        // An error occurred. Instruct the script writer to fix the 
        // compilation errors that were listed in the output stream.
        printf("Please correct the errors in the script and try again.\n");
        return 0;
    }
    // Find the function that is to be called. 
    asIScriptModule *mod = engine->GetModule("MyModule");
    asIScriptFunction *func = mod->GetFunctionByDecl("void main()");
    if( func == 0 )
    {
        // The function couldn't be found. Instruct the script writer
        // to include the expected function in the script.
        printf("The script must have the function 'void main()'. Please add it and try again.\n");
        return 0;
    }
    
    // Create our context, prepare it, and then execute
    asIScriptContext *ctx = engine->CreateContext();
    ctx->Prepare(func);
    r = ctx->Execute();
    if( r != asEXECUTION_FINISHED )
    {
        // The execution didn't complete as expected. Determine what happened.
        if( r == asEXECUTION_EXCEPTION )
        {
            // An exception occurred, let the script writer know what happened so it can be corrected.
            printf("An exception '%s' occurred. Please correct the code and try again.\n", ctx->GetExceptionString());
        }
    }

    //std::cout << r << std::endl;
    //lima::terminal::terminal& myTerm = lima::terminal::terminal::getInstance();

    /*lima::core::engine::scene myScene(0);
    myScene.openManifest("test.man");
    myScene.openFile("test.level");

    auto level = myScene.sceneData();

    for(auto& e : level){
        for(auto& v: e){
            std::cout << v.getRender() <<"["<<v.getPos().x << ", " << v.getPos().y <<"]";
        }
        std::cout << "\n";
    }*/
    
    /*lima::terminal::terminal& myTerm = lima::terminal::terminal::getInstance();
    myTerm.enableRawMode();
    lima::core::engine::layer myLayer("scene_0.level", "scene_0.man", 0, lima::vector2(1,1));

    myLayer.addScene("scene_1.level", "scene_1.man", 1);

    lima::core::engine::scene myScene = myLayer.getVisibleScene();

    auto level = myScene.sceneData();
    myTerm.disableRawMode();
    for(auto& e : level){
        for(auto& v: e){
            std::cout << v.getRender();
            //std::cout << v.getRender() <<"["<<v.getPos().x << ", " << v.getPos().y <<"]";
        }
        std::cout << "\n";
    }

    sleep(1);
    myTerm.clearScreen();*/

    /*myTerm.enableRawMode();

    myTerm.print("Hello World!");
    myTerm.pPrint("Testing World!\n");
    myTerm.cPrint("Downhere, world!", lima::vector2(15, 15));
    myTerm.pPrint("\nABC0");
    myTerm.xPrint("X", lima::vector2(15, 15));

    myTerm.xPrint("ABCDEFG\rABC2\n", lima::vector2(15,17));
        myTerm.setCursorPosition(lima::vector2(15,20));
    

    myTerm.disableRawMode();*/

    
    return 0;
}
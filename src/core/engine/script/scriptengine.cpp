#include "core/engine/script/scriptEngine.hpp"
#include "core/engine/script/lima_func.hpp"

void MessageCallback(const asSMessageInfo *msg){
            // todo: make this spdlog compliant
            const char *type = "ERR ";
            if( msg->type == asMSGTYPE_WARNING ) 
                type = "WARN";
            else if( msg->type == asMSGTYPE_INFORMATION ) 
                type = "INFO";
            printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
        }



namespace lima{
    namespace script{
        scriptEngine::scriptEngine(){
            _engine = asCreateScriptEngine();
            RegisterStdString(_engine);
            _errcode = _engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL); assert(_errcode >= 0);
            


            // Global Functions
            //_errcode = _engine->RegisterObjectType("limaEngine", 0, asOBJ_REF);
            //_errcode = _engine->RegisterObjectMethod("limaEngine", "uint64 limaRegisterID(string,string,uint64,char)", asMETHOD(scriptEngine,RegisterIDType), asCALL_THISCALL); assert(_errcode >=0);
            //_errcode = _engine->RegisterObjectMethod("limaEngine" , "void print(const& string)", asMETHOD(scriptEngine, print), asCALL_THISCALL); assert(_errcode >= 0);


            _errcode = _engine->RegisterGlobalFunction("uint64 limaRegisterID(string,string,uint64,int8)", asFUNCTION(limaFunc::RegisterIDType), asCALL_CDECL); assert(_errcode >= 0);
            _errcode = _engine->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(limaFunc::print), asCALL_CDECL); assert(_errcode >= 0);
            

            CScriptBuilder* mainScript = new CScriptBuilder();
            _errcode = mainScript->StartNewModule(_engine, "InitModule");
            if(_errcode < 0){
                std::cout << "Unrecoverable error starting InitModule module.";
                raise(SIGINT);
                return;
            }
            _errcode = mainScript->AddSectionFromFile("game/init.as");
            if(_errcode < 0){
                std::cout << "Was unable to load game/init.as\n";
                raise(SIGINT);
                return;
            }

            _errcode = mainScript->BuildModule();
            if(_errcode < 0){
                std::cout << "Please fix errors in init.as\n";
                raise(SIGINT);
                return;
            }

            asIScriptModule* mod = _engine->GetModule("InitModule");
            asIScriptFunction* func = mod->GetFunctionByDecl("void main()");
            _ctx = _engine->CreateContext();
            _ctx->Prepare(func);
            _errcode = _ctx->Execute();
            if(_errcode != asEXECUTION_FINISHED){
                if(_errcode == asEXECUTION_EXCEPTION){
                    std::cout << "An exception \'" << _ctx->GetExceptionString() << " occured. Please correct the code and try again.\n";
                }
            }


        }



        scriptEngine::~scriptEngine(){
            
            _ctx->Release();
            _engine->ShutDownAndRelease();
        }


    }
}
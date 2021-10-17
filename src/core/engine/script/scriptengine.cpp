#include "core/engine/script/scriptEngine.hpp"

namespace lima{
    namespace script{
        scriptEngine::scriptEngine(){
            _engine = asCreateScriptEngine();
            RegisterStdString(_engine);
            _errcode = _engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL); assert(_errcode >= 0);
        }

        scriptEngine::~scriptEngine(){
            

            _engine->ShutDownAndRelease();
        }
    }
}
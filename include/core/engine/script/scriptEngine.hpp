#include "angelscript.h"
#include <scriptstdstring/scriptstdstring.h>
#include <scriptbuilder/scriptbuilder.h>
#include <cassert>

namespace lima{
    namespace script{

        void MessageCallback(const asSMessageInfo *msg, void *param){
            // todo: make this spdlog compliant
            const char *type = "ERR ";
            if( msg->type == asMSGTYPE_WARNING ) 
                type = "WARN";
            else if( msg->type == asMSGTYPE_INFORMATION ) 
                type = "INFO";
            printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
        }

        class scriptEngine{
            public:
                scriptEngine();
                ~scriptEngine();

            private:
                int _errcode;
                asIScriptEngine* _engine;

        };


    }
}
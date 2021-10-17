#pragma once

#include "core/engine/script/ids/id_type.hpp"
#include "angelscript.h"
#include <scriptstdstring/scriptstdstring.h>
#include <scriptbuilder/scriptbuilder.h>
#include <iostream>
#include <cassert>
#include <unistd.h>
#include <signal.h>

// Note: Because you can only register values and objects n stuff per engine,
// everything that we want to register, we register on the creation of the scriptengine.
// After that all we have to do is setup a run function to start the contexts, and have the game running from there.
// Before that though, lets have initialized stuff, like IDS!

namespace lima{
    namespace script{

        static std::map<uint64_t, IDType> _idTypes; // yucky global vars, I know.

        /*void MessageCallback(const asSMessageInfo *msg){
            // todo: make this spdlog compliant
            const char *type = "ERR ";
            if( msg->type == asMSGTYPE_WARNING ) 
                type = "WARN";
            else if( msg->type == asMSGTYPE_INFORMATION ) 
                type = "INFO";
            printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
        }*/

        class scriptEngine{
            public:
                scriptEngine();
                ~scriptEngine();

                //uint64_t RegisterIDType(std::string pre, std::string post, uint64_t _id, char render);

                


                IDType getID(uint64_t _id){
                    IDType retType(_idTypes[_id]);
                    return retType;
                }

            private:
                int _errcode;
                asIScriptEngine* _engine;
                asIScriptFunction* _scriptMain;
                std::vector<CScriptBuilder*> _modules; // Because each CScriptBuilder only handles one module, lets track them all in vectors
                asIScriptContext* _ctx; // context to run scripts
                asIScriptContext* _ctxGL; // For game logic
                //std::map<uint64_t, IDType> _idTypes;
        };


    }
}
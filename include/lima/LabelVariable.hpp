#pragma once
#include "lima/render.hpp"
#include "lima/Resizable.hpp"
#include "lima/Label.hpp"
#include "lima/Vector2.hpp"
#include "lima/LimaConcepts.hpp"

namespace lima{

    template<lima::ToStringable T>
    class LabelVariable : Resizable, Label{
        public:
            LabelVariable(render* renderIn, T* varIn, Vector2 posIn = Vector2(1, 1), Vector2 szIn = Vector2(1,1)){
                currentRender = renderIn;
                renderIn->AddResizable(this);
                renderIn->AddLabel(this);
                var = varIn;
                Resizable::Position = posIn;
                Resizable::Size = szIn;
                ResizeBeans();
            }

            ~LabelVariable(){
                currentRender->RemoveResizable(this);
                currentRender->RemoveLabel(this);
            }

            void ResizeBeans(){
                if (currentRender != nullptr) {
                    Resizable::beans.clear();
                    currentRender->getBeans(Resizable::beans, Position.x, Position.y, Size.x, Size.y);
                }
            }

            void Resize() override {
                if(var == nullptr) return;
                ResizeBeans();                
                for(auto& e : Resizable::beans){
                    e->setChar(' ');
                }
                value = std::to_string(*var);
                std::size_t count = 0;
                for(auto& e : Resizable::beans){
                    if(count < value.length()){
                       e->setChar(value[count]);
                    }
                    count++;
                }
            }

            void Process() override{
                if(var == nullptr) return;
                
                for(auto& e : Resizable::beans){
                    e->setChar(' ');
                }
                value = std::to_string(*var);
                std::size_t count = 0;
                for(auto& e : Resizable::beans){
                    if(count < value.length()){
                       e->setChar(value[count]);
                    }
                    count++;
                }
            }

        private:
            std::string value;
            lima::render* currentRender;
            T* var;
    };

}
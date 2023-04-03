#include <napi.h>
#include <map>
#include "lua.hpp"

class NodejsLua : public Napi::ObjectWrap<NodejsLua> {
    public:
        static Napi::Object Init(Napi::Env env, Napi::Object exports);
        NodejsLua(const Napi::CallbackInfo& info);
    
    private:
        lua_State* L;
        std::map<std::string, Napi::Function> functions;

        Napi::Value openLibs(const Napi::CallbackInfo& info);
        Napi::Value doString(const Napi::CallbackInfo& info);
        Napi::Value doFile(const Napi::CallbackInfo& info);

        Napi::Value pushString(const Napi::CallbackInfo& info);
        Napi::Value pushNumber(const Napi::CallbackInfo& info);
        Napi::Value pushBoolean(const Napi::CallbackInfo& info);
        Napi::Value pushNil(const Napi::CallbackInfo& info);

        Napi::Value setGlobal(const Napi::CallbackInfo& info);
        Napi::Value getGlobal(const Napi::CallbackInfo& info);
        
        Napi::Value getType(const Napi::CallbackInfo& info);
        Napi::Value toString(const Napi::CallbackInfo& info);
        Napi::Value toNumber(const Napi::CallbackInfo& info);
        Napi::Value toBoolean(const Napi::CallbackInfo& info);

        Napi::Value getTop(const Napi::CallbackInfo& info);
        Napi::Value setTop(const Napi::CallbackInfo& info);
        
        Napi::Value replace(const Napi::CallbackInfo& info);
        Napi::Value pop(const Napi::CallbackInfo& info);
        Napi::Value setField(const Napi::CallbackInfo& info);
        Napi::Value getField(const Napi::CallbackInfo& info);
        Napi::Value yield(const Napi::CallbackInfo& info);
        Napi::Value collectGarbage(const Napi::CallbackInfo& info);
        //Napi::Value registerFunction(const Napi::CallbackInfo& info);

        Napi::Value status(const Napi::CallbackInfo& info);
        Napi::Value resume(const Napi::CallbackInfo& info);
        Napi::Value close(const Napi::CallbackInfo& info);
};
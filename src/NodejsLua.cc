#include <node.h>
#include <napi.h>
#include <map>
#include "NodejsLua.h"
#include "lua.hpp"

using namespace v8;

void ThrowError(Napi::Env env, std::string content) {
    Napi::TypeError::New(env, content.c_str()).ThrowAsJavaScriptException();
}

NodejsLua::NodejsLua(const Napi::CallbackInfo& info) : Napi::ObjectWrap<NodejsLua>(info) {
    this->L = luaL_newstate();
}

Napi::Value NodejsLua::openLibs(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    luaL_openlibs(this->L);
    return env.Undefined();
}

Napi::Value NodejsLua::doString(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsString()) {
        ThrowError(env, "Invalid argument provided. Argument must be a string!");
        return env.Undefined();
    }

    luaL_dostring(this->L, info[0].As<Napi::String>().Utf8Value().c_str());
    return env.Undefined();
}

Napi::Value NodejsLua::doFile(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsString()) {
        ThrowError(env, "Invalid argument provided. Argument must be a string!");
        return env.Undefined();
    }

    luaL_dofile(this->L, info[0].As<Napi::String>().Utf8Value().c_str());
    return env.Undefined();
}

Napi::Value NodejsLua::pushString(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsString()) {
        ThrowError(env, "Invalid argument provided. Argument must be a string!");
        return env.Undefined();
    }

    lua_pushstring(this->L, info[0].As<Napi::String>().Utf8Value().c_str());
    return env.Undefined();
}

Napi::Value NodejsLua::pushNumber(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsNumber()) {
        ThrowError(env, "Invalid argument provided. Argument must be a number!");
        return env.Undefined();
    }

    lua_pushnumber(this->L, info[0].ToNumber());
    return env.Undefined();
}

Napi::Value NodejsLua::pushBoolean(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsBoolean()) {
        ThrowError(env, "Invalid argument provided. Argument must be a boolean!");
        return env.Undefined();
    }

    lua_pushboolean(this->L, info[0].ToBoolean().Value());
    return env.Undefined();
}

Napi::Value NodejsLua::pushNil(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    lua_pushnil(this->L);
    return env.Undefined();
}

Napi::Value NodejsLua::setGlobal(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsString()) {
        ThrowError(env, "Invalid argument provided. Argument must be a string!");
        return env.Undefined();
    }

    lua_setglobal(this->L, info[0].As<Napi::String>().Utf8Value().c_str());
    return env.Undefined();
}

Napi::Value NodejsLua::getGlobal(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsString()) {
        ThrowError(env, "Invalid argument provided. Argument must be a string!");
        return env.Undefined();
    }

    lua_getglobal(this->L, info[0].As<Napi::String>().Utf8Value().c_str());
    return env.Undefined();
}

Napi::Value NodejsLua::getType(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsNumber()) {
        ThrowError(env, "Invalid argument provided. Argument must be a number!");
        return env.Undefined();
    }

    return Napi::Number::New(env, lua_type(this->L, info[0].As<Napi::Number>().Int32Value()));
}

Napi::Value NodejsLua::toString(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsNumber()) {
        ThrowError(env, "Invalid argument provided. Argument must be a number!");
        return env.Undefined();
    }

    return Napi::String::New(env, lua_tostring(this->L, info[0].ToNumber()));
}

Napi::Value NodejsLua::toNumber(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsNumber()) {
        ThrowError(env, "Invalid argument provided. Argument must be a number!");
        return env.Undefined();
    }

    return Napi::Number::New(env, lua_tonumber(this->L, info[0].ToNumber()));
}

Napi::Value NodejsLua::toBoolean(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsNumber()) {
        ThrowError(env, "Invalid argument provided. Argument must be a number!");
        return env.Undefined();
    }

    return Napi::Number::New(env, lua_toboolean(this->L, info[0].ToNumber()));
}

Napi::Value NodejsLua::getTop(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    return Napi::Number::New(env, lua_gettop(this->L));
}

Napi::Value NodejsLua::setTop(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsNumber()) {
        ThrowError(env, "Invalid argument provided. Argument must be a number!");
        return env.Undefined();
    }

    lua_settop(this->L, info[0].ToNumber());

    return env.Undefined();
}

Napi::Value NodejsLua::replace(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsNumber()) {
        ThrowError(env, "Invalid argument provided. Argument must be a number!");
        return env.Undefined();
    }

    lua_replace(this->L, info[0].ToNumber());
    return env.Undefined();
}

Napi::Value NodejsLua::pop(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsNumber()) {
        ThrowError(env, "Invalid argument provided. Argument must be a number!");
        return env.Undefined();
    }

    lua_pop(this->L, info[0].ToNumber().Int32Value());
    return env.Undefined();
}

Napi::Value NodejsLua::setField(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 2 || !info[0].IsNumber() || !info[1].IsString()) {
        ThrowError(env, "Invalid argument provided. First argument must be a number and second must be a string!");
        return env.Undefined();
    }

    lua_setfield(this->L, info[0].ToNumber(), info[1].As<Napi::String>().Utf8Value().c_str());
    return env.Undefined();
}

Napi::Value NodejsLua::getField(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 2 || !info[0].IsNumber() || !info[1].IsString()) {
        ThrowError(env, "Invalid argument provided. First argument must be a number and second must be a string!");
        return env.Undefined();
    }

    lua_getfield(this->L, info[0].ToNumber().Int32Value(), info[1].As<Napi::String>().Utf8Value().c_str());

    return env.Undefined();
}

Napi::Value NodejsLua::yield(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsNumber()) {
        ThrowError(env, "Invalid argument provided. First argument must be a number!");
        return env.Undefined();
    }

    return Napi::Number::New(env, lua_yield(this->L, info[0].ToNumber()));
}

Napi::Value NodejsLua::collectGarbage(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber()) {
        ThrowError(env, "Invalid argument provided. First and second argument must be a number!");
        return env.Undefined();
    }

    return Napi::Number::New(env, lua_gc(this->L, info[0].ToNumber(), info[1].ToNumber()));
}

Napi::Value NodejsLua::status(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    return Napi::Number::New(env, lua_status(this->L));
}

Napi::Value NodejsLua::resume(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    lua_resume(this->L, info[0].ToNumber());
    return env.Undefined();
}

Napi::Value NodejsLua::close(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    lua_close(this->L);
    return env.Undefined();
}

Napi::Object NodejsLua::Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "NodejsLua", {
        InstanceMethod("openLibs", &NodejsLua::openLibs),
        InstanceMethod("doString", &NodejsLua::doString),
        InstanceMethod("doFile", &NodejsLua::doFile),

        InstanceMethod("pushString", &NodejsLua::pushString),
        InstanceMethod("pushNumber", &NodejsLua::pushNumber),
        InstanceMethod("pushBoolean", &NodejsLua::pushBoolean),
        InstanceMethod("pushNil", &NodejsLua::pushNil),

        InstanceMethod("setGlobal", &NodejsLua::setGlobal),
        InstanceMethod("getGlobal", &NodejsLua::getGlobal),

        InstanceMethod("getType", &NodejsLua::getType),
        InstanceMethod("toString", &NodejsLua::toString),
        InstanceMethod("toNumber", &NodejsLua::toNumber),
        InstanceMethod("toBoolean", &NodejsLua::toBoolean),

        InstanceMethod("getTop", &NodejsLua::getTop),
        InstanceMethod("setTop", &NodejsLua::setTop),

        InstanceMethod("replace", &NodejsLua::replace),
        InstanceMethod("pop", &NodejsLua::pop),
        InstanceMethod("setField", &NodejsLua::setField),
        InstanceMethod("getField", &NodejsLua::getField),
        InstanceMethod("yield", &NodejsLua::yield),
        InstanceMethod("collectGarbage", &NodejsLua::collectGarbage),
        //InstanceMethod("registerFunction", &NodejsLua::registerFunction),

        InstanceMethod("status", &NodejsLua::status),
        InstanceMethod("resume", &NodejsLua::resume),
        InstanceMethod("close", &NodejsLua::close),
    });

    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    exports.Set("NodejsLua", func);

    env.SetInstanceData<Napi::FunctionReference>(constructor);

    return exports;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    NodejsLua::Init(env, exports);
    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init);
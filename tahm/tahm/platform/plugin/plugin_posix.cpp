#include "../../tahm.h"
#include <dlfcn.h>

typedef void(*InitFunction)(Tahm*);

bool NativeScript::LoadSharedObject(const char *filepath)
{
    handle = dlopen(filepath, RTLD_NOW);
    if (handle == NULL)
    {
        fprintf(stderr, "%s\n", dlerror());
        return false;
    }

    return true;
}

bool NativeScript::Bind(Tahm *instance)
{
    bool result = false;
    InitFunction init = NULL;
    if ((init = (InitFunction)dlsym(handle, "init")) == NULL)
        return false;

    init(instance);

    result |= ((m_start = (StartMethod)dlsym(handle, "start")) != NULL);
    result |= ((m_keyPressed = (KeyPressedMethod)dlsym(handle, "keypressed")) != NULL);
    result |= ((m_update = (UpdateMethod)dlsym(handle, "update")) != NULL);
    result |= ((m_draw = (DrawMethod)dlsym(handle, "draw")) != NULL);
    
    return result;
}

bool NativeScript::Close()
{
    if (handle == NULL) return false;
    if (dlclose(handle) != 0)
    {
        fprintf(stderr, "%s\n", dlerror());
        return false;
    }
    return true;
}

bool NativeScript::RunStart()
{
    if (m_start == NULL) return false;
    m_start();

    return true;
}

bool NativeScript::RunKeyPressed(Event event)
{
    if (m_keyPressed == NULL) return false;
    m_keyPressed(event);
    
    return true;
}

bool NativeScript::RunUpdate(float delta)
{
    if (m_update == NULL) return false;
    m_update(delta);

    return true;
}

bool NativeScript::RunDraw()
{
    if (m_draw == NULL) return false;
    m_draw();

    return true;
}
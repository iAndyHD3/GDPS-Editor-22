#include <dlfcn.h>
#include "blaze.h"
#include "cocos2d.h"
#include "EditorUIExt.h"


bool inEditor = false;


EditorUI *EditorUIExt::EditorUI_hk() {
    inEditor = true;
    return EditorUI_trp(this);
}

void EditorUIExt::EditorUIDest_hk() {
    inEditor = false;
    return EditorUIDest_trp(this);
}

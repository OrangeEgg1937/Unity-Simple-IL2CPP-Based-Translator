#ifndef DEMOAPP_IL2CPP_MANAGER_H
#define DEMOAPP_IL2CPP_MANAGER_H

#include <map>
#include "il2cpp_type.h"

struct il2cpp_helper_assembly {
    void *image;
    std::map<std::string, void *> class_map;
};

void il2cpp_manager_init();

extern std::map<std::string, il2cpp_helper_assembly> assembly_map;
extern std::map<void *, std::map<std::string, FieldInfo *>> class_field_map;

#endif //DEMOAPP_IL2CPP_MANAGER_H

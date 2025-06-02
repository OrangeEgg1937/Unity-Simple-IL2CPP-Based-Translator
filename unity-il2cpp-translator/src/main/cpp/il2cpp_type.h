#ifndef DEMOAPP_IL2CPP_TYPE_H
#define DEMOAPP_IL2CPP_TYPE_H

#include <stdint.h>

/**
 *  Ref: https://github.com/dreamanlan/il2cpp_ref/tree/09316fe508773b8ced098dae6147b44ee1f6516c/libil2cpp
 **/

typedef struct MethodInfo MethodInfo;

typedef void *Il2CppImage;
typedef char16_t Il2CppChar;
typedef void(*Il2CppMethodPointer)();
typedef void (*InvokerMethod)(Il2CppMethodPointer, const MethodInfo*, void*, void**, void*);
typedef const struct ___Il2CppMetadataMethodHandle* Il2CppMetadataMethodDefinitionHandle;
typedef const struct ___Il2CppMetadataGenericContainerHandle* Il2CppMetadataGenericContainerHandle;

typedef struct Il2CppObject {
    union {
        void *klass;
        void *vtable;
    };
    void *monitor;
} Il2CppObject;

// System.String
typedef struct Il2CppString
{
    Il2CppObject object;
    int32_t length;                             ///< Length of string *excluding* the trailing null (which is included in 'chars').
    Il2CppChar chars[0];
} Il2CppString;

typedef struct Il2CppAssemblyName {
    const char *name;
    const char *culture;
    const char *hash_value;
    const char *public_key;
    uint32_t hash_alg;
    int32_t hash_len;
    uint32_t flags;
    int32_t major;
    int32_t minor;
    int32_t build;
    int32_t revision;
    uint8_t *public_key_token;
} Il2CppAssemblyName;

typedef struct Il2CppAssembly {
    void *il2cpp_image;
    uint32_t token;
    int32_t referencedAssemblyStart;
    int32_t referencedAssemblyCount;
    Il2CppAssemblyName aname;
} Il2CppAssembly;

struct Il2CppType {
    void *data;
    unsigned int bits;
};

typedef struct FieldInfo {
    const char *name;
    const Il2CppType *type;
    void *il2CppClass_parent;
    int32_t offset; // If offset is -1, then it's thread static
    uint32_t token;
} FieldInfo;

typedef struct MethodInfo
{
    Il2CppMethodPointer methodPointer;
    Il2CppMethodPointer virtualMethodPointer;
    InvokerMethod invoker_method;
    const char* name;
    void *klass;
    const Il2CppType *return_type;
    const Il2CppType** parameters;

    union
    {
        const void* rgctx_data; /* is_inflated is true and is_generic is false, i.e. a generic instance method */
        Il2CppMetadataMethodDefinitionHandle methodMetadataHandle;
    };

    /* note, when is_generic == true and is_inflated == true the method represents an uninflated generic method on an inflated type. */
    union
    {
        const void* genericMethod; /* is_inflated is true */
        Il2CppMetadataGenericContainerHandle genericContainerHandle; /* is_inflated is false and is_generic is true */
    };

    uint32_t token;
    uint16_t flags;
    uint16_t iflags;
    uint16_t slot;
    uint8_t parameters_count;
    uint8_t is_generic : 1; /* true if method is a generic method definition */
    uint8_t is_inflated : 1; /* true if declaring_type is a generic instance or if method is a generic instance*/
    uint8_t wrapper_type : 1; /* always zero (MONO_WRAPPER_NONE) needed for the debugger */
    uint8_t has_full_generic_sharing_signature : 1;
    uint8_t is_unmanaged_callers_only : 1;
} MethodInfo;

typedef struct PropertyInfo {
    void *il2cpp_class_parent;
    const char *name;
    const MethodInfo *get;
    const MethodInfo *set;
    uint32_t attrs;
    uint32_t token;
} PropertyInfo;

typedef struct Il2CppClass
{
    // The following fields are always valid for a Il2CppClass structure
    const Il2CppImage* image;
    void* gc_desc;
    const char* name;
    const char* namespaze;
    Il2CppType byval_arg;
    Il2CppType this_arg;
    Il2CppClass* element_class;
    Il2CppClass* castClass;
    Il2CppClass* declaringType;
    Il2CppClass* parent;
    void *generic_class;
    const void* typeDefinition; // non-NULL for Il2CppClass's constructed from type defintions
    const void* interopData;
    Il2CppClass* klass; // hack to pretend we are a MonoVTable. Points to ourself
    // End always valid fields

    // The following fields need initialized before access. This can be done per field or as an aggregate via a call to Class::Init
    FieldInfo* fields; // Initialized in SetupFields
    const void* events; // Initialized in SetupEvents
    const PropertyInfo* properties; // Initialized in SetupProperties
    const MethodInfo** methods; // Initialized in SetupMethods
    Il2CppClass** nestedTypes; // Initialized in SetupNestedTypes
    Il2CppClass** implementedInterfaces; // Initialized in SetupInterfaces
    void* interfaceOffsets; // Initialized in Init
    void* static_fields; // Initialized in Init
    const void* rgctx_data; // Initialized in Init
    // used for fast parent checks
    Il2CppClass** typeHierarchy; // Initialized in SetupTypeHierachy
    // End initialization required fields

    uint32_t initializationExceptionGCHandle;

    uint32_t cctor_started;
    uint32_t cctor_finished;
    void* cctor_thread;

    // Remaining fields are always valid except where noted
    void* genericContainerIndex;
    uint32_t instance_size;
    uint32_t actualSize;
    uint32_t element_size;
    int32_t native_size;
    uint32_t static_fields_size;
    uint32_t thread_static_fields_size;
    int32_t thread_static_fields_offset;
    uint32_t flags;
    uint32_t token;

    uint16_t method_count; // lazily calculated for arrays, i.e. when rank > 0
    uint16_t property_count;
    uint16_t field_count;
    uint16_t event_count;
    uint16_t nested_type_count;
    uint16_t vtable_count; // lazily calculated for arrays, i.e. when rank > 0
    uint16_t interfaces_count;
    uint16_t interface_offsets_count; // lazily calculated for arrays, i.e. when rank > 0

    uint8_t typeHierarchyDepth; // Initialized in SetupTypeHierachy
    uint8_t genericRecursionDepth;
    uint8_t rank;
    uint8_t minimumAlignment; // Alignment of this type
    uint8_t naturalAligment; // Alignment of this type without accounting for packing
    uint8_t packingSize;

    // this is critical for performance of Class::InitFromCodegen. Equals to initialized && !has_initialization_error at all times.
    // Use Class::UpdateInitializedAndNoError to update
    uint8_t initialized_and_no_error : 1;

    uint8_t valuetype : 1;
    uint8_t initialized : 1;
    uint8_t enumtype : 1;
    uint8_t is_generic : 1;
    uint8_t has_references : 1;
    uint8_t init_pending : 1;
    uint8_t size_inited : 1;
    uint8_t has_finalize : 1;
    uint8_t has_cctor : 1;
    uint8_t is_blittable : 1;
    uint8_t is_import_or_windows_runtime : 1;
    uint8_t is_vtable_initialized : 1;
    uint8_t has_initialization_error : 1;
    void* vtable[0];
} Il2CppClass;

#endif //DEMOAPP_IL2CPP_TYPE_H

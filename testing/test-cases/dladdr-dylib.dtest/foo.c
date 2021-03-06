

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <dlfcn.h> 
#include <mach-o/dyld_priv.h>

extern void* __dso_handle;

int dylib_bar()
{
    return 2;
}

static int dylib_foo()
{
    return 3;
}

__attribute__((visibility("hidden"))) int dylib_hide()
{
    return 4;
}

// checks global symbol
static void verifybar()
{
    Dl_info info;
    if ( dladdr(&dylib_bar, &info) == 0 ) {
        printf("[FAIL] dladdr(&dylib_bar, xx) failed\n");
        exit(0);
    }
    if ( strcmp(info.dli_sname, "dylib_bar") != 0 ) {
        printf("[FAIL] dladdr()->dli_sname is \"%s\" instead of \"dylib_bar\"\n", info.dli_sname);
        exit(0);
    }
    if ( info.dli_saddr != &dylib_bar) {
        printf("[FAIL] dladdr()->dli_saddr is not &dylib_bar\n");
        exit(0);
    }
    if ( info.dli_fbase != &__dso_handle ) {
        printf("[FAIL] dladdr()->dli_fbase is not image that contains &dylib_bar\n");
        exit(0);
    }
}

// checks local symbol
static void verifyfoo()
{
    Dl_info info;
    if ( dladdr(&dylib_foo, &info) == 0 ) {
        printf("[FAIL] dladdr(&dylib_foo, xx) failed\n");
        exit(0);
    }
    if ( strcmp(info.dli_sname, "dylib_foo") != 0 ) {
        printf("[FAIL] dladdr()->dli_sname is \"%s\" instead of \"dylib_foo\"\n", info.dli_sname);
        exit(0);
    }
    if ( info.dli_saddr != &dylib_foo) {
        printf("[FAIL] dladdr()->dli_saddr is not &dylib_foo\n");
        exit(0);
    }
    if ( info.dli_fbase != &__dso_handle ) {
        printf("[FAIL] dladdr()->dli_fbase is not image that contains &dylib_foo\n");
        exit(0);
    }
}

// checks hidden symbol
static void verifyhide()
{
    Dl_info info;
    if ( dladdr(&dylib_hide, &info) == 0 ) {
        printf("[FAIL] dladdr(&dylib_hide, xx) failed\n");
        exit(0);
    }
    if ( strcmp(info.dli_sname, "dylib_hide") != 0 ) {
        printf("[FAIL] dladdr()->dli_sname is \"%s\" instead of \"dylib_hide\"\n", info.dli_sname);
        exit(0);
    }
    if ( info.dli_saddr != &dylib_hide) {
        printf("[FAIL] dladdr()->dli_saddr is not &dylib_hide\n");
        exit(0);
    }
    if ( info.dli_fbase != &__dso_handle ) {
        printf("[FAIL] dladdr()->dli_fbase is not image that contains &dylib_hide\n");
        exit(0);
    }
}


void verifyDylib()
{
    verifybar();
    verifyfoo();
    verifyhide();
}


/*
 * Copyright (c) 2017 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */



#ifndef __DYLD_APIS_H__
#define __DYLD_APIS_H__

#include <string.h>
#include <stdint.h>

#include "dlfcn.h"
#include "dyld_priv.h"


#define TEMP_HIDDEN __attribute__((visibility("hidden")))

namespace dyld3 {


uint32_t _dyld_image_count() TEMP_HIDDEN;

const mach_header* _dyld_get_image_header(uint32_t imageIndex) TEMP_HIDDEN;

intptr_t _dyld_get_image_slide(const mach_header* mh) TEMP_HIDDEN;

intptr_t _dyld_get_image_vmaddr_slide(uint32_t imageIndex) TEMP_HIDDEN;

const char* _dyld_get_image_name(uint32_t imageIndex) TEMP_HIDDEN;

int32_t NSVersionOfLinkTimeLibrary(const char* libraryName) TEMP_HIDDEN;

int32_t NSVersionOfRunTimeLibrary(const char* libraryName) TEMP_HIDDEN;

#if __WATCH_OS_VERSION_MIN_REQUIRED
uint32_t dyld_get_program_sdk_watch_os_version() TEMP_HIDDEN;

uint32_t dyld_get_program_min_watch_os_version() TEMP_HIDDEN;
#endif

#if TARGET_OS_BRIDGE
uint32_t dyld_get_program_sdk_bridge_os_version() TEMP_HIDDEN;

uint32_t dyld_get_program_min_bridge_os_version() TEMP_HIDDEN;
#endif


uint32_t dyld_get_sdk_version(const mach_header* mh) TEMP_HIDDEN;


uint32_t dyld_get_program_sdk_version() TEMP_HIDDEN;
uint32_t dyld_get_min_os_version(const mach_header* mh) TEMP_HIDDEN;

uint32_t dyld_get_program_min_os_version() TEMP_HIDDEN;


bool _dyld_get_image_uuid(const mach_header* mh, uuid_t uuid) TEMP_HIDDEN;

int _NSGetExecutablePath(char* buf, uint32_t* bufsize) TEMP_HIDDEN;

void _dyld_register_func_for_add_image(void (*func)(const mach_header *mh, intptr_t vmaddr_slide)) TEMP_HIDDEN;

void _dyld_register_func_for_remove_image(void (*func)(const mach_header *mh, intptr_t vmaddr_slide)) TEMP_HIDDEN;

void _dyld_objc_notify_register(_dyld_objc_notify_mapped    mapped,
                                _dyld_objc_notify_init      init,
                                _dyld_objc_notify_unmapped  unmapped) TEMP_HIDDEN;

const mach_header* dyld_image_header_containing_address(const void* addr) TEMP_HIDDEN;

const mach_header* _dyld_get_image_header_containing_address(const void* address) TEMP_HIDDEN;

bool _dyld_image_containing_address(const void* address) TEMP_HIDDEN;

const char* dyld_image_path_containing_address(const void* addr) TEMP_HIDDEN;

bool _dyld_is_memory_immutable(const void* addr, size_t length) TEMP_HIDDEN;


int dladdr(const void* addr, Dl_info* info) TEMP_HIDDEN;

char* dlerror() TEMP_HIDDEN;

int dlclose(void* handle) TEMP_HIDDEN;

void* dlopen(const char* path, int mode) TEMP_HIDDEN;

bool dlopen_preflight(const char* path) TEMP_HIDDEN;

void* dlsym(void* handle, const char* symbolName) TEMP_HIDDEN;

const struct dyld_all_image_infos* _dyld_get_all_image_infos() TEMP_HIDDEN;

bool dyld_shared_cache_some_image_overridden() TEMP_HIDDEN;

bool _dyld_get_shared_cache_uuid(uuid_t uuid) TEMP_HIDDEN;

const void* _dyld_get_shared_cache_range(size_t* length) TEMP_HIDDEN;

bool _dyld_find_unwind_sections(void* addr, dyld_unwind_sections* info) TEMP_HIDDEN;

bool dyld_process_is_restricted() TEMP_HIDDEN;

const char* dyld_shared_cache_file_path() TEMP_HIDDEN;

void dyld_dynamic_interpose(const mach_header* mh, const dyld_interpose_tuple array[], size_t count) TEMP_HIDDEN;

int dyld_shared_cache_find_iterate_text(const uuid_t cacheUuid, const char* extraSearchDirs[], void (^callback)(const dyld_shared_cache_dylib_text_info* info)) TEMP_HIDDEN;

int dyld_shared_cache_iterate_text(const uuid_t cacheUuid, void (^callback)(const dyld_shared_cache_dylib_text_info* info)) TEMP_HIDDEN;

void _dyld_fork_child() TEMP_HIDDEN;

// only in macOS and deprecated 
#if __MAC_OS_X_VERSION_MIN_REQUIRED
NSObjectFileImageReturnCode NSCreateObjectFileImageFromFile(const char* pathName, NSObjectFileImage *objectFileImage) TEMP_HIDDEN;
NSObjectFileImageReturnCode NSCreateObjectFileImageFromMemory(const void *address, size_t size, NSObjectFileImage *objectFileImage) TEMP_HIDDEN;
bool NSDestroyObjectFileImage(NSObjectFileImage objectFileImage) TEMP_HIDDEN;
uint32_t NSSymbolDefinitionCountInObjectFileImage(NSObjectFileImage objectFileImage) TEMP_HIDDEN;
const char*  NSSymbolDefinitionNameInObjectFileImage(NSObjectFileImage objectFileImage, uint32_t ordinal) TEMP_HIDDEN;
uint32_t NSSymbolReferenceCountInObjectFileImage(NSObjectFileImage objectFileImage) TEMP_HIDDEN;
const char*  NSSymbolReferenceNameInObjectFileImage(NSObjectFileImage objectFileImage, uint32_t ordinal, bool *tentative_definition) TEMP_HIDDEN;
bool NSIsSymbolDefinedInObjectFileImage(NSObjectFileImage objectFileImage, const char* symbolName) TEMP_HIDDEN;
void* NSGetSectionDataInObjectFileImage(NSObjectFileImage objectFileImage, const char* segmentName, const char* sectionName, size_t *size) TEMP_HIDDEN;
const char* NSNameOfModule(NSModule m) TEMP_HIDDEN;
const char* NSLibraryNameForModule(NSModule m) TEMP_HIDDEN;
NSModule NSLinkModule(NSObjectFileImage objectFileImage, const char* moduleName, uint32_t options) TEMP_HIDDEN;
bool NSUnLinkModule(NSModule module, uint32_t options) TEMP_HIDDEN;
bool NSIsSymbolNameDefined(const char* symbolName) TEMP_HIDDEN;
bool NSIsSymbolNameDefinedWithHint(const char* symbolName, const char* libraryNameHint) TEMP_HIDDEN;
bool NSIsSymbolNameDefinedInImage(const struct mach_header* image, const char* symbolName) TEMP_HIDDEN;
NSSymbol NSLookupAndBindSymbol(const char* symbolName) TEMP_HIDDEN;
NSSymbol NSLookupAndBindSymbolWithHint(const char* symbolName, const char* libraryNameHint) TEMP_HIDDEN;
NSSymbol NSLookupSymbolInModule(NSModule module, const char* symbolName) TEMP_HIDDEN;
NSSymbol NSLookupSymbolInImage(const struct mach_header* image, const char* symbolName, uint32_t options) TEMP_HIDDEN;
const char*  NSNameOfSymbol(NSSymbol symbol) TEMP_HIDDEN;
void* NSAddressOfSymbol(NSSymbol symbol) TEMP_HIDDEN;
NSModule NSModuleForSymbol(NSSymbol symbol) TEMP_HIDDEN;
void NSLinkEditError(NSLinkEditErrors *c, int *errorNumber, const char** fileName, const char** errorString) TEMP_HIDDEN;
bool  NSAddLibrary(const char* pathName) TEMP_HIDDEN;
bool NSAddLibraryWithSearching(const char* pathName) TEMP_HIDDEN;
const struct mach_header* NSAddImage(const char* image_name, uint32_t options) TEMP_HIDDEN;
void NSInstallLinkEditErrorHandlers(const NSLinkEditErrorHandlers *handlers) TEMP_HIDDEN;
bool _dyld_present(void) TEMP_HIDDEN;
bool _dyld_launched_prebound(void)   TEMP_HIDDEN;
bool _dyld_all_twolevel_modules_prebound(void) TEMP_HIDDEN;
bool _dyld_bind_fully_image_containing_address(const void* address)  TEMP_HIDDEN;
bool _dyld_image_containing_address(const void* address) TEMP_HIDDEN;
void _dyld_lookup_and_bind(const char* symbol_name, void **address, NSModule* module) TEMP_HIDDEN;
void _dyld_lookup_and_bind_with_hint(const char* symbol_name, const char* library_name_hint, void** address, NSModule* module) TEMP_HIDDEN;
void _dyld_lookup_and_bind_fully(const char* symbol_name, void** address, NSModule* module) TEMP_HIDDEN;
const struct mach_header*  _dyld_get_image_header_containing_address(const void* address) TEMP_HIDDEN;
#endif

} // namespace dyld3

#endif // __DYLD_APIS_H__



#pragma once

//I gave up on trying to make this work
//first sdl2 was too old
//then sdl2_image was too old
//then g++ was one version too old to support #include <format>
//then the png.h include threw 500 errors

//Good fucking luck i can't be bothered with this shit

// Well I managed to do it :p
// Things you can do by not using C++ in a C++ project :shrug:

#include "platform.h"

#include <cstdio>
#include <linux/limits.h>
#include <libgen.h>

void platformPreInit() {

}
void platformInit() {
	
}
void platformPostInit() {
	
}

void platformTrySaveImageFile(EventCallbackListener* caller) {}
void platformTryLoadImageFile(EventCallbackListener* caller) {}
void platformTrySaveOtherFile(EventCallbackListener* caller, std::vector<std::pair<std::string,std::string>> filetypes, std::string windowTitle, int evt_id) {}
void platformTryLoadOtherFile(EventCallbackListener* caller, std::string extension, std::string windowTitle) {}

void platformOpenFileLocation(PlatformNativePathString path) {}

FILE* platformOpenFile(PlatformNativePathString path, PlatformNativePathString mode) {
    FILE* ret = fopen(path.c_str(), mode.c_str());
    return ret;
}

Layer* platformGetImageFromClipboard() {
    return NULL;
}

PlatformNativePathString platformExecutableDirLocation() {
    char* path = new char[PATH_MAX];
    auto len = readlink("/proc/self/exe", path, PATH_MAX);
    if (len == -1) {
        perror("failed to get exe dir");
        exit(1);
    }
    char* dir = dirname(path);
    return std::string(dir);
}

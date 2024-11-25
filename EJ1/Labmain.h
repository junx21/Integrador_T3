#ifndef LABMAIN_H
#define LABMAIN_H


#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>

using namespace std;

struct ColorConsole
{
    static const char* fg_blue;
    static const char* bg_white;
};

struct ConsoleBox
{
    void new_text();
    void set_text(const string &text);
};

extern ConsoleBox* consoleBox;

// Funciones para cargar scripts
void load_script(const char* filename, bool show_script = false);
void load_script();


#endif //LABMAIN_H
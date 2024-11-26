#include <iostream>
#include <string>
#include <cstdio>



struct ColorConsole
{
    static constexpr auto fg_blue = "\033[34m";
    static constexpr auto bg_white = "\033[47m";
};

struct ConsoleBox
{
    void new_text() {/*...*/}
    void set_text(const std::string &text) { std::cout << text << std::endl; }
};

ConsoleBox *consoleBox = new ConsoleBox; // suponemos que ya está inicializado

void load_script(const char* filename, bool show_script = false)
{
    std::string script;
    FILE* f = nullptr;
    try
    {
        f = fopen(filename, "rb");
        if (!f)
        {
            std::cerr << "error de apertura de " << filename << std::endl;
            return;
        }

        int c;
        char buf[4001];
        while ((c = fread(buf, 1, 4000, f)) > 0)
        {
            buf[c] = 0;
            script.append(buf);
        }
        fclose(f);
        f = nullptr;

        if (show_script)
        {
            std::cout << ColorConsole::fg_blue << ColorConsole::bg_white;
            std::cout << script << std::endl;
        }
        consoleBox->new_text();
        consoleBox->set_text(script);
    }
    catch (...)
    {
        std::cerr << "error durante la lectura del archivo" <<std:: endl;
        if(f)
            fclose(f);
    }
}

void load_script()
{
    char filename[500];
    printf("Archivo: ");
    scanf("%499s", filename);
    load_script(filename, true);
}
#include <NGINE.hxx>
#include <cstdlib>

int main(void) try {

    Ngine::Window wnd(1280, 720, (char*)"Linux Ngine Test App");

    while(true) {
        if(const auto ecode = wnd.ProcessMessage())
            return *ecode;
    }

    return EXIT_SUCCESS;
} catch(const Ngine::Exception& e) {
    printf("%s", e.what());
}
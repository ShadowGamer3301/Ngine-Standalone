#include <NGINE.hxx>

int main(void) try {
	Ngine::Window wnd(1280, 720, (char*)"x");

	while (true)
	{
		// process all messages pending, but to not block for new messages
		if (const auto ecode = Ngine::Window::ProcessMessage())
		{
			// if return optional has value, means we're quitting so return exit code
			return *ecode;
		}
		// execute the game logic
	}
}
catch (const Ngine::Exception& e) {
	printf("%s", e.what());
}
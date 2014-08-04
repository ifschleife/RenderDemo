#include "renderdemo.h"

#include <QtWidgets/QApplication>


#if defined(_WIN32) && defined(_DEBUG)
#include <Windows.h>
#include <io.h>
#include <fcntl.h>

// maximum mumber of lines the output console should have
static const WORD MAX_CONSOLE_LINES = 500;

void redirect_io_to_console()
// code from http://dslweb.nwnexus.com/~ast/dload/guicon.htm
{
	int hConHandle = 0;
	long lStdHandle = 0;
	CONSOLE_SCREEN_BUFFER_INFO coninfo = CONSOLE_SCREEN_BUFFER_INFO();
	FILE* fp = nullptr;

	// allocate a console for this app
	AllocConsole();

	// set the screen buffer to be big enough to let us scroll text
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),	&coninfo);
	coninfo.dwSize.Y = MAX_CONSOLE_LINES;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),	coninfo.dwSize);

	// redirect unbuffered STDOUT to the console
	lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen(hConHandle, "w");
	*stdout = *fp;
	setvbuf(stdout, nullptr, _IONBF, 0);

	// redirect unbuffered STDIN to the console
	lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen(hConHandle, "r");
	*stdin = *fp;
	setvbuf(stdin, nullptr, _IONBF, 0);

	// redirect unbuffered STDERR to the console
	lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "w" );
	*stderr = *fp;
	setvbuf(stderr, nullptr, _IONBF, 0);

	// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog
	// point to console as well
	std::ios::sync_with_stdio();
}

#endif


int main(int argc, char *argv[])
{
#if defined(_WIN32) && defined(_DEBUG)
	redirect_io_to_console();
#endif

	QApplication a(argc, argv);

	MainWindow window;
	window.show();

	return a.exec();
}

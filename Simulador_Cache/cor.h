#pragma once
#include <Windows.h>

#define CBLUE cor.set(text_color::BLUE | text_color::BRIGHT);
#define CLBLUE cor.set(text_color::BLUE2 | text_color::BRIGHT);
#define CRED cor.set(text_color::RED | text_color::BRIGHT);
#define CGREEN cor.set(text_color::GREEN | text_color::BRIGHT);
#define CGRAY cor.set(text_color::GRAY | text_color::BRIGHT);
#define CPINK cor.set(text_color::PINK | text_color::BRIGHT);
#define CYELLOW cor.set(text_color::YELLOW | text_color::BRIGHT);
#define CPADRAO cor.reset();

class text_color {
public:
	enum {
		RED = FOREGROUND_RED,
		GREEN = FOREGROUND_GREEN,
		BLUE = FOREGROUND_BLUE,
		WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
		GRAY = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		PINK = FOREGROUND_RED | FOREGROUND_BLUE,
		YELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
		BLUE2 = FOREGROUND_GREEN | FOREGROUND_BLUE,
		BLACK = 0,
		BRIGHT = FOREGROUND_INTENSITY,
	};
public:
	text_color() {
		hout = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	string set(int color) {
		SetConsoleTextAttribute(hout, color);
		return "";
	}
	void reset() {
		SetConsoleTextAttribute(hout, GRAY);
	}
private:
	HANDLE hout;
};

//text_color con;
/*
con.set(text_color::GREEN | text_color::BRIGHT);
cout << "Hello, world!" << endl;
con.set(text_color::RED | text_color::BRIGHT);
cout << "I'm bright red!" << endl;
con.reset();
cout << "Back to normal" << endl;
//cin.get();


string  a = "cao";
//con.set("GREEN");
con.set(text_color::GRAY | text_color::BRIGHT);
cout << "Back to normal" << a << endl;
con.set(text_color::BLUE | text_color::BRIGHT);
cout << "Back to normal" << a << endl;
con.set(text_color::RED | text_color::BRIGHT);
cout << "Back to normal" << endl;
con.set(text_color::GREEN | text_color::BRIGHT);
cout << "Back to normal" << endl;
con.set(2);
cout << "Back to normal" << endl;
con.set(text_color::GRAY | text_color::BRIGHT);
cout << "Back to normal" << endl;

*/

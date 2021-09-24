#include"customFunctions.h"


HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
string timeNow() {
	// current date/time based on current system
	//time_t now = time(0);
	//tm* ltm = localtime(&now);

	struct tm ltm;
	time_t now = time(0);
	localtime_s(&ltm, &now);

	// print various components of tm structure.
	string returnVal = "", tm;
	for (int x : {ltm.tm_mday,ltm.tm_mon+1}) {
		tm = to_string(x);
		if (tm.size() < 2) tm = "0" + tm;
		returnVal += tm + "/";
	}returnVal += to_string(1900 + ltm.tm_year);
	return returnVal;
}

void color(int color) {
    SetConsoleTextAttribute(out_handle, color);
}

void gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(out_handle, c);
}
void ShowConsoleCursor(bool visible) {
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = visible;
    SetConsoleCursorInfo(out_handle, &info);
}

void setFontSize() {
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   // Width of each character in the font
    cfi.dwFontSize.Y = 20;                  // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_BOLD;
    // std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

    //std::cout << "Font: Consolas, Size: 18\n";
}
void setConsoleDimen() {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions

    MoveWindow(console, r.left, r.top, 800, 720, TRUE); // 800 width, 100 height
}
COORD get_console_cursor()
{
    COORD cordinator;

    CONSOLE_SCREEN_BUFFER_INFO console_cursor;
    GetConsoleScreenBufferInfo(out_handle, &console_cursor);
    cordinator.X = console_cursor.dwCursorPosition.X;
    cordinator.Y = console_cursor.dwCursorPosition.Y;

    return cordinator;
}
void set_console_cursor(const COORD& cordinator)
{
    SetConsoleCursorPosition(out_handle, cordinator);
}

void get_local_time(struct tm& ltm)
{
    time_t now = time(0);
    localtime_s(&ltm, &now);
}
void get_date_now(std::string& returnval)
{
    struct tm ltm;
    get_local_time(ltm);

    std::string months[] = { "nanimo", "January", "February",
                            "March", "April", "May", "June", "July", "August",
                            "September", "October", "November", "December" };
    returnval = "";
    std::string tm;
    tm += std::to_string(ltm.tm_mday);
    if (tm.size() < 2)
        tm = "0" + tm;

    returnval += tm + " " + months[ltm.tm_mon + 1] + ", ";
    returnval += std::to_string(1900 + ltm.tm_year);
}

void get_time_now(std::string& returnval)
{
    struct tm ltm;
    get_local_time(ltm);

    int hour_now = ltm.tm_hour;
    std::string pm_am = " AM";
    if (hour_now >= 12)
    {
        pm_am = " PM", hour_now -= 12;
        if (!hour_now)
            hour_now = 12;
    }
    else if (!hour_now)
        hour_now = 12;

    returnval = std::to_string(hour_now) + ':';
    (ltm.tm_min < 10) ? returnval += "0" + std::to_string(ltm.tm_min) : returnval += std::to_string(ltm.tm_min);
    if(ltm.tm_sec <10) returnval +=":0"+ to_string(ltm.tm_sec);
    else returnval += ":" + to_string(ltm.tm_sec);
    returnval += pm_am;
}
string formatted_time_date() {
    string tim, date;
    get_date_now(date);
    get_time_now(tim);
    return "     "+tim + "\n     " + date;
}
#include <windows.h>
#include <shellapi.h>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include "json.hpp" //downloaded from https://github.com/nlohmann/json/releases/latest

using json = nlohmann::json;
using namespace std;

HWND hListDontFollowMe, hListIDontFollow;

set<string> loadFollowers(const string &path)
{
    set<string> followers;
    ifstream f(path);
    if (!f.is_open())
        return followers;
    json data;
    f >> data;
    for (auto &el : data)
        if (!el["string_list_data"].empty())
            followers.insert(el["string_list_data"][0]["value"].get<string>());
    return followers;
}

set<string> loadFollowing(const string &path)
{
    set<string> following;
    ifstream f(path);
    if (!f.is_open())
        return following;
    json data;
    f >> data;
    for (auto &el : data["relationships_following"])
        following.insert(el["title"].get<string>());
    return following;
}

void openProfile(const string &username)
{
    string url = "https://www.instagram.com/" + username;
    ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
    {
        ifstream f1("followers.json");
        ifstream f2("following.json");
        if (!f1.is_open() || !f2.is_open())
        {
            MessageBox(hwnd,
                       "Missing JSON files!\n\nPlease make sure 'followers.json' and 'following.json' are in the same folder as this program.",
                       "InstaChecker - Error",
                       MB_ICONWARNING | MB_OK);
            PostQuitMessage(0);
            return 0;
        }
        CreateWindow("STATIC", "Don't follow you back:", WS_VISIBLE | WS_CHILD,
                     10, 10, 220, 20, hwnd, NULL, NULL, NULL);
        hListDontFollowMe = CreateWindow("LISTBOX", NULL, WS_VISIBLE | WS_CHILD | WS_VSCROLL | LBS_NOTIFY,
                                         10, 30, 260, 400, hwnd, (HMENU)1, NULL, NULL);

        CreateWindow("STATIC", "You don't follow back:", WS_VISIBLE | WS_CHILD,
                     300, 10, 250, 20, hwnd, NULL, NULL, NULL);
        hListIDontFollow = CreateWindow("LISTBOX", NULL, WS_VISIBLE | WS_CHILD | WS_VSCROLL | LBS_NOTIFY,
                                        300, 30, 260, 400, hwnd, (HMENU)2, NULL, NULL);

        CreateWindow("STATIC",
                     "Double click username in the list to open Instagram profile in browser",
                     WS_VISIBLE | WS_CHILD | SS_CENTER,
                     10, 460, 550, 20, hwnd, NULL, NULL, NULL);

        HFONT hFont = CreateFont(
            18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
            ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_SWISS, "Segoe UI");

        SendMessage(hListDontFollowMe, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(hListIDontFollow, WM_SETFONT, (WPARAM)hFont, TRUE);

        auto followers = loadFollowers("followers.json");
        auto following = loadFollowing("following.json");

        set<string> notFollowingBack, youDontFollowBack;

        for (auto &user : following)
            if (!followers.count(user))
                notFollowingBack.insert(user);
        for (auto &user : followers)
            if (!following.count(user))
                youDontFollowBack.insert(user);

        for (auto &u : notFollowingBack)
            SendMessage(hListDontFollowMe, LB_ADDSTRING, 0, (LPARAM)u.c_str());
        for (auto &u : youDontFollowBack)
            SendMessage(hListIDontFollow, LB_ADDSTRING, 0, (LPARAM)u.c_str());

        break;
    }
    case WM_COMMAND:
        if (HIWORD(wParam) == LBN_DBLCLK)
        {
            HWND list = (HWND)lParam;
            int idx = SendMessage(list, LB_GETCURSEL, 0, 0);
            if (idx != LB_ERR)
            {
                char name[256];
                SendMessage(list, LB_GETTEXT, idx, (LPARAM)name);
                openProfile(name);
            }
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = "InstaCheckerClass";
    RegisterClass(&wc);

    HWND hwnd = CreateWindow("InstaCheckerClass", "InstaChecker",
                             WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                             100, 100, 600, 520, NULL, NULL, hInst, NULL);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

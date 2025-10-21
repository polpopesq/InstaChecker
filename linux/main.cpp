#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include "../json.hpp"  // Header-only library: https://github.com/nlohmann/json

using json = nlohmann::json;
using namespace std;

// Load followers from followers.json
set<string> loadFollowers(const string &path) {
    set<string> followers;
    ifstream f(path);
    if (!f.is_open()) return followers;
    json data;
    f >> data;
    for (auto &el : data)
        if (!el["string_list_data"].empty())
            followers.insert(el["string_list_data"][0]["value"].get<string>());
    return followers;
}

// Load following from following.json
set<string> loadFollowing(const string &path) {
    set<string> following;
    ifstream f(path);
    if (!f.is_open()) return following;
    json data;
    f >> data;
    for (auto &el : data["relationships_following"])
        following.insert(el["title"].get<string>());
    return following;
}

// Cross-platform open in browser
void openProfile(const string &username) {
    string url = "https://www.instagram.com/" + username;
#ifdef _WIN32
    string cmd = "start " + url;
#elif __APPLE__
    string cmd = "open " + url;
#else
    string cmd = "xdg-open " + url;
#endif
    system(cmd.c_str());
}

// Utility: pretty section header
void section(const string &title) {
    cout << "\033[1;36m\n" << title << "\033[0m\n";
    cout << "---------------------------------------------\n";
}

int main() {
    system("clear");

    cout << "====================================\n";
    cout << "     🌐 InstaChecker (C++ CLI)      \n";
    cout << "====================================\n";

    auto followers = loadFollowers("followers.json");
    auto following = loadFollowing("following.json");

    if (followers.empty() && following.empty()) {
        cerr << "❌ Missing or invalid JSON files!\n";
        return 1;
    }

    set<string> notFollowingBack, youDontFollowBack;

    for (auto &u : following)
        if (!followers.count(u))
            notFollowingBack.insert(u);
    for (auto &u : followers)
        if (!following.count(u))
            youDontFollowBack.insert(u);

    section("eople who DON'T follow you back:");
    for (auto &u : notFollowingBack) cout << " • " << u << '\n';

    section("People YOU don't follow back:");
    for (auto &u : youDontFollowBack) cout << " • " << u << '\n';

    cout << "\nType a username to open their profile in your browser, or press Enter to exit:\n> ";
    string username;
    getline(cin, username);

    if (!username.empty()) {
        cout << "🔗 Opening " << username << " in browser...\n";
        openProfile(username);
    } else {
        cout << "Done.\n";
    }

    return 0;
}

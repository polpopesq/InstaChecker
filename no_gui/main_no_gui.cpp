#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include "../json.hpp" // https://github.com/nlohmann/json

using json = nlohmann::json;
using namespace std;

set<string> loadFollowers(const string &path)
{
    set<string> followers;
    ifstream f(path);
    if (!f.is_open())
    {
        cerr << "  Warning: Cannot open file '" << path << "'. Make sure it's in the same folder as the .exe\n";
        return followers;
    }
    json data;
    f >> data;
    for (auto &el : data)
    {
        if (!el["string_list_data"].empty())
            followers.insert(el["string_list_data"][0]["value"].get<string>());
    }
    return followers;
}

set<string> loadFollowing(const string &path)
{
    set<string> following;
    ifstream f(path);
    if (!f.is_open())
    {
        cerr << "  Warning: Cannot open file '" << path << "'. Make sure it's in the same folder as the .exe\n";
        return following;
    }
    json data;
    f >> data;
    for (auto &el : data["relationships_following"])
    {
        following.insert(el["title"].get<string>());
    }
    return following;
}

int main()
{
    cout << "Loading data...\n";

    set<string> followers = loadFollowers("followers.json");
    set<string> following = loadFollowing("following.json");

    // dacă lipsesc ambele fișiere sau sunt goale
    if (followers.empty() && following.empty())
    {
        cerr << "\n Error: Missing or invalid JSON files.\n";
        cerr << "Please place 'followers.json' and 'following.json' in the same folder as this executable.\n";
        cout << "\nPress Enter to exit...";
        cin.get();
        return 1;
    }

    set<string> notFollowingBack;
    set<string> youDontFollowBack;

    for (auto &user : following)
        if (!followers.count(user))
            notFollowingBack.insert(user);

    for (auto &user : followers)
        if (!following.count(user))
            youDontFollowBack.insert(user);

    cout << "\n============================================\n";
    cout << "People who DON'T follow you back:\n";
    cout << "============================================\n";
    for (auto &u : notFollowingBack)
        cout << " - " << u << endl;

    cout << "\n============================================\n";
    cout << "People YOU don't follow back:\n";
    cout << "============================================\n";
    for (auto &u : youDontFollowBack)
        cout << " - " << u << endl;

    cout << "\n Done.\n";
    cout << "\nPress Enter to exit...";
    cin.get();
    return 0;
}

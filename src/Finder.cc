#include "utils.hh"
#include "Finder.hh"
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

namespace ndatk {
    using namespace std;

    // Construct a Finder with colon delimited path string.
    Finder::Finder(const string& path) : path_list(parse_path(path)) {}

    // Set a Finder's search path to colon delimited path string.
    void Finder::set_path(const std::string& path)
    {
        path_list = parse_path(path);
    }

    // Return absolute path of first readable file with name in search path.
    string Finder::abs_path(const std::string& name) const
    {
        auto filepath = boost::filesystem::path(name);
        if (boost::filesystem::is_regular_file(filepath) && is_readable(filepath.string())) {
            return boost::filesystem::absolute(filepath).string();
        }

        for (const auto& p : path_list) {
            boost::filesystem::path f = boost::filesystem::path{ p } / name;

            if (is_readable(f.string()))
                return boost::filesystem::absolute(f).string();
        }
        return std::string{};          // readable name not found
    }

    // Return absolute path of first readable file with name in search path
    // starting with magic string.
    string Finder::abs_path(const std::string& name,
        const std::string& magic) const
    {
        auto fname = abs_path(name);
        if (!fname.empty() && file_starts_with(name, magic)) return fname;
        return std::string{};
    }

    // Convert search path to colon delimited string.
    string Finder::get_path(void) const
    {
        string s;
        for (const auto& p : path_list) {
            if (!s.empty()) {
#ifdef LINUX
                s += ":";
#else
                s += ";";
#endif
            }
            s += p;
        }
        return s;
    }

    // Parse colon delimited path string and return vector of elements.
    vector<string> Finder::parse_path(const string& path) const
    {
        vector<string> new_path;
        if (path.empty()) return new_path;
#ifdef LINUX
        vector<string> in_path(split(path, ':')); // tokenize path
#else
        vector<string> in_path(split(path, ';')); // tokenize path
#endif

        // Copy in_path to new_path, expanding CURRENT_PATH and ENVIRONMENT
        for (const auto& p : in_path) {
            if (p == "!!") {
                // insert CURRENT_PATH here
                new_path.insert(new_path.end(), path_list.begin(), path_list.end());
            }
            else if (boost::algorithm::starts_with(p, "$") ) {
                // insert ENVIRONMENT variable here
                auto env = get_env(p.substr(1));
                auto env_path = parse_path(env);
                new_path.insert(new_path.end(), env_path.begin(), env_path.end());
            }
            else {                  // insert value here
                new_path.push_back(p);
            }
        }
        return new_path;
    }
}

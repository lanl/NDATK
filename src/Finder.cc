#include "utils.hh"
#include "Finder.hh"
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

namespace ndatk {
#if _WIN32
    const char Finder::PATH_SEP = ';';
#else
    const char Finder::PATH_SEP = ':';
#endif
    using namespace std;
    namespace fs = boost::filesystem;

    // Construct a Finder with colon delimited path string.
    Finder::Finder(const string& path) : path_list(parse_path(path)) {}

    // Set a Finder's search path to colon delimited path string.
    void Finder::set_path(const std::string& path)
    {
        path_list = parse_path(path);
    }

    // Construct a Finder with array of paths.
    Finder::Finder(const PathList_t& paths) { set_path(paths);  }
    // Set a Finder's search path an array of paths.
    void Finder::set_path(const PathList_t& paths)
    {
        for (const auto& p : paths) {
            if (fs::exists(p)) path_list.push_back(p);
        }
    }

    // Return absolute path of first readable file with name in search path.
    string Finder::abs_path(const std::string& name) const
    {
        auto filepath = fs::path(name);
        if (fs::is_regular_file(filepath) && is_readable(filepath.string())) {
            return fs::absolute(filepath).string();
        }

        for (const auto& p : path_list) {
            auto f = fs::path{ p } / name;

            if (is_readable(f.string())) {
                return fs::absolute(f).string();
            }
        }
        return std::string{};          // readable name not found
    }

    // Return absolute path of first readable file with name in search path
    // starting with magic string.
    string Finder::abs_path(const std::string& name,
                            const std::string& magic) const
    {
        auto fname = abs_path(name);
        return file_starts_with(fname, magic) ? fname : std::string{};
    }

    // Convert search path to colon delimited string.
    string Finder::get_path(void) const
    {
        string s;
        for (const auto& p : path_list) {
            if (!s.empty()) {
                s += PATH_SEP;
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
        vector<string> in_path(split(path, PATH_SEP)); // tokenize path

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

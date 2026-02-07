#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <string>
#include <fstream>
#include <stdexcept>
#include <ctime>
#include <iomanip>
#include <sstream>

#if defined(_WIN32)
  #include <direct.h>
  #include <sys/stat.h>
#else
  #include <sys/stat.h>
  #include <sys/types.h>
  #include <unistd.h>
#endif

namespace files {

    inline std::string now_iso() {
        std::time_t t = std::time(nullptr);
        std::tm tm = *std::localtime(&t);

        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    inline std::string parent_dir(const std::string& path) {
        size_t pos = path.find_last_of("/\\");
        return (pos == std::string::npos) ? "" : path.substr(0, pos);
    }

    inline bool mkdir_once(const std::string& dir) {
        if (dir.empty()) return true;
    #if defined(_WIN32)
        struct _stat st{};
        if (_stat(dir.c_str(), &st) == 0 && (st.st_mode & _S_IFDIR)) return true;
        return _mkdir(dir.c_str()) == 0;
    #else
        struct stat st{};
        if (stat(dir.c_str(), &st) == 0 && S_ISDIR(st.st_mode)) return true;
        return ::mkdir(dir.c_str(), 0755) == 0;
    #endif
    }

    inline void ensure_dir(const std::string& dir) {
        if (dir.empty()) return;

        std::string path;
        for (char c : dir) {
            if (c == '/' || c == '\\') {
                mkdir_once(path);
            }
            path.push_back(c);
        }
        mkdir_once(path);
    }

    inline void write_text(const std::string& path, const std::string& content) {
        ensure_dir(parent_dir(path));

        std::ofstream out(path);
        if (!out) throw std::runtime_error("Failed to open: " + path);

        out << content;
    }
}
#endif

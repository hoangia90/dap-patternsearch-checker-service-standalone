#include "util.h"
// #include <filesystem>
#include "seal_api.h"

// #include <boost/filesystem.hpp>

// namespace fs = boost::filesystem;

bool sub_str_exist(const std::string &str, const std::string &sub_str)
{
    return str.size() >= sub_str.size() && str.compare(str.size() - sub_str.size(), sub_str.size(), sub_str) == 0;
}

// int findNumberOfFilesInDirectory(const std::string &path)
// {
//   auto dirIter = std::filesystem::directory_iterator(path);
//   int fileCount = std::count_if(
//       begin(dirIter),
//       end(dirIter),
//       [](auto &entry) { return entry.is_regular_file(); });
//   return fileCount;
// }

// int findNumberOfFilesInDirectory(std::string &path, std::string &ext)
// int findNumberOfFilesInDirectory(const std::string &path)
// {
//     // namespace fs = boost::filesystem;

//     std::string ext = ".ct";

// 	fs::path Path(path);
// 	int Nb_ext = 0;
// 	fs::directory_iterator end_iter; // Default constructor for an iterator is the end iterator

// 	for (fs::directory_iterator iter(Path); iter != end_iter; ++iter)
// 		if (iter->path().extension() == ext)
// 			++Nb_ext;

// 	return Nb_ext;
// }

// c++ 17
// std::vector<std::string> get_directories(const std::string &s)
// {
//     std::vector<std::string> r;
//     for(auto& p : std::filesystem::recursive_directory_iterator(s))
//         if (p.is_directory())
//             r.push_back(p.path().string());
//     return r;
// }

// struct path_leaf_string
// {
//     std::string operator()(const boost::filesystem::directory_entry &entry) const
//     {
//         return entry.path().leaf().string();
//     }
// };

// std::vector<std::string> get_directories(const std::string &s)
// {
//     std::vector<std::string> v;

//     boost::filesystem::path p(s);
//     boost::filesystem::directory_iterator start(p);
//     boost::filesystem::directory_iterator end;
//     std::transform(start, end, std::back_inserter(v), path_leaf_string());
    
//     std::copy(v.begin(), v.end(),
//     std::ostream_iterator<std::string>(std::cout, "\n"));

//     return v;
// }

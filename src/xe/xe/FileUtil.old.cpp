//
//#include "FileUtil.hpp"
//
//#include <fstream>
//#include <cassert>
//
//namespace xe {
//    std::string FileUtil::loadTextFile(const std::string &file) {
//        std::fstream fs;
//
//        fs.open(file.c_str(), std::ios_base::in);
//        
//        assert(fs.is_open());
//        
//        fs.seekg(0, std::ios_base::end);
//        
//        std::string content;
//        
//        content.resize(static_cast<int>(fs.tellg()) + 1);
//        
//        fs.seekg(0);
//        fs.read((char*) content.c_str(), content.size());
//
//        return content;
//    }
//}

#pragma once


#ifndef STRUCTURED_GL_FILE_UTILS_HPP
#define STRUCTURED_GL_FILE_UTILS_HPP

#include <iostream>
#include <fstream>
#include <string>

namespace PBRPipeline::Utils::FileUtils {

    static std::string readFile(const std::string& filePath) {
        std::ifstream file(filePath);
        std::string fileContents;
        if (!file.is_open()) {
            return fileContents;
        }
        while (file.good()) {
            file >> fileContents;
        }
        file.close();
        return fileContents;
    }

}

#endif // STRUCTURED_GL_FILE_UTILS_HPP

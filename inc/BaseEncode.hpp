// Include Guard
#ifndef BASEENCODE_HPP
#define BASEENCODE_HPP

#include <vector>
#include <string>

namespace BaseEncode {

    /**
     * This library implements the various types of base encoding 
     * described in [RFC4648](https://tools.ietf.org/html/rfc4648)
     */
    
    std::string Base16Encode(const std::vector<char>& data);
    std::string Base16Encode(const std::string& data);
    std::string Base16Decode(const std::vector<char>& data);
    std::string Base16Decode(const std::string& data);

    std::string Base32Encode(const std::vector<char>& data);
    std::string Base32Encode(const std::string& data);
    std::string Base32Decode(const std::vector<char>& data);
    std::string Base32Decode(const std::string& data);

    std::string Base64Encode(const std::vector<char>& data);
    std::string Base64Encode(const std::string& data);
    std::string Base64Decode(const std::vector<char>& data);
    std::string Base64Decode(const std::string& data);

}

#endif // BASEENCODE_HPP
#include <BaseEncode.hpp>

#include <iostream>

namespace BaseEncode {

    // Base16 Dictionary, used to encode/decode messages
    const std::string base16Dictionary = "0123456789ABCDEF";

    // Base32 Dictionary, used to encode/decode messages
    const std::string base32Dictionary = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";

    // Base64 Dictionary, used to encode/decode messages
    const std::string base64Dictionary = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    std::string Base16Encode(const std::vector<char>& data){
        std::vector<char> output;

        for (char ch : data) {
            int firstIndex = (ch & 0xF0) >> 4;
            int secondIndex = ch & 0x0F;

            output.push_back(base16Dictionary[firstIndex]);
            output.push_back(base16Dictionary[secondIndex]);
        }

        return std::string(output.begin(), output.end());
    }

    std::string Base16Encode(const std::string& data){
        return Base16Encode(std::vector<char>(data.begin(), data.end()));
    }

    std::string Base16Decode(const std::vector<char>& data){
        std::vector<char> output;

        for (int i = 0; i < data.size(); i += 2) {
            char decodedChar = (base16Dictionary.find(data.at(i)) << 4) + base16Dictionary.find(data.at(i+1));

            output.push_back(decodedChar);
        }

        return std::string(output.begin(), output.end());
    }

    std::string Base16Decode(const std::string& data){
        return Base16Decode(std::vector<char>(data.begin(), data.end()));
    }

    std::string Base32Encode(const std::vector<char>& data){
        std::vector<char> output;

        int dataSize = data.size();
        int indexes[8] = {0};

        // In case we have 5 bytes to convert, we only convert 5 - (5 % 3) = 3
        // because the other 2 will be converted in the switch case

        /*
            abcedfgh ijklmnop qrstuvxz ABCDEFGH IJKLMNOP

            abced fghij klmno pqrst uvxzA BCDEF GHIJK LMNOP

        */

        for (int i = 0; i < (dataSize - dataSize % 5); i += 5) {
            indexes[0] = (data.at(i) & 0xF8) >> 3;
            indexes[1] = ((data.at(i) & 0x07) << 2) + ((data.at(i+1) & 0xC0) >> 6);
            indexes[2] = ((data.at(i+1) & 0x3E) >> 1);
            indexes[3] = ((data.at(i+1) & 0x01) << 4) + ((data.at(i+2) & 0xF0) >> 4);
            indexes[4] = ((data.at(i+2) & 0x0F) << 1) + ((data.at(i+3) & 0x80) >> 7); 
            indexes[5] = ((data.at(i+3) & 0x7C) >> 2);
            indexes[6] = ((data.at(i+3) & 0x03) << 3) + ((data.at(i+4) & 0xE0) >> 5);
            indexes[7] = ((data.at(i+4) & 0x1F));

            for (int i = 0; i < 8; i++) {
                output.push_back(base32Dictionary[indexes[i]]);
            }
        }

        int padding = 0;

        switch (data.size() % 5) {
            case 4:
                indexes[0] = (data.at(dataSize - 4) & 0xF8) >> 3;
                indexes[1] = ((data.at(dataSize - 4) & 0x07) << 2) + ((data.at(dataSize - 3) & 0xC0) >> 6);
                indexes[2] = ((data.at(dataSize - 3) & 0x3E) >> 1);
                indexes[3] = ((data.at(dataSize - 3) & 0x01) << 4) + ((data.at(dataSize - 2) & 0xF0) >> 4);
                indexes[4] = ((data.at(dataSize - 2) & 0x0F) << 1) + ((data.at(dataSize - 1) & 0x80) >> 7); 
                indexes[5] = ((data.at(dataSize - 1) & 0x7C) >> 2);
                indexes[6] = ((data.at(dataSize - 1) & 0x03) << 3);

                for (int i = 0; i < 7; i++) {
                    output.push_back(base32Dictionary[indexes[i]]);
                }
                padding = 1;
                break;

            case 3:
                indexes[0] = (data.at(dataSize - 3) & 0xF8) >> 3;
                indexes[1] = ((data.at(dataSize - 3) & 0x07) << 2) + ((data.at(dataSize - 2) & 0xC0) >> 6);
                indexes[2] = ((data.at(dataSize - 2) & 0x3E) >> 1);
                indexes[3] = ((data.at(dataSize - 2) & 0x01) << 4) + ((data.at(dataSize - 1) & 0xF0) >> 4);
                indexes[4] = ((data.at(dataSize - 1) & 0x0F) << 1);

                for (int i = 0; i < 5; i++) {
                    output.push_back(base32Dictionary[indexes[i]]);
                }
                padding = 3;
                break;

            case 2:
                indexes[0] = (data.at(dataSize - 2) & 0xF8) >> 3;
                indexes[1] = ((data.at(dataSize - 2) & 0x07) << 2) + ((data.at(dataSize - 1) & 0xC0) >> 6);
                indexes[2] = ((data.at(dataSize - 1) & 0x3E) >> 1);
                indexes[3] = ((data.at(dataSize - 1) & 0x01) << 4);

                for (int i = 0; i < 4; i++) {
                    output.push_back(base32Dictionary[indexes[i]]);
                }
                padding = 4;
                break;

            case 1:
                indexes[0] = (data.at(dataSize - 1) & 0xF8) >> 3;
                indexes[1] = ((data.at(dataSize - 1) & 0x07) << 2);

                for (int i = 0; i < 2; i++) {
                    output.push_back(base32Dictionary[indexes[i]]);
                }
                padding = 6;
                break;
            case 0:
            default:
                break;
        }


        for (int i = 0; i < padding; i++) output.push_back('=');

        return std::string(output.begin(), output.end());
    }

    std::string Base32Encode(const std::string& data){
        return Base32Encode(std::vector<char>(data.begin(), data.end()));
    }

    std::string Base32Decode(const std::vector<char>& data){
        std::vector<char> output;

        int indexes[8] = {0};
        char chars[5] = {0};
        int dataSize = data.size();

        for (int i = 0; i < dataSize; i += 8) {

            for (int j = i, aux = 0; j < (i+8); j++, aux++) {
                indexes[aux] = (data.at(j) != '=' ? base32Dictionary.find(data.at(j)) : 0);
            }

            chars[0] = (indexes[0] << 3) + ((indexes[1] & 0x1C) >> 2);
            chars[1] = ((indexes[1] & 0x03) << 6) + ((indexes[2] & 0x1F) << 1) + ((indexes[3] & 0x10) >> 4);
            chars[2] = ((indexes[3] & 0x0F) << 4) + ((indexes[4] & 0x1E) >> 1);
            chars[3] = ((indexes[4] & 0x01) << 7) + (indexes[5] << 2) + ((indexes[6] & 0x18) >> 3);
            chars[4] = ((indexes[6] & 0x07) << 5) + indexes[7];

            for (int i = 0; i < 5; i++) 
                if (chars[i] != 0)
                    output.push_back(chars[i]);

        }

        return std::string(output.begin(), output.end());
    }

    std::string Base32Decode(const std::string& data){
        return Base32Decode(std::vector<char>(data.begin(), data.end()));
    }

    std::string Base64Encode(const std::vector<char>& data){
        std::vector<char> output;

        int dataSize = data.size();
        int indexes[4] = {0};

        // In case we have 5 bytes to convert, we only convert 5 - (5 % 3) = 3
        // because the other 2 will be converted in the switch case
        for (int i = 0; i < (dataSize - dataSize % 3); i += 3) {
            indexes[0] = (data.at(i) & 0xFC) >> 2;
            indexes[1] = ((data.at(i) & 0x03) << 4) + ((data.at(i+1) & 0xF0) >> 4);
            indexes[2] = ((data.at(i+1) & 0x0F) << 2) + ((data.at(i+2) & 0xC0) >> 6);
            indexes[3] = data.at(i+2) & 0x3F;

            for (int i = 0; i < 4; i++) {
                output.push_back(base64Dictionary[indexes[i]]);
            }
        }

        switch (data.size() % 3) {
            case 2:
                indexes[0] = (data.at(dataSize - 2) & 0xFC) >> 2;
                indexes[1] = ((data.at(dataSize - 2) & 0x03) << 4) + ((data.at(dataSize - 1) & 0xF0) >> 4);
                indexes[2] = ((data.at(dataSize - 1) & 0x0F) << 2);

                for (int i = 0; i < 3; i++) {
                    output.push_back(base64Dictionary[indexes[i]]);
                }

                output.push_back('=');
                break;

            case 1:
                indexes[0] = (data.at(dataSize - 1) & 0xFC) >> 2;
                indexes[1] = (data.at(dataSize - 1) & 0x03) << 4;

                for (int i = 0; i < 2; i++) {
                    output.push_back(base64Dictionary[indexes[i]]);
                }

                output.push_back('=');
                output.push_back('=');
                break;

            case 0:
            default:
                break;
        }

        return std::string(output.begin(), output.end());
    }

    std::string Base64Encode(const std::string& data){
        return Base64Encode(std::vector<char>(data.begin(), data.end()));
    }

    std::string Base64Decode(const std::vector<char>& data){
        std::vector<char> output;

        int indexes[4] = {0};
        char chars[3] = {0};

        int dataSize = data.size();

        for (int i = 0; i < dataSize; i += 4) {

            for (int j = i, aux = 0; j < (i+4); j++, aux++) {
                indexes[aux] = (data.at(j) != '=' ? base64Dictionary.find(data.at(j)) : 0);
            }

            chars[0] = (indexes[0] << 2) + ((indexes[1] & 0x30) >> 4);
            chars[1] = ((indexes[1] & 0x0F) << 4) + ((indexes[2] & 0x3C) >> 2);
            chars[2] = ((indexes[2] & 0x03) << 6) + (indexes[3] & 0x3F);

            for (int i = 0; i < 3; i++) 
                if (chars[i] != 0)
                    output.push_back(chars[i]);
        }
        
        return std::string(output.begin(), output.end());
    }

    std::string Base64Decode(const std::string& data){
        return Base64Decode(std::vector<char>(data.begin(), data.end()));
    }

}
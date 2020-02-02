#include <BaseEncode.hpp>

#include <iostream>

#define ESCAPE_SEQUENCE "\x1b"
#define RESET_TEXT ESCAPE_SEQUENCE"[0m"
#define RED_TEXT ESCAPE_SEQUENCE"[31m"
#define YELLOW_TEXT ESCAPE_SEQUENCE"[33m"
#define GREEN_TEXT ESCAPE_SEQUENCE"[92m"

struct BaseEncodeCase {
    std::string parameter;
    std::string result;
};

bool TestBase(const char * testName, std::vector<BaseEncodeCase> testCases, std::string(*fncToTest)(const std::string&)) {
    std::cout << YELLOW_TEXT "\nBEGAN " RESET_TEXT << testName << std::endl;

    for (auto testCase : testCases) {
        std::string b64 = fncToTest(testCase.parameter);

        if (b64.compare(testCase.result)) {
            std::cout << RED_TEXT "[FAILED!]" << RESET_TEXT " Test Case ( " << testCase.parameter << " )\n";
            std::cout << "Got: " << b64 << "\nExp: " << testCase.result << std::endl;
            std::cout << "Testing terminated!\n\n";
            return false;
        } else {
            std::cout << GREEN_TEXT "[PASSED!]" << RESET_TEXT " Test Case ( " << testCase.parameter << " ) Passed!\n";
        }
    }

    return true;
}

int main(int argc, char ** argv) {

    std::vector<BaseEncodeCase> testCasesB16Encoding =  {
        {"", ""},
        {"f", "66"},
        {"fo", "666F"},
        {"foo", "666F6F"},
        {"foob", "666F6F62"},
        {"fooba", "666F6F6261"},
        {"foobar", "666F6F626172"},
        {"Esta frase serve de teste para verificar se as funcoes funcionam corretamente", "457374612066726173652073657276652064652074657374652070617261207665726966696361722073652061732066756E636F65732066756E63696F6E616D20636F72726574616D656E7465"}
    };

    std::vector<BaseEncodeCase> testCasesB16Decoding =  {
        {"", ""},
        {"66", "f"},
        {"666F", "fo"},
        {"666F6F", "foo"},
        {"666F6F62", "foob"},
        {"666F6F6261", "fooba"},
        {"666F6F626172", "foobar"},
        {"457374612066726173652073657276652064652074657374652070617261207665726966696361722073652061732066756E636F65732066756E63696F6E616D20636F72726574616D656E7465", "Esta frase serve de teste para verificar se as funcoes funcionam corretamente"}
    };

    std::vector<BaseEncodeCase> testCasesB32Encoding =  {
        {"", ""},
        {"f", "MY======"},
        {"fo", "MZXQ===="},
        {"foo", "MZXW6==="},
        {"foob", "MZXW6YQ="},
        {"fooba", "MZXW6YTB"},
        {"foobar", "MZXW6YTBOI======"},
        {"Esta frase serve de teste para verificar se as funcoes funcionam corretamente", "IVZXIYJAMZZGC43FEBZWK4TWMUQGIZJAORSXG5DFEBYGC4TBEB3GK4TJMZUWGYLSEBZWKIDBOMQGM5LOMNXWK4ZAMZ2W4Y3JN5XGC3JAMNXXE4TFORQW2ZLOORSQ===="}
    };

    std::vector<BaseEncodeCase> testCasesB32Decoding =  {
        {"", ""},
        {"MY======", "f"},
        {"MZXQ====", "fo"},
        {"MZXW6===", "foo"},
        {"MZXW6YQ=", "foob"},
        {"MZXW6YTB", "fooba"},
        {"MZXW6YTBOI======", "foobar"},
        {"IVZXIYJAMZZGC43FEBZWK4TWMUQGIZJAORSXG5DFEBYGC4TBEB3GK4TJMZUWGYLSEBZWKIDBOMQGM5LOMNXWK4ZAMZ2W4Y3JN5XGC3JAMNXXE4TFORQW2ZLOORSQ====", "Esta frase serve de teste para verificar se as funcoes funcionam corretamente"}
    };

    std::vector<BaseEncodeCase> testCasesB64Encoding =  {
        {"", ""},
        {"f", "Zg=="},
        {"fo", "Zm8="},
        {"foo", "Zm9v"},
        {"foob", "Zm9vYg=="},
        {"fooba", "Zm9vYmE="},
        {"foobar", "Zm9vYmFy"},
        {"Esta frase serve de teste para verificar se as funcoes funcionam corretamente", "RXN0YSBmcmFzZSBzZXJ2ZSBkZSB0ZXN0ZSBwYXJhIHZlcmlmaWNhciBzZSBhcyBmdW5jb2VzIGZ1bmNpb25hbSBjb3JyZXRhbWVudGU="}
    };

    std::vector<BaseEncodeCase> testCasesB64Decoding =  {
        {"", ""},
        {"Zg==", "f"},
        {"Zm8=", "fo"},
        {"Zm9v", "foo"},
        {"Zm9vYg==", "foob"},
        {"Zm9vYmE=", "fooba"},
        {"Zm9vYmFy", "foobar"},
        {"RXN0YSBmcmFzZSBzZXJ2ZSBkZSB0ZXN0ZSBwYXJhIHZlcmlmaWNhciBzZSBhcyBmdW5jb2VzIGZ1bmNpb25hbSBjb3JyZXRhbWVudGU=", "Esta frase serve de teste para verificar se as funcoes funcionam corretamente"}
    };

    if (TestBase("Base16Encoding", testCasesB16Encoding, BaseEncode::Base16Encode) != true) return -1;
    if (TestBase("Base16Decoding", testCasesB16Decoding, BaseEncode::Base16Decode) != true) return -1;
    if (TestBase("Base32Encoding", testCasesB32Encoding, BaseEncode::Base32Encode) != true) return -1;
    if (TestBase("Base32Decoding", testCasesB32Decoding, BaseEncode::Base32Decode) != true) return -1;
    if (TestBase("Base64Encoding", testCasesB64Encoding, BaseEncode::Base64Encode) != true) return -1;
    if (TestBase("Base64Decoding", testCasesB64Decoding, BaseEncode::Base64Decode) != true) return -1;

    std::cout << GREEN_TEXT "\nAll tests finished with success\n\n" RESET_TEXT;

}
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <sys/types.h>

#include "crypto.hpp"

namespace fs = std::filesystem;
using namespace encrypt;
class ModelEncryptTest : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}
  const std::string commitCode = "bea4f2fe1875e12e5abcb4d40f85d99262ed3054";
};

TEST_F(ModelEncryptTest, EncryptDecrypt) {
  auto nonEncFile = "data/image.png";
  auto encFile = "image.png.enc";
  ASSERT_TRUE(fs::exists(nonEncFile));

  auto cryptoConfig = Crypto::deriveKeyFromCommit(commitCode);
  Crypto crypto(cryptoConfig);

  std::vector<u_char> encData;

  // encrypt file
  crypto.encryptFile(nonEncFile, encFile);

  // decrypt file
  std::vector<u_char> decData;
  crypto.decryptData(encFile, decData);

  // compare
  std::vector<u_char> nonEncData;
  std::ifstream ifs(nonEncFile, std::ios::binary);
  if (!ifs.is_open()) {
    FAIL() << "Failed to open file: " << nonEncFile;
  }
  ifs.seekg(0, std::ios::end);
  nonEncData.resize(ifs.tellg());
  ifs.seekg(0);
  ifs.read((char *)nonEncData.data(), nonEncData.size());
  ASSERT_EQ(decData.size(), nonEncData.size());
  ASSERT_EQ(memcmp(decData.data(), nonEncData.data(), decData.size()), 0);
  fs::remove(encFile);
}

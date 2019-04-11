#include <iostream>
#include <string>
#include <cryptlib.h>
#include <files.h>
#include <hex.h>

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <md5.h>

int main()
{
	const std::string key{ "yzbqklnj" };
	std::string hex_digest{};

	using namespace CryptoPP;
	HexEncoder to_string_encoder(new StringSink(hex_digest));
	HexEncoder to_file_encoder(new FileSink(std::cout));

	Weak::MD5 hash;
	std::string digest;
	digest.resize(hash.DigestSize());

	std::string msg;
	unsigned suffix{ 1 };

	unsigned fiveZeroesIteration{ 0 };
	unsigned sixZeroesIteration{ 0 };
	do
	{
		msg = key + std::to_string(suffix);
		hex_digest = "";

		hash.Update((const byte*)msg.data(), msg.size());
		hash.Final((byte*)&digest[0]);

		StringSource(digest, true, new Redirector(to_string_encoder));

		//std::cout << msg << " -> " << hex_digest << std::endl;

		if (!fiveZeroesIteration && hex_digest.find("00000") == 0)
		{
			fiveZeroesIteration = suffix;
			std::cout << suffix << ": " << msg << " -> " << hex_digest << std::endl;
		}
		if (!sixZeroesIteration && hex_digest.find("000000") == 0)
		{
			sixZeroesIteration = suffix;
			std::cout << suffix << ": " << msg << " -> " << hex_digest << std::endl;
		}
		++suffix;
		if (suffix % 1000 == 0)
		{
			std::cout << suffix << std::endl;
		}
	} while (!fiveZeroesIteration || !sixZeroesIteration);

	std::cout << "First time five zeroes appear at iteration " << fiveZeroesIteration << std::endl;
	std::cout << "First time six zeroes appear at iteration " << sixZeroesIteration << std::endl;

	std::cin.get();
}
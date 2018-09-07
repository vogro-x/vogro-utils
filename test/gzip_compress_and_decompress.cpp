#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
using namespace std;
// namespace io = boost::iostreams;
std::string string_compress_encode(const std::string &data) {
  std::stringstream compressed;
  std::stringstream original;
  original << data;
  boost::iostreams::filtering_streambuf<boost::iostreams::input> out;
  out.push(boost::iostreams::zlib_compressor());
  out.push(original);
  boost::iostreams::copy(out, compressed);

  /**need to encode here **/
  // std::string compressed_encoded =
  //     base64_encode(reinterpret_cast<const unsigned char *>(compressed.c_str()),
  //                   compressed.length());

  // return compressed_encoded.str();
  return compressed.str();
}

std::string string_decompress_decode(const std::string &data) {
  std::stringstream compressed_encoded;
  std::stringstream decompressed;
  compressed_encoded << data;

  /** first decode  then decompress **/
  // std::string compressed = base64_decode(compressed_encoded);

  boost::iostreams::filtering_streambuf<boost::iostreams::input> in;
  in.push(boost::iostreams::zlib_decompressor());
  // in.push(compressed);
  in.push(data);
  boost::iostreams::copy(in, decompressed);
  return decompressed.str();
}

//文件压缩,当文件太小的时候，压缩之后反而文件还变大了
//只有当文件比较大的时候压缩，文件才会变小
int main(int argc, char *argv[]) {

  std::ifstream inStream("/home/andrew/音乐/vogro-utils/test/tt.aa",
                         std::ios_base::in);
  std::ofstream outStream("/home/andrew/音乐/vogro-utils/test/tt.aa.gz",
                          std::ios_base::out);
  boost::iostreams::filtering_streambuf<boost::iostreams::input> in;
  in.push(boost::iostreams::gzip_compressor());
  in.push(inStream);
  boost::iostreams::copy(in, outStream);
  inStream.close();
  outStream.close();
  return EXIT_SUCCESS;
}

/*
#ifndef __GZIP_H__
#define __GZIP_H__

#include <sstream>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>

class Gzip {
public:
	static std::string compress(const std::string& data)
	{
		namespace bio = boost::iostreams;

		std::stringstream compressed;
		std::stringstream origin(data);

		bio::filtering_streambuf<bio::input> out;
		out.push(bio::gzip_compressor(bio::gzip_params(bio::gzip::best_compression)));
		out.push(origin);
		bio::copy(out, compressed);

		return compressed.str();
	}

	static std::string decompress(const std::string& data)
	{
		namespace bio = boost::iostreams;

		std::stringstream compressed(data);
		std::stringstream decompressed;

		bio::filtering_streambuf<bio::input> out;
		out.push(bio::gzip_decompressor());
		out.push(compressed);
		bio::copy(out, decompressed);

		return decompressed.str();
	}
};

#endif // __GZIP_H__



*/
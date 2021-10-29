#include "CompressionZlib.h"
#include <string.h>



long CompressionZlib::ZipString(std::string string, char* out) {
    int len = (int)string.length();
    long bytes = CompressionZlib::Zip(string.c_str(), out, len);
    return bytes;
}

long CompressionZlib::Zip(const char* inData, char* outData, unsigned int lenIn) {
    z_stream defstream;
    defstream.zalloc = Z_NULL;
    defstream.zfree = Z_NULL;
    defstream.opaque = Z_NULL;

    defstream.avail_in = (uInt)lenIn; // size of input, string + terminator
    defstream.next_in = (Bytef*)inData;
   // defstream.avail_out = (uInt)len; // size of output
    defstream.next_out = (Bytef*)outData; // output char array

    // the actual compression work.
    deflateInit(&defstream, Z_BEST_COMPRESSION);
    deflate(&defstream, Z_FINISH);
    deflateEnd(&defstream);
    return defstream.total_out;
}

long CompressionZlib::UnZip(const char* inData, char* outData, unsigned int lenIn) {
    z_stream infstream;
    infstream.zalloc = Z_NULL;
    infstream.zfree = Z_NULL;
    infstream.opaque = Z_NULL;

    infstream.avail_in = (uInt)lenIn; // size of input
    infstream.next_in = (Bytef*)inData; // input char array
    //infstream.avail_out = (uInt)len * 5; // size of output
    infstream.next_out = (Bytef*)outData; // output char array

    // the actual DE-compression work.
    inflateInit(&infstream);
    inflate(&infstream, Z_NO_FLUSH);
    inflateEnd(&infstream);

    return infstream.total_out;
}

extern "C"
{
#include "zlib.h"
}
#include <cstring>
#include <iostream>

static const int input_buffer_size = 1024*1024;

/// Read a gzip compressed file and append the contents to a container.
/**
 * Designed for reading raw vector dumps from GNU Octave's fwrite() which have
 * been gzipped from the command line to save space.
 * Should theoretically work with structs or other complex types as ScalarType
 * but untested with anything other than scalars (float, double).
 */
template<typename ScalarType, typename VectorType = std::vector<ScalarType> >
bool read_gzip(const char* filename, VectorType& dst)
{
    gzFile file;
    file = gzopen(filename, "r");
    if (!file)
    {
        std::cerr << "gzopen of " << filename << " failed: " << std::strerror(errno) << std::endl;
        return false;
    }

    while (true)
    {
        int err;
        int bytes_read;
        unsigned char buffer[input_buffer_size];
        bytes_read = gzread(file, buffer, input_buffer_size);
        ScalarType* data = reinterpret_cast<ScalarType*>(&buffer[0]);
        unsigned int elements_read = bytes_read / sizeof(Scalar);
        dst.reserve(elements_read + dst.size()); // pre-allocate space
        for (unsigned int i = 0; i < bytes_read/sizeof(Scalar); ++i)
        {
            dst.push_back(data[i]);
        }
        if (bytes_read < input_buffer_size)
        {
            if (gzeof(file))
            {
                break;
            }
            else
            {
                const char * error_string;
                error_string = gzerror(file, &err);
                if (err)
                {
                    std::cerr << "zlib error: " << error_string << std::endl;
                    return false;
                }
            }
        }
    }
    gzclose(file);
    return true;
}

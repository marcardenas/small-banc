#include <smallbanc/io.hpp>

#include <filesystem>
#include <fstream>

namespace smallbanc
{

namespace io
{

FileReader::FileReader( const std::string &file ) : IFileReader()
{
  m_file = file;
}

std::string FileReader::read() const {}

} // namespace io

} // namespace smallbanc
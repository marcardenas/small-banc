#include <smallbanc/io.hpp>

#include <fstream>

namespace smallbanc
{

namespace io
{

FileReader::FileReader( const std::string &file ) : IFileReader()
{
  m_file = file;
}

std::string FileReader::read() const { return ""; }

void FileWriter::write( const std::string &content ) const
{
  std::ofstream ofs( m_file, std::ios::out | std::ios::trunc );
  if ( ofs.is_open() )
  {
    ofs << content;
    ofs.close();
  }
}

void FileWriter::initialize() const
{
  std::ofstream ofs( m_file, std::ios::out | std::ios::trunc );

  if ( ofs.is_open() )
  {
    ofs.close();
  }
}

} // namespace io

} // namespace smallbanc
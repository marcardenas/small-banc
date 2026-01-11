#include <smallbanc/io.h>

#include <filesystem>
#include <fstream>

namespace smallbanc
{

namespace io
{

void FileCreator::create()
{
  std::ofstream file( m_file );

  if ( file.is_open() )
  {
    file.close();
  }
  else
  {
    throw std::runtime_error( "Could not create file: " + m_file );
  }
}

bool FileCreator::exists() const
{
  if ( !std::filesystem::exists( m_file ) )
  {
    return false;
  }

  return true;
}

} // namespace io

} // namespace smallbanc
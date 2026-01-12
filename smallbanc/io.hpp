#pragma once

#include <string>

namespace smallbanc
{

namespace io
{

class IFileReader
{
public:
  virtual ~IFileReader() = default;
  virtual std::string read() const = 0;
};

class FileReader : public IFileReader
{
public:
  FileReader( const std::string& file );
  std::string read() const;
private:
  std::string m_file;
};

} // namespace io

} // namespace smallbanc

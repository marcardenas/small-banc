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
  virtual std::string filename() const = 0;
};

class IFileWriter
{
public:
  virtual ~IFileWriter() = default;
  virtual void write( const std::string &content ) const = 0;
  virtual std::string filename() const = 0;

  virtual void initialize() const = 0;
};

class FileReader : public IFileReader
{
public:
  FileReader( const std::string &file );
  std::string read() const;
  std::string filename() const { return m_file; }

private:
  std::string m_file;
};

class FileWriter : public IFileWriter
{
public:
  FileWriter( const std::string &file ) : m_file( file ) {}
  void write( const std::string &content ) const override;
  std::string filename() const override { return m_file; }

  void initialize() const override;

private:
  std::string m_file;
};

} // namespace io

} // namespace smallbanc

#pragma once

#include <string>

namespace smallbanc
{

namespace io
{

class IFileCreator
{
public:
  virtual ~IFileCreator() = default;
  
  void set( const std::string& file ) { m_file = file; }
  virtual void create() = 0;
  virtual bool exists() const = 0;

protected:
    std::string m_file;
};

class FileCreator : public IFileCreator
{
public:
  FileCreator() : IFileCreator() {}

  void create() override;
  bool exists() const override;
};

} // namespace io

} // namespace smallbanc

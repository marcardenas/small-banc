// ----------------------------------------------------------------------------

#pragma once

// ----------------------------------------------------------------------------

#include "smallbanc/io.hpp"
#include "smallbanc/model.hpp"

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

// ----------------------------------------------------------------------------

namespace smallbanc
{

// ----------------------------------------------------------------------------

namespace io
{
class IFileReader;
class IFileWriter;
} // namespace io

// ----------------------------------------------------------------------------

namespace client
{

// ----------------------------------------------------------------------------

class ClientReader
{
public:
  ClientReader( const std::string &file ) : m_file( file ) {}
  ~ClientReader();

  std::vector<smallbanc::model::Client> read() const;

private:
  std::string m_file;

  std::unique_ptr<smallbanc::io::IFileReader> m_reader;
};

// ----------------------------------------------------------------------------

class ClientWriter : public smallbanc::model::IModelWriter
{
public:
  ClientWriter( const std::string &file ) : m_file( file )
  {
    m_writer = std::make_unique<smallbanc::io::FileWriter>( file );
  }
  ~ClientWriter();

  void insert( const smallbanc::model::Client &client );
  void remove( unsigned int client_id );
  void initialize() const;
  void write() const;
  bool exists() const { return std::filesystem::exists( m_file ); }

private:
  std::string build_client_record(
    const smallbanc::model::Client &client ) const;

  std::string m_file;

  std::unique_ptr<smallbanc::io::IFileWriter> m_writer;
  std::vector<smallbanc::model::Client> m_dispatch_list;
};

// ----------------------------------------------------------------------------

} // namespace client

// ----------------------------------------------------------------------------

} // namespace smallbanc

// ----------------------------------------------------------------------------
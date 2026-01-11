#include <cstdint>

struct LedgerRecordHeader
{
  uint32_t magic;
  uint8_t version;
  uint32_t length;
  uint64_t tx_id;
  uint64_t timestamp;
};

struct LedgerEntry
{
};

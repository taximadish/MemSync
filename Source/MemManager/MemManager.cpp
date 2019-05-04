#include "MemManager.h"
#include "MemEntries/Coins.h"

#define POUCH_PTR 0x8041EB00

MemManager::MemManager()
{
  m_entries = {};

  addEntry(new Coins());


  /*
  createEntry("Level", Common::MemType::type_halfword, POUCH_PTR,
              std::vector<int32_t>{0x8A});

  createEntry("Star Points", Common::MemType::type_halfword, POUCH_PTR,
              std::vector<int32_t>{0x96});
                          */
}

void MemManager::addEntry(IMemEntry* entry)
{
  m_entries[entry->Name()] = entry;
}

void MemManager::setEntryValue(std::string name, std::string value)
{
  m_entries[name]->setValue(value);
}

std::string MemManager::readEntryValue(std::string name)
{
  return m_entries[name]->getValue();
}

std::string MemManager::getUpdate(std::string name, std::string hostVal)
{
  return m_entries[name]->getUpdate(hostVal);
}

void MemManager::handleUpdate(std::string name, std::string updateString)
{
  m_entries[name]->handleUpdate(updateString);
}

std::vector<std::string> MemManager::Keys()
{
  std::vector<std::string> keys;
  for (std::map<std::string, IMemEntry*>::iterator it = m_entries.begin(); it != m_entries.end();
       ++it)
  {
    keys.push_back(it->first);
  }

  return keys;
}
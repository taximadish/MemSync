#include "Shines.h"

Shines::Shines()
{ 
  m_watch = new MemWatchEntry(Name().c_str(), POUCH_PTR, Common::MemType::type_halfword);

  m_watch->setBoundToPointer(true);
  m_watch->addOffset(0x9C);
}

std::string Shines::Name()
{
  return "Shines";
}

bool Shines::setValue(std::string value)
{
  int32_t intVal = atoi(value.c_str());
  if (intVal > 999)
    value = "999";
  if (intVal < 0)
    value = "0";
  m_watch->writeMemoryFromString(value);
  return true;
}

std::string Shines::getValue()
{
  return m_watch->getStringFromMemory();
}

std::string Shines::getUpdate(std::string hostVal)
{
  int32_t currentVal = atoi(m_watch->getStringFromMemory().c_str());
  int32_t newVal = atoi(hostVal.c_str());

  if (currentVal == newVal)
  {
    return NO_UPDATE;
  }

  return std::to_string(currentVal - newVal);
}

void Shines::handleUpdate(std::string updateString)
{
  int32_t currentVal = atoi(m_watch->getStringFromMemory().c_str());
  int32_t valToAdd = atoi(updateString.c_str());

  setValue(std::to_string(currentVal + valToAdd));
}
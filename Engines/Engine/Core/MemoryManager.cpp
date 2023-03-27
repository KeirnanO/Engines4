#include "MemoryManager.h"

std::unique_ptr<MemoryManager> MemoryManager::instance = nullptr;

MemoryManager* MemoryManager::GetInstance()
{
	if (instance.get() == nullptr) {
		instance.reset(new MemoryManager(1024 * 1024));
	}
	return instance.get();
}

void* MemoryManager::allocate(size_t amount)
{
	std::cout << "Allocating " << amount << " bytes of memory\n";
	return &m_MasterBlock[m_BlockIndex += amount];
}


MemoryManager::MemoryManager(size_t  masterBlockSize) : m_MasterBlock(nullptr) {
	m_MasterBlock = static_cast<byte*>(malloc(masterBlockSize));
	m_BlockIndex = 0;
}


MemoryManager::~MemoryManager()
{
	std::cout << "Freed the memory\n";
	if (m_MasterBlock) free(m_MasterBlock);
}
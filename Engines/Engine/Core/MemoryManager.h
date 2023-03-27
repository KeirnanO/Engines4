#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <iostream>
#include <memory.h>


using byte = unsigned char;
class MemoryManager {
public:
	MemoryManager(const MemoryManager&) = delete;
	MemoryManager(const MemoryManager&&) = delete;
	MemoryManager& operator=(const MemoryManager&) = delete;
	MemoryManager& operator=(MemoryManager&&) = delete;

	static MemoryManager* GetInstance();

	void* allocate(size_t amount);

	
	~MemoryManager();

private:
	MemoryManager(size_t masterBlockSize);

	static std::unique_ptr<MemoryManager> instance;
	byte* m_MasterBlock;
	size_t m_BlockIndex;
};


#endif
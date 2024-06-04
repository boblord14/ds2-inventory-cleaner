#ifndef _SIGNATURE_H_
#define _SIGNATURE_H_

#include <Windows.h>
#include <vector>
#include <stdexcept>
#include <TlHelp32.h>

//Signature class that takes a CE style string and scans only the text section
//Thank you to tremwil for the suggestion and walkthrough on how to scan the code with XOR + AND
struct ExecutableSection {
    ExecutableSection(void* ptr, DWORD size) {
        SectionPtr = ptr;
        SectionSize = size;
    };
    void* SectionPtr = nullptr;
    DWORD SectionSize = 0;
};

struct ModuleData {
    ModuleData(const char* module);
    HMODULE ModuleHandle = nullptr;
    void* BaseAddress = nullptr;
    size_t ImageSize = 0;
    std::vector<ExecutableSection> ExecutableSections;
};


enum ScanOffset {
    Default = 0x1,
    Align4 = 0x4,
    Align8 = 0x8,
    Align16 = 0x10,
};

struct Signature {
    explicit Signature(const char* sig, int offset = 0);
    void* Scan(ModuleData* moduleData, ScanOffset offset = Default);
    void* Scan(ModuleData* moduleData, int address_offset, int instruction_size, ScanOffset offset = Default);
    void* GetRelativeOffset(int address_offset, int instruction_size);
    void* ScanResult = nullptr;
private:
    std::vector<uint8_t> _bytes = {};
    std::vector<uint8_t> _mask = {};
    const int _offset;
    static int hex2num(char h);
};



#endif // _SIGNATURE_H_
#ifndef CRC8_CCIT_H
#define	CRC8_CCIT_H

#include <cstdint>

class CRC8_CCIT
{
private:
    uint8_t crc{0};
public:
    void Add(uint8_t value);

    uint8_t Value() const
    {
        return crc;
    }

    void Reset()
    {
        crc = 0;
    }
};

#endif	/* CRC8_CCIT_H */

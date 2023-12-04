
#ifndef INCLUDE_BLOOM_FILTER_HPP
#define INCLUDE_BLOOM_FILTER_HPP

#include <iostream>

typedef unsigned int bloom_type;

static const uint32_t hash_function_count = 10;
static const uint32_t bit_width = 1840;

static const std::size_t bits_per_char = 0x08;
static const unsigned char bit_mask[bits_per_char] = {
                                                       0x01,  //00000001
                                                       0x02,  //00000010
                                                       0x04,  //00000100
                                                       0x08,  //00001000
                                                       0x10,  //00010000
                                                       0x20,  //00100000
                                                       0x40,  //01000000
                                                       0x80   //10000000
                                                     };


static bloom_type salt[hash_function_count] =
                                 {
                                    0xAA55AA55, 0x55335533,
                                    0x33CC33CC, 0xCC66CC66,
                                    0x66996699, 0x99B599B5,
                                    0xB54BB54B, 0x4BAA4BAA,
                                    0xAA33AA33, 0x55CC55CC
                                 };


class bloom_filter
{
public:
    bloom_filter(uint64_t seed = 0xA5A5A5A5):random_seed_(seed * 0xA5A5A5A5)
    {
        for (int i = 0; i < hash_function_count; i++)
        {
            salt[i] = salt[i] * salt[(i + 3) % hash_function_count] + static_cast<bloom_type>(random_seed_);
        }
    }

    inline virtual void compute_indices(const bloom_type& hash, std::size_t& bit_index, std::size_t& bit) const
    {
        bit_index = hash % bit_width;
        bit       = bit_index % bits_per_char;
    }

    inline bloom_type hash_ap(const unsigned char* begin, std::size_t remaining_length, bloom_type hash) const
    {
        const unsigned char* itr = begin;
        unsigned int loop        = 0;

        while (remaining_length >= 8)
        {
            const unsigned int& i1 = *(reinterpret_cast<const unsigned int*>(itr)); itr += sizeof(unsigned int);
            const unsigned int& i2 = *(reinterpret_cast<const unsigned int*>(itr)); itr += sizeof(unsigned int);

            hash ^= (hash <<  7) ^  i1 * (hash >> 3) ^
                (~((hash << 11) + (i2 ^ (hash >> 5))));

            remaining_length -= 8;
        }

        if (remaining_length)
        {
            if (remaining_length >= 4)
            {
                const unsigned int& i = *(reinterpret_cast<const unsigned int*>(itr));

                if (loop & 0x01)
                hash ^=    (hash <<  7) ^  i * (hash >> 3);
                else
                hash ^= (~((hash << 11) + (i ^ (hash >> 5))));

                ++loop;

                remaining_length -= 4;

                itr += sizeof(unsigned int);
            }

            if (remaining_length >= 2)
            {
                const unsigned short& i = *(reinterpret_cast<const unsigned short*>(itr));

                if (loop & 0x01)
                hash ^=    (hash <<  7) ^  i * (hash >> 3);
                else
                hash ^= (~((hash << 11) + (i ^ (hash >> 5))));

                ++loop;

                remaining_length -= 2;

                itr += sizeof(unsigned short);
            }

            if (remaining_length)
            {
                hash += ((*itr) ^ (hash * 0xA5A5A5A5)) + loop;
            }
        }

        return hash;
    }

    inline void insert(const unsigned char* key_begin, const std::size_t& length)
    {
        std::size_t bit_index = 0;
        std::size_t bit       = 0;

        for (std::size_t i = 0; i < hash_function_count; ++i)
        {
            compute_indices(hash_ap(key_begin, length, salt[i]), bit_index, bit);

            bit_table_[bit_index / bits_per_char] |= bit_mask[bit];
        }

    }

    template <typename T>
    inline void insert(const T& t)
    {
        insert(reinterpret_cast<const unsigned char*>(&t),sizeof(T));
    }

    inline void insert(const std::string& key)
    {
        insert(reinterpret_cast<const unsigned char*>(key.data()),key.size());
    }

    inline void insert(const char* data, const std::size_t& length)
    {
        insert(reinterpret_cast<const unsigned char*>(data),length);
    }

    inline virtual bool contains(const unsigned char* key_begin, const std::size_t length) const
    {
        std::size_t bit_index = 0;
        std::size_t bit       = 0;

        for (std::size_t i = 0; i < hash_function_count; ++i)
        {
            compute_indices(hash_ap(key_begin, length, salt[i]), bit_index, bit);

            if ((bit_table_[bit_index / bits_per_char] & bit_mask[bit]) != bit_mask[bit])
            {
                return false;
            }
        }

        return true;
    }

    template <typename T>
    inline bool contains(const T& t) const
    {
        return contains(reinterpret_cast<const unsigned char*>(&t),static_cast<std::size_t>(sizeof(T)));
    }

    inline bool contains(const std::string& key) const
    {
        return contains(reinterpret_cast<const unsigned char*>(key.c_str()),key.size());
    }

    inline bool contains(const char* data, const std::size_t& length) const
    {
        return contains(reinterpret_cast<const unsigned char*>(data),length);
    }

private:
    unsigned char bit_table_[bit_width / 8] = {0};
    uint64_t random_seed_;
};

#endif
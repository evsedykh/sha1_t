
#include "sha1_t.h"

#include <cstring>
#include <stdexcept>

sha1_t::sha1_t()
{
}

// ASCII table codes including all 0-9, A-F, and a-f digits
// Incorrect symbols lead to zero values!
const unsigned int hex_dig[256] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 0-9
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 10-19
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 20-29
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 30-39
                                    0, 0, 0, 0, 0, 0, 0, 0,		   // 40-47
                                    0, 1, 2, 3, 4, 5, 6, 7, 8, 9,  // 48-57  -->  0-9 digits
                                    0, 0, 0, 0, 0, 0, 0,		   // 58-64
                                    10, 11, 12, 13, 14, 15,        // 65-70  -->  A-F digits
                                    0, 0, 0, 0, 0, 0, 0,		   // 71-77
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 78-87
                                    0, 0, 0, 0, 0, 0, 0, 0, 0,     // 88-96
                                    10, 11, 12, 13, 14, 15, 	   // 98-102  -->  a-f digits
                                    0, 0, 0, 0, 0, 0, 0,           // 103-109
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 110-119
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 120-129
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 130-139
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 140-149
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 150-159
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 160-169
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 170-179
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 180-189
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 190-199
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 200-209
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 210-219
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 220-229
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 230-239
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 240-249
                                    0, 0, 0, 0, 0, 0 };			   // 250-255


const unsigned char hex2char[ 16 ] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

inline unsigned int toNumber( char c1, char c2 )
{
    return (hex_dig[static_cast<size_t>(c1) ] << 4) | hex_dig[ static_cast<size_t>(c2) ];
}


sha1_t::sha1_t( const sha1_t& sha1 )
{
    memcpy( &m_data, &sha1, binlen );
}


sha1_t::sha1_t( const std::string& str )
{
    if( str.length() != strlen )
    {
        std::string msg = "Bad SHA1: " + str + "!";
        throw std::length_error( msg );
    }
    for( unsigned int i = 0; i < binlen; ++i)
    {
        m_data[ i ] = toNumber( str[2*i], str[2*i+1]);
    }
}

sha1_t::~sha1_t()
{
}

bool sha1_t::operator== ( const sha1_t& other ) const
{
    return memcmp( &m_data, &other, binlen ) == 0;
}

bool sha1_t::operator< ( const sha1_t& other ) const
{
    return memcmp( &m_data, &other, binlen ) < 0;
}

std::string sha1_t::string() const
{
    std::string str( strlen, '_');
    for( unsigned int i = 0; i < binlen; ++i )
    {
        str[ 2 * i ] = hex2char[ ( ( m_data[ i ] & 0xF0 ) >> 4) ];
        str[ 2 * i + 1 ] = hex2char[ m_data[ i ] & 0x0F ];
    }
    return str;
}

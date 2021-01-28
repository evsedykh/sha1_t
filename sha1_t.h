#ifndef SHA1_T_H
#define SHA1_T_H

#include <string>

class sha1_t
{
public:

    sha1_t();

    sha1_t( const std::string& str );

    sha1_t( const sha1_t& sha1 );

    ~sha1_t();

    bool operator== ( const sha1_t& other ) const;

    bool operator< ( const sha1_t& other ) const;

    std::string string() const;

    static const size_t strlen = 40;

    static const size_t binlen = 20;


protected:

    unsigned char m_data[ binlen ];

    friend struct sha1_hasher;
};

struct sha1_hasher
{
    size_t operator()( const sha1_t& sha1 ) const
    {
        return *reinterpret_cast< const size_t* >( &sha1.m_data );
    }
};

typedef sha1_t SHA1String;

#endif

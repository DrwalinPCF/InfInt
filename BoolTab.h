
#ifndef BOOLTAB_H
#define BOOLTAB_H

#include <vector>
#include <cstring>

typedef unsigned long long int uint64;
typedef long long int int64;
typedef unsigned int uint32;
typedef int int32;

namespace My
{
class InfInt;
};

class BoolTab
{
protected:
	
	std::vector < uint64 > val;
	inline void ClearLeadingZeros();
	
private:
	
	
public:
	
	friend class My::InfInt;
	
	inline void Clear();
	
	const static uint64 bits = 8 * sizeof(uint64);
	
	inline bool GetBit( const uint64 pos ) const;
	inline void SetBit( const uint64 pos, const bool value );
	inline uint64 GetSize() const;
	
	inline BoolTab& operator = ( const BoolTab& src );
	
	inline BoolTab operator ~ ( void ) const;
	inline BoolTab operator & ( const BoolTab& src ) const;
	inline BoolTab operator | ( const BoolTab& src ) const;
	inline BoolTab operator ^ ( const BoolTab& src ) const;
	inline BoolTab operator << ( const uint64 src ) const;
	inline BoolTab operator >> ( const uint64 src ) const;
	
	inline BoolTab& operator &= ( const BoolTab& src );
	inline BoolTab& operator |= ( const BoolTab& src );
	inline BoolTab& operator ^= ( const BoolTab& src );
	inline BoolTab& operator <<= ( const uint64 src );
	inline BoolTab& operator >>= ( const uint64 src );
	
	inline bool operator < ( const BoolTab& src ) const;
	inline bool operator <= ( const BoolTab& src ) const;
	inline bool operator > ( const BoolTab& src ) const;
	inline bool operator >= ( const BoolTab& src ) const;
	inline bool operator == ( const BoolTab& src ) const;
	inline bool operator != ( const BoolTab& src ) const;
	
	inline BoolTab operator + ( const BoolTab& src ) const;
	inline BoolTab operator - ( const BoolTab& src ) const;		// if src > *this then undefined behavior
	inline BoolTab& operator += ( const BoolTab& src );			// need optimization
	inline BoolTab& operator -= ( const BoolTab& src );			// if src > *this then undefined behavior		// need optimization
	inline BoolTab& Increment();
	inline BoolTab& Decrement();								// if *this == 0 then return 0
	
	inline void * GetValue();
	inline void FromData( const void * data, const uint64 bytes );
	
	BoolTab();
	BoolTab( const uint64 src );
};

#endif


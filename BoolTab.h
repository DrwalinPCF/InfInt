
#ifndef BOOLTAB_H
#define BOOLTAB_H

#include <vector>
#include <cstring>

typedef unsigned long long int uint64;
typedef long long int int64;

class BoolTab
{
protected:
	
	std::vector < uint64 > val;
	
private:
	
	inline void ClearLeadingZeros();
	
public:
	
	friend class InfInt;
	
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
	
	inline void * GetValue();
	inline void FromData( const void * data, const uint64 bytes );
	
	BoolTab();
};

#endif


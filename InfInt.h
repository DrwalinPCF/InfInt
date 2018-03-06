
#ifndef INFINT_H
#define INFINT_H

#include "BoolTab.h"

class InfInt
{
private:
	
	BoolTab val;
	bool pos;
	
	InfInt( const BoolTab& sval, const bool spos );
	
	const static InfInt zero( BoolTab(), true );
	
public:
	
	inline bool IsPositive() const;
	inline bool IsNegative() const;
	inline bool GetSign() const;
	inline InfInt& operator = ( const InfInt& src );
	
	inline InfInt operator & ( const InfInt& src ) const;
	inline InfInt operator | ( const InfInt& src ) const;
	inline InfInt operator ^ ( const InfInt& src ) const;
	inline InfInt operator << ( const InfInt& src ) const;
	inline InfInt operator >> ( const InfInt& src ) const;
	
	inline InfInt& operator &= ( const InfInt& src );
	inline InfInt& operator |= ( const InfInt& src );
	inline InfInt& operator ^= ( const InfInt& src );
	inline InfInt& operator <<= ( const InfInt& src );
	inline InfInt& operator >>= ( const InfInt& src );
	
	inline bool operator < ( const InfInt& src ) const;
	inline bool operator <= ( const InfInt& src ) const;
	inline bool operator > ( const InfInt& src ) const;
	inline bool operator >= ( const InfInt& src ) const;
	inline bool operator == ( const InfInt& src ) const;
	inline bool operator != ( const InfInt& src ) const;
	
	inline InfInt operator + ( const InfInt& src ) const;
	inline InfInt operator - ( const InfInt& src ) const;
	inline InfInt operator * ( const InfInt& src ) const;
	inline InfInt operator / ( const InfInt& src ) const;
	inline InfInt operator % ( const InfInt& src ) const;
	
	inline InfInt& operator += ( const InfInt& src );
	inline InfInt& operator -= ( const InfInt& src );
	inline InfInt& operator *= ( const InfInt& src );
	inline InfInt& operator /= ( const InfInt& src );
	inline InfInt& operator %= ( const InfInt& src );
	
	inline unsigned long long int ToULL() const;
	inline long long int ToLL() const;
	inline void * GetData();
	inline unsigned long long int Size() const;
	inline void ToString( char * str, const unsigned long long int len ) const;
	
	static inline InfInt pow( const InfInt& val, const InfInt& exp );
	static inline InfInt sqrt( const InfInt& val );
	static inline InfInt log( const InfInt& base, const InfInt& val );
	
	InfInt( const char * str );
	InfInt( const void * data, const uint64 bytes );
	InfInt( const long long int val );
	InfInt( const int val );
	InfInt( const short val );
	InfInt( const char val );
	InfInt( const unsigned long long int val );
	InfInt( const unsigned int val );
	InfInt( const unsigned short val );
	InfInt( const unsigned char val );
};

#endif

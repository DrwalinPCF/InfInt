#include <string>

#ifndef INFINT_H
#define INFINT_H

#include "BoolTab.h"
#include <cstdio>

namespace My
{

/*
	if val.GetSize() == 0 && pos == false
	that means some kind of error
*/

class InfInt
{
private:
public:
	
	BoolTab val;
	bool pos;
	
	
	inline bool IsPositive() const;
	inline bool IsNegative() const;
	inline bool GetSign() const;
	inline uint64 GetSize() const;
	inline uint64 GetBytesNumber() const;
	
	inline InfInt& operator = ( const InfInt& src );
	
	
	inline InfInt operator ~ (void) const;
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
	
	inline bool Div( const InfInt& src, InfInt& result, InfInt& rest ) const;		// return if division is valid
	
	inline InfInt operator - ( void ) const;
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
	inline InfInt& Increment();
	inline InfInt& Decrement();
	
	inline unsigned long long int ToULL() const;
	inline long long int ToLL() const;
	inline void * GetData();
	inline unsigned long long int Size() const;
	inline void ToString( char * str, const unsigned long long int len ) const;
	
	inline InfInt lb() const;	// return binary logarithm
	static inline InfInt pow( const InfInt& val, const InfInt& exp );
	static inline InfInt sqrt( const InfInt& val );
	static inline InfInt log( const InfInt& base, const InfInt& val );
	
	InfInt();
	
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
	
	InfInt( const BoolTab& sval, const bool spos );
	static inline InfInt Make( const BoolTab& sval, const bool spos );
	
												static std::string ToString( const My::InfInt& val )
												{
													char str[1000000];
													val.ToString( str, 1000000-100 );
													std::vector < unsigned int > ch;
													std::string dst = "";
													
													bool stillZeros = true;
													
													
													
													for( int i = 0; str[i]; ++i )
													{
														if( str[i] == '-' )
														{
															dst = "-";
															continue;
														}
														if( stillZeros )
														{
															if( str[i] != '0' )
																stillZeros = false;
															else
																continue;
														}
														if( str[i] >= '0' && str[i] <= '9' )
															ch.insert( ch.begin(), (unsigned int)(str[i]-'0') );
														else
															ch.insert( ch.begin(), (unsigned int)(str[i]+10-'A') );
													}
													
													while( ch.size() )
													{
														if( ch.back() < 10 )
															dst.append( 1, (char)(ch.back()+'0') );
														else
															dst.append( 1, (char)((ch.back()-10)+'A') );
														ch.resize( ch.size()-1 );
													}
													return dst;
													
													
												}
};



};

#endif


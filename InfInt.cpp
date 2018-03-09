
#ifndef INFINT_CPP
#define INFINT_CPP

#include "InfInt.h"
#include "BoolTab.cpp"

namespace My
{

InfInt::InfInt( const BoolTab& sval, const bool spos )
{
	this->val = sval;
	this->pos = spos;
	this->val.ClearLeadingZeros();
	if( this->val.GetSize() == 0 )		this->pos = true;
}

inline InfInt InfInt::Make( const BoolTab& sval, const bool spos )
{
	InfInt dst;
	dst.val = sval;
	dst.pos = spos;
	dst.val.ClearLeadingZeros();
	if( dst.val.GetSize() == 0 )		dst.pos = true;
	return dst;
}

inline bool InfInt::IsPositive() const
{
	return this->pos;
}

inline bool InfInt::IsNegative() const
{
	return !(this->pos);
}

inline bool InfInt::GetSign() const
{
	return this->pos;
}

inline uint64 InfInt::GetSize() const
{
	return this->val.GetSize();
}

inline uint64 InfInt::GetBytesNumber() const
{
	return this->val.val.size() * sizeof(uint64);
}

inline InfInt& InfInt::operator = ( const InfInt& src )
{
	this->val = src.val;
	this->pos = src.pos;
}

inline InfInt InfInt::operator ~ ( void ) const
{
	return InfInt::Make( ~(this->val), !(this->pos) );
}

inline InfInt InfInt::operator & ( const InfInt& src ) const
{
	return InfInt::Make( this->val & src.val, this->pos && src.pos );
}

inline InfInt InfInt::operator | ( const InfInt& src ) const
{
	return InfInt::Make( this->val | src.val, this->pos || src.pos );
}

inline InfInt InfInt::operator ^ ( const InfInt& src ) const
{
	return InfInt::Make( (this->val) ^ src.val, this->pos ^ src.pos );
}

inline InfInt InfInt::operator << ( const InfInt& src ) const
{
	if( src.val.val.size() )
		return InfInt::Make( src.pos ? (this->val<<src.ToULL()) : (this->val>>src.ToULL()), this->pos );
	return *this;
}

inline InfInt InfInt::operator >> ( const InfInt& src ) const
{
	if( src.val.val.size() )
		return InfInt::Make( src.pos ? (this->val>>src.ToULL()) : (this->val<<src.ToULL()), this->pos );
	return *this;
}

inline InfInt& InfInt::operator &= ( const InfInt& src )
{
	this->val &= src.val;
	this->pos = this->pos && src.pos;
	this->val.ClearLeadingZeros();
	if( this->val.GetSize() == 0 )		this->pos = true;
	return *this;
}

inline InfInt& InfInt::operator |= ( const InfInt& src )
{
	this->val |= src.val;
	this->pos = this->pos || src.pos;
	this->val.ClearLeadingZeros();
	if( this->val.GetSize() == 0 )		this->pos = true;
	return *this;
}

inline InfInt& InfInt::operator ^= ( const InfInt& src )
{
	this->val ^= src.val;
	this->pos = this->pos ^ src.pos;
	this->val.ClearLeadingZeros();
	if( this->val.GetSize() == 0 )		this->pos = true;
	return *this;
}

inline InfInt& InfInt::operator <<= ( const InfInt& src )
{
	if( src.pos )
		this->val <<= src.ToULL();
	else
		this->val >>= src.ToULL();
	this->val.ClearLeadingZeros();
	return *this;
}

inline InfInt& InfInt::operator >>= ( const InfInt& src )
{
	if( src.pos )
		this->val >>= src.ToULL();
	else
		this->val <<= src.ToULL();
	this->val.ClearLeadingZeros();
	if( this->val.GetSize() == 0 )		this->pos = true;
	return *this;
}

inline bool InfInt::operator < ( const InfInt& src ) const
{
	if( !this->pos && src.pos )
		return true;
	if( this->pos && !src.pos )
		return false;
	if( this->pos )
		return this->val < src.val;
	return this->val > src.val;
}

inline bool InfInt::operator <= ( const InfInt& src ) const
{
	if( !this->pos && src.pos )
		return true;
	if( this->pos && !src.pos )
		return false;
	if( this->pos )
		return this->val <= src.val;
	return this->val >= src.val;
}

inline bool InfInt::operator > ( const InfInt& src ) const
{
	if( !this->pos && src.pos )
		return false;
	if( this->pos && !src.pos )
		return true;
	if( this->pos )
		return this->val > src.val;
	return this->val < src.val;
}

inline bool InfInt::operator >= ( const InfInt& src ) const
{
	if( !this->pos && src.pos )
		return false;
	if( this->pos && !src.pos )
		return true;
	if( this->pos )
		return this->val >= src.val;
	return this->val <= src.val;
}

inline bool InfInt::operator == ( const InfInt& src ) const
{
	if( this->pos == src.pos )
		return this->val == src.val;
	return false;
}

inline bool InfInt::operator != ( const InfInt& src ) const
{
	if( this->pos != src.pos )
		return true;
	if( this->val != src.val )
		return true;
	return false;
}

inline InfInt InfInt::operator - ( void ) const
{
	return InfInt::Make( this->val, !this->pos );
}

#define printf(x)

inline InfInt InfInt::operator + ( const InfInt& src ) const
{
	if( this->val.val.size() == 0 )
	{
printf( "+::1" );
		return src;
	}
	if( src.val.val.size() == 0 )
	{
printf( "+::2" );
		return *this;
	}
printf( "+::3" );
	if( this->pos && !src.pos )
	{
printf( "+::4" );
		return (*this) - InfInt::Make( src.val, true );
	}
	else if( !this->pos && src.pos )
	{
printf( "+::5" );
		return src - InfInt::Make( this->val, true );
	}
	else // this->pos == src.pos
	{
printf( "+::6" );
		InfInt dst;
printf( "+::7" );
		uint64 carryIn = 0, carryOut = 0, i = 0, max, min;
		register uint64 temp;
		dst.pos = this->pos;
printf( "+::8" );
		if( this->val.GetSize() < src.val.GetSize() )
		{
printf( "+::9" );
			min = this->val.GetSize();
			max = src.val.GetSize();
printf( "+::10" );
		}
		else
		{
printf( "+::11" );
			max = this->val.GetSize();
			min = src.val.GetSize();
printf( "+::12" );
		}
		
		// Positive adding:
		
printf( "+::13" );
		dst.val = this->val;
printf( "+::14" );
		dst.val.val.resize( (max+2)>max ? max+2 : (uint64(0)-uint64(1)), uint64(0) );
printf( "+::15" );
		
		while( i < src.val.val.size() || carryOut )
		{
printf( "+::16" );
			carryIn = carryOut;
			carryOut ^= carryOut;
printf( "+::17" );
			
			temp = dst.val.val[i];
printf( "+::18" );
			
			if( i < src.val.val.size() )
			{
printf( "+::19" );
				temp += src.val.val[i];
printf( "+::20" );
				//check if this->val.val[i] overflow with src.val.val[i]
				if( temp < src.val.val[i] )
					++carryOut;
				else if( temp < dst.val.val[i] )
					++carryOut;
			}
			
printf( "+::21" );
			dst.val.val[i] = temp;
printf( "+::22" );
			dst.val.val[i] += carryIn;
printf( "+::23" );
			//check if dst.val.val[i] overflow with carryIn
			if( dst.val.val[i] < temp )
				++carryOut;
printf( "+::24" );
			
			++i;
		}
printf( "+::25" );
		
		dst.val.ClearLeadingZeros();
		return dst;
	}
printf( "+::26" );
	return InfInt();
}

#define printf(x)

inline InfInt InfInt::operator - ( const InfInt& src ) const
{
	if( src.val.val.size() == 0 )
		return *this;
	if( this->val.val.size() == 0 )
		return -src;
	if( !this->pos && src.pos )
	{
		return InfInt::Make( this->val, false ) + InfInt::Make( src.val, false );
	}
	else if( this->pos && !src.pos )
	{
		return InfInt::Make( this->val, true ) + InfInt::Make( src.val, true );
	}
	// this->pos == src.pos
	else if( !this->pos )
	{
		return - ( InfInt::Make( this->val, true ) - InfInt::Make( src.val, true ) );
	}	
	else
	{
		InfInt a = *this;
		InfInt b = src;
		
		bool tempBool = a.val >= b.val;
		
		if( tempBool )
		{
			b.val = ~b.val;
			b.val.val.resize( a.val.val.size(), uint64(0) - uint64(1) );
			
			InfInt dst;
			dst = a + b + InfInt(1);
			
			if( dst.val.val.size() > 0 )
			{
				dst.val.val.resize( dst.val.val.size() - 1 );
			}
			dst.val.ClearLeadingZeros();
			return dst;
		}
		else
		{
			return - ( b - a );
		}
	}
	return InfInt();
}

inline InfInt InfInt::operator * ( const InfInt& src ) const//
{
	if( src.val.val.size() == 0 || this->val.val.size() == 0 )
		return InfInt(0);
	InfInt dst(0);
	uint64 a1, a2, b1, b2;
	uint64 i, j;
	InfInt infi(0), infj;
	
	for( i = 0; i < this->val.val.size(); ++i, infi += InfInt(64) )
	{
		a1 = this->val.val[i] & uint64( uint32(0)-uint32(1) );
		a2 = ( this->val.val[i] - a1 ) >> uint64(32);		// & uint64( uint64( uint32(0)-uint32(1) ) << uint64(32) );
		for( j = 0, infj = InfInt(0); j < src.val.val.size(); ++j, infj += InfInt(64) )
		{
			b1 = src.val.val[j] & uint64( uint32(0)-uint32(1) );
			b2 = ( src.val.val[j] - b1 ) >> uint64(32);		// & uint64( uint64( uint32(0)-uint32(1) ) << uint64(32) );
			
			dst = dst + ( ( (InfInt(a1*b1)) + (InfInt(a2*b1)<<InfInt(32)) + (InfInt(a1*b2)<<InfInt(32)) + (InfInt(a2*b2)<<InfInt(64)) ) << ( infi + infj ) );
		}
	}
	
	dst.pos = !( this->pos ^ src.pos );
	
	return dst;
}

#undef printf

inline InfInt& InfInt::operator += ( const InfInt& src )
{
	(*this) = (*this) + src;
	return *this;
}

inline InfInt& InfInt::operator -= ( const InfInt& src )
{
	(*this) = (*this) - src;
	return *this;
}

inline InfInt& InfInt::operator *= ( const InfInt& src )
{
	(*this) = (*this) * src;
	return *this;
}

/*
inline InfInt InfInt::Div( const InfInt& src, InfInt& result, InfInt& rest ) const;//

inline InfInt InfInt::operator / ( const InfInt& src ) const;//
inline InfInt InfInt::operator % ( const InfInt& src ) const;//

inline InfInt& InfInt::operator /= ( const InfInt& src );//
inline InfInt& InfInt::operator %= ( const InfInt& src );//
*/

inline unsigned long long int InfInt::ToULL() const
{
	if( this->val.GetSize() )
		return this->val.val[0];
	return uint64(0);
}

inline long long int InfInt::ToLL() const
{
	if( this->val.GetSize() )
		return int64( this->val.val[0] & ((uint64(0)-uint64(1))-(uint64(1)<<uint64(63))) ) * ( this->pos ? int64(1) : int64(-1) );
	return int64(0);
}

inline void * InfInt::GetData()
{
	return &(this->val.val.front());
}

inline unsigned long long int InfInt::Size() const
{
	return this->val.GetSize();
}

inline void InfInt::ToString( char * str, const unsigned long long int len ) const
{
	// only hexadecimal now
	uint64 i = 0;
	
	if( !this->pos )
		str[0] = '-';
	for( ; i < this->val.GetSize(); ++i )
	{
		sprintf( str+(i*16)+(this->pos?uint64(0):uint64(1)), "%16.16llX", this->val.val[(this->val.val.size()-1)-i] );
	}
	str[i*16+(this->pos?uint64(0):uint64(1))] = 0;
}

inline InfInt InfInt::lb() const
{
	if( this->pos )
	{
		if( this->val.GetSize() )
		{
			InfInt dst( uint64( ( this->val.GetSize() * sizeof(uint64) * 8 ) ) );
			for( ; dst > InfInt(0); dst -= InfInt(1) )
			{
				if( this->val.GetBit( dst.ToULL() ) )
					return dst;
			}
		}
		return InfInt();
	}
	return InfInt::Make( BoolTab(), false );
}

/*
static inline InfInt InfInt::pow( const InfInt& val, const InfInt& exp );//
static inline InfInt InfInt::sqrt( const InfInt& val );//
static inline InfInt InfInt::log( const InfInt& base, const InfInt& val );//

InfInt::InfInt( const char * str );//
InfInt::InfInt( const void * data, const uint64 bytes );//
InfInt::InfInt( const long long int val );//
InfInt::InfInt( const short val );//
InfInt::InfInt( const char val );//
InfInt::InfInt( const unsigned short val );//
InfInt::InfInt( const unsigned char val );//
*/

InfInt::InfInt()
{
	this->pos = true;
	this->val.Clear();
}

InfInt::InfInt( const unsigned int val )
{
	this->pos = true;
	this->val.val.resize( 1 );
	this->val.val.front() = uint64(val);
	this->val.ClearLeadingZeros();
	if( this->val.GetSize() == 0 )		this->pos = true;
}

InfInt::InfInt( const unsigned long long int val )
{
	this->pos = true;
	this->val.val.resize( 1 );
	this->val.val.front() = val;
	this->val.ClearLeadingZeros();
	if( this->val.GetSize() == 0 )		this->pos = true;
}

InfInt::InfInt( const int val )
{
	this->val.val.resize( 1 );
	if( val < 0 )
	{
		this->pos = false;
		this->val.val.front() = uint64(val*-1);
	}
	else
	{
		this->pos = true;
		this->val.val.front() = uint64(val);
	}
	this->val.ClearLeadingZeros();
	if( this->val.GetSize() == 0 )		this->pos = true;
}

};

#endif


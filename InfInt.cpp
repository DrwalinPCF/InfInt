
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
		(*this) <<= src.ToULL();
	else
		(*this) >>= src.ToULL();
	this->val.ClearLeadingZeros();
	return *this;
}

inline InfInt& InfInt::operator >>= ( const InfInt& src )
{
	if( src.val.val.size() )
	{
		if( src.pos )
			(*this) >>= src.val.val[0];
		else
			(*this) <<= src.val.val[0];
	}
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

inline InfInt InfInt::operator + ( const InfInt& src ) const
{
	if( this->pos && !src.pos )
	{
		return (*this) - InfInt::Make( src.val, true );
	}
	else if( !this->pos && src.pos )
	{
		return src - InfInt::Make( this->val, true );
	}
	else // this->pos == src.pos
	{
		InfInt dst;
		uint64 carryIn = 0, carryOut = 0, i = 0, max, min, temp;
		dst.pos = this->pos;
		if( this->val.GetSize() < src.val.GetSize() )
		{
			min = this->val.GetSize();
			max = src.val.GetSize();
		}
		else
		{
			max = this->val.GetSize();
			min = src.val.GetSize();
		}
		
		// Positive adding:
		
		dst.val = this->val;
		dst.val.val.resize( (max+2)>max ? max+2 : (uint64(0)-uint64(1)), uint64(0) );
		
		while( i < dst.val.GetSize() || carryOut )
		{
			carryIn = carryOut;
			carryOut ^= carryOut;
			
			temp = dst.val.val[i];
			
			if( i < src.val.GetSize() )
			{
				temp += src.val.val[i];
				//check if this->val.val[i] overflow with src.val.val[i]
				if( temp < src.val.val[i] || temp < dst.val.val[i] )
					++carryOut;
			}
			
			dst.val.val[i] = temp;
			dst.val.val[i] += carryIn;
			//check if dst.val.val[i] overflow with carryIn
			if( dst.val.val[i] < temp )
				++carryOut;
			
			++i;
		}
		
		dst.val.ClearLeadingZeros();
		return dst;
	}
	return InfInt();
}

#define printf(x)

inline InfInt InfInt::operator - ( const InfInt& src ) const
{
printf( "-::0" );
	if( src.val.GetSize() == 0 )
		return *this;
printf( "-::1" );
	if( !this->pos && src.pos )
	{
printf( "-::2" );
		return InfInt::Make( this->val, false ) + InfInt::Make( src.val, false );
	}
	else if( this->pos && !src.pos )
	{
printf( "-::3" );
		return InfInt::Make( this->val, true ) + InfInt::Make( src.val, true );
	}
	// this->pos == src.pos
	else if( !this->pos )
	{
printf( "-::4" );
		return - ( InfInt::Make( this->val, true ) - InfInt::Make( src.val, true ) );
	}	
	else
	{
printf( "-::5" );
		InfInt a = *this;
printf( "-::6" );
		InfInt b = src;
printf( "-::7" );
		
		bool tempBool = a.val >= b.val;
printf( "-::7.(6)" );
		
		if( tempBool )
		{
printf( "-::8" );
			b.val = ~b.val;
printf( "-::9" );
			b.val.val.resize( a.val.val.size(), uint64(0) - uint64(1) );
printf( "-::10" );
			
			InfInt dst;
printf( "-::11" );
			dst = a + b + InfInt(1);
printf( "-::12" );
			
			if( dst.val.val.size() > 0 )
			{
printf( "-::13" );
				dst.val.val.resize( dst.val.val.size() - 1 );
printf( "-::14" );
			}
printf( "-::15" );
			dst.val.ClearLeadingZeros();
printf( "-::16" );
			return dst;
		}
		else
		{
printf( "-::17" );
			return - ( b - a );
		}
printf( "-::18" );
	}
printf( "-::19" );
	return InfInt();
}

inline InfInt InfInt::operator * ( const InfInt& src ) const//
{
	InfInt dst(0);
	InfInt la = InfInt(src.val.GetSize()) * InfInt(sizeof(uint64)) * InfInt(8);
	InfInt temp = InfInt::Make( this->val, true );
	
	for( ; la >= InfInt(0); la -= InfInt(1) )
	{
		if( src.val.GetBit( la.ToULL() ) )
		{
			dst += ( temp << la );
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
}

InfInt::InfInt( const unsigned long long int val )
{
	this->pos = true;
	this->val.val.resize( 1 );
	this->val.val.front() = val;
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
}

};

#endif


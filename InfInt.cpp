
#ifndef INFINT_CPP
#define INFINT_CPP

#include "InfInt.h"
#include "BoolTab.cpp"

InfInt::InfInt( const BoolTab& sval, const bool spos )
{
	this->val = sval;
	this->pos = spos;
	if( this->val.GetSize() == 0 )		this->pos = true;
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

inline InfInt& InfInt::operator = ( const InfInt& src )
{
	this->val = src.val;
	this->pos = src.pos;
}

inline InfInt InfInt::operator & ( const InfInt& src ) const
{
	return InfInt( this->val & src.val, this->pos && src.pos );
}

inline InfInt InfInt::operator | ( const InfInt& src ) const
{
	return InfInt( this->val | src.val, this->pos || src.pos );
}

inline InfInt InfInt::operator ^ ( const InfInt& src ) const
{
	return InfInt( this->val ^ src.val, this->pos ^^ src.pos );
}

inline InfInt InfInt::operator << ( const InfInt& src ) const
{
	if( src.val.val.size() )
		return InfInt( src.pos ? (this->val<<src.val.val[0]) : (this->val>>src.val.val[0]), this->pos );
	return *this;
}

inline InfInt InfInt::operator >> ( const InfInt& src ) const
{
	if( src.val.val.size() )
		return InfInt( src.pos ? (this->val>>src.val.val[0]) : (this->val<<src.val.val[0]), this->pos );
	if( this->val.GetSize() == 0 )		this->pos = true;
	return *this;
}


inline InfInt& InfInt::operator &= ( const InfInt& src )
{
	this->val &= src.val;
	this->pos = this->pos && src.pos;
	if( this->val.GetSize() == 0 )		this->pos = true;
	return *this;
}

inline InfInt& InfInt::operator |= ( const InfInt& src )
{
	this->val |= src.val;
	this->pos = this->pos || src.pos;
	if( this->val.GetSize() == 0 )		this->pos = true;
	return *this;
}

inline InfInt& InfInt::operator ^= ( const InfInt& src )
{
	this->val ^= src.val;
	this->pos = this->pos ^^ src.pos;
	if( this->val.GetSize() == 0 )		this->pos = true;
	return *this;
}

inline InfInt& InfInt::operator <<= ( const InfInt& src )
{
	if( src.val.val.size() )
	{
		if( src.pos )
			(*this) <<= src.val.val[0];
		else
			(*this) >>= src.val.val[0];
	}
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
	if( this->val.GetSize() == 0 )		this->pos = true;
	return *this;
}

inline bool InfInt::operator < ( const InfInt& src ) const
{
	if( !this->pos && src.pos )
		return true;
	if( this->pos && !src.pos )
		return false;
	if( this-pos )
		return this->val < src.val;
	return this->val > src.val;
}

inline bool InfInt::operator <= ( const InfInt& src ) const
{
	if( !this->pos && src.pos )
		return true;
	if( this->pos && !src.pos )
		return false;
	if( this-pos )
		return this->val <= src.val;
	return this->val >= src.val;
}

inline bool InfInt::operator > ( const InfInt& src ) const
{
	if( !this->pos && src.pos )
		return false;
	if( this->pos && !src.pos )
		return false;
	if( this-pos )
		return this->val > src.val;
	return this->val < src.val;
}

inline bool InfInt::operator >= ( const InfInt& src ) const
{
	if( !this->pos && src.pos )
		return false;
	if( this->pos && !src.pos )
		return false;
	if( this-pos )
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

inline InfInt operator - () const
{
	return InfInt( this->val, !this->pos );
}

inline InfInt InfInt::operator + ( const InfInt& src ) const
{
	if( this->pos && !src.pos )
	{
		return (*this) - InfInt( src.val, false );
	}
	else if( !this->pos && src.pos )
	{
		return src - InfInt( this->val, false );
	}
	else
	{
		InfInt dst;
		uint64 carryIn = 0, carryOut = 0, i = 0, max, min, temp;
		dst.pos = this->pos;
		if( this->val.size() < pos.val.size() )
		{
			min = this.val.size();
			max = pos.val.size();
		}
		else
		{
			max = this.val.size();
			min = pos.val.size();
		}
		
		// Positive adding:
		
		dst.val = this->val;
		dst.val.resize( max+2, uint64(0) );
		
		while( true )
		{
			carryIn = carryOut;
			carryOut ^= carryOut;
			
			temp = dst.val[i]
			
			if( i < src.val.size() )
			{
				temp += src.val[i];
				//check if this->val[i] overflow with src.val[i]
				if( temp < src.val[i] || temp < dst.val[i] )
					++carryOut;
			}
			
			dst.val[i] = temp;
			dst.val[i] += carryIn;
			//check if dst.val[i] overflow with carryIn
			if( dst.val[i] < temp )
				++carryOut;
			
			++i;
		}
		
		dst.val.ClearLeadingZeros();
	}
	return InfInt();
}

/*
inline InfInt InfInt::operator - ( const InfInt& src ) const;//
inline InfInt InfInt::operator * ( const InfInt& src ) const;//
inline InfInt InfInt::operator / ( const InfInt& src ) const;//
inline InfInt InfInt::operator % ( const InfInt& src ) const;//

inline InfInt& InfInt::operator += ( const InfInt& src );//
inline InfInt& InfInt::operator -= ( const InfInt& src );//
inline InfInt& InfInt::operator *= ( const InfInt& src );//
inline InfInt& InfInt::operator /= ( const InfInt& src );//
inline InfInt& InfInt::operator %= ( const InfInt& src );//
*/

inline unsigned long long int InfInt::ToULL() const
{
	return this->val.val[0];
}

inline long long int InfInt::ToLL() const
{
	return int64( this->val.val[0] & ((uint64(0)-uint64(1))-(uint64(1)<<uint64(63))) ) * ( this->pos ? int64(1) : int64(-1) );
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
	
	for( ; i < this->val.size(); ++i )
	{
		sprintf( str+(i*16), "%llX", ............//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	
}

static inline InfInt InfInt::pow( const InfInt& val, const InfInt& exp );//
static inline InfInt InfInt::sqrt( const InfInt& val );//
static inline InfInt InfInt::log( const InfInt& base, const InfInt& val );//

InfInt::InfInt( const char * str );//
InfInt::InfInt( const void * data, const uint64 bytes );//
InfInt::InfInt( const long long int val );//
InfInt::InfInt( const int val );//
InfInt::InfInt( const short val );//
InfInt::InfInt( const char val );//
InfInt::InfInt( const unsigned long long int val );//
InfInt::InfInt( const unsigned int val );//
InfInt::InfInt( const unsigned short val );//
InfInt::InfInt( const unsigned char val );//

#endif


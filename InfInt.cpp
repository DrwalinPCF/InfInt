
#ifndef INFINT_CPP
#define INFINT_CPP

#include "InfInt.h"
#include "BoolTab.cpp"

namespace My
{

InfInt::InfInt( const BoolTab& sval, const bool spos = true )
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
		return src;
	}
	if( src.val.val.size() == 0 )
	{
		return *this;
	}
	
	if( this->pos && !src.pos )
	{
		if( this->val > src.val )
		{
			return InfInt::Make( this->val - src.val, true );
		}
		else
		{
			return InfInt::Make( src.val - this->val, false );
		}
	}
	else if( !this->pos && src.pos )
	{
		if( this->val > src.val )
		{
			return InfInt::Make( this->val - src.val, false );
		}
		else
		{
			return InfInt::Make( src.val - this->val, true );
		}
	}
	else // this->pos == src.pos
	{
		InfInt dst( this->val + src.val, this->pos );
		dst.val.ClearLeadingZeros();
		return dst;
	}
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
	else
	{
		if( this->val > src.val )
		{
			return InfInt::Make( this->val - src.val, this->pos );
		}
		else
		{
			return InfInt::Make( src.val - this->val, !this->pos );
		}
	}
	return InfInt();
}

inline InfInt InfInt::operator * ( const InfInt& src ) const//
{
	if( src.val.val.size() == 0 || this->val.val.size() == 0 )
		return InfInt(0);
	
	InfInt dst(0);
	register uint64 a1, a2, b1, b2;
	uint64 i, j;
	
	for( i = 0; i < this->val.val.size(); ++i )
	{
		a1 = this->val.val[i] & 0xFFFFFFFF;
		a2 = this->val.val[i] >> uint64(32);
		for( j = 0; j < src.val.val.size(); ++j )
		{
			b1 = src.val.val[j] & 0xFFFFFFFF;
			b2 = src.val.val[j] >> uint64(32);
			
			dst.val = dst.val + ( ( (BoolTab(a1*b1)) + ( BoolTab(a2*b1) << uint64(32) ) + ( BoolTab(a1*b2) << uint64(32) ) + ( BoolTab(a2*b2) << uint64(64) ) ) << uint64((i+j)*64) );
		}
	}
	
	dst.pos = !( this->pos ^ src.pos );
	return dst;
}

inline bool InfInt::Div( const InfInt& src, InfInt& result, InfInt& rest ) const
{
	if( src.val.val.size() )
	{
		uint64 loga = this->lb().ToULL();
		uint64 logb = src.lb().ToULL();
		
		if( loga < logb )
		{
			result = InfInt(0);
			rest = *this;
			result.pos = !( this->pos ^ src.pos );
			rest.pos = !( this->pos ^ src.pos );
			return true;
		}
		else if( loga == logb )
		{
			if( this->val >= src.val )
			{
				result = InfInt(1);
				rest.val = this->val - src.val;
				
				result.pos = !( this->pos ^ src.pos );
				rest.pos = !( this->pos ^ src.pos );
				printf( "\n I hope it work. Code: InfInt::Div::Test = 1\n" );
				return true;
			}
			else
			{
				result = InfInt(0);
				rest = *this;
				result.pos = !( this->pos ^ src.pos );
				rest.pos = !( this->pos ^ src.pos );
				return true;
			}
		}
		
		rest = *this;
		result = InfInt(0);
		uint64 move = loga - logb;
		
		BoolTab tempSrc = src.val << move;
		
		while( true )
		{
			if( rest.val >= tempSrc )
			{
				rest.val -= tempSrc;
				result.val.SetBit( move, true );
			}
			
			if( move == 0 )
				break;
			--move;
			tempSrc >>= uint64(1);
		}
		
		result.pos = !( this->pos ^ src.pos );
		rest.pos = !( this->pos ^ src.pos );
		return true;
	}
	return false;
}

#undef printf

inline InfInt& InfInt::operator += ( const InfInt& src )		// need optimization
{
	(*this) = (*this) + src;
	return *this;
}

inline InfInt& InfInt::operator -= ( const InfInt& src )		// need optimization
{
	(*this) = (*this) - src;
	return *this;
}

inline InfInt& InfInt::operator *= ( const InfInt& src )		// need optimization
{
	(*this) = (*this) * src;
	return *this;
}

/*

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
			uint64 dst = this->val.val.size() * sizeof(uint64) * 8;
			for( ; dst > 0; --dst )
			{
				if( this->val.GetBit( dst ) )
					return InfInt(dst);
			}
		}
	}
	return InfInt(0);
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
	if( val )
	{
		this->val.val.resize( 1 );
		this->val.val.front() = uint64(val);
	}
	else
	{
		this->val.val.resize( 0 );
	}
}

InfInt::InfInt( const unsigned long long int val )
{
	this->pos = true;
	if( val )
	{
		this->val.val.resize( 1 );
		this->val.val.front() = val;
	}
	else
	{
		this->val.val.resize( 0 );
	}
}


InfInt::InfInt( const int val )
{
	if( val < 0 )
	{
		this->pos = false;
		this->val.val.resize( 1 );
		this->val.val.front() = uint64(val*-1);
	}
	else if( val == 0 )
	{
		this->pos = true;
		this->val.val.resize( 0 );
	}
	else
	{
		this->val.val.resize( 1 );
		this->pos = true;
		this->val.val.front() = uint64(val);
	}
}


};

#endif


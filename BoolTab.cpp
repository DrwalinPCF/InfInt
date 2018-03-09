
#ifndef BOOLTAB_CPP
#define BOOLTAB_CPP

#include "BoolTab.h"

inline void BoolTab::ClearLeadingZeros()
{
	if( this->val.size() )
	{
		uint64 i = this->val.size();
		
		for( i = this->val.size(); i > 0; --i )
			if( this->val[i-1] != 0 )
				break;
		
		this->val.resize( i );
	}
}

inline void BoolTab::Clear()
{
	this->val.clear();
}

inline bool BoolTab::GetBit( const uint64 pos ) const
{
	if( pos >= 0 && pos < this->val.size()*BoolTab::bits )
		return bool( this->val[pos/BoolTab::bits] & (uint64(1)<<(pos%BoolTab::bits)) );
	return false;
}

inline uint64 BoolTab::GetSize() const
{
	return this->val.size();
}

inline void BoolTab::SetBit( const uint64 pos, const bool value )
{
	if( pos >= 0 )
	{
		if( pos >= this->val.size()*BoolTab::bits )
		{
			this->val.resize( unsigned( (pos+BoolTab::bits)/BoolTab::bits ) );
		}
		
		if( GetBit( pos ) != value )
		{
			if( value )
			{
				this->val[pos/BoolTab::bits] |= uint64(1) << uint64(pos%BoolTab::bits);
			}
			else
			{
				this->val[pos/BoolTab::bits] -= uint64(1) << uint64(pos%BoolTab::bits);
				//ClearLeadingZeros();
			}
		}
	}
}

inline BoolTab& BoolTab::operator = ( const BoolTab& src )
{
	this->val = src.val;
}

inline BoolTab BoolTab::operator ~ ( void ) const
{
	BoolTab dst;
	dst.val.resize( this->val.size() );
	uint64 i = 0;
	for( ; i < this->val.size(); ++i )
		dst.val[i] = ~this->val[i];
	return dst;
}

inline BoolTab BoolTab::operator & ( const BoolTab& src ) const
{
	BoolTab dst;
	uint64 i = 0;
	
	dst.val.resize( src.val.size() < this->val.size() ? this->val.size() : src.val.size() );
	
	for( ; i < this->val.size(); ++i )
		dst.val[i] = this->val[i] & src.val[i];
	
	return dst;
}

inline BoolTab BoolTab::operator | ( const BoolTab& src ) const
{
	BoolTab dst;
	uint64 i = 0;
	
	dst.val.resize( src.val.size() < this->val.size() ? this->val.size() : src.val.size() );
	
	for( ; i < this->val.size(); ++i )
		dst.val[i] = this->val[i] | src.val[i];
	
	return dst;
}

inline BoolTab BoolTab::operator ^ ( const BoolTab& src ) const
{
	BoolTab dst;
	uint64 i = 0;
	
	dst.val.resize( src.val.size() < this->val.size() ? this->val.size() : src.val.size() );
	
	for( ; i < this->val.size(); ++i )
		dst.val[i] = this->val[i] ^ src.val[i];
	
	return dst;
}

inline BoolTab BoolTab::operator << ( const uint64 src ) const
{
	BoolTab dst;
	
	uint64 full = src / bits;
	uint64 rest = src % bits;
	
	dst.val.resize( unsigned( this->val.size() + full + uint64(rest!=0) + 1 ) );
	
	memset( &(dst.val.front()), 0, dst.val.size()*sizeof(uint64) );
	
	for( uint64 i = 0; i < this->val.size(); ++i )
		dst.val[i+full] |= this->val[i] << rest;
	if( rest )
		for( uint64 i = 0; i < this->val.size(); ++i )
			dst.val[i+full+1] |= this->val[i] >> (bits-rest);
	
	//dst.ClearLeadingZeros();
	return dst;
}

inline BoolTab BoolTab::operator >> ( const uint64 src ) const
{
	BoolTab dst;
	
	uint64 full = src / bits;
	uint64 rest = src % bits;
	
	if( this->val.size() > full )
		dst.val.resize( unsigned( this->val.size() - full ) );
	else
	{
		dst.val.clear();
		return dst;
	}
	
	memset( &(dst.val.front()), 0, dst.val.size()*sizeof(uint64) );
	
	for( uint64 i = full; i < this->val.size(); ++i )
		dst.val[i-full] |= this->val[i] >> rest;
	if( rest )
		for( uint64 i = full+1; i < this->val.size(); ++i )
			dst.val[i-full-1] |= this->val[i] << (bits-rest);
	
	//dst.ClearLeadingZeros();
	return dst;
}

inline BoolTab& BoolTab::operator <<= ( const uint64 src )
{
	uint64 full = src / bits;
	uint64 rest = src % bits;
	
	std::vector < uint64 > temp = this->val;
	
	this->val.resize( unsigned( temp.size() + full + uint64(rest!=0) + 1 ) );
	
	memset( &(this->val.front()), 0, this->val.size()*sizeof(uint64) );
	
	/*
	for( uint64 i = 0; i < temp.size(); ++i )
	{
		this->val[i+full] |= temp[i] << rest;
		if(rest)
			this->val[i+full+1] |= temp[i] >> (bits-rest);
	}
	*/
	
	for( uint64 i = 0; i < temp.size(); ++i )
		this->val[i+full] |= temp[i] << rest;
	if(rest)
		for( uint64 i = 0; i < temp.size(); ++i )
			this->val[i+full+1] |= temp[i] >> (bits-rest);
	
	//ClearLeadingZeros();
	return *this;
}

inline BoolTab& BoolTab::operator >>= ( const uint64 src )
{
	uint64 full = src / bits;
	uint64 rest = src % bits;
	
	std::vector < uint64 > temp = this->val;
	
	if( temp.size() /*+ uint64(rest!=0)*/ > full )
		this->val.resize( unsigned( temp.size() /*+ uint64(rest!=0)*/ - full ) );
	else
	{
		this->val.clear();
		return *this;
	}
	
	memset( &(this->val.front()), 0, this->val.size()*sizeof(uint64) );
	
	/*
	for( uint64 i = full; i < temp.size(); ++i )
	{
		this->val[i-full] |= temp[i] >> rest;
		this->val[i-full-1] |= temp[i] << (bits-rest);
	}
	*/
	
	for( uint64 i = full; i < temp.size(); ++i )
		this->val[i-full] |= temp[i] >> rest;
	if( rest )
		for( uint64 i = full+1; i < temp.size(); ++i )
			this->val[i-full-1] |= temp[i] << (bits-rest);
	
	//ClearLeadingZeros();
	return *this;
}

inline BoolTab& BoolTab::operator &= ( const BoolTab& src )
{
	uint64 i = 0;
	
	this->val.resize( src.val.size() < this->val.size() ? this->val.size() : src.val.size() );
	
	for( ; i < this->val.size(); ++i )
		this->val[i] &= src.val[i];
	
	return *this;
}

inline BoolTab& BoolTab::operator |= ( const BoolTab& src )
{
	uint64 i = 0;
	
	this->val.resize( src.val.size() < this->val.size() ? this->val.size() : src.val.size() );
	
	for( ; i < this->val.size(); ++i )
		this->val[i] |= src.val[i];
	
	return *this;
}

inline BoolTab& BoolTab::operator ^= ( const BoolTab& src )
{
	uint64 i = 0;
	
	this->val.resize( src.val.size() < this->val.size() ? this->val.size() : src.val.size() );
	
	for( ; i < this->val.size(); ++i )
		this->val[i] ^= src.val[i];
	
	return *this;
}

inline bool BoolTab::operator < ( const BoolTab& src ) const
{
	uint64 i;
	if( this->val.size() < src.val.size() )
		return true;
	if( this->val.size() > src.val.size() )
		return false;
	for( i = this->val.size()-1; i > 0; --i )
	{
		if( this->val[i] < src.val[i] )
			return true;
		if( this->val[i] > src.val[i] )
			return false;
	}
	if( this->val[i] < src.val[i] )
		return true;
	return false;
}

inline bool BoolTab::operator <= ( const BoolTab& src ) const
{
	uint64 i;
	if( this->val.size() < src.val.size() )
		return true;
	if( this->val.size() > src.val.size() )
		return false;
	for( i = this->val.size()-1; i > 0; --i )
	{
		if( this->val[i] < src.val[i] )
			return true;
		if( this->val[i] > src.val[i] )
			return false;
	}
	if( this->val[i] > src.val[i] )
		return false;
	return true;
}

inline bool BoolTab::operator > ( const BoolTab& src ) const
{
	uint64 i;
	if( this->val.size() > src.val.size() )
		return true;
	if( this->val.size() < src.val.size() )
		return false;
	for( i = this->val.size()-1; i > 0; --i )
	{
		if( this->val[i] > src.val[i] )
			return true;
		if( this->val[i] < src.val[i] )
			return false;
	}
	if( this->val[i] > src.val[i] )
		return true;
	return false;
}

inline bool BoolTab::operator >= ( const BoolTab& src ) const
{
	uint64 i;
	if( this->val.size() > src.val.size() )
		return true;
	if( this->val.size() < src.val.size() )
		return false;
	for( i = this->val.size()-1; i > 0; --i )
	{
		if( this->val[i] > src.val[i] )
			return true;
		if( this->val[i] < src.val[i] )
			return false;
	}
	if( this->val[i] < src.val[i] )
		return false;
	return true;
}

inline bool BoolTab::operator == ( const BoolTab& src ) const
{
	return this->val == src.val;
}

inline bool BoolTab::operator != ( const BoolTab& src ) const
{
	return this->val != src.val;
}


inline BoolTab BoolTab::operator + ( const BoolTab& src ) const
{
	BoolTab dst;
	uint64 carryFlag = 0, i = 0, max, min;
	if( this->val.size() < src.val.size() )
	{
		min = this->val.size();
		max = src.val.size();
	}
	else
	{
		max = this->val.size();
		min = src.val.size();
	}
	
	dst.val.resize( (max+uint64(1))>max ? max+uint64(1) : max, uint64(0) );
	
	for( ; i < min; ++i )
	{
		dst.val[i] = this->val[i] + src.val[i] + carryFlag;
		if( dst.val[i] < this->val[i] || dst.val[i] < src.val[i] )
			carryFlag = 1;
		else
			carryFlag ^= carryFlag;
	}
	
	if( this->val.size() < src.val.size() )
	{
		for( ; i < max; ++i )
		{
			dst.val[i] = src.val[i] + carryFlag;
			if( dst.val[i] < src.val[i] )
				carryFlag = 1;
			else
				for( ++i; i < max; ++i )
					dst.val[i] = src.val[i];
		}
	}
	else
	{
		for( ; i < max; ++i )
		{
			dst.val[i] = this->val[i] + carryFlag;
			if( dst.val[i] < this->val[i] )
				carryFlag = 1;
			else
				for( ++i; i < max; ++i )
					dst.val[i] = this->val[i];
		}
	}
	
	if( i < dst.val.size() )
		dst.val[i] = carryFlag;
	
	return dst;
}

inline BoolTab BoolTab::operator - ( const BoolTab& src ) const
{
	BoolTab dst;
	uint64 carryFlag = 1, i = 0, max, min;
	if( this->val.size() < src.val.size() )
	{
		min = this->val.size();
		max = src.val.size();
	}
	else
	{
		max = this->val.size();
		min = src.val.size();
	}
	
	dst.val.resize( (max+uint64(2))>max ? max+uint64(2) : max, uint64(0) );
	
	
	for( ; i < min; ++i )
	{
		dst.val[i] = this->val[i] + (~src.val[i]) + carryFlag;
		if( dst.val[i] < this->val[i] || dst.val[i] < (~src.val[i]) )
			carryFlag = 1;
		else
			carryFlag ^= carryFlag;
	}
	
	if( this->val.size() < src.val.size() )
	{
		for( ; i < max; ++i )
		{
			dst.val[i] = (~src.val[i]) + carryFlag;
			if( dst.val[i] < src.val[i] )
				carryFlag = 1;
			else
			{
				printf( "\n BoolTab::operator-()::ErrorCode = 1. Please report this to Drwalin." );
				printf( "\n These error means that: a-b was called when b>a\n" );
				for( ++i; i < max; ++i )
					dst.val[i] = ~src.val[i];
			}
		}
	}
	else
	{
		for( ; i < max; ++i )
		{
			dst.val[i] = this->val[i] + (uint64(0)-uint64(1)) + carryFlag;
			if( dst.val[i] < (uint64(0)-uint64(1)) )
				carryFlag = 1;
			else
				carryFlag ^= 0;
		}
	}
	
	if( i < dst.val.size() )
		dst.val[i] = carryFlag;
	
	dst.ClearLeadingZeros();
	if( dst.val.size() )
		dst.val.resize( dst.val.size() - 1 );
	
	return dst;
}


/*
inline BoolTab& BoolTab::operator += ( const BoolTab& src );
inline BoolTab& BoolTab::operator -= ( const BoolTab& src );
inline BoolTab& BoolTab::Increment();
inline BoolTab& BoolTab::Decrement();
*/

inline void * BoolTab::GetValue()
{
	return &(this->val.front());
}

inline void BoolTab::FromData( const void * data, const uint64 bytes )
{
	this->val.resize( bytes/sizeof(uint64) + uint64(bytes%sizeof(uint64) ? 1 : 0 ) );
	memset( &(this->val.front()), 0, this->val.size()*sizeof(uint64) );
	memcpy( &(this->val.front()), data, bytes );
	//ClearLeadingZeros();
}

BoolTab::BoolTab()
{
}

BoolTab::BoolTab( const uint64 src )
{
	this->val.resize( 1 );
	this->val.front() = src;
}

#endif

// Scan & Print:

#include <cstdio>

void PrintBinary( BoolTab a )
{
	uint64 i = 0;
	for( i = 0; i < a.GetSize()*BoolTab::bits; ++i )
	{
		printf( "%i", a.GetBit(i) ? 1 : 0 );
	}
}

void ScanBinary( BoolTab& a )
{
	a.Clear();
	char * str = new char[1<<20];
	scanf( "%s", str );
	uint64 i = 0;
	for( ; str[i]; ++i )
		a.SetBit( i, str[i]=='1' );
	delete[] str;
}




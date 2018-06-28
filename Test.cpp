
#include "InfInt.cpp"

#include "infint2.0.cpp"

#include <cstdlib>
#include <ctime>
#include <string>

std::string ToString( InfInt vals )
{
	InfInt val = vals;
	std::vector < unsigned int > ch;
	std::string dst = "";
	if( val < 0 )
	{
		dst += "-";
		val = -val;
	}
	for( ; val != 0; val /= 16 )
	{
		ch.push_back((val%16).toUnsignedInt());
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

My::InfInt Mul( My::InfInt pow )
{
	My::InfInt a(10);
	My::InfInt dst(0);
	My::InfInt i(0);
	for( ; i < pow; i = i + My::InfInt(1) )
		dst = dst + a;
	return dst;
}

std::string ToString( const My::InfInt& val )
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

#include <conio.h>
#include <ctime>

int main()
{
	srand( time( NULL ) );
	
	My::InfInt a[100];
	InfInt b[100];
	uint64 tempu = 0, tempu2, j;
	tempu = (uint64(rand())<<uint64(48)) + (uint64(rand())<<uint64(32)) + (uint64(rand())<<uint64(16)) + uint64(rand());
	
	int i;
	InfInt counter = 0, errorCounter = 0;
	
	a[0] = 311;
	b[0] = 311;
	
	while( true )//for( uint64 efbsuvesfjsakfhesabfjkkfba = 0; efbsuvesfjsakfhesabfjkkfba < 100; ++efbsuvesfjsakfhesabfjkkfba )
	{
		tempu = (uint64(rand())<<uint64(48)) + (uint64(rand())<<uint64(32)) + (uint64(rand())<<uint64(16)) + uint64(rand());
		//tempu  = 311*311*311*311*311*311*311*311;
		//tempu /= 311;
		//tempu >>= 33;
		
		a[0] *= tempu;
		b[0] *= tempu;
		
		a[0] += tempu;
		a[0] += a[0];
		a[0] += a[0];
		b[0] += tempu;
		b[0] += b[0];
		b[0] += b[0];
		
		
		
		
		
		
		
		
		/*
		a[0] *= ( a[0] * a[0] );
		a[1] = a[0] >> My::InfInt(113);
		a[0].Div( a[1], a[2], a[3] );
		
		b[0] *= ( b[0] * b[0] );
		b[1] = b[0] / pow( 2, 113 );
		b[2] = b[0] / b[1];
		b[3] = b[0] % b[1];
		*/
		
		for( i = 0; i < 100; ++i )
		{
			if( ToString( a[i] ) != ToString( b[i] ) )
			{
				++errorCounter;
				printf( "\n " );
				std::cout << ToString( a[i] );
				printf( " == " );
				std::cout << ToString( b[i] );
				printf( "  : ( %i )", i );
			}
		}
		
		++counter;
		
		if( counter % InfInt(1) == InfInt(0) )
		{
			std::cout << "\n Counter = " << counter << "   ErrorCounter = " << errorCounter << "   Log_10= " << log( InfInt(10), b[0] );
//			printf( "      My::InfInt = %s   InfInt = %s ", ToString(a[0]).c_str(), ToString(b[0]).c_str() );
		}
	}
	
	return 0;
}




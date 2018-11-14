
//  a *= rand
// 64:30000 - 11730ms
// 64:30000 - 9289ms
// 64:30000 - 9254ms
// 64:30000 - 12177ms
// 64:30000 - 12186ms ; 38183ms
// 32:30000 - ...
// 64:10000 - 886ms, 3099ms, 6447ms, 12036ms, 19864ms, 29731ms, 42744ms
// 32:10000 - 
// 64:1000 - 13ms, 36ms, 72ms, 132ms, 218ms, 318ms, ...
// 32:1000 - 4219ms, 23755ms
//  a += rand
// 1000000 - 1027ms

#define ENV64X
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

My::InfInt Mul( My::InfInt a, My::InfInt pow )
{
	//My::InfInt a(10);
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
	/*
	std::cout << "\n" << ToString( InfInt( uint64(int64(-1)) ) * InfInt( uint64(int64(-1)) ) ) << "\n";
	*/
	
	srand( time( NULL ) );
	
	My::InfInt a[100];
	InfInt b[100];
	uint64 tempu = 0, tempu2, j;
	tempu = (uint64(rand())<<uint64(48)) + (uint64(rand())<<uint64(32)) + (uint64(rand())<<uint64(16)) + uint64(rand());
	
	int i;
	uint64 counter = 0, errorCounter = 0;
	
	a[0] = 311;
	b[0] = 311;
	
	while( true )
	{
		tempu = (uint64(rand())<<uint64(48)) + (uint64(rand())<<uint64(32)) + (uint64(rand())<<uint64(16)) + uint64(rand());
		
		a[0] *= My::InfInt( tempu );
		//b[0] *= InfInt( tempu );
		
		
		
		
		
		
		
		
		/*
		a[0] *= ( a[0] * a[0] );
		a[1] = a[0] >> My::InfInt(113);
		a[0].Div( a[1], a[2], a[3] );
		
		b[0] *= ( b[0] * b[0] );
		b[1] = b[0] / pow( 2, 113 );
		b[2] = b[0] / b[1];
		b[3] = b[0] % b[1];
		*/
		
		/*
		for( i = 0; i < 100; ++i )
		{
			if( ToString( a[i] ) != ToString( b[i] ) )
			{
				++errorCounter;
				//if( counter % InfInt(10) == InfInt(0) )
				{
					printf( "\n " );
					std::cout << ToString( a[i] );
					printf( " == " );
					std::cout << ToString( b[i] );
					printf( "  : ( %i )", i );
				}
			}
		}
		*/
		
		++counter;
		if( counter % 10000 == 0 )
		{
			std::cout << "\n Counter = " << counter << "   ErrorCounter = " << errorCounter << /*"   Log_10= " << log( InfInt(10), b[0] ) << */ "   Time: " << clock();
//			printf( "      My::InfInt = %s   InfInt = %s ", ToString(a[0]).c_str(), ToString(b[0]).c_str() );
		}
	}
	
	return 0;
}




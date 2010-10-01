/**
 * @file testHashTree.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/09/02
 *
 * Functions for testing class HashTree.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"

#include "Board/Board.h"
#include "DGtal/io/colormaps/HueShadeColorMap.h"
#include "DGtal/io/colormaps/GrayscaleColorMap.h"
#include "DGtal/io/colormaps/GradientColorMap.h"
#include "DGtal/io/colormaps/ColorBrightnessColorMap.h"

#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/kernel/images/ImageContainerByHashTree.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace LibBoard;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class HashTree.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testHashTree()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing simple init ..." );


  typedef SpaceND<int,4> Space4Type;
  typedef HyperRectDomain<Space4Type> TDomain;
  typedef TDomain::Point Point;

  //Default image selector = STLVector
  typedef experimental::ImageContainerByHashTree<TDomain, int > Image;

  const int t[ ] = { 1, 2, 3 ,4};
  const int t2[ ] = { 5, 5, 3 ,4};
  Point a ( t );
  Point b ( t2 );

  ///Domain characterized by points a and b
  Image myImage ( 3, 3,0 );

  trace.info() << myImage;
  nbok += true ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "true == true" << std::endl;
  trace.endBlock();

  return nbok == nb;
}


/**
 * Example of a test. To be completed.
 *
 */
bool testGetSetVal()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  typedef SpaceND<int,2> SpaceType;
  typedef HyperRectDomain<SpaceType> TDomain;
  typedef TDomain::Point Point;
  Board board;
  typedef HueShadeColorMap<unsigned char,2> HueTwice;
  board.setUnit(Board::UCentimeter);


  //Default image selector = STLVector
  typedef experimental::ImageContainerByHashTree<TDomain, int > Image;

  Point a( 1,1 );
  Point b ( 50,50 );
  Point c(15,15);
  Point d(128,128);


  trace.beginBlock ( "Image init" );
  ///Domain characterized by points
  Image myImage ( 3, 8, 0 );
  trace.info() << myImage;
  trace.endBlock();
  

  trace.beginBlock("SetVal");
  for( a[1] = 0; a[1] < 256; a[1]++)
    for( a[0] = 0; a[0] < 256; a[0]++)
      {
	if ( pow((double)(a[0]-128),3.0) - pow((double)(a[1]-128),3.0) < pow(32.0,3.0))
	  myImage.setValue(a, 30);
	else
	  if ( pow((double)(a[0]-128),3.0) - pow((double)(a[1]-128),3.0) < pow(64.0,3.0))
	    myImage.setValue(a, 10);	
      }
  trace.endBlock();
  
  bool result=true;
  
  trace.beginBlock("GetVal consistency test");
  for( a[1] = 0; a[1] < 256; a[1]++)
    for( a[0] = 0; a[0] < 256; a[0]++)
      {
	if ( pow((a[0]-128),3.0) - pow((a[1]-128),3.0) < pow(32,3.0))
	  result = result && (myImage(a) == 30);
	else
	  if ( pow((a[0]-128),3.0) - pow((a[1]-128),3.0) < pow(64,3.0))
	    result = result && (myImage(a) == 10);	    
      }
  trace.endBlock();
  
  if (result)
    trace.info() << "Get/Set test passed"<<endl;
  else
    trace.error() << "Get/Set test error"<<endl;
  nbok += result ? 1 : 0;
  nb++;
  
  trace.info() << myImage;
   
  myImage.selfDraw<HueTwice>(board,0,255);
  board.saveSVG( "hashtree.svg" );


  ///Domain characterized by points
  Image myImage2 ( 5, 8, 0 );
  
  trace.beginBlock("SetVal (keysize=5)");
  for( a[1] = 0; a[1] < 256; a[1]++)
    for( a[0] = 0; a[0] < 256; a[0]++)
      {
	if ( pow((a[0]-128),3.0) - pow((a[1]-128),3.0) < pow(32,3.0))
	  myImage2.setValue(a, 30);
	else
	  if ( pow((a[0]-128),3.0) - pow((a[1]-128),3.0) < pow(64,3.0))
	    myImage2.setValue(a, 10);	
      }
  trace.endBlock();
  
  result=true;
  
  trace.beginBlock("GetVal consistency test  (keysize=5)");
  for( a[1] = 0; a[1] < 256; a[1]++)
    for( a[0] = 0; a[0] < 256; a[0]++)
      {
	if ( pow((a[0]-128),3.0) - pow((a[1]-128),3.0) < pow(32,3.0))
	  result = result && (myImage2(a) == 30);
	else
	  if ( pow((a[0]-128),3.0) - pow((a[1]-128),3.0) < pow(64,3.0))
	    result = result && (myImage2(a) == 10);	    
      }
  trace.endBlock();
  
  if (result)
    trace.info() << "Get/Set test passed"<<endl;
  else
    trace.error() << "Get/Set test error"<<endl;
  nbok += result ? 1 : 0;
  nb++;
  
  trace.warning() << "(" << nbok << "/" << nb << ") "
	       << "true == true" << std::endl;


  return nbok == nb;
}


bool testBadKeySizes()
{
   unsigned int nbok = 0;
  unsigned int nb = 0;

  typedef SpaceND<int,2> SpaceType;
  typedef HyperRectDomain<SpaceType> TDomain;
  typedef TDomain::Point Point;
  Board board;
  typedef HueShadeColorMap<unsigned char,2> HueTwice;
  board.setUnit(Board::UCentimeter);


  //Default image selector = STLVector
  typedef experimental::ImageContainerByHashTree<TDomain, char> Image;

  Point d(128,128);

  trace.beginBlock ( "Test maximal depth >  number of bits of the HashKey type" );
  Image myImage ( 3, 80, 0 );
  trace.info() << myImage;
  trace.endBlock();

  trace.beginBlock ( "Test morton hash size >  number of bits of the HashKey type" );
  ///This should raise an ASSERT abort if uncommented
  //  Image myImage2 ( 80, 8, 0 );
  //trace.info() << myImage2;
  trace.endBlock();
  
  //Default image selector = STLVector
  typedef experimental::ImageContainerByHashTree<TDomain, unsigned int, DGtal::uint32_t> Image2;
  trace.beginBlock ( "Changing the HashKey type" );
  Image2 myImage3( 3, 80, 0 );
  trace.info() << myImage3;
  trace.endBlock();


  return true;  
}

//////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class HashTree" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testHashTree() && testGetSetVal() && testBadKeySizes();  // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
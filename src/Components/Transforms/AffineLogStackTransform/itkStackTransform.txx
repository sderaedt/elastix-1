/*======================================================================

  This file is part of the elastix software.

  Copyright (c) University Medical Center Utrecht. All rights reserved.
  See src/CopyrightElastix.txt or http://elastix.isi.uu.nl/legal.php for
  details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE. See the above copyright notices for more information.

======================================================================*/

#ifndef _itkStackTransform_txx
#define _itkStackTransform_txx

#include "itkStackTransform.h"
#include <fstream>

namespace itk
{


/**
 * ********************* Constructor ****************************
 */

template < class TScalarType, unsigned int NInputDimensions, unsigned int NOutputDimensions >
StackTransform<TScalarType,NInputDimensions,NOutputDimensions>
::StackTransform(): Superclass( OutputSpaceDimension ),
  m_NumberOfSubTransforms( 0 ),
  m_StackSpacing( 1.0 ),
  m_StackOrigin( 0.0 )
{

} // end Constructor


/**
 * ************************ SetParameters ***********************
 */

template < class TScalarType, unsigned int NInputDimensions, unsigned int NOutputDimensions >
void
StackTransform<TScalarType,NInputDimensions,NOutputDimensions>::SetParameters( const ParametersType & param )
{
  // All subtransforms should be the same and should have the same number of parameters.
  // Here we check if the number of parameters is #subtransforms * #parameters per subtransform.
  if ( param.GetSize() != this->GetNumberOfParameters() )
  {
    itkExceptionMacro( << "Number of parameters does not match the number of subtransforms * the number of parameters per subtransform." );
  }

  // Set separate subtransform parameters
  const NumberOfParametersType numSubTransformParameters = this->m_SubTransformContainer[ 0 ]->GetNumberOfParameters();
  //this->SubtractMean(param);

  for ( unsigned int t = 0; t < this->m_NumberOfSubTransforms; ++t )
  {
    // MS, \todo: the new itk::TransformParameters only have constructors taking 1 argument
    ParametersType subparams ( ParametersArrayType( &( param.data_block()[ t * numSubTransformParameters ] ), numSubTransformParameters, false ) );
    //ParametersType subparams( numSubTransformParameters );
    //unsigned int index = t * numSubTransformParameters;
    //for ( unsigned int p = 0; p < numSubTransformParameters; ++p, ++index )
    //{
    //  subparams[ p ] = param[ index ];
    //}
    this->m_SubTransformContainer[ t ]->SetParametersByValue( subparams );
  }

  this->Modified();
} // end SetParameters


/**
 * ************************ GetParameters ***********************
 */
template < class TScalarType, unsigned int NInputDimensions, unsigned int NOutputDimensions >
const typename StackTransform<TScalarType,NInputDimensions,NOutputDimensions>::ParametersType &
StackTransform< TScalarType, NInputDimensions, NOutputDimensions >
::GetParameters ( void ) const
{
//    ofstream file; ofstream file2;
//    file.open("parameters.txt", ios::app);
//    file2.open("initialparameters.txt", ios::app);
//    this->m_Parameters.SetSize( this->GetNumberOfParameters() );

//    ParametersType dummyparams;
//    ParametersType dummyidentityparams;
//    dummyparams.SetSize(this->GetNumberOfParameters());
//    dummyidentityparams.SetSize(this->GetNumberOfParameters());

//    const NumberOfParametersType numSubTransformParameters = this->m_SubTransformContainer[ 0 ]->GetNumberOfParameters();
//    unsigned int lastDimSize = this->GetNumberOfParameters()/numSubTransformParameters;

//    unsigned int i = 0;
//    for ( unsigned int t = 0; t < this->m_NumberOfSubTransforms; ++t )
//    {
//        const ParametersType & subparams = this->m_SubTransformContainer[ t ]->GetParameters();
//        for ( unsigned int p = 0; p < this->m_SubTransformContainer[ 0 ]->GetNumberOfParameters(); ++p, ++i )
//        {
//            dummyparams[ i ] = subparams[ p ];
//        }
//    }
//    file2 << dummyparams << std::endl;

//    unsigned int j = 0; unsigned int o=0;
//    for ( unsigned int t = 0; t < this->m_NumberOfSubTransforms; ++t )
//    {
//        ParametersType identitysubparams;
//        identitysubparams.SetSize(this->m_SubTransformContainer[ 0 ]->GetNumberOfParameters());
//        vnl_matrix<double> identitymatrix(identitysubparams.size()/2,identitysubparams.size()/2);
//        identitymatrix.set_identity();
//        for(unsigned int s = 0; s < identitysubparams.size()/2;  s++)
//        {
//            for(unsigned int q = 0; q < identitysubparams.size()/2; q++)
//            {
//                identitysubparams[o] = identitymatrix(s,q);
//                o++;
//            }
//        }
//        for ( unsigned int p = 0; p < this->m_SubTransformContainer[ 0 ]->GetNumberOfParameters(); ++p, ++i )
//        {
//            dummyidentityparams[ j ] = identitysubparams[ p ];
//        }
//    }
//    //subtract mean from parameters
//    const unsigned int numParametersPerLastDimension = this->GetNumberOfParameters() / lastDimSize;
//    ParametersType mean ( numParametersPerLastDimension );
//    mean.Fill( 0.0 );

//    /** Compute mean per control point. */
//    for ( unsigned int t = 0; t < lastDimSize; ++t )
//    {
//        const unsigned int startc = numParametersPerLastDimension * t;
//        for ( unsigned int c = startc; c < startc + numParametersPerLastDimension; ++c )
//        {
//           const unsigned int index = c % numParametersPerLastDimension;
//            mean[ index ] += dummyparams[ c ];
//        }
//    }
//    mean /= static_cast< double >( lastDimSize );

//    /** Update derivative per control point. */
//    for ( unsigned int t = 0; t < lastDimSize; ++t )
//    {
//        const unsigned int startc = numParametersPerLastDimension * t;
//        for ( unsigned int c = startc; c < startc + numParametersPerLastDimension; ++c )
//        {
//           const unsigned int index = c % numParametersPerLastDimension;
//           dummyparams[ c ] -= mean[ index ];
//        }
//    }

//    dummyparams += dummyidentityparams;

  //Fill params with parameters of subtransforms
  unsigned int k = 0;
  for ( unsigned int t = 0; t < this->m_NumberOfSubTransforms; ++t )
  {
    const ParametersType & subparams = this->m_SubTransformContainer[ t ]->GetParameters();
    for ( unsigned int p = 0; p < this->m_SubTransformContainer[ 0 ]->GetNumberOfParameters(); ++p, ++k )
    {
      this->m_Parameters[ k ] = subparams[ p ];
    }
  }
  //this->m_Parameters = dummyparams;

  //file << this->m_Parameters << std::endl;

  return this->m_Parameters;
} // end GetParameters


/**
 * ********************* TransformPoint ****************************
 */

template < class TScalarType, unsigned int NInputDimensions, unsigned int NOutputDimensions >
typename StackTransform<TScalarType,NInputDimensions,NOutputDimensions>
::OutputPointType
StackTransform<TScalarType,NInputDimensions,NOutputDimensions>
::TransformPoint(const InputPointType & ipp ) const
{
  /** Reduce dimension of input point. */
  SubTransformInputPointType ippr;
  for ( unsigned int d = 0; d < ReducedInputSpaceDimension; ++d )
  {
    ippr[ d ] = ipp[ d ];
  }

  /** Transform point using right subtransform. */
  SubTransformOutputPointType oppr;
  const unsigned int subt
    = vnl_math_min( this->m_NumberOfSubTransforms - 1, static_cast<unsigned int>(
      vnl_math_max( 0,
      vnl_math_rnd( ( ipp[ ReducedInputSpaceDimension ] - m_StackOrigin ) / m_StackSpacing ) ) ) );
  oppr = this->m_SubTransformContainer[ subt ]->TransformPoint( ippr );

  /** Increase dimension of input point. */
  OutputPointType opp;
  for ( unsigned int d = 0; d < ReducedOutputSpaceDimension; ++d )
  {
    opp[ d ] = oppr[ d ];
  }

  opp[ ReducedOutputSpaceDimension ] = ipp[ ReducedInputSpaceDimension ];

  return opp;

} // end TransformPoint

/**
 * ********************* GetJacobian ****************************
 */

template < class TScalarType, unsigned int NInputDimensions, unsigned int NOutputDimensions >
void
StackTransform<TScalarType,NInputDimensions,NOutputDimensions>
::GetJacobian(
  const InputPointType & ipp,
  JacobianType & jac,
  NonZeroJacobianIndicesType & nzji ) const
{
  /** Reduce dimension of input point. */
  SubTransformInputPointType ippr;
  for ( unsigned int d = 0; d < ReducedInputSpaceDimension; ++d )
  {
    ippr[ d ] = ipp[ d ];
  }

  /** Get Jacobian from right subtransform. */
  const unsigned int subt
    = vnl_math_min( this->m_NumberOfSubTransforms - 1, static_cast<unsigned int>(
      vnl_math_max( 0,
      vnl_math_rnd( ( ipp[ ReducedInputSpaceDimension ] - m_StackOrigin ) / m_StackSpacing ) ) ) );
  SubTransformJacobianType subjac;
  this->m_SubTransformContainer[ subt ]->GetJacobian( ippr, subjac, nzji );

  /** Fill output Jacobian. */
  jac.set_size( InputSpaceDimension, nzji.size() );
  jac.Fill( 0.0 );

  for ( unsigned int d = 0; d < ReducedInputSpaceDimension; ++d )
  {
    for ( unsigned int n = 0; n < nzji.size(); ++n )
    {
      jac[ d ][ n ] = subjac[ d ][ n ];
    }
  }

  /** Update non zero Jacobian indices. */
  for ( unsigned int i = 0; i < nzji.size(); ++i )
  {
    nzji[ i ] += subt * this->m_SubTransformContainer[ 0 ]->GetNumberOfParameters();
  }


} // end GetJacobian()


/**
 * ********************* GetNumberOfNonZeroJacobianIndices ****************************
 */

template<class TScalarType, unsigned int NDimensions, unsigned int VSplineOrder>
unsigned long
StackTransform<TScalarType, NDimensions,VSplineOrder>
::GetNumberOfNonZeroJacobianIndices( void ) const
{
  return this->m_SubTransformContainer[ 0 ]->GetNumberOfNonZeroJacobianIndices();

} // end GetNumberOfNonZeroJacobianIndices()


} // end namespace itk


#endif

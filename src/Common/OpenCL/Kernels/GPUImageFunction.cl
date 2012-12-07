/*======================================================================

  This file is part of the elastix software.

  Copyright (c) University Medical Center Utrecht. All rights reserved.
  See src/CopyrightElastix.txt or http://elastix.isi.uu.nl/legal.php for
  details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE. See the above copyright notices for more information.

======================================================================*/
//
// \author Denis P. Shamonin and Marius Staring. Division of Image Processing,
// Department of Radiology, Leiden, The Netherlands
//
// This implementation was taken from elastix (http://elastix.isi.uu.nl/).
//
// \note This work was funded by the Netherlands Organisation for
// Scientific Research (NWO NRG-2010.02 and NWO 639.021.124).
//
// OpenCL implementation of itk::ImageFunction
//------------------------------------------------------------------------------
// Definition of GPUFunction 1D/2D/3D
typedef struct {
  uint start_index;
  uint end_index;
  float start_continuous_index;
  float end_continuous_index;
} GPUImageFunction1D;

typedef struct {
  uint2 start_index;
  uint2 end_index;
  float2 start_continuous_index;
  float2 end_continuous_index;
} GPUImageFunction2D;

typedef struct {
  uint3 start_index;
  uint3 end_index;
  float3 start_continuous_index;
  float3 end_continuous_index;
} GPUImageFunction3D;

//------------------------------------------------------------------------------
#ifdef DIM_1
bool interpolator_is_inside_buffer_1d(
  const float index,
  __constant GPUImageFunction1D *image_function )
{
  if ( !( index >= image_function->start_continuous_index
    && index < image_function->end_continuous_index ) )
  {
    return false;
  }

  return true;
}

#endif // DIM_1

//------------------------------------------------------------------------------
#ifdef DIM_2
bool interpolator_is_inside_buffer_2d(
  const float2 index,
  __constant GPUImageFunction2D *image_function )
{
  if ( !( index.x >= image_function->start_continuous_index.x
    && index.x < image_function->end_continuous_index.x ) )
  {
    return false;
  }
  if ( !( index.y >= image_function->start_continuous_index.y
    && index.y < image_function->end_continuous_index.y ) )
  {
    return false;
  }

  return true;
}

#endif // DIM_2

//------------------------------------------------------------------------------
#ifdef DIM_3
bool interpolator_is_inside_buffer_3d(
  const float3 index,
  __constant GPUImageFunction3D *image_function )
{
  if ( !( index.x >= image_function->start_continuous_index.x
    && index.x < image_function->end_continuous_index.x ) )
  {
    return false;
  }
  if ( !( index.y >= image_function->start_continuous_index.y
    && index.y < image_function->end_continuous_index.y ) )
  {
    return false;
  }
  if ( !( index.z >= image_function->start_continuous_index.z
    && index.z < image_function->end_continuous_index.z ) )
  {
    return false;
  }

  return true;
}

#endif // DIM_3

//------------------------------------------------------------------------------
// OpenCL 1D implementation of
// itkImageFunction::ConvertContinuousIndexToNearestIndex()
#ifdef DIM_1
uint convert_continuous_index_to_nearest_index_1d( const float cindex )
{
  return round( cindex );
}

#endif // DIM_1

//------------------------------------------------------------------------------
// OpenCL 2D implementation of
// itkImageFunction::ConvertContinuousIndexToNearestIndex()
#ifdef DIM_2
uint2 convert_continuous_index_to_nearest_index_2d( const float2 cindex )
{
  uint2 index;

  index.x = round( cindex.x );
  index.y = round( cindex.y );
  return index;
}

#endif // DIM_2

//------------------------------------------------------------------------------
// OpenCL 3D implementation of
// itkImageFunction::ConvertContinuousIndexToNearestIndex()
#ifdef DIM_3
uint3 convert_continuous_index_to_nearest_index_3d( const float3 cindex )
{
  uint3 index;

  //index.x = (uint)( cindex.x + 0.499999f );
  //index.y = (uint)( cindex.y + 0.499999f );
  //index.z = (uint)( cindex.z + 0.499999f );
  index.x = round( cindex.x );
  index.y = round( cindex.y );
  index.z = round( cindex.z );
  return index;
}

#endif // DIM_3

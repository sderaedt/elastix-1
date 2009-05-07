#ifndef __elxNormalizedCorrelationMetric_H__
#define __elxNormalizedCorrelationMetric_H__

#include "elxIncludes.h"
#include "itkNormalizedCorrelationImageToImageMetric2.h"

#include "elxTimer.h"

namespace elastix
{
using namespace itk;

	/**
	 * \class NormalizedCorrelationMetric
	 * \brief An metric based on the itk::NormalizedCorrelationImageToImageMetric2.
	 *
	 * The parameters used in this class are:
	 * \parameter Metric: Select this metric as follows:\n
	 *		<tt>(Metric "NormalizedCorrelation")</tt>
	 * \parameter SubtractMean: Flag to set if the sample mean is subtracted from the
	 *    sample values in the cross correlation formula. This typically results in narrower
	 *    valleys in the cost fucntion. Default value is true.\n
	 *		example: <tt>(SubtractMean "false")</tt> \n
	 * \parameter	UseAllPixels: Flag to force the metric to use ALL voxels for 
	 *		computing the metric value and its derivative in each iteration.
	 *    Choose one of {"true", "false"}. Default is "true". \n
	 *		example: <tt>(UseAllPixels "false")</tt> \n
	 *    note: the NewSamplesEveryIteration parameter is ignored by this metric.\n
	 * \parameter NumberOfSpatialSamples: The number of image voxels used for computing the
	 *		metric value and its derivative in each iteration. Must be given for each resolution.\n
	 *		example: <tt>(NumberOfSpatialSamples 2048 2048 4000)</tt> \n
	 *		The default is 5000.
	 *
	 * \ingroup Metrics
	 *
	 */

	template <class TElastix >
		class NormalizedCorrelationMetric:
		public
			NormalizedCorrelationImageToImageMetric2<
				ITK_TYPENAME MetricBase<TElastix>::FixedImageType,
				ITK_TYPENAME MetricBase<TElastix>::MovingImageType >,
		public MetricBase<TElastix>
	{
	public:

		/** Standard ITK-stuff. */
		typedef NormalizedCorrelationMetric										Self;
		typedef NormalizedCorrelationImageToImageMetric2<
			typename MetricBase<TElastix>::FixedImageType,
			typename MetricBase<TElastix>::MovingImageType >		Superclass1;
		typedef MetricBase<TElastix>													Superclass2;
		typedef SmartPointer<Self>														Pointer;
		typedef SmartPointer<const Self>											ConstPointer;
		
		/** Method for creation through the object factory. */
		itkNewMacro( Self );
		
		/** Run-time type information (and related methods). */
		itkTypeMacro( NormalizedCorrelationMetric, NormalizedCorrelationImageToImageMetric2 );
		
		/** Name of this class.
		 * Use this name in the parameter file to select this specific metric. \n
		 * example: <tt>(Metric "NormalizedCorrelation")</tt>\n
		 */
		elxClassNameMacro( "NormalizedCorrelation" );

		/** Typedefs inherited from the superclass. */
		typedef typename Superclass1::TransformType							TransformType;
		typedef typename Superclass1::TransformPointer 					TransformPointer;		
		typedef typename Superclass1::TransformJacobianType			TransformJacobianType;
		typedef typename Superclass1::InterpolatorType 					InterpolatorType;
		typedef typename Superclass1::MeasureType								MeasureType;
		typedef typename Superclass1::DerivativeType 						DerivativeType;
		typedef typename Superclass1::ParametersType 						ParametersType;
		typedef typename Superclass1::FixedImageType 						FixedImageType;
		typedef typename Superclass1::MovingImageType						MovingImageType;
		typedef typename Superclass1::FixedImageConstPointer 		FixedImageConstPointer;
		typedef typename Superclass1::MovingImageConstPointer		MovingImageConstPointer;
		
		/** The moving image dimension. */
		itkStaticConstMacro( MovingImageDimension, unsigned int,
			MovingImageType::ImageDimension );
		
		/** Other typedef's. */
		typedef typename Superclass1::FixedImageMaskType 				FixedMaskImageType;
		typedef typename Superclass1::MovingImageMaskType				MovingMaskImageType;
		typedef typename Superclass1::FixedImageMaskPointer			FixedMaskImagePointer;
		typedef typename Superclass1::MovingImageMaskPointer		MovingMaskImagePointer;
		
		/** Typedef's inherited from Elastix. */
		typedef typename Superclass2::ElastixType								ElastixType;
		typedef typename Superclass2::ElastixPointer						ElastixPointer;
		typedef typename Superclass2::ConfigurationType					ConfigurationType;
		typedef typename Superclass2::ConfigurationPointer			ConfigurationPointer;
		typedef typename Superclass2::RegistrationType					RegistrationType;
		typedef typename Superclass2::RegistrationPointer				RegistrationPointer;
		typedef typename Superclass2::ITKBaseType								ITKBaseType;
			
		/** Typedef for timer. */
		typedef tmr::Timer					TimerType;
		/** Typedef for timer. */
		typedef TimerType::Pointer	TimerPointer;

		/** Execute stuff before registration:
		 * \li Set the flag to subtract the mean.
		 * \li Set the flag to use all samples.
		 */
		virtual void BeforeRegistration(void);

		/** Execute stuff before each new pyramid resolution:
		 * \li Set the number of spatial samples.
		 */
		virtual void BeforeEachResolution(void);

		/** Sets up a timer to measure the intialisation time and
		 * calls the Superclass' implementation.
		 */
		virtual void Initialize(void) throw (ExceptionObject);

		/**
		 * Force the metric to base its computation on a new subset of image samples.
		 *
		 * This metric cannot respond to this function correctly. It is meant for stochastic
     * optimizers, to allow them to request a refreshment of the sample set.
		 * However, this metric can not deal with such a request.
		 * 
		 * It has two modes of operation, defined by the (UseAllPixels ...) option. If this
     * parameter is set to true, all voxels in the image are used. If set to false,
		 * every derivative/value calculation is based on a new, randomly selected subset
		 * of voxels. So, if you want to combine the metric with a stochastic optimizer,
		 * simply set the UseAllPixels parameter to false.
		 *
		 * Therefore, this metric just silently ignores the request.
		 */
		virtual void SelectNewSamples(void){};

	protected:

		/** The constructor. */
		NormalizedCorrelationMetric();
		/** The destructor. */
		virtual ~NormalizedCorrelationMetric() {}

	private:

		/** The private constructor. */
		NormalizedCorrelationMetric( const Self& );	// purposely not implemented
		/** The private copy constructor. */
		void operator=( const Self& );							// purposely not implemented
		
	}; // end class NormalizedCorrelationMetric


} // end namespace elastix


#ifndef ITK_MANUAL_INSTANTIATION
#include "elxNormalizedCorrelationMetric.hxx"
#endif

#endif // end #ifndef __elxNormalizedCorrelationMetric_H__
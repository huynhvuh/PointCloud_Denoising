/**
 * @name TEMPLATE FOR AUTONOMOUS DRIVING COMPONENTS
 * @copyright Gaussin Manugistique S.A. (c)
 * @author Vu-Hoi HUYNH
 * @brief Spherical projection of LIDAR PointCloud into 2D image.
 * @version 1.0
 * @date 02/06/2021
 * @comment 
 */

#include "SphericalProjection.hpp"

/******************************************************************************************************************************************************
CONSTRUCTORS & DESTRUCTORS
******************************************************************************************************************************************************/
// Constructor
SphericalProjection::SphericalProjection() {
	this->height 			= 32;		// pixel
	this->width 			= 512;		// pixel
	this->elevation_max 	= 15.0;		// degree
	this->elevation_min 	= -16.0;	// degree
	this->delta_elevation 	= 1.0;		// degree
	this->azimuth_max 		= 360.0;	// degree
	this->azimuth_min 		= 0.0;		// degree
	this->delta_azimuth 	= 0.09;		// degree
}

// Destructor
SphericalProjection::~SphericalProjection() {
}

/******************************************************************************************************************************************************
PUBLIC METHODS
******************************************************************************************************************************************************/
/** @brief Set parameters for object.
	@param _height Image height (pixel)
	@param _width Image width (pixel)
	@param _elevation_max Maximum elevation (degree)
	@param _elevation_min Minimum elevation (degree)
	@param _delta_elevation Elevation resolution (degree)
	@param _azimuth_max Maximum azimuth (degree)
	@param _azimuth_min Minimum azimuth (degree)
	@param _delta_azimuth Azimuth resolution (degree)
**/
void SphericalProjection::setParameters(int _height, int _width,
										double _elevation_max, double _elevation_min, double _delta_elevation, 
										double _azimuth_max, double _azimuth_min, double _delta_azimuth) {
	this->height 			= _height;			// pixel
	this->width 			= _width;			// pixel
	this->elevation_max 	= _elevation_max;	// degree
	this->elevation_min 	= _elevation_min;	// degree
	this->delta_elevation 	= _delta_elevation;	// degree
	this->azimuth_max 		= _azimuth_max;		// degree
	this->azimuth_min 		= _azimuth_min;		// degree
	this->delta_azimuth 	= _delta_azimuth;	// degree
}

	/** @brief Read inputs for object.
		@param _iAzimuths Azimuth data
		@param _iDistances Distance data
		@param _iIntensities Intensity data
    **/
void SphericalProjection::readInputs(	std::vector<double>& _iAzimuths,
										std::vector<double>& _iDistances,
										std::vector<double>& _iIntensities) {
	// Receives the inputs from the MAPS wrapper and saves them on the class
	this->iAzimuths 	= _iAzimuths;
	this->iDistances 	= _iDistances;
	this->iIntensities 	= _iIntensities;
}

/** @brief Process data for object.
**/
void SphericalProjection::processData() {
	// Check angles
	angleChecking(this->elevation_max, this->elevation_min, this->delta_elevation);
	angleChecking(this->azimuth_max, this->azimuth_min, this->delta_azimuth);

	// Correct image size
	sizeCorrection(this->height, this->elevation_max, this->elevation_min, this->delta_elevation);
	sizeCorrection(this->width, this->azimuth_max, this->azimuth_min, this->delta_azimuth);

	// Make image
	this->oImage = cv::Mat(this->height, this->width, CV_64FC(4), cv::Scalar::all(0));
	for (int i {0}; i < this->iAzimuths.size(); ++i) {
		double elevation = this->elevation_max;		// elevation angle in degree
		for (int j {0}; j < this->height; ++j) {
			int pixel_u = 0, pixel_v = 0;
			normalize(elevation, this->iAzimuths[i], &pixel_u, &pixel_v);
			this->oImage.at<cv::Vec4d>(pixel_u, pixel_v) = cv::Vec4d{elevation, this->iAzimuths[i], 
																	 this->iDistances[this->height * i + j], 
																	 this->iIntensities[this->height * i + j]};
			elevation -= 1;
		}
	}
}

/** @brief Write out the processed data.
	@param _oImage Image projected
**/
void SphericalProjection::writeOutputs(cv::Mat& _oImage) {
	// Pass the values of scores to the MAPS wrapper
	_oImage = this->oImage.clone();
}

/******************************************************************************************************************************************************
PRIVATE METHODS
******************************************************************************************************************************************************/
/** @brief Angle checking
 * 1. If maximum < minimum, then swap maximum and minimum values 
 * 2. If maximum - minimum = 360??, then these two values are equal and maximum -= resolution.
	@param maximum InputOutput maximum value
	@param minimum InputOutput minimum value
	@param resolution Input resolution value
**/
void SphericalProjection::angleChecking(double& maximum, double& minimum, const double resolution) {
    if (maximum < minimum)
        std::swap(maximum, minimum);
	maximum = (maximum - minimum == 360.0 ? maximum - resolution : maximum);
}

/** @brief Correct height/width based on their maximum value calculated from angle specification
	@param size InputOutput size value (height/width)
	@param maximum Input maximum value
	@param minimum Input minimum value
	@param resolution Input resolution value
**/
void SphericalProjection::sizeCorrection(int& size, const double maximum, const double minimum, const double resolution) {
	int max_size = int((maximum - minimum) / resolution) + 1;
	size = size > max_size || size < 0 ? max_size : size;
}

/** @brief Project a point into image plane.
	@param elevation Input elevation value
	@param azimuth Input azimuth value
	@param pixel_u Output pixel element u
	@param pixel_v Output pixel element v
**/
void SphericalProjection::normalize(const double elevation, const double azimuth, int* pixel_u, int* pixel_v) {
	// Calculate pixel u and make sure that it is in the range [0, this->height - 1]
	int u = round((elevation - this->elevation_min) / (this->elevation_max - this->elevation_min) * (this->height - 1));
	u = std::min(this->height - 1, u);
	u = std::max(0, u);
	*pixel_u = int(u);

	// Calculate pixel v and make sure that it is in the range [0, this->width - 1]
	int v = round((azimuth - this->azimuth_min) / (this->azimuth_max - this->azimuth_min) * (this->width - 1));
	v = std::min(this->width - 1, v);
	v = std::max(0, v);
	*pixel_v = int(v);
}

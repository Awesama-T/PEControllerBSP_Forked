/**
 ********************************************************************************
 * @file 		monitoring_library.h
 * @author 		Waqas Ehsan Butt
 * @date 		Apr 7, 2023
 *
 * @brief    
 ********************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 Taraz Technologies Pvt. Ltd.</center></h2>
 * <h3><center>All rights reserved.</center></h3>
 *
 * <center>This software component is licensed by Taraz Technologies under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the License. You may obtain 
 * a copy of the License at:
 *                        www.opensource.org/licenses/BSD-3-Clause</center>
 *
 ********************************************************************************
 */

#ifndef MONITORING_LIB_H_
#define MONITORING_LIB_H_

#ifdef __cplusplus
extern "C" {
#endif


/** @defgroup Monitoring_Library Monitoring Library
 * @brief Contains the declaration required for monitoring procedures
 * @{
 */
/********************************************************************************
 * Includes
 *******************************************************************************/
#include "general_header.h"
/********************************************************************************
 * Defines
 *******************************************************************************/

/********************************************************************************
 * Typedefs
 *******************************************************************************/
/** @defgroup MonitoringLib_Exported_Typedefs Type Definitions
 * @{
 */
/**
 * @brief Defines the available measurements types
 */
typedef enum
{
	MEASURE_RMS = 0,     /**< Represents the Root Mean Square measurement */
	MEASURE_AVG,         /**< Represents the Average measurement  */
	MEASURE_MAX,         /**< Represents the Maximum measurement  */
	MEASURE_MIN,         /**< Represents the Minimum measurement  */
	MEASURE_PkToPk,      /**< Represents the Peak to Peak (Maximum - Minimum) measurement  */
	MEASURE_COUNT,		 /**< Represents the total number of available measurements */
} measure_type_t;
/**
 * @}
 */
/********************************************************************************
 * Structures
 *******************************************************************************/
/** @defgroup MonitoringLib_Exported_Strutures Structures
 * @{
 */
typedef struct
{
	float rms;				/**< @brief RMS measurement */
	float avg;				/**< @brief Average measurement */
	float max;				/**< @brief Maximum measurement */
	float min;				/**< @brief Minimum measurement */
	int samplesLeft;		/**< @brief No of samples left before computation */
	int sampleCount;		/**< @brief No of samples to be used for statistics computation */
} temp_stats_data_t;
/**
 * @brief Contains the required members for statistical analysis
 * @note This structure sequence should be the same with @ref measure_type_t
 */
typedef struct
{
	float rms;				/**< @brief RMS measurement */
	float avg;				/**< @brief Average measurement */
	float max;				/**< @brief Maximum measurement */
	float min;				/**< @brief Minimum measurement */
	float pkTopk;			/**< @brief Peak to peak measurement */
} stats_data_t;


/**
 * @}
 */
/********************************************************************************
 * Exported Variables
 *******************************************************************************/

/********************************************************************************
 * Global Function Prototypes
 *******************************************************************************/
/** @defgroup MAX11046_Exported_Functions Functions
 * @{
 */
/**
 * @brief Insert new data for computation of statistics. If samples are enough statistics will be computed.
 * @param data Pointer to the first element of the new data array
 * @param stats Pointer to the first element of the statistics array
 * @param count Number of consecutive statistics computations
 */
extern uint32_t Stats_Compute_SingleSample(float* data, temp_stats_data_t* tempStats, stats_data_t* stats, int chCount);
extern uint32_t Stats_Compute_MultiSample_16ch(float* data, temp_stats_data_t* tempStats, stats_data_t* stats, int sampleCount);
extern TCritical void Stats_Reset(temp_stats_data_t* tempStats, stats_data_t* stats, int sampleCount, int chCount);
/********************************************************************************
 * Code
 *******************************************************************************/




/**
 * @}
 */
#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif 
/* EOF */

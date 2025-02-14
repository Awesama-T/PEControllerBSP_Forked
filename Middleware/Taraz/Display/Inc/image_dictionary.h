/**
 ********************************************************************************
 * @file 		image_dictionary.h
 * @author 		Waqas Ehsan Butt
 * @date 		May 18, 2023
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

#ifndef IMAGE_DICTIONARY_H_
#define IMAGE_DICTIONARY_H_

#ifdef __cplusplus
extern "C" {
#endif

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
typedef struct
{
	uint16_t width;
	uint16_t height;
	uint32_t pixelFormat;
	const uint8_t* data;
} image_info_t;
/********************************************************************************
 * Structures
 *******************************************************************************/

/********************************************************************************
 * Exported Variables
 *******************************************************************************/
extern image_info_t taraz_logo_info;
extern image_info_t intelliSENS_QR_info;
extern image_info_t intelliSENS_logo_info;
extern image_info_t bsp_docs_QR_info;
/********************************************************************************
 * Global Function Prototypes
 *******************************************************************************/

/********************************************************************************
 * Code
 *******************************************************************************/


#ifdef __cplusplus
}
#endif

#endif 
/* EOF */

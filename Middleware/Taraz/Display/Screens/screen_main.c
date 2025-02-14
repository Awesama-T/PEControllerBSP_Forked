/**
 ********************************************************************************
 * @file    	screen_main.c
 * @author 		Waqas Ehsan Butt
 * @date    	May 12, 2023
 *
 * @brief   
 ********************************************************************************
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

/********************************************************************************
 * Includes
 *******************************************************************************/
#include "screen_base.h"
#include "stdlib.h"
#include "utility_lib.h"
#include "interprocessor_comms.h"
#include "screen_main_app.h"
/********************************************************************************
 * Defines
 *******************************************************************************/
#define BASE_MEASURE_TAG		(20)
#define MEASURE_TAG(index)		TAG_ATTACH(index + BASE_MEASURE_TAG)
#define IS_MEASURE_TAG(tag)		(tag >= BASE_MEASURE_TAG && tag < (BASE_MEASURE_TAG + 16))
/**
 * @brief Get the measurement index from tag
 */
#define GET_MEASURE_INDEX(tag)	(tag - BASE_MEASURE_TAG)
/********************************************************************************
 * Typedefs
 *******************************************************************************/
typedef struct
{
	lv_obj_t* lblReading;
	lv_obj_t* lblValue;
} ch_disp_t;
/********************************************************************************
 * Structures
 *******************************************************************************/

/********************************************************************************
 * Static Variables
 *******************************************************************************/
static lv_obj_t* screen;
static ch_disp_t chDisplay[16];
static volatile bool isActive;
static volatile uint8_t tag = TAG_NONE;
/********************************************************************************
 * Global Variables
 *******************************************************************************/

/********************************************************************************
 * Function Prototypes
 *******************************************************************************/
void ConfigScreen_LoadMeasurement(int measurementIndex);
/********************************************************************************
 * Code
 *******************************************************************************/
static void event_handler(lv_event_t * e)
{
	if (!isActive)
		return;
	tag = GET_TAG(e);
}

/**
 * @brief Create a cell for measurement display on main grid
 * @param parent
 * @param index
 */
static void MeasurementCell_Create(lv_obj_t * parent, int index)
{
	static lv_style_t cellGridStyle;
	static lv_style_t chNameContainerStyle, chValueContainerStyle;
	static lv_style_t chNameLblStyle, chReadingTypeLblStyle, chValueLblStyle;
	static bool init = false;
	// initialize styles once
	if (!init)
	{
		BSP_Screen_InitGridStyle(&cellGridStyle, 1, 0, 0, 5, &lvColorStore.mediumTaraz);
		BSP_Screen_InitGridStyle(&chValueContainerStyle, 0, 0, 0, 0, &lvColorStore.background);
		BSP_Screen_InitGridStyle(&chNameContainerStyle, 0, 0, 0, 0, &lvColorStore.mediumTaraz);
		// Initialize the basic grid cell label styles
		BSP_Screen_InitLabelStyle(&chValueLblStyle, &MEASUREMENT_VALUE_FONT, LV_TEXT_ALIGN_CENTER, &lvColorStore.darkFont);
		BSP_Screen_InitLabelStyle(&chReadingTypeLblStyle, &lv_font_montserrat_14, LV_TEXT_ALIGN_LEFT, &lvColorStore.darkFont);
		BSP_Screen_InitLabelStyle(&chNameLblStyle, &lv_font_montserrat_22, LV_TEXT_ALIGN_CENTER, &lvColorStore.darkFont);
		init = true;
	}

	int col = index % 4;
	int row = index / 4;

	ch_disp_t* disp = &chDisplay[index];

	// Set main grid element
	static lv_coord_t rows[] = {LV_GRID_FR(5), LV_GRID_FR(2), LV_GRID_TEMPLATE_LAST};
	lv_obj_t * grid = lv_grid_create_general(parent, singleRowCol, rows, &cellGridStyle, NULL, event_handler, MEASURE_TAG(index));
	lv_obj_set_grid_cell(grid, LV_GRID_ALIGN_STRETCH, col, 1, LV_GRID_ALIGN_STRETCH, row, 1);

	char txtVal[10];
	const char* txtRead = NULL;
	txtRead = measureTxts[(uint8_t)dispMeasures.chMeasures[index].type];
	ftoa_custom(0, txtVal, 4, 1);

	lv_obj_t * containerValue = lv_container_create_general(grid, &chValueContainerStyle, 0, 0, event_handler, MEASURE_TAG(index));
	disp->lblValue = lv_label_create_general(containerValue, &chValueLblStyle, txtVal, NULL, NULL);
	disp->lblReading = lv_label_create_general(containerValue, &chReadingTypeLblStyle, txtRead, NULL, NULL);
	lv_obj_align(disp->lblValue, LV_ALIGN_CENTER, 0, -8);
	lv_obj_align(disp->lblReading, LV_ALIGN_BOTTOM_LEFT, 2, 0);

	// set the name portion
	lv_obj_t* containerName = lv_container_create_general(grid, &chNameContainerStyle, 1, 0, event_handler, MEASURE_TAG(index));
	lv_obj_t* lblName = lv_label_create_general(containerName, &chNameLblStyle, dispMeasures.chNames[index], NULL, NULL);
	lv_obj_center(lblName);
}

/**
 * @brief Create the measurement grid
 * @param parent
 */
static void MeasurementGrid_Create(lv_obj_t* parent)
{
	// create monitoring grid
	static lv_coord_t cols[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
	static lv_coord_t rows[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
	lv_obj_t* grid = lv_grid_create_general(parent, cols, rows, &lvStyleStore.thinMarginGrid, NULL, NULL, NULL);
	lv_obj_set_grid_cell(grid, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 0, 1);
	// create all cells
	for (int i = 0; i < 16; i++)
		MeasurementCell_Create(grid, i);
}

static void FileMenu_Create(lv_obj_t* parent, int row)
{
	static lv_style_t stripGridStyle;
	static lv_style_t lblStyle;
	static lv_style_t btnStyle;
	static bool init = false;
	// initialize styles once
	if (!init)
	{
		BSP_Screen_InitGridStyle(&stripGridStyle, 1, 2, 2, 5, &lvColorStore.background);
		BSP_Screen_InitBtnStyle(&btnStyle, 0, 4, &lvColorStore.btnBg2);
		// Initialize the basic grid cell label styles
		BSP_Screen_InitLabelStyle(&lblStyle, &lv_font_montserrat_22, LV_TEXT_ALIGN_CENTER, &lvColorStore.darkFont);
		init = true;
	}

	// Set main grid element
	static lv_coord_t cols[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
	lv_obj_t * grid = lv_grid_create_general(parent, cols, singleRowCol, &stripGridStyle, NULL, NULL, NULL);
	lv_obj_set_grid_cell(grid, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, row, 1);

	lv_obj_t* infoBtn = lv_btn_create_general(grid, &btnStyle, &lblStyle, "Info", event_handler, TAG_ATTACH(TAG_APPINFO));
	lv_obj_set_grid_cell(infoBtn, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 0, 1);

	lv_obj_t* docsBtn = lv_btn_create_general(grid, &btnStyle, &lblStyle, "Help", event_handler, TAG_ATTACH(TAG_HELP));
	lv_obj_set_grid_cell(docsBtn, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_STRETCH, 0, 1);

	lv_obj_t* intBtn = lv_btn_create_general(grid, &btnStyle, &lblStyle, "", event_handler, TAG_ATTACH(TAG_intelliSENS));
	lv_obj_set_grid_cell(intBtn, LV_GRID_ALIGN_STRETCH, 2, 1, LV_GRID_ALIGN_STRETCH, 0, 1);
}

static void ControlGrid_Create(lv_obj_t* parent)
{
	// create control grid
	static lv_coord_t rows[] = {60, LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
	lv_obj_t* grid = lv_grid_create_general(parent, singleRowCol, rows, &lvStyleStore.defaultGrid, NULL, NULL, NULL);
	lv_obj_set_grid_cell(grid, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_STRETCH, 0, 1);

	FileMenu_Create(grid, 0);
	AppControlGrid_Create(grid, 1, 0);
}

static void Load(void)
{
	lv_scr_load(screen);
	isActive = true;
}

static void Unload(void)
{
	if (isActive)
	{
		isActive = false;
		//lv_obj_del(screen);
	}
}

static screen_type_t Refresh(void)
{
	if (isActive)
	{
		if (tag != TAG_NONE)
		{
			uint8_t tagBuff = tag;
			tag = TAG_NONE;
			if (IS_MEASURE_TAG(tagBuff))
			{
				uint8_t index = GET_MEASURE_INDEX(tagBuff);
				ConfigScreen_LoadMeasurement(index);
				return SCREEN_CONF;
			}
			if (tagBuff == TAG_intelliSENS)
				return SCREEN_intelliSENS;
			if (tagBuff == TAG_APPINFO)
				return SCREEN_APPINFO;
			if (tagBuff == TAG_HELP)
				return SCREEN_HELP;
		}

		screen_type_t scr = AppControlGrid_TouchDetect();
		if (scr!=SCREEN_NONE)
			return scr;

		AppControlGrid_Refresh();
		{
			for (int i = 0; i < 16; i++)
			{
				measure_type_t type = dispMeasures.chMeasures[i].type;
				float* stats = ((float*)&dispMeasures.adcInfo->stats[i]);
				char txt[10];
				int len = ftoa_custom(stats[(uint8_t)type], txt, 4, 1);
				strcat_custom(txt, unitTxts[(uint8_t)dispMeasures.adcInfo->units[i]], len, false);
				lv_label_set_text(chDisplay[i].lblValue, txt);
				lv_label_set_text(chDisplay[i].lblReading, measureTxts[(uint8_t)dispMeasures.chMeasures[i].type]);
			}
		}
	}
	return SCREEN_NONE;
}

/**
 * @brief Initialize screen
 * @param _screen Pointer to fill the screen information
 */
void MainScreen_Init(screens_t* _screen)
{
	static ltdc_layer_info_t directLayer =
	{
			.xAlign = ALIGN_RIGHT_X,
			.yAlign = ALIGN_UP_Y,
			.posY = 6
	};
	directLayer.posX = (((APP_AREA_RATIO * DISPLAY_WIDTH_RAM) / (MEASUREMENT_AREA_RATIO + APP_AREA_RATIO)) / 6) - (intelliSENS_logo_info.width / 2);
	directLayer.PixelFormat = intelliSENS_logo_info.pixelFormat;
	directLayer.width = intelliSENS_logo_info.width;
	directLayer.height = intelliSENS_logo_info.height;
	directLayer.data = intelliSENS_logo_info.data;

	// Make the screen
	// create the screen
	screen = lv_obj_create(NULL);

	// create basic grid
	static lv_coord_t colsScreen[] = {LV_GRID_FR(MEASUREMENT_AREA_RATIO), LV_GRID_FR(APP_AREA_RATIO), LV_GRID_TEMPLATE_LAST};
	lv_obj_t* screenGrid = lv_grid_create_general(screen, colsScreen, singleRowCol, &lvStyleStore.defaultGrid, NULL, NULL, NULL);
	lv_obj_set_size(screenGrid, DISPLAY_WIDTH_RAM, DISPLAY_HEIGHT_RAM);

	MeasurementGrid_Create(screenGrid);
	ControlGrid_Create(screenGrid);

	_screen->Refresh = Refresh;
	_screen->Load = Load;
	_screen->Unload = Unload;
	_screen->directLayer = &directLayer;
	_screen->lvglLayer = &defaultLayer;
}

/* EOF */

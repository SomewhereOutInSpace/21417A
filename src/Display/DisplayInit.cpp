//Note: Rendering area is 480x239 pixels
#include "robokauz/PRELUDE.hpp"
#include "robokauz/COMMON.hpp"
#include "pros/apix.h"
#include "robokauz/Display/EventHandlers.hpp"
#include "robokauz/Display/DisplayGlobals.hpp"
#include "robokauz/Display/DisplayUtils.hpp"

void initializeDisplay()
{
    configureTheming();
    home_page = createPage(SCREEN, 480, 239, LV_ALIGN_IN_TOP_MID, 0, 0, false);
    lv_style_copy(&status_style, home_page->style_p);
    lv_style_copy(&confirm_style, home_page->style_p);
    configureStyling();
    
    left_panel = createContainer(home_page, 240, 239, LV_ALIGN_IN_TOP_LEFT, 120, 0, LV_LAYOUT_OFF);
    status_mode_switcher = createMatrix(switcher_map, 240, 25, left_panel, LV_ALIGN_IN_BOTTOM_MID, 0, -1, *handleStatusModeSwitcher);
    
    status_page = createPage(left_panel, 240, 214, LV_ALIGN_IN_TOP_LEFT, 0, 0, false);
    status_text = createLabel(status_page, "Initializing...", LV_LABEL_ALIGN_LEFT, LV_ALIGN_IN_TOP_LEFT, 0, 0);
    lv_label_set_long_mode(status_text, LV_LABEL_LONG_BREAK);
    lv_obj_set_style(status_text, &status_style);
    lv_obj_set_size(status_text, 260, 214);

    controls_page = createPage(left_panel, 240, 214, LV_ALIGN_IN_TOP_LEFT, 0, 0, true);
    mode_controls = createMatrix(controls_map_locked, 240, 214, controls_page, LV_ALIGN_IN_TOP_MID, 0, 0, *handleControls);

    right_panel = createContainer(home_page, 240, 239, LV_ALIGN_IN_RIGHT_MID, -120, 0, LV_LAYOUT_COL_M);
    
    side_page = createPage(right_panel, 240, 239, LV_ALIGN_IN_TOP_LEFT, 0, 0, false);
    side_buttons = createMatrix(side_map, 240, 214, side_page, LV_ALIGN_IN_TOP_LEFT, 0, 0, *handleSideSelect);
    waiting_label = createLabel(side_page, "Waiting...", LV_LABEL_ALIGN_CENTER, LV_ALIGN_IN_BOTTOM_MID, 0, 23);
    
    strat_page = createPage(right_panel, 240, 239, LV_ALIGN_IN_TOP_LEFT, 0, 0, true);
    strat_buttons = createMatrix(strat_map, 240, 214, strat_page, LV_ALIGN_IN_TOP_LEFT, 0, 0, *handleStratSelect);
    selector_cancel = createButton(strat_page, "#FF0000 Cancel#", 240, 25, LV_ALIGN_IN_BOTTOM_MID, 0, 24, *handleSelectionCancel);

    ready_page = createPage(right_panel, 240, 239, LV_ALIGN_IN_TOP_LEFT, 0, 0, true);
    ready_container = createContainer(ready_page, 240, 214, LV_ALIGN_IN_RIGHT_MID, -120, 0, LV_LAYOUT_CENTER);
    ready_label = createLabel(ready_container, "Error", LV_LABEL_ALIGN_CENTER, LV_ALIGN_CENTER, -25, 0);
    lv_obj_set_style(ready_label, &confirm_style);
    lv_obj_set_size(ready_label, 240, 214);
    selector_finalized = createButton(ready_page, "#FF0000 Cancel#", 240, 25, LV_ALIGN_IN_BOTTOM_MID, 0, 24, *handleSelectionCancel);

    static uint32_t user_data = 10;
    lv_task_t * status_update_task = lv_task_create(statusUpdateTask, 50, LV_TASK_PRIO_MID, &user_data);
    lv_task_t * routine_update_task = lv_task_create(routineUpdateTask, 50, LV_TASK_PRIO_MID, &user_data);
}
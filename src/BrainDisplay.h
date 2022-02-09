#pragma once
#include "pros/apix.h"
#define TEAM "VEX 21417A #ff0000 Invictus#"
#define VERSION "\nCompetition Suite v2.0.0"
#define CODENAME " \"Multi-file Revolution\""
#define COMPILED "\nCompiled on " __DATE__ " at " __TIME__ "\n"

lv_obj_t * outputLabel =  lv_label_create(lv_scr_act(), NULL);
lv_obj_t * debugLabel = lv_label_create(lv_scr_act(), NULL);

void splashDisplay()
{
    /*Modify the Label's text*/
    lv_label_set_text(outputLabel, TEAM VERSION CODENAME COMPILED);
    lv_label_set_text(debugLabel, "Debug line ready.");

    /* Align the Label to the center
     * NULL means align on parent (which is the screen now)
     * 0, 0 at the end means an x, y offset after alignment*/
    lv_obj_align(outputLabel, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
    lv_obj_align(debugLabel, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);

    lv_label_set_recolor(outputLabel, true);  
}

void brainPrint(std::string str)
{
    std::string newlined = str + "\n";
    lv_label_ins_text(outputLabel, LV_LABEL_POS_LAST, newlined.c_str());
}

void debugPrint(std::string str)
{
    lv_label_set_text(debugLabel, str.c_str());
}
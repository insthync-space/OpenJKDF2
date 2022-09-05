#include "jkGUIJoystick.h"

#include "General/Darray.h"
#include "General/stdBitmap.h"
#include "General/stdString.h"
#include "General/stdFont.h"
#include "Engine/rdMaterial.h" // TODO move stdVBuffer
#include "stdPlatform.h"
#include "jk.h"
#include "Gui/jkGUIRend.h"
#include "Gui/jkGUI.h"
#include "Gui/jkGUIDialog.h"
#include "Main/jkStrings.h"
#include "Win95/stdDisplay.h"
#include "General/stdFileUtil.h"
#include "Engine/sithControl.h"
#include "Platform/stdControl.h"
#include "World/jkPlayer.h"
#include "Win95/Windows.h"
#include "Gui/jkGUISetup.h"
#include "Engine/sithControl.h"

static int jkGuiJoystick_dword_557078;
static int jkGuiJoystick_aUnk1[36];
static Darray jkGuiJoystick_darray;
static int jkGuiJoystick_dword_557128;
static Darray jkGuiJoystick_darray2;
static jkGuiJoystickStrings jkGuiJoystick_strings;
static float jkGuiJoystick_aFloats[36];
static wchar_t jkGuiJoystick_awTmp[256];
static Darray jkGuiJoystick_darray3;
static int jkGuiJoystick_dword_5576F0;
static int jkGuiJoystick_dword_5576F4;
static wchar_t jkGuiJoystick_waIdk2[4];

static int jkGuiJoystick_dword_536B98 = -1;
static int jkGuiJoystick_dword_536B9C = -1;

static jkGuiJoystickEntry jkGuiJoystick_aEntries[36] =
{
    { AXIS_JOY1_X, "AXIS_JOY1_X", 0, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0 },
    { AXIS_JOY1_Y, "AXIS_JOY1_Y", 1, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0 },
    { AXIS_JOY1_Z, "AXIS_JOY1_Z", 2, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0 },
    { AXIS_JOY1_R, "AXIS_JOY1_R", 3, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0 },
    { AXIS_JOY1_U, "AXIS_JOY1_U", 4, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0 },
    { AXIS_JOY1_V, "AXIS_JOY1_V", 5, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0 },
    { AXIS_JOY2_X, "AXIS_JOY2_X", 128, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0 },
    { AXIS_JOY2_Y, "AXIS_JOY2_Y", 129, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0 },
    { AXIS_JOY2_Z, "AXIS_JOY2_Z", 130, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0 },
    { AXIS_JOY2_R, "AXIS_JOY2_R", 131, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0 },
    { AXIS_JOY2_U, "AXIS_JOY2_U", 132, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0 },
    { AXIS_JOY2_V, "AXIS_JOY2_V", 133, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0 },
    { KEY_JOY1_B1, "KEY_JOY1_B1", 32, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0 },
    { KEY_JOY1_B2, "KEY_JOY1_B2", 33, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0 },
    { KEY_JOY1_B3, "KEY_JOY1_B3", 34, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0 },
    { KEY_JOY1_B4, "KEY_JOY1_B4", 35, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0 },
    { KEY_JOY1_B5, "KEY_JOY1_B5", 36, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0 },
    { KEY_JOY1_B6, "KEY_JOY1_B6", 37, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0 },
    { KEY_JOY1_B7, "KEY_JOY1_B7", 38, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0 },
    { KEY_JOY1_B8, "KEY_JOY1_B8", 39, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0 },
    { KEY_JOY1_HLEFT, "KEY_JOY1_HLEFT", 16, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0},
    { KEY_JOY1_HUP, "KEY_JOY1_HUP", 17, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0 },
    { KEY_JOY1_HRIGHT, "KEY_JOY1_HRIGHT", 18, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0},
    { KEY_JOY1_HDOWN, "KEY_JOY1_HDOWN", 19, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0},
    { KEY_JOY2_B1, "KEY_JOY2_B1", 160, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0 },
    { KEY_JOY2_B2, "KEY_JOY2_B2", 161, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0 },
    { KEY_JOY2_B3, "KEY_JOY2_B3", 162, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0 },
    { KEY_JOY2_B4, "KEY_JOY2_B4", 163, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0 },
    { KEY_JOY2_B5, "KEY_JOY2_B5", 164, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0 },
    { KEY_JOY2_B6, "KEY_JOY2_B6", 165, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0 },
    { KEY_JOY2_B7, "KEY_JOY2_B7", 166, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0 },
    { KEY_JOY2_B8, "KEY_JOY2_B8", 167, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0 },
    { KEY_JOY2_HLEFT, "KEY_JOY2_HLEFT", 144, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0},
    { KEY_JOY2_HUP, "KEY_JOY2_HUP", 145, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0 },
    { KEY_JOY2_HRIGHT, "KEY_JOY2_HRIGHT", 146, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0},
    { KEY_JOY2_HDOWN, "KEY_JOY2_HDOWN", 147, INPUT_FUNC_FORWARD, 0u, NULL, 0,  0.0}
};

static int jkGuiJoystick_aIdk1[2] = {0xD, 0xE};
static int jkGuiJoystick_aIdk2[2] = {0x13, 0x11};
static int jkGuiJoystick_aIdk2_[2] = {0x12, 0x11}; // unused?
static int jkGuiKeyboard_aIdk3[2] = {0xAA, 0x0};

static jkGuiElement jkGuiJoystick_aElements[33] = {
    { ELEMENT_TEXT, 0, 0, NULL, 3, { 0, 410, 640, 20 }, 1, 0, NULL, NULL, NULL, NULL, { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }, 0 },
    { ELEMENT_TEXT, 0, 6, "GUI_SETUP", 3, { 20, 20, 600, 40 }, 1, 0, NULL, NULL, NULL, NULL, { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }, 0 },
    { ELEMENT_TEXTBUTTON, 100, 2, "GUI_GENERAL", 3, { 20, 80, 120, 40 }, 1, 0, "GUI_GENERAL_HINT", NULL, NULL, NULL, { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }, 0 },
    { ELEMENT_TEXTBUTTON, 101, 2, "GUI_GAMEPLAY", 3, { 140, 80, 120, 40 }, 1, 0, "GUI_GAMEPLAY_HINT", NULL, NULL, NULL, { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }, 0 },
    { ELEMENT_TEXTBUTTON, 102, 2, "GUI_DISPLAY", 3, { 260, 80, 120, 40 }, 1, 0, "GUI_DISPLAY_HINT", NULL, NULL, NULL, { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }, 0 },
    { ELEMENT_TEXTBUTTON, 103, 2, "GUI_SOUND", 3, { 380, 80, 120, 40 }, 1, 0, "GUI_SOUND_HINT", NULL, NULL, NULL, { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }, 0 },
    { ELEMENT_TEXTBUTTON, 104, 2, "GUI_CONTROLS", 3, { 500, 80, 120, 40 }, 1, 0, "GUI_CONTROLS_HINT", NULL, NULL, NULL, { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }, 0 },
    { ELEMENT_TEXTBUTTON, 105, 2, "GUI_KEYBOARD", 3, { 40, 120, 140, 40 }, 1, 0, "GUI_KEYBOARD_HINT", NULL, NULL, NULL, { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }, 0 },
    { ELEMENT_TEXTBUTTON, 106, 2, "GUI_MOUSE", 3, { 180, 120, 140, 40 }, 1, 0, "GUI_MOUSE_HINT", NULL, NULL, NULL, { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }, 0 },
    { ELEMENT_TEXTBUTTON, 107, 2, "GUI_JOYSTICK", 3, { 320, 120, 140, 40 }, 1, 0, "GUI_JOYSTICK_HINT", NULL, NULL, NULL, { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }, 0 },
    { ELEMENT_TEXTBUTTON, 108, 2, "GUI_CONTROLOPTIONS", 3, { 460, 120, 140, 40 }, 1, 0, "GUI_CONTROLOPTIONS_HINT", NULL, NULL, NULL, { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }, 0 },
    { ELEMENT_LISTBOX, 0, 0, NULL, 0, { 20, 170, 380, 141 }, 1, 0, "GUI_CONTROLSLIST_HINT", NULL, jkGuiJoystick_ClickList1, jkGuiJoystick_aIdk1, { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }, 0 },
    { ELEMENT_LISTBOX, 0, 0, NULL, 0, { 420, 170, 200, 141 }, 1, 0, "GUI_CONTROLSLIST_HINT", NULL,jkGuiJoystick_ClickList2, jkGuiJoystick_aIdk1, { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }, 0 },
    { ELEMENT_LISTBOX, 0, 0, NULL, 0, { 420, 170, 200, 141 }, 1, 0, "GUI_CONTROLSLIST_HINT", NULL, jkGuiJoystick_ClickList3, jkGuiJoystick_aIdk1, { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }, 0 },
    { ELEMENT_TEXTBUTTON, 0, 2, "GUI_ADD_CONTROL", 3, { 420, 165, 200, 40 }, 1, 0, "GUI_MOUSE_ADD_HINT", NULL, jkGuiJoystick_AddEditClick, NULL, { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }, 0 },
    { ELEMENT_TEXTBUTTON, 0, 2, "GUI_EDIT_CONTROL", 3, { 420, 165, 200, 40 }, 1, 0, "GUI_EDIT_CONTROL_HINT", NULL, jkGuiJoystick_AddEditClick, NULL, { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }, 0 },
    { ELEMENT_TEXTBUTTON, 0, 2, "GUI_REMOVE_CONTROL", 3, { 420, 205, 200, 40 }, 1, 0, "GUI_MOUSE_REMOVE_HINT", NULL, jkGuiJoystick_RemoveClick, NULL, { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }, 0 },
    { ELEMENT_TEXTBUTTON, 0, 2, "GUI_CAPTURE", 3, { 420, 245, 200, 40 }, 1, 0, "GUI_CAPTURE_HINT", NULL, jkGuiJoystick_CaptureClick, NULL, { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }, 0 },
    { ELEMENT_TEXTBUTTON, 0, 2, "GUI_CALIBRATE_JOYSTICK", 3, { 420, 285, 200, 40 }, 1, 0, "GUI_CALIBRATE_JOYSTICK_HINT", NULL, jkGuiJoystick_CalibrateClick, NULL, { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }, 0 },
    { ELEMENT_CHECKBOX, 0, 0, "GUI_REVERSE_AXIS", 0, { 320, 355, 300, 20 }, 1, 0, "GUI_REVERSE_HINT", NULL, NULL, NULL, { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }, 0 },
    { ELEMENT_CHECKBOX, 0, 0, "GUI_CONTROL_RAW", 0, { 320, 375, 300, 20 }, 1, 0, "GUI_RAW_HINT", NULL, NULL, NULL, { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }, 0 },
    { ELEMENT_TEXT, 0, 0, "GUI_SENSITIVITY", 2, { 50, 335, 170, 20 }, 1, 0, NULL, NULL, NULL, NULL, { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }, 0 },
    { ELEMENT_SLIDER, 0, 0, (const char *)0x64, 50, { 60, 355, 205, 30 }, 1, 0, "GUI_SENSITIVITY_HINT", NULL, NULL, jkGuiJoystick_aIdk2, { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }, 0 },
    { ELEMENT_TEXTBUTTON, 1, 2, "GUI_OK", 3, { 440, 430, 200, 40 }, 1, 0, NULL, NULL, jkGuiJoystick_OkCancelClick, NULL, { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }, 0 },
    { ELEMENT_TEXTBUTTON, -1, 2, "GUI_CANCEL", 3, { 0, 430, 200, 40 }, 1, 0, NULL, NULL, jkGuiJoystick_OkCancelClick, NULL, { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }, 0 },
    { ELEMENT_TEXTBUTTON, 0, 2, "GUI_RESTORE_DEFAULTS", 3, { 200, 430, 240, 40 }, 1, 0, NULL, NULL, jkGuiJoystick_RestoreDefaultsClick, NULL, { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }, 0 },
    { ELEMENT_CHECKBOX, 0, 0, "GUI_DISABLE_JOYSTICK", 0, { 320, 335, 300, 20 }, 1, 0, "GUI_DISABLE_JOYSTICK_HINT", NULL, NULL, NULL, { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }, 0 },
    { ELEMENT_TEXT, 0, 2, &jkGuiJoystick_awTmp, 3, { 50, 180, 320, 120 }, 1, 0, NULL, NULL, NULL, NULL, { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }, 0 },
    { ELEMENT_TEXT, 0, 2, &jkGuiJoystick_awTmp, 3, { 50, 180, 540, 120 }, 1, 0, NULL, NULL, NULL, NULL, { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }, 0 },
    { ELEMENT_TEXT, 0, 0, jkGuiJoystick_strings.aStrings[0], 3, { 20, 310, 380, 25 }, 1, 0, NULL, NULL, NULL, NULL, { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }, 0 },
    { ELEMENT_TEXT, 0, 0, jkGuiJoystick_strings.aStrings[1], 3, { 20, 335, 380, 25 }, 1, 0, NULL, NULL, NULL, NULL, { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }, 0 },
    { ELEMENT_TEXT, 0, 0, jkGuiJoystick_strings.aStrings[2], 3, { 20, 360, 380, 25 }, 1, 0, NULL, NULL, NULL, NULL, { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }, 0 },
    { ELEMENT_END, 0, 0, NULL, 0, { 0, 0, 0, 0 }, 0, 0, NULL, NULL, NULL, NULL, { 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }, 0 }
};

static jkGuiMenu jkGuiJoystick_menu = {
  jkGuiJoystick_aElements, 0, 225, 255, 15, NULL, NULL, jkGui_stdBitmaps, jkGui_stdFonts, jkGuiKeyboard_aIdk3, jkGuiJoystick_MenuTick, "thermloop01.wav", "thrmlpu2.wav", NULL, NULL, NULL, 0, NULL, NULL
};  

void jkGuiJoystick_nullsub_51()
{
    ;
}

int jkGuiJoystick_ClickList1(jkGuiElement *pElement, jkGuiMenu *pMenu, int mouseX, int mouseY, int bRedraw)
{
    if ( !jkGuiJoystick_dword_5576F0 )
    {
        jkGuiRend_ClickSound(pElement, pMenu, mouseX, mouseY, bRedraw);
        if ( pElement->texInfo.anonymous_18 )
        {
            jkGuiRend_PlayWav(pMenu->soundClick);
            return -1;
        }
        if ( bRedraw )
            jkGuiJoystick_dword_557128 = 1;
        jkGuiJoystick_Draw(pMenu, 1);
    }
    return 0;
}

void jkGuiJoystick_Draw(jkGuiMenu *pMenu, int bRedraw)
{
    int v2; // eax
    int v3; // ebx
    int v4; // esi
    int v5; // ecx
    stdControlKeyInfoEntry *v6; // eax
    double v7; // st7
    wchar_t *v8; // eax
    jkGuiMenu *v9; // edi
    Darray *v10; // edi
    stdControlKeyInfoEntry *v11; // eax
    int v12; // eax
    int v13; // esi
    stdControlKeyInfoEntry *v14; // esi
    double v15; // st7
    int v16; // edx
    uint32_t v17; // eax
    int v18; // eax
    jkGuiElement *v19; // eax
    jkGuiElement *v20; // [esp+10h] [ebp-8h]
    unsigned int v21; // [esp+14h] [ebp-4h]

    v2 = jkGuiJoystick_darray2.total;
    if ( jkGuiJoystick_darray2.total != 1 )
    {
        while ( 1 )
        {
            if ( jkGuiJoystick_aElements[26].selectedTextEntry )
                goto LABEL_19;
            jkGuiJoystick_aElements[11].bIsVisible = 1;
            jkGuiJoystick_aElements[28].bIsVisible = 0;
            v3 = jkGuiRend_GetId(&jkGuiJoystick_darray2, jkGuiJoystick_aElements[11].selectedTextEntry);
            v4 = jkGuiJoystick_aEntries[v3].inputFunc;
            v5 = jkGuiJoystick_dword_536B9C;
            v21 = v4;
            if ( v3 == jkGuiJoystick_dword_536B9C && jkGuiJoystick_dword_557128 == jkGuiJoystick_dword_536B98 )
                return;
            if ( jkGuiJoystick_dword_536B9C >= 0 )
            {
                v6 = jkGuiJoystick_aEntries[jkGuiJoystick_dword_536B9C].pControlEntry;
                if ( v6 )
                {
                    if ( jkGuiJoystick_aElements[22].bIsVisible )
                    {
                        if ( jkGuiJoystick_aElements[22].selectedTextEntry > 50 )
                            v7 = (double)(jkGuiJoystick_aElements[22].selectedTextEntry - 50) * 0.059999999 - -1.0;
                        else
                            v7 = (double)jkGuiJoystick_aElements[22].selectedTextEntry * 0.015 - -0.25;
                        v6->binaryAxisVal = v7;
                    }
                    if ( jkGuiJoystick_aElements[20].bIsVisible )
                        v6->flags = v6->flags & ~8u | (jkGuiJoystick_aElements[20].selectedTextEntry != 0 ? 8 : 0);
                    if ( jkGuiJoystick_aElements[19].bIsVisible )
                        v6->flags = v6->flags & ~4u | (jkGuiJoystick_aElements[19].selectedTextEntry != 0 ? 0 : 4);
                }
            }
            if ( !jkGuiJoystick_dword_557128 )
                break;
            if ( v5 == v3 )
            {
                jkGuiJoystick_aElements[25].bIsVisible = 0;
                jkGuiJoystick_aElements[14].bIsVisible = 0;
                jkGuiJoystick_aElements[15].bIsVisible = 0;
                jkGuiJoystick_aElements[16].bIsVisible = 0;
                jkGuiJoystick_aElements[17].bIsVisible = 0;
                jkGuiJoystick_aElements[18].bIsVisible = 0;
                if ( v3 >= 12 )
                {
                    jkGuiJoystick_aElements[12].bIsVisible = 0;
                    v10 = &jkGuiJoystick_darray3;
                    v20 = &jkGuiJoystick_aElements[13];
                    v11 = jkGuiJoystick_aEntries[v3].pControlEntry;
                    if ( v11 && (v11->flags & 4) != 0 )
                        v21 = v4 | 0x80000000;
                }
                else
                {
                    jkGuiJoystick_aElements[13].bIsVisible = 0;
                    v10 = &jkGuiJoystick_darray;
                    v20 = &jkGuiJoystick_aElements[12];
                }
                v12 = v10->total;
                v13 = 0;
                v20->selectedTextEntry = 0;
                if ( v12 > 0 )
                {
                    while ( jkGuiRend_GetId(v10, v13) != v21 )
                    {
                        if ( ++v13 >= v10->total )
                            goto LABEL_38;
                    }
                    v20->selectedTextEntry = v13;
                }
LABEL_38:
                v9 = pMenu;
                v20->bIsVisible = 1;
                v9->focusedElement = v20;
                goto LABEL_39;
            }
            v2 = jkGuiJoystick_darray2.total;
            jkGuiJoystick_dword_557128 = 0;
            if ( jkGuiJoystick_darray2.total == 1 )
                goto LABEL_19;
        }
        v9 = pMenu;
        jkGuiJoystick_aElements[15].bIsVisible = v4 != -1;
        jkGuiJoystick_aElements[16].bIsVisible = v4 != -1;
        jkGuiJoystick_aElements[13].bIsVisible = 0;
        jkGuiJoystick_aElements[14].bIsVisible = v4 == -1;
        jkGuiJoystick_aElements[12].bIsVisible = 0;
        jkGuiJoystick_aElements[17].bIsVisible = 1;
        jkGuiJoystick_aElements[18].bIsVisible = 1;
        jkGuiJoystick_aElements[25].bIsVisible = 1;
        pMenu->focusedElement = &jkGuiJoystick_aElements[11];
LABEL_39:
        if ( jkGuiJoystick_dword_557128 || (v14 = jkGuiJoystick_aEntries[v3].pControlEntry) == 0 || v3 >= 12 )
        {
            jkGuiJoystick_aElements[19].bIsVisible = 0;
            jkGuiJoystick_aElements[20].bIsVisible = 0;
            jkGuiJoystick_aElements[21].bIsVisible = 0;
            jkGuiJoystick_aElements[22].bIsVisible = 0;
        }
        else
        {
            v15 = v14->binaryAxisVal;
            v16 = (jkGuiJoystick_aEntries[v3].flags >> 3) & 1;
            jkGuiJoystick_aElements[19].bIsVisible = 1;
            jkGuiJoystick_aElements[20].bIsVisible = v16;
            jkGuiJoystick_aElements[21].bIsVisible = 1;
            jkGuiJoystick_aElements[22].bIsVisible = 1;
            if ( v15 == 0.0 )
                v15 = 1.0;
            if ( v15 > 1.0 )
                v17 = (__int64)((v15 - 1.0) * 16.666666 - -0.5) + 50; // TODO int64?
            else
                v17 = (__int64)((v15 - 0.25) * 66.666664 - -0.5); // TODO int64?
            jkGuiJoystick_aElements[22].selectedTextEntry = v17;
            v18 = (v14->flags >> 3) & 1;
            jkGuiJoystick_aElements[19].selectedTextEntry = (~v14->flags >> 2) & 1;
            jkGuiJoystick_aElements[20].selectedTextEntry = v18;
        }
        if ( bRedraw )
        {
            v19 = v9->lastMouseOverClickable;
            if ( v19 == &jkGuiJoystick_aElements[15] || v19 == &jkGuiJoystick_aElements[14] )
                v9->lastMouseOverClickable = 0;
            jkGuiRend_Paint(v9);
            if ( !v9->lastMouseOverClickable )
            {
                int mouseX = 0;
                int mouseY = 0;
                jkGuiRend_GetMousePos(&mouseX, &mouseY);
                jkGuiRend_MouseMovedCallback(v9, mouseX, mouseY);
            }
        }
        jkGuiJoystick_dword_536B9C = v3;
        jkGuiJoystick_dword_536B98 = jkGuiJoystick_dword_557128;
        return;
    }
LABEL_19:
    jkGuiJoystick_aElements[11].bIsVisible = 0;
    jkGuiJoystick_aElements[12].bIsVisible = 0;
    jkGuiJoystick_aElements[13].bIsVisible = 0;
    jkGuiJoystick_aElements[14].bIsVisible = 0;
    jkGuiJoystick_aElements[15].bIsVisible = 0;
    jkGuiJoystick_aElements[16].bIsVisible = 0;
    jkGuiJoystick_aElements[17].bIsVisible = 0;
    jkGuiJoystick_aElements[18].bIsVisible = 0;
    jkGuiJoystick_aElements[19].bIsVisible = 0;
    jkGuiJoystick_aElements[20].bIsVisible = 0;
    jkGuiJoystick_aElements[21].bIsVisible = 0;
    jkGuiJoystick_aElements[22].bIsVisible = 0;
    jkGuiJoystick_aElements[25].bIsVisible = 0;
    if ( v2 == 1 )
    {
        jkGuiJoystick_aElements[23].bIsVisible = 0;
        jkGuiJoystick_aElements[26].bIsVisible = 0;
    }
    jkGuiJoystick_aElements[27].bIsVisible = 0;
    jkGuiJoystick_aElements[28].bIsVisible = 1;
    if ( v2 == 1 )
        v8 = jkStrings_GetText("GUI_NO_JOYSTICK");
    else
        v8 = jkStrings_GetText("GUI_JOYSTICK_DISABLED");
    _wcsncpy(jkGuiJoystick_awTmp, v8, 0xFFu);
    jkGuiJoystick_awTmp[255] = 0;
    if ( bRedraw )
        jkGuiRend_Paint(pMenu);
}

int jkGuiJoystick_ClickList2(jkGuiElement *pElement, jkGuiMenu *pMenu, int mouseX, int mouseY, int bRedraw)
{
    char *v6; // edx

    if ( jkGuiJoystick_dword_5576F0 )
        return 0;
    jkGuiRend_ClickSound(pElement, pMenu, mouseX, mouseY, bRedraw);
    if ( pElement->texInfo.anonymous_18 )
    {
        v6 = pMenu->soundClick;
        jkGuiJoystick_dword_557128 = 0;
        jkGuiRend_PlayWav(v6);
    }
    if ( bRedraw )
    {
        jkGuiJoystick_BindControl(jkGuiJoystick_aElements[11].selectedTextEntry, pElement->selectedTextEntry);
        jkGuiJoystick_dword_557128 = 0;
    }
    jkGuiJoystick_Draw(pMenu, 1);
    return 0;
}

void jkGuiJoystick_BindControl(int a1, int a2)
{
    int v2; // edi
    int v3; // esi
    int v4; // ebx
    int v5; // eax
    int v6; // ebp
    int v7; // ebx
    stdControlKeyInfoEntry *v8; // ecx
    stdControlKeyInfoEntry *v9; // eax
    unsigned int v10; // edx
    wchar_t *v11; // eax
    wchar_t *v12; // [esp-4h] [ebp-18h]
    float v13; // [esp+10h] [ebp-4h]

    v13 = 1.0;
    v2 = 0;
    v3 = jkGuiRend_GetId(&jkGuiJoystick_darray2, a1);
    v4 = jkGuiRend_GetId(&jkGuiJoystick_darray, a2);
    v5 = jkGuiJoystick_aEntries[v3].inputFunc;
    v6 = jkGuiJoystick_aEntries[v3].dikNum;
    v7 = v4 & ~0x80000000;
    if ( v5 != -1 )
    {
        v8 = jkGuiJoystick_aEntries[v3].pControlEntry;
        if ( v8 )
        {
            v13 = v8->binaryAxisVal;
            v2 = v8->flags & 4;
        }
        sithControl_ShiftFuncKeyinfo(v5, jkGuiJoystick_aEntries[v3].dxKeyNum);
    }
    v9 = sithControl_MapAxisFunc(v7, v6, v2);
    if ( v9 )
    {
        v10 = v9->flags & ~8u;
        v9->binaryAxisVal = v13;
        v9->flags = v10 | 4;
        jkGuiJoystick_sub_41B390();
    }
    else
    {
        v12 = jkStrings_GetText("ERR_CANNOT_BIND_CONTROL");
        v11 = jkStrings_GetText("ERROR");
        jkGuiDialog_ErrorDialog(v11, v12);
        jkGuiJoystick_Draw(&jkGuiJoystick_menu, 0);
        jkGuiRend_Paint(&jkGuiJoystick_menu);
    }
}

void jkGuiJoystick_sub_41B390()
{
    jkGuiJoystickEntry* v0; // eax
    jkGuiJoystickEntry* v1; // edi
    int v2; // ebp
    int v3; // esi
    wchar_t *v4; // ebx
    wchar_t *v5; // eax
    int v6; // esi
    int v7; // [esp+10h] [ebp-208h]
    int v8; // [esp+14h] [ebp-204h]
    wchar_t wtmp[256]; // [esp+18h] [ebp-200h] BYREF

    jkGuiRend_DarrayFreeEntry(&jkGuiJoystick_darray2);
    jkGuiRend_DarrayFreeEntry(&jkGuiJoystick_darray);
    jkGuiRend_DarrayFreeEntry(&jkGuiJoystick_darray3);
    v0 = &jkGuiJoystick_aEntries[0];
    do
    {
        v0->inputFunc = -1;
        v0->flags = 0;
        v0->dxKeyNum = 0;
        v0->binaryAxisVal = 0.0;
        v0->pControlEntry = 0;
        v0++;
    }
    while ( v0 < &jkGuiJoystick_aEntries[36]);
    sithControl_EnumBindings(jkGuiJoystick_EnumFunc, 0, 1, 0, 0);
    v7 = 0;
    v1 = &jkGuiJoystick_aEntries[0];
    do
    {
        v2 = v1->keybits & 0xF;
        v8 = v1->keybits & 0x30;
        v3 = v1->keybits & 0x80;
        v4 = jkStrings_GetText(v1->displayStrKey);
        if ( v1->inputFunc == -1 )
        {
            v5 = L"--";
        }
        else if ( v8 )
        {
            v5 = jkGuiRend_GetString(&jkGuiJoystick_darray3, v1->binaryAxisValInt);
        }
        else
        {
            v5 = jkGuiRend_GetString(&jkGuiJoystick_darray, v1->binaryAxisValInt);
        }
        jk_snwprintf(wtmp, 0x100u, L"%ls\t%ls", v4, v5);
        v6 = v3 >> 7;
        if ( stdControl_aJoystickExists[v6] && !v8 && (stdControl_aJoysticks[v1->dikNum].flags & 1) != 0
          || v8 == 32 && v2 < stdControl_aJoystickMaxButtons[v6]
          || v8 == 16 && stdControl_aJoystickEnabled[v6] )
        {
            jkGuiRend_DarrayReallocStr(&jkGuiJoystick_darray2, wtmp, v7);
        }
        ++v1;
        ++v7;
    }
    while ( v1 < &jkGuiJoystick_aEntries[36] );
    jkGuiRend_DarrayReallocStr(&jkGuiJoystick_darray2, 0, 0);
    jkGuiRend_DarrayReallocStr(&jkGuiJoystick_darray, 0, 0);
    jkGuiRend_DarrayReallocStr(&jkGuiJoystick_darray3, 0, 0);
    jkGuiRend_SetClickableString(&jkGuiJoystick_aElements[11], &jkGuiJoystick_darray2);
    jkGuiRend_SetClickableString(&jkGuiJoystick_aElements[12], &jkGuiJoystick_darray);
    jkGuiRend_SetClickableString(&jkGuiJoystick_aElements[13], &jkGuiJoystick_darray3);
}

int jkGuiJoystick_EnumFunc(int inputFuncIdx, char *pInputFuncStr, uint32_t flags, int dxKeyNum, uint32_t dikNum, int flags2, stdControlKeyInfoEntry *pControlEntry, Darray *pDarr)
{
    int v8; // ebx
    wchar_t *v9; // esi
    wchar_t *v10; // eax
    int v11; // ebp
    int v12; // edi
    int i; // esi
    jkGuiJoystickEntry* v14; // eax
    wchar_t *v16; // [esp+10h] [ebp-224h]
    char v17[32]; // [esp+14h] [ebp-220h] BYREF
    wchar_t v18[256]; // [esp+34h] [ebp-200h] BYREF

    v8 = 0;
    v9 = jkGuiJoystick_waIdk2;
    if ( (flags & 1) == 0 )
        return 1;
    v10 = jkStrings_GetText2(pInputFuncStr);
    v16 = v10;
    if ( !v10 )
        return 1;
    v11 = inputFuncIdx;
    if ( (flags & 2) != 0 )
    {
        _strncpy(v17, pInputFuncStr, 0x1Fu);
        v17[31] = 0;
        if ( (flags2 & 1) != 0 )
        {
            strncat(v17, "_A", 0x20u);
            v8 = 1;
        }
        else if ( (flags2 & 4) != 0 )
        {
            strncat(v17, "_R", 0x20u);
            v11 = inputFuncIdx | 0x80000000;
        }
        else
        {
            strncat(v17, "_K", 0x20u);
        }
        v9 = jkStrings_GetText(v17);
        if ( !v9 )
            return 1;
        v10 = v16;
    }
    jk_snwprintf(v18, 0xFFu, L"%ls%ls", v10, v9);
    if ( v8 )
    {
        v12 = jkGuiJoystick_darray.total;
        for ( i = 0; i < v12; ++i )
        {
            if ( jkGuiRend_GetId(&jkGuiJoystick_darray, i) == v11 )
                break;
        }
        if ( i == v12 )
        {
            jkGuiRend_DarrayReallocStr(&jkGuiJoystick_darray, v18, v11);
            goto LABEL_23;
        }
    }
    else
    {
        v12 = jkGuiJoystick_darray3.total;
        for ( i = 0; i < v12; ++i )
        {
            if ( jkGuiRend_GetId(&jkGuiJoystick_darray3, i) == v11 )
                break;
        }
        if ( i == v12 )
        {
            jkGuiRend_DarrayReallocStr(&jkGuiJoystick_darray3, v18, v11);
            goto LABEL_23;
        }
    }
    v12 = i;
LABEL_23:
    if ( pControlEntry )
    {
        v14 = &jkGuiJoystick_aEntries[0];
        do
        {
            if ( dikNum == v14->dikNum )
            {
                v14->inputFunc = inputFuncIdx;
                v14->flags = flags;
                v14->dxKeyNum = dxKeyNum;
                v14->binaryAxisValInt = v12;
                v14->pControlEntry = pControlEntry;
            }
            ++v14;
        }
        while ( v14 < &jkGuiJoystick_aEntries[36] );
    }
    return 1;
}

int jkGuiJoystick_ClickList3(jkGuiElement *pElement, jkGuiMenu *pMenu, int mouseX, int mouseY, int bRedraw)
{
    jkGuiMenu *v6; // edi
    char *v7; // edx
    int v8; // esi
    int v9; // edi
    unsigned int v10; // eax
    int v11; // ebx
    int v12; // edi
    unsigned int v13; // esi
    int v14; // eax
    int v15; // ebp
    int v16; // esi
    wchar_t *v17; // eax
    wchar_t *v18; // [esp-14h] [ebp-14h]

    if ( jkGuiJoystick_dword_5576F0 )
        return 0;
    v6 = pMenu;
    jkGuiRend_ClickSound(pElement, pMenu, mouseX, mouseY, bRedraw);
    if ( pElement->texInfo.anonymous_18 )
    {
        v7 = pMenu->soundClick;
        jkGuiJoystick_dword_557128 = 0;
        jkGuiRend_PlayWav(v7);
    }
    if ( bRedraw )
    {
        v8 = pElement->selectedTextEntry;
        v9 = jkGuiRend_GetId(&jkGuiJoystick_darray2, jkGuiJoystick_aElements[11].selectedTextEntry);
        v10 = jkGuiRend_GetId(&jkGuiJoystick_darray3, v8);
        v11 = v10 & ~0x80000000;
        v12 = v9;
        v13 = v10 >> 29;
        v14 = jkGuiJoystick_aEntries[v12].inputFunc;
        v15 = jkGuiJoystick_aEntries[v12].dikNum;
        v16 = v13 & 4;
        if ( v14 != -1 )
            sithControl_ShiftFuncKeyinfo(v14, jkGuiJoystick_aEntries[v12].dxKeyNum);
        if ( sithControl_MapFunc(v11, v15, v16) )
        {
            jkGuiJoystick_sub_41B390();
        }
        else
        {
            v18 = jkStrings_GetText("ERR_CANNOT_BIND_CONTROL");
            v17 = jkStrings_GetText("ERROR");
            jkGuiDialog_ErrorDialog(v17, v18);
            jkGuiJoystick_Draw(&jkGuiJoystick_menu, 0);
            jkGuiRend_Paint(&jkGuiJoystick_menu);
        }
        v6 = pMenu;
        jkGuiJoystick_dword_557128 = 0;
    }
    jkGuiJoystick_Draw(v6, 1);
    return 0;
}

int jkGuiJoystick_AddEditClick(jkGuiElement *pElement, jkGuiMenu *pMenu, int mouseX, int mouseY, int bRedraw)
{
    if ( !jkGuiJoystick_dword_5576F0 )
    {
        jkGuiJoystick_dword_557128 = 1;
        jkGuiRend_PlayWav(pMenu->soundClick);
        jkGuiJoystick_Draw(pMenu, 1);
    }
    return 0;
}

int jkGuiJoystick_RemoveClick(jkGuiElement *pElement, jkGuiMenu *pMenu, int mouseX, int mouseY, int bRedraw)
{
    int v5; // eax

    v5 = jkGuiRend_GetId(&jkGuiJoystick_darray2, jkGuiJoystick_aElements[11].selectedTextEntry);
    if ( !jkGuiJoystick_dword_5576F0 )
    {
        sithControl_ShiftFuncKeyinfo(jkGuiJoystick_aEntries[v5].inputFunc, jkGuiJoystick_aEntries[v5].dxKeyNum);
        jkGuiRend_PlayWav(pMenu->soundClick);
        jkGuiJoystick_sub_41B390();
        jkGuiJoystick_dword_536B9C = -1;
        jkGuiJoystick_dword_536B98 = -1;
        jkGuiJoystick_Draw(pMenu, 1);
    }
    return 0;
}

int jkGuiJoystick_OkCancelClick(jkGuiElement *pElement, jkGuiMenu *pMenu, int mouseX, int mouseY, int bRedraw)
{
    int result; // eax
    int v6; // esi
    int v7; // edi
    unsigned int v8; // eax
    int v9; // ebx
    int v10; // edi
    unsigned int v11; // esi
    int v12; // eax
    int v13; // ebp
    int v14; // esi
    wchar_t *v15; // eax
    wchar_t *v16; // [esp-4h] [ebp-14h]

    if ( !jkGuiJoystick_dword_5576F0 )
    {
        jkGuiRend_PlayWav(pMenu->soundClick);
        result = pElement->hoverId;
        if ( !jkGuiJoystick_dword_557128 )
            return result;
        if ( result == 1 && jkGuiJoystick_aElements[11].bIsVisible )
        {
            if ( jkGuiJoystick_aElements[13].bIsVisible )
            {
                v6 = jkGuiJoystick_aElements[13].selectedTextEntry;
                v7 = jkGuiRend_GetId(&jkGuiJoystick_darray2, jkGuiJoystick_aElements[11].selectedTextEntry);
                v8 = jkGuiRend_GetId(&jkGuiJoystick_darray3, v6);
                v9 = v8 & ~0x80000000;
                v10 = v7;
                v11 = v8 >> 29;
                v12 = jkGuiJoystick_aEntries[v10].inputFunc;
                v13 = jkGuiJoystick_aEntries[v10].dikNum;
                v14 = v11 & 4;
                if ( v12 != -1 )
                    sithControl_ShiftFuncKeyinfo(v12, jkGuiJoystick_aEntries[v10].dxKeyNum);
                if ( sithControl_MapFunc(v9, v13, v14) )
                {
                    jkGuiJoystick_sub_41B390();
                }
                else
                {
                    v16 = jkStrings_GetText("ERR_CANNOT_BIND_CONTROL");
                    v15 = jkStrings_GetText("ERROR");
                    jkGuiDialog_ErrorDialog(v15, v16);
                    jkGuiJoystick_Draw(&jkGuiJoystick_menu, 0);
                    jkGuiRend_Paint(&jkGuiJoystick_menu);
                }
            }
            else if ( jkGuiJoystick_aElements[12].bIsVisible )
            {
                jkGuiJoystick_BindControl(jkGuiJoystick_aElements[11].selectedTextEntry, jkGuiJoystick_aElements[12].selectedTextEntry);
            }
        }
        jkGuiJoystick_dword_557128 = 0;
        jkGuiJoystick_Draw(pMenu, 1);
    }
    return 0;
}

int jkGuiJoystick_RestoreDefaultsClick(jkGuiElement *pElement, jkGuiMenu *pMenu, int mouseX, int mouseY, int bRedraw)
{
    wchar_t *v6; // eax
    wchar_t *v7; // [esp-8h] [ebp-8h]

    if ( jkGuiJoystick_dword_5576F0 )
        return 0;
    jkGuiRend_PlayWav(pMenu->soundClick);
    v7 = jkStrings_GetText("GUI_RESTORE_DEFAULTS_Q");
    v6 = jkStrings_GetText("GUI_RESTORE_DEFAULTS");
    if ( jkGuiDialog_YesNoDialog(v6, v7) )
        sithControl_JoyInputInit();
    jkGuiJoystick_sub_41B390();
    jkGuiJoystick_dword_536B9C = -1;
    jkGuiJoystick_dword_536B98 = -1;
    jkGuiJoystick_Draw(pMenu, 0);
    jkGuiRend_Paint(pMenu);
    return 0;
}

int jkGuiJoystick_CaptureClick(jkGuiElement *pElement, jkGuiMenu *pMenu, int mouseX, int mouseY, int bRedraw)
{
    if ( !jkGuiJoystick_dword_5576F0 )
    {
        jkGuiRend_PlayWav(pMenu->soundClick);
        jkGuiJoystick_dword_5576F0 = 1;
        jkGuiJoystick_MenuTick(pMenu);
    }
    return 0;
}

int jkGuiJoystick_CalibrateClick(jkGuiElement *pElement, jkGuiMenu *pMenu, int mouseX, int mouseY, int bRedraw)
{
    if ( !jkGuiJoystick_dword_5576F0 )
    {
        jkGuiRend_PlayWav(pMenu->soundClick);
        Windows_CalibrateJoystick();
    }
    return 0;
}

void jkGuiJoystick_MenuTick(jkGuiMenu *pMenu)
{
    int v1; // eax
    int v2; // ebp
    wchar_t *v3; // eax
    jkGuiJoystickEntry *v4; // esi
    jkGuiJoystickEntry* v5; // eax
    int v6; // ecx
    char *v7; // ecx
    jkGuiJoystickEntry* v8; // ebx
    int v9; // eax
    int v10; // esi
    int v11; // edi
    double v12; // st7
    double v14; // st7
    wchar_t *v15; // esi
    wchar_t *v16; // eax
    jkGuiMenu *v17; // esi
    unsigned int v18; // [esp-4h] [ebp-28h]
    int v19; // [esp-4h] [ebp-28h]
    float *v20; // [esp+10h] [ebp-14h]
    int v21; // [esp+14h] [ebp-10h]
    int pOut; // [esp+18h] [ebp-Ch] BYREF
    int v23; // [esp+1Ch] [ebp-8h]
    jkGuiJoystickStrings *v24; // [esp+20h] [ebp-4h]

    while ( 1 )
    {
        v1 = jkGuiJoystick_dword_5576F0;
        v2 = 0;
        v21 = 0;
        v23 = 0;
        if ( jkGuiJoystick_dword_5576F0 && !jkGuiJoystick_dword_5576F4 )
        {
            jkGuiJoystick_aElements[27].bIsVisible = 1;
            jkGuiJoystick_aElements[29].bIsVisible = 1;
            jkGuiJoystick_aElements[30].bIsVisible = 1;
            jkGuiJoystick_aElements[31].bIsVisible = 1;
            jkGuiJoystick_aElements[11].bIsVisible = 0;
            jkGuiJoystick_aElements[26].bIsVisible = 0;
            jkGuiJoystick_aElements[19].bIsVisible = 0;
            jkGuiJoystick_aElements[20].bIsVisible = 0;
            jkGuiJoystick_aElements[21].bIsVisible = 0;
            jkGuiJoystick_aElements[22].bIsVisible = 0;
            v3 = jkStrings_GetText("GUI_CAPTURE_TEXT");
            _wcsncpy(jkGuiJoystick_awTmp, v3, 0xFFu);
            jkGuiJoystick_awTmp[255] = 0;
            if ( jkGuiJoystick_dword_557078 )
            {
                stdControl_ToggleCursor(1);
                stdControl_bControlsActive = 0;
            }
            else
            {
                stdControl_Open();
            }
            stdControl_Flush();
            v4 = &jkGuiJoystick_aEntries[0];
            memset(jkGuiJoystick_aUnk1, 0, sizeof(jkGuiJoystick_aUnk1));
            do
            {
                if ( (v4->keybits & 0x30) == 0 )
                {
                    v18 = v4->dikNum;
                    jkGuiJoystick_aUnk1[v18] = stdControl_aJoysticks[v18].flags & 2;
                    stdControl_EnableAxis(v18);
                }
                v4++;
            }
            while ( v4 < &jkGuiJoystick_aEntries[36] );
            v1 = jkGuiJoystick_dword_5576F0;
            v23 = 1;
            v21 = 1;
        }
        if ( !v1 && jkGuiJoystick_dword_5576F4 )
        {
            jkGuiJoystick_dword_536B98 = -1;
            jkGuiJoystick_dword_536B9C = -1;
            jkGuiJoystick_aElements[27].bIsVisible = 0;
            jkGuiJoystick_aElements[29].bIsVisible = 0;
            jkGuiJoystick_aElements[30].bIsVisible = 0;
            jkGuiJoystick_aElements[31].bIsVisible = 0;
            jkGuiJoystick_aElements[11].bIsVisible = 1;
            jkGuiJoystick_aElements[26].bIsVisible = 1;
            jkGuiJoystick_Draw(pMenu, 0);
            v5 = &jkGuiJoystick_aEntries[0];
            do
            {
                v6 = v5->dikNum;
                if ( (v5->keybits & 0x30) == 0 && !jkGuiJoystick_aUnk1[v6] )
                    stdControl_aJoysticks[v6].flags &= ~2u;
                ++v5;
            }
            while ( v5 < &jkGuiJoystick_aEntries[36] );
            if ( jkGuiJoystick_dword_557078 )
                stdControl_ToggleCursor(0);
            else
                stdControl_Close();
            v1 = jkGuiJoystick_dword_5576F0;
            v21 = 1;
        }
        jkGuiJoystick_dword_5576F4 = v1;
        if ( !v1 )
            goto LABEL_44;
        pOut = 0;
        stdControl_bControlsActive = 1;
        stdControl_ReadControls();
        memset(&jkGuiJoystick_strings, 0, sizeof(jkGuiJoystick_strings));
        stdControl_ReadKey(1, &pOut);
        if ( !pOut )
            break;
        stdControl_FinishRead();
        v7 = pMenu->soundClick;
        jkGuiJoystick_dword_5576F0 = 0;
        stdControl_bControlsActive = jkGuiJoystick_dword_557078 == 0;
        jkGuiRend_PlayWav(v7);
    }
    v24 = &jkGuiJoystick_strings;
    v15 = v24->aStrings[0];
    v20 = jkGuiJoystick_aFloats;
    v8 = &jkGuiJoystick_aEntries[0];
    while ( 1 )
    {
        v9 = v8->dikNum;
        if ( (v8->keybits & 0x30) != 0 )
        {
            if ( !stdControl_ReadKey(v9, &pOut) )
                goto LABEL_36;
LABEL_35:
            v2 = 1;
            goto LABEL_36;
        }
        v10 = v9;
        v19 = v8->dikNum;
        v11 = stdControl_aJoysticks[v9].flags;
        stdControl_aJoysticks[v9].flags = v11 | 2;
        v12 = stdControl_ReadAxis(v19);
        stdControl_aJoysticks[v10].flags = v11;
        if ( v23 != 0 )
        {
            *v20 = v12;
            goto LABEL_36;
        }
        v14 = v12 - *v20;
        if ( v14 < 0.0 )
            v14 = -v14;
        if ( v14 > 0.2 )
            goto LABEL_35;
LABEL_36:
        if ( v2 )
        {
            if ( v15 < v24->aStrings[3] )
            {
                v16 = jkStrings_GetText(v8->displayStrKey);
                _wcscpy(v15, v16);
            }
            v15 = v24->aStrings[1];
        }
        ++v8;
        if ( ++v20 >= &jkGuiJoystick_aFloats[36] )
            break;
        v2 = 0;
    }
    stdControl_FinishRead();
    stdControl_bControlsActive = jkGuiJoystick_dword_557078 == 0;
    if ( !v21 )
    {
        v17 = pMenu;
        jkGuiRend_UpdateAndDrawClickable(&jkGuiJoystick_aElements[29], pMenu, 1);
        jkGuiRend_UpdateAndDrawClickable(&jkGuiJoystick_aElements[30], pMenu, 1);
        jkGuiRend_UpdateAndDrawClickable(&jkGuiJoystick_aElements[31], pMenu, 1);
        v1 = jkGuiJoystick_dword_5576F0;
        goto LABEL_45;
    }
    v1 = jkGuiJoystick_dword_5576F0;
LABEL_44:
    v17 = pMenu;
LABEL_45:
    if ( v21 )
    {
        jkGuiRend_Paint(v17);
        v1 = jkGuiJoystick_dword_5576F0;
    }
    jkGuiRend_SetCursorVisible(v1 == 0);
}

int jkGuiJoystick_Show()
{
    int v0; // edi
    stdControlKeyInfoEntry *v1; // eax
    double v2; // st7

    jkGuiJoystick_dword_557078 = stdControl_bOpen;
    jkGuiJoystick_dword_5576F4 = 0;
    jkGuiJoystick_dword_5576F0 = 0;
    jkGuiRend_DarrayNewStr(&jkGuiJoystick_darray2, 64, 1);
    jkGuiRend_DarrayNewStr(&jkGuiJoystick_darray, 64, 1);
    jkGuiRend_DarrayNewStr(&jkGuiJoystick_darray3, 64, 1);
    jkGuiJoystick_sub_41B390();
    jkGui_sub_412E20(&jkGuiJoystick_menu, 100, 104, 104);
    jkGui_sub_412E20(&jkGuiJoystick_menu, 105, 108, 107);
    jkGuiJoystick_aElements[12].bIsVisible = 1;
    jkGuiJoystick_aElements[13].bIsVisible = 0;
    jkGuiJoystick_aElements[27].bIsVisible = 0;
    jkGuiJoystick_aElements[28].bIsVisible = 0;
    jkGuiJoystick_aElements[29].bIsVisible = 0;
    jkGuiJoystick_aElements[30].bIsVisible = 0;
    jkGuiJoystick_aElements[31].bIsVisible = 0;
    jkGuiJoystick_aElements[26].func = jkGuiJoystick_DisableJoystickClick;
    jkGuiJoystick_aElements[11].selectedTextEntry = 0;
    jkGuiJoystick_aElements[12].selectedTextEntry = 0;
    jkGuiJoystick_aElements[13].selectedTextEntry = 0;
    jkGuiJoystick_dword_557128 = 0;
    jkGuiJoystick_dword_536B98 = -1;
    jkGuiJoystick_dword_536B9C = -1;
    jkGuiJoystick_aElements[26].selectedTextEntry = (sithWeapon_controlOptions >> 5) & 1;
    jkGuiJoystick_Draw(&jkGuiJoystick_menu, 0);
    jkGuiRend_SetElementIdk(&jkGuiJoystick_aElements[14], 45);
    jkGuiRend_SetElementIdk(&jkGuiJoystick_aElements[16], 46);
    jkGuiRend_MenuSetLastElement(&jkGuiJoystick_menu, &jkGuiJoystick_aElements[23]);
    jkGuiRend_SetDisplayingStruct(&jkGuiJoystick_menu, &jkGuiJoystick_aElements[24]);
    jkGuiSetup_sub_412EF0(&jkGuiJoystick_menu, 1);
    v0 = jkGuiRend_DisplayAndReturnClicked(&jkGuiJoystick_menu);
    if ( jkGuiJoystick_aElements[11].bIsVisible )
    {
        v1 = jkGuiJoystick_aEntries[jkGuiRend_GetId(&jkGuiJoystick_darray2, jkGuiJoystick_aElements[11].selectedTextEntry)].pControlEntry;
        if ( jkGuiJoystick_aElements[22].bIsVisible )
        {
            if ( jkGuiJoystick_aElements[22].selectedTextEntry > 50 )
                v2 = (double)(jkGuiJoystick_aElements[22].selectedTextEntry - 50) * 0.059999999 - -1.0;
            else
                v2 = (double)jkGuiJoystick_aElements[22].selectedTextEntry * 0.015 - -0.25;
            v1->binaryAxisVal = v2;
        }
        if ( jkGuiJoystick_aElements[20].bIsVisible )
            v1->flags = v1->flags & ~8u | (jkGuiJoystick_aElements[20].selectedTextEntry != 0 ? 8 : 0);
        if ( jkGuiJoystick_aElements[19].bIsVisible )
            v1->flags = v1->flags & ~4u | (jkGuiJoystick_aElements[19].selectedTextEntry != 0 ? 0 : 4);
    }
    if ( jkGuiJoystick_aElements[26].selectedTextEntry )
        sithWeapon_controlOptions |= 0x20;
    else
        sithWeapon_controlOptions &= ~0x20;

    if ( v0 == 1 )
        jkPlayer_WriteConf(jkPlayer_playerShortName);
    else
        jkPlayer_ReadConf(jkPlayer_playerShortName);
    jkGuiRend_DarrayFree(&jkGuiJoystick_darray2);
    jkGuiRend_DarrayFree(&jkGuiJoystick_darray);
    jkGuiRend_DarrayFree(&jkGuiJoystick_darray3);
    return v0;
}

int jkGuiJoystick_DisableJoystickClick(jkGuiElement *pElement, jkGuiMenu *pMenu, int mouseX, int mouseY, int bRedraw)
{
    if ( !jkGuiJoystick_dword_5576F0 )
    {
        jkGuiRend_DrawClickableAndUpdatebool(pElement, pMenu,0,0,0);
        jkGuiJoystick_dword_536B98 = -1;
        jkGuiJoystick_dword_536B9C = -1;
        jkGuiJoystick_Draw(pMenu, 1);
    }
    return 0;
}

void jkGuiJoystick_Initialize()
{
    jkGui_InitMenu(&jkGuiJoystick_menu, jkGui_stdBitmaps[3]);
}

void jkGuiJoystick_Shutdown()
{
    ;
}
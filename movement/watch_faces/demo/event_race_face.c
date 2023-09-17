/*
 * MIT License
 *
 * Copyright (c) 2023 <#author_name#>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdlib.h>
#include "event_race_face.h"

void event_race_face_setup(movement_settings_t *settings, uint8_t watch_face_index, void ** context_ptr) {
    (void) settings;
    if (*context_ptr == NULL) *context_ptr = malloc(sizeof(uint8_t));
}

void event_race_face_activate(movement_settings_t *settings, void *context) {
    (void) settings;
    *((uint8_t *)context) = 0;
    movement_request_tick_frequency(64);
}

static void _disp_ctr(uint8_t ctr) {
    char* buf = " ";
    buf[0] = '0' + ctr;
    watch_display_string(buf, 7);
}

bool event_race_face_loop(movement_event_t event, movement_settings_t *settings, void *context) {
    uint8_t* ctr_ptr = (uint8_t *)context;

    switch (event.event_type) {
        case EVENT_ACTIVATE:
            _disp_ctr(*ctr_ptr);
            break;
        case EVENT_TICK:
            break;
        case EVENT_ALARM_BUTTON_UP:
            *ctr_ptr = (*ctr_ptr + 1) % 10;
            _disp_ctr(*ctr_ptr);
            break;
    }

    return true;
}

void event_race_face_resign(movement_settings_t *settings, void *context) {
    (void) settings;
    (void) context;
}


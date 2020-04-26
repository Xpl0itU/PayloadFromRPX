/***************************************************************************
 * Copyright (C) 2016
 * by Dimok
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any
 * damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any
 * purpose, including commercial applications, and to alter it and
 * redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you
 * must not claim that you wrote the original software. If you use
 * this software in a product, an acknowledgment in the product
 * documentation would be appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and
 * must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source
 * distribution.
 ***************************************************************************/
#include "utils.h"
#include "types.h"

#define mcp_rodata_phys(addr) ((u32)(addr) - 0x05060000 + 0x08220000)
#define mcp_data_phys(addr) ((u32)(addr) - 0x05074000 + 0x08234000)
#define acp_phys(addr) ((u32)(addr) - 0xE0000000 + 0x12900000)

void instant_patches_setup(void) {
   
    // fix 10 minute timeout that crashes MCP after 10 minutes of booting
    *(volatile u32*)(0x05022474 - 0x05000000 + 0x081C0000) = 0xFFFFFFFF;    // NEW_TIMEOUT
    
    // patch default title id to system menu
    *(volatile u32*)mcp_data_phys(0x050B817C) = *(volatile u32*)0x0017FFF0;
    *(volatile u32*)mcp_data_phys(0x050B8180) = *(volatile u32*)0x0017FFF4;

    // force check USB storage on load
    *(volatile u32*)acp_phys(0xE012202C) = 0x00000001; // find USB flag
}

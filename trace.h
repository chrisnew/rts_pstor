/* Driver for Realtek PCI-Express card reader
 * Header file
 *
 * Copyright(c) 2009 Realtek Semiconductor Corp. All rights reserved.  
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, see <http:
 *
 * Author:
 *   wwang (wei_wang@realsil.com.cn)
 *   No. 450, Shenhu Road, Suzhou Industry Park, Suzhou, China
 */

#ifndef __REALTEK_RTSX_TRACE_H
#define __REALTEK_RTSX_TRACE_H

#define _MSG_TRACE

#ifdef _MSG_TRACE
static inline char *filename(char *path)
{
	char *ptr;

	if (path == NULL) {
		return NULL;
	}

	ptr = path;

	while (*ptr != '\0') {
		if ((*ptr == '\\') || (*ptr == '/')) {
			path = ptr + 1;
		}
		ptr ++;
	}

	return path;
}

#define TRACE_RET(chip, ret)   										\
do {													\
	char *_file = filename(__FILE__);								\
	RTSX_DEBUGP(("[%s][%s]:[%d]\n", _file, __FUNCTION__, __LINE__));				\
	(chip)->trace_msg[(chip)->msg_idx].line = (u16)(__LINE__);					\
	strncpy((chip)->trace_msg[(chip)->msg_idx].func, __FUNCTION__, MSG_FUNC_LEN-1);			\
	strncpy((chip)->trace_msg[(chip)->msg_idx].file, _file, MSG_FILE_LEN-1); 			\
	get_current_time((chip)->trace_msg[(chip)->msg_idx].timeval_buf, TIME_VAL_LEN);			\
	(chip)->trace_msg[(chip)->msg_idx].valid = 1;							\
	(chip)->msg_idx ++; 										\
	if ((chip)->msg_idx >= TRACE_ITEM_CNT) { 							\
		(chip)->msg_idx = 0;									\
	}												\
	return (ret); 											\
} while (0)

#define TRACE_GOTO(chip, label)   									\
do {													\
	char *_file = filename(__FILE__);								\
	RTSX_DEBUGP(("[%s][%s]:[%d]\n", _file, __FUNCTION__, __LINE__));				\
	(chip)->trace_msg[(chip)->msg_idx].line = (u16)(__LINE__);					\
	strncpy((chip)->trace_msg[(chip)->msg_idx].func, __FUNCTION__, MSG_FUNC_LEN-1);			\
	strncpy((chip)->trace_msg[(chip)->msg_idx].file, _file, MSG_FILE_LEN-1); 			\
	get_current_time((chip)->trace_msg[(chip)->msg_idx].timeval_buf, TIME_VAL_LEN);			\
	(chip)->trace_msg[(chip)->msg_idx].valid = 1;							\
	(chip)->msg_idx ++; 										\
	if ((chip)->msg_idx >= TRACE_ITEM_CNT) { 							\
		(chip)->msg_idx = 0;									\
	}												\
	goto label; 											\
} while (0)
#else
#define TRACE_RET(chip, ret)	return (ret)
#define TRACE_GOTO(chip, label)	goto label
#endif

#if DBG

#include "general.h"

#define CATCH_TRIGGER1(chip)				\
do {							\
	if (trigger_enabled) {				\
		rtsx_writeb((chip), 0x1F, 0xFF);	\
		rtsx_writeb((chip), 0x1F, 0x00);	\
		RTSX_DEBUGP(("Catch trigger1!\n"));	\
	}						\
} while (0)

#define CATCH_TRIGGER2(chip)				\
do {							\
	if (trigger_enabled) {				\
		rtsx_writeb((chip), 0x20, 0xFF);	\
	}						\
} while (0)

#define ENABLE_TRIGGER()			\
do {						\
	trigger_enabled = 1;			\
} while (0)

#define DISABLE_TRIGGER()			\
do {						\
	trigger_enabled = 0;			\
} while (0)

#else

#define CATCH_TRIGGER1(chip)
#define CATCH_TRIGGER2(chip)
#define ENABLE_TRIGGER()
#define DISABLE_TRIGGER()

#endif

#if DBG
static inline void rtsx_dump(u8 *buf, int buf_len)
{
	int i;
	u8 tmp[16] = {0};
	u8 *_ptr = buf;
	
	for (i = 0; i < ((buf_len)/16); i++) {
		RTSX_DEBUGP(("%02x %02x %02x %02x %02x %02x %02x %02x "
			"%02x %02x %02x %02x %02x %02x %02x %02x\n",
			_ptr[0], _ptr[1], _ptr[2], _ptr[3], _ptr[4], _ptr[5], 
			_ptr[6], _ptr[7], _ptr[8], _ptr[9], _ptr[10], _ptr[11],
			_ptr[12], _ptr[13], _ptr[14], _ptr[15]));
		_ptr += 16;
	}
	if ((buf_len) % 16) {
		memcpy(tmp, _ptr, (buf_len) % 16);
		_ptr = tmp;
		RTSX_DEBUGP(("%02x %02x %02x %02x %02x %02x %02x %02x "
			"%02x %02x %02x %02x %02x %02x %02x %02x\n",
			_ptr[0], _ptr[1], _ptr[2], _ptr[3], _ptr[4], _ptr[5],
			_ptr[6], _ptr[7], _ptr[8], _ptr[9], _ptr[10], _ptr[11],
			_ptr[12], _ptr[13], _ptr[14], _ptr[15]));
	}	
}

#define RTSX_DUMP(buf, buf_len)		rtsx_dump((u8 *)(buf), (buf_len))

#else
#define RTSX_DUMP(buf, buf_len)
#endif

#endif  

#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

enum { COMMAND_N_CHARACTERS = 0x00
     , COMMAND_N_ROWS       = 0x01
     , COMMAND_SEND_DATA    = 0x02
     , COMMAND_VERSION      = 0x03
     , COMMAND_SEND_ERROR   = 0x04
     , COMMAND_SEND_OK      = 0x05
     , COMMAND_SEND_LINE    = 0x06
     , COMMAND_RESET        = 0x07
     , COMMAND_TEST_MODE    = 't'
     };

#endif// __PROTOCOL_H__

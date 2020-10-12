#ifndef FUNC_CODE_H
#define FUNC_CODE_H 1


#define FC_READ_COILS                       (char) 0x01
#define FC_READ_DISCRETE_INPUTS             (char) 0x02
#define FC_READ_HOLDING_REGISTERS           (char) 0x03
#define FC_READ_INPUT_REGISTERS             (char) 0x04
#define FC_READ_FIFO_QUEUE                  (char) 0x18

#define FC_WRITE_SINGLE_COIL                (char) 0x05
#define FC_WRITE_SINGLE_REGISTER            (char) 0x06
#define FC_WRITE_MULTIPLE_COILS             (char) 0x0F
#define FC_WRITE_MULTIPLE_REGISTERS         (char) 0x10
#define FC_MASK_WRITE_REGISTER              (char) 0x16

#define FC_READ_WRITE_MULTIPLE_REGISTERS    (char) 0x17

#define FC_READ_EXCEPTION_STATUS            (char) 0x07
#define FC_DIAGNOSTICS                      (char) 0x08
#define FC_ENCAPSULATED_INTERFACE_TRANSPORT (char) 0x2B

#define FC_GET_COMM_EVENT_COUNTER           (char) 0x0B
#define FC_GET_COMM_EVENT_LOG               (char) 0x0C

#define FC_REPORT_SLAVE_ID                  (char) 0x11

#define FC_READ_FILE_RECORD                 (char) 0x14
#define FC_WRITE_FILE_RECORD                (char) 0x15

#define FC_IS_EXCEPTION(X) !!((X) & (0x80))
#define FC_GET(X) ((X) & (0x80 - 1))

#endif
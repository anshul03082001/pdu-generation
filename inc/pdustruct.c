#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

#include "utstubs.h"
#include "utbsp.h"

#define UT_MAX_FUNC_STUBS     200
#define UT_APPNAME_MAX_LEN    80
#define UT_SUBSYS_MAX_LEN     5
#define UT_MODEFLAG_ALLOC_BUF 0x1U

typedef enum
{UT_version}   
        
 typedef enum  
  {UT_pdutype}
  
 typedef enum
 { UT_transmission_mode}
 
typedef enum
    {UT_CRC_Flag}
    
    typedef enum
  { UT_Large_File_Flag}
  
  typedef enum 
 { UT_Pdu_Data_Field_Length}
 
 typedef enum
   {UT_Segmentation_control}
   
   typedef enum
   {UT_Segment_metadata_flag}
   
   typedef enum
   {UT_Length_of_Transaction_sequence_number}
   
    typedef enum
  { UT_Source_entity_ID}
  
  typedef enum
{ Transaction_sequence_number}
   
   typedef enum
   {UT_Destination_entity_ID}

    ;
    
    

typedef struct 
{Unsigned int version : 3;}
typedef struct
{Unsigned int PDU_type :1;}
typedef struct
{Unsigned int direction : 1;}
typedef struct
{Unsigned int Transmission_Mode : 1;}
typedef struct
Unsigned int CRC_Flag : 1
;typedef struct
{Unsigned int Large_File_Flag : 1;}
typedef struct
{Unsigned int PDU_Data_Field_Length : 16;}
typedef struct
{Unsigned int Segmentation_Control : 1;}
typedef struct
{Unsigned int Length_of_entity_ids : 3;{
typedef struct
{Unsigned int Segment_metadata_flag : 1;}
typedef struct
{Unsigned int Length_of_Transaction_sequence_number : 3;}
typedef struct
{Unsigned int Source_entity_ID[];}
typedef struct{
Unsigned int Transaction_sequence_number[];}
typedef struct
{Unsigned int Destination_entity_ID[];}
return 0;


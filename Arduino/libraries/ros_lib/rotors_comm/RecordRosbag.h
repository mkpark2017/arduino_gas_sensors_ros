#ifndef _ROS_SERVICE_RecordRosbag_h
#define _ROS_SERVICE_RecordRosbag_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rotors_comm
{

static const char RECORDROSBAG[] = "rotors_comm/RecordRosbag";

  class RecordRosbagRequest : public ros::Msg
  {
    public:
      typedef bool _record_type;
      _record_type record;

    RecordRosbagRequest():
      record(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_record;
      u_record.real = this->record;
      *(outbuffer + offset + 0) = (u_record.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->record);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_record;
      u_record.base = 0;
      u_record.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->record = u_record.real;
      offset += sizeof(this->record);
     return offset;
    }

    const char * getType(){ return RECORDROSBAG; };
    const char * getMD5(){ return "396b06ea5fee4a93fc2d2be6c15809f7"; };

  };

  class RecordRosbagResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;

    RecordRosbagResponse():
      success(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.real = this->success;
      *(outbuffer + offset + 0) = (u_success.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->success);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.base = 0;
      u_success.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->success = u_success.real;
      offset += sizeof(this->success);
     return offset;
    }

    const char * getType(){ return RECORDROSBAG; };
    const char * getMD5(){ return "358e233cde0c8a8bcfea4ce193f8fc15"; };

  };

  class RecordRosbag {
    public:
    typedef RecordRosbagRequest Request;
    typedef RecordRosbagResponse Response;
  };

}
#endif

#ifndef _ROS_concert_workflow_engine_msgs_WorkflowsStatus_h
#define _ROS_concert_workflow_engine_msgs_WorkflowsStatus_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace concert_workflow_engine_msgs
{

  class WorkflowsStatus : public ros::Msg
  {
    public:
      typedef const char* _service_name_type;
      _service_name_type service_name;
      typedef int8_t _status_type;
      _status_type status;
      typedef const char* _message_type;
      _message_type message;
      enum { READY =  1 };
      enum { START =  2 };
      enum { RUNNING =  3 };
      enum { STOP =  4 };
      enum { ERROR =  -1 };

    WorkflowsStatus():
      service_name(""),
      status(0),
      message("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_service_name = strlen(this->service_name);
      varToArr(outbuffer + offset, length_service_name);
      offset += 4;
      memcpy(outbuffer + offset, this->service_name, length_service_name);
      offset += length_service_name;
      union {
        int8_t real;
        uint8_t base;
      } u_status;
      u_status.real = this->status;
      *(outbuffer + offset + 0) = (u_status.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->status);
      uint32_t length_message = strlen(this->message);
      varToArr(outbuffer + offset, length_message);
      offset += 4;
      memcpy(outbuffer + offset, this->message, length_message);
      offset += length_message;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_service_name;
      arrToVar(length_service_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_service_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_service_name-1]=0;
      this->service_name = (char *)(inbuffer + offset-1);
      offset += length_service_name;
      union {
        int8_t real;
        uint8_t base;
      } u_status;
      u_status.base = 0;
      u_status.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->status = u_status.real;
      offset += sizeof(this->status);
      uint32_t length_message;
      arrToVar(length_message, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_message; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_message-1]=0;
      this->message = (char *)(inbuffer + offset-1);
      offset += length_message;
     return offset;
    }

    const char * getType(){ return "concert_workflow_engine_msgs/WorkflowsStatus"; };
    const char * getMD5(){ return "24fa7d7ee2f6b7cfe974804fbd2e1ae0"; };

  };

}
#endif
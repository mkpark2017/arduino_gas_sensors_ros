#ifndef _ROS_concert_workflow_engine_msgs_EnableWorkflows_h
#define _ROS_concert_workflow_engine_msgs_EnableWorkflows_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "concert_workflow_engine_msgs/Workflow.h"

namespace concert_workflow_engine_msgs
{

  class EnableWorkflows : public ros::Msg
  {
    public:
      typedef const char* _service_name_type;
      _service_name_type service_name;
      typedef bool _enable_type;
      _enable_type enable;
      uint32_t workflows_length;
      typedef concert_workflow_engine_msgs::Workflow _workflows_type;
      _workflows_type st_workflows;
      _workflows_type * workflows;

    EnableWorkflows():
      service_name(""),
      enable(0),
      workflows_length(0), workflows(NULL)
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
        bool real;
        uint8_t base;
      } u_enable;
      u_enable.real = this->enable;
      *(outbuffer + offset + 0) = (u_enable.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->enable);
      *(outbuffer + offset + 0) = (this->workflows_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->workflows_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->workflows_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->workflows_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->workflows_length);
      for( uint32_t i = 0; i < workflows_length; i++){
      offset += this->workflows[i].serialize(outbuffer + offset);
      }
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
        bool real;
        uint8_t base;
      } u_enable;
      u_enable.base = 0;
      u_enable.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->enable = u_enable.real;
      offset += sizeof(this->enable);
      uint32_t workflows_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      workflows_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      workflows_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      workflows_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->workflows_length);
      if(workflows_lengthT > workflows_length)
        this->workflows = (concert_workflow_engine_msgs::Workflow*)realloc(this->workflows, workflows_lengthT * sizeof(concert_workflow_engine_msgs::Workflow));
      workflows_length = workflows_lengthT;
      for( uint32_t i = 0; i < workflows_length; i++){
      offset += this->st_workflows.deserialize(inbuffer + offset);
        memcpy( &(this->workflows[i]), &(this->st_workflows), sizeof(concert_workflow_engine_msgs::Workflow));
      }
     return offset;
    }

    const char * getType(){ return "concert_workflow_engine_msgs/EnableWorkflows"; };
    const char * getMD5(){ return "cacdbbe404b169f5b2bf8c4c9a373315"; };

  };

}
#endif
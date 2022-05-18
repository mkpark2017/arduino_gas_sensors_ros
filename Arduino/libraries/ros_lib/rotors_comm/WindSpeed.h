#ifndef _ROS_rotors_comm_WindSpeed_h
#define _ROS_rotors_comm_WindSpeed_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Vector3.h"

namespace rotors_comm
{

  class WindSpeed : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef geometry_msgs::Vector3 _velocity_type;
      _velocity_type velocity;

    WindSpeed():
      header(),
      velocity()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->velocity.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->velocity.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "rotors_comm/WindSpeed"; };
    const char * getMD5(){ return "ae00d2a331b8545eaf96c531128ff0ef"; };

  };

}
#endif
#ifndef _ROS_wind_visualization_Wind_h
#define _ROS_wind_visualization_Wind_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Vector3.h"

namespace wind_visualization
{

  class Wind : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef geometry_msgs::Vector3 _wind_type;
      _wind_type wind;

    Wind():
      header(),
      wind()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->wind.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->wind.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "wind_visualization/Wind"; };
    const char * getMD5(){ return "d800f0587649e6f6b38b23769c101b4f"; };

  };

}
#endif